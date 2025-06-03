# Find all directories containing .h files (header files)
# This command searches the src directory for all .h files, extracts their directory paths,
# removes duplicates with sort -u, and stores them in ASM_INCLUDE_DIRS variable
ASM_INCLUDE_DIRS := $(shell find src -type f -name '*.h' -exec dirname {} \; | sort -u)

# Add -I flags for each include directory
# The foreach function iterates through each directory in ASM_INCLUDE_DIRS and prefixes it with -I
# This creates include path flags that tell the assembler where to find header files
ASFLAGS = -f elf32 $(foreach dir,$(ASM_INCLUDE_DIRS),-I$(dir))

# Define all source object files that need to be compiled
# These .o files will be generated from corresponding .c and .asm source files
SOURCES = src/boot/boot.o \
          src/kernel/kernel.o \
          src/drivers/graphics/monitor.o \
          src/arch/i386/gdt/gdt.o \
          src/arch/i386/gdt/gdt_load.o \
          src/arch/i386/idt/idt.o \
          src/arch/i386/idt/idt_load.o \
          src/arch/i386/interrupts/isr.o \
          src/drivers/timer/timer.o \
          src/drivers/pic.o \
          src/lib/tinylib.o

# C compiler flags for cross-compilation to 32-bit x86
# -m32: generate 32-bit code
# -ffreestanding: environment may not have standard library
# -O2: optimization level 2
# -nostdlib: don't use standard library
# -nostdinc: don't use standard include paths
# -fno-builtin: don't recognize built-in functions
# -fno-stack-protector: disable stack protection (not available in kernel)
# -c: compile only, don't link
# -Isrc: add src directory to include path
CFLAGS = -m32 -ffreestanding -O2 -nostdlib -nostdinc \
         -fno-builtin -fno-stack-protector -c \
         -Isrc 

# Linker flags
# -T src/linker.ld: use custom linker script
# Other flags same as CFLAGS for consistency
LDFLAGS = -T src/linker.ld -ffreestanding -O2 -nostdlib

# Output directory for the final kernel binary
KERNEL_DIR = kernel

# Default target - builds the kernel binary
all: $(KERNEL_DIR)/kernel.bin

# Clean target - removes all compiled object files and the kernel binary
# IMPORTANT: Each command line must start with a TAB character, not spaces
clean:
	rm -f $(SOURCES) $(KERNEL_DIR)/kernel.bin

# Main kernel binary target - depends on all source object files
$(KERNEL_DIR)/kernel.bin: $(SOURCES)
	mkdir -p $(KERNEL_DIR)
	i686-linux-gnu-gcc $(LDFLAGS) -o $(KERNEL_DIR)/kernel.bin $(SOURCES) -lgcc

# Pattern rule for compiling C source files to object files
# $< refers to the first prerequisite (the .c file)
# $@ refers to the target (the .o file)
src/%.o: src/%.c
	i686-linux-gnu-gcc $(CFLAGS) $< -o $@

# Pattern rule for assembling ASM source files to object files
# Uses NASM assembler with the flags defined in ASFLAGS
src/%.o: src/%.asm
	nasm $(ASFLAGS) $< -o $@

# Debug target - prints various information for troubleshooting
# The @ symbol suppresses printing the command itself, only shows output
debug:
	@echo "ASM include dirs: $(ASM_INCLUDE_DIRS)"
	@echo "ASFLAGS: $(ASFLAGS)"
	@echo "Checking for source files:"
	@ls -la src/arch/i386/gdt/
	@ls -la src/arch/i386/interrupts/
	@echo "Object files that should be built:"
	@echo $(SOURCES)

# Symbols target - examines symbol tables in compiled object files
# Uses nm command to display symbols, with error handling if files don't exist
symbols:
	@echo "Symbols in gdt.o:"
	@nm src/arch/i386/gdt/gdt.o 2>/dev/null || echo "gdt.o not found"
	@echo "Symbols in interrupt files:"
	@nm src/arch/i386/interrupts/*.o 2>/dev/null || echo "interrupt .o files not found"

# .PHONY declares targets that don't create files with the same name
# This prevents conflicts if files named 'all', 'clean', etc. exist
.PHONY: all clean debug symbols
