
SOURCES = src/boot/boot.o \
		  src/kernel/kernel.o \
		  src/drivers/graphics/monitor.o \
		  src/arch/i386/gdt/gdt.o \
		  src/arch/i386/idt/idt.o \
		  src/arch/i386/interrupts/isr.o \
		  src/drivers/timer/timer.o \
		  src/lib/tinylib.o

CFLAGS = -m32 -ffreestanding -O2 -nostdlib -nostdinc \
		 -fno-builtin -fno-stack-protector -c \
		 -Isrc 

LDFLAGS = -T src/linker.ld -ffreestanding -O2 -nostdlib

ASFLAGS = -f elf32

KERNEL_DIR = kernel

all: $(KERNEL_DIR)/kernel.bin

clean:
	rm -f $(SOURCES) $(KERNEL_DIR)/kernel.bin

$(KERNEL_DIR)/kernel.bin: $(SOURCES)
	mkdir -p $(KERNEL_DIR)
	i686-linux-gnu-gcc $(LDFLAGS) -o $(KERNEL_DIR)/kernel.bin $(SOURCES) -lgcc

src/%.o: src/%.c
	i686-linux-gnu-gcc $(CFLAGS) $< -o $@

src/%.o: src/%.asm 
	i686-linux-gnu-as --32 $< -o $@

src/%.o: src/%.asm
	nasm $(ASFLAGS) $< -o $@

debug:
	@echo "Checking for source files:"
	@ls -la src/arch/i386/gdt/
	@ls -la src/arch/i386/interrupts/
	@echo "Object files that should be built:"
	@echo $(SOURCES)

symbols:
	@echo "Symbols in gdt.o:"
	@nm src/arch/i386/gdt/gdt.o 2>/dev/null || echo "gdt.o not found"
	@echo "Symbols in interrupt files:"
	@nm src/arch/i386/interrupts/*.o 2>/dev/null || echo "interrupt .o files not found"

.PHONY: all clean debug symbols
