#ifndef MC146818RTC_H
#define MC146818RTC_H

#include "hw/isa/isa.h"
#include "hw/timer/mc146818rtc_regs.h"

#define TYPE_MC146818_RTC "mc146818rtc"

ISADevice *mc146818_rtc_init(ISABus *bus, int base_year, qemu_irq intercept_irq);
ISADevice *mc146818_rtc_init_with_base(ISABus *bus, int base_year, int iobase, qemu_irq intercept_irq);
void rtc_set_memory(ISADevice *dev, int addr, int val);
int rtc_get_memory(ISADevice *dev, int addr);

#endif /* MC146818RTC_H */
