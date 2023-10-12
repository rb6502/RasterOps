
/* ClearVue/LC current software version 1.0 */
/* Last Modified - Wednesday, October 17, 1990 4:31:24 PM */
/* © Raster Ops Corp., 1988, 1989, 1990    All Rights Reserved
   Written:    Thu Jan  4, 1990     Wade D. Eilrich in Aztec C V3.6B
   Modified from the source code for the 108+ V1.4 rom which was written 
   by Wade Eilrich using Aztec C V3.6B.
			   
   Parts of this code were modified from the example driver in the Apple book:
	"Designing Cards and Drivers for Macintosh II and Macintosh SE"
			      
   Changes for ClearVue/LC and beyond Wednesday, October 17, 1990 2:08:33 PM
   by Jim Huffman
			   
*/
/*  Wednesday, October 17, 1990 2:08:45 PM  Version 1.0 ClearVue/LC */
/* **********************      	  CONSTANTS        ******************* */
#define  _DRIVER
#ifndef MAKINGGS
 #define MAKINGGS 0
#endif
#if MAKINGGS
#define MAKINGGS 1
#asm
MAKINGGS EQU 1
#endasm
#else
#asm
MAKINGGS EQU 0
#endasm
#endif
#define TMS34061       0x00040000 		/* 34061 Address */
#define VIDINTERRUPT   0x000400B8 		/* Hi byte of Control1 */
#define UTILADDRESS    0x00080000 		/* Utility Register */
#define SLOTFss        0xFFF00000		/* Slot Fss00000 */
#define VStartBlankLo 0x00040060
#define VStartBlankHi 0x00040068
#define VCountLo      0x00040110
#define VCountHi      0x00040118
#define VTotalLo	  0x00040070
#define VTotalHi	  0x00040078
#define	pix1	0x80    /* 1-bit  per pixel */
#asm
TMS34061	EQU		$00040000
UTILREG		EQU		$00080000	; Utility Register Address
MONMASK     EQU    	$100		; Bit 8 is the monitor present line
OSCASEL		EQU		$0			; Oscillator select bit 0
OSCBSEL		EQU		$1			; Oscillator select bit 1
#endasm
#define grey1a 0xAAAAAAAA  	/* 1-bit, first  half of the dithered gray pattern */ 
#define grey1b 0x55555555  	/* 1-bit, second half of the dithered gray pattern */ 
#define MAXLUT        3	    	/* There are three (RGB) lookup tables associated with each DAC */
#define SCRNWID1024 256     	/* Width of the screen in long integers (1024/4 = 256) */
#define SCRNLEN1024 435     	/* Last row on the 1024 x 870 screen */
#define PIXSTART   0x80		/* Starting mode for the pixel depths (0x80 = 1 bit) */
#define EIGHTBIT      8		/* Shift constant used in LUTtranslate */
#include "zoom.h"
enum OSErrors
{
  controlErr = -17,
  statusErr  = -18,
  openErr    = -23
};
enum ScreenModes
{
  mode1024   = 1024,
  mode640    =  640,
};
/* No interlace */  
enum SetInterrupts
{
  interruptOn      = 0x74,
  interruptLaceOn  = 0x76,
  interruptOff     = 0x70,
  interruptLaceOff = 0x72
};
enum ZoomDefs
{
  x1 = 0,
  x2,
  x4
};
enum panStatusTypes
{
  getPanRate = 8192,	/* GetPanRate()	get the scaling factor for the x/y panning rate.     */
  getSlow,		/* GetSlow()	get the slow panning speed. 			     */
  getFast,		/* GetFast()	get the fast panning speed. 			     */
  getMargin,	/* GetMargin()	get the width (in pixels) of the slow panning area.  */
  getZoom,		/* GetZoom()	get the current zoom state (1 = x1, 2 = x2, 3 = x4.) */
  getRects,		/* GetRects()	get the fast and slow panning rectangles and speeds. */
  getXY,		/* GetXY()      get the currentX and currentY screen positions.	     */
  getAll,		/* GetAll()		get all the various parameters			     */
  getPZMode,	/* GetPZMode()  get the pixel mode				     */
  getPZ			/* GetPZ()		get the pan & zoom enable flag			     */
};
enum panControlTypes
{
  zoomIn = 8192,	/* ZoomIn()	zoom in.     	 	     			     */
  zoomOut,		/* ZoomOut()	zoom out. 			     		     */
  panX,			/* PanX()		pan in the x direction. 	  		     */
  panY,			/* PanY()		pan in the y direction.  	   		     */
  panTo,		/* PanTo()		pan to x,y  			 		     */
  setRects, 	/* SetRects()	set the fast and slow panning rectangles. 	     */
  setXY,		/* SetXY()		set the X,Y coordinates (screen top left)	     */
  setSlow,		/* SetSlow()	set the slow panning rate			     */
  setFast,		/* SetFast()	set the fast panning rate			     */
  setBorder,	/* SetBorder()  set the panning border width			     */
  setPZ,		/* SetPZ()		enable panning and zooming			     */
};
/* Driver storage */
typedef struct mystorage
{
  SlotIntQElement *myslotqeleptr;	/* 768 */
  unsigned char *myintrptcode;		/* 772 */
  unsigned short bwmapping;			/* 776 */
  unsigned short mode;				/* 778 */
  unsigned short pages;				/* 780 */
  unsigned short zoom;				/* 782 */
  unsigned short screensize;		/* 784 */
  unsigned long  screenbase;		/* 786 */
  Boolean InterruptFlag;			/* True if interrupts are enabled, false otherwise		*/
	/* Required for Pan/Zoom */
  short slot;			/* Slot and driver refNum of the video board		*/
  short refNum;
  short currentRate;	/* The proportional value for scaling x/y pan rates 		*/
  short currentZoom;	/* Zoom state: 1 = 1X, 2 = 2X, 3 = 4X 				*/
  short fastSpeed;		/* Fast multiplier for the pan rate 				*/
  short slowSpeed;		/* Slow multiplier for the pan rate 				*/
  short currentX;		/* The value in the pan register 				*/
  short currentY;		/* Aggregate number from the two y-registers 			*/
  short xSize;			/* 1024 x 768, 680 x 870 				*/
  short ySize;
  short theMode;		/* The pixel depth: 0 = 1 bit, 1 = 2 bit, 2 = 4 bit, 3 = 8 bit 	*/
  short border;			/* The border constant which defines the panRect 		*/
  Rect theRect;			/* The rect of our GDevice					*/
  Rect panRect;			/* The border of the active panning area			*/
  Rect currentScreen;		/* The active screen rect 					*/
  Boolean enablePZ;		/* True if pan & zoom are enabled, false otherwise 		*/
  Boolean zCenter;		/* True if screen centered, false if mouse centered zoom 	*/
  Boolean enableVD;		/* True if the enlarge panning option is in effect, else false  */
  short xResolution;	/* Used to hold the screen size if enlarge panning is enabled   */
  short yResolution;	/* Used to hold the screen size if enlarge panning is enabled   */
} mystorage, *mystoragePtr;
#define devBase(slot) ((unsigned long)slot << 20) | 0xFF000000;
/* The structure of PRAM */
typedef char SignedByte;
typedef struct SPRAMRecord
{
  short boardID;
  SignedByte vendorUse1;
  SignedByte vendorUse2;
  SignedByte vendorUse3;
  SignedByte vendorUse4;
  SignedByte vendorUse5;
  SignedByte vendorUse6;
} SPRAMRecord, *SPRAMRecPtr;
  
/* Driver control parameter block for panning rectangles and speeds */
typedef struct panInfoParam
{
  ParamBlockHeader;
  short ioRefNum;
  short csCode;
  Rect fastRect, slowRect;
}panInfoParam, *panInfoParamPtr;
/* Driver control zoom & pan parameter block */
typedef struct zoomCtrlParam
{
  ParamBlockHeader;
  short ioRefNum;
  short csCode;
  short csParam[22];
} zoomCtrlParam, panCtrlParam;
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
; Offset List Entry 1
;=============================================================
    MACRO  OSLstEntry1
A%2
      DC.L          (%1<<24)+%2-A%2
    ENDM
;=============================================================
; Offset List Entry 2 - 1024f640
;=============================================================
    MACRO  OSLstEntry2
B%2
      DC.L          (%1<<24)+%2-B%2
    ENDM
;=============================================================
; Offset List Entry 3 - 2048f870
;=============================================================
    MACRO  OSLstEntry3
C%2
      DC.L          (%1<<24)+%2-C%2
    ENDM
;=============================================================
; Offset List Entry 4 - 4096f870
;=============================================================
    MACRO  OSLstEntry4
D%2
      DC.L          (%1<<24)+%2-D%2
    ENDM
;=============================================================
; Offset List Entry 5 - 8192f870
;=============================================================
    MACRO  OSLstEntry5
E%2
      DC.L          (%1<<24)+%2-E%2
    ENDM
;=============================================================
; Data List Entry
;=============================================================
    MACRO  DatLstEntry
      DC.L          (%1<<24)+%2
    ENDM
#endasm
 
/* **********************   SRESOURCE DIRECTORY    ******************* */
/* sResource Directory for Standard ClearVue/LC  */
#asm
    public  directory
directory
    OSLstEntry  1,boardsreslist       ; Board sResource List Offset
    OSLstEntry  $80,mysreslist1024    ; My sResource List 1024 Offset
    OSLstEntry  $81,mysreslist640     ; My sResource List 640 Offset
    OSLstEntry  $82,mysres1024f1024    ; My sResource List 1024f1024 Offset
    OSLstEntry  $83,mysres1024f640    ; My sResource List 1024f640 Offset
    DatLstEntry $FF,0                 ; End
#endasm
/* Board sResource List */
#asm
boardsreslist
    OSLstEntry  1,boardtype     	; Board sResource Type Format Offset
    OSLstEntry  2,boardname     	; Board sResource Name Offset
    DatLstEntry $20,$0276			; Board ID (ClearVue GS/LC)
    OSLstEntry  $22,primaryinit 	; Primary Initialization Code seBlock Offset
    OSLstEntry  $24,vendorinfo  	; Vendor Info List Offset
    OSLstEntry	$26,secondaryinit 	; Secondary Initialization Code seBlock Offset
    OSLstEntry  65,modenamesdir 	; Video family mode names
    DatLstEntry $FF,0           	; End
#endasm
/* Video family mode names directory */
#asm
modenamesdir
    OSLstEntry	$80,s1024x768
    OSLstEntry	$81,s640x870
 	OSLstEntry	$82,s1024f1024ex	; 1024x1024 Extended DeskTop
	OSLstEntry  $83,s1024f640ex		; 1024x1024 Extended DeskTop
 	DatLstEntry	$FF,0				; End
#endasm
#asm
s1024x768 even
	DC.L ends1024x768-s1024x768
	DC.W 20
	DC.B '1024x768'
	DC.W 0
ends1024x768
s640x870 even
	DC.L ends640x870-s640x870
	DC.W 22
	DC.B '640x870'
	DC.W 0
ends640x870
s1024f1024ex even
	DC.L ends1024f1024ex-s1024f1024ex
	DC.W 24
	DC.B '1024x1024 Extended'
	DC.W 0
ends1024f1024ex
s1024f6400ex even
	DC.L ends1024f640ex-s1024f640ex
	DC.W 25
	DC.B '1024x1024 Extended'
	DC.W 0
ends1024f640ex
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
    dc.b  'RasterOps ClearVue LC'
    dc.w  0        ; For Alignment
#endasm
/*__________________________________________________________________________________________________
   Secondary Initialization Code seBlock
   Look for the new Slot Manager in ROM, look for 32-bit QuickDraw, install/delete the appropriate
   sResource ID(s).
*/
#asm
secondaryinit even
;
; ==================BEGINNING OF SECONDARY INIT BLOCK=====================
;
    dc.l  endsecondaryinit-secondaryinit    ; Length of seBlock
    dc.b  2                                 ; Revision Level 2 (The Slot Manager REQUIRES this to be 2!)
    dc.b  2                                 ; CPU ID 2 (68020)
    dc.w  0                                 ; Reserved
    dc.l  4                                 ; Code Offset 4  (In other words, next!)
; General equates
Slot          EQU    0	; Offset in SeBlock
SlotNum       EQU   49	; Offset in SpBlock
sResource     EQU   50  ; sResource ID Offset in spBlock
ExtDev        EQU   51	; External Device Offset in SpBlock
SpsResult     EQU    0	; SpsResult Offset in SpBlock
SpsPointer    EQU    4	; SpsPointer Offset in SpBlock
SReadPRAMRec  EQU   17	; routine selector to the Slot Manager
SPutPRAMRec   EQU   18 	; routine selector to the Slot Manager
SDeleteSRTRec EQU   49	; routine selector to the Slot Manager
vendorUse5    EQU    6  ; vendorUse5 byte Offset in pRAM record
vendorUse6    EQU    7  ; vendorUse6 byte Offset in pRAM record
AppleError    EQU    2  ; the number Apple uses to show a slot manager error
;
; 2ND INIT CODE
; On Entry:  A0 -> Slot Manager SEBlock
;
; Uses:  A3 - copy of SEBlock pointer
;        A2 - slot base address
;        A1 - Table pointer
;        A0 - scratch
;        D6 - RefNum
;        D5 - Version # of Slot Manager
;        D4 - Resource ID to use
;        D3 - save mmu mode
;        D1 - scratch
;        D0 - scratch
			
; Convert the slot byte to $Fs000000
	MOVEM.L	A0-A5/D0-D7,-(sp)	; Save nearly all registers
	MOVE.W	#1,2(A0)			; Set the Secondary Init Status Field (in the SEBlock
								; pointed to by A0) to positive (no error.)
	MOVE.L	A0,A3				; Store the pointer away for later restoration
; Call sVersion to determine which version of Slot Manager is present
	MOVEQ   #0,D5				; Set ROM Slot Manager Version to 0
	LEA     -56(SP),SP			; Allocate a SpBlock on the stack
	MOVE.L  SP,A0				; Get the address of the SpBlock in A0 (required by slot manager calls)
	MOVEQ   #8,D0				; Use the sVersion call of the slot manager
	DC.W    $A06E				; _SlotManager
	MOVE.L	(A0),D1				; get spResult
	LEA     56(SP),SP			; Repair the stack
	TST.W   D0					; Check for error.
	BMI     cannotbe			; If error doing that call, then _sVersion not available
								;   at 2nd init, so this code could not have been called
	CMP.L	#2,D1				; If the Slot Manager version >= 2,
	BGE		secondary_exit		; then the work was all done in primary init
; Slot Manager Version must be 1 or greater (Patch installed or in ROM)
; Check pRAM for a valid Extended DeskTop sResource ID (vendorUse6)
; We assume that if it is non-zero then it is valid, (since PrimaryInit will set it to
; zero if there was any switch change.)	
sChkpRAM
	LEA     -56(SP),SP	      	; Allocate a SpBlock on the stack
	MOVE.L  SP,A0		      	; Put the address of the SpBlock in A0 (required by slot manager calls)
    LEA     sPRAMRec,A1	      	; Get the address of our local pRAM record
    MOVE.L  A1,SpsResult(A0)    ; Put it in the spsResult field as required
	MOVE.B  Slot(A3),SlotNum(A0)  ; Poke the slot number
    MOVEQ   #SReadPRAMRec,D0  	; Use the SReadPRAMRec call of the slot manager
    DC.W    $A06E           	; _SlotManager
	TST.W   D0		      		; Check for error.
	BEQ     sChkOk		      	; If no error doing that call, then continue on for more
	MOVE    #2,2(A3)	      	; Else set the Secondary Init Status Field to error.
sChkOk
    MOVE.B  vendorUse5(A1),D4   ; start with the switch setting
    TST.B   vendorUse6(A1)	    ; is there an sResource ID in vendorUse6?
    BEQ.S   do_info	      	    ; No - just do a normal inserts
	MOVE.B  vendorUse6(A1),D4   ; Otherwise - do a get RSRC info on the Extended DeskTop sResource
; Get Driver Reference number for the skinny resolution that should have been left by the primary init
do_info
	MOVE.L  SP,A0				; else Get the address of the SpBlock in A0 (required by slot manager calls)
	MOVE.B  (A3),49(A0)			; Poke the slot number
	CLR.B   51(A0)				; Poke the external device number (we don't have one, so zero)
	MOVE.B  D4,50(A0)			; Poke the slot resource number to kill
	MOVEQ   #22,D0				; Use the sRsrcInfo call of the slot manager
	DC.W    $A06E				; _SlotManager
	TST.W   D0					; Check for error.
	BEQ     info_ok				; If no error doing that call, then continue on for more
	MOVE    #2,2(A3)			; Else set the Secondary Init Status Field to error.
								; Now spRefNum, if non-zero, indicates this was boot screen
info_ok
	MOVE.W	38(SP),D6			; Save spsRefNum
do_delete
	MOVE.L  SP,A0				; Get the address of the SpBlock in A0 (required by slot manager calls)
	CLR.B   51(A0)				; Poke the external device number (we don't have one, so zero)
	MOVE.B  (A3),49(A0)			; Poke the slot number
	MOVE.B  D4,50(A0)			; Poke the slot resource number to kill
	MOVEQ   #49,D0				; Use the SDeleteSRTRec call of the slot manager
	DC.W    $A06E				; _SlotManager
	TST.W   D0					; Check for error.
	BEQ     doInsert			; If no error doing that call, then continue on for more
	MOVE    #2,2(A3)			; Else set the Secondary Init Status Field to error.
doInsert	
	MOVE.L  SP,A0				; Get the address of the SpBlock in A0 (required by slot manager calls)
	MOVE.W  D6,38(A0)			; Poke the refNum to make sure dCtlDevBase gets updated
	MOVE.B  (A3),49(A0)			; Poke the slot number
	CLR.B   51(A0)				; Poke the external device number (we don't have one, so zero)
	MOVE.B  D4,50(A0)			; Poke the slot resource number to add
	CLR.L   4(A0)				; Poke spsPointer to nil
	CLR.L   24(A0)				; Poke spParamData to nil to enable resource
	MOVEQ   #10,D0				; Use the InsertSRTRec call of the slot manager
	DC.W    $A06E				; _SlotManager
	TST.W   D0					; Check for error.
	BEQ     insert_ok			; If no error doing that call, then continue on for more
	MOVE    #2,2(A3)			; Else set the Secondary Init Status Field to error.
insert_ok
    LEA		sPRAMRec,A1			; get the PRAM record
    MOVE.L	#$80,D7				; starting Extended DeskTop sResource ID
	MOVE.L	#$85,D5				; ending Extended DeskTop sResource ID
  
doExtInsert
    CMP.B   D4,D7				; Is this already inserted?
	BEQ.S   disable_def			; Yes, don't disable our active sResource, instead disable the default
	MOVE.L  SP,A0				; Get the address of the SpBlock in A0 (required by slot manager calls)
	CLR.B   51(A0)				; Poke the external device number (we don't have one, so zero)
	MOVE.B  D7,50(A0)			; Poke the slot resource number to insert
	CLR.W   38(A0)				; Zero the refNum of our driver (don't update the pixMap stuff)
	MOVE.L  #1,24(A0)			; Poke spParamData to one to disable the resource
	CLR.L   4(A0)				; Poke spsPointer to nil
	MOVEQ   #10,D0				; Use the InsertSRTRec call of the slot manager
	DC.W    $A06E				; _SlotManager
	TST.W   D0					; Check for error.
	BEQ     disable_ok			; If no error doing that call, then continue on for more
	MOVE    #2,2(A3)			; Else set the Secondary Init Status Field to error.
disable_ok
    ADDI.B #1,D7
    CMP.B  D5,D7
	BLE.S  doExtInsert
    BRA.S  delSpBlock
disable_def
    CMP.B	#$81,D4
	BMI.S	disable_ok
	MOVE.L SP,A0				; disable the default (from the switches)
    LEA    sPRAMRec,A1			; Get the address of our local pRAM record
	MOVE.B vendorUse5(A1),50(A0) ; Poke the slot resource number to insert disabled
	CLR.L  4(A0)				; set up the rest of the SpBlock
	MOVE.L #1,24(A0)
	MOVEQ  #10,D0				; insert it
	DC.W   $A06E
	TST.W  D0
	BEQ.S  disable_ok
	MOVE   #2,2(A3)				; Else set the Secondary Init Status Field to error.
	BRA.S  disable_ok
 
delSpBlock
	LEA     56(SP),SP			; Repair the stack
    BRA.S   secondary_exit
	
; No fat slot support, 2nd init should never have been called!
cannotbe
	MOVE    #2,2(A3)			; Set the Secondary Init Status Field to error.
secondary_exit
	MOVEM.L (SP)+,A0-A5/D0-D7  	; Restore nearly all registers
	RTS
wait1 even
    CLR.L   D0
    MOVE.W  $D00,D0            	; Get TimeDBRA Global
moredbras                      	; Loop for 1 ms
    DBRA    D0,moredbras
    RTS
; Storage
sPRAMRec even
    DC.W    0					; secondary init pRAM record storage
    DC.W    0	
    DC.W    0
    DC.W    0
; ==================END OF SECONDARY INIT BLOCK=====================
endsecondaryinit
#endasm
/* **********************      PRIMARY INIT       ******************* */
#asm
;***********************************************************************
;  Primary Init Code Block
;***********************************************************************
primaryinit even
; Header information
    dc.l  endprimaryinit-primaryinit        ; Length of seBlock
    dc.b  2                     ; Revision Level 2 (The Slot Manager REQUIRES this to be 2!)
    dc.b  2                     ; CPU ID 2 (68020)
    dc.w  0                     ; Reserved
    dc.l  4                     ; Code Offset 4  (In other words, next!)
;
; PRIMARY INIT CODE
;
; On Entry:  A0 -> Slot Manager seBlock
;
; Uses:  A2 <- converted slot byte ($Fss00000)
;        A3 <- Slot Manager seBlock
;        D6 <- TMS34061 util register contents
;	     D7 <- pixel clock select
; Convert the slot byte to $Fss00000
    MOVEM.L A0-A5/D0-D7,-(SP)  	; save nearly all registers	
    MOVE   #1,2(A0)            	; Set the Primary Init Status Field (in the seBlock
                                ; pointed to by A0) to positive (no error)
    MOVE.L  A0,A3               ; Store the pointer away for later restoration
	
; We now need to create a $Fss00000 out of the seSlot field in the seBlock:
    MOVEQ   #0,D0               ; Zero all of D0
    MOVE.B  (A0),D0             ; Grab the seSlot byte (range=$09-$0E)
    LSL     #4,D0               ; Shove it into the high nibble ($s0)
    OR.B    (A0),D0             ; Or it with its previous self to get $ss
    ORI     #$F00,D0            ; Or to get $Fss
    SWAP    D0                  ; Now get $0Fss0000
    LSL.L   #4,D0               ; And finally have $Fss00000
    MOVE.L  D0,A2               ; Stow it away
    BSR	    wait_one			; wait one millisecond
	
monitorOK
	
;????
;                           M O D E     R  E  G  I  S  T  E  R
; ----------------------------------------------------------------------------------
; |    |    |    |    |    |    |    |    ||    |    |	  |    |    |    |    |    |
; | 15 | 14 | 13 | 12 | 11 | 10 |  9 |  8 ||  7 |  6 |  5 |  4 |  3 |  2 |  1 |  0 |
; |    |    |    |    |    |    |    |    ||    |    |	  |    |    |    |    |    |
; ----------------------------------------------------------------------------------
;
; ----------------------------------------------------------------------------------
; |            Not used                   | Syn | X-Zoom  |     not used      | Mon |
; ----------------------------------------------------------------------------------
;
; Read/Write bits:
; Sync Enable           ( 7):    $00 = Disable, $01 = Enable
;
; X Direction Zoom      ( 5, 6): $00 = 1-X,    $01 = 2-X,    $10 = 4-X,       $11 = 8-X
;
; Monitor sense         (0)      $0  = portrait (640X870 75Hz),      $1  = 19" (1024X768 75Hz)
;
    BRA.S   sDel
PRAMRec
    DC.W    0
    DC.W    0
    DC.W    0
    DC.W    0
tempStorage
    DC.B    0
    DC.B    0 					; for alignment
    
; Do slot resource deletion for unused resolutions
sDel    
    MOVE.L  #$80,D7             ; make an sResource ID (default is 1024 x 768)
    MOVE.L	D7,D6
	ANDI.L	#3,D6
    LEA     -56(SP),SP          ; Allocate a SpBlock on the stack
    MOVE.L  SP,A0               ; Get the address of the SpBlock in A0 (required by slot manager calls)
    MOVE.B  (A3),49(A0)         ; Poke the slot number
    CLR.B   51(A0)              ; Poke the external device number (we don't have one, so zero)
    LEA     PRAMRec,A1
    MOVE.L  A1,0(A0)
    MOVEQ   #17,D0              ; Use the SReadPRAMRec call of the slot manager
    DC.W    $A06E               ; _SlotManager
    LEA     PRAMRec,A1			; Get the address of our PRAM record
    TST.B	7(A1)				; check the vendorUse6 byte
	BNE.S	usePRAM
 
; save the new switch setting in PRAM, zero the Extended DeskTop (vendorUse6) byte
    LEA     PRAMRec,A1
    MOVE.B  D7,6(A1)			; put the switch setting in vendorUse5
    MOVE.B	D7,7(A1)			; save the monitor setting in vendorUse6 byte
 
    MOVE.L  A1,4(A0)			; place the address of our PRAM storage in spsPointer
    MOVEQ   #18,D0              ; Use the SPutPRAMRec call of the slot manager
    DC.W    $A06E               ; _SlotManager
    
    LEA     tempStorage,A0		; save our requested resource
    MOVE.B  D7,0(A0)            ; in temporary storage
    MOVE.B  #$80,D7				; Start deletion from lowest to highest sResource numbers
    BRA.S   chkRSRC
    
usePRAM                         ; Check the PRAM to see which sResource ID has been requested
    MOVE.B  #$80,D7				; Start deletion from lowest to highest sResource numbers
    MOVE.B  7(A1),D0			; Check for an Extended DeskTop resource
    TST.B   D0					; if it is non-zero then we go for the Extended DeskTop
    BNE.S   usePZE
 
    MOVE.B  6(A1),D0			; Otherwise, use the switch settings
    
usePZE
    LEA     tempStorage,A1		; Temporary storage for our sResource ID to be loaded
    MOVE.B  D0,(A1)				; Save the ID number
chkRSRC
    LEA     tempStorage,A1		; Get the storage containing our sResource ID to be loaded
    MOVE.L  D7,D0				; Get the current sResource ID we are checking
    CMP.B   (A1),D0				; Is this the one to be loaded?
    BEQ.S   loopPRAM			; Yes - just loop, don't delete it
    BSR.S   deleteRec			; Otherwise just delete this resource
loopPRAM
    ADDQ    #1,D7				; Increment the current resource number
    CMP.L   #$85,D7				; Check against the max valid sRecource ID number
    BLE.S   chkRSRC				; If less, we have more to check
    BRA.S   readytoinit			; Otherwise we are all done
; This subroutine deletes a resource from the resource table
; D0 contains the resource ID to be deleted
deleteRec
    MOVE.L  SP,A0               ; Get the address of the SpBlock in A0 (required by slot manager calls)
    MOVE.B  (A3),49(A0)         ; Poke the slot number
    CLR.B   51(A0)              ; Poke the external device number (we don't have one, so zero)
    MOVE.B  D0,50(A0)           ; Poke the slot resource number to kill
    MOVEQ   #49,D0              ; Use the SDeleteSRTRec call of the slot manager
    DC.W    $A06E               ; _SlotManager
    TST.W   D0                  ; Check for error.
    BNE.S   delDone         	; If no error doing that call, then return
    MOVE    #2,2(A3)            ; Else set the Primary Init Status Field to error.
								; (This is the value Apple uses in their video ROM.)
delDone                         
    RTS
	
; Initialize the utility register with the value in D6
util_init
    MOVE.L  A2,A0               ; Get the slot address
    ADD.L   #UTILREG,A0         ; Get the utility register
    MOVE.L  D6,(A0)             ; Stuff the init value into the utility register
    RTS
	
readytoinit
; Call sVersion to determine which version of Slot Manager is present	
	MOVEQ   #0,D5				; Set ROM Slot Manager Version to 0
	MOVE.L  SP,A0				; Get the address of the SpBlock in A0 (required by slot manager calls)
	MOVEQ   #8,D0				; Use the sVersion call of the slot manager
	DC.W    $A06E				; _SlotManager
	MOVE.L	(A0),D1				; get spResult
	TST.W   D0					; Check for error.
    BMI.S	pdoInit				; sVersion is NOT present, just continue
	CMP.L	#2,D1				; If the Slot Manager version >= 2,
	BLT.S	pdoInit				; then we have new roms, else just continue
	
newRoms
    LEA		PRAMRec,A1			; get the PRAM record
	MOVE.L	#$80,D7
	MOVE.L	#$85,D5
 
 
pExtInsert
    CMP.B   D4,D7				; Is this already inserted?
	BEQ.S   pdisable_def		; Yes, don't disable our active sResource, instead disable the default
	MOVE.L  SP,A0				; Get the address of the SpBlock in A0 (required by slot manager calls)
	CLR.B   51(A0)				; Poke the external device number (we don't have one, so zero)
	MOVE.B  D7,50(A0)			; Poke the slot resource number to insert
	CLR.W   38(A0)				; Zero the refNum of our driver (don't update the pixMap stuff)
	MOVE.L  #1,24(A0)			; Poke spParamData to one to disable the resource
	CLR.L   4(A0)				; Poke spsPointer to nil
	MOVEQ   #10,D0				; Use the InsertSRTRec call of the slot manager
	DC.W    $A06E				; _SlotManager
	TST.W   D0					; Check for error.
	BEQ     pdisable_ok			; If no error doing that call, then continue on for more
	MOVE    #2,2(A3)			; Else set the Secondary Init Status Field to error.
pdisable_ok
    ADDI.B #1,D7
    CMP.B  D5,D7
	BLE.S  pExtInsert
    BRA.S  pdoInit
pdisable_def
    CMP.B  #83,D4
	BMI.S   pdisable_ok
	MOVE.L SP,A0				; disable the default (from the switches)
    LEA    PRAMRec,A1			; Get the address of our local pRAM record
	MOVE.B vendorUse5(A1),50(A0) ; Poke the slot resource number to insert disabled
	CLR.L  4(A0)				; set up the rest of the SpBlock
	MOVE.L #1,24(A0)
	MOVEQ  #10,D0				; insert it
	DC.W   $A06E
	TST.W  D0
	BEQ.S  pdisable_ok
	MOVE   #2,2(A3)				; Else set the Primary Init Status Field to error.
	BRA.S  pdisable_ok
pdoInit
    LEA     56(SP),SP           ; Repair the stack
    AND.L   #$FFFFFFFC,D6		; set up the crystal
    LEA     PRAMRec,A1			; Get the address of our PRAM record
    TST.B   6(A1)				; check the vendorUse5 byte
    BEQ.S   size1024            ; If it is zero default to 1024x768 monitor initialization.
    CMP.B   #$80,6(A1)          ; Are we in 1024x768 mode?
    BEQ.S   size1024            ;    Yes, then goto size1024.
    CMP.B   #$81,6(A1)			; Are we in 640x870 mode
    BNE.S   size1024            ;    No, hmmm - well, default to 1024x768 anyway.
    
; We must be using a 640x480 monitor
size640
    OR.L    #2,D6
    LEA     _57MHz,A0
    BSR.S   doInit
    BRA.S   done
; We must be using a 1024x768 monitor
size1024
    LEA     _80MHz,A0			; all ClearVue/GS and 708+ products are 75Hz refresh rates
    BSR.S   doInit				; ini the oscillator
done
; Check for a monitor attached to the card
    MOVE.L	A2,A0				; get the base address
    ADD.L	#UTILREG,A0			; get the utility register
    MOVE.W	2(A0),D0			; get the data
    ANDI.W	#MONMASK,D0			; mask off the unused bits
    CMP.W 	#MONMASK,D0			; is there a monitor connected
    BNE.S	showPict			; yes - just continue
    MOVE.W	2(A0),D0			; get the data
    ANDI.W	#$800,D0			; mask off the unused data
    CMP.W	#$800,D0			; is the enable switch set?
    BNE.S	showPict			; yes - just continue	
    LEA     -56(SP),SP          ; Allocate a SpBlock on the stack
    LEA     tempStorage,A0		; Delete the enabled sResource
	MOVE.B  (A0),D0
	BSR.S   deleteRec
    LEA     56(SP),SP           ; remove the SpBlock from the stack
    MOVE.L  A2,-(SP)            ; Toss screenbase onto the stack
    BSR.S	blankDisable		; Disable the screen
    LEA     4(SP),SP            ; Repair the stack
	BRA.S   allDone
	
showPict
    MOVE.W  D6,D0				; get our crystal setting
    AND.L   #3,D0				; mask out everything else
    MOVE.W  D0,-(SP)			; pass it to _putpict
    MOVE.L  A2,-(SP)            ; Toss screenbase onto the stack
    JSR     _putpict			; Draw Logo, and ROM Version
    MOVE.L  (SP)+,A0
    MOVE.W  (SP)+,D0			; Repair the stack
allDone
; All done - exit
    MOVE.L  A2,A0
    ADD.L   #$E000B,A0			; Get the address of the DAC mask register
    MOVE.B  #$FF,(A0)			; initialize it
    MOVEM.L (SP)+,A0-A5/D0-D7	; Restore nearly all registers
    RTS
; Do the init routine pointed to by A0
doInit
    MOVE.L  A2,-(SP)            ; Toss screenbase onto the stack
    JSR     wait_one            ; JSR to the 1ms delay routine
    BSR.S   init                ; BSR to the init routine
    JSR     wait_one            ; JSR to the 1ms delay routine
    JSR     wait_one            ; JSR to the 1ms delay routine
    BSR.S   util_init			; Initialize the utility register
    JSR     wait_one            ; JSR to the 1ms delay routine
    BSR.S   blankEnable        ; Enable the screen
    JSR     wait_one            ; JSR to the 1ms delay routine
    LEA     4(SP),SP            ; Repair the stack
    RTS
;***********************************************************************
; Wait 1ms
;***********************************************************************
wait_one
    CLR.L   D0
    MOVE.W  $D00,D0             ; Get TimeDBRA Global
more_dbras                      ; Loop for 1 ms
    DBRA    D0,more_dbras
    RTS
;***********************************************************************
; blank Enable
;***********************************************************************
blankEnable
    MOVE.L	A2,A0				; get the base
	MOVE.L	#TMS34061,D0		; offset to the TMS34061
	MOVE.B	#$68,$C8(A0,D0.L)
	RTS
;***********************************************************************
;blank Disable
;***********************************************************************
blankDisable
    MOVE.L	A2,A0				; get the base
	MOVE.L	#TMS34061,D0		; offset to the TMS34061
	MOVE.B	#$48,$C8(A0,D0.L)
	RTS
	
;***********************************************************************
; Initialize the 34061
;   A0 <= the address of the appropriate timing table
;   A2 <= our base address
; uses:
;   D1 <= offset to the 34061
;   D0 <= 34061 register counter
;***********************************************************************
init
  MOVE.L	A2,A1
  MOVE.L	#TMS34061,D1	; offset to the TMS34061
  MOVEQ		#13,D0			; number of 34061 register pairs to stuff
LoopInit
  MOVE.B	(A0)+,8(A1,D1.L)
  MOVE.B	(A0)+,0(A1,D1.L)
  ADDA.L	#$10,A1
  DBRA		D0,LoopInit
  RTS
;***********************************************************************
; Timing tables for the TMS34061
;***********************************************************************
_80MHz
  DC.W	$0004	; hEndSync
  DC.W	$000D	; hEndBlank
  DC.W	$004D	; hStartBlank
  DC.W	$0052	; hTotal
  DC.W	$0002	; vEndSync
  DC.W	$001F	; vEndBlank
  DC.W	$031F	; vStartBlank
  DC.W	$0322	; vTotal
  DC.W	$0004	; displayUpdate
  DC.W	$0000	; displayStart
  DC.W	$0000	; vInterrupt
  DC.W	$7080	; control1, bit 10 = vIntEnable, bit 11 = errIntEnable
  DC.W	$4800	; control2, bit 13 = screenEnable (0 = blank)
_57MHz
  DC.W	$0004   ; hEndSync
  DC.W	$000A   ; hEndBlank
  DC.W	$003C	; hStartBlank
  DC.W	$003F   ; hTotal
  DC.W	$0005   ; vEndSync
  DC.W	$0051   ; vEndBlank
  DC.W	$02A9   ; vStartBlank
  DC.W	$02D9   ; vTotal
  DC.W	$0004   ; displayUpdate
  DC.W	$0000	; displayStart
  DC.W	$0000	; vInterrupt
  DC.W	$7080   ; control1, bit 10 = vIntEnable, bit 11 = errIntEnable
  DC.W	$4800	; control2, bit 13 = screenEnable (0 = blank)
;***********************************************************************
; RasterOps Logo BitMap
;
; 31 Bytes wide
; 37 Lines high
;***********************************************************************
_ROlogo even
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
 
_ROMV1 even
; 6 Bytes wide
; 9 Lines high   1.0
  DC.B    $00,$00,$00,$00,$00,$00
  DC.B    $43,$00,$00,$00,$00,$00
  DC.B    $C4,$80,$00,$00,$00,$00
  DC.B    $44,$80,$00,$00,$00,$00
  DC.B    $44,$80,$00,$00,$00,$00
  DC.B    $44,$80,$00,$00,$00,$00
  DC.B    $44,$80,$00,$00,$00,$00
  DC.B    $EB,$00,$00,$00,$00,$00
  DC.B    $00,$00,$00,$00,$00,$00
  DC.W    $00            ; For alignment
  DC.W    $00            	; For alignment
#endasm
setupPict(base)
unsigned long base;
{
#asm
PictStart even
	movem.l D0-D7/A0-A4,-(SP)
	movea.l	8(a6),A0
	CLR.L   D0				; D0 = the proper pattern
	MOVE.W	#32,D4		    ; D4 = longs per row for the screen
	MOVE.W	#869,D3		    ; D3 = screen height - 1				
	MOVE.L	8(A6),A1		; point to the screenbase			
NxtRow2	
	MOVE.L	A1,A0			; get next row
	MOVE.W	D4,D2			; get longs per row
	SUB.W	#1,D2			; make count 0 based
NxtLong2	
	MOVE.L	D0,(A0)+		; write black
	DBF	D2,NxtLong2			; for entire width of row		
	ADD.W	#128,A1		    ; bump to next row
	DBF	D3,NxtRow2			; until no more rows
#endasm
}
drawpict(ramStart,length, width, incrValue, pictAddr)
unsigned long ramStart;
unsigned short length, width, incrValue;
unsigned long pictAddr;
{
  register unsigned char *to,*bm,c;
  register short i,j,k;
  
to = (unsigned char *)ramStart;
bm = (unsigned char *)pictAddr;
for (i=0;i<length;i++)
  {
    for (j=0;j<width;j++)
      {
        *to++ = *bm++;
      }
    to += incrValue;
  }
}
drawlogo(base,screenlength)
unsigned long base,screenlength;
{
  register unsigned char *to, *bm, c;
  register short i,j,k,s,length;
  extern ROlogo;
length = (screenlength/2)-124-16;  
for (i=0;i<length-16;i+=16)
  {
    to = (unsigned char *)(base+((unsigned long)(0x20010+i)));
    bm = (unsigned char *)&ROlogo;
    for(s=0;s<37;s++)
      {
        for (j=0;j<16;j++) *to++ = 0xFF;
	    for (j=0;j<31;j++)
	      {
	        if (c = bm[s*31+j])
	          {
	            for (k=0;k<8;k++)
		          {
		            if (c & 0x80) *to++ = 0xFF;
		            else *to++ = 0;
		            c <<= 1;
		          }
	          }
	        else for (k=0;k<8;k++) *to++ = 0;
	      }
	    to += 760;
      }
  }
for (i=0;i<=20;i+=2)
  {
    to = (unsigned char *)((unsigned long)(base+(0x20010+(i*1024L))));
    for (j=0;j<length;j++) *to++ = 0;
    to = (unsigned char *)((unsigned long)(base+(0x20010+((40-i)*1024L))));
    for (j=0;j<length;j++) *to++ = 0;
    to = (unsigned char *)((unsigned long)(base+(0x20010+((i+1)*1024L))));
    for (j=0;j<length;j++) *to++ = 0;
    to = (unsigned char *)((unsigned long)(base+(0x20010+((40-(i+1))*1024L))));
    for (j=0;j<length;j++) *to++ = 0;
  }
}
/* This routine draws the RasterOps Logo and ROM version on a black background */
putpict(base, crystal)
unsigned long base;
short crystal;
{   
  unsigned long screenlength;
  extern ROlogo, ROMV1;
setupPict(base);
switch(crystal)
  {
    case 0: 	screenlength = 1024L;
      		 	break;
      
    case 1: 	screenlength = 800L;
      		 	break;
    case 2: 	screenlength = 640L;
      		 	break;
    default:    screenlength = 1024L;   /* Change this for a custom crystal */
      		 	break;
  }
drawpict((unsigned long)(base+0x3400+(screenlength-56)), 9, 6, 976, (unsigned long)&ROMV1);
drawlogo(base,screenlength);
drawpict((unsigned long)(base+0x3400+(screenlength-56)),9,6,976,(unsigned long)&ROMV1);
drawpict((unsigned long)(base+0x20000+((screenlength/2)-128)),37,31,776,(unsigned long)&ROlogo);     
}  
#asm
; ==================END OF PRIMARY INIT BLOCK=====================
endprimaryinit even
#endasm
/* **********************   VENDOR INFO    ******************* */
/* Vendor Info List */
#asm
vendorinfo
    OSLstEntry  1,vendordesign    ; Vendor Design ID Offset
    OSLstEntry  3,cardrevision    ; Card's Revision Level Offset
    OSLstEntry  4,cardpartnumber  ; Card Part Number Offset
	OSLstEntry  5,cardrevisiondate	; Card Revison Date Offset
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
	dc.b  'ClearVue LC'
    dc.w  0            ; For Alignment
cardrevisiondate
    dc.b  '2:28 PM  Oct 17, 1990'
	dc.w  0            ; For Alignment
#endasm
/* **********************   SRESOURCE LIST    ******************* */
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
/* My sResource List 640 */
#asm
mysreslist640
    OSLstEntry1 1,mytype              ; My sResource Type Format Offset
    OSLstEntry1 2,myname              ; My sResource Name Offset
    OSLstEntry1 4,mydrvrdir           ; My sResource Driver Directory Offset
    DatLstEntry 8,1                   ; sRsrcHWDevId = 1
    OSLstEntry1 $A,minorbase          ; MinorBase Offset
    OSLstEntry1 $B,minorlen           ; MinorLength Offset
    OSLstEntry1 $80,bit1parmlist640   ; One-Bit-Per-Pixel Parameter List Offset
    DatLstEntry $FF,0                 ; End
#endasm
/* My sResource List 1024f1024 */
#asm
mysres1024f640
    OSLstEntry2 1,mytype              ; My sResource Type Format Offset
    OSLstEntry2 2,myname              ; My sResource Name Offset
    OSLstEntry2 4,mydrvrdir           ; My sResource Driver Directory Offset
    DatLstEntry 8,1                   ; sRsrcHWDevId = 1
    OSLstEntry2 $A,minorbase          ; MinorBase Offset
    OSLstEntry2 $B,minorlen           ; MinorLength Offset
    OSLstEntry2 $80,bit1parm1024f1024  ; One-Bit-Per-Pixel Parameter List Offset
    DatLstEntry $FF,0                 ; End
#endasm
/* My sResource List 1024f640 */
#asm
mysres8192f870
    OSLstEntry5 1,mytype              ; My sResource Type Format Offset
    OSLstEntry5 2,myname              ; My sResource Name Offset
    OSLstEntry5 4,mydrvrdir           ; My sResource Driver Directory Offset
    DatLstEntry 8,1                   ; sRsrcHWDevId = 1
    OSLstEntry5 $A,minorbase          ; MinorBase Offset
    OSLstEntry5 $B,minorlen           ; MinorLength Offset
    OSLstEntry5 $80,bit1parm1024f640  ; One-Bit-Per-Pixel Parameter List Offset
    DatLstEntry $FF,0                 ; End
#endasm
#asm
DrHwCB208_SE30        EQU $0143       ; V1.41
DrHwRasterOpsCB208    EQU $0132       ; V1.41
DrHwClearVueGS        EQU $026F       ; V1.01
DrHwClearVueGS_LC        EQU $026F       ; V1.0 ????
CatDisplay            EQU     3
TypVideo              EQU     1
DrSwApple             EQU     1
DrHwTFB               EQU     1
#endasm
/* My sResource Type Format */
#asm
mytype
    dc.w  CatDisplay               ; Category:
    dc.w  TypVideo                 ; Type:
    dc.w  DrSwApple                ; DrvrSw:
    dc.w  DrHwClearVueGS_LC
#endasm
  
/* My sResource Name */
#asm
myname
    dc.b  'Display_Video_Apple_RasterOpsClearVue/LC'
    dc.w  0        ; For Alignment
#endasm
/* MinorBase */
#asm
minorbase
    dc.l  0        ; No offset from normal beginning of slot space
#endasm
/* MinorLength */
#asm
minorlen
    dc.l  $D9800   ; 870K of Video RAM
#endasm
/* One-Bit-Per-Pixel Parameter List */
#asm
bit1parmlist1024
    OSLstEntry  1,bit1parms1024  ; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,8              ; Number of Pages: 8
    DatLstEntry 4,0              ; Device Type: 0
    DatLstEntry $FF,0            ; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bit1parms1024
    dc.l  endbit1parms1024-bit1parms1024  ; Length of sBlock
    dc.l  $000                      ; Offset to Page 0 of Video RAM: none
    dc.w  $400                      ; RowBytes
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
/* One-Bit-Per-Pixel Parameter List */
#asm
bit1parmlist640
    OSLstEntry  1,bit1parms640   ; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,8              ; Number of Pages: 8
    DatLstEntry 4,0              ; Device Type: 0
    DatLstEntry $FF,0            ; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bit1parms640
    dc.l  endbit1parms640-bit1parms640  ; Length of sBlock
    dc.l  $000                      ; Offset to Page 0 of Video RAM: none
    dc.w  $400                      ; RowBytes
    dc.l  0                         ; BoundsRect: (0,0,480,870) [TLBR]
    dc.l  $01E00366                 ;
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
endbit1parms640
#endasm
/* One-Bit-Per-Pixel Parameter List */
#asm
bit1parm1024f640
    OSLstEntry  1,bit1p1024f640  ; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,8              ; Number of Pages: 8
    DatLstEntry 4,0              ; Device Type: 0
    DatLstEntry $FF,0            ; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bit1p1024f640
    dc.l  endbit1p1024f640-bit1p1024f640  ; Length of sBlock
    dc.l  $000                      ; Offset to Page 0 of Video RAM: none
    dc.w  $400                      ; RowBytes
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
endbit1p1024f640
#endasm
/* One-Bit-Per-Pixel Parameters sBlock - 2048f870 */
#asm
bit1p2048f870
    dc.l  endbit1p2048f870-bit1p2048f870  ; Length of sBlock
    dc.l  $000                      ; Offset to Page 0 of Video RAM: none
    dc.w  $400                      ; RowBytes
    dc.l  0                         ; BoundsRect: (0,0,870,2048) [TLBR]
    dc.l  $03660800                 ;
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
endbit1p2048f870
#endasm
/* One-Bit-Per-Pixel Parameter List - 4096f870 */
#asm
bit1parm4096f870
    OSLstEntry  1,bit1p4096f870  ; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,8              ; Number of Pages: 8
    DatLstEntry 4,0              ; Device Type: 0
    DatLstEntry $FF,0            ; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock - 4096f870 */
#asm
bit1p4096f870
    dc.l  endbit1p4096f870-bit1p4096f870  ; Length of sBlock
    dc.l  $000                      ; Offset to Page 0 of Video RAM: none
    dc.w  $400                      ; RowBytes
    dc.l  0                         ; BoundsRect: (0,0,870,4096) [TLBR]
    dc.l  $03661000                 ;
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
endbit1p4096f870
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bit1p8192f870
    dc.l  endbit1p8192f870-bit1p8192f870  ; Length of sBlock
    dc.l  $000                      ; Offset to Page 0 of Video RAM: none
    dc.w  $400                      ; RowBytes (always)
    dc.l  0                         ; BoundsRect: (0,0,870,8192) [TLBR]
    dc.l  $03662000                 ;
    dc.w  0                         ; PixMap Version Number
    dc.w  0                         ; unused
    dc.l  0                         ; used for our 24/32-bit environment flags
    dc.l  $00480000                 ; Horizontal Res
    dc.l  $00480000                 ; Vertical Res
    dc.w  0                         ; Pixel Type (0=Chunky)
    dc.w  1                         ; Pixel Size
    dc.w  1                         ; Components in Pixel
    dc.w  1                         ; Bits Per Component
    dc.l  0                         ; PlaneBytes Offset
endbit1p8192f870
#endasm
/* My sResource Driver Directory */
#asm
mydrvrdir
    OSLstEntry  2,mydrvr            ; My 68020 Driver sBlock Offset
    DatLstEntry $FF,0               ; End
#endasm
/* **********************   VIDEO DRIVER    ******************* */
/* My 68020 Driver sBlock */
#asm
mydrvr
; ==================BEGINNING OF DRIVER BLOCK=====================
    dc.l  endmydrvr-mydrvr          ; Length of sBlock
#endasm
/* RasterOps ClearVue GS/LC and 708+/LC Video Driver */
#asm
;   This driver is called to install itself, and gets control here.
;   The paramBlock must be filled in so we can close the old driver
;   from the slot ROM.
;	We jump to the install code at the end of the driver open.
; 	We expect to be called with:
;		D5 <= slot ID
;		A0 <= paramBlock pointer
;	We use:
;		D4 => driver refNum
;		A2 => DCE Handle
;		A4 => paramBlock pointer
;		A5 => dce pointer
;The Driver Header: This is the address installed in the driver's Device Control Entry,
;so that all the standard Macintosh driver header info is in the right spots.
_VDriver
    dc.w    $4C00             	; driver responds to Control and Status, NeedsLock
    dc.w    0                 	; NOT A DA (was "update every x seconds")
    dc.w    0                 	; NOT A DA (was "detect events")
    dc.w    0                 	; NOT A DA (was "menu ID number")
    dc.w    _myopen-_VDriver    ; open routine
    dc.w    _prime-_VDriver     ; prime routine (not needed for this driver)
    dc.w    _control-_VDriver 	; control routine
    dc.w    _status-_VDriver  	; status routine
    dc.w    _myclose-_VDriver   ; close routine
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
 if MAKINGGS
    dc.b    ".RasterOps 1.0 ClearVue/GS LC Video Driver"
 else
    dc.b    ".RasterOps 1.4 708+/LC Video Driver"
 endc 
 
_titleend
    ds      0                ;for alignment
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
   move.w  4(sp),D0      ; Return error code
   BTST    #1,6(A0)      ; Check ioTrap field of the paramblock if it has the "NoQueue" bit set.
   BEQ.S   _goiodone     ; The bit wasn't set, so it has a queue element allocated for it.  Go do jIODone.
   RTS                   ; Go back for a normal return since no queue element was allocated.
_goiodone
   add.l   #6,sp         ; Pop our return address away, and error code
   unlk    a6            ; Unlink the subroutine (Return address is now on top of stack)
   MOVEA.L $8FC,A0       ; Load address of jIODone routine
   JMP     (A0)          ; Use it to exit with
#endasm
/********************************************************************************************/
/* Forward declarations */
OSErr setgamma();
unsigned short LUTtranslate();
OSErr setlut();
void getlut();
void GrayScreen();
void WaitForVBlank();
void putPRAM5();
void putPRAM6();
short checkPRAM6();
short checkPRAM5();
short abs();
void calcRects();
void PanTo();
void Center();
void ZoomIn();
void ZoomOut();
void PanY();
/********************************************************************************************/
/*
   Driver open()
   
*/
 
OSErr myopen()
{
  AuxDCEPtr dcep;            /* Auxiliary Device Control Entry pointer. 		*/
  register mystoragePtr msp;
  register unsigned long *dacaddr, *dacdata, *dacmask;
  register unsigned short *modereg,mapmode,i;
  CntrlParam *pbp;           /* Application-passed parameter block pointer. 		*/
  THz oldzone;               /* Previous heap zone 					*/
  SlotIntQElement *sqeptr;   /* Slot queue element pointer 				*/
  extern long intrpthandler, /* Define the interrupt handling routine as external; 	*/
              intrptend;     /* As well as the end of the interrupt handler. 		*/
  short theID;
  SpBlock sp;
  SPRAMRecord spRec;
#asm
    movem.l    a0-a5/d1-d7,-(sp)  ; save nearly all registers
#endasm
save(&dcep,&pbp);      				/* A0 -> pbp, A1 -> dcep 			*/
oldzone = GetZone();             	/* Get current heap zone */
SetZone(SystemZone());           	/* Force memory operations to the System Heap. 	*/
/* Allocate a handle to our private storage, then lock it and deref it. */
if (!(dcep->dCtlStorage = NewHandle((long)sizeof(struct mystorage)))) 
  {
    SetZone(oldzone);              	/* Force memory operations to the original heap. */
    #asm
    	movem.l    (sp)+,a0-a5/d1-d7   ; restore nearly all registers
    #endasm
    return(openErr);             	/* Return that we couldn't open successfully. 	*/
  }
HLock(dcep->dCtlStorage);
msp = (mystoragePtr)(*(dcep->dCtlStorage));
/* ----------------------------Install Interrupts------------------------------		*/
if (!(msp->myintrptcode = (unsigned char *)NewPtr((unsigned long)&intrptend-(unsigned long)&intrpthandler)))
  {
    SetZone(oldzone);              /* Force memory operations to the original heap. 	*/
    DisposHandle(dcep->dCtlStorage);
    #asm
    	movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
    #endasm
    return(openErr);                   /* Return that we couldn't open successfully. 	*/
  }
  
/* Copy the code from ourself to a separate pointer block.  That way,
   if the driver needs to be replaced, (as when the 24-bit environment is installed)
   then interrupts never have to be altered since the code is external from
   the old driver (this one) that would be removed in such a replacement.
   [Of course, a pointer to the external block is stored in the external
   variable section block (dcep->dCtlStorage) so you can still find it if
   you do, in fact, need to alter it.] */
BlockMove(&intrpthandler,msp->myintrptcode,(unsigned long)&intrptend-(unsigned long)&intrpthandler);
if (!(sqeptr = (SlotIntQElement *)NewPtr((long)sizeof(SlotIntQElement))))
  {
    SetZone(oldzone);              /* Force memory operations to the original heap. 	*/
    #asm
    	movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
    #endasm
    DisposPtr(msp->myintrptcode);
    DisposHandle(dcep->dCtlStorage);
    return(openErr);                   /* Return that we couldn't open successfully. 	*/
  }
msp->myslotqeleptr = sqeptr;
SetZone(oldzone);                /* Force memory operations to the original heap. 	*/
/* Set up the fields of the slot queue element block. 					*/
sqeptr->sqLink = 0;
sqeptr->sqType = 6;
sqeptr->sqPrio = 0;
sqeptr->sqAddr = (ProcPtr)msp->myintrptcode;
sqeptr->sqParm = dcep->dCtlDevBase;
/* Install that slot queue element into the interrupt table. 				*/
if(mysintinstall(sqeptr,dcep->dCtlSlot))
  {
    #asm
    	movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
    #endasm
    SetZone(oldzone);              /* Force memory operations to the original heap. 	*/
    DisposPtr(sqeptr);
    DisposPtr(msp->myintrptcode);
    DisposHandle(dcep->dCtlStorage);
    return(openErr);                   /* Return that we couldn't open successfully. 	*/
  }
  
/* Turn interrupts on. */
*(unsigned long *)((((unsigned long)(dcep->dCtlDevBase) & SLOTFss)) + VIDINTERRUPT) = interruptOn;
msp->InterruptFlag = true;
/* -----------------------------End Install Interrupts------------------------------ 	*/
/* Check PRAM vendorUse5 for the type of monitor connected */
msp->slot = dcep->dCtlSlot;
theID = checkPRAM5(msp->slot);
switch(theID&0x00FF)
  {
    case 0:
    case 0x80: msp->screensize = mode1024;
               break;
    case 0x81: msp->screensize = mode640;
               break;
    default:   msp->screensize = mode1024;
               break;
  }
theID = checkPRAM6(msp->slot);
/* Check PRAM vendorUse6 for the type of Virtual DeskTop selected */
switch(theID&0x00ff)
  {
    case 0x84 :
    case 0x85 : msp->xSize = mode1024;
  	        	msp->ySize = 870;
	        	break;
    case 0x86:  msp->xSize = 2048;
                msp->ySize = 870;
				break;
    case 0x87:  msp->xSize = 4096;
                msp->ySize = 870;
				break;
    case 0x88:  msp->xSize = 8192;
                msp->ySize = 870;
				break;
    default:    switch(msp->screensize)
		  		  {
    		    	case mode1024: 	msp->xSize = mode1024;
    		   		   				msp->ySize = 768;
		   		  					break;
		   
    		    	case mode640:  	msp->xSize = mode640;
    		   		   				msp->ySize = 870;
		   		   					break;
  		  		  }
  }
/*  Initialize our structure's data */
msp->screenbase = (unsigned long)(dcep->dCtlDevBase);
msp->mode       = pix1; 	/* csCode for 1-bit mode 				*/
msp->pages      = 8;      	/* There are eight pages available in 1-bit mode 	*/
#if MAKINGGS
msp->bwmapping  = 0x0100;	/* Black/white mapping is always on! 				*/
#else
msp->bwmapping  = 0;		/* Black/white mapping is off 				*/
#endif
msp->zoom       = x1;		/* Zoom x1 						*/
/* Initialize the pan and zoom globals */
msp->currentRate  =  0;		/* No panning until zoomed or Virtual DeskTop is enabled */
msp->currentZoom  =  1;		/* No zooming until chosen by a key 			*/
msp->currentX 	  =  0;		/* 0,0 							*/
msp->currentY 	  =  0;
msp->border 	  = 10;		/* Ten pixels difference between fast and slow panning 	*/
msp->refNum	  	  = dcep->dCtlRefNum;
msp->zCenter      = true;				/* Zoom to screen center is default.		*/
msp->theMode	  = msp->mode & 0x0F;	/* Strip out the hi-bits of the pixel mode. 	*/
msp->slowSpeed    =  1;					/* One pixel per pan for all modes.		*/
msp->fastSpeed    =  2 << msp->theMode;	/* 8-bit = Sixteen pixels per pan.		*/
										/* 4-bit = Eight pixels per pan.		*/
										/* 2-bit = Four pixels per pan.			*/
										/* 1-bit = Two pixels per pan.			*/
msp->enablePZ = false;					/* Pan & zoom not enabled */
msp->enableVD = false;					/* Enlarged panning not enabled */
GrayScreen(msp->mode,msp->screenbase);
#asm
    movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
#endasm
return(0);	/* Successful Open */
}
/* Prime is not used in this driver */
prime()
{
}
/********************************************************************************************/
/* 
   OSErr Control()
   Control() is called to set preferences for the driver's mode of operation. It simply 
   performs the action indicated in the paramblock passed to it. We support structures:
   CntrlParam, zoomCtrlParam and panInfoParam. Control() always returns the appropriate
   error code.
*/
OSErr control()
{
  register mystoragePtr msp;
  AuxDCEPtr dcep;        	/* Auxiliary Device Control Entry pointer. 			*/
  CntrlParam *pbp;     		/* Application-passed parameter block pointer. 			*/
  register unsigned long *dacaddr, *dacdata;
  register unsigned short mapmode,*modereg,i;	/* Grayscale or color mapping flag 		*/
  register unsigned long *ptr; 			/* Pointer to the TMS34061 Control Register 2 	*/
  register unsigned long *ptr1;
  GDHandle dev;  
  Ptr paramptr;			/* Local copy of pointer to csParam 				*/
  zoomCtrlParam *zp;     	/* Application-passed zoom & pan parameter block pointer. 	*/
  panInfoParam *pp;
  THz oldzone;               	/* Previous heap zone 						*/
  SlotIntQElement *sqeptr;   	/* Slot queue element pointer 					*/
  extern long intrpthandler, 	/* Define the interrupt handling routine as external; 		*/
              intrptend;     	/* As well as the end of the interrupt handler. 		*/ 
  OSErr error = noErr;
  OSErr setgamma();
  short defStart;		/* Default startup sResource ID in pRAM				*/
  short lastMode;
  
/* 0 - Init
   1 - KillIO
   2 - SetMode
   3 - SetEntries
   4 - SetGamma
   5 - GrayScreen
   6 - SetGray
   7 - SetInterrupt (0 => disable, 1 => enable)
(-1) - GoodBye
  8192 - Zoom In
  8193 - Zoom Out
  8194 - Pan X
  8195 - Pan Y
  8196 - Pan To
  8197 - SetRects
  8198 - SetXY
  8199 - SetSlow
  8200 - SetFast
  8201 - SetBorder
  8202 - SetPZ
  8203 - SetCenter
  8294 - SetVD
  
*/
#asm
    movem.l    a0-a5/d1-d7,-(sp)  ; save nearly all registers
#endasm
  save(&dcep,&pbp);      /* A0 -> pbp, A1 -> dcep */
msp = (mystoragePtr)(*(dcep->dCtlStorage));
zp  = (panCtrlParam *)pbp; 		    /* Set up our pan-status block pointer      */
pp  = (panInfoParam *)pbp;
paramptr = *((Ptr *)(pbp->csParam));
  /* Switch on the type of the type of action we are to repond to or do. */
switch(pbp->csCode)
  {
    case 0:         /* Reset the video card. (Init) */
        /* Set the return values we are responsible for. */
      	((VDPgInfoPtr)paramptr)->csMode = pix1;         /* Return that we're in 1-Bit mode. */
      	((VDPgInfoPtr)paramptr)->csPage = 0;
      	((VDPgInfoPtr)paramptr)->csBaseAddr = (Ptr)msp->screenbase;
        /* Set the mode variable in our private storage. */
      	msp->mode = pix1;
		msp->theMode = msp->mode & 0x0F;
        /* Reset the hardware to 1-bit mode. */
        /* Make a (short) pointer to the utility register. */
      	modereg  = (unsigned short *)(((unsigned long)(dcep->dCtlDevBase) & SLOTFss) + UTILADDRESS + 2);
      	mapmode  = *modereg;
      	mapmode &= 0xFFF3;
		
		*modereg = mapmode;
	
        /* Gray the screen using 1-bit mode.
      	GrayScreen(msp,(unsigned long)(dcep->dCtlDevBase));  */
      	break;
    case 1:         /* Remove all pending I/O. (KillIO) */
      	break;
    case 2:	    /* Set the card's video mode. (SetMode) */	
        /* Set the mode variable in our private storage. */
		lastMode = msp->mode;
      	msp->mode = ((VDPgInfoPtr)paramptr)->csMode;
		/* Check for a valid mode */
		if ((msp->mode < 0x80) || (msp->mode > 0x80)) error = controlErr;
		if (error == controlErr)
	  	  {
	    	msp->mode = lastMode;   /* Restore the old mode */
	    	break;			/* Return the error */
	  	  }
		msp->theMode = msp->mode & 0x0F;
     	/* Figure out the number of pages available for use: */
		/* the algorithm is: pages = 8 / mode. (mode is one of 1,2,4,8) */		
  		msp->pages = EIGHTBIT >> (msp->mode - PIXSTART);
        /* Make a (short) pointer to the mode register. */
      	modereg = (unsigned short *)(((unsigned long)(dcep->dCtlDevBase) & SLOTFss) + UTILADDRESS + 2);
        /* Use mapmode as a scratch variable to get the positioned mode bits. */
		/* The pixel depth is in bits 2 & 3 */
      	mapmode  = *modereg;	/* Get the current contents of the mode register */
      	mapmode &= 0xFFF3;	/* Strip out the pixel mode bits */
      	mapmode |= (msp->mode & 3)<<2;	/* Set our new pixel depth */
		*modereg = mapmode;	/* Stuff it in the mode register */
	
        /* Set the return values we are responsible for. */
      	((VDPgInfoPtr)paramptr)->csBaseAddr = (Ptr)msp->screenbase;
		((VDPgInfoPtr)paramptr)->csPage     = msp->pages;	
      	break;
    case 3:         /* Change card's color lookup table(s). (SetEntries) */
     	break;
    case 4:         /* Change card's gamma table. (SetGamma) */
      	break;
    case 5:         /* Gray the video page with dithered grey, (GrayScreen) */
        /* using the current screen size and mode. */
		GrayScreen(msp->mode,msp->screenbase);
      	break;
    case 6:         /* Map color lookup table(s) to color or grayscale. SetGray) */
      	break;
    case 7:         /* If csCode is 0 disable interrupts, else enable them (SetInterrupts() */
    	msp->InterruptFlag = (((VDPgInfoPtr)paramptr)->csMode) ? true : false;
#asm
  movem.l    a0-a5/d1-d7,-(sp)  ; save nearly all registers
#endasm
		if (msp->InterruptFlag)
	     {
			if (!(msp->myintrptcode = (unsigned char *)NewPtr((unsigned long)&intrptend-(unsigned long)&intrpthandler)))
		      {
		    	SetZone(oldzone);              /* Force memory operations to the original heap. 	*/
		    	DisposHandle(dcep->dCtlStorage);
#asm
  movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
#endasm
		    	error = controlErr;                   /* Return that we couldn't open successfully. 	*/
		    	break;
		  	  }
  
			BlockMove(&intrpthandler,msp->myintrptcode,(unsigned long)&intrptend-(unsigned long)&intrpthandler);
			if (!(sqeptr = (SlotIntQElement *)NewPtr((long)sizeof(SlotIntQElement))))
		  	  {
		    	SetZone(oldzone);              /* Force memory operations to the original heap. 	*/
#asm
  movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
#endasm
		    	DisposPtr(msp->myintrptcode);
		    	DisposHandle(dcep->dCtlStorage);
		    	error = controlErr;                   /* Return that we couldn't open successfully. 	*/
		    	break;
		  	  }
			msp->myslotqeleptr = sqeptr;
			SetZone(oldzone);                /* Force memory operations to the original heap. 	*/
			/* Set up the fields of the slot queue element block. 					*/
			sqeptr->sqLink = 0;
			sqeptr->sqType = 6;
			sqeptr->sqPrio = 0;
			sqeptr->sqAddr = (ProcPtr)msp->myintrptcode;
			sqeptr->sqParm = dcep->dCtlDevBase;
			/* Install that slot queue element into the interrupt table. 				*/
			if(mysintinstall(sqeptr,dcep->dCtlSlot))
		  	  {
#asm
  movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
#endasm
		    	SetZone(oldzone);              /* Force memory operations to the original heap. 	*/
		    	DisposPtr(sqeptr);
		    	DisposPtr(msp->myintrptcode);
		    	DisposHandle(dcep->dCtlStorage);
		    	error = controlErr;                   /* Return that we couldn't open successfully. 	*/
		    	break;
		  	  }
			/* Turn interrupts on. */
			*(unsigned long *)(((unsigned long)(dcep->dCtlDevBase)) + VIDINTERRUPT) = interruptOn;
	   	  }
		else
	   	  {
			/* Turn interrupts off. 		*/
			*(unsigned long *)(((unsigned long)(dcep->dCtlDevBase)) + VIDINTERRUPT) = interruptOff;
			mysintremove(msp->myslotqeleptr,dcep->dCtlSlot);	/* Pull interrupts out.	*/
			DisposPtr(msp->myslotqeleptr);	/* Nuke our slot queue element block. */
			DisposPtr(msp->myintrptcode);	/* Nuke our interrupt code block. */
	   	  }
#asm
  movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
#endasm
		break;
    case 9:         /* Set default mode */
      	defStart = *((char *) &(((VDPgInfoPtr)paramptr)->csMode));
      	defStart &= 0x008F;
        if (defStart > 0x88) 
		  {
		    putPRAM5(dcep->dCtlSlot,0);
		    putPRAM6(dcep->dCtlSlot,0);
	      }
     	else 
		  {
		    if (defStart < 0x84) putPRAM5(dcep->dCtlSlot,defStart);
		    putPRAM6(dcep->dCtlSlot,defStart);
	      }
      break;
    case 8192:	   /* Zoom in */
      	if (msp->enablePZ) ZoomIn(msp);
		break;      
    case 8193:	   /* Zoom Out */
		if (msp->enablePZ) ZoomOut(msp);
		break;
		
    case 8194:	   /* Pan X according to the paramblock sent:
       		          The paramBlock specifies:
    		              short zp->csParam[0] = direction
		                  short zp->csParam[1] = speed			*/
		zp = (zoomCtrlParam *)pbp;
		/* PanX(zp->csParam[0],zp->csParam[1], msp); */
		break;
		
    case 8195:	   /* Pan Y according to the paramblock sent:
    		          The paramBlock specifies:
    		              short zp->csParam[0] = direction
		         		  short zp->csParam[1] = speed			*/
		zp = (zoomCtrlParam *)pbp;
      	PanY(zp->csParam[0], zp->csParam[1], msp);
		break;
      
    case 8196:	   /* Pan To 
    		      The paramBlock specifies:
    		          short zp->csParam[0] = x
		          	  short zp->csParam[1] = y			*/
			zp = (zoomCtrlParam *)pbp;
      		PanTo(zp->csParam[0], zp->csParam[1], msp);
		break;
		
    case 8197:	   /* SetRects */ 
		dev = GetDeviceList();
		do
  		  {
    		if (msp->refNum == (*dev)->gdRefNum) 
       		  {
         		msp->theRect = (*dev)->gdRect;
         		break;
       		  }
  		  }
		while(dev = (GDHandle)(*dev)->gdNextGD);
		calcRects(msp);		/* Calculate our panning region.		*/
		break;
    case 8198:	    /* SetXY */
    	msp->currentX = zp->csParam[0];
		msp->currentY = zp->csParam[1];
		break;
    case 8199:	    /* SetSlow */
    	msp->slowSpeed = zp->csParam[0];
		break;
    case 8200:	    /* SetFast */
    	msp->fastSpeed = zp->csParam[0];
		break;
    case 8201:	    /* SetBorder */
    	msp->border = zp->csParam[0];
		break;
    case 8202:	    /* SetPZ */
    	msp->enablePZ = (zp->csParam[0]) ? true : false;
		break;
    case 8203:	    /* SetCenter */
    	msp->zCenter = (zp->csParam[0]) ? true : false;
		break;
    case 8204:	    /* SetVD */
    	msp->enableVD = (zp->csParam[0]) ? true : false;
		if (msp->enableVD)
		  {
		    msp->currentRate = 1 << (6 - msp->theMode);
		    switch(msp->screensize)
		      {
		        case mode1024: 	if (msp->xSize == mode1024) msp->enableVD = false;
		                       	else
				                  {
					   				msp->xResolution = 1024;
				           			msp->yResolution =  768;
					              }
				       			break;
		        case mode640:   msp->xResolution = 640;
				       			msp->yResolution = 870;
				       			break;
		      }
		  }
		break;
    case -1:      /* Goodbye condition.  Done when the "GoodBye Kiss" is given. 	*/
     	myclose();  /* Clean up things before leaving. 				*/
      	break;
		
   default:
		error = controlErr;
		break;
  }
#asm
    movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
#endasm
checkiodone(error);
return(error);
}
/****************************************************************************************/
/*
   OSErr status()
   
   The driver supports status calls for struct CntrlParam csCodes 2 through 6 and,
   8192 through 8196. All standard results are as documented in:
      "Designing Cards and Drivers for Macintosh II and Macintosh SE" (Addison Wesley, 1987.)
   All pan & zoom status results of type 'short' are returned in struct panCtrlParam 
   element csParam[0]. GetRects() returns struct panInfo. 
  csCode	Function	Requirements
     2		GetMode() 	get the card's video mode.
     3		GetEntries()	get values from card's color lookup table(s).
     4   	GetPages()	get the total number of video pages on the card.
     5   	GetBaseAddr()	get base address of specified page in current mode.
     6		GetGray()	get mapping mode (color or grayscale) of color lookup table(s).
     7		GetInterrupt()  get the status of the interrupts (1 = enabled, 0 otherwise)
     8		GetGamma()	get a pointer to the current gamma table data
     
  8192		GetPanRate()	get the scaling factor for the x/y panning rate.
  8193		GetSlow()	get the slow panning speed.
  8194		GetFast()	get the fast panning speed.
  8195		GetMargin()	get the width (in pixels) of the slow panning area.
  8196		GetZoom()	get the current zoom state (1 = x1, 2 = x2, 3 = x4.)
  8197		GetRects()	get the fast and slow panning rectangles.
  8198		GetXY()		get the currentX and currentY screen coordinates.
  8199		GetAll()	get all the various pan and zoom variables
  8200		GetPZMode()	get the pixel mode
  8201		GetPZ()		get the pan and zoom enable flag
*/
OSErr status()
{
  register mystoragePtr msp; /* Pointer to our private storage (globals.) 		*/
  AuxDCEPtr dcep;        /* Auxiliary Device Control Entry pointer. 			*/
  CntrlParam *pbp;       /* Application-passed parameter block pointer. 		*/
  Ptr paramptr;		 /* Local copy of pointer to csParam 				*/
  short defStart;	 /* Default startup sResource ID in pRAM			*/
  Ptr tempptr;
  OSErr error = noErr;
  panCtrlParam *zp;	 /* Application-passed pan-status parameter block pointer. 	*/
  panInfoParam *pp;	 /* Application-passed pan-info parameter block pointer. 	*/	
  GDHandle dev;  
  
#asm
    movem.l    a0-a5/d1-d7,-(sp)  ; save nearly all registers
#endasm
save(&dcep,&pbp);      				  /* A0 -> pbp, A1 -> dcep 		*/
msp = (mystoragePtr)(*(dcep->dCtlStorage)); /* Set up our pointer to the globals 	*/
zp  = (panCtrlParam *)pbp; 		    /* Set up our pan-status block pointer      */
pp  = (panInfoParam *)pbp;
paramptr = *((Ptr *)(pbp->csParam));
/* Do the function as requested in the csCode field of the CntrlParam struct. 	*/
switch(pbp->csCode)
  {
    case 2:   	/* GetMode() 		Get the card's video mode. 			*/
              	/*   			Set the return values we are responsible for. 	*/
      		((VDPgInfoPtr)paramptr)->csMode     = msp->mode;
      		((VDPgInfoPtr)paramptr)->csPage     = msp->pages;
      		((VDPgInfoPtr)paramptr)->csBaseAddr = (Ptr)msp->screenbase;
      		break;
			
    case 3:   	/* GetEntries()		Get values from card's color lookup table(s).	*/
      		break;
		
    case 4:   	/* GetPages()		Get the total number of video pages on the card.*/
      		((VDPgInfoPtr)paramptr)->csPage = msp->pages;
      		break;
		
    case 5:   	/* GetBaseAddr()	Get base address of specified page in current mode. */
      		#asm
	     				bra.s	getPage			; jump over the table
					
		 	modeTbl:
		 			DC.W	$AAAA,$AAAA,$0080,$0300	; 1-bit mode
		 			DC.W	$CCCC,$CCCC,$0100,$0300	; 2-bit mode
					DC.W	$F0F0,$F0F0,$0200,$0300	; 4-bit mode
					DC.W	$FF00,$FF00,$0400,$0300	; 8-bit mode
		 	getPage:
					move.l	$1C(A0),A2		; csParam(A0)     -> A2
		 			move.w	6(A2),D0		; csPage(A2)      -> D0 (the requested page)
		 			move.l	$14(A1),A3		; dCtlStorage(A1) -> A3 (pointer to our storage)
		 			move.w	$0A(A3),D1		; myMode(A3)      -> D1 (the current mode)
		 			sub 	#$80,D1			; make the mode a number from 0 to 3
		 			lea	modeTbl,A0		; A0 is the mode table
					mulu	4(A0,D1*8),D0		; D0 is page * rowBytes
					mulu	8(A0,D1*8),D0		; D0 is page * rowBytes * height
					add.l	$2A(A1),D0		; dCtlDevBase(A1) -> D0 (page * rowBytes * height) + base address of video ram
					move.l	D0,8(A2)		; D0 -> csBaseAddr(A2)  (return the base address)
	  	#endasm
      		break;
		
    case 6:   	/* GetGray()		Get mapping mode (color or grayscale) of color lookup table(s).	*/
      		((VDPgInfoPtr)paramptr)->csMode = msp->bwmapping;
      		break;
    case 7:   	/* GetInterrupts()	Get the status of the interrupts (1 = enabled, 0 otherwise)	*/
      		((VDPgInfoPtr)paramptr)->csMode = (msp->InterruptFlag) ? 1L : 0L;
      		break;
    case 8:   	/* GetGamma()		Get a pointer to the current gamma table data.			*/
      		break;
    case 9:    /* GetDefault()		Get the default startup resolution			        */
      defStart  = checkPRAM6(dcep->dCtlSlot); /* Get the default startup from pRAM 				*/
      defStart &= 0x00FF;     		 /* Mask off the hi-byte (the EXT.W make these contain 0xFF!) 	*/
      if (defStart == 0)
        {
	  /* If there isn't an Extended DeskTop then use the vendorUse5 byte of pRAM 			*/
	  defStart = checkPRAM5(dcep->dCtlSlot);
	  defStart &= 0x00FF;	/* Mask off the hi-byte (the EXT.W make these contain 0xFF!) 		*/
	}
      ((VDPgInfoPtr)paramptr)->csMode = defStart;	 /* Return the default 				*/
      break;
    /* Pan and Zoom status calls							*/
    case 8192:  /* GetPanRate() */
      		zp->csParam[0] = msp->currentRate;
    		break;
		
    case 8193:  /* GetSlow() */
      		zp->csParam[0] = msp->slowSpeed;
    		break;
		
    case 8194:  /* GetFast() */
      		zp->csParam[0] = msp->fastSpeed;
    		break;
		
    case 8195:  /* GetMargin() */
      		zp->csParam[0] = msp->border;
    		break;
		
    case 8196:  /* GetZoom() */
      		zp->csParam[0] = msp->currentZoom;
    		break;
		
    case 8197:  /* GetRects() */
		dev = GetDeviceList();
		do
  		  {
    		if (msp->refNum == (*dev)->gdRefNum) 
       		  {
         		msp->theRect = (*dev)->gdRect;
         		break;
       		  }
  		  }
		while(dev = (GDHandle)(*dev)->gdNextGD);
		calcRects(msp);		/* Calculate our panning region.		*/
		pp->fastRect = msp->theRect;
		pp->slowRect = msp->panRect; 
    	break;
    case 8198:  /* GetXY() */
      		zp->csParam[0] = msp->currentX;
      		zp->csParam[1] = msp->currentY;
		break;
    case 8199:  /* GetAll() */
		dev = GetDeviceList();
		do
  		  {
    		if (msp->refNum == (*dev)->gdRefNum) 
       		  {
         		msp->theRect = (*dev)->gdRect;
         		break;
       	      }
  		  }
		while(dev = (GDHandle)(*dev)->gdNextGD);
		calcRects(msp);		/* Calculate our panning region.		*/
      	zp->csParam[ 0] = msp->currentZoom;
      	zp->csParam[ 1] = msp->currentX;
      	zp->csParam[ 2] = msp->currentY;
      	zp->csParam[ 3] = msp->theMode;
      	zp->csParam[ 4] = msp->border;
      	zp->csParam[ 5] = msp->fastSpeed;
      	zp->csParam[ 6] = msp->slowSpeed;
      	zp->csParam[ 7] = msp->slot;
      	zp->csParam[ 8] = msp->panRect.top;
      	zp->csParam[ 9] = msp->panRect.left;
      	zp->csParam[10] = msp->panRect.bottom;
      	zp->csParam[11] = msp->panRect.right;
      	zp->csParam[12] = msp->theRect.top;
      	zp->csParam[13] = msp->theRect.left;
      	zp->csParam[14] = msp->theRect.bottom;
      	zp->csParam[15] = msp->theRect.right;
      	zp->csParam[16] = msp->xSize;
      	zp->csParam[17] = msp->ySize;
      	zp->csParam[18] = msp->currentRate;
		zp->csParam[19] = msp->enableVD;
		zp->csParam[20] = msp->xResolution;
		zp->csParam[21] = msp->yResolution;
		break;
    case 8200:  /* GetPZMode() */
		zp->csParam[0] = msp->theMode;
		break;
		
    case 8201:  /* GetPZ() */
    		zp->csParam[0] = (msp->enablePZ) ? 1 : 0;
		break;
		
    case 8202:  /* GetCenter() */
    		zp->csParam[0] = (msp->zCenter) ? 1 : 0;
		break;
    default:    error = statusErr;
		
  }
#asm
    movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
#endasm
checkiodone(error);
return(error);
}
/* This routine is run whenever the driver is told to close. 			*/
myclose()
{
  AuxDCEPtr dcep;        /* Auxiliary Device Control Entry pointer. 		*/
  register mystoragePtr msp;
  register unsigned long *ptr;
  CntrlParam *pbp;     /* Application-passed parameter block pointer. 	*/
#asm
    movem.l    a0-a5/d1-d7,-(sp)  ; save nearly all registers
#endasm
/* A0 -> pbp, A1 -> dcep 		*/
save(&dcep,&pbp);     
msp = (mystoragePtr)(*(dcep->dCtlStorage));
/* Turn off the screen */
ptr = (unsigned long *)(dcep->dCtlDevBase + TMS34061);
*((unsigned long *)&((unsigned char *)ptr)[0xC8]) = 0x48;		/* control2, bit 13 = screenEnable (1 = run) */
/* Turn interrupts off. 		*/
*(unsigned long *)(((unsigned long)(dcep->dCtlDevBase)) + VIDINTERRUPT) = interruptOff;
/* Pull interrupts out. 		*/
mysintremove(msp->myslotqeleptr,dcep->dCtlSlot);
/* Nuke our slot queue element block. 	*/
DisposPtr(msp->myslotqeleptr);
/* Nuke our interrupt code block. 	*/
DisposPtr(msp->myintrptcode);
/* Nuke our variable storage block. 	*/
HUnlock(dcep->dCtlStorage);
DisposHandle(dcep->dCtlStorage);
#asm
    movem.l    (sp)+,a0-a5/d1-d7  ; restore nearly all registers
#endasm
/* Successful Close 			*/
return(0);             
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
    ADDA.L  #$400D0,A0     ; add offset to clear video interrupt (read a long register)
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
#endasm
void GrayScreen(theMode,theBase)
short theMode;
unsigned long theBase;
{
#asm
;---------------------------------------------------------------------
;			D0 = Page
;			A3 = dCtlStorage Ptr.
;
;  All registers are preserved.
	BRA.S	GStart
	
; Mode info:     Pattern,Bytes-per-row,Height
ModTbl:	
	DC.W	$AAAA,$AAAA,$0080,$0300		; one bit per pixel
GStart	MOVEM.L	D0-D4/A0-A3,-(SP)	; save all registers		
	MOVE.W	8(A6),D1		; get the mode
	ANDI.W	#3,D1			; make it 0 based
  	LEA		ModTbl,A1		; point to tables	
	MOVE.L	0(A1,D1*8),D0	; D0 = the proper pattern
	MOVE.W	4(A1,D1*8),D4	; D4 = bytes per row for the screen
	MOVE.W	6(A1,D1*8),D3	; D3 = screen height				
	SUBQ	#1,D3			; make it 0 based
	MOVE.L	D0,D1			; get inverse of pattern		
	NOT.L	D1				; for alternate lines				
	MOVE.L	10(A6),A1		; point to the screenbase			
NxtRow1	
	MOVE.L	A1,A0			; get next row
	MOVE.W	D4,D2			; get bytes per row
	LSR		#2,D2			; get longs per row
	SUB.W	#1,D2			; make count 0 based
NxtLong1	
	MOVE.L	D0,(A0)+		; write gray
	DBF		D2,NxtLong1		; for entire width of row		
	EXG		D0,D1			; get inverse gray for next row		
	ADD.W	#$400,A1		; bump to next row
	DBF		D3,NxtRow1		; until no more rows
GSDone
	MOVEM.L	(SP)+,D0-D4/A0-A3	; restore all registers							
#endasm
}
/********************************************************************************************/
void OWaitForVBlank(base)
unsigned long base;
{
#asm
	BRA.S	owaitHere
oRD1 DC.L	0
oRD2 DC.L	0
oRD3 DC.L	0
oRA0 DC.L	0
owaitHere
    MOVE.L	A0,D0
	LEA		oRD1,A0
	MOVE.L	D1,(A0)+
	MOVE.L	D2,(A0)+
	MOVE.L	D3,(A0)+
	MOVE.L	D0,(A0)+
	MOVEA.L	8(SP),A0
    MOVE.W  SR,-(SP)     	; Stash current status register
    MOVE.W  #$2200,SR    	; Shut interrupts off (at least most of them)
	MOVE.L	#$C0060,D1		; 34061 vertical start blank register
	MOVE.L	#$C0110,D2		; 34061 vertical count register
	CLR.L	D4
	MOVE.B	11(A0,D1.L),D4	; get the StartBlank hi byte
	ASL.L	#8,D4
	ADD.B   3(A0,D1.L),D4	; get the StartBlank lo byte
owait4Blank
	CLR.L	D3
	MOVE.B	11(A0,D2.L),D3	; get the count hi byte
	ASL.L	#8,D3
	MOVE.B	3(A0,D2.L),D3	; get the count lo byte
	CMP.W	D3,D4
	BGE.S	owait4Blank
owait4Blank2
    CLR.L	D3
	MOVE.B	11(A0,D2.L),D3	; get the count hi byte
	ASL.L	#8,D3
	MOVE.B	3(A0,D2.L),D3	; get the count lo byte
	CMP.W	D3,D4
	BLE.S	owait4Blank2
	
    MOVE.W  (SP)+,SR     	; Put interrupts back to before
	LEA		RD1,A0
	MOVE.L	(A0)+,D1
	MOVE.L	(A0)+,D2
	MOVE.L	(A0)+,D3
	MOVE.L	(A0)+,D0
	MOVE.L	D0,A0
#endasm
}
void WaitForVBlank(base)
unsigned long base;
{
#asm
	BRA.S	waitHere
RD1 DC.L	0
RD2 DC.L	0
RD3 DC.L	0
RD4 DC.L	0
RD5 DC.L    0
RA0 DC.L	0
waitHere
    MOVE.L	A0,D0
	LEA		RD1,A0
	MOVE.L	D1,(A0)+
	MOVE.L	D2,(A0)+
	MOVE.L	D3,(A0)+
	MOVE.L	D4,(A0)+
	MOVE.L	D5,(A0)+
	MOVE.L	D0,(A0)+
	MOVEA.L	8(SP),A0
    MOVE.W  SR,-(SP)     	; Stash current status register
    MOVE.W  #$2200,SR    	; Shut interrupts off (at least most of them)
	MOVE.L	#$C0060,D1		; 34061 vertical start blank register
	MOVE.L	#$C0110,D2		; 34061 vertical count register
	CLR.L	D4
	MOVE.B	11(A0,D1.L),D4	; get the StartBlank hi byte
	ROL.L	#8,D4
	MOVE.B   3(A0,D1.L),D4	; get the StartBlank lo byte
wait4Blank
	CLR.L	D3
	MOVE.B	11(A0,D2.L),D3	; get the count hi byte
	ROL.L	#8,D3
	MOVE.B	3(A0,D2.L),D3	; get the count lo byte
	CLR.L	D5
	MOVE.B	11(A0,D2.L),D5	; get the count hi byte
	ROL.L	#8,D5
	MOVE.B	3(A0,D2.L),D5	; get the count lo byte
	CMP		D3,D5
	BNE.S	wait4Blank
	
	CMP.W	D4,D3
	BMI.S	wait4Blank
	
    MOVE.W  (SP)+,SR     	; Put interrupts back to before
	LEA		RD1,A0
	MOVE.L	(A0)+,D1
	MOVE.L	(A0)+,D2
	MOVE.L	(A0)+,D3
	MOVE.L	(A0)+,D4
	MOVE.L	(A0)+,D5
	MOVE.L	(A0)+,D0
	MOVE.L	D0,A0
#endasm
}
/********************************************************************************************/
/* Had to do this myself due to a bug in the Aztec C compiler (3.6B) */
void putPRAM6(slot,sRecID)
short slot,sRecID;
{
#asm
    BRA.S   inPRAM6
PRAM6Rec
    DC.W    0
    DC.W    0
    DC.W    0
    DC.W    0
    
inPRAM6
    MOVE.W   8(A6),D0		; Get the slot number
    LEA     -56(SP),SP          ; Allocate a SpBlock on the stack
    MOVE.L  SP,A0               ; Get the address of the SpBlock in A0 (required by slot manager calls)
    MOVE.B  D0,49(A0)           ; Poke the slot number
    CLR.B   51(A0)              ; Poke the external device number (we don't have one, so zero)
    LEA     PRAM6Rec,A1
    MOVE.L  A1,0(A0)
    MOVEQ   #17,D0              ; Use the sReadPRAMRec call of the slot manager
    DC.W    $A06E               ; _SlotManager
    LEA     PRAM6Rec,A1		; Get the address of our PRAM record
    MOVE.W  10(A6),D0		; get the vendorUse6 byte passed to us
    MOVE.B  D0,7(A1)		; put it in the vendorUse6 byte for the primaryinit
    MOVE.L  SP,A0               ; Get the address of the SpBlock in A0 (required by slot manager calls)
    MOVE.L  A1,4(A0)		; put a pointer to the pRAM record in the SpsPointer field
    MOVEQ   #18,D0              ; Use the sPutPRAMRec call of the slot manager
    DC.W    $A06E               ; _SlotManager
    LEA     56(SP),SP           ;We don't check errors, so just repair the stack and exit
#endasm
}
/********************************************************************************************/
/* Had to do this myself due to a bug in the Aztec C compiler (3.6B) */
void putPRAM5(slot,sRecID)
short slot,sRecID;
{
#asm
    BRA.S   inPRAM5
PRAM5Rec
    DC.W    0
    DC.W    0
    DC.W    0
    DC.W    0
    
inPRAM5
    MOVE.W   8(A6),D0		; Get the slot number
    LEA     -56(SP),SP          ; Allocate a SpBlock on the stack
    MOVE.L  SP,A0               ; Get the address of the SpBlock in A0 (required by slot manager calls)
    MOVE.B  D0,49(A0)           ; Poke the slot number
    CLR.B   51(A0)              ; Poke the external device number (we don't have one, so zero)
    LEA     PRAM5Rec,A1
    MOVE.L  A1,0(A0)
    MOVEQ   #17,D0              ; Use the sReadPRAMRec call of the slot manager
    DC.W    $A06E               ; _SlotManager
    LEA     PRAM5Rec,A1		; Get the address of our PRAM record
    MOVE.W  10(A6),D0		; get the vendorUse6 byte passed to us
    MOVE.B  D0,6(A1)		; put it in the vendorUse6 byte for the primaryinit
    MOVE.L  SP,A0               ; Get the address of the SpBlock in A0 (required by slot manager calls)
    MOVE.L  A1,4(A0)		; put a pointer to the pRAM record in the SpsPointer field
    MOVEQ   #18,D0              ; Use the sPutPRAMRec call of the slot manager
    DC.W    $A06E               ; _SlotManager
    LEA     56(SP),SP           ;We don't check errors, so just repair the stack and exit
#endasm
}
/********************************************************************************************/
/* Had to do this myself due to a bug in the Aztec C compiler (3.4B) */
short checkPRAM6(slot)
short slot;
{
#asm
    BRA.S   checkPRAM6
PRAM6
    DC.W    0
    DC.W    0
    DC.W    0
    DC.W    0
    
; Do slot resource deletion for unused resolutions
checkPRAM6
    MOVE.W   8(A6),D0		; Get the slot number
    LEA     -56(SP),SP          ; Allocate a SpBlock on the stack
    MOVE.L  SP,A0               ; Get the address of the SpBlock in A0 (required by slot manager calls)
    MOVE.B  D0,49(A0)           ; Poke the slot number
    CLR.B   51(A0)              ; Poke the external device number (we don't have one, so zero)
    LEA     PRAM6,A1
    MOVE.L  A1,0(A0)
    MOVEQ   #17,D0              ; Use the SReadPRAMRec call of the slot manager
    DC.W    $A06E               ; _SlotManager
    LEA     PRAM6,A1		; Get the address of our PRAM record
    MOVE.B  7(A1),D0		; check the vendorUse6 byte
    EXT.W   D0			; return it as a word
    LEA     56(SP),SP           ; Repair the stack
#endasm
}
/********************************************************************************************/
/* Had to do this myself due to a bug in the Aztec C compiler (3.4B) */
short checkPRAM5(slot)
short slot;
{
#asm
    BRA.S   checkPRAM5
PRAM5
    DC.W    0
    DC.W    0
    DC.W    0
    DC.W    0
    
; Do slot resource deletion for unused resolutions
checkPRAM5
    MOVE.W   8(A6),D0		; Get the slot number
    LEA     -56(SP),SP          ; Allocate a SpBlock on the stack
    MOVE.L  SP,A0               ; Get the address of the SpBlock in A0 (required by slot manager calls)
    MOVE.B  D0,49(A0)           ; Poke the slot number
    CLR.B   51(A0)              ; Poke the external device number (we don't have one, so zero)
    LEA     PRAM5,A1
    MOVE.L  A1,0(A0)
    MOVEQ   #17,D0              ; Use the SReadPRAMRec call of the slot manager
    DC.W    $A06E               ; _SlotManager
    LEA     PRAM5,A1		; Get the address of our PRAM record
    MOVE.B  6(A1),D0		; check the vendorUse5 byte
    EXT.W   D0			; return it as a word
    LEA     56(SP),SP           ; Repair the stack
#endasm
}
/********************************************************************************************/
short abs(number)
short number;
{
  short value;
return(value = (number < 0) ? number * (-1) : number);
}
/********************************************************************************************/
/* 
   void calcRects()
   
   Set up our fastSpeed & slowSpeed pan rectangles. Any mouse movement inside the
   panRect does NOT generate pan commands. Any mouse movement outside the panRect,
   but inside the currentScreen generates a slowSpeed pan command. Any mouse movement
   outside the currentScreen generates a fastSpeed pan command.
   Input:	msp				pointer to our globals			
   
   Uses:	currentY		(global) determines the "y" coordinates
   			currentX		(global) determines the "x" coordinates
   			currentZoom		(global) zoom state
			xSize			(global) virtual screen size
			ySize			(global) virtual screen size
			xResolution		(global) enlarged panning area real screen size
			yResolution		(global) enlarged panning area real screen size
			enableVD		(global) flag determining enlarged panning area
			Border			(global) determines the panning area
			
   Assigns:	currentScreen	(global) the rectangle of the current viewing screen
			panRect			(global) the rectangle enclosing the non-panning area
*/
void calcRects(msp)
mystoragePtr msp;
{
  Point theTop, theBottom;
theTop.h = msp->currentX + msp->theRect.left; 
theTop.v = (msp->currentY >> 2) + msp->theRect.top;
if (msp->enableVD)
  {
    theBottom.h = theTop.h + (msp->xResolution >> (msp->currentZoom - 1));
    theBottom.v = theTop.v + (msp->yResolution >> (msp->currentZoom - 1));
  }
else
  {
    theBottom.h = theTop.h + (msp->xSize >> (msp->currentZoom - 1));
    theBottom.v = theTop.v + (msp->ySize >> (msp->currentZoom - 1));
  }
SetRect(&msp->currentScreen, theTop.h, theTop.v, theBottom.h, theBottom.v);
SetRect(&msp->panRect, msp->currentScreen.left, msp->currentScreen.top, msp->currentScreen.right, msp->currentScreen.bottom);
InsetRect(&msp->panRect, msp->border, msp->border);
}
/********************************************************************************************/
/* 
   void PanTo(x,y,msp)
   
   Pan to the given x,y coordinates.
   The Colorboard 108+ pan (x) register (8-bit) is at: 0xD8000. The pan (y) register is
   in the TMS34061 Display Start Register which can be accessed as two byte locations:
   		lo byte: 	0xFssC0093
   		hi-byte: 	0xFssC009B
   These two locations determine the row address of the starting video line.
   Input:	x		The 'x' coordinate at the top left of the view screen.
   		y		The 'y' coordinate at the top left of the view screen.
   		msp             Auxiliary Device Control Entry pointer.
*/
void PanTo(x,y,msp)
short x,y;
mystoragePtr msp;
{
  unsigned long devbase = 0;
  unsigned long xBase;
  unsigned long y1Base, y2Base;
devbase  = devBase(msp->slot);
y1Base   = devbase | 0xC0093;
y2Base   = devbase | 0xC009B;
xBase    = devbase | 0xD8003;
#asm
    MOVE.W  SR,-(SP)     ; Stash current status register
    MOVE.W  #$2200,SR    ; Shut interrupts off (at least most of them)
#endasm
*((unsigned char *) (xBase))  = (x>>(2+(3-msp->theMode))) & 0x00FF;
*((unsigned char *) (y1Base)) = (y<<2) & 0x00FF;
*((unsigned char *) (y2Base)) = ((y<<2) & 0x0F00) >> 8;
#asm
    MOVE.W  (SP)+,SR     ; Put interrupts back to before
#endasm
}
/************************************************************************************************/
/* 
  void Center(msp,direction)
  Center the zoom based on the global Boolean zCenter. 
  If zCenter is true we do a screen centered zoom.
  If zCenter is false we do a mouse based zoom.
  (Note: the top left of the screen is at 0,0 local coordinates
   the bottom right is at xSize-1,ySize-1 local coordinates)
  
  Input:	msp
            direction	In /Out (0/1)
  Uses:		zCenter 
  			currentRate
  			theMode
  			currentZoom
  Assigns:	currentX
  			currentY
  		
*/
void Center(msp,direction)
mystoragePtr msp;
short direction;
{
  Point mouseLoc;
  register short xBounds, yBounds;
  register short tempX, tempY;
  register short tempZoom;
  unsigned long devbase = 0;
  unsigned char *xBase, *y1Base, *y2Base;
devbase  = devBase(msp->slot);
y1Base   = (unsigned char *)(devbase + 0xC0093);
y2Base   = (unsigned char *)(devbase + 0xC009B);
xBase    = (unsigned char *)(devbase + 0xD8003);
tempZoom = msp->currentZoom-1;
if (msp->enableVD)
  {
    tempX   = msp->xResolution;
    tempY   = msp->yResolution;
  }
else
  {
    tempX   = msp->xSize;
    tempY   = msp->ySize;
  }
tempX >>= tempZoom;
tempY >>= tempZoom;
xBounds = msp->xSize - tempX;
yBounds = msp->ySize - tempY;
tempX >>= 1;
tempY >>= 1;
if (msp->zCenter)
  {
    /* Get the current x,y coordinates */
    msp->currentX = *xBase & 0xFF;
	msp->currentX <<= (5-msp->theMode);		/* Was just 2 */
	msp->currentY = (*y1Base & 0xFF) + ((*y2Base & 0x0F) << 8);
	msp->currentY >>= 2;
	
    if (direction) msp->currentX -= tempX >> 1;
    else msp->currentX += tempX;
    if (msp->currentX < 0) msp->currentX = 0;		/* Stay on the screen */
    if (msp->currentX > xBounds) msp->currentX = xBounds;
		
    if (direction) msp->currentY -= tempY >> 1;
    else msp->currentY += tempY;
    if (msp->currentY < 0) msp->currentY = 0;		/* Stay on the screen */      		
    if (msp->currentY > yBounds) msp->currentY = yBounds;
  }
else
  {
    GetMouse(&mouseLoc);
    LocalToGlobal(&mouseLoc);
	/* Adjust for multiple monitors */
	/* Check left/right */
    if ((mouseLoc.h < 0) || (mouseLoc.h > msp->xSize)) mouseLoc.h -= msp->theRect.left;
    /* Check up/down */
	if ((mouseLoc.v < 0) || (mouseLoc.v > msp->ySize)) mouseLoc.v -= msp->theRect.top;
	
    /* Do X coordinate */
    msp->currentX = mouseLoc.h - tempX;
    if (msp->currentX < 0) msp->currentX = 0;		/* Stay on the screen */
    if (msp->currentX > xBounds) msp->currentX = xBounds;
    
    /* Do Y coordinate */
    msp->currentY = mouseLoc.v - tempY;
    if (msp->currentY < 0) msp->currentY = 0;
    if (msp->currentY > yBounds) msp->currentY = yBounds;		
  }   
}
/********************************************************************************************/
/* 
   void ZoomIn()
   
   Zoom In.
   
   Input:	msp             Auxiliary Device Control Entry pointer.
   Uses:	xSize		(global) determines the "x" boundary
			slot		(global) determines the hardware addresses
				
   Assigns:	currentRate	(global) 1 << (7 - theMode) = zoom 2X,
   			currentZoom	(global) 2 = zoom 2X, 3 = zoom 4X
   			currentX	(global) the top left of our new viewing screen
   			currentY	(global) the bottom right of new current viewing screen
   Calls:	PanTo()		Go to the new x,y of our current viewing screen
   			calcRects()	Both currentX & currentY have changed
   
*/
void ZoomIn(msp)
mystoragePtr msp;
{
  unsigned long devbase = 0;
  unsigned long xBase, yBase;
  unsigned short sUtilValue,  utilValue;
  unsigned char  cCtrl2Value, ctrl2Value;
  void PanY();
  
devbase     = devBase(msp->slot);
xBase       = devbase | 0xD0002;
yBase       = devbase | 0xC0083;
sUtilValue  = *((unsigned short *)(xBase));
utilValue   = sUtilValue & 0xFFCF;
cCtrl2Value = *((unsigned char *)(yBase));
switch(sUtilValue & 0x0030)
  {
    case 0x0000:	utilValue  	|= 0x0010;
    		  		ctrl2Value  	 = 2;
    		  		msp->currentRate = 1 << (6 - msp->theMode);
    		 		msp->currentZoom = 2;
   		 	    	Center(msp,0);
    		 		break;
    case 0x0010:	utilValue  	|= 0x0020;
    		 		ctrl2Value  	 = 1;
    		  		msp->currentRate = 1 << (7 - msp->theMode);
    		 		msp->currentZoom = 3;
   		 	    	Center(msp,0);
   		 	    	break;
    case 0x0020:  	return;
  }
OWaitForVBlank(devbase);
*((unsigned short *) (xBase)) = utilValue;
*((unsigned char *)  (yBase)) = ctrl2Value;
PanTo(msp->currentX,msp->currentY,msp);
PanY(-1,0,msp);
calcRects(msp);
}
/********************************************************************************************/
/* 
   void ZoomOut()
   
   Zoom Out.
   The ClearVue/GS uses the word at 0xFssD0002 for the zoom (x) (bits 4 & 5.)
       00 = zoom 1X, 01 = zoom 2x, 10 = zoom 4X (binary.)
    The zoom (y) register uses the byte at 0xFssC00083 (bits 3 & 4.)
       00 = zoom 4X, 01 = zoom 2x, 10 = zoom 1X (binary.)
  
   Input:	msp             Auxiliary Device Control Entry pointer.
   Uses:	xSize		(global) determines the "x" boundary
			slot		(global) determines the hardware addresses
   Assigns:	currentRate	(global) 0 = zoom 1X, 1 << (7 - theMode) = zoom 2X
   			currentZoom	(global) 1 = zoom 1X, 2 = zoom 2X
   			currentX	(global) the top left of our new viewing screen
   			currentY	(global) the bottom right of our new viewing screen
   Calls:	PanTo()		Go to the x,y of our new viewing screen
   			calcRects()	Both currentX & currentY have changed
   				
*/
void ZoomOut(msp)
mystoragePtr msp;
{
  unsigned long devbase = 0;
  unsigned long xBase, yBase;
  short tempX, tempY;
  unsigned short sUtilValue;
  unsigned short utilValue;
  unsigned char  cCtrl2Value;
  unsigned char  ctrl2Value;
devbase  = devBase(msp->slot);
xBase = devbase | 0xD0002;
yBase = devbase | 0xC0083;
sUtilValue  = *((unsigned short *) (xBase));
utilValue   = sUtilValue & 0xFFCF;
cCtrl2Value = *((unsigned char *) (yBase));
switch(sUtilValue & 0x0030)
  {
    case 0x0000:  
    case 0x0010:  	utilValue  	&= 0xFFCF;
    		 		ctrl2Value  	 = 4;
    		 		msp->currentRate = (msp->enableVD) ? 1 << (6 - msp->theMode) : 0;
    		 		msp->currentZoom = 1;
    		 		Center(msp,1);
    		 		break;
			  
    case 0x0020:	utilValue  	|= 0x0010;
    		 		ctrl2Value  	 = 2;
    		 		msp->currentRate = 1 << (7 - msp->theMode);
   		 			msp->currentZoom = 2;
   		 			Center(msp,1);
    		 		break;
  }
OWaitForVBlank(devbase);
*((unsigned short *) (xBase)) = utilValue;
*((unsigned char *)  (yBase)) = ctrl2Value;
PanTo(msp->currentX, msp->currentY,msp);
PanY(-1,0,msp);
calcRects(msp);
}
/********************************************************************************************/
/* 
   void PanY()
   
   Pan in the y-direction.
   The ClearVue/GS pan (y) registerin the TMS34061 Display Start Register
   there are two byte locations: lo byte - 0xC0093 & hi-byte - 0xC009B which
   determine the row address of the starting video line.
          
   Input:	direction		(-1) = pan down, 0 = pan up.
   			speed			fastSpeed or slowSpeed
   			msp             Auxiliary Device Control Entry pointer.
   Uses: 	slot 			(global) to compute the hardware addresses.
   			currentRate		(global) used to determine the pan rate of speed
            ySize			(global) to calculate the boundary of our view screen.
            currentZoom		(global) return if we are at zoom = 1X.
   Assigns: currentY   		(global) bottom right of our view screen rectangle.
   Calls:	calcRects()		currentY was changed.
   
*/
void PanY(direction, speed, msp)
short direction, speed;
mystoragePtr msp;
{
  register unsigned long devbase = 0;
  register unsigned long y1Base;
  register unsigned long y2Base;
  register unsigned short videoStart;
  register short tempStart, yBounds;
  unsigned char y1Value, y2Value;
devbase  = devBase(msp->slot);
y1Base   = devbase | 0xC0093;
y2Base   = devbase | 0xC009B;
y1Value  = *((unsigned char *) (y1Base));
y2Value  = *((unsigned char *) (y2Base));
videoStart  = ((y2Value << 8) & 0x0F00) + y1Value;
yBounds  = (msp->enableVD) ? msp->ySize + (msp->yResolution - (msp->yResolution>>2)) : msp->ySize;
if ((msp->enableVD) && (msp->yResolution == 600)) yBounds = 670;
tempStart = (direction)  ? videoStart - (msp->currentRate * speed * 2) : videoStart + (msp->currentRate * speed * 2);
if ( (tempStart > 0) && (tempStart < (yBounds * msp->currentZoom)) ) videoStart = (unsigned short) tempStart;
if (tempStart >= (yBounds * msp->currentZoom)) videoStart = yBounds * msp->currentZoom;
else if (tempStart <= 0) videoStart = 0;
          
*((unsigned char *) (y1Base)) = (unsigned char)(videoStart & 0xFF);
*((unsigned char *) (y2Base)) = (unsigned char)((videoStart >> 8) & 0x0F);
msp->currentY = videoStart;
calcRects(msp);
}
#asm
; ==================END OF DRIVER BLOCK=============
    public endmydrvr
#endasm
