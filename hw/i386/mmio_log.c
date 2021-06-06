#include <inttypes.h>

#include "qemu/osdep.h"
#include "hw/qdev.h"
#include "hw/sysbus.h"
#include "qom/cpu.h"
#include "target/i386/cpu.h"

#define TYPE_MMIO_LOG "mmio-log"
#define MMIOLOG(obj) OBJECT_CHECK(MMIOLogState, (obj), TYPE_MMIO_LOG)

typedef struct
{
	SysBusDevice parent_obj;

	/* Set by properties. */
	uint32_t base;
	uint32_t size;

	MemoryRegion iomem;
} MMIOLogState;


static void mmio_log_write(void *opaque, hwaddr addr, uint64_t val, unsigned width)
{
	MMIOLogState *s = MMIOLOG(opaque);
	unsigned int address = s->base + addr;
	X86CPU *cpu = X86_CPU(first_cpu);
	unsigned int cs = cpu->env.segs[R_CS].selector;
	unsigned int eip = cpu->env.eip;
	fprintf(stderr, "write: pc=%04x:%08x, %08x <- %0*x\n", cs, eip, address, width*2, (unsigned int)val);
}

static uint64_t mmio_log_read(void *opaque, hwaddr addr, unsigned width)
{
	MMIOLogState *s = MMIOLOG(opaque);
	unsigned int address = s->base + addr;
	X86CPU *cpu = X86_CPU(first_cpu);
	unsigned int cs = cpu->env.segs[R_CS].selector;
	unsigned int eip = cpu->env.eip;
	fprintf(stderr, "read:  pc=%04x:%08x, %08x -> %d bytes\n", cs, eip, address, width);
	return 0;
}

static const MemoryRegionOps mmio_log_ops =
{
	.read = mmio_log_read,
	.write = mmio_log_write,
	.valid.min_access_size = 1,
	.valid.max_access_size = 4,
	.endianness = DEVICE_NATIVE_ENDIAN,
};

static Property mmio_log_properties[] = 
{
	DEFINE_PROP_UINT32("base", MMIOLogState, base, 0x21d00000),
	DEFINE_PROP_UINT32("size", MMIOLogState, size, 1),
	DEFINE_PROP_END_OF_LIST(),
};

static void mmio_log_realize(DeviceState *d, Error **errp)
{
	SysBusDevice *sbd = SYS_BUS_DEVICE(d);
	MMIOLogState *s = MMIOLOG(d);

	memory_region_init_io(&s->iomem, OBJECT(s), &mmio_log_ops, s,
			      TYPE_MMIO_LOG, s->size);
	sysbus_init_mmio(sbd, &s->iomem);
	memory_region_add_subregion(sysbus_address_space(sbd), s->base, &s->iomem);
	*errp = 0;
}

static void mmio_log_class_init(ObjectClass *klass, void *data)
{
	DeviceClass *dc = DEVICE_CLASS(klass);

	dc->props = mmio_log_properties;
	dc->realize = mmio_log_realize;
	set_bit(DEVICE_CATEGORY_MISC, dc->categories);
}

static const TypeInfo mmio_log_info =
{
	.name = TYPE_MMIO_LOG,
	.parent = TYPE_SYS_BUS_DEVICE,
	.instance_size = sizeof(MMIOLogState),
	.class_init = mmio_log_class_init,
};

static void mmio_log_register_types(void)
{
	type_register_static(&mmio_log_info);
}

type_init(mmio_log_register_types)
