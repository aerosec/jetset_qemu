#!/usr/bin/env bash
$( dirname "${BASH_SOURCE[0]}" )/build/arm-softmmu/qemu-system-arm -machine sam3x8e \
  -m 256 \
  -initial_pc 0x80c21 \
  -initial_sp 0x20088000 \
  -kernel $(dirname "${BASH_SOURCE[0]}")/../jetset_public_data/p2im_firmware/Steering_Control \
  -serial stdio \
  -d nochain -singlestep -S -qmp tcp:localhost:$1,server,nowait
