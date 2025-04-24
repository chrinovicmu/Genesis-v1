
SOURCES=boot.o main.o  
CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -c
LDFLAGS=-Tlink.ld 
ASFLAGS=-felf32

all: kernel

clean:
	-rm *.o kernel 

kernel: $(SOURCES)
	ld -m elf_i386 $(LDFLAGS) -o kernel $(SOURCES)

%.o: %.c
	gcc $(CFLAGS) $< -o $@

%.o: %.s
	nasm $(ASFLAGS) $< -o $@
