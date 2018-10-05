#!/bin/bash
set -e # fail on error

KERNEL_SECTOR_LENGTH=50

C_FILES='kernel common cmos screen math pic keyboard'
O_FILES='boot.o kernel.o common.o cmos.o screen.o math.o pic.o keyboard.o'

# cleanup
rm -f $O_FILES os.flp

echo Assembling boot...
nasm -felf32 -o boot.o boot.asm

echo Compiling...
for c_file in $C_FILES; do
    echo Compiling $c_file...
    gcc -m32 -nostdlib -Wall -Werror -Wno-main -std=c11 -fno-asynchronous-unwind-tables -c -o $c_file.o $c_file.c
done

echo Linking...
ld --oformat=binary -melf_i386 -Ttext=0x7C00 --omagic -o os.flp $O_FILES

echo Padding...
echo $(wc -c os.flp | cut -d' ' -f1) / $(( $KERNEL_SECTOR_LENGTH * 0x200 ))
dd if=/dev/null of=os.flp bs=1 count=1 seek=$(( $KERNEL_SECTOR_LENGTH * 0x200 )) status=none

echo Done.

# cleanup
rm -f $O_FILES
