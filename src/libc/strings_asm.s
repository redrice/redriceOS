	global _bzero
; bzero: d0 - address, d1 - length
_bzero:
	move.l		d0,a0
.1:	clr.w		(a0)+
	subq.l		#2,d1
	bne		.1

	rts

