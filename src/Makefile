AS=vasmm68k_mot
CC=vc
LD=vlink
AWK=awk
CFLAGS=+redriceos -c99 -Ilibc/ -I.
ASFLAGS=-Fvobj -m68000 -quiet
LDSCRIPT=cart_atarist.ld
LDFLAGS=-brawbin1 -T $(LDSCRIPT)# -M
HW_DESCR=hardware_atarist
HW_ASM_INC=$(HW_DESCR).i
HW_C_INC=$(HW_DESCR).h

OBJS=boot.o kernel.o con.o exception.o exception_asm.o fb.o fbterm.o memory.o libc/printf.o libc/divmod.o libc/strings_asm.o umm_malloc/umm_malloc.o
ROM_IMAGE=redriceos.img

all: $(ROM_IMAGE)

$(ROM_IMAGE) : $(OBJS) $(LDSCRIPT)
	$(LD) $(LDFLAGS) -o $(ROM_IMAGE) $(OBJS)

%.o : %.s $(HW_ASM_INC)
	$(AS) $(ASFLAGS) -o $@ $<

%.o : %.c $(HW_C_INC)
	$(CC) $(CFLAGS) -c $<

$(HW_C_INC) $(HW_ASM_INC) : $(HW_DESCR).csv $(HW_DESCR).awk
# XXX: %.h %.i : %.csv %.awk
	$(AWK) -f $(subst csv,awk,$<) $<

clean :
	rm -f $(ROM_IMAGE) $(OBJS) $(HW_ASM_INC) $(HW_C_INC)

