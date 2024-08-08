nasm -f bin -o ../../../compiled/x86_64/bin/boot.bin boot.asm
dd if=../../../compiled/x86_64/bin/boot.bin of=../../../compiled/x86_64/boot.img
qemu-system-x86_64 -drive format=raw,file=../../../compiled/x86_64/boot.img
