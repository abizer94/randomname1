# $@ = target file
# $< = first dependency
# $^ = all dependencies

# detect all .o files based on their .c source
C_SOURCES = $(wildcard *.c drivers/*.c)
HEADERS = $(wildcard *.h  drivers/*.h )
OBJ_FILES = ${C_SOURCES:.c=.o interrupts.o}

CC ?= x86_64-elf-gcc
LD ?= x86_64-elf-ld

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Notice how dependencies are built as needed
kernel.bin: bl/k_ent.o ${OBJ_FILES}
	$(LD) -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

os-image.bin: bl/mbr.bin kernel.bin
	cat $^ > $@

#run: os-image.bin
#	qemu-system-i386 -fda $<
run: disk.img
	qemu-system-i386 -drive format=raw,file=$<


echo: os-image.bin
	xxd $<

# only for debug
kernel.elf: bl/kernel_entry.o ${OBJ_FILES}
	$(LD) -m elf_i386 -o $@ -Ttext 0x1000 $^

disk.img: os-image.bin
	dd if=os-image.bin of=disk.img bs=512 conv=notrunc

debug: disk.img kernel.elf
	qemu-system-x86_64 -drive format=raw,file=disk.img
	
%.o: %.c ${HEADERS}
	$(CC) -g -m32 -ffreestanding -fno-pie -fno-stack-protector -c $< -o $@ # -g for debugging

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

%.dis: %.bin
	ndisasm -b 32 $< > $@

clean:
	$(RM) *.bin *.o *.dis *.elf
	$(RM) *.o
	$(RM) bl/*.o bl/*.bin
	$(RM) drivers/*.o
