AS=vasmm68k_mot
CC=vc
LD=vlink
AWK=awk
CFLAGS=+redriceos -c99 -Ilibc/ -I. -cpu=68000 -O3
ASFLAGS=-Fvobj -m68000 -quiet
LDSCRIPT_CART=cart_atarist.ld
LDSCRIPT_ROM=rom256k_atarist.ld
LDFLAGS=-brawbin1 # -M
HW_DESCR=hardware_atarist
HW_ASM_INC=$(HW_DESCR).i
HW_C_INC=$(HW_DESCR).h

OBJS_ROM=boot_rom.o
OBJS_CART=boot_cart.o
OBJS=acia.o boot.o kernel.o con.o exception.o exception_asm.o fb.o fbterm.o fb_blit_hw.o ikbd.o ipl.o irq.o keymap_ikbd.o ktest.o memory.o mfp.o mmio.o msgbuf.o systimer.o libc/atoi.o libc/printf.o libc/divmod.o libc/string.o libc/strings_asm.o umm_malloc/umm_malloc.o
ROM_IMAGE=redriceos-rom.img
CART_IMAGE=redriceos-cart.img

all: $(ROM_IMAGE) $(CART_IMAGE)

$(ROM_IMAGE) : $(OBJS) $(OBJS_ROM) $(LDSCRIPT_ROM)
	$(LD) $(LDFLAGS) -T $(LDSCRIPT_ROM) -o $(ROM_IMAGE) $(OBJS_ROM) $(OBJS)

$(CART_IMAGE) : $(OBJS) $(OBJS_CART) $(LDSCRIPT_CART)
	$(LD) $(LDFLAGS) -T $(LDSCRIPT_CART) -o $(CART_IMAGE) $(OBJS_CART) $(OBJS)

%.o : %.s $(HW_ASM_INC)
	$(AS) $(ASFLAGS) -o $@ $<

%.o : %.c $(HW_C_INC)
	$(CC) $(CFLAGS) -c $<

$(HW_C_INC) $(HW_ASM_INC) : $(HW_DESCR).csv $(HW_DESCR).awk
# XXX: %.h %.i : %.csv %.awk
	$(AWK) -f $(subst csv,awk,$<) $<

clean :
	rm -f $(ROM_IMAGE) $(CART_IMAGE) $(OBJS) $(OBJS_CART) $(OBJS_ROM) $(HW_ASM_INC) $(HW_C_INC)

