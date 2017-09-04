; memory mapped I/O bus access routines
	global _mmio_read_1
	global _mmio_write_1
	global _mmio_set_1
	global _mmio_unset_1

_mmio_read_1:
	move.b		(a0),d0
	rts

_mmio_write_1:
	move.b		d0,(a0)
	rts

_mmio_set_1:
	or.b		(a0),d0
	move.b		d0,(a0)
	rts

_mmio_unset_1:
	move.b		(a0),d1
	not		d0
	and		d0,d1
	move.b		d1,(a0)
	rts

;_mmio_read_2:
;	move.w		(a0),(a1)
;	rts
; ...

; vim: set ft=asm68k:
