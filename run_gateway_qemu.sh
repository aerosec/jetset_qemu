#!/usr/bin/env bash
$( dirname "${BASH_SOURCE[0]}" )/build/arm-softmmu/qemu-system-arm -machine stm32f4 \
  -m 256 \
  -initial_pc 0x8003659 \
  -initial_sp 0x20005000 \
  -kernel $(dirname "${BASH_SOURCE[0]}")/../jetset_public_data/p2im_firmware/Gateway \
  -serial stdio \
  -d nochain -singlestep -S -qmp tcp:localhost:$1,server,nowait
