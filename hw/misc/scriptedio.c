#include "qemu/osdep.h"
#include "hw/qdev.h"
#include "hw/isa/isa.h"
#include "qapi/error.h"

#define TYPE_SCRIPTEDIO "scripted-io"
#define SCRIPTEDIO(obj) OBJECT_CHECK(ScriptedIOState, (obj), TYPE_SCRIPTEDIO)

typedef struct {
	ISADevice parent_obj;

	/* Set by properties */
	char *script_path;
	uint32_t constant;
	uint32_t iobase;
	uint32_t iosize;

	MemoryRegion io;

	uint32_t index;
	uint32_t script_count;
	uint32_t *script;
	PortioList port_list;
} ScriptedIOState;

static void scripted_io_write(void *opaque, hwaddr addr, uint64_t val, unsigned width)
{
	/* Ignore writes. */
}

static uint64_t scripted_io_read(void *opaque, hwaddr addr, unsigned width)
{
	ScriptedIOState *sio = SCRIPTEDIO(opaque);

	if (sio->index == sio->script_count)
		return sio->constant;
	return sio->script[sio->index++];
}

static const MemoryRegionOps scripted_io_ops =
{
	.write = scripted_io_write,
	.read = scripted_io_read,
	.valid.min_access_size = 1,
	.valid.max_access_size = 4,
	.endianness = DEVICE_LITTLE_ENDIAN,
};

static void scripted_io_free_script(ScriptedIOState *sio)
{
	g_free(sio->script);
	sio->script = NULL;
	sio->script_count = 0;
}

static int scripted_io_read_script(ScriptedIOState *sio, Error **errp)
{
	sio->script_count = 0;
	sio->script = NULL;

	if (!sio->script_path)
		return 0;

	FILE *fp = fopen(sio->script_path, "r");
	if (!fp)
	{
		error_setg_errno(errp, errno, "%s", sio->script_path);
		return -1;
	}
	gsize size = 16;
	sio->script = g_malloc(size * sizeof(uint32_t));
	while (!feof(fp) && !ferror(fp))
	{
		unsigned int x;
		int ret = fscanf(fp, " %x", &x);
		if (ret < 0)
			break; /* EOF */
		if (ret != 1)
		{
			error_setg(errp, "Script entry %u invalid", sio->script_count+1);
			break;
		}
		if (sio->script_count == size)
		{
			size *= 2;
			sio->script = g_realloc(sio->script, size * sizeof(uint32_t));
		}
		sio->script[sio->script_count++] = x;
	}
	if (*errp == NULL && ferror(fp))
		error_setg_errno(errp, errno, "%s", sio->script_path);
	fclose(fp);
	if (*errp)
	{
		scripted_io_free_script(sio);
		return -1;
	}
	return 0;
}

static void scripted_io_init(Object *d)
{
	ScriptedIOState *sio = SCRIPTEDIO(d);

	memory_region_init_io(&sio->io, OBJECT(sio), &scripted_io_ops,
			      sio, TYPE_SCRIPTEDIO, sio->iosize);
}

static void scripted_io_realize(DeviceState *d, Error **errp)
{
	ISADevice *dev = ISA_DEVICE(d);
	ScriptedIOState *sio = SCRIPTEDIO(d);

	/* Read the script. */
	if (scripted_io_read_script(sio, errp))
		return;
	sio->index = 0;
	isa_register_ioport(dev, &sio->io, sio->iobase);
}

static void scripted_io_unrealize(DeviceState *d, Error **errp)
{
	ScriptedIOState *sio = SCRIPTEDIO(d);
	
	scripted_io_free_script(sio);
}

static void scripted_io_reset(DeviceState *d)
{
	ScriptedIOState *sio = SCRIPTEDIO(d);
	sio->index = 0;
}

static const VMStateDescription vmstate_scripted_io =
{
	.name = TYPE_SCRIPTEDIO,
	.version_id = 0,
	.minimum_version_id = 0,
	.fields = (VMStateField[])
	{
		VMSTATE_UINT32(index, ScriptedIOState),
		VMSTATE_VARRAY_UINT32(script, ScriptedIOState, script_count, 0, vmstate_info_uint32, uint32_t),
		VMSTATE_END_OF_LIST(),
	},
};

static Property scripted_io_properties[] =
{
	DEFINE_PROP_STRING("script", ScriptedIOState, script_path),
	DEFINE_PROP_UINT32("const", ScriptedIOState, constant, -1),
	DEFINE_PROP_UINT32("iobase", ScriptedIOState, iobase, 0x4000),
	DEFINE_PROP_UINT32("iosize", ScriptedIOState, iosize, 0x1),
	DEFINE_PROP_END_OF_LIST(),
};


/* Set virtual function pointers and properties. */
static void scripted_io_class_init(ObjectClass *klass, void *data)
{
	DeviceClass *dc = DEVICE_CLASS(klass);

	dc->props = scripted_io_properties;
	dc->realize = scripted_io_realize;
	dc->unrealize = scripted_io_unrealize;
	dc->reset = scripted_io_reset;
	dc->vmsd = &vmstate_scripted_io;
	set_bit(DEVICE_CATEGORY_MISC, dc->categories);
}

static const TypeInfo scripted_io_info =
{
	.name		= TYPE_SCRIPTEDIO,
	.parent		= TYPE_ISA_DEVICE,
	.instance_size	= sizeof(ScriptedIOState),
	.instance_init	= scripted_io_init,
	.class_init	= scripted_io_class_init,
};

static void scripted_io_register_types(void)
{
	type_register_static(&scripted_io_info);
}

type_init(scripted_io_register_types)
