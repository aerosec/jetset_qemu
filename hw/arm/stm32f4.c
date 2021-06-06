#include "qemu/osdep.h"
#include "qapi/error.h"
#include "hw/boards.h"
#include "qemu/error-report.h"
#include "hw/arm/stm32f205_soc.h"
#include "hw/arm/arm.h"
#include "exec/address-spaces.h"




static void make_ram(MemoryRegion *mr, const char *name,
                     hwaddr base, hwaddr size)
{
    memory_region_init_ram(mr, NULL, name, size, &error_fatal);
    memory_region_add_subregion(get_system_memory(), base, mr);
}

static void stm32f4_init(MachineState *machine)
{
    DeviceState *dev;
    MemoryRegion *sram1;
    MemoryRegion *sram3;
    MemoryRegion *sysmem = get_system_memory();

    dev = qdev_create(NULL, TYPE_STM32F205_SOC);
    qdev_prop_set_string(dev, "cpu-type", ARM_CPU_TYPE_NAME("cortex-m3"));
    object_property_set_bool(OBJECT(dev), true, "realized", &error_fatal);


    armv7m_load_kernel(ARM_CPU(first_cpu), machine->kernel_filename,
                       FLASH_SIZE);

    
    DeviceState *synth_dev;
    if (concrete_target == NULL)
    {
        synth_dev = qdev_create(NULL, "synth_plc");
    }
    else if (strcmp(concrete_target, "cnc") == 0){
        synth_dev = qdev_create(NULL, "cnc_device");
    }
    else if (strcmp(concrete_target,"console") == 0){
        synth_dev = qdev_create(NULL, "console_device");
    }
    else if (strcmp(concrete_target,"drone") == 0){
        synth_dev = qdev_create(NULL, "drone_device");
    }
    else if (strcmp(concrete_target,"gateway") == 0){
        synth_dev = qdev_create(NULL, "gateway_device");
    }
    else if (strcmp(concrete_target,"heat_press") == 0){
        synth_dev = qdev_create(NULL, "heat_press_device");
    }
    else if (strcmp(concrete_target,"robot") == 0){
        synth_dev = qdev_create(NULL, "robot_device");
    }
    else if (strcmp(concrete_target,"reflow_oven") == 0){
        synth_dev = qdev_create(NULL, "reflow_oven_device");
    }
    else if (strcmp(concrete_target,"plc") == 0){
        synth_dev = qdev_create(NULL, "plc_device");
    }
    else if (strcmp(concrete_target,"steering_control") == 0){
        synth_dev = qdev_create(NULL, "steering_control_device");
    }
    else {
        printf("Invalid concrete_target = %s\n", concrete_target);
    }

    qdev_init_nofail(synth_dev);
}

static void stm32f4_machine_init(MachineClass *mc)
{
    mc->desc = "STM32f4XXX Family of Machines";
    mc->init = stm32f4_init;
    mc->ignore_memory_transaction_failures = true;
}

DEFINE_MACHINE("stm32f4", stm32f4_machine_init)
