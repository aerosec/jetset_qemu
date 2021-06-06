#!/usr/bin/env bash
$( dirname "${BASH_SOURCE[0]}" )/build/arm-softmmu/qemu-system-arm -machine raspi2 \
  -kernel $(dirname "${BASH_SOURCE[0]}")/../jetset_public_data/rpi/final/zImage \
  -dtb $(dirname "${BASH_SOURCE[0]}")/../jetset_public_data/rpi/final/bcm2709-rpi-2-b.dtb -m 1024 \
  -initrd $(dirname "${BASH_SOURCE[0]}")/../jetset_public_data/rpi/test.cpio.gz \
  -serial stdio -append "rw earlyprintk 	loglevel=8 console=ttyAMA0,115200 dwc_otg.lpm_enable=0 root=/dev/mmcblk0p2" \
  -d nochain -S -qmp tcp:localhost:$1,server,nowait
