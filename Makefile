
SOURCES = src/boot/boot.o \
		  src/kernel/kernel.o \
		  src/drivers/graphics/monitor.o \
		  src/lib/common.o \
		  src/arch/i386/descriptor_tables.o \
		  src/arch/i386/isr.o \
		  src/arch/i386/interrupt.o \
		  src/drivers/timer/timer.o \
		  src/arch/i386/gdt.o \
		  src/lib/tinylib.o

CFLAGS = -m32 -ffreestanding -O2 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -c
LDFLAGS = -T src/linker.ld -ffreestanding -O2 -nostdlib
ASFLAGS = -f elf32

# Output directory for the kernel binary
KERNEL_DIR = kernel

all: $(KERNEL_DIR)/kernel.bin

clean:
	rm -f src/*.o $(KERNEL_DIR)/kernel.bin

$(KERNEL_DIR)/kernel.bin: $(SOURCES)
	# Ensure the kernel directory exists
	mkdir -p $(KERNEL_DIR)
	i686-linux-gnu-gcc $(LDFLAGS) -o $(KERNEL_DIR)/kernel.bin $(SOURCES) -lgcc

src/%.o: src/%.c
	i686-linux-gnu-gcc $(CFLAGS) $< -o $@

src/%.o: src/%.s
	nasm $(ASFLAGS) $< -o $@
