#!/usr/bin/env bash
$( dirname "${BASH_SOURCE[0]}" )/build/arm-softmmu/qemu-system-arm -machine mk64fn1 \
  -m 256 \
  -initial_pc 0x99d \
  -initial_sp  0x1fff0200 \
  -kernel $(dirname "${BASH_SOURCE[0]}")/../jetset_public_data/p2im_firmware/Console \
  -serial stdio \
  -concrete_target console \
  -d nochain -singlestep #-S -qmp tcp:localhost:$1,server,nowait
