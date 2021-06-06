/*
 * STM32 Arduino-like boards emulation.
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
#include "hw/arm/cortexm-helper.h"

/*
 * This file defines several Arduino-like STM32 boards.
 */

#if 0
/* ----- Netduino 2 ----- */
static void
netduino2_board_init_callback(MachineState *machine);

static QEMUMachine netduino2_machine = {
    .name = "Netduino2",
    .desc = "Netduino Development Board with STM32F2 (Experimental)",
    .init = netduino2_board_init_callback};

static void netduino2_board_init_callback(MachineState *machine)
{
    cm_board_greeting(machine);
    //cortexm_mcu_alloc(machine, TYPE_STM32F205RF);

    /* TODO: Add board inits */
}
#endif




