nasm -f bin -o boot.bin boot.asm
nasm -f bin -o kernel.bin kernel.asm
dd if=/dev/zero of=disk.img bs=2048 count=1
dd if=./boot.bin of=disk.img bs=2048 seek=0 count=1
dd if=./kernel.bin of=disk.img bs=512 seek=1 count=1
qemu-system-x86_64 -drive file=disk.img,format=raw
