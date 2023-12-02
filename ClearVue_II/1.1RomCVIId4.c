/* RasterOps Board Declaration ROM */
/* ClearVue/II, Version 1.0  1024X768-72Hz  1 Bit only */
/* Written in Aztec C, version 3.4 by Jim Huffman */
/* Fri Jan 27, 1989 09:40:38 */
/* ClearVue/II, Version 1.1  1024X768-72Hz  1 Bit only */
/* Written in Aztec C, version 3.6 by Jim Huffman */
/* Monday, July 30, 1990 5:31:05 PM */
#define _DRIVER           ;tells the compiler that we are doing a driver
/* To compile each version, set appropriate define and equate to 1 */
/* or all to 0 for standard ClearVue/II */
#define TESTING 0
/* EQUs must be set to match defines above */
#if TESTING
#asm
TESTING EQU 1
#endasm
#else
#asm
TESTING EQU 0
#endasm
#endif
#asm
;*************************************************************
;Macros
;*************************************************************
;=============================================================
; Offset List Entry
;=============================================================
    MACRO  OSLstEntry
X%2
      DC.L          (%1<<24)+%2-X%2
    ENDM
;=============================================================
; Data List Entry
;=============================================================
    MACRO  DatLstEntry
      DC.L          (%1<<24)+%2
    ENDM
#endasm
/* sResource Directory for Standard ClearVue/II */
#asm
    public  directory
directory
    OSLstEntry  1,boardsreslist       ; Board sResource List Offset
    OSLstEntry  $80,mysreslist1024    ; My sResource List 1024 Offset
    DatLstEntry $FF,0                 ; End
#endasm
/* Board sResource List */
#asm
boardsreslist
    OSLstEntry  1,boardtype     ; Board sResource Type Format Offset
    OSLstEntry  2,boardname     ; Board sResource Name Offset
    DatLstEntry $20,$01BF       ; Board ID RasterOps ClearVue/II id
    OSLstEntry  $22,primaryinit ; Primary Initialization Code seBlock Offset
    OSLstEntry  $24,vendorinfo  ; Vendor Info List Offset
    DatLstEntry $FF,0           ; End
#endasm
/* Board sResource Type Format */
#asm
boardtype
    dc.w  1        ; Category: CatBoard
    dc.w  0        ; Type:     TypBoard
    dc.w  0        ; DrvrSw:   0 for Board
    dc.w  0        ; DrvrHw:   0 for Board
#endasm
/* Board sResource Name */
#asm
boardname          ; Official Product Name
    dc.b  'RasterOps ClearVue/II'
    dc.w  0        ; For Alignment
#endasm
/* Primary Initialization Code seBlock */
#asm
primaryinit
;
; ==================BEGINNING OF PRIMARY INIT BLOCK=====================
;
    dc.l  endprimaryinit-primaryinit        ; Length of seBlock
    dc.b  2                                 ; Revision Level 2 (The Slot Manager REQUIRES this to be 2!)
    dc.b  2                                 ; CPU ID 2 (68020)
    dc.w  0                                 ; Reserved
    dc.l  4                                 ; Code Offset 4  (In other words, next!)
;
; INIT CODE
; On Entry:  A0 -> Slot Manager SEBlock
;
; Convert the slot byte to $Fss00000
    movem.l a0-a5/d0-d7,-(sp)   ; save nearly all registers
    MOVE    #1,2(A0)            ; Set the Primary Init Status Field (in the SEBlock
                                ; pointed to by A0) to positive (no error)
    MOVE.L  A0,A3               ; Store the pointer away for later restoration
                                ; We now need to create a $Fss00000 out of the seSlot field in the SEBlock:
    MOVEQ   #0,D0               ; Zero all of D0
    MOVE.B  (A0),D0             ; Grab the seSlot byte (range=$09-$0E)
    LSL     #4,D0               ; Shove it into the high nibble ($s0)
    OR.B    (A0),D0             ; Or it with its previous self to get $ss
    ORI     #$F00,D0            ; Or to get $Fss
    SWAP    D0                  ; Now get $0Fss0000
    LSL.L   #4,D0               ; And finally have $Fss00000
    MOVE.L  D0,A2               ; Stow it away
    MOVE.L  A2,-(SP)            ; Toss screenbase onto the stack
    JSR     _init1024           ; JSR to the 1024x768 init routine
    JSR     wait_one            ; JSR to the 1ms delay routine
    JSR     _gray1024           ; JSR to the 1024x768 screengray routine
    LEA     4(SP),SP            ; Repair the stack
    movem.l (sp)+,a0-a5/d0-d7   ; restore nearly all registers
  RTS
wait_one
    CLR.L   D0
    MOVE.W  $D00,D0             ; Get TimeDBRA Global
more_dbras                      ; Loop for 1 ms
    DBRA    D0,more_dbras
    RTS
#endasm
init1024(base)               /* 1024x768 Screen Init Routine 60 Hz Repeat */
unsigned long base;
{
  register unsigned long *ptr,i,j; 
  ptr = (unsigned long *)(base);
  *((unsigned long *)&((unsigned char *)ptr)[0x000]) = 0x05;  /*  0  Horizontal End Sync */
  *((unsigned long *)&((unsigned char *)ptr)[0x080]) = 0;
  *((unsigned long *)&((unsigned char *)ptr)[0x100]) = 0x0E;  /*  1  Horizontal End Blank */
  *((unsigned long *)&((unsigned char *)ptr)[0x180]) = 0;
  *((unsigned long *)&((unsigned char *)ptr)[0x004]) = 0x4E;  /*  2  Horizontal Start Blank */
  *((unsigned long *)&((unsigned char *)ptr)[0x084]) = 0;
  *((unsigned long *)&((unsigned char *)ptr)[0x104]) = 0x53;  /*  3  Horizontal Total */
  *((unsigned long *)&((unsigned char *)ptr)[0x184]) = 0;
  *((unsigned long *)&((unsigned char *)ptr)[0x008]) = 0x02;  /*  4  Vertical End Sync */
  *((unsigned long *)&((unsigned char *)ptr)[0x088]) = 0;
  *((unsigned long *)&((unsigned char *)ptr)[0x108]) = 0x4D;  /*  5  Vertical End Blank */
  *((unsigned long *)&((unsigned char *)ptr)[0x188]) = 0;
  *((unsigned long *)&((unsigned char *)ptr)[0x00C]) = 0x4D;  /*  6  Vertical Start Blank */
  *((unsigned long *)&((unsigned char *)ptr)[0x08C]) = 0x03;
  *((unsigned long *)&((unsigned char *)ptr)[0x10C]) = 0x78;  /*  7  Vertical Total */
  *((unsigned long *)&((unsigned char *)ptr)[0x18C]) = 0x03;
  *((unsigned long *)&((unsigned char *)ptr)[0x010]) = 0x04;  /*  8  Display Update */
  *((unsigned long *)&((unsigned char *)ptr)[0x090]) = 0;
  *((unsigned long *)&((unsigned char *)ptr)[0x110]) = 0;     /*  9  Display Start */
  *((unsigned long *)&((unsigned char *)ptr)[0x190]) = 0;
  *((unsigned long *)&((unsigned char *)ptr)[0x014]) = 0;     /*  A  Vertical Interrupt */
  *((unsigned long *)&((unsigned char *)ptr)[0x094]) = 0;
  *((unsigned long *)&((unsigned char *)ptr)[0x114]) = 0x80;  /*  B  Control Register 1 */
  *((unsigned long *)&((unsigned char *)ptr)[0x194]) = 0x10;
  *((unsigned long *)&((unsigned char *)ptr)[0x018]) = 0;     /*  C  Control Register 2 */
  *((unsigned long *)&((unsigned char *)ptr)[0x098]) = 0x28;
}
gray1024(base)               /* 1024X768 Gray Screen Routine */
unsigned long base;
{
  register unsigned long *ptr,i,j; 
    /* Gray the screen in 1 bit. */
  /* clear whole memory width */
  ptr = (unsigned long *)(base+0x40000);
  for (i=0;i<386;i++)
  {
    for (j=0;j<32;j++)
      *ptr++ = 0xAAAAAAAA;
    for (j=0;j<32;j++)
      *ptr++ = 0x55555555;
  }
  show_version(base);
  show_logo(base);
}
show_version(base)
unsigned long base;
{
  unsigned char   *to, *bm, c;
  short   s, j, k;
  extern unsigned char rommbm;
  
  /* Draw ROM Version */
  to = (unsigned char *)(base+0x40000+128*9+124);  /* Start 32 pixels from the left side, 9 rows down. */
/*  to = (unsigned char *)(base+0x40000+128*9+4);  /* Start 32 pixels from the right side, 9 rows down. */
  bm = &rommbm;
  /* Draw the version in 1 bit */
  for (s=0;s<9;s++)
  {
    for (j=0;j<3;j++)
    {
      *to++ = *bm++;
    }
    to += 128-3;
  }
}
show_logo(base)
unsigned long base;
{
  unsigned char   *to, *bm, c;
  short   s, j, k;
  extern unsigned char rologobm;
  
  /* Draw ROM Version */
  to = (unsigned char *)(base+0x40000+(unsigned long)128*363+(128-31)/2);  /* Centered */
  bm = &rologobm;
  /* Draw the version in 1 bit */
  for (s=0;s<3;s++) /* 3 lines of white above */
  {
    for (j=0;j<31;j++)
    {
      *to++ = 0;
    }
    to += 128-31;
  }
  for (s=0;s<37;s++)  /* 37 lines of logo black on white */
  {
    for (j=0;j<31;j++)
    {
      *to++ = *bm++;
    }
    to += 128-31;
  }
  for (s=0;s<3;s++) /* 3 lines of white below */
  {
    for (j=0;j<31;j++)
    {
      *to++ = 0;
    }
    to += 128-31;
  }
}
#asm
_rologobm
;
; RasterOps Logo BitMap
;
; 31 Bytes wide
; 37 Lines high
  DC.B    $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$FC,$00,$00,$00,$00,$00
  DC.B    $00,$00,$00,$00,$00,$00,$00,$0F,$C0,$00,$00,$00,$00
  DC.B    $00,$7F,$FF,$FC,$00,$00,$00,$00,$00,$00,$00,$01,$FC,$00,$00,$00,$00,$00
  DC.B    $00,$00,$00,$00,$FF,$80,$00,$0F,$C0,$00,$00,$00,$00
  DC.B    $00,$7F,$FF,$FF,$00,$00,$00,$00,$00,$00,$00,$01,$FC,$00,$00,$00,$00,$00
  DC.B    $00,$00,$00,$07,$FF,$E0,$00,$1F,$80,$00,$00,$00,$00
  DC.B    $00,$0F,$FF,$FF,$C0,$00,$00,$00,$00,$00,$00,$01,$FC,$00,$00,$00,$00,$00
  DC.B    $00,$00,$00,$1F,$FF,$F0,$00,$1F,$80,$00,$00,$00,$00
  DC.B    $00,$07,$FC,$3F,$E0,$00,$00,$00,$00,$00,$00,$01,$F8,$00,$00,$00,$00,$00
  DC.B    $00,$00,$00,$7F,$87,$F8,$00,$1F,$80,$00,$00,$00,$00
  DC.B    $00,$07,$F8,$0F,$F0,$00,$3C,$FE,$00,$1F,$E0,$03,$F8,$00,$00,$FE,$00,$1E
  DC.B    $00,$E0,$00,$FE,$01,$FC,$00,$FF,$F8,$00,$03,$FC,$00
  DC.B    $00,$0F,$F8,$0F,$F0,$01,$FE,$FE,$00,$7F,$FC,$3F,$FF,$E0,$07,$FF,$80,$7F
  DC.B    $03,$F0,$01,$FC,$01,$FC,$07,$FF,$FF,$00,$0F,$FF,$80
  DC.B    $00,$0F,$F0,$07,$F8,$07,$FF,$FE,$00,$FF,$FF,$3F,$FF,$C0,$1F,$FF,$C0,$FF
  DC.B    $87,$F0,$03,$F8,$00,$FE,$0F,$FF,$1F,$C0,$1F,$FF,$E0
  DC.B    $00,$0F,$F0,$07,$F8,$0F,$F3,$FC,$00,$FC,$FF,$7F,$FF,$C0,$3F,$CF,$C1,$FF
  DC.B    $8F,$F8,$07,$F0,$00,$FE,$0E,$7F,$07,$E0,$1F,$9F,$E0
  DC.B    $00,$0F,$F0,$07,$F8,$1F,$C1,$FC,$01,$F8,$3F,$07,$F0,$00,$7F,$87,$E3,$FF
  DC.B    $9F,$F8,$0F,$F0,$00,$FE,$00,$7F,$07,$F0,$3F,$07,$E0
  DC.B    $00,$1F,$F0,$07,$F8,$3F,$81,$FC,$01,$F8,$1F,$07,$F0,$00,$FF,$07,$E7,$3F
  DC.B    $BB,$F8,$1F,$E0,$00,$FF,$00,$7F,$03,$F0,$3F,$03,$E0
  DC.B    $00,$1F,$E0,$07,$F8,$7F,$01,$FC,$01,$FC,$0E,$07,$F0,$01,$FE,$07,$EE,$3F
  DC.B    $F1,$F8,$1F,$E0,$00,$FF,$00,$7E,$03,$F8,$3F,$81,$C0
  DC.B    $00,$1F,$E0,$0F,$F0,$7F,$03,$F8,$01,$FE,$06,$07,$E0,$01,$FE,$07,$FC,$3F
  DC.B    $E1,$F8,$3F,$C0,$00,$FF,$00,$FE,$03,$F8,$3F,$C0,$C0
  DC.B    $00,$1F,$E0,$0F,$F0,$FE,$03,$F8,$01,$FF,$00,$0F,$E0,$03,$FC,$0F,$D8,$3F
  DC.B    $C1,$F0,$3F,$C0,$00,$FF,$00,$FE,$03,$F8,$3F,$E0,$00
  DC.B    $00,$3F,$E0,$1F,$E0,$FE,$03,$F8,$00,$FF,$80,$0F,$E0,$03,$FC,$0F,$C0,$7F
  DC.B    $80,$E0,$7F,$C0,$00,$FF,$00,$FE,$03,$F8,$1F,$F0,$00
  DC.B    $00,$3F,$C0,$1F,$C1,$FC,$03,$F8,$00,$FF,$C0,$0F,$E0,$07,$F8,$1F,$80,$7F
  DC.B    $80,$00,$7F,$80,$00,$FF,$00,$FC,$03,$F8,$1F,$F8,$00
  DC.B    $00,$3F,$C0,$3F,$81,$FC,$07,$F0,$00,$7F,$E0,$0F,$C0,$07,$F8,$7E,$00,$7F
  DC.B    $00,$00,$7F,$80,$01,$FF,$01,$FC,$03,$F8,$0F,$FC,$00
  DC.B    $00,$3F,$C0,$7F,$03,$FC,$07,$F0,$00,$3F,$F0,$1F,$C0,$07,$FB,$F8,$00,$7F
  DC.B    $00,$00,$FF,$80,$01,$FF,$01,$FC,$03,$F8,$07,$FE,$00
  DC.B    $00,$7F,$C0,$FE,$03,$F8,$07,$F0,$00,$1F,$F8,$1F,$C0,$0F,$FF,$C0,$00,$FE
  DC.B    $00,$00,$FF,$00,$01,$FE,$01,$FC,$07,$F0,$03,$FF,$00
  DC.B    $00,$7F,$83,$F8,$03,$F8,$0F,$F0,$00,$0F,$F8,$1F,$C0,$0F,$FE,$00,$00,$FE
  DC.B    $00,$00,$FF,$00,$01,$FE,$01,$F8,$07,$F0,$01,$FF,$00
  DC.B    $00,$7F,$9F,$E0,$03,$F8,$0F,$E0,$00,$07,$FC,$1F,$80,$0F,$F0,$00,$00,$FE
  DC.B    $00,$01,$FF,$00,$03,$FE,$03,$F8,$07,$F0,$00,$FF,$80
  DC.B    $00,$7F,$FF,$C0,$03,$F8,$1F,$E0,$C6,$03,$FC,$3F,$83,$0F,$F0,$00,$C0,$FE
  DC.B    $00,$01,$FF,$00,$03,$FC,$03,$F8,$0F,$E0,$C0,$7F,$80
  DC.B    $00,$FF,$FF,$E0,$03,$F8,$3F,$E1,$C7,$01,$FC,$3F,$87,$0F,$F0,$01,$C1,$FC
  DC.B    $00,$01,$FE,$00,$03,$FC,$03,$F8,$0F,$E0,$E0,$3F,$80
  DC.B    $00,$FF,$0F,$E0,$03,$F8,$7F,$E3,$8F,$80,$FC,$3F,$8E,$0F,$F8,$03,$81,$FC
  DC.B    $00,$01,$FE,$00,$07,$FC,$03,$F0,$1F,$C1,$F0,$1F,$80
  DC.B    $00,$FF,$0F,$F0,$03,$FC,$EF,$E7,$0F,$C0,$FC,$3F,$9C,$0F,$F8,$07,$01,$FC
  DC.B    $00,$01,$FE,$00,$07,$F8,$07,$F0,$1F,$C1,$F8,$1F,$80
  DC.B    $00,$FF,$0F,$F0,$03,$FF,$CF,$FE,$1F,$E0,$F8,$3F,$F8,$07,$FE,$1E,$01,$FC
  DC.B    $00,$01,$FE,$00,$07,$F8,$07,$F8,$3F,$83,$FC,$1F,$00
  DC.B    $01,$FF,$07,$F0,$01,$FF,$8F,$FC,$1F,$F1,$F8,$3F,$F0,$07,$FF,$FC,$03,$F8
  DC.B    $00,$01,$FE,$00,$0F,$F0,$07,$FC,$FF,$03,$FE,$3F,$00
  DC.B    $01,$FE,$07,$F8,$01,$FF,$0F,$F8,$1F,$FF,$F0,$1F,$E0,$03,$FF,$F0,$03,$F8
  DC.B    $00,$01,$FE,$00,$0F,$F0,$07,$FF,$FE,$03,$FF,$FE,$00
  DC.B    $01,$FE,$07,$F8,$00,$FC,$07,$E0,$07,$FF,$E0,$1F,$80,$01,$FF,$C0,$03,$F8
  DC.B    $00,$00,$FE,$00,$1F,$E0,$0F,$EF,$F8,$00,$FF,$FC,$00
  DC.B    $01,$FE,$03,$F8,$00,$70,$03,$80,$00,$FF,$80,$0E,$00,$00,$7E,$00,$03,$F8
  DC.B    $00,$00,$FE,$00,$1F,$C0,$0F,$E3,$C0,$00,$1F,$F0,$00
  DC.B    $03,$FE,$03,$FC,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
  DC.B    $00,$00,$FE,$00,$3F,$80,$0F,$C0,$00,$00,$00,$00,$00
  DC.B    $03,$FC,$03,$FC,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
  DC.B    $00,$00,$7F,$00,$7F,$00,$0F,$C0,$00,$00,$00,$00,$00
  DC.B    $03,$FC,$01,$FC,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
  DC.B    $00,$00,$7F,$00,$FE,$00,$1F,$C0,$00,$00,$00,$00,$00
  DC.B    $07,$FC,$01,$FE,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
  DC.B    $00,$00,$3F,$C3,$FC,$00,$1F,$80,$00,$00,$00,$00,$00
  DC.B    $0F,$FE,$01,$FF,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
  DC.B    $00,$00,$1F,$FF,$F0,$00,$3F,$C0,$00,$00,$00,$00,$00
  DC.B    $7F,$FF,$C0,$FF,$E0,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
  DC.B    $00,$00,$07,$FF,$C0,$01,$FF,$F8,$00,$00,$00,$00,$00
  DC.B    $7F,$FF,$C0,$FF,$E0,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
  DC.B    $00,$00,$00,$FE,$00,$01,$FF,$F8,$00,$00,$00,$00,$00
_rommbm
; 3 Bytes wide
; 9 Lines high   1.0
  DC.B    $00,$00,$00
  DC.B    $10,$07,$00
  DC.B    $30,$08,$80
  DC.B    $10,$08,$80
  DC.B    $10,$08,$80
  DC.B    $10,$08,$80
  DC.B    $10,$08,$80
  DC.B    $38,$87,$00
  DC.B    $00,$00,$00
  DC.W    $00            ; For alignment
#endasm
#asm
; ==================END OF PRIMARY INIT BLOCK=====================
endprimaryinit
#endasm
/* Vendor Info List */
#asm
vendorinfo
    OSLstEntry  1,vendordesign    ; Vendor Design ID Offset
    OSLstEntry  3,cardrevision    ; Card's Revision Level Offset
    OSLstEntry  4,cardpartnumber  ; Card Part Number Offset
    DatLstEntry $FF,0             ; End
#endasm
/* Actual Vendor Info */
#asm
vendordesign
    dc.b  'RasterOps'
    dc.w  0            ; For Alignment
cardrevision
    dc.b  'ROM Version: 1.0'
    dc.w  0            ; For Alignment
cardpartnumber
    dc.b  '410'
    dc.w  0            ; For Alignment
#endasm
/* My sResource List 1024 */
#asm
mysreslist1024
    OSLstEntry  1,mytype               ; My sResource Type Format Offset
    OSLstEntry  2,myname               ; My sResource Name Offset
    OSLstEntry  4,mydrvrdir            ; My sResource Driver Directory Offset
    DatLstEntry 8,1                    ; sRsrcHWDevId = 1
    OSLstEntry  $A,minorbase           ; MinorBase Offset
    OSLstEntry  $B,minorlen            ; MinorLength Offset
    OSLstEntry  $80,bit1parmlist1024   ; One-Bit-Per-Pixel Parameter List Offset
    DatLstEntry $FF,0                  ; End
#endasm
#asm
DrHwRasterOpsCB108    EQU $0120
DrHwRasterOpsCB100N   EQU $011C
DrHwRasterOpsCB100P   EQU $011D
DrHwRasterOpsCB100PUK EQU $011E
DrHwRasterOpsCVII     EQU $013C
CatDisplay            EQU     3
TypVideo              EQU     1
DrSwApple             EQU     1
DrHwTFB               EQU     1
#endasm
/* My sResource Type Format */
#asm
mytype
    dc.w  CatDisplay           ; Category:
    dc.w  TypVideo             ; Type:
    dc.w  DrSwApple            ; DrvrSw:
    dc.w  DrHwRasterOpsCVII    ; DrvrHw:
#endasm
  
/* My sResource Name */
#asm
myname
    dc.b  'Display_Video_Apple_RasterOpsCVII'
    dc.w  0        ; For Alignment
#endasm
/* MinorBase */
#asm
minorbase
    dc.l  0        ; no offset from normal beginning of slot space
#endasm
/* MinorLength */
#asm
minorlen
    dc.l  $60000   ; 768 lines * 128 bytes/line of Video RAM + $40000 offset
#endasm
/* One-Bit-Per-Pixel Parameter List */
#asm
bit1parmlist1024
    OSLstEntry  1,bit1parms1024  ; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              ; Number of Pages: 1
    DatLstEntry 4,0              ; Device Type: 0
    DatLstEntry $FF,0            ; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bit1parms1024
    dc.l  endbit1parms1024-bit1parms1024  ; Length of sBlock
    dc.l  $40000                    ; Offset to Page 0 of Video RAM: $40000
    dc.w  $80                       ; RowBytes
    dc.l  0                         ; BoundsRect: (0,0,768,1024) [TLBR]
    dc.l  $03000400                 ;
    dc.w  0                         ; PixMap Version Number
    dc.w  0                         ; unused
    dc.l  0                         ; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 ; Horizontal Res
    dc.l  $00480000                 ; Vertical Res
    dc.w  0                         ; Pixel Type (0=Chunky)
    dc.w  1                         ; Pixel Size
    dc.w  1                         ; Components in Pixel
    dc.w  1                         ; Bits Per Component
    dc.l  0                         ; PlaneBytes Offset
endbit1parms1024
#endasm
/* My sResource Driver Directory */
#asm
mydrvrdir
    OSLstEntry  2,mydrvr            ; My 68020 Driver sBlock Offset
    DatLstEntry $FF,0               ; End
#endasm
/* My 68020 Driver sBlock */
#asm
mydrvr
; ==================BEGINNING OF DRIVER BLOCK=====================
    dc.l  endmydrvr-mydrvr          ; Length of sBlock
#endasm
/* RasterOps ClearVue 10 Video Driver */
#asm
_main
    dc.w    $4C00             ; driver responds to Control and Status, NeedsLock
    dc.w    0                 ; NOT A DA (was "update every x seconds")
    dc.w    0                 ; NOT A DA (was "detect events")
    dc.w    0                 ; NOT A DA (was "menu ID number")
    dc.w    _myopen-_main    ; open routine
    dc.w    _nop-_main     ; prime routine (not needed for this driver)
    dc.w    _control-_main ; control routine
    dc.w    _status-_main  ; status routine
    dc.w    _myclose-_main   ; close routine
    dc.b    _titleend-_title
_title
                 ;  Be sure to use this format:  "RasterOps VVV BBBBB xxx..."
                 ;  Where VV = Version number of the driver,
                 ;        BBBBB = Board model
                 ;        xxx... = Anything else you want to say.
                 ;  The "Ops ", and BBBBB are checked by the 24-bit environment installer
                 ;  to determine if this hardware can support that environment, so be
                 ;  sure to include them in this format if you want the environment to
                 ;  recognize your hardware.
    dc.b    ".RasterOps 1.0 ClearVue/II  Video Driver"
    
_titleend
    dc.w      0                ;for alignment
_save
    move.l    8(sp),a2
    move.l    a0,(a2)        ; save pb pointer
    move.l    4(sp),a2
    move.l    a1,(a2)        ; save DCE pointer
    rts
_mysintinstall               ; Had to do this myself due to bug in library
    move.w    8(sp),d0
    move.l    4(sp),a0
    dc.w      $A075          ; SIntInstall
    rts
_mysintremove                ; Had to do this myself due to bug in library
    move.w    8(sp),d0
    move.l    4(sp),a0
    dc.w      $A076          ; SIntRemove
    rts
_checkiodone
   clr.l   d0            ; Zero return error code for now
   BTST    #1,6(A0)      ; Check ioTrap field of the paramblock if it's asynch
;   BTST    #9,8(A0)      ; Check ioTrap field of the paramblock if it's asynch
   BEQ.S   _goiodone     ; It's an asynch call, so use jIODone
   RTS                   ; Go back for a normal synchronous return
_goiodone
   add.l   #4,sp         ; Pop our return address away
   unlk    a6            ; Unlink the subroutine (Return address is now on top of stack)
   MOVEA.L $8FC,A0       ; Load address of jIODone routine
   JMP     (A0)          ; Use it to exit with
#endasm
typedef struct controlparam
{
  ParamBlockHeader;
  short ioRefNum;
  short csCode;
  long csParam;
} controlparam;
typedef struct mystorage
{
  SlotIntQElement *myslotqeleptr;
  unsigned char *myintrptcode;
  unsigned short bwmapping;
  unsigned short mode;
  unsigned short screensize;
  unsigned long  screenbase;
} mystorage;
myopen()
{
  AuxDCEPtr dcep;            /* Auxiliary Device Control Entry pointer. */
  controlparam *pbp;         /* Application-passed parameter block pointer. */
  THz oldzone;               /* Previous heap zone */
  long merror;               /* Memory error */
  SlotIntQElement *sqeptr;   /* Slot queue element pointer */
  extern long intrpthandler, /* Define the interrupt handling routine as external; */
              intrptend;     /* As well as the end of the interrupt handler. */
#asm
    movem.l    a0-a5/d1-d7,-(sp)  ; save nearly all registers
#endasm
  save(&dcep,&pbp);      /* A0 -> pbp, A1 -> dcep */
  oldzone = GetZone();             /* Get current heap zone */
  SetZone(SystemZone());           /* Force memory operations to the System Heap. */
  if (!(dcep->dCtlStorage = NewHandle((long)sizeof(struct mystorage))))  /* I'm only using a pointer here instead of a handle. */
  {
    SetZone(oldzone);              /* Force memory operations to the original heap. */
#asm
    movem.l    (sp)+,a0-a5/d1-d7   ; restore nearly all registers
#endasm
    return(-23);                   /* Return that we couldn't open successfully. */
  }
  /* ----------------------------Install Interrupts------------------------------*/
  ((struct mystorage *)(*(dcep->dCtlStorage)))->myslotqeleptr = sqeptr;
  if (!(((struct mystorage *)(*(dcep->dCtlStorage)))->myintrptcode =
     (unsigned char *)NewPtr((unsigned long)&intrptend-(unsigned long)&intrpthandler)))
  {
    SetZone(oldzone);              /* Force memory operations to the original heap. */
    DisposHandle(dcep->dCtlStorage);
#asm
    movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
#endasm
    return(-23);                   /* Return that we couldn't open successfully. */
  }
  
    /* Copy the code from ourself to a separate pointer block.  That way,
       if the driver needs to be replaced, (as when the 24-bit environment is installed)
       then interrupts never have to be altered since the code is external from
       the old driver (this one) that would be removed in such a replacement.
       [Of course, a pointer to the external block is stored in the external
        variable section block (dcep->dCtlStorage) so you can still find it if
        you do, in fact, need to alter it.] */
  BlockMove(&intrpthandler,((struct mystorage *)(*(dcep->dCtlStorage)))->myintrptcode,
     (unsigned long)&intrptend-(unsigned long)&intrpthandler);
  if (!(sqeptr = (SlotIntQElement *)NewPtr((long)sizeof(SlotIntQElement))))
  {
    SetZone(oldzone);              /* Force memory operations to the original heap. */
#asm
    movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
#endasm
    DisposPtr(((struct mystorage *)(*(dcep->dCtlStorage)))->myintrptcode);
    DisposHandle(dcep->dCtlStorage);
    return(-23);                   /* Return that we couldn't open successfully. */
  }
  SetZone(oldzone);                /* Force memory operations to the original heap. */
    /* Set up the fields of the slot queue element block. */
  sqeptr->sqLink = 0;
  sqeptr->sqType = 6;
  sqeptr->sqPrio = 0;
  sqeptr->sqAddr = (ProcPtr)((struct mystorage *)(*(dcep->dCtlStorage)))->myintrptcode;
  sqeptr->sqParm = dcep->dCtlDevBase;
    /* Install that slot queue element into the interrupt table. */
  if(mysintinstall(sqeptr,dcep->dCtlSlot))
  {
#asm
    movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
#endasm
    SetZone(oldzone);              /* Force memory operations to the original heap. */
    DisposPtr(sqeptr);
    DisposPtr(((struct mystorage *)(*(dcep->dCtlStorage)))->myintrptcode);
    DisposHandle(dcep->dCtlStorage);
    return(-23);                   /* Return that we couldn't open successfully. */
  }
    /* Turn interrupts on. */
    *(unsigned long *)(((unsigned long)(dcep->dCtlDevBase)) + 0x00194) = 0x14;
    /* -----------------------------End Install Interrupts------------------------------ */
    /* Set up our private storage variables. */
  ((struct mystorage *)(*(dcep->dCtlStorage)))->screensize = 1024;
  ((struct mystorage *)(*(dcep->dCtlStorage)))->screenbase = ((unsigned long)(dcep->dCtlDevBase))+(unsigned long)0x40000;
  ((struct mystorage *)(*(dcep->dCtlStorage)))->mode = 0x80;
  ((struct mystorage *)(*(dcep->dCtlStorage)))->bwmapping = 0;
    /* All done.  Hop out. */
#asm
    movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
#endasm
  return(0);             /* Successful Open */
}
/* This routine is run whenever the driver is told to close. */
myclose()
{
  AuxDCEPtr dcep;        /* Auxiliary Device Control Entry pointer. */
  controlparam *pbp;     /* Application-passed parameter block pointer. */
#asm
    movem.l    a0-a5/d1-d7,-(sp)  ; save nearly all registers
#endasm
  save(&dcep,&pbp);      /* A0 -> pbp, A1 -> dcep */
    /* Turn interrupts off. */
   *(unsigned long *)(((unsigned long)(dcep->dCtlDevBase)) + 0x00194) = 0x10;
    /* Pull interrupts out. */
  mysintremove(((struct mystorage *)(*(dcep->dCtlStorage)))->myslotqeleptr,dcep->dCtlSlot);
    /* Nuke our slot queue element block. */
  DisposPtr(((struct mystorage *)(*(dcep->dCtlStorage)))->myslotqeleptr);
    /* Nuke our interrupt code block. */
  DisposPtr(((struct mystorage *)(*(dcep->dCtlStorage)))->myintrptcode);
    /* Nuke our variable storage block. */
  DisposHandle(dcep->dCtlStorage);
#asm
    movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
#endasm
  return(0);             /* Successful Close */
}
nop()                    /* This routine doesn't do anything!  Neat, huh? */
{
  return(0);             /* Go home and tell mommy all about it. */
}
/* This is the workhorse of the driver.  Control() is called for most of
   the operations a driver needs to perform.  It simply performs the
   action indicated in the controlparam block and returns. */
control()
{
  AuxDCEPtr dcep;        /* Auxiliary Device Control Entry pointer. */
  controlparam *pbp;     /* Application-passed parameter block pointer. */
  register unsigned short mapmode,*modereg;    /* Grayscale or color mapping flag,
                                                  Pointer to the mode register. */
#asm
    movem.l    a0-a5/d1-d7,-(sp)  ; save nearly all registers
#endasm
  save(&dcep,&pbp);      /* A0 -> pbp, A1 -> dcep */
  /* Switch on the type of the type of action we are to repond to or do. */
  switch(pbp->csCode)
  {
    case 0:         /* Reset the video card. (Init) */
        /* Set the return values we are responsible for. */
      ((VDPgInfoPtr)(pbp->csParam))->csMode = 0x80;         /* Return that we're in 1-Bit mode. */
      ((VDPgInfoPtr)(pbp->csParam))->csPage = 0;
      ((VDPgInfoPtr)(pbp->csParam))->csBaseAddr =
                     (Ptr)(((struct mystorage *)(*(dcep->dCtlStorage)))->screenbase);
        /* Set the mode variable in our private storage. */
      ((struct mystorage *)(*(dcep->dCtlStorage)))->mode = 0x80;
      
        /* Reset the hardware to 1-bit mode. */
        /* Gray the screen using 1-bit mode. */
      grayscrn(((struct mystorage *)(*(dcep->dCtlStorage)))->screenbase);
      break;
    case 1:         /* Remove all pending I/O. (KillIO) */
      break;
    case 2:         /* Set the card's video mode. (SetMode) */
        /* Set the mode variable in our private storage. */
      ((struct mystorage *)(*(dcep->dCtlStorage)))->mode = ((VDPgInfoPtr)(pbp->csParam))->csMode;
      
        /* Reset the hardware to the new mode.  The mode can only be 0x80 (1-bit)
           or 0x81 (8-bit), so just AND to get that bit and shift it into place. */
        /* Set the return value we are responsible for. */
      ((VDPgInfoPtr)(pbp->csParam))->csBaseAddr =
                     (Ptr)((struct mystorage *)(*(dcep->dCtlStorage)))->screenbase;
      break;
    case 3:         /* Change card's color lookup table(s). (SetEntries) */
      setlut(((VDSetEntryPtr)(pbp->csParam))->csTable,((VDSetEntryPtr)(pbp->csParam))->csStart,
             ((VDSetEntryPtr)(pbp->csParam))->csCount,dcep);
      break;
    case 4:         /* Change card's gamma table. (SetGamma) */
      break;
    case 5:         /* Gray the video page with dithered gray. (GrayScreen) */
        /* Gray the screen using the current screen size and mode. */
      grayscrn(((struct mystorage *)(*(dcep->dCtlStorage)))->screenbase);
      break;
    case 6:         /* Map color lookup table(s) to color or grayscale. SetGray) */
      ((struct mystorage *)(*(dcep->dCtlStorage)))->bwmapping = ((VDPgInfoPtr)(pbp->csParam))->csMode & 0x0100;
      break;
    case -1:  /* Goodbye condition.  Done when the "GoodBye Kiss" is given. */
      myclose();      /* Clean up things before leaving. */
      break;
  }
#asm
    movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
#endasm
  checkiodone();
}
status()
{
  AuxDCEPtr dcep;        /* Auxiliary Device Control Entry pointer. */
  controlparam *pbp;     /* Application-passed parameter block pointer. */
#asm
    movem.l    a0-a5/d1-d7,-(sp)  ; save nearly all registers
#endasm
  save(&dcep,&pbp);      /* A0 -> pbp, A1 -> dcep */
     /* Switch on the type of the type of action we are to repond to or do. */
  switch(pbp->csCode)
  {
    case 2:   /* Get the card's video mode. (GetMode) */
        /* Set the return values we are responsible for. */
      ((VDPgInfoPtr)(pbp->csParam))->csMode = ((struct mystorage *)(*(dcep->dCtlStorage)))->mode;
      ((VDPgInfoPtr)(pbp->csParam))->csPage = 0;
      ((VDPgInfoPtr)(pbp->csParam))->csBaseAddr =
                     (Ptr)((struct mystorage *)(*(dcep->dCtlStorage)))->screenbase;
      break;
    case 3:   /* Get values from card's color lookup table(s). (GetEntries) */
      getlut(((VDSetEntryPtr)(pbp->csParam))->csTable,((VDSetEntryPtr)(pbp->csParam))->csStart,
             ((VDSetEntryPtr)(pbp->csParam))->csCount,dcep);
      break;
    case 4:   /* Get the total number of video pages on the card. (GetPages) */
      ((VDPgInfoPtr)(pbp->csParam))->csPage = 1;
      break;
    case 5:   /* Get base address of specified page in current mode. (GetBaseAddr) */
        /* Set the return value we are responsible for. */
      ((VDPgInfoPtr)(pbp->csParam))->csBaseAddr =
                     (Ptr)((struct mystorage *)(*(dcep->dCtlStorage)))->screenbase;
      break;
    case 6:   /* Get mapping mode (color or grayscale) of color lookup table(s). (GetGray) */
      ((VDPgInfoPtr)(pbp->csParam))->csMode = ((struct mystorage *)(*(dcep->dCtlStorage)))->bwmapping;
      break;
  }
#asm
    movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
#endasm
  checkiodone();
}
setlut(thetable,start,count,dcep)
unsigned short *thetable;
short start,count;
AuxDCEPtr dcep;        /* Auxiliary Device Control Entry pointer. */
{
  unsigned long *pokepos,dacaddr,timeout; /* -4(A6), -8(A6), -C(A6) */
  register unsigned short color,i;
  register unsigned short *table;
  register unsigned char *dacdata,*clutbackup;
  unsigned short addr;
  extern long intrpthandler,intrdata;
  /* Does nothing ???? */
}
getlut(thetable,start,count,dcep)
unsigned short *thetable;
short start,count;
AuxDCEPtr dcep;        /* Auxiliary Device Control Entry pointer. */
{
  register short color,addr,i;
  register unsigned char *clutbackup;
  register unsigned short *table;
  /* Does nothing ???? */
}
/* Clear the whole screen to gray pattern whatever the bits per pixel and screen size.*/
grayscrn(base)               /* 1024X768 Gray Screen Routine */
unsigned long base;
{
  register unsigned long *ptr,i,j; 
    /* Gray the screen in 1 bit. */
  /* clear whole memory width */
  ptr = (unsigned long *)base;
  for (i=0;i<386;i++)
  {
    for (j=0;j<32;j++)
      *ptr++ = 0xAAAAAAAA;
    for (j=0;j<32;j++)
      *ptr++ = 0x55555555;
  }
}
#asm
;
; Board Interrupt Handler
;
; On entry:  A1 contains the slot base address
;            D0-D3/A0-A3 have already been preserved
;            (but only in native Mac OS, *not* AUX!)
;
_intrpthandler
;    AUX is such a baby that it requires this line anyway.
    MOVEM.L    A0-A5/D1-D7,-(SP)  ; save nearly all registers
    MOVE.L  A1,A0          ; stow slot base address in A0
    MOVE.L  A1,D0          ; stow slot base address in D0
    ADDA.L  #$0118,A0     ; add offset to clear video interrupt (read a long register)
    MOVE.L  (A0),D1        ; clear interrupts
                           ; D0 is currently: $Fssxxxxx, we need: $0000000s
    ROL.L   #8,D0          ; D0 is now: $sxxxxxFs
    ANDI.L  #$F,D0         ; D0 is now: $0000000s, the slot number
    MOVEA.L $D28,A0        ; get the address of the VBL task manager
    JSR     (A0)           ; go service the interrupt with slot number in D0
    MOVEQ   #1,D0          ; signal that the interrupt was serviced
;     Repair registers to make AUX happy.
    MOVEM.L    (SP)+,A0-A5/D1-D7  ; restore nearly all registers
    RTS                    ; run home to mommy-caller
_intrptend
; ==================END OF DRIVER BLOCK=====================
    public endmydrvr
#endasm
