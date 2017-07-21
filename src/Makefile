AS=vasmm68k_mot
CC=vc
LD=vlink
CFLAGS=+redriceos
ASFLAGS=-Fvobj
LDSCRIPT=rom-atarist.ld
LDFLAGS=-brawbin1 -M -T $(LDSCRIPT)

OBJS=boot.o kernel.o
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

