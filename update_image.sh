#!/bin/bash

#attach floppy file to loop device
sudo losetup /dev/loop0 floppy.img

#mount the loop device- accsess like a normal file system
sudo mount /dev/loop0 /mnt

#copy custom kernel binary into mounterd image
sudo cp src/kernel /mnt/kernel

#unmount floope image
sudo umount /dev/loop0

#detaches loop device
sudo losetup -d /dev/loop0
