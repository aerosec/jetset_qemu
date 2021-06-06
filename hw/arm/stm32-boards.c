/*
 * STM32 boards emulation.
 *
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qemu-common.h"
#include "qemu/log.h"

#include "hw/arm/stm32-mcus.h"
#include "hw/display/gpio-led.h"
#include "sysemu/sysemu.h"

/*
void cm_object_property_add_child(Object *obj, const char *node_name,
        Object *child)
{
    Error *err = NULL;
    object_property_add_child(obj, node_name, child, &err);
    if (err) {
        error_report("Adding child %s for %s failed: %s.", node_name,
                object_get_typename(obj), error_get_pretty(err));
        exit(1);
    }
}
*/

Object *cm_object_new(Object *parent, const char* node_name,
        const char *type_name)
{
    Error *err = NULL;
    if (object_class_by_name(type_name) == NULL) {
        //error_report("Creating object of type %s failed; no such type.",
        //        type_name);
        exit(1);
    }

    Object *obj = object_new(type_name);
    if (!obj) {
        //error_report("Creating object of type %s failed.", type_name);
        exit(1);
    }

    //cm_object_property_add_child(parent, node_name, obj);
    object_property_add_child(parent, node_name, obj, &err);
    return obj;
}


Object *cm_object_get_machine(void)
{
    static Object *obj;

    if (obj == NULL) {
        obj = container_get(object_get_root(), "/machine");
    }

    return obj;
}


Object *cm_object_new_mcu(MachineState *machine, const char *board_device_name)
{
    const char *device_name = board_device_name;
    return cm_object_new(cm_object_get_machine(), "mcu", device_name);
}

static void stm32f4_discovery_board_init_callback(MachineState *machine)
{

    {
        Error *err = NULL;
        /* Create the MCU */
        Object *mcu = cm_object_new_mcu(machine, TYPE_STM32F407VG);
        /* Set the board specific oscillator frequencies. */
        object_property_set_int(mcu, 8000000, "hse-freq-hz", &err);
        object_property_set_int(mcu, 32768, "lse-freq-hz", &err);

        object_property_set_bool(mcu, true, "realized", &err);
    }
  
static void stm32f4_machine_init(MachineClass *mc)
{
    mc->desc = "stm32f4 chip";
    mc->init = stm32f4_discovery_board_init_callback;
}
DEFINE_MACHINE("stm32f4", stm32f4_machine_init)






