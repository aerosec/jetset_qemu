/*
 * Rasperry Pi 2 emulation ARM control logic module.
 * Copyright (c) 2015, Microsoft
 * Written by Andrew Baumann
 *
 * Based on bcm2835_ic.c (Raspberry Pi emulation) (c) 2012 Gregory Estrade
 * This code is licensed under the GNU GPLv2 and later.
 *
 * At present, only implements interrupt routing, and mailboxes (i.e.,
 * not local timer, PMU interrupt, or AXI counters).
 *
 * Ref:
 * https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2836/QA7_rev3.4.pdf
 */

#include "qemu/osdep.h"
#include "hw/intc/bcm2836_control.h"
#include "qemu/log.h"

#define REG_GPU_ROUTE           0x0c
#define REG_TIMERCONTROL        0x40
#define REG_MBOXCONTROL         0x50
#define REG_IRQSRC              0x60
#define REG_FIQSRC              0x70
#define REG_MBOX0_WR            0x80
#define REG_MBOX0_RDCLR         0xc0
#define REG_LIMIT              0x100

#define IRQ_BIT(cntrl, num) (((cntrl) & (1 << (num))) != 0)
#define FIQ_BIT(cntrl, num) (((cntrl) & (1 << ((num) + 4))) != 0)

#define IRQ_CNTPSIRQ    0
#define IRQ_CNTPNSIRQ   1
#define IRQ_CNTHPIRQ    2
#define IRQ_CNTVIRQ     3
#define IRQ_MAILBOX0    4
#define IRQ_MAILBOX1    5
#define IRQ_MAILBOX2    6
#define IRQ_MAILBOX3    7
#define IRQ_GPU         8
#define IRQ_PMU         9
#define IRQ_AXI         10
#define IRQ_TIMER       11
#define IRQ_MAX         IRQ_TIMER

int prev_irq = 0;

//int global_gpu_irq = 0;
int pending_intr = 0;

int next_pending_irq_reg(void)
{ 
  /*if(pending_intr == 0)
    return 0;
  pending_intr = 0;
  return 1 << IRQ_GPU;
  */
  if (pending_intr == 0)
    return 0;
  pending_intr += 1;
  if(pending_intr > 12) {
    pending_intr = 0;
    //printf("control READ returning %d\n", 0);
    return 0;
  }
  //printf("control READ returning %d\n",1 << pending_intr);
  return 1 << pending_intr;
}

/* Update interrupts.  */
static void bcm2836_control_update(BCM2836ControlState *s)
{
    s->irqsrc[0] = 0;

    /* gpu => 0x100 */
    if (s->gpu_irq && pending_intr == 0) {
        pending_intr = 1;
        //s->irqsrc[0] |= 1 << IRQ_GPU;//next_pending_irq_reg();/*(uint32_t)1 << IRQ_GPU;*/
    }

    // timer => 0x8
    if(s->timerirqs[0] != 0){
        s->irqsrc[0] |= (uint32_t)1 << 3;
    }

    qemu_set_irq(s->irq[0], s->irqsrc[0] != 0);
}

static void bcm2836_control_set_local_irq3(void *opaque, int core, int level)
{
    BCM2836ControlState *s = opaque;
    s->timerirqs[0] = level;
    bcm2836_control_update(s);
}

static void bcm2836_control_set_gpu_irq(void *opaque, int irq, int level)
{
    BCM2836ControlState *s = opaque;
    s->gpu_irq = level;
    bcm2836_control_update(s);
}

static uint64_t bcm2836_control_read(void *opaque, hwaddr offset, unsigned size)
{
    BCM2836ControlState *s = opaque;
    uint32_t v = s->irqsrc[0];
    if(pending_intr)
        v = next_pending_irq_reg();

    if(v != 8)
        printf("control READ 0x%x\n",v);
    return v;// | next_pending_irq_reg();
    //return next_pending_irq_reg();
}

static void bcm2836_control_write(void *opaque, hwaddr offset,
                                  uint64_t val, unsigned size)
{
    /*BCM2836ControlState *s = opaque;

    if (offset >= REG_MBOX0_WR && offset < REG_MBOX0_RDCLR) {
        s->mailboxes[(offset - REG_MBOX0_WR) >> 2] |= val;
    } */
}

static const MemoryRegionOps bcm2836_control_ops = {
    .read = bcm2836_control_read,
    .write = bcm2836_control_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
    .valid.min_access_size = 4,
    .valid.max_access_size = 4,
};

static void bcm2836_control_reset(DeviceState *d)
{
    BCM2836ControlState *s = BCM2836_CONTROL(d);
    int i;

    s->route_gpu_irq = s->route_gpu_fiq = 0;

    for (i = 0; i < BCM2836_NCORES; i++) {
        s->timercontrol[i] = 0;
        s->mailboxcontrol[i] = 0;
    }

    for (i = 0; i < BCM2836_NCORES * BCM2836_MBPERCORE; i++) {
        s->mailboxes[i] = 0;
    }
}

static void bcm2836_control_init(Object *obj)
{
    BCM2836ControlState *s = BCM2836_CONTROL(obj);
    DeviceState *dev = DEVICE(obj);

    memory_region_init_io(&s->iomem, obj, &bcm2836_control_ops, s,
                          TYPE_BCM2836_CONTROL, REG_LIMIT);
    sysbus_init_mmio(SYS_BUS_DEVICE(s), &s->iomem);

   
    qdev_init_gpio_in_named(dev, bcm2836_control_set_local_irq3, "cntvirq",
                            BCM2836_NCORES);

    /* IRQ and FIQ inputs from upstream bcm2835 controller */
    qdev_init_gpio_in_named(dev, bcm2836_control_set_gpu_irq, "gpu-irq", 1);

    /* outputs to CPU cores */
    qdev_init_gpio_out_named(dev, s->irq, "irq", BCM2836_NCORES);
    //qdev_init_gpio_out_named(dev, s->fiq, "fiq", BCM2836_NCORES);
}


static void bcm2836_control_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->reset = bcm2836_control_reset;
}

static TypeInfo bcm2836_control_info = {
    .name          = TYPE_BCM2836_CONTROL,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(BCM2836ControlState),
    .class_init    = bcm2836_control_class_init,
    .instance_init = bcm2836_control_init,
};

static void bcm2836_control_register_types(void)
{
    type_register_static(&bcm2836_control_info);
}

type_init(bcm2836_control_register_types)
