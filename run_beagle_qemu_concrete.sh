#!/usr/bin/env bash
$( dirname "${BASH_SOURCE[0]}" )/build/arm-softmmu/qemu-system-arm -machine beagle \
  -m 256 \
  -kernel $(dirname "${BASH_SOURCE[0]}")/../jetset_public_data/beagle/kernel/MLO \
  -serial stdio \
  -concrete_target beagle \
  -d nochain -singlestep #-S -qmp tcp:localhost:$1,server,nowait
