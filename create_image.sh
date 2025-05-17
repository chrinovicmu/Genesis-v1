#!/bin/bash

set -e

mkdir -p iso/boot/grub

cp kernel/kernel.bin iso/boot/kernel.bin
cp src/boot/grub/grub.cfg iso/grub/grub.cfg

grub-mkrescue -o kernel.iso iso

qemu-system-i386 -kernel kernel/kernel.bin -d int -D qemu.log
