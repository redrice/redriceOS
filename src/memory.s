;
; This file is very heavily based on memory init routines from EmuTOS, which
; are copyrighted in the following way:
;
; Copyright (C) 2001-2017 by Authors:
;
; Authors:
;  MAD  Martin Doering
;  PES  Petr Stehlik
;  jfdn Jean-François DEL NERO
;  VRI  Vincent Rivière
;  RFB  Roger Burrows
;
; This file is distributed under the GPL, version 2 or at your
; option any later version.
;
	xref memory_configured
	xref _bzero
	xref __bss_start
	xref __bss_len
	global memory_init
	global bss_clear

	include	hardware_atarist.i

	code

memory_init:
	move.b	#$a,ST_MMU	; start with 2x 2 MiB banks

; init the test pattern
	movea.w	#$000008,a0	; bank 0
	lea	$200008,a1	; bank 1
	moveq	#0,d0
init_pattern_loop:
	move.w	d0,(a0)+	; bank 0
	move.w	d0,(a1)+	; bank 1
	add.w	#$fa54,d0	; next pattern data
	cmpa.l	#$200,a0	; 200 word done?
	bne	init_pattern_loop

	move.l	#$200000,d1	; start with bank 1
	moveq	#0,d5		; highest usable memory address
	moveq	#0,d6		; value to be set into MMU register

	; test for 128k bank config
test_128k_STE:
	lsr.w	#2,d6
	move.l	#$20000,d4
	movea.l	#$40008,a0
	lea	test_128k_ST,a5	; return point of test pattern
	bra	check_test_pattern
test_128k_ST:
	beq	bank_test_end
	movea.w	#$208,a0
	lea	test_512k_STE,a5 ; return point of test pattern
	bra	check_test_pattern
test_512k_STE:
	beq	bank_test_end
	move.l	#$80000,d4
	movea.l	#$80008,a0
	lea	test_512k_ST,a5	; return point of test pattern
	bra	check_test_pattern
test_512k_ST:
	beq	bank_test_end_512k
	movea.w	#$408,a0
	lea	test_2m,a5	; return point of test pattern 
	bra	check_test_pattern
test_2m:
	beq	bank_test_end_512k
	movea.w #$008,a0	; 0kB/2MB test for both ST and STE
	lea	last_return,a5	; return point of test pattern
	moveq	#0,d4	
	bra	check_test_pattern
last_return:
	bne	bank_test_end
	move.l	#$200000,d4
	addq.w	#4,d6
bank_test_end_512k:
	addq.w	#4,d6
bank_test_end:
	add.l	d4,d5
	sub.l	#$200000,d1	; do the test for bank 0
	beq	test_128k_STE

	move.b	d6,ST_MMU

mem_sanity_check:
	move.l	#$ff0055aa,d0
mem_sanity_loop:
	move.l	d5,a0
	subq.l	#4,a0
	move.l	d0,(a0)
	cmp.l	(a0),d0
	beq	mem_sanity_done
	lsr.l	#1,d5
	bra	mem_sanity_loop
mem_sanity_done:

	move.l  d5,_phystop	; save in phystop variable, kernel.c

	jmp memory_configured

check_test_pattern:
	adda.l	d1,a0		; compute starting address
	moveq	#0,d0		; first pattern word
	lea	$1f8(a0),a1	; end address
check_test_pattern_loop:
	cmp.w	(a0)+,d0
	bne	end_check_test_pattern
	add.w	#$fa54,d0
	cmpa.l	a0,a1
	bne	check_test_pattern_loop
end_check_test_pattern:
	jmp	(a5)

bss_clear:
	move.l	#__bss_start,d0
	move.l	#__bss_len,d1
	jsr	_bzero

	rts

; vim: set ft=asm68k:

