nasm -f bin -o ../../../compiled/x86_64/bin/boot.bin boot.asm
../stage2/TRSB/compile-x86_64.sh
cd ../../../compiled/x86_64/bin
cat boot.bin boot2.bin > x86_64.bin
cd ..
dd if=./bin/x86_64.bin of=./boot.img bs=2560 count=1
qemu-system-x86_64 -drive format=raw,file=./boot.img
