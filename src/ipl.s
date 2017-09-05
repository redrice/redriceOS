	global _ipl_get
	global _ipl_set

	code
; ipl_get: returns current IPL in d0
_ipl_get:
	move		sr,d0		; load SR into D0
	and		#$0F00,d0	; mask out other bits than IPL
	asr		#8,d0		; shift right to make 8-bit value
	rts

; ipl_set: d0 - new ipl level
_ipl_set:
	and		#$F,d0		; leave 8-bits just to be sure
	asl		#8,d0		; shift left to put bits into IPL pos.
	move		sr,d1		; load SR into D1
	and		#$F0FF,d1	; mask out current IPL
	or		d1,d0		; OR current SR state with new IPL
	move		d0,sr		; load D0 into SR
	rts

; vim: set ft=asm68k:
