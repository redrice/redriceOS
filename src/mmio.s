; memory mapped I/O bus access routines
	global _mmio_read_1
	global _mmio_write_1

_mmio_read_1:
	move.b		(a0),(a1)
	rts

_mmio_write_1:
	move.b		(a1),(a0)
	rts

;_mmio_read_2:
;	move.w		(a0),(a1)
;	rts
; ...

