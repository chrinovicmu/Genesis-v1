#!/bin/bash

mkdir -p iso/boot/grub

cp src/kernel.bin iso/boot/kernel.bin
cp src/grub.cfg iso/boot/grub/grub.cfg

grub-mkrescue -o kernel.iso iso
