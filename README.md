# Jetset QEMU

A quick note on how to rigger the symbolic execution and how it works!

The symbolic execution works by taint-tracking TCG variables inside qemu; 
when a symbolic operation occurs, this is transmitted to jetset_engine.

In order to taint variables (in a simplified way), we do two things:

1. We initialize a "symbolic device" class that handles tainting mmio reads.
2. We instantiate that device class in our CPU machine class.
3. We coordinate QEMU with `jetset_engine`.

## Initializing and Instantiating a Symbolic Device

1. Create a synthetic device header file. An example is in `include/hw/misc/simple_synth.h`. Here we've defined a single mmio memory region.
2. Now instantiate that device. Here, an example is in a corresponding `hw/misc/simple_synth.c` device.
3. Add this machine class to the compilation sequence, e.g. `obj-$(CONFIG_SYNTH_CMU900) += cmu900.o` We've added `common-obj-y += simple_synth.o` to `hw/misc/Makefile.objs`.  (You may want to modify `./default-configs`.)
4. Initialize this class in your CPU machine; for example:

```
DeviceState *dev = qdev_create(NULL, "simple_synth");
qdev_prop_set_uint32(dev, "size", 0xb000);
qdev_prop_set_uint32(dev, "base_addr", RAM_OFFSET);
qdev_init_nofail(dev);
```

5. After this, we may need to reconfigure and recompile QEMU. From the root jetset directory, run:

```
make config_qemu
make build_qemu
```

## Coordinating with Jetset Engine

You will want to create a run_myDevice_qemu.sh script that will be referenced from the engine (see the root Jetset `Makefile` for examples).

The shell script will look something like this:

```
#!/usr/bin/env bash
DIR=$(realpath $(dirname ${BASH_SOURCE[0]}))
QEMU="$DIR"/build/i386-softmmu/qemu-system-i386
RAM="$DIR"/../firmware/myDevice-ram.bin

TERM=xterm "${QEMU}" \
  -M myMachineName \
  -serial stdio \
  -display none \
  -parallel none \
  -device loader,force-raw=true,addr=0x21E80000,file="${RAM}" \ # defines a base address device
  -d nochain -singlestep -S -qmp tcp:localhost:$1,server,nowait # arguments that set up the correct communication with jetset
```
