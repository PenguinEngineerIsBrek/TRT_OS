nasm -f bin -o ./compiled/x86_64/bin/boot.bin ./src/bootloader/boot.asm
gcc -w -nostdlib -m32 -Ttext 0x7e00 ./src/kernel/kernel.c ./src/kernel/idt.c -o ./compiled/x86_64/bin/kernel.bin
gcc -w -nostdlib -m32 -Ttext 0x00001000 ./src/kernel/isr10.c -o ./compiled/x86_64/bin/isr10.bin
gcc -w -nostdlib -m32 -Ttext 0x00001300 ./src/kernel/isr13.c -o ./compiled/x86_64/bin/isr13.bin
cd ./compiled/x86_64/bin/
cat isr10.bin isr13.bin > isr.bin
cat boot.bin isr.bin kernel.bin > x86_64.bin
cd ..
dd if=./bin/x86_64.bin of=./boot.img bs=5632 count=1
qemu-system-i386 -drive format=raw,file=./boot.img
