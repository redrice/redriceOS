AS=vasmm68k_mot
CC=vc
LD=vlink
CFLAGS=+redriceos -c99 -Ilibc/ -I.
ASFLAGS=-Fvobj -m68000
LDSCRIPT=cart_atarist.ld # use rom-atarist.ld if you want to build ROM image
LDFLAGS=-brawbin1 -T $(LDSCRIPT)# -M
HW_ASM_INC=hardware_atarist.i
HW_C_INC=hardware_atarist.h

OBJS=boot.o kernel.o con.o fb.o fbterm.o memory.o libc/printf.o libc/divmod.o libc/strings_asm.o umm_malloc/umm_malloc.o
ROM_IMAGE=redriceos.img

all: $(ROM_IMAGE)

$(ROM_IMAGE) : $(OBJS) $(LDSCRIPT)
	$(LD) $(LDFLAGS) -o $(ROM_IMAGE) $(OBJS)

%.o : %.s $(HW_ASM_INC)
	$(AS) $(ASFLAGS) -o $@ $<

%.o : %.c $(HW_C_INC)
	$(CC) $(CFLAGS) -c $<

$(HW_C_INC) $(HW_ASM_INC) : hardware_atarist.csv hardware_atarist.awk
# XXX: %.h %.i : %.csv %.awk
	awk -f $(subst csv,awk,$<) $< 

clean :
	rm -f $(ROM_IMAGE) $(OBJS) $(HW_ASM_INC) $(HW_C_INC)

