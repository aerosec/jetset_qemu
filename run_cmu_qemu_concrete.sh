#!/usr/bin/env bash
$( dirname "${BASH_SOURCE[0]}" )/build/i386-softmmu/qemu-system-i386 -M cmu900 \
  -drive if=pflash,format=raw,index=0,file=$(pwd)/firmware/cmu/boot.bin \
  -drive if=pflash,format=raw,index=1,file=$(pwd)/firmware/cmu/app.bin \
  -drive if=pflash,format=raw,index=2,file=$(pwd)/firmware/cmu/data.bin \
  -display none -d nochain \
  -concrete_target cmu900
