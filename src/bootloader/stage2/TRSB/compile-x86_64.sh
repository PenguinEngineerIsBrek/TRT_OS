nasm -f bin -o ../../../compiled/x86_64/bin/loader.bin ../stage2/TRSB/load_kernel.asm
gcc ../stage2/TRSB/idt.c -o ../../../compiled/x86_64/bin/idt.bin
cd ../../../compiled/x86_64/bin/
cat idt.bin loader.bin > boot2.bin
