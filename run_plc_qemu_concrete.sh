#!/usr/bin/env bash
$( dirname "${BASH_SOURCE[0]}" )/build/arm-softmmu/qemu-system-arm -machine stm32f4 \
  -kernel $(dirname "${BASH_SOURCE[0]}")/../jetset_public_data/p2im_firmware/PLC \
  -serial stdio \
  -concrete_target plc \
  -d nochain -singlestep #-S -qmp tcp:localhost:$1,server,nowait
