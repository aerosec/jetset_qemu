/*
 * Beagle board emulation. http://beagleboard.org/
 *
 * Copyright (c) 2009 Nokia Corporation
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 or
 * (at your option) any later version of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */


#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qemu-common.h"
#include "sysemu/sysemu.h"
#include "hw/arm/omap.h"
#include "hw/arm/arm.h"
#include "hw/boards.h"
#include "hw/i2c/i2c.h"
#include "net/net.h"
#include "hw/block/flash.h"
#include "hw/sysbus.h"
#include "sysemu/blockdev.h"
#include "exec/address-spaces.h"
#include "hw/char/serial.h"


#define BEAGLE_NAND_CS       0
#define BEAGLE_SMC_CS        1
#define BEAGLE_NAND_PAGESIZE 0x800
#define BEAGLE_SDRAM_SIZE    (256 * 1024 * 1024) /* 256MB */
#define BEAGLE_XM_SDRAM_SIZE (512 * 1024 * 1024) /* 512MB */
/* GPIO ID pins are used to identify which beagle variant we have */
#define BEAGLE_GPIO_ID1      171
#define BEAGLE_GPIO_ID2      172
#define BEAGLE_GPIO_ID3      173

extern char* concrete_target;

/* Beagle board support */
struct beagle_s {
    struct omap_mpu_state_s *cpu;

    DeviceState *nand;
    void *twl4030;
    DeviceState *smc;
    DeviceState *ddc;
};


static uint32_t get_firmware_size(char* filename)
{
    FILE *f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    uint32_t fsize = ftell(f);
    fseek(f, 0, SEEK_SET); 
    fclose(f);
    return fsize;
   
}


static uint8_t* read_firmware(char* filename)
{
    
    FILE *f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    uint32_t fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  

    uint8_t *data = malloc(fsize + 1);
    fread(data, 1, fsize, f);
    fclose(f);

    return data;
}

static void beagle_common_init(MachineState *machine,
                               ram_addr_t ram_size, int cpu_model)
{
    MemoryRegion *sysmem = get_system_memory();
    struct beagle_s *s = (struct beagle_s *) g_malloc0(sizeof(*s));
    DriveInfo *dmtd = drive_get(IF_MTD, 0, 0);
    //can be removed
    DriveInfo *dsd  = drive_get(IF_SD, 0, 0);

    if (!dmtd && !dsd) {
        hw_error("%s: SD or NAND image required", __FUNCTION__);
    }
//#if MAX_SERIAL_PORTS < 1
//#error MAX_SERIAL_PORTS must be at least 1!
//#endif
    s->cpu = omap3_mpu_init(sysmem, cpu_model, ram_size,
                            NULL, NULL, serial_hd(0), NULL);
    s->nand = nand_init(dmtd ? blk_by_legacy_dinfo(dmtd) : NULL,
                        NAND_MFR_MICRON, 0xba);
    nand_setpins(s->nand, 0, 0, 0, 1, 0); /* no write-protect */
    
    uint32_t offset = 0x402007F8;
    uint8_t *data = read_firmware(machine->kernel_filename);
    uint32_t data_len = get_firmware_size(machine->kernel_filename);
    cpu_physical_memory_write(offset, data, data_len);
    
    DeviceState *synth_dev;

    if (concrete_target == NULL)
    {
        synth_dev = qdev_create(NULL, "synth_beagle");
    }
    else if (strcmp(concrete_target,"beagle") == 0){
        synth_dev = qdev_create(NULL, "synth_beagle_concrete");
    }
    else {
        printf("Invalid concrete_target = %s\n", concrete_target);
    }


    qdev_init_nofail(synth_dev);
}

static void beagle_xm_init(MachineState *machine)
{
    beagle_common_init(machine, BEAGLE_XM_SDRAM_SIZE, omap3630);
}

static void beagle_init(MachineState *machine)
{
    beagle_common_init(machine, BEAGLE_SDRAM_SIZE, omap3430);
}


static void beagle_xm_machine_init(MachineClass *mc)
{
    mc->desc = "BeagleBoneXM";
    mc->init = beagle_xm_init;
    mc->block_default_type = IF_MTD;
    mc->no_parallel = 1;
    mc->no_floppy = 1;
    mc->no_cdrom = 1;
    mc->max_cpus = 1;
    mc->min_cpus = 1;
    mc->default_cpus = 1;
    mc->default_ram_size = BEAGLE_XM_SDRAM_SIZE;
    mc->ignore_memory_transaction_failures = true;
}
DEFINE_MACHINE("beaglexm", beagle_xm_machine_init)

static void beagle_machine_init(MachineClass *mc)
{
    mc->desc = "BeagleBone";
    mc->init = beagle_init;
    mc->block_default_type = IF_MTD;
    mc->no_parallel = 1;
    mc->no_floppy = 1;
    mc->no_cdrom = 1;
    mc->max_cpus = 1;
    mc->min_cpus = 1;
    mc->default_cpus = 1;
    mc->default_ram_size = BEAGLE_SDRAM_SIZE;
    mc->ignore_memory_transaction_failures = true;
}
DEFINE_MACHINE("beagle", beagle_machine_init)

