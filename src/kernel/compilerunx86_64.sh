gcc -ffreestanding -c ~/Desktop/work/TRT_OS/src/kernel/kernel.c  -o ~/Desktop/work/TRT_OS/compiled/x86_64/bin/kernel.o
ld -o ~/Desktop/work/TRT_OS/compiled/x86_64/bin/kernel.bin -Ttext 0x10000 --oformat binary ~/Desktop/work/TRT_OS/compiled/x86_64/bin/kernel.o
