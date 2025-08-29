# $@ = target file
# $< = first dependency
# $^ = all dependencies

# detect all .o files based on their .c source
C_SOURCES = $(wildcard *.c drivers/*.c)
HEADERS = $(wildcard *.h  drivers/*.h )
OBJ_FILES = ${C_SOURCES:.c=.o interrupts.o}
RM := rm -f

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

disk.img: bl/mbr.bin kernel.bin
	# 1. Create empty 64MB disk image
	dd if=/dev/zero of=disk.img bs=1M count=64

	# 2. Partition the disk with a single FAT32 partition
	echo -e "o\nn\np\n1\n2048\n\n\
	a\n1\n\
	t\nc\n\
	w" | fdisk disk.img
	echo '00000000: 2022 00' > chs_patch.hex

	# Apply patch at offset 0x1BF (Head = byte 1 of partition entry)
	xxd -r - offset=447 chs_patch.hex | dd of=disk.img bs=1 seek=447 conv=notrunc

	rm -f chs_patch.hex
		# Manually patch CHS in partition table (bytes 1–3 of entry at 0x1BE)
#	printf '\x20\x21\x00' | dd of=disk.img bs=1 seek=$$((0x1BE + 1)) conv=notrunc




	# 3. Write MBR bootloader to sector 0
	dd if=bl/mbr.bin of=disk.img bs=1 count=446 conv=notrunc
	dd if=bl/mbr.bin of=disk.img bs=1 skip=510 seek=510 count=2 conv=notrunc

	# 4. Format partition (FAT32) — offset starts at 2048*512 = 1048576
	mkfs.vfat -F 32 -n BOOT -C fat32part.img 64512
	# note: 64512 = 64MB - 2048 sectors reserved for MBR

	# 5. Copy kernel into FAT32 partition using mtools (mcopy needs mtools.conf)
	mcopy -i fat32part.img kernel.bin ::KERNAL.BIN

	# 6. Write the FAT32 partition back into the full image at offset 1MiB
	dd if=fat32part.img of=disk.img bs=512 seek=2048 conv=notrunc
	dd if=kernel.bin of=disk.img bs=512 seek=2049 conv=notrunc status=progress

	rm -f fat32part.img
	


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
	$(RM) fat32part.img
	$(RM) disk.img
