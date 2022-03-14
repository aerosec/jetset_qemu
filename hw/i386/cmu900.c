/*
 * QEMU PC System Emulator
 *
 * Copyright (c) 2003-2004 Fabrice Bellard
 * Copyright (c) 2015 Regents of the University of California
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "qemu/osdep.h"
#include "hw/sysbus.h" // Must be included before escc.h

#include "hw/block/flash.h"
#include "hw/boards.h"
#include "hw/char/escc.h"
#include "hw/i386/pc.h"
#include "hw/loader.h"
#include "hw/timer/i8254.h"
#include "hw/timer/mc146818rtc.h"
#include "sysemu/qtest.h"
#include "target/i386/cpu.h"
#include "qapi/error.h"
#include "qemu/error-report.h"

/* baud_rate = clock_frequency/(2*clock_mode*(time_constant+2))
 * We know
 *   baud_rate = 9600
 *   clock_mode = 16
 *   time_constant = 0x0018
 * Thus, clock_frequency is 7987200.
 */
#define ESCC_CLOCK 7987200

extern char* concrete_target;

static void add_shared_mem(const char *name, uint64_t addr, uint64_t size)
{
    DeviceState *dev = qdev_create(NULL, "shared-mem-device");
    qdev_prop_set_string(dev, "name", name);
    qdev_prop_set_uint64(dev, "base-addr", addr);
    qdev_prop_set_uint64(dev, "size", size);
    qdev_prop_set_bit(dev, "master", true);
    qdev_init_nofail(dev);
}

static void pc_init_cmu900(MachineState *machine)
{
    //printf("Initializing!\n");
    PCMachineState *pcms = PC_MACHINE(machine);
    MemoryRegion *system_memory = get_system_memory();
    //MemoryRegion *system_io = get_system_io();
    MemoryRegion *ram;
    //ISABus *isa_bus = isa_bus_new(NULL, system_memory, system_io, &error_abort);

    machine->ram_size = 0x01000000;
    pcms->above_4g_mem_size = 0;
    pcms->below_4g_mem_size = machine->ram_size;

    pc_cpus_init(pcms);

    ram = g_malloc(sizeof(*ram));
    memory_region_allocate_system_memory(ram, NULL, "pc.ram",
                                         machine->ram_size);
    memory_region_add_subregion(system_memory, 0, ram);
    // Add the boot flash.
    DriveInfo *dinfo = drive_get(IF_PFLASH, 0, 0);
    if (dinfo) {
        BlockBackend *blk = blk_by_legacy_dinfo(dinfo);

        // Single AM29F080B-90SI (x8).
        // AMD flash command emulation.
        DeviceState *dev = qdev_create(NULL, TYPE_CFI_PFLASH02);
        qdev_prop_set_drive(dev, "drive", blk, &error_abort);
        qdev_prop_set_uint32(dev, "num-blocks", 16);
        qdev_prop_set_uint32(dev, "sector-length", 64*1024);
        qdev_prop_set_uint8(dev, "width", 1); // 1-byte wide interface.
        qdev_prop_set_uint8(dev, "device-width", 1); // x8 mode.
        qdev_prop_set_uint8(dev, "max-device-width", 1); // 8-bit chips.
        qdev_prop_set_uint8(dev, "mappings", 1); // No mapping aliases.
        qdev_prop_set_uint8(dev, "big-endian", 0);
        qdev_prop_set_uint16(dev, "id0", 0x0001); // Manufacturer ID.
        qdev_prop_set_uint16(dev, "id1", 0x00D5); // Device ID (top boot block)
        qdev_prop_set_uint16(dev, "id2", 0xFFFF); // Not used with this chip.
        qdev_prop_set_uint16(dev, "id3", 0xFFFF); // Not used with this chip.
        qdev_prop_set_uint16(dev, "unlock-addr0", 0x0555);
        qdev_prop_set_uint16(dev, "unlock-addr1", 0x02AA);
        qdev_prop_set_string(dev, "name", "cmu900.boot");
        qdev_init_nofail(dev);
        sysbus_mmio_map(SYS_BUS_DEVICE(dev), 0, 0xFFF00000);
    } else {
        if (!qtest_enabled()) {
            error_report("Missing CMU 900 boot flash, use option:\n"
                         "  -drive if=pflash,format=raw,index=0,file=/path/to/boot.bin");
        }
        // Fake a small ROM where the 486 boots.
        // QEMU's TCG goes wild otherwise.
        MemoryRegion *mr = g_malloc(sizeof *mr);
        uint8_t *boot_ram = g_malloc0(16);
        boot_ram[0] = 0xFA; // cli
        boot_ram[1] = 0xF4; // hlt
        boot_ram[2] = 0xEB; // jmp $-3
        boot_ram[3] = -3;
        memory_region_init_ram_ptr(mr, OBJECT(machine), "cmu900.fakeboot", 16, boot_ram);
        memory_region_add_subregion(system_memory, 0xFFFFFFF0, mr);
    }
    //printf("Added the boot flash\n");
    // Add the app flash.
    dinfo = drive_get(IF_PFLASH, 0, 1);
    if (dinfo) {
        BlockBackend *blk = blk_by_legacy_dinfo(dinfo);

        // Four interleaved AM29F032B (x8).
        // AMD flash command emulation.
        DeviceState *dev = qdev_create(NULL, TYPE_CFI_PFLASH02);
        qdev_prop_set_drive(dev, "drive", blk, &error_abort);
        qdev_prop_set_uint32(dev, "num-blocks", 64);
        qdev_prop_set_uint32(dev, "sector-length", 4*64*1024);
        qdev_prop_set_uint8(dev, "width", 4); // 4-byte wide interface.
        qdev_prop_set_uint8(dev, "device-width", 1); // x8 mode.
        qdev_prop_set_uint8(dev, "max-device-width", 1); // 8-bit chips.
        qdev_prop_set_uint8(dev, "mappings", 1); // No mapping aliases.
        qdev_prop_set_uint8(dev, "big-endian", 0);
        qdev_prop_set_uint16(dev, "id0", 0x0001); // Manufacturer ID.
        qdev_prop_set_uint16(dev, "id1", 0x0041); // Device ID (top boot block)
        qdev_prop_set_uint16(dev, "id2", 0xFFFF); // Not used with this chip.
        qdev_prop_set_uint16(dev, "id3", 0xFFFF); // Not used with this chip.
        qdev_prop_set_uint16(dev, "unlock-addr0", 0x0555);
        qdev_prop_set_uint16(dev, "unlock-addr1", 0x02AA);
        qdev_prop_set_string(dev, "name", "cmu900.app");
        qdev_init_nofail(dev);
        sysbus_mmio_map(SYS_BUS_DEVICE(dev), 0, 0x01000000);
    } else if (!qtest_enabled()) {
        error_report("Missing CMU 900 app flash, use option:\n"
                     "  -drive if=pflash,format=raw,index=1,file=/path/to/app.bin");
    }
    // Add the data flash.
    dinfo = drive_get(IF_PFLASH, 0, 2);
    if (dinfo) {
        BlockBackend *blk = blk_by_legacy_dinfo(dinfo);
        assert(blk);

        // Two interleaved AM29LV160DT-90SI in 16-bit word mode (x16).
        // AMD flash command emulation.
        DeviceState *dev = qdev_create(NULL, TYPE_CFI_PFLASH02);
        qdev_prop_set_drive(dev, "drive", blk, &error_abort);
        // Nonuniform flash.
        qdev_prop_set_uint32(dev, "num-blocks0", 31);
        qdev_prop_set_uint32(dev, "sector-length0", 2*64*1024);

        qdev_prop_set_uint32(dev, "num-blocks1", 1);
        qdev_prop_set_uint32(dev, "sector-length1", 2*32*1024);

        qdev_prop_set_uint32(dev, "num-blocks2", 2);
        qdev_prop_set_uint32(dev, "sector-length2", 2*8*1024);

        qdev_prop_set_uint32(dev, "num-blocks3", 1);
        qdev_prop_set_uint32(dev, "sector-length3", 2*16*1024);

        qdev_prop_set_uint8(dev, "width", 4); // 4-byte wide interface.
        qdev_prop_set_uint8(dev, "device-width", 2); // x16 mode.
        qdev_prop_set_uint8(dev, "max-device-width", 2); // 16-bit chips.
        qdev_prop_set_uint8(dev, "mappings", 1); // No mapping aliases.
        qdev_prop_set_uint8(dev, "big-endian", 0);
        qdev_prop_set_uint16(dev, "id0", 0x0001); // Manufacturer ID.
        qdev_prop_set_uint16(dev, "id1", 0x22C4); // Device ID (top boot block)
        qdev_prop_set_uint16(dev, "id2", 0xFFFF); // Not used with this chip.
        qdev_prop_set_uint16(dev, "id3", 0xFFFF); // Not used with this chip.
        qdev_prop_set_uint16(dev, "unlock-addr0", 0x0555);
        qdev_prop_set_uint16(dev, "unlock-addr1", 0x02AA);
        qdev_prop_set_string(dev, "name", "cmu900.data");
        qdev_init_nofail(dev);
        sysbus_mmio_map(SYS_BUS_DEVICE(dev), 0, 0x41000000);
    } else if (!qtest_enabled()) {
        error_report("Missing CMU 900 data flash, use option:\n"
                     "  -drive if=pflash,format=raw,index=2,file=/path/to/data.bin");
    }

    // Add the DPRAM.
    add_shared_mem("cmu900.dpram", 0x21C01000, 0x1000);
    // Add the IOproc RAM.
    add_shared_mem("cmu900.ioproc.ram", 0x21E80000, 0x100000);
    // Add the Anaproc RAM.
    add_shared_mem("cmu900.anaproc.ram", 0x23A00000, 0x40000);

    DeviceState *synth_dev;

    if (concrete_target == NULL)
    {
        synth_dev = qdev_create(NULL, "synth_cmu900");
    }
    else if (strcmp(concrete_target,"cmu900") == 0){
        synth_dev = qdev_create(NULL, "synth_cmu900_concrete");
    }
    else {
        printf("Invalid concrete_target = %s\n", concrete_target);
        exit(1);
    }
    qdev_init_nofail(synth_dev);
}


static void cmu900_machine_options(MachineClass *m)
{
    PCMachineClass *pcmc = PC_MACHINE_CLASS(m);
    m->desc = "Rockwell Collins CMU900";
    m->max_cpus = 1;
    m->default_cpu_type = X86_CPU_TYPE_NAME("486");
    // machine_class_allow_dynamic_sysbus_dev(m, type);
    pcmc->pci_enabled = false;
    pcmc->smbios_defaults = false;
    pcmc->gigabyte_align = false;
    pcmc->smbios_legacy_mode = true;
    pcmc->has_reserved_memory = false;
}

DEFINE_PC_MACHINE(cmu900, "cmu900", pc_init_cmu900,
                  cmu900_machine_options);

// vim: set sw=4 sts=4 ts=8 et:
