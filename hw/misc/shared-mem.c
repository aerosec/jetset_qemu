#include "qemu/osdep.h"
#include "hw/qdev.h"
#include "hw/sysbus.h"
#include "qapi/error.h"
#include "sysemu/sysemu.h"

#define TYPE_SHARED_MEM_DEVICE "shared-mem-device"
#define SHARED_MEM_DEVICE(obj) \
    OBJECT_CHECK(SharedMemDeviceState, (obj), TYPE_SHARED_MEM_DEVICE)

#define SHARED_MEM_PREFIX "/qemu."

typedef struct SharedMemDeviceState
{
    SysBusDevice parent_obj;

    uint64_t base_addr;
    uint64_t alias_addr;
    uint64_t size;
    char *name;
    bool master;

    void *mem;
    MemoryRegion mr;
    MemoryRegion alias_mr;
    Notifier exit;
} SharedMemDeviceState;

static void close_shared_memory(SharedMemDeviceState *s)
{
    if (s->mem) {
        munmap(s->mem, s->size);
        if (s->master) {
            char *path = g_strconcat(SHARED_MEM_PREFIX, s->name, (char *)NULL);
            //fprintf(stderr, "Unlinking shared mem %s\n", path);
            shm_unlink(path);
            g_free(path);
        }
        s->mem = NULL;
    }
}

static void exit_notify(Notifier *notifier, void *opaque)
{
    SharedMemDeviceState *s = container_of(notifier, SharedMemDeviceState, exit);
    close_shared_memory(s);
}

static void open_shared_memory(SharedMemDeviceState *s, Error **errp)
{
    char *path = g_strconcat(SHARED_MEM_PREFIX, s->name, (char *)NULL);

    /* Open a file descriptor for the shared memory. */
    int fd = -1;
    if (s->master) {
        /* Make sure the name is not in use already. */
        shm_unlink(path);
        fd = shm_open(path, O_RDWR | O_CREAT | O_EXCL, 0660);
        if (fd == -1) {
            error_setg_errno(errp, errno, "Failed to open shared memory %s",
                             path);
            goto cleanup;
        }
        /* Set the size. */
        if (ftruncate(fd, s->size) < 0) {
            error_setg_errno(errp, errno,
                             "Failed to truncate shared memory %s to "
                             "0x%" PRIx64 " bytes",
                             path, s->size);
            goto cleanup;
        }
    } else {
        fd = shm_open(path, O_RDWR, 0660);
        if (fd == -1) {
            error_setg_errno(errp, errno, "Failed to open shared memory %s",
                             path);
            goto cleanup;
        }
        shm_unlink(path);
    }
    
    /* Mmap the file. */
    s->mem = mmap(0, s->size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (s->mem == MAP_FAILED) {
        error_setg_errno(errp, errno, "Failed to map shared memory %s", path);
        goto cleanup;
    }

    /* Add a notifier to clean up our memory. */
    s->exit.notify = exit_notify;
    qemu_add_exit_notifier(&s->exit);

    /* Close the file descriptor now that it is no longer needed. */
    close(fd);
    g_free(path);
    return;

cleanup:
    if (fd != -1) {
        shm_unlink(path);
        close(fd);
    }
    g_free(path);
    s->mem = NULL;
}

// 1. The class is initialized via .class_init
// 2. The instance is initialized via .instance_init
// 3. The instance is realized via the device class's realize
// https://people.redhat.com/~thuth/blog/qemu/2018/09/10/instance-init-realize.html

static void shmem_realize(DeviceState *d, Error **errp)
{
    SysBusDevice *sbd = SYS_BUS_DEVICE(d);
    SharedMemDeviceState *s = SHARED_MEM_DEVICE(d);
    Object *obj = OBJECT(s);
    //MemoryRegion *sysbus = sysbus_address_space(sbd);

    if (s->size == 0) {
        error_setg(errp, "Property 'size' not set");
        return;
    }
    if (s->name == NULL) {
        error_setg(errp, "Property 'name' not set");
        return;
    }

    open_shared_memory(s, errp);
    if (s->mem == NULL) {
        return;
    }

    memory_region_init_ram_ptr(&s->mr, obj, s->name, s->size, s->mem);
    sysbus_init_mmio(sbd, &s->mr);
    sysbus_mmio_map(sbd, 0, s->base_addr);

    if (s->alias_addr) {
        memory_region_init_alias(&s->alias_mr, obj, s->name, &s->mr, 0,
                                 s->size);
        sysbus_init_mmio(sbd, &s->alias_mr);
        sysbus_mmio_map(sbd, 1, s->alias_addr);
    }
}

static void shmem_unrealize(DeviceState *d, Error **errp)
{
    SharedMemDeviceState *s = SHARED_MEM_DEVICE(d);
    close_shared_memory(s);
    if (s->exit.notify) {
        qemu_remove_exit_notifier(&s->exit);
    }
}

// Set the description, list of properties, and function for realizing an
// instance of the class.
static void shmem_class_init(ObjectClass *oc, void *data)
{
    static Property properties[] =
    {
        DEFINE_PROP_UINT64("base-addr", SharedMemDeviceState, base_addr, 0),
        DEFINE_PROP_UINT64("alias-addr", SharedMemDeviceState, alias_addr, 0),
        DEFINE_PROP_SIZE("size", SharedMemDeviceState, size, 0),
        DEFINE_PROP_STRING("name", SharedMemDeviceState, name),
        DEFINE_PROP_BOOL("master", SharedMemDeviceState, master, false),
        DEFINE_PROP_END_OF_LIST(),
    };

    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->desc = "Shared memory";
    dc->props = properties;
    dc->realize = shmem_realize;
    dc->unrealize = shmem_unrealize;
    set_bit(DEVICE_CATEGORY_MISC, dc->categories);
}

// Registers the type for creation by name.
static void shmem_register_types(void)
{
    static const TypeInfo info =
    {
        .name = TYPE_SHARED_MEM_DEVICE,
        .parent = TYPE_SYS_BUS_DEVICE,
        .instance_size = sizeof(SharedMemDeviceState),
        .class_init = shmem_class_init,
    };
    type_register_static(&info);
}

type_init(shmem_register_types)

/* vim: set sw=4 sts=4 ts=8 et: */
