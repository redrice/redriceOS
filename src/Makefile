AS=vasmm68k_mot
CC=vc
LD=vlink
CFLAGS=+redriceos -c99 -Ilibc/
ASFLAGS=-Fvobj -m68000
LDSCRIPT=cart-atarist.ld # use rom-atarist.ld if you want to build ROM image
LDFLAGS=-brawbin1 -M -T $(LDSCRIPT)

OBJS=boot.o kernel.o fb.o console.o memory.o libc/doprintf.o libc/divmod.o libc/strings_asm.o
ROM_IMAGE=redriceos.img

all: $(ROM_IMAGE)

$(ROM_IMAGE) : $(OBJS) $(LDSCRIPT)
	$(LD) $(LDFLAGS) -o $(ROM_IMAGE) $(OBJS)

%.o : %.s
	$(AS) $(ASFLAGS) -o $@ $<

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f $(ROM_IMAGE) $(OBJS)

