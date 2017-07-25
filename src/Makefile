AS=vasmm68k_mot
CC=vc
LD=vlink
CFLAGS=+redriceos -c99
ASFLAGS=-Fvobj -m68000
LDSCRIPT=rom-atarist.ld
LDFLAGS=-brawbin1 -M -T $(LDSCRIPT)

OBJS=boot.o kernel.o fb.o console.o
#AS_INCS=hw-atarist.i
ROM_IMAGE=redriceos-atarist.img

all: $(ROM_IMAGE)

$(ROM_IMAGE) : $(OBJS) $(LDSCRIPT)
	$(LD) $(LDFLAGS) -o $(ROM_IMAGE) $(OBJS)

%.o : %.s
	$(AS) $(ASFLAGS) -o $@ $<

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f $(ROM_IMAGE) $(OBJS)

