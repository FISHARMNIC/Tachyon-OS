# run in linux/vm
mkdir /tmp/lima/bin

echo 1
#assemble boot.s file
as --32 ../bin/boot/boot.s -o /tmp/lima/bin/boot.o

echo 2

#compile kernel.c file
if (gcc -m32 -c ../kernel.c -o /tmp/lima/bin/kernel.o -ffreestanding -O3) ; then
    gcc -m32 -c ../apps/test.c -o /tmp/lima/bin/test.o -ffreestanding -O3
    gcc -m32 -c ../apps/interpreter.c -o /tmp/lima/bin/interpreter.o -ffreestanding -O3
    echo 3
    #linking the kernel with kernel.o and boot.o files
    if (ld -m elf_i386 -T ../bin/boot/linker.ld /tmp/lima/bin/kernel.o\
        /tmp/lima/bin/test.o \
        /tmp/lima/bin/interpreter.o\
        /tmp/lima/bin/boot.o -o /tmp/lima/bin/MyOS.bin -nostdlib) ; then
        echo 4
        #check MyOS.bin file is x86 multiboot file or not
        grub-file --is-x86-multiboot /tmp/lima/bin/MyOS.bin

        #building the iso file
        mkdir -p /tmp/lima/isodir/boot/grub
        cp /tmp/lima/bin/MyOS.bin /tmp/lima/isodir/boot/MyOS.bin
        cp ../bin/boot/grub.cfg /tmp/lima/isodir/boot/grub/grub.cfg
        grub-mkrescue -o /tmp/lima/bin/MyOS.iso /tmp/lima/isodir

    fi
fi

exit