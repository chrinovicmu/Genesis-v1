SOURCES=boot.o kernel.o monitor.o common.o
CFLAGS=-m32 -ffreestanding -O2 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -c
LDFLAGS=-T linker.ld -ffreestanding -O2 -nostdlib
ASFLAGS=-f elf32

all: kernel.bin

clean:
	rm -f *.o kernel.bin

kernel.bin: $(SOURCES)
	i686-linux-gnu-gcc $(LDFLAGS) -o kernel.bin $(SOURCES) -lgcc

%.o: %.c
	i686-linux-gnu-gcc $(CFLAGS) $< -o $@

%.o: %.s
	nasm $(ASFLAGS) $< -o $@
