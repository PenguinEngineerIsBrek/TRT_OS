nasm -f elf32 -o ./compiled/x86_64/bin/boot.o ./src/bootloader/boot.asm
gcc -w -nostdlib -m32 -Ttext 0x7e00 ./src/kernel/kernel.c ./src/kernel/idt.c -o ./compiled/x86_64/bin/kernel.o
cd ./compiled/x86_64/bin/
ld -m elf_i386 -o trtos boot.o kernel.o  
cd ..
dd if=./bin/trtos.bin of=./boot.img bs=5632 count=1
qemu-system-i386 -drive format=raw,file=./boot.img
