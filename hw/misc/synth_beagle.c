
#include "qemu/osdep.h"
#include "hw/qdev.h"
#include "qapi/error.h"
#include "hw/sysbus.h"
#include "hw/i386/pc.h"
#include <unistd.h>
#include "exec/taint.h"

#define TYPE_SYNTH "synth_beagle"
#define SYNTH(obj) OBJECT_CHECK(SynthState, (obj), TYPE_SYNTH)


typedef struct {
    SysBusDevice parent_obj;
    qemu_irq* irq_set;
    int global_idx;


    MemoryRegion io_L3RT;

    MemoryRegion io_L3SI;

    MemoryRegion io_Reserved0;

    MemoryRegion io_MPUSSIA;

    MemoryRegion io_IVA22SSIA;

    MemoryRegion io_SGXSSIA;

    MemoryRegion io_SMSTA;

    MemoryRegion io_GPMCTA;

    MemoryRegion io_OCMRAMTA;

    MemoryRegion io_OCMROMTA;

    MemoryRegion io_D2DIA;

    MemoryRegion io_D2DTA;

    MemoryRegion io_Reserved1;

    MemoryRegion io_HSUSBHOSTIA;

    MemoryRegion io_HSUSBOTGIA;

    MemoryRegion io_Reserved2;

    MemoryRegion io_sDMARDIA;

    MemoryRegion io_sDMAWRIA;

    MemoryRegion io_DisplaySSIA;

    MemoryRegion io_CAMERAISPIA;

    MemoryRegion io_DAPIA;

    MemoryRegion io_IVA22SSTA;

    MemoryRegion io_SGXSSTA;

    MemoryRegion io_L4CoreTA;

    MemoryRegion io_L4PerTA;

    MemoryRegion io_Reserved3;

    MemoryRegion io_RTPM;

    MemoryRegion io_Reserved4;

    MemoryRegion io_GPMCPM;

    MemoryRegion io_OCMRAMPM;

    MemoryRegion io_OCMROMPM;

    MemoryRegion io_D2DPM;

    MemoryRegion io_Reserved5;

    MemoryRegion io_IVA22PM;

    MemoryRegion io_Reserved6;

    MemoryRegion io_SMS;

    MemoryRegion io_SDRC;

    MemoryRegion io_GPMC;

    MemoryRegion io_L4ID_SCM;

    MemoryRegion io_L4ID_SCM_TA;

    MemoryRegion io_L4ID_CM_A;

    MemoryRegion io_L4ID_CM_B;

    MemoryRegion io_L4ID_CM_TA;

    MemoryRegion io_L4ID_CORE_AP;

    MemoryRegion io_L4ID_CORE_IP;

    MemoryRegion io_L4ID_CORE_LA;

    MemoryRegion io_L4ID_DSI;

    MemoryRegion io_L4ID_DSS;

    MemoryRegion io_L4ID_DISPC;

    MemoryRegion io_L4ID_RFBI;

    MemoryRegion io_L4ID_VENC;

    MemoryRegion io_L4ID_DSS_TA;

    MemoryRegion io_L4ID_SDMA;

    MemoryRegion io_L4ID_SDMA_TA;

    MemoryRegion io_L4ID_I2C3;

    MemoryRegion io_L4ID_I2C3_TA;

    MemoryRegion io_4ID_USBTLL;

    MemoryRegion io_L4ID_USBTLL_TA;

    MemoryRegion io_4ID_USBHOST;

    MemoryRegion io_L4ID_USBHOST_OHCI;

    MemoryRegion io_4ID_USBHOST_EHCI;

    MemoryRegion io_L4ID_USBHOST_TA;

    MemoryRegion io_L4ID_UART1;

    MemoryRegion io_L4ID_UART1_TA;

    MemoryRegion io_4ID_UART2;

    MemoryRegion io_L4ID_UART2_TA;

    MemoryRegion io_L4ID_I2C1;

    MemoryRegion io_L4ID_I2C1_TA;

    MemoryRegion io_L4ID_I2C2;

    MemoryRegion io_L4ID_I2C2_TA;

    MemoryRegion io_L4ID_MCBSP1;

    MemoryRegion io_L4ID_MCBSP1_TA;

    MemoryRegion io_L4ID_GPTIMER10;

    MemoryRegion io_L4ID_GPTIMER10_TA;

    MemoryRegion io_4ID_GPTIMER11;

    MemoryRegion io_L4ID_GPTIMER11_TA;

    MemoryRegion io_L4ID_MAILBOX;

    MemoryRegion io_L4ID_MAILBOX_TA;

    MemoryRegion io_L4ID_MCBSP5;

    MemoryRegion io_L4ID_MCBSP5_TA;

    MemoryRegion io_L4ID_MCSPI1;

    MemoryRegion io_L4ID_MCSPI1_TA;

    MemoryRegion io_L4ID_MCSPI2;

    MemoryRegion io_L4ID_MCSPI2_TA;

    MemoryRegion io_L4ID_MMCSDIO1;

    MemoryRegion io_L4ID_MMCSDIO1_TA;

    MemoryRegion io_L4ID_MSPRO;

    MemoryRegion io_L4ID_MSPRO_TA;

    MemoryRegion io_L4ID_HSUSBOTG;

    MemoryRegion io_L4ID_HSUSBOTG_TA;

    MemoryRegion io_L4ID_MMCSDIO3;

    MemoryRegion io_L4ID_MMCSDIO3_TA;

    MemoryRegion io_L4ID_HDQ1WIRE;

    MemoryRegion io_L4ID_HDQ1WIRE_TA;

    MemoryRegion io_L4ID_MMCSDIO2;

    MemoryRegion io_L4ID_MMCSDIO2_TA;

    MemoryRegion io_L4ID_ICRMPU;

    MemoryRegion io_L4ID_ICRMPU_TA;

    MemoryRegion io_L4ID_MCSPI3;

    MemoryRegion io_L4ID_MCSPI3_TA;

    MemoryRegion io_L4ID_MCSPI4;

    MemoryRegion io_L4ID_MCSPI4_TA;

    MemoryRegion io_L4ID_CAMERAISP;

    MemoryRegion io_L4ID_CAMERAISP_TA;

    MemoryRegion io_L4ID_SR1;

    MemoryRegion io_L4ID_SR1_TA;

    MemoryRegion io_L4ID_SR2;

    MemoryRegion io_L4ID_SR2_TA;

    MemoryRegion io_L4ID_ICRMODEM;

    MemoryRegion io_L4ID_ICRMODEM_TA;

    MemoryRegion io_L4ID_GPTIMER12;

    MemoryRegion io_L4ID_GPTIMER12_TA;

    MemoryRegion io_L4ID_PRM_A;

    MemoryRegion io_L4ID_PRM_TA;

    MemoryRegion io_L4ID_TAP;

    MemoryRegion io_L4ID_TAP_TA;

    MemoryRegion io_L4ID_GPIO1;

    MemoryRegion io_L4ID_GPIO1_TA;

    MemoryRegion io_L4ID_WDTIMER2;

    MemoryRegion io_L4ID_WDTIMER2_TA;

    MemoryRegion io_L4ID_GPTIMER1;

    MemoryRegion io_L4ID_GPTIMER1_TA;

    MemoryRegion io_L4ID_32KTIMER;

    MemoryRegion io_L4ID_32KTIMER_TA;

    MemoryRegion io_L4ID_WAKEUP_AP;

    MemoryRegion io_L4ID_WAKEUP_C_IP;

    MemoryRegion io_L4ID_WAKEUP_LA;

    MemoryRegion io_L4ID_WAKEUP_E_IP;

    MemoryRegion io_L4ID_PER_AP;

    MemoryRegion io_L4ID_PER_IP;

    MemoryRegion io_L4ID_PER_LA;

    MemoryRegion io_L4ID_UART3;

    MemoryRegion io_L4ID_UART3_TA;

    MemoryRegion io_L4ID_MCBSP2;

    MemoryRegion io_L4ID_MCBSP2_TA;

    MemoryRegion io_L4ID_MCBSP3;

    MemoryRegion io_L4ID_MCBSP3_TA;

    MemoryRegion io_L4ID_MCBSP4;

    MemoryRegion io_L4ID_MCBSP4_TA;

    MemoryRegion io_L4ID_MCBSP2S;

    MemoryRegion io_L4ID_MCBSP2S_TA;

    MemoryRegion io_L4ID_MCBSP3S;

    MemoryRegion io_L4ID_MCBSP3S_TA;

    MemoryRegion io_L4ID_WDTIMER3;

    MemoryRegion io_L4ID_WDTIMER3_TA;

    MemoryRegion io_L4ID_GPTIMER2;

    MemoryRegion io_L4ID_GPTIMER2_TA;

    MemoryRegion io_L4ID_GPTIMER3;

    MemoryRegion io_L4ID_GPTIMER3_TA;

    MemoryRegion io_L4ID_GPTIMER4;

    MemoryRegion io_L4ID_GPTIMER4_TA;

    MemoryRegion io_L4ID_GPTIMER5;

    MemoryRegion io_L4ID_GPTIMER5_TA;

    MemoryRegion io_L4ID_GPTIMER6;

    MemoryRegion io_L4ID_GPTIMER6_TA;

    MemoryRegion io_L4ID_GPTIMER7;

    MemoryRegion io_L4ID_GPTIMER7_TA;

    MemoryRegion io_L4ID_GPTIMER8;

    MemoryRegion io_L4ID_GPTIMER8_TA;

    MemoryRegion io_L4ID_GPTIMER9;

    MemoryRegion io_L4ID_GPTIMER9_TA;

    MemoryRegion io_L4ID_UART4;

    MemoryRegion io_L4ID_UART4_TA;

    MemoryRegion io_L4ID_GPIO2;

    MemoryRegion io_L4ID_GPIO2_TA;

    MemoryRegion io_L4ID_GPIO3;

    MemoryRegion io_L4ID_GPIO3_TA;

    MemoryRegion io_L4ID_GPIO4;

    MemoryRegion io_L4ID_GPIO4_TA;

    MemoryRegion io_L4ID_GPIO5;

    MemoryRegion io_L4ID_GPIO5_TA;

    MemoryRegion io_L4ID_GPIO6;

    MemoryRegion io_L4ID_GPIO6_TA;

    MemoryRegion io_L4ID_EMU_AP;

    MemoryRegion io_L4ID_EMU_IP_C;

    MemoryRegion io_L4ID_EMU_LA;

    MemoryRegion io_L4ID_EMU_IP_DAP;

    MemoryRegion io_L4ID_MPUEMU;

    MemoryRegion io_L4ID_MPUEMU_TA;

    MemoryRegion io_L4ID_TPIU;

    MemoryRegion io_L4ID_TPIU_TA;

    MemoryRegion io_L4ID_ETB;

    MemoryRegion io_L4ID_ETB_TA;

    MemoryRegion io_L4ID_DAPCTL;

    MemoryRegion io_L4ID_DAPCTL_TA;

    MemoryRegion io_L4ID_SDTI_TA;

    MemoryRegion io_L4ID_SDTI_CFG;

    MemoryRegion io_L4ID_SDTI;

    MemoryRegion io_L4ID_EMU_PRM_A;

    MemoryRegion io_L4ID_EMU_PRM_B;

    MemoryRegion io_L4ID_EMU_PRM_TA;

    MemoryRegion io_L4ID_EMU_GPIO1;

    MemoryRegion io_L4ID_EMU_GPIO1_TA;

    MemoryRegion io_L4ID_EMU_WDTM2;

    MemoryRegion io_L4ID_EMU_WDTM2_TA;

    MemoryRegion io_L4ID_EMU_GPTM1;

    MemoryRegion io_L4ID_EMU_GPTM1_TA;

    MemoryRegion io_L4ID_EMU_32KTM;

    MemoryRegion io_L4ID_EMU_32KTM_TA;

    MemoryRegion io_L4ID_EMU_WKUP_AP;

    MemoryRegion io_L4ID_EMU_WKUP_IPC;

    MemoryRegion io_L4ID_EMU_WKUP_LA;

    MemoryRegion io_L4ID_EMU_WKUP_IPE;
} SynthState;


static void synth_write_L3RT(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L3RT.addr + addr, val);
}

static uint64_t synth_read_L3RT(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L3RT.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L3RT =
{
    .write = synth_write_L3RT,
    .read = synth_read_L3RT,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L3SI(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L3SI.addr + addr, val);
}

static uint64_t synth_read_L3SI(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L3SI.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L3SI =
{
    .write = synth_write_L3SI,
    .read = synth_read_L3SI,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_Reserved0(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_Reserved0.addr + addr, val);
}

static uint64_t synth_read_Reserved0(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_Reserved0.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_Reserved0 =
{
    .write = synth_write_Reserved0,
    .read = synth_read_Reserved0,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_MPUSSIA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_MPUSSIA.addr + addr, val);
}

static uint64_t synth_read_MPUSSIA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_MPUSSIA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_MPUSSIA =
{
    .write = synth_write_MPUSSIA,
    .read = synth_read_MPUSSIA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_IVA22SSIA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_IVA22SSIA.addr + addr, val);
}

static uint64_t synth_read_IVA22SSIA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_IVA22SSIA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_IVA22SSIA =
{
    .write = synth_write_IVA22SSIA,
    .read = synth_read_IVA22SSIA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_SGXSSIA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_SGXSSIA.addr + addr, val);
}

static uint64_t synth_read_SGXSSIA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_SGXSSIA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_SGXSSIA =
{
    .write = synth_write_SGXSSIA,
    .read = synth_read_SGXSSIA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_SMSTA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_SMSTA.addr + addr, val);
}

static uint64_t synth_read_SMSTA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_SMSTA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_SMSTA =
{
    .write = synth_write_SMSTA,
    .read = synth_read_SMSTA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_GPMCTA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_GPMCTA.addr + addr, val);
}

static uint64_t synth_read_GPMCTA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_GPMCTA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_GPMCTA =
{
    .write = synth_write_GPMCTA,
    .read = synth_read_GPMCTA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_OCMRAMTA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_OCMRAMTA.addr + addr, val);
}

static uint64_t synth_read_OCMRAMTA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_OCMRAMTA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_OCMRAMTA =
{
    .write = synth_write_OCMRAMTA,
    .read = synth_read_OCMRAMTA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_OCMROMTA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_OCMROMTA.addr + addr, val);
}

static uint64_t synth_read_OCMROMTA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_OCMROMTA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_OCMROMTA =
{
    .write = synth_write_OCMROMTA,
    .read = synth_read_OCMROMTA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_D2DIA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_D2DIA.addr + addr, val);
}

static uint64_t synth_read_D2DIA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_D2DIA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_D2DIA =
{
    .write = synth_write_D2DIA,
    .read = synth_read_D2DIA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_D2DTA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_D2DTA.addr + addr, val);
}

static uint64_t synth_read_D2DTA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_D2DTA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_D2DTA =
{
    .write = synth_write_D2DTA,
    .read = synth_read_D2DTA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_Reserved1(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_Reserved1.addr + addr, val);
}

static uint64_t synth_read_Reserved1(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_Reserved1.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_Reserved1 =
{
    .write = synth_write_Reserved1,
    .read = synth_read_Reserved1,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_HSUSBHOSTIA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_HSUSBHOSTIA.addr + addr, val);
}

static uint64_t synth_read_HSUSBHOSTIA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_HSUSBHOSTIA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_HSUSBHOSTIA =
{
    .write = synth_write_HSUSBHOSTIA,
    .read = synth_read_HSUSBHOSTIA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_HSUSBOTGIA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_HSUSBOTGIA.addr + addr, val);
}

static uint64_t synth_read_HSUSBOTGIA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_HSUSBOTGIA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_HSUSBOTGIA =
{
    .write = synth_write_HSUSBOTGIA,
    .read = synth_read_HSUSBOTGIA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_Reserved2(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_Reserved2.addr + addr, val);
}

static uint64_t synth_read_Reserved2(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_Reserved2.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_Reserved2 =
{
    .write = synth_write_Reserved2,
    .read = synth_read_Reserved2,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_sDMARDIA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_sDMARDIA.addr + addr, val);
}

static uint64_t synth_read_sDMARDIA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_sDMARDIA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_sDMARDIA =
{
    .write = synth_write_sDMARDIA,
    .read = synth_read_sDMARDIA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_sDMAWRIA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_sDMAWRIA.addr + addr, val);
}

static uint64_t synth_read_sDMAWRIA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_sDMAWRIA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_sDMAWRIA =
{
    .write = synth_write_sDMAWRIA,
    .read = synth_read_sDMAWRIA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_DisplaySSIA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_DisplaySSIA.addr + addr, val);
}

static uint64_t synth_read_DisplaySSIA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_DisplaySSIA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_DisplaySSIA =
{
    .write = synth_write_DisplaySSIA,
    .read = synth_read_DisplaySSIA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_CAMERAISPIA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_CAMERAISPIA.addr + addr, val);
}

static uint64_t synth_read_CAMERAISPIA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_CAMERAISPIA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_CAMERAISPIA =
{
    .write = synth_write_CAMERAISPIA,
    .read = synth_read_CAMERAISPIA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_DAPIA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_DAPIA.addr + addr, val);
}

static uint64_t synth_read_DAPIA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_DAPIA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_DAPIA =
{
    .write = synth_write_DAPIA,
    .read = synth_read_DAPIA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_IVA22SSTA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_IVA22SSTA.addr + addr, val);
}

static uint64_t synth_read_IVA22SSTA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_IVA22SSTA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_IVA22SSTA =
{
    .write = synth_write_IVA22SSTA,
    .read = synth_read_IVA22SSTA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_SGXSSTA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_SGXSSTA.addr + addr, val);
}

static uint64_t synth_read_SGXSSTA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_SGXSSTA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_SGXSSTA =
{
    .write = synth_write_SGXSSTA,
    .read = synth_read_SGXSSTA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4CoreTA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4CoreTA.addr + addr, val);
}

static uint64_t synth_read_L4CoreTA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4CoreTA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4CoreTA =
{
    .write = synth_write_L4CoreTA,
    .read = synth_read_L4CoreTA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4PerTA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4PerTA.addr + addr, val);
}

static uint64_t synth_read_L4PerTA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4PerTA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4PerTA =
{
    .write = synth_write_L4PerTA,
    .read = synth_read_L4PerTA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_Reserved3(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_Reserved3.addr + addr, val);
}

static uint64_t synth_read_Reserved3(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_Reserved3.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_Reserved3 =
{
    .write = synth_write_Reserved3,
    .read = synth_read_Reserved3,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_RTPM(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_RTPM.addr + addr, val);
}

static uint64_t synth_read_RTPM(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_RTPM.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_RTPM =
{
    .write = synth_write_RTPM,
    .read = synth_read_RTPM,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_Reserved4(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_Reserved4.addr + addr, val);
}

static uint64_t synth_read_Reserved4(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_Reserved4.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_Reserved4 =
{
    .write = synth_write_Reserved4,
    .read = synth_read_Reserved4,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_GPMCPM(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_GPMCPM.addr + addr, val);
}

static uint64_t synth_read_GPMCPM(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_GPMCPM.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_GPMCPM =
{
    .write = synth_write_GPMCPM,
    .read = synth_read_GPMCPM,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_OCMRAMPM(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_OCMRAMPM.addr + addr, val);
}

static uint64_t synth_read_OCMRAMPM(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_OCMRAMPM.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_OCMRAMPM =
{
    .write = synth_write_OCMRAMPM,
    .read = synth_read_OCMRAMPM,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_OCMROMPM(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_OCMROMPM.addr + addr, val);
}

static uint64_t synth_read_OCMROMPM(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_OCMROMPM.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_OCMROMPM =
{
    .write = synth_write_OCMROMPM,
    .read = synth_read_OCMROMPM,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_D2DPM(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_D2DPM.addr + addr, val);
}

static uint64_t synth_read_D2DPM(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_D2DPM.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_D2DPM =
{
    .write = synth_write_D2DPM,
    .read = synth_read_D2DPM,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_Reserved5(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_Reserved5.addr + addr, val);
}

static uint64_t synth_read_Reserved5(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_Reserved5.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_Reserved5 =
{
    .write = synth_write_Reserved5,
    .read = synth_read_Reserved5,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_IVA22PM(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_IVA22PM.addr + addr, val);
}

static uint64_t synth_read_IVA22PM(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_IVA22PM.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_IVA22PM =
{
    .write = synth_write_IVA22PM,
    .read = synth_read_IVA22PM,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_Reserved6(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_Reserved6.addr + addr, val);
}

static uint64_t synth_read_Reserved6(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_Reserved6.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_Reserved6 =
{
    .write = synth_write_Reserved6,
    .read = synth_read_Reserved6,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_SMS(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_SMS.addr + addr, val);
}

static uint64_t synth_read_SMS(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_SMS.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_SMS =
{
    .write = synth_write_SMS,
    .read = synth_read_SMS,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_SDRC(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_SDRC.addr + addr, val);
}

static uint64_t synth_read_SDRC(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_SDRC.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_SDRC =
{
    .write = synth_write_SDRC,
    .read = synth_read_SDRC,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_GPMC(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_GPMC.addr + addr, val);
}

static uint64_t synth_read_GPMC(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_GPMC.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_GPMC =
{
    .write = synth_write_GPMC,
    .read = synth_read_GPMC,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_SCM(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_SCM.addr + addr, val);
}

static uint64_t synth_read_L4ID_SCM(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_SCM.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_SCM =
{
    .write = synth_write_L4ID_SCM,
    .read = synth_read_L4ID_SCM,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_SCM_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_SCM_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_SCM_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_SCM_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_SCM_TA =
{
    .write = synth_write_L4ID_SCM_TA,
    .read = synth_read_L4ID_SCM_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_CM_A(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_CM_A.addr + addr, val);
}

static uint64_t synth_read_L4ID_CM_A(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_CM_A.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_CM_A =
{
    .write = synth_write_L4ID_CM_A,
    .read = synth_read_L4ID_CM_A,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_CM_B(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_CM_B.addr + addr, val);
}

static uint64_t synth_read_L4ID_CM_B(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_CM_B.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_CM_B =
{
    .write = synth_write_L4ID_CM_B,
    .read = synth_read_L4ID_CM_B,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_CM_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_CM_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_CM_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_CM_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_CM_TA =
{
    .write = synth_write_L4ID_CM_TA,
    .read = synth_read_L4ID_CM_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_CORE_AP(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_CORE_AP.addr + addr, val);
}

static uint64_t synth_read_L4ID_CORE_AP(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_CORE_AP.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_CORE_AP =
{
    .write = synth_write_L4ID_CORE_AP,
    .read = synth_read_L4ID_CORE_AP,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_CORE_IP(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_CORE_IP.addr + addr, val);
}

static uint64_t synth_read_L4ID_CORE_IP(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_CORE_IP.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_CORE_IP =
{
    .write = synth_write_L4ID_CORE_IP,
    .read = synth_read_L4ID_CORE_IP,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_CORE_LA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_CORE_LA.addr + addr, val);
}

static uint64_t synth_read_L4ID_CORE_LA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_CORE_LA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_CORE_LA =
{
    .write = synth_write_L4ID_CORE_LA,
    .read = synth_read_L4ID_CORE_LA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_DSI(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_DSI.addr + addr, val);
}

static uint64_t synth_read_L4ID_DSI(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_DSI.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_DSI =
{
    .write = synth_write_L4ID_DSI,
    .read = synth_read_L4ID_DSI,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_DSS(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_DSS.addr + addr, val);
}

static uint64_t synth_read_L4ID_DSS(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_DSS.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_DSS =
{
    .write = synth_write_L4ID_DSS,
    .read = synth_read_L4ID_DSS,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_DISPC(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_DISPC.addr + addr, val);
}

static uint64_t synth_read_L4ID_DISPC(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_DISPC.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_DISPC =
{
    .write = synth_write_L4ID_DISPC,
    .read = synth_read_L4ID_DISPC,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_RFBI(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_RFBI.addr + addr, val);
}

static uint64_t synth_read_L4ID_RFBI(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_RFBI.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_RFBI =
{
    .write = synth_write_L4ID_RFBI,
    .read = synth_read_L4ID_RFBI,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_VENC(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_VENC.addr + addr, val);
}

static uint64_t synth_read_L4ID_VENC(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_VENC.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_VENC =
{
    .write = synth_write_L4ID_VENC,
    .read = synth_read_L4ID_VENC,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_DSS_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_DSS_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_DSS_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_DSS_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_DSS_TA =
{
    .write = synth_write_L4ID_DSS_TA,
    .read = synth_read_L4ID_DSS_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_SDMA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_SDMA.addr + addr, val);
}

static uint64_t synth_read_L4ID_SDMA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_SDMA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_SDMA =
{
    .write = synth_write_L4ID_SDMA,
    .read = synth_read_L4ID_SDMA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_SDMA_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_SDMA_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_SDMA_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_SDMA_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_SDMA_TA =
{
    .write = synth_write_L4ID_SDMA_TA,
    .read = synth_read_L4ID_SDMA_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_I2C3(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_I2C3.addr + addr, val);
}

static uint64_t synth_read_L4ID_I2C3(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_I2C3.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_I2C3 =
{
    .write = synth_write_L4ID_I2C3,
    .read = synth_read_L4ID_I2C3,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_I2C3_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_I2C3_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_I2C3_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_I2C3_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_I2C3_TA =
{
    .write = synth_write_L4ID_I2C3_TA,
    .read = synth_read_L4ID_I2C3_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_4ID_USBTLL(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_4ID_USBTLL.addr + addr, val);
}

static uint64_t synth_read_4ID_USBTLL(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_4ID_USBTLL.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_4ID_USBTLL =
{
    .write = synth_write_4ID_USBTLL,
    .read = synth_read_4ID_USBTLL,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_USBTLL_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_USBTLL_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_USBTLL_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_USBTLL_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_USBTLL_TA =
{
    .write = synth_write_L4ID_USBTLL_TA,
    .read = synth_read_L4ID_USBTLL_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_4ID_USBHOST(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_4ID_USBHOST.addr + addr, val);
}

static uint64_t synth_read_4ID_USBHOST(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_4ID_USBHOST.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_4ID_USBHOST =
{
    .write = synth_write_4ID_USBHOST,
    .read = synth_read_4ID_USBHOST,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_USBHOST_OHCI(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_USBHOST_OHCI.addr + addr, val);
}

static uint64_t synth_read_L4ID_USBHOST_OHCI(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_USBHOST_OHCI.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_USBHOST_OHCI =
{
    .write = synth_write_L4ID_USBHOST_OHCI,
    .read = synth_read_L4ID_USBHOST_OHCI,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_4ID_USBHOST_EHCI(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_4ID_USBHOST_EHCI.addr + addr, val);
}

static uint64_t synth_read_4ID_USBHOST_EHCI(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_4ID_USBHOST_EHCI.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_4ID_USBHOST_EHCI =
{
    .write = synth_write_4ID_USBHOST_EHCI,
    .read = synth_read_4ID_USBHOST_EHCI,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_USBHOST_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_USBHOST_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_USBHOST_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_USBHOST_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_USBHOST_TA =
{
    .write = synth_write_L4ID_USBHOST_TA,
    .read = synth_read_L4ID_USBHOST_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_UART1(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_UART1.addr + addr, val);
}

static uint64_t synth_read_L4ID_UART1(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_UART1.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_UART1 =
{
    .write = synth_write_L4ID_UART1,
    .read = synth_read_L4ID_UART1,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_UART1_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_UART1_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_UART1_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_UART1_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_UART1_TA =
{
    .write = synth_write_L4ID_UART1_TA,
    .read = synth_read_L4ID_UART1_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_4ID_UART2(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_4ID_UART2.addr + addr, val);
}

static uint64_t synth_read_4ID_UART2(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_4ID_UART2.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_4ID_UART2 =
{
    .write = synth_write_4ID_UART2,
    .read = synth_read_4ID_UART2,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_UART2_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_UART2_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_UART2_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_UART2_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_UART2_TA =
{
    .write = synth_write_L4ID_UART2_TA,
    .read = synth_read_L4ID_UART2_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_I2C1(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_I2C1.addr + addr, val);
}

static uint64_t synth_read_L4ID_I2C1(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_I2C1.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_I2C1 =
{
    .write = synth_write_L4ID_I2C1,
    .read = synth_read_L4ID_I2C1,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_I2C1_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_I2C1_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_I2C1_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_I2C1_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_I2C1_TA =
{
    .write = synth_write_L4ID_I2C1_TA,
    .read = synth_read_L4ID_I2C1_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_I2C2(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_I2C2.addr + addr, val);
}

static uint64_t synth_read_L4ID_I2C2(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_I2C2.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_I2C2 =
{
    .write = synth_write_L4ID_I2C2,
    .read = synth_read_L4ID_I2C2,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_I2C2_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_I2C2_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_I2C2_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_I2C2_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_I2C2_TA =
{
    .write = synth_write_L4ID_I2C2_TA,
    .read = synth_read_L4ID_I2C2_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCBSP1(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCBSP1.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCBSP1(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCBSP1.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCBSP1 =
{
    .write = synth_write_L4ID_MCBSP1,
    .read = synth_read_L4ID_MCBSP1,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCBSP1_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCBSP1_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCBSP1_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCBSP1_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCBSP1_TA =
{
    .write = synth_write_L4ID_MCBSP1_TA,
    .read = synth_read_L4ID_MCBSP1_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER10(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER10.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER10(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER10.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER10 =
{
    .write = synth_write_L4ID_GPTIMER10,
    .read = synth_read_L4ID_GPTIMER10,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER10_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER10_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER10_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER10_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER10_TA =
{
    .write = synth_write_L4ID_GPTIMER10_TA,
    .read = synth_read_L4ID_GPTIMER10_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_4ID_GPTIMER11(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_4ID_GPTIMER11.addr + addr, val);
}

static uint64_t synth_read_4ID_GPTIMER11(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_4ID_GPTIMER11.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_4ID_GPTIMER11 =
{
    .write = synth_write_4ID_GPTIMER11,
    .read = synth_read_4ID_GPTIMER11,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER11_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER11_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER11_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER11_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER11_TA =
{
    .write = synth_write_L4ID_GPTIMER11_TA,
    .read = synth_read_L4ID_GPTIMER11_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MAILBOX(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MAILBOX.addr + addr, val);
}

static uint64_t synth_read_L4ID_MAILBOX(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MAILBOX.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MAILBOX =
{
    .write = synth_write_L4ID_MAILBOX,
    .read = synth_read_L4ID_MAILBOX,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MAILBOX_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MAILBOX_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_MAILBOX_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MAILBOX_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MAILBOX_TA =
{
    .write = synth_write_L4ID_MAILBOX_TA,
    .read = synth_read_L4ID_MAILBOX_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCBSP5(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCBSP5.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCBSP5(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCBSP5.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCBSP5 =
{
    .write = synth_write_L4ID_MCBSP5,
    .read = synth_read_L4ID_MCBSP5,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCBSP5_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCBSP5_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCBSP5_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCBSP5_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCBSP5_TA =
{
    .write = synth_write_L4ID_MCBSP5_TA,
    .read = synth_read_L4ID_MCBSP5_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCSPI1(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCSPI1.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCSPI1(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCSPI1.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCSPI1 =
{
    .write = synth_write_L4ID_MCSPI1,
    .read = synth_read_L4ID_MCSPI1,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCSPI1_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCSPI1_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCSPI1_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCSPI1_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCSPI1_TA =
{
    .write = synth_write_L4ID_MCSPI1_TA,
    .read = synth_read_L4ID_MCSPI1_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCSPI2(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCSPI2.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCSPI2(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCSPI2.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCSPI2 =
{
    .write = synth_write_L4ID_MCSPI2,
    .read = synth_read_L4ID_MCSPI2,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCSPI2_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCSPI2_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCSPI2_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCSPI2_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCSPI2_TA =
{
    .write = synth_write_L4ID_MCSPI2_TA,
    .read = synth_read_L4ID_MCSPI2_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MMCSDIO1(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MMCSDIO1.addr + addr, val);
}

static uint64_t synth_read_L4ID_MMCSDIO1(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MMCSDIO1.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MMCSDIO1 =
{
    .write = synth_write_L4ID_MMCSDIO1,
    .read = synth_read_L4ID_MMCSDIO1,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MMCSDIO1_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MMCSDIO1_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_MMCSDIO1_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MMCSDIO1_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MMCSDIO1_TA =
{
    .write = synth_write_L4ID_MMCSDIO1_TA,
    .read = synth_read_L4ID_MMCSDIO1_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MSPRO(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MSPRO.addr + addr, val);
}

static uint64_t synth_read_L4ID_MSPRO(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MSPRO.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MSPRO =
{
    .write = synth_write_L4ID_MSPRO,
    .read = synth_read_L4ID_MSPRO,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MSPRO_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MSPRO_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_MSPRO_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MSPRO_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MSPRO_TA =
{
    .write = synth_write_L4ID_MSPRO_TA,
    .read = synth_read_L4ID_MSPRO_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_HSUSBOTG(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_HSUSBOTG.addr + addr, val);
}

static uint64_t synth_read_L4ID_HSUSBOTG(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_HSUSBOTG.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_HSUSBOTG =
{
    .write = synth_write_L4ID_HSUSBOTG,
    .read = synth_read_L4ID_HSUSBOTG,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_HSUSBOTG_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_HSUSBOTG_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_HSUSBOTG_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_HSUSBOTG_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_HSUSBOTG_TA =
{
    .write = synth_write_L4ID_HSUSBOTG_TA,
    .read = synth_read_L4ID_HSUSBOTG_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MMCSDIO3(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MMCSDIO3.addr + addr, val);
}

static uint64_t synth_read_L4ID_MMCSDIO3(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MMCSDIO3.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MMCSDIO3 =
{
    .write = synth_write_L4ID_MMCSDIO3,
    .read = synth_read_L4ID_MMCSDIO3,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MMCSDIO3_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MMCSDIO3_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_MMCSDIO3_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MMCSDIO3_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MMCSDIO3_TA =
{
    .write = synth_write_L4ID_MMCSDIO3_TA,
    .read = synth_read_L4ID_MMCSDIO3_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_HDQ1WIRE(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_HDQ1WIRE.addr + addr, val);
}

static uint64_t synth_read_L4ID_HDQ1WIRE(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_HDQ1WIRE.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_HDQ1WIRE =
{
    .write = synth_write_L4ID_HDQ1WIRE,
    .read = synth_read_L4ID_HDQ1WIRE,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_HDQ1WIRE_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_HDQ1WIRE_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_HDQ1WIRE_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_HDQ1WIRE_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_HDQ1WIRE_TA =
{
    .write = synth_write_L4ID_HDQ1WIRE_TA,
    .read = synth_read_L4ID_HDQ1WIRE_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MMCSDIO2(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MMCSDIO2.addr + addr, val);
}

static uint64_t synth_read_L4ID_MMCSDIO2(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MMCSDIO2.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MMCSDIO2 =
{
    .write = synth_write_L4ID_MMCSDIO2,
    .read = synth_read_L4ID_MMCSDIO2,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MMCSDIO2_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MMCSDIO2_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_MMCSDIO2_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MMCSDIO2_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MMCSDIO2_TA =
{
    .write = synth_write_L4ID_MMCSDIO2_TA,
    .read = synth_read_L4ID_MMCSDIO2_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_ICRMPU(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_ICRMPU.addr + addr, val);
}

static uint64_t synth_read_L4ID_ICRMPU(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_ICRMPU.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_ICRMPU =
{
    .write = synth_write_L4ID_ICRMPU,
    .read = synth_read_L4ID_ICRMPU,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_ICRMPU_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_ICRMPU_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_ICRMPU_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_ICRMPU_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_ICRMPU_TA =
{
    .write = synth_write_L4ID_ICRMPU_TA,
    .read = synth_read_L4ID_ICRMPU_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCSPI3(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCSPI3.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCSPI3(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCSPI3.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCSPI3 =
{
    .write = synth_write_L4ID_MCSPI3,
    .read = synth_read_L4ID_MCSPI3,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCSPI3_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCSPI3_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCSPI3_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCSPI3_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCSPI3_TA =
{
    .write = synth_write_L4ID_MCSPI3_TA,
    .read = synth_read_L4ID_MCSPI3_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCSPI4(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCSPI4.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCSPI4(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCSPI4.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCSPI4 =
{
    .write = synth_write_L4ID_MCSPI4,
    .read = synth_read_L4ID_MCSPI4,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCSPI4_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCSPI4_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCSPI4_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCSPI4_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCSPI4_TA =
{
    .write = synth_write_L4ID_MCSPI4_TA,
    .read = synth_read_L4ID_MCSPI4_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_CAMERAISP(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_CAMERAISP.addr + addr, val);
}

static uint64_t synth_read_L4ID_CAMERAISP(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_CAMERAISP.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_CAMERAISP =
{
    .write = synth_write_L4ID_CAMERAISP,
    .read = synth_read_L4ID_CAMERAISP,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_CAMERAISP_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_CAMERAISP_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_CAMERAISP_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_CAMERAISP_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_CAMERAISP_TA =
{
    .write = synth_write_L4ID_CAMERAISP_TA,
    .read = synth_read_L4ID_CAMERAISP_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_SR1(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_SR1.addr + addr, val);
}

static uint64_t synth_read_L4ID_SR1(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_SR1.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_SR1 =
{
    .write = synth_write_L4ID_SR1,
    .read = synth_read_L4ID_SR1,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_SR1_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_SR1_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_SR1_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_SR1_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_SR1_TA =
{
    .write = synth_write_L4ID_SR1_TA,
    .read = synth_read_L4ID_SR1_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_SR2(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_SR2.addr + addr, val);
}

static uint64_t synth_read_L4ID_SR2(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_SR2.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_SR2 =
{
    .write = synth_write_L4ID_SR2,
    .read = synth_read_L4ID_SR2,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_SR2_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_SR2_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_SR2_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_SR2_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_SR2_TA =
{
    .write = synth_write_L4ID_SR2_TA,
    .read = synth_read_L4ID_SR2_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_ICRMODEM(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_ICRMODEM.addr + addr, val);
}

static uint64_t synth_read_L4ID_ICRMODEM(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_ICRMODEM.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_ICRMODEM =
{
    .write = synth_write_L4ID_ICRMODEM,
    .read = synth_read_L4ID_ICRMODEM,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_ICRMODEM_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_ICRMODEM_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_ICRMODEM_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_ICRMODEM_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_ICRMODEM_TA =
{
    .write = synth_write_L4ID_ICRMODEM_TA,
    .read = synth_read_L4ID_ICRMODEM_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER12(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER12.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER12(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER12.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER12 =
{
    .write = synth_write_L4ID_GPTIMER12,
    .read = synth_read_L4ID_GPTIMER12,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER12_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER12_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER12_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER12_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER12_TA =
{
    .write = synth_write_L4ID_GPTIMER12_TA,
    .read = synth_read_L4ID_GPTIMER12_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_PRM_A(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_PRM_A.addr + addr, val);
}

static uint64_t synth_read_L4ID_PRM_A(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_PRM_A.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_PRM_A =
{
    .write = synth_write_L4ID_PRM_A,
    .read = synth_read_L4ID_PRM_A,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_PRM_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_PRM_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_PRM_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_PRM_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_PRM_TA =
{
    .write = synth_write_L4ID_PRM_TA,
    .read = synth_read_L4ID_PRM_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_TAP(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_TAP.addr + addr, val);
}

static uint64_t synth_read_L4ID_TAP(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_TAP.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_TAP =
{
    .write = synth_write_L4ID_TAP,
    .read = synth_read_L4ID_TAP,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_TAP_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_TAP_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_TAP_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_TAP_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_TAP_TA =
{
    .write = synth_write_L4ID_TAP_TA,
    .read = synth_read_L4ID_TAP_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPIO1(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPIO1.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPIO1(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPIO1.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPIO1 =
{
    .write = synth_write_L4ID_GPIO1,
    .read = synth_read_L4ID_GPIO1,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPIO1_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPIO1_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPIO1_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPIO1_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPIO1_TA =
{
    .write = synth_write_L4ID_GPIO1_TA,
    .read = synth_read_L4ID_GPIO1_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_WDTIMER2(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_WDTIMER2.addr + addr, val);
}

static uint64_t synth_read_L4ID_WDTIMER2(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_WDTIMER2.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_WDTIMER2 =
{
    .write = synth_write_L4ID_WDTIMER2,
    .read = synth_read_L4ID_WDTIMER2,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_WDTIMER2_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_WDTIMER2_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_WDTIMER2_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_WDTIMER2_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_WDTIMER2_TA =
{
    .write = synth_write_L4ID_WDTIMER2_TA,
    .read = synth_read_L4ID_WDTIMER2_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER1(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER1.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER1(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER1.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER1 =
{
    .write = synth_write_L4ID_GPTIMER1,
    .read = synth_read_L4ID_GPTIMER1,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER1_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER1_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER1_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER1_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER1_TA =
{
    .write = synth_write_L4ID_GPTIMER1_TA,
    .read = synth_read_L4ID_GPTIMER1_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_32KTIMER(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_32KTIMER.addr + addr, val);
}

static uint64_t synth_read_L4ID_32KTIMER(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_32KTIMER.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_32KTIMER =
{
    .write = synth_write_L4ID_32KTIMER,
    .read = synth_read_L4ID_32KTIMER,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_32KTIMER_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_32KTIMER_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_32KTIMER_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_32KTIMER_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_32KTIMER_TA =
{
    .write = synth_write_L4ID_32KTIMER_TA,
    .read = synth_read_L4ID_32KTIMER_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_WAKEUP_AP(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_WAKEUP_AP.addr + addr, val);
}

static uint64_t synth_read_L4ID_WAKEUP_AP(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_WAKEUP_AP.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_WAKEUP_AP =
{
    .write = synth_write_L4ID_WAKEUP_AP,
    .read = synth_read_L4ID_WAKEUP_AP,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_WAKEUP_C_IP(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_WAKEUP_C_IP.addr + addr, val);
}

static uint64_t synth_read_L4ID_WAKEUP_C_IP(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_WAKEUP_C_IP.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_WAKEUP_C_IP =
{
    .write = synth_write_L4ID_WAKEUP_C_IP,
    .read = synth_read_L4ID_WAKEUP_C_IP,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_WAKEUP_LA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_WAKEUP_LA.addr + addr, val);
}

static uint64_t synth_read_L4ID_WAKEUP_LA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_WAKEUP_LA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_WAKEUP_LA =
{
    .write = synth_write_L4ID_WAKEUP_LA,
    .read = synth_read_L4ID_WAKEUP_LA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_WAKEUP_E_IP(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_WAKEUP_E_IP.addr + addr, val);
}

static uint64_t synth_read_L4ID_WAKEUP_E_IP(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_WAKEUP_E_IP.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_WAKEUP_E_IP =
{
    .write = synth_write_L4ID_WAKEUP_E_IP,
    .read = synth_read_L4ID_WAKEUP_E_IP,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_PER_AP(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_PER_AP.addr + addr, val);
}

static uint64_t synth_read_L4ID_PER_AP(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_PER_AP.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_PER_AP =
{
    .write = synth_write_L4ID_PER_AP,
    .read = synth_read_L4ID_PER_AP,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_PER_IP(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_PER_IP.addr + addr, val);
}

static uint64_t synth_read_L4ID_PER_IP(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_PER_IP.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_PER_IP =
{
    .write = synth_write_L4ID_PER_IP,
    .read = synth_read_L4ID_PER_IP,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_PER_LA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_PER_LA.addr + addr, val);
}

static uint64_t synth_read_L4ID_PER_LA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_PER_LA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_PER_LA =
{
    .write = synth_write_L4ID_PER_LA,
    .read = synth_read_L4ID_PER_LA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_UART3(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_UART3.addr + addr, val);
}

static uint64_t synth_read_L4ID_UART3(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_UART3.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_UART3 =
{
    .write = synth_write_L4ID_UART3,
    .read = synth_read_L4ID_UART3,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_UART3_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_UART3_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_UART3_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_UART3_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_UART3_TA =
{
    .write = synth_write_L4ID_UART3_TA,
    .read = synth_read_L4ID_UART3_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCBSP2(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCBSP2.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCBSP2(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCBSP2.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCBSP2 =
{
    .write = synth_write_L4ID_MCBSP2,
    .read = synth_read_L4ID_MCBSP2,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCBSP2_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCBSP2_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCBSP2_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCBSP2_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCBSP2_TA =
{
    .write = synth_write_L4ID_MCBSP2_TA,
    .read = synth_read_L4ID_MCBSP2_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCBSP3(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCBSP3.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCBSP3(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCBSP3.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCBSP3 =
{
    .write = synth_write_L4ID_MCBSP3,
    .read = synth_read_L4ID_MCBSP3,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCBSP3_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCBSP3_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCBSP3_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCBSP3_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCBSP3_TA =
{
    .write = synth_write_L4ID_MCBSP3_TA,
    .read = synth_read_L4ID_MCBSP3_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCBSP4(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCBSP4.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCBSP4(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCBSP4.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCBSP4 =
{
    .write = synth_write_L4ID_MCBSP4,
    .read = synth_read_L4ID_MCBSP4,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCBSP4_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCBSP4_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCBSP4_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCBSP4_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCBSP4_TA =
{
    .write = synth_write_L4ID_MCBSP4_TA,
    .read = synth_read_L4ID_MCBSP4_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCBSP2S(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCBSP2S.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCBSP2S(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCBSP2S.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCBSP2S =
{
    .write = synth_write_L4ID_MCBSP2S,
    .read = synth_read_L4ID_MCBSP2S,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCBSP2S_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCBSP2S_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCBSP2S_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCBSP2S_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCBSP2S_TA =
{
    .write = synth_write_L4ID_MCBSP2S_TA,
    .read = synth_read_L4ID_MCBSP2S_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCBSP3S(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCBSP3S.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCBSP3S(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCBSP3S.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCBSP3S =
{
    .write = synth_write_L4ID_MCBSP3S,
    .read = synth_read_L4ID_MCBSP3S,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MCBSP3S_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MCBSP3S_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_MCBSP3S_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MCBSP3S_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MCBSP3S_TA =
{
    .write = synth_write_L4ID_MCBSP3S_TA,
    .read = synth_read_L4ID_MCBSP3S_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_WDTIMER3(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_WDTIMER3.addr + addr, val);
}

static uint64_t synth_read_L4ID_WDTIMER3(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_WDTIMER3.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_WDTIMER3 =
{
    .write = synth_write_L4ID_WDTIMER3,
    .read = synth_read_L4ID_WDTIMER3,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_WDTIMER3_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_WDTIMER3_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_WDTIMER3_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_WDTIMER3_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_WDTIMER3_TA =
{
    .write = synth_write_L4ID_WDTIMER3_TA,
    .read = synth_read_L4ID_WDTIMER3_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER2(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER2.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER2(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER2.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER2 =
{
    .write = synth_write_L4ID_GPTIMER2,
    .read = synth_read_L4ID_GPTIMER2,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER2_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER2_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER2_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER2_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER2_TA =
{
    .write = synth_write_L4ID_GPTIMER2_TA,
    .read = synth_read_L4ID_GPTIMER2_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER3(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER3.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER3(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER3.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER3 =
{
    .write = synth_write_L4ID_GPTIMER3,
    .read = synth_read_L4ID_GPTIMER3,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER3_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER3_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER3_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER3_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER3_TA =
{
    .write = synth_write_L4ID_GPTIMER3_TA,
    .read = synth_read_L4ID_GPTIMER3_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER4(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER4.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER4(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER4.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER4 =
{
    .write = synth_write_L4ID_GPTIMER4,
    .read = synth_read_L4ID_GPTIMER4,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER4_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER4_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER4_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER4_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER4_TA =
{
    .write = synth_write_L4ID_GPTIMER4_TA,
    .read = synth_read_L4ID_GPTIMER4_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER5(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER5.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER5(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER5.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER5 =
{
    .write = synth_write_L4ID_GPTIMER5,
    .read = synth_read_L4ID_GPTIMER5,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER5_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER5_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER5_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER5_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER5_TA =
{
    .write = synth_write_L4ID_GPTIMER5_TA,
    .read = synth_read_L4ID_GPTIMER5_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER6(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER6.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER6(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER6.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER6 =
{
    .write = synth_write_L4ID_GPTIMER6,
    .read = synth_read_L4ID_GPTIMER6,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER6_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER6_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER6_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER6_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER6_TA =
{
    .write = synth_write_L4ID_GPTIMER6_TA,
    .read = synth_read_L4ID_GPTIMER6_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER7(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER7.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER7(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER7.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER7 =
{
    .write = synth_write_L4ID_GPTIMER7,
    .read = synth_read_L4ID_GPTIMER7,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER7_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER7_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER7_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER7_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER7_TA =
{
    .write = synth_write_L4ID_GPTIMER7_TA,
    .read = synth_read_L4ID_GPTIMER7_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER8(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER8.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER8(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER8.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER8 =
{
    .write = synth_write_L4ID_GPTIMER8,
    .read = synth_read_L4ID_GPTIMER8,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER8_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER8_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER8_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER8_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER8_TA =
{
    .write = synth_write_L4ID_GPTIMER8_TA,
    .read = synth_read_L4ID_GPTIMER8_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER9(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER9.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER9(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER9.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER9 =
{
    .write = synth_write_L4ID_GPTIMER9,
    .read = synth_read_L4ID_GPTIMER9,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPTIMER9_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPTIMER9_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPTIMER9_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPTIMER9_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPTIMER9_TA =
{
    .write = synth_write_L4ID_GPTIMER9_TA,
    .read = synth_read_L4ID_GPTIMER9_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_UART4(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_UART4.addr + addr, val);
}

static uint64_t synth_read_L4ID_UART4(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_UART4.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_UART4 =
{
    .write = synth_write_L4ID_UART4,
    .read = synth_read_L4ID_UART4,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_UART4_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_UART4_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_UART4_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_UART4_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_UART4_TA =
{
    .write = synth_write_L4ID_UART4_TA,
    .read = synth_read_L4ID_UART4_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPIO2(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPIO2.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPIO2(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPIO2.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPIO2 =
{
    .write = synth_write_L4ID_GPIO2,
    .read = synth_read_L4ID_GPIO2,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPIO2_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPIO2_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPIO2_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPIO2_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPIO2_TA =
{
    .write = synth_write_L4ID_GPIO2_TA,
    .read = synth_read_L4ID_GPIO2_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPIO3(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPIO3.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPIO3(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPIO3.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPIO3 =
{
    .write = synth_write_L4ID_GPIO3,
    .read = synth_read_L4ID_GPIO3,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPIO3_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPIO3_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPIO3_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPIO3_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPIO3_TA =
{
    .write = synth_write_L4ID_GPIO3_TA,
    .read = synth_read_L4ID_GPIO3_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPIO4(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPIO4.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPIO4(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPIO4.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPIO4 =
{
    .write = synth_write_L4ID_GPIO4,
    .read = synth_read_L4ID_GPIO4,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPIO4_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPIO4_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPIO4_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPIO4_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPIO4_TA =
{
    .write = synth_write_L4ID_GPIO4_TA,
    .read = synth_read_L4ID_GPIO4_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPIO5(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPIO5.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPIO5(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPIO5.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPIO5 =
{
    .write = synth_write_L4ID_GPIO5,
    .read = synth_read_L4ID_GPIO5,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPIO5_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPIO5_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPIO5_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPIO5_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPIO5_TA =
{
    .write = synth_write_L4ID_GPIO5_TA,
    .read = synth_read_L4ID_GPIO5_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPIO6(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPIO6.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPIO6(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPIO6.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPIO6 =
{
    .write = synth_write_L4ID_GPIO6,
    .read = synth_read_L4ID_GPIO6,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_GPIO6_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_GPIO6_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_GPIO6_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_GPIO6_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_GPIO6_TA =
{
    .write = synth_write_L4ID_GPIO6_TA,
    .read = synth_read_L4ID_GPIO6_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_AP(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_AP.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_AP(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_AP.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_AP =
{
    .write = synth_write_L4ID_EMU_AP,
    .read = synth_read_L4ID_EMU_AP,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_IP_C(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_IP_C.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_IP_C(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_IP_C.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_IP_C =
{
    .write = synth_write_L4ID_EMU_IP_C,
    .read = synth_read_L4ID_EMU_IP_C,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_LA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_LA.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_LA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_LA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_LA =
{
    .write = synth_write_L4ID_EMU_LA,
    .read = synth_read_L4ID_EMU_LA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_IP_DAP(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_IP_DAP.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_IP_DAP(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_IP_DAP.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_IP_DAP =
{
    .write = synth_write_L4ID_EMU_IP_DAP,
    .read = synth_read_L4ID_EMU_IP_DAP,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MPUEMU(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MPUEMU.addr + addr, val);
}

static uint64_t synth_read_L4ID_MPUEMU(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MPUEMU.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MPUEMU =
{
    .write = synth_write_L4ID_MPUEMU,
    .read = synth_read_L4ID_MPUEMU,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_MPUEMU_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_MPUEMU_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_MPUEMU_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_MPUEMU_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_MPUEMU_TA =
{
    .write = synth_write_L4ID_MPUEMU_TA,
    .read = synth_read_L4ID_MPUEMU_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_TPIU(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_TPIU.addr + addr, val);
}

static uint64_t synth_read_L4ID_TPIU(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_TPIU.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_TPIU =
{
    .write = synth_write_L4ID_TPIU,
    .read = synth_read_L4ID_TPIU,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_TPIU_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_TPIU_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_TPIU_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_TPIU_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_TPIU_TA =
{
    .write = synth_write_L4ID_TPIU_TA,
    .read = synth_read_L4ID_TPIU_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_ETB(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_ETB.addr + addr, val);
}

static uint64_t synth_read_L4ID_ETB(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_ETB.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_ETB =
{
    .write = synth_write_L4ID_ETB,
    .read = synth_read_L4ID_ETB,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_ETB_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_ETB_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_ETB_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_ETB_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_ETB_TA =
{
    .write = synth_write_L4ID_ETB_TA,
    .read = synth_read_L4ID_ETB_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_DAPCTL(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_DAPCTL.addr + addr, val);
}

static uint64_t synth_read_L4ID_DAPCTL(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_DAPCTL.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_DAPCTL =
{
    .write = synth_write_L4ID_DAPCTL,
    .read = synth_read_L4ID_DAPCTL,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_DAPCTL_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_DAPCTL_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_DAPCTL_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_DAPCTL_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_DAPCTL_TA =
{
    .write = synth_write_L4ID_DAPCTL_TA,
    .read = synth_read_L4ID_DAPCTL_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_SDTI_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_SDTI_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_SDTI_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_SDTI_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_SDTI_TA =
{
    .write = synth_write_L4ID_SDTI_TA,
    .read = synth_read_L4ID_SDTI_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_SDTI_CFG(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_SDTI_CFG.addr + addr, val);
}

static uint64_t synth_read_L4ID_SDTI_CFG(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_SDTI_CFG.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_SDTI_CFG =
{
    .write = synth_write_L4ID_SDTI_CFG,
    .read = synth_read_L4ID_SDTI_CFG,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_SDTI(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_SDTI.addr + addr, val);
}

static uint64_t synth_read_L4ID_SDTI(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_SDTI.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_SDTI =
{
    .write = synth_write_L4ID_SDTI,
    .read = synth_read_L4ID_SDTI,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_PRM_A(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_PRM_A.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_PRM_A(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_PRM_A.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_PRM_A =
{
    .write = synth_write_L4ID_EMU_PRM_A,
    .read = synth_read_L4ID_EMU_PRM_A,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_PRM_B(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_PRM_B.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_PRM_B(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_PRM_B.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_PRM_B =
{
    .write = synth_write_L4ID_EMU_PRM_B,
    .read = synth_read_L4ID_EMU_PRM_B,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_PRM_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_PRM_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_PRM_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_PRM_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_PRM_TA =
{
    .write = synth_write_L4ID_EMU_PRM_TA,
    .read = synth_read_L4ID_EMU_PRM_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_GPIO1(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_GPIO1.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_GPIO1(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_GPIO1.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_GPIO1 =
{
    .write = synth_write_L4ID_EMU_GPIO1,
    .read = synth_read_L4ID_EMU_GPIO1,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_GPIO1_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_GPIO1_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_GPIO1_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_GPIO1_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_GPIO1_TA =
{
    .write = synth_write_L4ID_EMU_GPIO1_TA,
    .read = synth_read_L4ID_EMU_GPIO1_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_WDTM2(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_WDTM2.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_WDTM2(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_WDTM2.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_WDTM2 =
{
    .write = synth_write_L4ID_EMU_WDTM2,
    .read = synth_read_L4ID_EMU_WDTM2,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_WDTM2_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_WDTM2_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_WDTM2_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_WDTM2_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_WDTM2_TA =
{
    .write = synth_write_L4ID_EMU_WDTM2_TA,
    .read = synth_read_L4ID_EMU_WDTM2_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_GPTM1(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_GPTM1.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_GPTM1(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_GPTM1.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_GPTM1 =
{
    .write = synth_write_L4ID_EMU_GPTM1,
    .read = synth_read_L4ID_EMU_GPTM1,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_GPTM1_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_GPTM1_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_GPTM1_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_GPTM1_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_GPTM1_TA =
{
    .write = synth_write_L4ID_EMU_GPTM1_TA,
    .read = synth_read_L4ID_EMU_GPTM1_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_32KTM(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_32KTM.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_32KTM(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_32KTM.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_32KTM =
{
    .write = synth_write_L4ID_EMU_32KTM,
    .read = synth_read_L4ID_EMU_32KTM,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_32KTM_TA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_32KTM_TA.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_32KTM_TA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_32KTM_TA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_32KTM_TA =
{
    .write = synth_write_L4ID_EMU_32KTM_TA,
    .read = synth_read_L4ID_EMU_32KTM_TA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_WKUP_AP(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_WKUP_AP.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_WKUP_AP(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_WKUP_AP.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_WKUP_AP =
{
    .write = synth_write_L4ID_EMU_WKUP_AP,
    .read = synth_read_L4ID_EMU_WKUP_AP,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_WKUP_IPC(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_WKUP_IPC.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_WKUP_IPC(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_WKUP_IPC.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_WKUP_IPC =
{
    .write = synth_write_L4ID_EMU_WKUP_IPC,
    .read = synth_read_L4ID_EMU_WKUP_IPC,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_WKUP_LA(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_WKUP_LA.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_WKUP_LA(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_WKUP_LA.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_WKUP_LA =
{
    .write = synth_write_L4ID_EMU_WKUP_LA,
    .read = synth_read_L4ID_EMU_WKUP_LA,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_L4ID_EMU_WKUP_IPE(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{  
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_L4ID_EMU_WKUP_IPE.addr + addr, val);
}

static uint64_t synth_read_L4ID_EMU_WKUP_IPE(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    return taint_mmio_read(sio->io_L4ID_EMU_WKUP_IPE.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_L4ID_EMU_WKUP_IPE =
{
    .write = synth_write_L4ID_EMU_WKUP_IPE,
    .read = synth_read_L4ID_EMU_WKUP_IPE,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_init(Object *d){}

static void synth_realize(DeviceState *d, Error **errp)
{
    SysBusDevice *dev = SYS_BUS_DEVICE(d);
    SynthState *sio = SYNTH(d);
    Object *obj = OBJECT(sio);
    MemoryRegion *sysbus = sysbus_address_space(dev);
    
    memory_region_init_io(
        &sio->io_L3RT, obj, &synth_io_ops_L3RT, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_L3RT);
    memory_region_add_subregion(sysbus, 0x68000000, &sio->io_L3RT);

    memory_region_init_io(
        &sio->io_L3SI, obj, &synth_io_ops_L3SI, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_L3SI);
    memory_region_add_subregion(sysbus, 0x68000400, &sio->io_L3SI);

    memory_region_init_io(
        &sio->io_Reserved0, obj, &synth_io_ops_Reserved0, sio, TYPE_SYNTH, 0xc00
    );
    sysbus_init_mmio(dev, &sio->io_Reserved0);
    memory_region_add_subregion(sysbus, 0x68000800, &sio->io_Reserved0);

    memory_region_init_io(
        &sio->io_MPUSSIA, obj, &synth_io_ops_MPUSSIA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_MPUSSIA);
    memory_region_add_subregion(sysbus, 0x68001400, &sio->io_MPUSSIA);

    memory_region_init_io(
        &sio->io_IVA22SSIA, obj, &synth_io_ops_IVA22SSIA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_IVA22SSIA);
    memory_region_add_subregion(sysbus, 0x68001800, &sio->io_IVA22SSIA);

    memory_region_init_io(
        &sio->io_SGXSSIA, obj, &synth_io_ops_SGXSSIA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_SGXSSIA);
    memory_region_add_subregion(sysbus, 0x68001c00, &sio->io_SGXSSIA);

    memory_region_init_io(
        &sio->io_SMSTA, obj, &synth_io_ops_SMSTA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_SMSTA);
    memory_region_add_subregion(sysbus, 0x68002000, &sio->io_SMSTA);

    memory_region_init_io(
        &sio->io_GPMCTA, obj, &synth_io_ops_GPMCTA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_GPMCTA);
    memory_region_add_subregion(sysbus, 0x68002400, &sio->io_GPMCTA);

    memory_region_init_io(
        &sio->io_OCMRAMTA, obj, &synth_io_ops_OCMRAMTA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_OCMRAMTA);
    memory_region_add_subregion(sysbus, 0x68002800, &sio->io_OCMRAMTA);

    memory_region_init_io(
        &sio->io_OCMROMTA, obj, &synth_io_ops_OCMROMTA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_OCMROMTA);
    memory_region_add_subregion(sysbus, 0x68002c00, &sio->io_OCMROMTA);

    memory_region_init_io(
        &sio->io_D2DIA, obj, &synth_io_ops_D2DIA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_D2DIA);
    memory_region_add_subregion(sysbus, 0x68003000, &sio->io_D2DIA);

    memory_region_init_io(
        &sio->io_D2DTA, obj, &synth_io_ops_D2DTA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_D2DTA);
    memory_region_add_subregion(sysbus, 0x68003400, &sio->io_D2DTA);

    memory_region_init_io(
        &sio->io_Reserved1, obj, &synth_io_ops_Reserved1, sio, TYPE_SYNTH, 0x800
    );
    sysbus_init_mmio(dev, &sio->io_Reserved1);
    memory_region_add_subregion(sysbus, 0x68003800, &sio->io_Reserved1);

    memory_region_init_io(
        &sio->io_HSUSBHOSTIA, obj, &synth_io_ops_HSUSBHOSTIA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_HSUSBHOSTIA);
    memory_region_add_subregion(sysbus, 0x68004000, &sio->io_HSUSBHOSTIA);

    memory_region_init_io(
        &sio->io_HSUSBOTGIA, obj, &synth_io_ops_HSUSBOTGIA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_HSUSBOTGIA);
    memory_region_add_subregion(sysbus, 0x68004400, &sio->io_HSUSBOTGIA);

    memory_region_init_io(
        &sio->io_Reserved2, obj, &synth_io_ops_Reserved2, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_Reserved2);
    memory_region_add_subregion(sysbus, 0x68004800, &sio->io_Reserved2);

    memory_region_init_io(
        &sio->io_sDMARDIA, obj, &synth_io_ops_sDMARDIA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_sDMARDIA);
    memory_region_add_subregion(sysbus, 0x68004c00, &sio->io_sDMARDIA);

    memory_region_init_io(
        &sio->io_sDMAWRIA, obj, &synth_io_ops_sDMAWRIA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_sDMAWRIA);
    memory_region_add_subregion(sysbus, 0x68005000, &sio->io_sDMAWRIA);

    memory_region_init_io(
        &sio->io_DisplaySSIA, obj, &synth_io_ops_DisplaySSIA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_DisplaySSIA);
    memory_region_add_subregion(sysbus, 0x68005400, &sio->io_DisplaySSIA);

    memory_region_init_io(
        &sio->io_CAMERAISPIA, obj, &synth_io_ops_CAMERAISPIA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_CAMERAISPIA);
    memory_region_add_subregion(sysbus, 0x68005800, &sio->io_CAMERAISPIA);

    memory_region_init_io(
        &sio->io_DAPIA, obj, &synth_io_ops_DAPIA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_DAPIA);
    memory_region_add_subregion(sysbus, 0x68005c00, &sio->io_DAPIA);

    memory_region_init_io(
        &sio->io_IVA22SSTA, obj, &synth_io_ops_IVA22SSTA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_IVA22SSTA);
    memory_region_add_subregion(sysbus, 0x68006000, &sio->io_IVA22SSTA);

    memory_region_init_io(
        &sio->io_SGXSSTA, obj, &synth_io_ops_SGXSSTA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_SGXSSTA);
    memory_region_add_subregion(sysbus, 0x68006400, &sio->io_SGXSSTA);

    memory_region_init_io(
        &sio->io_L4CoreTA, obj, &synth_io_ops_L4CoreTA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_L4CoreTA);
    memory_region_add_subregion(sysbus, 0x68006800, &sio->io_L4CoreTA);

    memory_region_init_io(
        &sio->io_L4PerTA, obj, &synth_io_ops_L4PerTA, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_L4PerTA);
    memory_region_add_subregion(sysbus, 0x68006c00, &sio->io_L4PerTA);

    memory_region_init_io(
        &sio->io_Reserved3, obj, &synth_io_ops_Reserved3, sio, TYPE_SYNTH, 0x9000
    );
    sysbus_init_mmio(dev, &sio->io_Reserved3);
    memory_region_add_subregion(sysbus, 0x68007000, &sio->io_Reserved3);

    memory_region_init_io(
        &sio->io_RTPM, obj, &synth_io_ops_RTPM, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_RTPM);
    memory_region_add_subregion(sysbus, 0x68010000, &sio->io_RTPM);

    memory_region_init_io(
        &sio->io_Reserved4, obj, &synth_io_ops_Reserved4, sio, TYPE_SYNTH, 0x2000
    );
    sysbus_init_mmio(dev, &sio->io_Reserved4);
    memory_region_add_subregion(sysbus, 0x68010400, &sio->io_Reserved4);

    memory_region_init_io(
        &sio->io_GPMCPM, obj, &synth_io_ops_GPMCPM, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_GPMCPM);
    memory_region_add_subregion(sysbus, 0x68012400, &sio->io_GPMCPM);

    memory_region_init_io(
        &sio->io_OCMRAMPM, obj, &synth_io_ops_OCMRAMPM, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_OCMRAMPM);
    memory_region_add_subregion(sysbus, 0x68012800, &sio->io_OCMRAMPM);

    memory_region_init_io(
        &sio->io_OCMROMPM, obj, &synth_io_ops_OCMROMPM, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_OCMROMPM);
    memory_region_add_subregion(sysbus, 0x68012c00, &sio->io_OCMROMPM);

    memory_region_init_io(
        &sio->io_D2DPM, obj, &synth_io_ops_D2DPM, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_D2DPM);
    memory_region_add_subregion(sysbus, 0x68013000, &sio->io_D2DPM);

    memory_region_init_io(
        &sio->io_Reserved5, obj, &synth_io_ops_Reserved5, sio, TYPE_SYNTH, 0xc00
    );
    sysbus_init_mmio(dev, &sio->io_Reserved5);
    memory_region_add_subregion(sysbus, 0x68013400, &sio->io_Reserved5);

    memory_region_init_io(
        &sio->io_IVA22PM, obj, &synth_io_ops_IVA22PM, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_IVA22PM);
    memory_region_add_subregion(sysbus, 0x68014000, &sio->io_IVA22PM);

    memory_region_init_io(
        &sio->io_Reserved6, obj, &synth_io_ops_Reserved6, sio, TYPE_SYNTH, 0xfebc00
    );
    sysbus_init_mmio(dev, &sio->io_Reserved6);
    memory_region_add_subregion(sysbus, 0x68014400, &sio->io_Reserved6);

    memory_region_init_io(
        &sio->io_SMS, obj, &synth_io_ops_SMS, sio, TYPE_SYNTH, 0x1000000
    );
    sysbus_init_mmio(dev, &sio->io_SMS);
    memory_region_add_subregion(sysbus, 0x6c000000, &sio->io_SMS);

    memory_region_init_io(
        &sio->io_SDRC, obj, &synth_io_ops_SDRC, sio, TYPE_SYNTH, 0x1000000
    );
    sysbus_init_mmio(dev, &sio->io_SDRC);
    memory_region_add_subregion(sysbus, 0x6d000000, &sio->io_SDRC);

    memory_region_init_io(
        &sio->io_GPMC, obj, &synth_io_ops_GPMC, sio, TYPE_SYNTH, 0x1000000
    );
    sysbus_init_mmio(dev, &sio->io_GPMC);
    memory_region_add_subregion(sysbus, 0x6e000000, &sio->io_GPMC);

    memory_region_init_io(
        &sio->io_L4ID_SCM, obj, &synth_io_ops_L4ID_SCM, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_SCM);
    memory_region_add_subregion(sysbus, 0x48002000, &sio->io_L4ID_SCM);

    memory_region_init_io(
        &sio->io_L4ID_SCM_TA, obj, &synth_io_ops_L4ID_SCM_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_SCM_TA);
    memory_region_add_subregion(sysbus, 0x48003000, &sio->io_L4ID_SCM_TA);

    memory_region_init_io(
        &sio->io_L4ID_CM_A, obj, &synth_io_ops_L4ID_CM_A, sio, TYPE_SYNTH, 0x2000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_CM_A);
    memory_region_add_subregion(sysbus, 0x48004000, &sio->io_L4ID_CM_A);

    memory_region_init_io(
        &sio->io_L4ID_CM_B, obj, &synth_io_ops_L4ID_CM_B, sio, TYPE_SYNTH, 0x800
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_CM_B);
    memory_region_add_subregion(sysbus, 0x48006000, &sio->io_L4ID_CM_B);

    memory_region_init_io(
        &sio->io_L4ID_CM_TA, obj, &synth_io_ops_L4ID_CM_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_CM_TA);
    memory_region_add_subregion(sysbus, 0x48007000, &sio->io_L4ID_CM_TA);

    memory_region_init_io(
        &sio->io_L4ID_CORE_AP, obj, &synth_io_ops_L4ID_CORE_AP, sio, TYPE_SYNTH, 0x800
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_CORE_AP);
    memory_region_add_subregion(sysbus, 0x48040000, &sio->io_L4ID_CORE_AP);

    memory_region_init_io(
        &sio->io_L4ID_CORE_IP, obj, &synth_io_ops_L4ID_CORE_IP, sio, TYPE_SYNTH, 0x800
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_CORE_IP);
    memory_region_add_subregion(sysbus, 0x48040800, &sio->io_L4ID_CORE_IP);

    memory_region_init_io(
        &sio->io_L4ID_CORE_LA, obj, &synth_io_ops_L4ID_CORE_LA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_CORE_LA);
    memory_region_add_subregion(sysbus, 0x48041000, &sio->io_L4ID_CORE_LA);

    memory_region_init_io(
        &sio->io_L4ID_DSI, obj, &synth_io_ops_L4ID_DSI, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_DSI);
    memory_region_add_subregion(sysbus, 0x4804fc00, &sio->io_L4ID_DSI);

    memory_region_init_io(
        &sio->io_L4ID_DSS, obj, &synth_io_ops_L4ID_DSS, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_DSS);
    memory_region_add_subregion(sysbus, 0x48050000, &sio->io_L4ID_DSS);

    memory_region_init_io(
        &sio->io_L4ID_DISPC, obj, &synth_io_ops_L4ID_DISPC, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_DISPC);
    memory_region_add_subregion(sysbus, 0x48050400, &sio->io_L4ID_DISPC);

    memory_region_init_io(
        &sio->io_L4ID_RFBI, obj, &synth_io_ops_L4ID_RFBI, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_RFBI);
    memory_region_add_subregion(sysbus, 0x48050800, &sio->io_L4ID_RFBI);

    memory_region_init_io(
        &sio->io_L4ID_VENC, obj, &synth_io_ops_L4ID_VENC, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_VENC);
    memory_region_add_subregion(sysbus, 0x48050c00, &sio->io_L4ID_VENC);

    memory_region_init_io(
        &sio->io_L4ID_DSS_TA, obj, &synth_io_ops_L4ID_DSS_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_DSS_TA);
    memory_region_add_subregion(sysbus, 0x48051000, &sio->io_L4ID_DSS_TA);

    memory_region_init_io(
        &sio->io_L4ID_SDMA, obj, &synth_io_ops_L4ID_SDMA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_SDMA);
    memory_region_add_subregion(sysbus, 0x48056000, &sio->io_L4ID_SDMA);

    memory_region_init_io(
        &sio->io_L4ID_SDMA_TA, obj, &synth_io_ops_L4ID_SDMA_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_SDMA_TA);
    memory_region_add_subregion(sysbus, 0x48057000, &sio->io_L4ID_SDMA_TA);

    memory_region_init_io(
        &sio->io_L4ID_I2C3, obj, &synth_io_ops_L4ID_I2C3, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_I2C3);
    memory_region_add_subregion(sysbus, 0x48060000, &sio->io_L4ID_I2C3);

    memory_region_init_io(
        &sio->io_L4ID_I2C3_TA, obj, &synth_io_ops_L4ID_I2C3_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_I2C3_TA);
    memory_region_add_subregion(sysbus, 0x48061000, &sio->io_L4ID_I2C3_TA);

    memory_region_init_io(
        &sio->io_4ID_USBTLL, obj, &synth_io_ops_4ID_USBTLL, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_4ID_USBTLL);
    memory_region_add_subregion(sysbus, 0x48062000, &sio->io_4ID_USBTLL);

    memory_region_init_io(
        &sio->io_L4ID_USBTLL_TA, obj, &synth_io_ops_L4ID_USBTLL_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_USBTLL_TA);
    memory_region_add_subregion(sysbus, 0x48063000, &sio->io_L4ID_USBTLL_TA);

    memory_region_init_io(
        &sio->io_4ID_USBHOST, obj, &synth_io_ops_4ID_USBHOST, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_4ID_USBHOST);
    memory_region_add_subregion(sysbus, 0x48064000, &sio->io_4ID_USBHOST);

    memory_region_init_io(
        &sio->io_L4ID_USBHOST_OHCI, obj, &synth_io_ops_L4ID_USBHOST_OHCI, sio, TYPE_SYNTH, 0x400
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_USBHOST_OHCI);
    memory_region_add_subregion(sysbus, 0x48064400, &sio->io_L4ID_USBHOST_OHCI);

    memory_region_init_io(
        &sio->io_4ID_USBHOST_EHCI, obj, &synth_io_ops_4ID_USBHOST_EHCI, sio, TYPE_SYNTH, 0x7800
    );
    sysbus_init_mmio(dev, &sio->io_4ID_USBHOST_EHCI);
    memory_region_add_subregion(sysbus, 0x48064800, &sio->io_4ID_USBHOST_EHCI);

    memory_region_init_io(
        &sio->io_L4ID_USBHOST_TA, obj, &synth_io_ops_L4ID_USBHOST_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_USBHOST_TA);
    memory_region_add_subregion(sysbus, 0x48065000, &sio->io_L4ID_USBHOST_TA);

    memory_region_init_io(
        &sio->io_L4ID_UART1, obj, &synth_io_ops_L4ID_UART1, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_UART1);
    memory_region_add_subregion(sysbus, 0x4806a000, &sio->io_L4ID_UART1);

    memory_region_init_io(
        &sio->io_L4ID_UART1_TA, obj, &synth_io_ops_L4ID_UART1_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_UART1_TA);
    memory_region_add_subregion(sysbus, 0x4806b000, &sio->io_L4ID_UART1_TA);

    memory_region_init_io(
        &sio->io_4ID_UART2, obj, &synth_io_ops_4ID_UART2, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_4ID_UART2);
    memory_region_add_subregion(sysbus, 0x4806c000, &sio->io_4ID_UART2);

    memory_region_init_io(
        &sio->io_L4ID_UART2_TA, obj, &synth_io_ops_L4ID_UART2_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_UART2_TA);
    memory_region_add_subregion(sysbus, 0x4806d000, &sio->io_L4ID_UART2_TA);

    memory_region_init_io(
        &sio->io_L4ID_I2C1, obj, &synth_io_ops_L4ID_I2C1, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_I2C1);
    memory_region_add_subregion(sysbus, 0x48070000, &sio->io_L4ID_I2C1);

    memory_region_init_io(
        &sio->io_L4ID_I2C1_TA, obj, &synth_io_ops_L4ID_I2C1_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_I2C1_TA);
    memory_region_add_subregion(sysbus, 0x48071000, &sio->io_L4ID_I2C1_TA);

    memory_region_init_io(
        &sio->io_L4ID_I2C2, obj, &synth_io_ops_L4ID_I2C2, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_I2C2);
    memory_region_add_subregion(sysbus, 0x48072000, &sio->io_L4ID_I2C2);

    memory_region_init_io(
        &sio->io_L4ID_I2C2_TA, obj, &synth_io_ops_L4ID_I2C2_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_I2C2_TA);
    memory_region_add_subregion(sysbus, 0x48073000, &sio->io_L4ID_I2C2_TA);

    memory_region_init_io(
        &sio->io_L4ID_MCBSP1, obj, &synth_io_ops_L4ID_MCBSP1, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCBSP1);
    memory_region_add_subregion(sysbus, 0x48074000, &sio->io_L4ID_MCBSP1);

    memory_region_init_io(
        &sio->io_L4ID_MCBSP1_TA, obj, &synth_io_ops_L4ID_MCBSP1_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCBSP1_TA);
    memory_region_add_subregion(sysbus, 0x48075000, &sio->io_L4ID_MCBSP1_TA);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER10, obj, &synth_io_ops_L4ID_GPTIMER10, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER10);
    memory_region_add_subregion(sysbus, 0x48086000, &sio->io_L4ID_GPTIMER10);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER10_TA, obj, &synth_io_ops_L4ID_GPTIMER10_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER10_TA);
    memory_region_add_subregion(sysbus, 0x48087000, &sio->io_L4ID_GPTIMER10_TA);

    memory_region_init_io(
        &sio->io_4ID_GPTIMER11, obj, &synth_io_ops_4ID_GPTIMER11, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_4ID_GPTIMER11);
    memory_region_add_subregion(sysbus, 0x48088000, &sio->io_4ID_GPTIMER11);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER11_TA, obj, &synth_io_ops_L4ID_GPTIMER11_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER11_TA);
    memory_region_add_subregion(sysbus, 0x48089000, &sio->io_L4ID_GPTIMER11_TA);

    memory_region_init_io(
        &sio->io_L4ID_MAILBOX, obj, &synth_io_ops_L4ID_MAILBOX, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MAILBOX);
    memory_region_add_subregion(sysbus, 0x48094000, &sio->io_L4ID_MAILBOX);

    memory_region_init_io(
        &sio->io_L4ID_MAILBOX_TA, obj, &synth_io_ops_L4ID_MAILBOX_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MAILBOX_TA);
    memory_region_add_subregion(sysbus, 0x48095000, &sio->io_L4ID_MAILBOX_TA);

    memory_region_init_io(
        &sio->io_L4ID_MCBSP5, obj, &synth_io_ops_L4ID_MCBSP5, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCBSP5);
    memory_region_add_subregion(sysbus, 0x48096000, &sio->io_L4ID_MCBSP5);

    memory_region_init_io(
        &sio->io_L4ID_MCBSP5_TA, obj, &synth_io_ops_L4ID_MCBSP5_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCBSP5_TA);
    memory_region_add_subregion(sysbus, 0x48097000, &sio->io_L4ID_MCBSP5_TA);

    memory_region_init_io(
        &sio->io_L4ID_MCSPI1, obj, &synth_io_ops_L4ID_MCSPI1, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCSPI1);
    memory_region_add_subregion(sysbus, 0x48098000, &sio->io_L4ID_MCSPI1);

    memory_region_init_io(
        &sio->io_L4ID_MCSPI1_TA, obj, &synth_io_ops_L4ID_MCSPI1_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCSPI1_TA);
    memory_region_add_subregion(sysbus, 0x48099000, &sio->io_L4ID_MCSPI1_TA);

    memory_region_init_io(
        &sio->io_L4ID_MCSPI2, obj, &synth_io_ops_L4ID_MCSPI2, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCSPI2);
    memory_region_add_subregion(sysbus, 0x4809a000, &sio->io_L4ID_MCSPI2);

    memory_region_init_io(
        &sio->io_L4ID_MCSPI2_TA, obj, &synth_io_ops_L4ID_MCSPI2_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCSPI2_TA);
    memory_region_add_subregion(sysbus, 0x4809b000, &sio->io_L4ID_MCSPI2_TA);

    memory_region_init_io(
        &sio->io_L4ID_MMCSDIO1, obj, &synth_io_ops_L4ID_MMCSDIO1, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MMCSDIO1);
    memory_region_add_subregion(sysbus, 0x4809c000, &sio->io_L4ID_MMCSDIO1);

    memory_region_init_io(
        &sio->io_L4ID_MMCSDIO1_TA, obj, &synth_io_ops_L4ID_MMCSDIO1_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MMCSDIO1_TA);
    memory_region_add_subregion(sysbus, 0x4809d000, &sio->io_L4ID_MMCSDIO1_TA);

    memory_region_init_io(
        &sio->io_L4ID_MSPRO, obj, &synth_io_ops_L4ID_MSPRO, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MSPRO);
    memory_region_add_subregion(sysbus, 0x4809e000, &sio->io_L4ID_MSPRO);

    memory_region_init_io(
        &sio->io_L4ID_MSPRO_TA, obj, &synth_io_ops_L4ID_MSPRO_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MSPRO_TA);
    memory_region_add_subregion(sysbus, 0x4809f000, &sio->io_L4ID_MSPRO_TA);

    memory_region_init_io(
        &sio->io_L4ID_HSUSBOTG, obj, &synth_io_ops_L4ID_HSUSBOTG, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_HSUSBOTG);
    memory_region_add_subregion(sysbus, 0x480ab000, &sio->io_L4ID_HSUSBOTG);

    memory_region_init_io(
        &sio->io_L4ID_HSUSBOTG_TA, obj, &synth_io_ops_L4ID_HSUSBOTG_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_HSUSBOTG_TA);
    memory_region_add_subregion(sysbus, 0x480ac000, &sio->io_L4ID_HSUSBOTG_TA);

    memory_region_init_io(
        &sio->io_L4ID_MMCSDIO3, obj, &synth_io_ops_L4ID_MMCSDIO3, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MMCSDIO3);
    memory_region_add_subregion(sysbus, 0x480ad000, &sio->io_L4ID_MMCSDIO3);

    memory_region_init_io(
        &sio->io_L4ID_MMCSDIO3_TA, obj, &synth_io_ops_L4ID_MMCSDIO3_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MMCSDIO3_TA);
    memory_region_add_subregion(sysbus, 0x480ae000, &sio->io_L4ID_MMCSDIO3_TA);

    memory_region_init_io(
        &sio->io_L4ID_HDQ1WIRE, obj, &synth_io_ops_L4ID_HDQ1WIRE, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_HDQ1WIRE);
    memory_region_add_subregion(sysbus, 0x480b2000, &sio->io_L4ID_HDQ1WIRE);

    memory_region_init_io(
        &sio->io_L4ID_HDQ1WIRE_TA, obj, &synth_io_ops_L4ID_HDQ1WIRE_TA, sio, TYPE_SYNTH, 0x0
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_HDQ1WIRE_TA);
    memory_region_add_subregion(sysbus, 0x480b3000, &sio->io_L4ID_HDQ1WIRE_TA);

    memory_region_init_io(
        &sio->io_L4ID_MMCSDIO2, obj, &synth_io_ops_L4ID_MMCSDIO2, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MMCSDIO2);
    memory_region_add_subregion(sysbus, 0x480b4000, &sio->io_L4ID_MMCSDIO2);

    memory_region_init_io(
        &sio->io_L4ID_MMCSDIO2_TA, obj, &synth_io_ops_L4ID_MMCSDIO2_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MMCSDIO2_TA);
    memory_region_add_subregion(sysbus, 0x480b5000, &sio->io_L4ID_MMCSDIO2_TA);

    memory_region_init_io(
        &sio->io_L4ID_ICRMPU, obj, &synth_io_ops_L4ID_ICRMPU, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_ICRMPU);
    memory_region_add_subregion(sysbus, 0x480b6000, &sio->io_L4ID_ICRMPU);

    memory_region_init_io(
        &sio->io_L4ID_ICRMPU_TA, obj, &synth_io_ops_L4ID_ICRMPU_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_ICRMPU_TA);
    memory_region_add_subregion(sysbus, 0x480b7000, &sio->io_L4ID_ICRMPU_TA);

    memory_region_init_io(
        &sio->io_L4ID_MCSPI3, obj, &synth_io_ops_L4ID_MCSPI3, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCSPI3);
    memory_region_add_subregion(sysbus, 0x480b8000, &sio->io_L4ID_MCSPI3);

    memory_region_init_io(
        &sio->io_L4ID_MCSPI3_TA, obj, &synth_io_ops_L4ID_MCSPI3_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCSPI3_TA);
    memory_region_add_subregion(sysbus, 0x480b9000, &sio->io_L4ID_MCSPI3_TA);

    memory_region_init_io(
        &sio->io_L4ID_MCSPI4, obj, &synth_io_ops_L4ID_MCSPI4, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCSPI4);
    memory_region_add_subregion(sysbus, 0x480ba000, &sio->io_L4ID_MCSPI4);

    memory_region_init_io(
        &sio->io_L4ID_MCSPI4_TA, obj, &synth_io_ops_L4ID_MCSPI4_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCSPI4_TA);
    memory_region_add_subregion(sysbus, 0x480bb000, &sio->io_L4ID_MCSPI4_TA);

    memory_region_init_io(
        &sio->io_L4ID_CAMERAISP, obj, &synth_io_ops_L4ID_CAMERAISP, sio, TYPE_SYNTH, 0x4000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_CAMERAISP);
    memory_region_add_subregion(sysbus, 0x480bc000, &sio->io_L4ID_CAMERAISP);

    memory_region_init_io(
        &sio->io_L4ID_CAMERAISP_TA, obj, &synth_io_ops_L4ID_CAMERAISP_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_CAMERAISP_TA);
    memory_region_add_subregion(sysbus, 0x480c0000, &sio->io_L4ID_CAMERAISP_TA);

    memory_region_init_io(
        &sio->io_L4ID_SR1, obj, &synth_io_ops_L4ID_SR1, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_SR1);
    memory_region_add_subregion(sysbus, 0x480c9000, &sio->io_L4ID_SR1);

    memory_region_init_io(
        &sio->io_L4ID_SR1_TA, obj, &synth_io_ops_L4ID_SR1_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_SR1_TA);
    memory_region_add_subregion(sysbus, 0x480ca000, &sio->io_L4ID_SR1_TA);

    memory_region_init_io(
        &sio->io_L4ID_SR2, obj, &synth_io_ops_L4ID_SR2, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_SR2);
    memory_region_add_subregion(sysbus, 0x480cb000, &sio->io_L4ID_SR2);

    memory_region_init_io(
        &sio->io_L4ID_SR2_TA, obj, &synth_io_ops_L4ID_SR2_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_SR2_TA);
    memory_region_add_subregion(sysbus, 0x480cc000, &sio->io_L4ID_SR2_TA);

    memory_region_init_io(
        &sio->io_L4ID_ICRMODEM, obj, &synth_io_ops_L4ID_ICRMODEM, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_ICRMODEM);
    memory_region_add_subregion(sysbus, 0x480cd000, &sio->io_L4ID_ICRMODEM);

    memory_region_init_io(
        &sio->io_L4ID_ICRMODEM_TA, obj, &synth_io_ops_L4ID_ICRMODEM_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_ICRMODEM_TA);
    memory_region_add_subregion(sysbus, 0x480ce000, &sio->io_L4ID_ICRMODEM_TA);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER12, obj, &synth_io_ops_L4ID_GPTIMER12, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER12);
    memory_region_add_subregion(sysbus, 0x48304000, &sio->io_L4ID_GPTIMER12);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER12_TA, obj, &synth_io_ops_L4ID_GPTIMER12_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER12_TA);
    memory_region_add_subregion(sysbus, 0x48305000, &sio->io_L4ID_GPTIMER12_TA);

    memory_region_init_io(
        &sio->io_L4ID_PRM_A, obj, &synth_io_ops_L4ID_PRM_A, sio, TYPE_SYNTH, 0x2000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_PRM_A);
    memory_region_add_subregion(sysbus, 0x48306000, &sio->io_L4ID_PRM_A);

    memory_region_init_io(
        &sio->io_L4ID_PRM_TA, obj, &synth_io_ops_L4ID_PRM_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_PRM_TA);
    memory_region_add_subregion(sysbus, 0x48309000, &sio->io_L4ID_PRM_TA);

    memory_region_init_io(
        &sio->io_L4ID_TAP, obj, &synth_io_ops_L4ID_TAP, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_TAP);
    memory_region_add_subregion(sysbus, 0x4830a000, &sio->io_L4ID_TAP);

    memory_region_init_io(
        &sio->io_L4ID_TAP_TA, obj, &synth_io_ops_L4ID_TAP_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_TAP_TA);
    memory_region_add_subregion(sysbus, 0x4830b000, &sio->io_L4ID_TAP_TA);

    memory_region_init_io(
        &sio->io_L4ID_GPIO1, obj, &synth_io_ops_L4ID_GPIO1, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPIO1);
    memory_region_add_subregion(sysbus, 0x48310000, &sio->io_L4ID_GPIO1);

    memory_region_init_io(
        &sio->io_L4ID_GPIO1_TA, obj, &synth_io_ops_L4ID_GPIO1_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPIO1_TA);
    memory_region_add_subregion(sysbus, 0x48311000, &sio->io_L4ID_GPIO1_TA);

    memory_region_init_io(
        &sio->io_L4ID_WDTIMER2, obj, &synth_io_ops_L4ID_WDTIMER2, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_WDTIMER2);
    memory_region_add_subregion(sysbus, 0x48314000, &sio->io_L4ID_WDTIMER2);

    memory_region_init_io(
        &sio->io_L4ID_WDTIMER2_TA, obj, &synth_io_ops_L4ID_WDTIMER2_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_WDTIMER2_TA);
    memory_region_add_subregion(sysbus, 0x48315000, &sio->io_L4ID_WDTIMER2_TA);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER1, obj, &synth_io_ops_L4ID_GPTIMER1, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER1);
    memory_region_add_subregion(sysbus, 0x48318000, &sio->io_L4ID_GPTIMER1);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER1_TA, obj, &synth_io_ops_L4ID_GPTIMER1_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER1_TA);
    memory_region_add_subregion(sysbus, 0x48319000, &sio->io_L4ID_GPTIMER1_TA);

    memory_region_init_io(
        &sio->io_L4ID_32KTIMER, obj, &synth_io_ops_L4ID_32KTIMER, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_32KTIMER);
    memory_region_add_subregion(sysbus, 0x48320000, &sio->io_L4ID_32KTIMER);

    memory_region_init_io(
        &sio->io_L4ID_32KTIMER_TA, obj, &synth_io_ops_L4ID_32KTIMER_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_32KTIMER_TA);
    memory_region_add_subregion(sysbus, 0x48321000, &sio->io_L4ID_32KTIMER_TA);

    memory_region_init_io(
        &sio->io_L4ID_WAKEUP_AP, obj, &synth_io_ops_L4ID_WAKEUP_AP, sio, TYPE_SYNTH, 0x800
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_WAKEUP_AP);
    memory_region_add_subregion(sysbus, 0x48328000, &sio->io_L4ID_WAKEUP_AP);

    memory_region_init_io(
        &sio->io_L4ID_WAKEUP_C_IP, obj, &synth_io_ops_L4ID_WAKEUP_C_IP, sio, TYPE_SYNTH, 0x800
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_WAKEUP_C_IP);
    memory_region_add_subregion(sysbus, 0x48328800, &sio->io_L4ID_WAKEUP_C_IP);

    memory_region_init_io(
        &sio->io_L4ID_WAKEUP_LA, obj, &synth_io_ops_L4ID_WAKEUP_LA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_WAKEUP_LA);
    memory_region_add_subregion(sysbus, 0x48329000, &sio->io_L4ID_WAKEUP_LA);

    memory_region_init_io(
        &sio->io_L4ID_WAKEUP_E_IP, obj, &synth_io_ops_L4ID_WAKEUP_E_IP, sio, TYPE_SYNTH, 0x800
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_WAKEUP_E_IP);
    memory_region_add_subregion(sysbus, 0x4832a000, &sio->io_L4ID_WAKEUP_E_IP);

    memory_region_init_io(
        &sio->io_L4ID_PER_AP, obj, &synth_io_ops_L4ID_PER_AP, sio, TYPE_SYNTH, 0x800
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_PER_AP);
    memory_region_add_subregion(sysbus, 0x49000000, &sio->io_L4ID_PER_AP);

    memory_region_init_io(
        &sio->io_L4ID_PER_IP, obj, &synth_io_ops_L4ID_PER_IP, sio, TYPE_SYNTH, 0x800
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_PER_IP);
    memory_region_add_subregion(sysbus, 0x49000800, &sio->io_L4ID_PER_IP);

    memory_region_init_io(
        &sio->io_L4ID_PER_LA, obj, &synth_io_ops_L4ID_PER_LA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_PER_LA);
    memory_region_add_subregion(sysbus, 0x49001000, &sio->io_L4ID_PER_LA);

    memory_region_init_io(
        &sio->io_L4ID_UART3, obj, &synth_io_ops_L4ID_UART3, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_UART3);
    memory_region_add_subregion(sysbus, 0x49020000, &sio->io_L4ID_UART3);

    memory_region_init_io(
        &sio->io_L4ID_UART3_TA, obj, &synth_io_ops_L4ID_UART3_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_UART3_TA);
    memory_region_add_subregion(sysbus, 0x49021000, &sio->io_L4ID_UART3_TA);

    memory_region_init_io(
        &sio->io_L4ID_MCBSP2, obj, &synth_io_ops_L4ID_MCBSP2, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCBSP2);
    memory_region_add_subregion(sysbus, 0x49022000, &sio->io_L4ID_MCBSP2);

    memory_region_init_io(
        &sio->io_L4ID_MCBSP2_TA, obj, &synth_io_ops_L4ID_MCBSP2_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCBSP2_TA);
    memory_region_add_subregion(sysbus, 0x49023000, &sio->io_L4ID_MCBSP2_TA);

    memory_region_init_io(
        &sio->io_L4ID_MCBSP3, obj, &synth_io_ops_L4ID_MCBSP3, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCBSP3);
    memory_region_add_subregion(sysbus, 0x49024000, &sio->io_L4ID_MCBSP3);

    memory_region_init_io(
        &sio->io_L4ID_MCBSP3_TA, obj, &synth_io_ops_L4ID_MCBSP3_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCBSP3_TA);
    memory_region_add_subregion(sysbus, 0x49025000, &sio->io_L4ID_MCBSP3_TA);

    memory_region_init_io(
        &sio->io_L4ID_MCBSP4, obj, &synth_io_ops_L4ID_MCBSP4, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCBSP4);
    memory_region_add_subregion(sysbus, 0x49026000, &sio->io_L4ID_MCBSP4);

    memory_region_init_io(
        &sio->io_L4ID_MCBSP4_TA, obj, &synth_io_ops_L4ID_MCBSP4_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCBSP4_TA);
    memory_region_add_subregion(sysbus, 0x49027000, &sio->io_L4ID_MCBSP4_TA);

    memory_region_init_io(
        &sio->io_L4ID_MCBSP2S, obj, &synth_io_ops_L4ID_MCBSP2S, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCBSP2S);
    memory_region_add_subregion(sysbus, 0x49028000, &sio->io_L4ID_MCBSP2S);

    memory_region_init_io(
        &sio->io_L4ID_MCBSP2S_TA, obj, &synth_io_ops_L4ID_MCBSP2S_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCBSP2S_TA);
    memory_region_add_subregion(sysbus, 0x49029000, &sio->io_L4ID_MCBSP2S_TA);

    memory_region_init_io(
        &sio->io_L4ID_MCBSP3S, obj, &synth_io_ops_L4ID_MCBSP3S, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCBSP3S);
    memory_region_add_subregion(sysbus, 0x4902a000, &sio->io_L4ID_MCBSP3S);

    memory_region_init_io(
        &sio->io_L4ID_MCBSP3S_TA, obj, &synth_io_ops_L4ID_MCBSP3S_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MCBSP3S_TA);
    memory_region_add_subregion(sysbus, 0x4902b000, &sio->io_L4ID_MCBSP3S_TA);

    memory_region_init_io(
        &sio->io_L4ID_WDTIMER3, obj, &synth_io_ops_L4ID_WDTIMER3, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_WDTIMER3);
    memory_region_add_subregion(sysbus, 0x49030000, &sio->io_L4ID_WDTIMER3);

    memory_region_init_io(
        &sio->io_L4ID_WDTIMER3_TA, obj, &synth_io_ops_L4ID_WDTIMER3_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_WDTIMER3_TA);
    memory_region_add_subregion(sysbus, 0x49031000, &sio->io_L4ID_WDTIMER3_TA);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER2, obj, &synth_io_ops_L4ID_GPTIMER2, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER2);
    memory_region_add_subregion(sysbus, 0x49032000, &sio->io_L4ID_GPTIMER2);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER2_TA, obj, &synth_io_ops_L4ID_GPTIMER2_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER2_TA);
    memory_region_add_subregion(sysbus, 0x49033000, &sio->io_L4ID_GPTIMER2_TA);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER3, obj, &synth_io_ops_L4ID_GPTIMER3, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER3);
    memory_region_add_subregion(sysbus, 0x49034000, &sio->io_L4ID_GPTIMER3);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER3_TA, obj, &synth_io_ops_L4ID_GPTIMER3_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER3_TA);
    memory_region_add_subregion(sysbus, 0x49035000, &sio->io_L4ID_GPTIMER3_TA);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER4, obj, &synth_io_ops_L4ID_GPTIMER4, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER4);
    memory_region_add_subregion(sysbus, 0x49036000, &sio->io_L4ID_GPTIMER4);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER4_TA, obj, &synth_io_ops_L4ID_GPTIMER4_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER4_TA);
    memory_region_add_subregion(sysbus, 0x49037000, &sio->io_L4ID_GPTIMER4_TA);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER5, obj, &synth_io_ops_L4ID_GPTIMER5, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER5);
    memory_region_add_subregion(sysbus, 0x49038000, &sio->io_L4ID_GPTIMER5);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER5_TA, obj, &synth_io_ops_L4ID_GPTIMER5_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER5_TA);
    memory_region_add_subregion(sysbus, 0x49039000, &sio->io_L4ID_GPTIMER5_TA);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER6, obj, &synth_io_ops_L4ID_GPTIMER6, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER6);
    memory_region_add_subregion(sysbus, 0x4903a000, &sio->io_L4ID_GPTIMER6);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER6_TA, obj, &synth_io_ops_L4ID_GPTIMER6_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER6_TA);
    memory_region_add_subregion(sysbus, 0x4903b000, &sio->io_L4ID_GPTIMER6_TA);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER7, obj, &synth_io_ops_L4ID_GPTIMER7, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER7);
    memory_region_add_subregion(sysbus, 0x4903c000, &sio->io_L4ID_GPTIMER7);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER7_TA, obj, &synth_io_ops_L4ID_GPTIMER7_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER7_TA);
    memory_region_add_subregion(sysbus, 0x4903d000, &sio->io_L4ID_GPTIMER7_TA);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER8, obj, &synth_io_ops_L4ID_GPTIMER8, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER8);
    memory_region_add_subregion(sysbus, 0x4903e000, &sio->io_L4ID_GPTIMER8);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER8_TA, obj, &synth_io_ops_L4ID_GPTIMER8_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER8_TA);
    memory_region_add_subregion(sysbus, 0x4903f000, &sio->io_L4ID_GPTIMER8_TA);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER9, obj, &synth_io_ops_L4ID_GPTIMER9, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER9);
    memory_region_add_subregion(sysbus, 0x49040000, &sio->io_L4ID_GPTIMER9);

    memory_region_init_io(
        &sio->io_L4ID_GPTIMER9_TA, obj, &synth_io_ops_L4ID_GPTIMER9_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPTIMER9_TA);
    memory_region_add_subregion(sysbus, 0x49041000, &sio->io_L4ID_GPTIMER9_TA);

    memory_region_init_io(
        &sio->io_L4ID_UART4, obj, &synth_io_ops_L4ID_UART4, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_UART4);
    memory_region_add_subregion(sysbus, 0x49042000, &sio->io_L4ID_UART4);

    memory_region_init_io(
        &sio->io_L4ID_UART4_TA, obj, &synth_io_ops_L4ID_UART4_TA, sio, TYPE_SYNTH, 0xd000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_UART4_TA);
    memory_region_add_subregion(sysbus, 0x49043000, &sio->io_L4ID_UART4_TA);

    memory_region_init_io(
        &sio->io_L4ID_GPIO2, obj, &synth_io_ops_L4ID_GPIO2, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPIO2);
    memory_region_add_subregion(sysbus, 0x49050000, &sio->io_L4ID_GPIO2);

    memory_region_init_io(
        &sio->io_L4ID_GPIO2_TA, obj, &synth_io_ops_L4ID_GPIO2_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPIO2_TA);
    memory_region_add_subregion(sysbus, 0x49051000, &sio->io_L4ID_GPIO2_TA);

    memory_region_init_io(
        &sio->io_L4ID_GPIO3, obj, &synth_io_ops_L4ID_GPIO3, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPIO3);
    memory_region_add_subregion(sysbus, 0x49052000, &sio->io_L4ID_GPIO3);

    memory_region_init_io(
        &sio->io_L4ID_GPIO3_TA, obj, &synth_io_ops_L4ID_GPIO3_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPIO3_TA);
    memory_region_add_subregion(sysbus, 0x49053000, &sio->io_L4ID_GPIO3_TA);

    memory_region_init_io(
        &sio->io_L4ID_GPIO4, obj, &synth_io_ops_L4ID_GPIO4, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPIO4);
    memory_region_add_subregion(sysbus, 0x49054000, &sio->io_L4ID_GPIO4);

    memory_region_init_io(
        &sio->io_L4ID_GPIO4_TA, obj, &synth_io_ops_L4ID_GPIO4_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPIO4_TA);
    memory_region_add_subregion(sysbus, 0x49055000, &sio->io_L4ID_GPIO4_TA);

    memory_region_init_io(
        &sio->io_L4ID_GPIO5, obj, &synth_io_ops_L4ID_GPIO5, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPIO5);
    memory_region_add_subregion(sysbus, 0x49056000, &sio->io_L4ID_GPIO5);

    memory_region_init_io(
        &sio->io_L4ID_GPIO5_TA, obj, &synth_io_ops_L4ID_GPIO5_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPIO5_TA);
    memory_region_add_subregion(sysbus, 0x49057000, &sio->io_L4ID_GPIO5_TA);

    memory_region_init_io(
        &sio->io_L4ID_GPIO6, obj, &synth_io_ops_L4ID_GPIO6, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPIO6);
    memory_region_add_subregion(sysbus, 0x49058000, &sio->io_L4ID_GPIO6);

    memory_region_init_io(
        &sio->io_L4ID_GPIO6_TA, obj, &synth_io_ops_L4ID_GPIO6_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_GPIO6_TA);
    memory_region_add_subregion(sysbus, 0x49059000, &sio->io_L4ID_GPIO6_TA);

    memory_region_init_io(
        &sio->io_L4ID_EMU_AP, obj, &synth_io_ops_L4ID_EMU_AP, sio, TYPE_SYNTH, 0x800
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_AP);
    memory_region_add_subregion(sysbus, 0x54006000, &sio->io_L4ID_EMU_AP);

    memory_region_init_io(
        &sio->io_L4ID_EMU_IP_C, obj, &synth_io_ops_L4ID_EMU_IP_C, sio, TYPE_SYNTH, 0x800
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_IP_C);
    memory_region_add_subregion(sysbus, 0x54006800, &sio->io_L4ID_EMU_IP_C);

    memory_region_init_io(
        &sio->io_L4ID_EMU_LA, obj, &synth_io_ops_L4ID_EMU_LA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_LA);
    memory_region_add_subregion(sysbus, 0x54007000, &sio->io_L4ID_EMU_LA);

    memory_region_init_io(
        &sio->io_L4ID_EMU_IP_DAP, obj, &synth_io_ops_L4ID_EMU_IP_DAP, sio, TYPE_SYNTH, 0x800
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_IP_DAP);
    memory_region_add_subregion(sysbus, 0x54008000, &sio->io_L4ID_EMU_IP_DAP);

    memory_region_init_io(
        &sio->io_L4ID_MPUEMU, obj, &synth_io_ops_L4ID_MPUEMU, sio, TYPE_SYNTH, 0x8000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MPUEMU);
    memory_region_add_subregion(sysbus, 0x54010000, &sio->io_L4ID_MPUEMU);

    memory_region_init_io(
        &sio->io_L4ID_MPUEMU_TA, obj, &synth_io_ops_L4ID_MPUEMU_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_MPUEMU_TA);
    memory_region_add_subregion(sysbus, 0x54018000, &sio->io_L4ID_MPUEMU_TA);

    memory_region_init_io(
        &sio->io_L4ID_TPIU, obj, &synth_io_ops_L4ID_TPIU, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_TPIU);
    memory_region_add_subregion(sysbus, 0x54019000, &sio->io_L4ID_TPIU);

    memory_region_init_io(
        &sio->io_L4ID_TPIU_TA, obj, &synth_io_ops_L4ID_TPIU_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_TPIU_TA);
    memory_region_add_subregion(sysbus, 0x5401a000, &sio->io_L4ID_TPIU_TA);

    memory_region_init_io(
        &sio->io_L4ID_ETB, obj, &synth_io_ops_L4ID_ETB, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_ETB);
    memory_region_add_subregion(sysbus, 0x5401b000, &sio->io_L4ID_ETB);

    memory_region_init_io(
        &sio->io_L4ID_ETB_TA, obj, &synth_io_ops_L4ID_ETB_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_ETB_TA);
    memory_region_add_subregion(sysbus, 0x5401c000, &sio->io_L4ID_ETB_TA);

    memory_region_init_io(
        &sio->io_L4ID_DAPCTL, obj, &synth_io_ops_L4ID_DAPCTL, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_DAPCTL);
    memory_region_add_subregion(sysbus, 0x5401d000, &sio->io_L4ID_DAPCTL);

    memory_region_init_io(
        &sio->io_L4ID_DAPCTL_TA, obj, &synth_io_ops_L4ID_DAPCTL_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_DAPCTL_TA);
    memory_region_add_subregion(sysbus, 0x5401e000, &sio->io_L4ID_DAPCTL_TA);

    memory_region_init_io(
        &sio->io_L4ID_SDTI_TA, obj, &synth_io_ops_L4ID_SDTI_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_SDTI_TA);
    memory_region_add_subregion(sysbus, 0x5401f000, &sio->io_L4ID_SDTI_TA);

    memory_region_init_io(
        &sio->io_L4ID_SDTI_CFG, obj, &synth_io_ops_L4ID_SDTI_CFG, sio, TYPE_SYNTH, 0x10000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_SDTI_CFG);
    memory_region_add_subregion(sysbus, 0x54500000, &sio->io_L4ID_SDTI_CFG);

    memory_region_init_io(
        &sio->io_L4ID_SDTI, obj, &synth_io_ops_L4ID_SDTI, sio, TYPE_SYNTH, 0x100000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_SDTI);
    memory_region_add_subregion(sysbus, 0x54600000, &sio->io_L4ID_SDTI);

    memory_region_init_io(
        &sio->io_L4ID_EMU_PRM_A, obj, &synth_io_ops_L4ID_EMU_PRM_A, sio, TYPE_SYNTH, 0x2000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_PRM_A);
    memory_region_add_subregion(sysbus, 0x54706000, &sio->io_L4ID_EMU_PRM_A);

    memory_region_init_io(
        &sio->io_L4ID_EMU_PRM_B, obj, &synth_io_ops_L4ID_EMU_PRM_B, sio, TYPE_SYNTH, 0x800
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_PRM_B);
    memory_region_add_subregion(sysbus, 0x54708000, &sio->io_L4ID_EMU_PRM_B);

    memory_region_init_io(
        &sio->io_L4ID_EMU_PRM_TA, obj, &synth_io_ops_L4ID_EMU_PRM_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_PRM_TA);
    memory_region_add_subregion(sysbus, 0x54709000, &sio->io_L4ID_EMU_PRM_TA);

    memory_region_init_io(
        &sio->io_L4ID_EMU_GPIO1, obj, &synth_io_ops_L4ID_EMU_GPIO1, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_GPIO1);
    memory_region_add_subregion(sysbus, 0x54710000, &sio->io_L4ID_EMU_GPIO1);

    memory_region_init_io(
        &sio->io_L4ID_EMU_GPIO1_TA, obj, &synth_io_ops_L4ID_EMU_GPIO1_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_GPIO1_TA);
    memory_region_add_subregion(sysbus, 0x54711000, &sio->io_L4ID_EMU_GPIO1_TA);

    memory_region_init_io(
        &sio->io_L4ID_EMU_WDTM2, obj, &synth_io_ops_L4ID_EMU_WDTM2, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_WDTM2);
    memory_region_add_subregion(sysbus, 0x54714000, &sio->io_L4ID_EMU_WDTM2);

    memory_region_init_io(
        &sio->io_L4ID_EMU_WDTM2_TA, obj, &synth_io_ops_L4ID_EMU_WDTM2_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_WDTM2_TA);
    memory_region_add_subregion(sysbus, 0x54715000, &sio->io_L4ID_EMU_WDTM2_TA);

    memory_region_init_io(
        &sio->io_L4ID_EMU_GPTM1, obj, &synth_io_ops_L4ID_EMU_GPTM1, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_GPTM1);
    memory_region_add_subregion(sysbus, 0x54718000, &sio->io_L4ID_EMU_GPTM1);

    memory_region_init_io(
        &sio->io_L4ID_EMU_GPTM1_TA, obj, &synth_io_ops_L4ID_EMU_GPTM1_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_GPTM1_TA);
    memory_region_add_subregion(sysbus, 0x54719000, &sio->io_L4ID_EMU_GPTM1_TA);

    memory_region_init_io(
        &sio->io_L4ID_EMU_32KTM, obj, &synth_io_ops_L4ID_EMU_32KTM, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_32KTM);
    memory_region_add_subregion(sysbus, 0x54720000, &sio->io_L4ID_EMU_32KTM);

    memory_region_init_io(
        &sio->io_L4ID_EMU_32KTM_TA, obj, &synth_io_ops_L4ID_EMU_32KTM_TA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_32KTM_TA);
    memory_region_add_subregion(sysbus, 0x54721000, &sio->io_L4ID_EMU_32KTM_TA);

    memory_region_init_io(
        &sio->io_L4ID_EMU_WKUP_AP, obj, &synth_io_ops_L4ID_EMU_WKUP_AP, sio, TYPE_SYNTH, 0x800
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_WKUP_AP);
    memory_region_add_subregion(sysbus, 0x54728000, &sio->io_L4ID_EMU_WKUP_AP);

    memory_region_init_io(
        &sio->io_L4ID_EMU_WKUP_IPC, obj, &synth_io_ops_L4ID_EMU_WKUP_IPC, sio, TYPE_SYNTH, 0x800
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_WKUP_IPC);
    memory_region_add_subregion(sysbus, 0x54728800, &sio->io_L4ID_EMU_WKUP_IPC);

    memory_region_init_io(
        &sio->io_L4ID_EMU_WKUP_LA, obj, &synth_io_ops_L4ID_EMU_WKUP_LA, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_WKUP_LA);
    memory_region_add_subregion(sysbus, 0x54729000, &sio->io_L4ID_EMU_WKUP_LA);

    memory_region_init_io(
        &sio->io_L4ID_EMU_WKUP_IPE, obj, &synth_io_ops_L4ID_EMU_WKUP_IPE, sio, TYPE_SYNTH, 0x800
    );
    sysbus_init_mmio(dev, &sio->io_L4ID_EMU_WKUP_IPE);
    memory_region_add_subregion(sysbus, 0x5472a000, &sio->io_L4ID_EMU_WKUP_IPE);

}


static void synth_reset(DeviceState *d)
{
    SynthState *sio = SYNTH(d);

    sio->global_idx = 0;
}

static void synth_class_init(ObjectClass *klass, void *data)
{
        DeviceClass *dc = DEVICE_CLASS(klass);
        dc->realize = synth_realize;
        dc->reset = synth_reset;
        set_bit(DEVICE_CATEGORY_MISC, dc->categories);
}

static const TypeInfo synth_info =
{
        .name           = TYPE_SYNTH,
        .parent         = TYPE_SYS_BUS_DEVICE,
        .instance_size  = sizeof(SynthState),
        .instance_init  = synth_init,
        .class_init     = synth_class_init,
};
static void synth_register_types(void)
{
        type_register_static(&synth_info);
}

type_init(synth_register_types)
