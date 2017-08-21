* (c) 1987 Atari Corporation
*    All Rights Reserved.

* BLiTTER BASE ADDRESS

BLiTTER   equ  $FF8A00

* BLiTTER REGISTER OFFSETS

Halftone  equ  0
Src_Xinc  equ  32
Src_Yinc  equ  34
Src_Addr  equ  36
Endmask1  equ  40
Endmask2  equ  42
Endmask3  equ  44
Dst_Xinc  equ  46
Dst_Yinc  equ  48
Dst_Addr  equ  50
X_Count   equ  54
Y_Count   equ  56
HOP       equ  58
OP        equ  59
Line_Num  equ  60
Skew      equ  61

* BLiTTER REGISTER FLAGS

fHOP_Source    equ  1
fHOP_Halftone  equ  0

fSkewFXSR      equ  7
fSkewNFSR      equ  6

fLineBusy      equ  7
fLineHog       equ  6
fLineSmudge    equ  5

* BLiTTER REGISTER MASKS

mHOP_Source    equ  $02
mHOP_Halftone  equ  $01

mSkewFXSR      equ  $80
mSkewNFSR      equ  $40

mLineBusy      equ  $80
mLineHog       equ  $40
mLineSmudge    equ  $20

*         E n D m A s K   d A t A
*
* These tables are referenced by PC relative instructions.  Thus,
* the labels on these tables must remain within 128 bytes of the
* referencing instructions forever.  Amen.
*
* 0: Destination  1: Source   <<< Invert right end mask data >>>

lf_endmask:
     dc.w $FFFF

rt_endmask:
     dc.w $7FFF
     dc.w $3FFF
     dc.w $1FFF
     dc.w $0FFF
     dc.w $07FF
     dc.w $03FF
     dc.w $01FF
     dc.w $00FF
     dc.w $007F
     dc.w $003F
     dc.w $001F
     dc.w $000F
     dc.w $0007
     dc.w $0003
     dc.w $0001
     dc.w $0000

* TiTLE:  BLiT_iT
*
* PuRPoSE:
*    Transfer a rectangular block of pixels located at an
*    arbitrary X,Y position in the source memory form to
*    another arbitrary X,Y position in the destination memory
*    form using replace mode (boolean operator 3).
*    The source and destination rectangles should not overlap.
*
* iN:
*    a4   pointer to 34 byte input parameter block
*
* Note: This routine must be executed in supervisor mode as
*    access is made to hardware registers in the protected region
*    of the memory map.
*
*
*    I n p u t   p a r a m e t e r   b l o c k   o f f s e t s

SRC_FORM  equ  0    ; Base address of source memory form .l
SRC_NXWD  equ  4    ; Offset between words in source plane .w
SRC_NXLN  equ  6    ; Source form width .w
SRC_NXPL  equ  8    ; Offset between source planes .w
SRC_XMIN  equ  10   ; Source blt rectangle minimum X .w
SRC_YMIN  equ  12   ; Source blt rectangle minimum Y .w

DST_FORM  equ  14   ; Base address of destination memory form .l 
DST_NXWD  equ  18   ; Offset between words in destination plane.w
DST_NXLN  equ  20   ; Destination form width .w
DST_NXPL  equ  22   ; Offset between destination planes .w
DST_XMIN  equ  24   ; Destination blt rectangle minimum X .w
DST_YMIN  equ  26   ; Destination blt rectangle minimum Y .w

WIDTH     equ  28   ; Width of blt rectangle .w
HEIGHT    equ  30   ; Height of blt rectangle .w
PLANES    equ  32   ; Number of planes to blt .w

BLiT_iT:

     lea  BLiTTER,a5          ; a5-> BLiTTER register block  

*
* Calculate Xmax coordinates from Xmin coordinates and width
*
     move.w    WIDTH(a4),d6  
     subq.w    #1,d6               ; d6<- width-1  

     move.w    SRC_XMIN(a4),d0     ; d0<- src Xmin  
     move.w    d0,d1
     add.w     d6,d1               ; d1<- src Xmax=src Xmin+width-1

     move.w    DST_XMIN(a4),d2     ; d2<- dst Xmin  
     move.w    d2,d3
     add.w     d6,d3               ; d3<- dst Xmax=dstXmin+width-1

*
* Endmasks are derived from source Xmin mod 16 and source Xmax
*    mod 16
*  
     moveq.l   #$0F,d6   ; d6<- mod 16 mask

     move.w    d2,d4          ; d4<- DST_XMIN
     and.w     d6,d4          ; d4<- DST_XMIN mod 16
     add.w     d4,d4          ; d4<- offset into left end mask tbl

     move.w    lf_endmask(pc,d4.w),d4        ; d4<- left endmask

     move.w    d3,d5          ; d5<- DST_XMAX
     and.w     d6,d5          ; d5<- DST_XMAX mod 16
     add.w     d5,d5          ; d5<- offset into right end mask tbl

     move.w    rt_endmask(pc,d5.w),d5   ; d5<-inverted right end mask
     not.w     d5                       ; d5<- right end mask

*  
* Skew value is (destination Xmin mod 16 - source Xmin mod 16)
* && 0x000F.  Three discriminators are used to determine the
* states of FXSR and NFSR flags:
*
*    bit 0     0: Source Xmin mod 16 =< Destination Xmin mod 16
*              1: Source Xmin mod 16 >  Destination Xmin mod 16
*
*    bit 1     0: SrcXmax/16-SrcXmin/16 <> DstXmax/16-DstXmin/16
*                   Source span              Destination span
*              1: SrcXmax/16-SrcXmin/16 == DstXmax/16-DstXmin/16
*
*    bit 2     0: multiple word Destination span
*              1: single word Destination span
*
*    These flags form an offset into a skew flag table yielding
*    correct FXSR and NFSR flag states for the given source and
*    destination alignments
*

     move.w    d2,d7     ; d7<- Dst Xmin
     and.w     d6,d7     ; d7<- Dst Xmin mod16
     and.w     d0,d6     ; d6<- Src Xmin mod16
     sub.w     d6,d7     ; d7<- Dst Xmin mod16-Src Xmin mod16
*                        ; if Sx&F > Dx&F then cy:1 else cy:0
     clr.w     d6        ; d6<- initial skew flag table index
     addx.w    d6,d6     ; d6[bit0]<- intraword alignment flag

     lsr.w     #4,d0     ; d0<- word offset to src Xmin
     lsr.w     #4,d1     ; d1<- word offset to src Xmax
     sub.w     d0,d1     ; d1<- Src span - 1

     lsr.w     #4,d2     ; d2<- word offset to dst Xmin
     lsr.w     #4,d3     ; d3<- word offset to dst Xmax
     sub.w     d2,d3     ; d3<- Dst span - 1
     bne       set_endmasks   ; 2nd discriminator is one word dst  

* When destination spans a single word, both end masks are merged
* into Endmask1.  The other end masks will be ignored by the BLiTTER

     and.w     d5,d4          ; d4<- single word end mask
     addq.w    #4,d6          ; d6[bit2]:1 => single word dst

set_endmasks:

     move.w    d4,Endmask1(a5)     ; left end mask
     move.w    #$FFFF,Endmask2(a5) ; center end mask
     move.w    d5,Endmask3(a5)     ; right end mask

     cmp.w     d1,d3          ; the last discriminator is the
     bne       set_count      ; equality of src and dst spans

     addq.w    #2,d6          ; d6[bit1]:1 => equal spans

set_count:
     move.w    d3,d4
     addq.w    #1,d4          ; d4<- number of words in dst line
     move.w    d4,X_Count(a5) ; set value in BLiTTER

* Calculate Source starting address:
*
*   Source Form address              +
*  (Source Ymin * Source Form Width) +
* ((Source Xmin/16) * Source Xinc)  

     move.l    SRC_FORM(a4),a0     ; a0-> start of Src form
     move.w    SRC_YMIN(a4),d4     ; d4<- offset in lines to Src Ymin
     move.w    SRC_NXLN(a4),d5     ; d5<- length of Src form line
     mulu      d5,d4               ; d4<- byte offset to (0, Ymin)
     add.l     d4,a0               ; a0-> (0, Ymin)

     move.w    SRC_NXWD(a4),d4;    d4<- offset between consecutive
     move.w    d4,Src_Xinc(a5)     ;      words in Src plane

     mulu      d4,d0          ; d0<- offset to word containing Xmin
     add.l     d0,a0          ; a0-> 1st src word (Xmin, Ymin)

* Src_Yinc is the offset in bytes from the last word of one Source
* line to the first word of the next Source line

     mulu      d4,d1               ; d1<- width of src line in bytes
     sub.w     d1,d5               ; d5<- value added to ptr at end
     move.w    d5,Src_Yinc(a5)     ; of line to reach start of next

* Calculate Destination starting address

     move.l    DST_FORM(a4),a1     ; a1-> start of dst form
     move.w    DST_YMIN(a4),d4     ; d4<- offset in lines to dst Ymin
     move.w    DST_NXLN(a4),d5     ; d5<- width of dst form

     mulu      d5,d4     ; d4<- byte offset to (0, Ymin)
     add.l     d4,a1     ; a1-> dst (0, Ymin)

     move.w    DST_NXWD(a4),d4     ; d4<- offset between consecutive
     move.w    d4,Dst_Xinc(a5)     ;  words in dst plane

     mulu      d4,d2               ; d2<- DST_NXWD * (DST_XMIN/16)
     add.l     d2,a1               ; a1-> 1st dst word (Xmin, Ymin)

* Calculate Destination Yinc

     mulu      d4,d3               ; d3<- width of dst line - DST_NXWD
     sub.w     d3,d5               ; d5<- value added to dst ptr at
     move.w    d5,Dst_Yinc(a5)     ;  end of line to reach next line

* The low nibble of the difference in Source and Destination alignment
* is the skew value.  Use the skew flag index to reference FXSR and
* NFSR states in skew flag table.

     and.b     #$0F,d7                  ; d7<- isolated skew count
     or.b      skew_flags(pc,d6.w),d7 ; d7<- necessary flags and skew
     move.b    d7,Skew(a5)              ; load Skew register  

     move.b    #mHOP_Source,HOP(a5)     ; set HOP to source only
     move.b    #3,OP(a5)           ; set OP to "replace" mode

     lea       Line_Num(a5),a2     ; fast refer to Line_Num register
     move.b    #fLineBusy,d2       ; fast refer to LineBusy flag
     move.w    PLANES(a4),d7       ; d7 <- plane counter
     bra       begin

*    T h e   s e t t i n g   o f   s k e w   f l a g s
*
*
* QUALIFIERS   ACTIONS           BITBLT DIRECTION: LEFT -> RIGHT
*
* equal Sx&F>
* spans Dx&F FXSR NFSR
*
* 0     0     0    1 |..ssssssssssssss|ssssssssssssss..|  
*   |......dddddddddd|dddddddddddddddd|dd..............|  
*  
* 0     1     1    0 |..dddddddddddddd|dddddddddddddd..|
*   |......ssssssssss|ssssssssssssssss|ss..............|  
*  
* 1     0     0    0 |..ssssssssssssss|ssssssssssssss..|  
*                    |...ddddddddddddd|ddddddddddddddd.|  
*  
* 1     1     1    1 |...sssssssssssss|sssssssssssssss.|  
*                    |..dddddddddddddd|dddddddddddddd..|  


skew_flags:

     dc.b mSkewNFSR           ; Source span < Destination span
     dc.b mSkewFXSR           ; Source span > Destination span
     dc.b 0                   ; Spans equal Shift Source right
     dc.b mSkewNFSR+mSkewFXSR ; Spans equal Shift Source left

* When Destination span is but a single word ...

     dc.b 0         ; Implies a Source span of no words
     dc.b mSkewFXSR ; Source span of two words
     dc.b 0         ; Skew flags aren't set if Source and
     dc.b 0         ; Destination spans are both one word

next_plane:
     move.l    a0,Src_Addr(a5)     ; load Source pointer to this plane

     move.l    a1,Dst_Addr(a5)     ; load Dest ptr to this plane  
     move.w    HEIGHT(a4),Y_Count(a5)   ; load the line count  

     move.b    #mLineBusy,(a2)     ; <<< start the BLiTTER >>>  

     add.w     SRC_NXPL(a4),a0     ; a0-> start of next src plane  
     add.w     DST_NXPL(a4),a1     ; a1-> start of next dst plane  


* The BLiTTER is usually operated with the HOG flag cleared.
* In this mode the BLiTTER and the ST's cpu share the bus equally,
* each taking 64 bus cycles while the other is halted.  This mode
* allows interrupts to be fielded by the cpu while an extensive
* BitBlt is being processed by the BLiTTER.  There is a drawback in
* that BitBlts in this shared mode may take twice as long as BitBlts
* executed in hog mode.  Ninety percent of hog mode performance is
* achieved while retaining robust interrupt handling via a method
* of prematurely restarting the BLiTTER.  When control is returned
* to the cpu by the BLiTTER, the cpu immediately resets the BUSY
* flag, restarting the BLiTTER after just 7 bus cycles rather than
* after the usual 64 cycles.  Interrupts pending will be serviced
* before the restart code regains control.  If the BUSY flag is
* reset when the Y_Count is zero, the flag will remain clear
* indicating BLiTTER completion and the BLiTTER won't be restarted.
*
* (Interrupt service routines may explicitly halt the BLiTTER
* during execution time critical sections by clearing the BUSY flag.
* The original BUSY flag state must be restored however, before
* termination of the interrupt service routine.)

restart:
     bset.b    d2,(a2)        ; Restart BLiTTER and test the BUSY
     nop                      ; flag state.  The "nop" is executed
     bne  restart             ; prior to the BLiTTER restarting.
*                             ; Quit if the BUSY flag was clear.  

begin:
     dbra d7,next_plane
     rts

