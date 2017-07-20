AS=vasmm68k_mot
LD=vlink
ASFLAGS=-Fvobj
LDSCRIPT=rom-atarist.ld
LDFLAGS=-brawbin1 -M -T $(LDSCRIPT)

OBJS=boot.o
#AS_INCS=hw-atarist.i
ROM_IMAGE=redriceos-atarist.img

all: $(ROM_IMAGE)

$(ROM_IMAGE) : $(OBJS) $(LDSCRIPT)
	$(LD) $(LDFLAGS) -o $(ROM_IMAGE) $(OBJS)

%.o : %.s
	$(AS) $(CROSS_ASFLAGS) -Fvobj -o $@ $<

clean :
	rm -f $(ROM_IMAGE) $(OBJS)

