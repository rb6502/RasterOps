/* RasterOps MediaTime(24MTV) Board Declaration ROMs */
/* MediaTime		v2.0 */
/* This is written in Aztec C, version 3.6B by Jim Huffman */
/* PZE code written in Aztec C, version 3.6B by Wade Eilrich */
/* Compile under MPW 3.0 shell */
/* Thursday, December 6, 1990 11:55:23 AM - Created from 264,208,364,24S - JWH */
/* Thursday, December 6, 1990 11:55:23 AM - Created from 264,208,364,24S - JWH */
/* 6/20/94 10:16:37 AM - v2.0d1: adapted from 24STV v2.0d2 - jwh */
/* 7/5/94 11:02:26 AM - v2.0b2: energy saver bug - jwh */
/* 7/8/94 11:17:16 AM - v2.0b3: fixed bug in cycling text - jwh */
/* 7/13/94 10:03:43 AM - v2.0b4: range check for GetModeTiming - jwh */
/* 7/20/94 2:29:46 PM - v2.0: remove b4 from board name string - jwh */
#define _DRIVER           ;tells the compiler that we are doing a driver
#define DEBUG_STATUS	0
#define DEBUG_CONTROL	0
#if DEBUG_STATUS
#define DBS_STATUS(s)	myDebugStr(s)
#else
#define DBS_STATUS(s)
#endif
#if DEBUG_CONTROL
#define DBS_CONTROL(s)	myDebugStr(s)
#else
#define DBS_CONTROL(s)
#endif
/* To compile each version, set appropriate define to 1 */
#ifndef TESTING
 #define TESTING 0
#endif
/* EQUs must be set to match defines above */
#if MAKINGROPS
#asm
MAKINGROPS EQU 1
#endasm
#else
#asm
MAKINGROPS EQU 0
#endasm
#endif
#if MAKINGRGB
#asm
MAKINGRGB EQU 1
#endasm
#else
#asm
MAKINGRGB EQU 0
#endasm
#endif
#if MAKINGTV
#asm
MAKINGTV EQU 1
#endasm
#else
#asm
MAKINGTV EQU 0
#endasm
#endif
#if MAKINGVERB
#asm
MAKINGVERB EQU 1
#endasm
#else
#asm
MAKINGVERB EQU 0
#endasm
#endif
pascal myDebugStr() = 0xABFF;
pascal ADBReInit() = 0xA07B;
/*
pascal void ShutDwnStart(void)
    = {0x3F3C,0x0002,0xA895}; 
*/
#define DEF_WIDTH		640
#define DEF_HEIGHT		480
#define MemWidth		1024L
#define COLOR_RED		0x00ff0000
#define COLOR_GREEN		0X0000ff00
#define COLOR_BLUE		0x000000ff
#define COLOR_WHITE		0x00ffffff
#define COLOR_BLACK		0x00000000
#define COLOR_GRAY224	0x00e0e0e0
#define COLOR_RGBtech	0x003366cc
#define COLOR_ROPS		0x0000dfaa
#define COLOR_ROPS_AA	0x0060d8b8
#define COLOR_SLOGAN	0x00c0c0c0
#define COLOR_SLOGAN_AA	0x00707070
#define COLOR_VER		0x00808080
#define COLOR_VER_AA	0x00e0e0e0
#define COLOR_VER2		0x00808080
#define COLOR_VER2_AA	0x00404040
#define	sRsrcBoard			1
#define	sTimingTableDir		0x0080
/* Timing Resource IDs */
#define	ID_6x4			0x0080
#define	ID_5x4			0x0081
#define	ID_6x4ntsc		0x0082
#define	ID_5x4ntsc		0x0083
#define	ID_6x4ntscGL	0x0084
#define	ID_5x4ntscGL	0x0085
#define	ID_6x4pal		0x0086
#define	ID_5x4pal		0x0087
#define	ID_6x4palGL		0x0088
#define	ID_5x4palGL		0x0089
/* Video sResource IDs */
#define FirstResource	((unsigned short) 0x0080)
#define LastResource	((unsigned short) 0x0087)
#define FirstMonitor	((unsigned short) 0x0080)
#define LastMonitor		((unsigned short) 0x0085)
#define FirstExtended	((unsigned short) 0x0086)
#define LasttExtended	((unsigned short) 0x0087)
#define DefaultResource	((unsigned short) 0x0080)
#define NITEMS_VBLANK	((short) 128)		/* number of items to load on each vertical blanking */	
/* Defines for PZ */
#define devBase(slot) (((unsigned long)slot << 24) | 0xF0000000L);
/* The structure of PRAM */
typedef unsigned char Byte;
typedef struct SPRAMRecord
{
  short boardID;
  Byte vendorUse1;
  Byte vendorUse2;
  Byte vendorUse3;
  Byte vendorUse4;
  Byte vendorUse5;
  Byte vendorUse6;
} SPRAMRecord, *SPRAMRecPtr;
typedef struct BMHeader {
	long	filesize;
	char	filename[8];
	short	width;
	short	height;
	long	color;
	char	flags;
	char	unused;
} BMHeader;
#define BITCOMPRESSED	0x80
typedef struct BMHeader23 {		/* header for boards using byte lanes 0 & 1 */
	short	filler0;		/* dont delete this one */
	short	filesizeH;
	short	filler1;
	short	filesizeL;
	short	filler2;
	char	filename0[2];
	short	filler3;
	char	filename1[2];
	short	filler4;
	char	filename2[2];
	short	filler5;
	char	filename3[2];
	short	filler6;
	short	width;
	short	filler7;
	short	height;
	short	filler8;
	short	colorH;
	short	filler9;
	short	colorL;
	short	filler10;
	char	flags;
	char	unused;
} BMHeader23;
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
enum panStatusTypes
{
  getPanRate = 8192,	/* GetPanRate()	get the scaling factor for the x/y panning rate.     */
  getSlow,		/* GetSlow()	get the slow panning speed. 			     */
  getFast,		/* GetFast()	get the fast panning speed. 			     */
  getMargin,		/* GetMargin()	get the width (in pixels) of the slow panning area.  */
  getZoom,		/* GetZoom()	get the current zoom state (1 = x1, 2 = x2, 3 = x4.) */
  getRects,		/* GetRects()	get the fast and slow panning rectangles and speeds. */
  getXY,		/* GetXY()      get the currentX and currentY screen positions.	     */
  getAll,		/* GetAll()	get all the various parameters			     */
  getPZMode,		/* GetPZMode()  get the pixel mode				     */
  getPZ			/* GetPZ()	get the pan & zoom enable flag			     */
};
enum panControlTypes
{
  zoomIn = 8192,	/* ZoomIn()	zoom in.     	 	     			     */
  zoomOut,		/* ZoomOut()	zoom out. 			     		     */
  panX,			/* PanX()	pan in the x direction. 	  		     */
  panY,			/* PanY()	pan in the y direction.  	   		     */
  panTo,		/* PanTo()	pan to x,y  			 		     */
  setRects, 		/* SetRects()	set the fast and slow panning rectangles. 	     */
  setXY,		/* SetXY()	set the X,Y coordinates (screen top left)	     */
  setSlow,		/* SetSlow()	set the slow panning rate			     */
  setFast,		/* SetFast()	set the fast panning rate			     */
  setBorder,		/* SetBorder()  set the panning border width			     */
  setPZ,		/* SetPZ()	enable panning and zooming			     */
};
#asm
;*************************************************************
; SlotManager equates
	include	"azTraps.asm"
	include	"azSlotEqu.asm"
;*************************************************************
#endasm
#include "24MTVsRes.c"
/*
 * Macros for testing the configuration
 *
 * pi stands for primary init
 * isr stands for interrupt service routine
 */
#define BIT_INTERLACED	0x8
#define BIT_PAL			0x4
#define BIT_GENLOCK		0x2
#define BIT_UNDERSCAN	0x1
#define ISINTERLACED(base) \
	(*((long *) (base + MON_TYPE)) & 0x00000002)
#define ISINTERLACEDID(pram) \
	((pram->vendorUse5 != 0x80) && (pram->vendorUse5 != 0x83))
	
#define piISPAL(pram) \
	((pram->vendorUse5 == 0x82) || (pram->vendorUse5 == 0x85))
	
#define ISGENLOCK(base) \
	((*((short *)(base + pip_status_2)) & 0x0040) == 0)
#define piISUNDERSCAN(pram) \
	((pram->vendorUse5 == 0x83) || (pram->vendorUse5 == 0x84) || (pram->vendorUse5 == 0x85))	
#define WASINTERLACED(base) \
	(*((long *) (base + OSC_SEL)) & 0x00000003)
	
#define WASGENLOCK(base) \
	(*((long *) (base + EXT_SYNC_ENABLE)) & 0x00000001)
#define isrISPAL(base) \
	(*(short *)(base + pip_status_3) & 0x0020)
	
#define isrISUNDERSCAN(base) \
	((*(short *)(base + H_START_BLANK + 2) - *(short *)(base + H_END_BLANK + 2)) != 640/4)
	
/***********************************************************************
/*  Primary Init Prototypes
/***********************************************************************/
void piGradScrn24();
unsigned long	RGB2Long();
#asm
;***********************************************************************
;  Primary Init Code Block
;***********************************************************************
primaryinit even
; Header information
    DC.L  endprimaryinit-primaryinit        ; Length of seBlock
    DC.B  2                     ; Revision Level 2 (The Slot Manager REQUIRES this to be 2!)
    DC.B  2                     ; CPU ID 2 (68020)
    DC.W  0                     ; Reserved
    DC.L  4                     ; Code Offset 4  (In other words, next!)
;
; PRIMARY INIT CODE
;
; On Entry:  A0 -> Slot Manager seBlock
;
	MOVEM.L A0-A5/D0-D7,-(SP)  	; save nearly all registers	
	MOVE.L	A0,-(SP)			; push SeBlock pointer
	JSR		_cPrimaryInit		; call our c routine
	LEA		4(SP),SP			; repair stack caused by c call
	MOVEM.L (SP)+,A0-A5/D0-D7	; Restore nearly all registers
	RTS
#endasm
/*
 * This is the C version of the primary init
 */
cPrimaryInit(SeBlkPtr)
SEBlock	*SeBlkPtr;									/* pointer to SeBlock passed to us */
{
	register unsigned short	slot;					/* slot number */
	register unsigned long	base;					/* address of our frame buffer */
	unsigned short			pram5;					/* parameter ram 5 */
	register unsigned short	pram6;					/* parameter ram 6 */
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	SPRAMRecord				PRAMRec;				/* temp storage for pram record */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	register SPRAMRecord	*PRAMPtr = &PRAMRec;	/* temp storage for pram record */
	short					i;						/* loop counter */
	
	/*
	 * set status to 1 (success)
	 * get slot number
	 * contruct 32 bit address of our frame buffer
	 * set up sp block slot number and ext device to be used in all slot manager calls
	 */
	pisVersion(SpPtr);
	if(SpPtr->spResult < 2)	/* QD32 must be in ROM or we don't fly! */
	{
		SeBlkPtr->seStatus = -1;
		return;
	}
	else
	{
		SeBlkPtr->seStatus = 1;
	}
	slot = SeBlkPtr->seSlot;
	base = 0xf0000000 | (((unsigned long) slot) << 24L);
	SpPtr->spSlot = slot;
	SpPtr->spExtDev = 0;	
	
	/*
	 * check the switch (or monitor select line), then check the control panel soft selection
	 * if they are not compatible, go with the monitor select and reset the cp selection
	 */
	piGetPRAM((unsigned long) SpPtr, (unsigned long) PRAMPtr);
	
	pram5 = PRAMPtr->vendorUse5;
	if((pram5 < FirstMonitor) || (pram5 > LastMonitor))
	{
		pram5 = DefaultResource;
		PRAMPtr->vendorUse5 = DefaultResource;
	}
	
	pram6 =  PRAMPtr->vendorUse6;
	if((pram6 < FirstResource) || (pram6 > LastResource))
	{
		pram6 = DefaultResource;
	}
	
	if((pram6 <= LastMonitor) && (pram6 != pram5))
	{
		pram6 = pram5;
	}
	
	PRAMPtr->vendorUse6 = pram6;
	piSetPRAM(SpPtr, PRAMPtr);
	
	piDisableExcept(SpPtr, pram6);
	/*
	 * init the board
	 * draw color cube, logo, rom version
	 */
	if(!piAUXRunning()) {
		initscrn(base, PRAMPtr);
#if MAKINGRGB
		{
			short	width,height;
			short	xcenter,ycenter;
			
			if(piISUNDERSCAN(PRAMPtr)) {		/* 576x432 */
				width = 576;
				height = 432;
			}
			else {								/* 640x480 */
				width = 640;
				height = 480;
			}
			xcenter = width/2;
			ycenter = height/2;
			piEraseScrn(base, (long) COLOR_GRAY224);
			pi_draw_bm24(base, "RGBArc1 ", (short) (xcenter - 54), (short) (ycenter - 46), (long) COLOR_RED);
			pi_draw_bm24(base, "RGBArc2 ", (short) (xcenter + 54), (short) (ycenter - 47), (long) COLOR_GREEN);
			pi_draw_bm24(base, "RGBArc3 ", (short) (xcenter-1), (short) (ycenter + 87-46), (long) COLOR_BLUE);
			pi_draw_bm24(base, "RGBTop  ", (short) (xcenter), (short) (ycenter - 161), (long) COLOR_BLUE);
			pi_draw_bm24(base, "RGBBot  ", (short) (xcenter), (short) (ycenter + 111), (long) COLOR_BLUE);
			pi_draw_bm24(base, "ver     ", (short) (width-36), 20, (long) COLOR_VER2);
			pi_draw_bm24(base, "ver_aa  ", (short) (width-36), 20, (long) COLOR_VER2_AA);
		}
#endif
#if MAKINGTV
/*
 * Truevision
 */
#define COLOR_TVBACK	0x0000bdffL
#define COLOR_TVBLACK	0x00181818L
#define COLOR_TVRED		0x00ff1818L
#define COLOR_TVGREEN	0x0010d610L
#define COLOR_TVBLUE	0x001818ffL
#define COLOR_TVBLACK_A	0x000077aaL
#define COLOR_TVRED_A	0x00551818L
#define COLOR_TVGREEN_A	0x00184418L
#define COLOR_TVBLUE_A	0x00181855L
		{
			short	width,height;
			short	xcenter,ycenter;
			short	xoff,yoff;
			
			if(piISUNDERSCAN(PRAMPtr)) {		/* 576x432 */
				width = 576;
				height = 432;
			}
			else {								/* 640x480 */
				width = 640;
				height = 480;
			}
			xcenter = width/2;
			ycenter = height/3;
			xoff = -128;
			yoff = 1;
			
			/* piEraseScrn(base, (long) COLOR_TVBACK); */
			piGradScrn24(base, (long) COLOR_TVBACK);
			
			pi_draw_bm24(base, "bTV     ", (short) (xcenter), (short) (ycenter), (long) COLOR_TVBLACK);
			pi_draw_bm24(base, "bTVA    ", (short) (xcenter), (short) (ycenter), (long) COLOR_TVBLACK_A);
			
			pi_draw_bm24(base, "bTVr    ", (short) (xcenter+xoff), (short) (ycenter+yoff), (long) COLOR_TVRED);
			pi_draw_bm24(base, "bTVg    ", (short) (xcenter+xoff+9), (short) (ycenter+yoff), (long) COLOR_TVGREEN);
			pi_draw_bm24(base, "bTVr    ", (short) (xcenter+xoff+16), (short) (ycenter+yoff), (long) COLOR_TVBLUE);
			pi_draw_bm24(base, "bTVrA   ", (short) (xcenter+xoff), (short) (ycenter+yoff), (long) COLOR_TVRED_A);
			pi_draw_bm24(base, "bTVgA   ", (short) (xcenter+xoff+9), (short) (ycenter+yoff), (long) COLOR_TVGREEN_A);
			pi_draw_bm24(base, "bTVrA   ", (short) (xcenter+xoff+16), (short) (ycenter+yoff), (long) COLOR_TVBLUE_A);
			pi_draw_bm24(base, "ver     ", (short) (width-36), 20, (long) COLOR_VER2);
		}
#endif
#if MAKINGROPS
		if(piISUNDERSCAN(PRAMPtr)) {		/* 576x432 */
			ColorCube(base, PRAMPtr);
			pi_draw_bm24(base, "logo    ", 288, 74, (long) COLOR_ROPS);
			pi_draw_bm24(base, "logo_aa ", 288, 74, (long) COLOR_ROPS_AA);
			pi_draw_bm24(base, "slogan  ", 288, 396, (long) COLOR_SLOGAN);
			pi_draw_bm24(base, "sloganaa", 288, 396, (long) COLOR_SLOGAN_AA);
			pi_draw_bm24(base, "ver     ", 540, 20, (long) COLOR_VER);
			pi_draw_bm24(base, "ver_aa  ", 540, 20, (long) COLOR_VER_AA);
		}
		else {								/* 640x480 */
			ColorCube(base, PRAMPtr);
			pi_draw_bm24(base, "logo    ", 320, 82, (long) COLOR_ROPS);
			pi_draw_bm24(base, "logo_aa ", 320, 82, (long) COLOR_ROPS_AA);
			pi_draw_bm24(base, "slogan  ", 320, 440, (long) COLOR_SLOGAN);
			pi_draw_bm24(base, "sloganaa", 320, 440, (long) COLOR_SLOGAN_AA);
			pi_draw_bm24(base, "ver     ", 600, 20, (long) COLOR_VER);
			pi_draw_bm24(base, "ver_aa  ", 600, 20, (long) COLOR_VER_AA);
		}
#endif
		pi_show(base);
	
		/* 
		 * wait for 2 seconds
		 */
	
		i = 2000;
		while(i--)
			pi_wait_one();
	}
	else {	
		initscrn(base, PRAMPtr);
		pi_show(base);
	}
}
/*
 * AUXRunning()
 *
 * returns true(non-zero) if AUX is running, otherwise 0
 */
piAUXRunning()
{
	register short	flags;
	
	flags  = *((short *) (0x0b22));
	return (flags & (0x0200));
}
/*
 * DisableExcept(SpPtr, ResourceNumber)
 */
piDisableExcept(SpPtr, ResourceNumber)
register SpBlock	*SpPtr;			/* our sp block pointer to make the slot manager call */
register unsigned short	ResourceNumber;
{
	register unsigned short	start;
	register unsigned short	end;
	register unsigned short	i;
/* These are already set 	
	SpPtr->spSlot = slot;
	SpPtr->spExtDev = 0;
*/
	SpPtr->spsPointer = 0;		/* not ram sRsrc */
	SpPtr->spRefNum = 0;		/* dont update dCtlDevBase */
	start = (FirstResource);
	end = (LastResource);
	for(i = start; i <= end; i++)
	{
		if (i != ResourceNumber)
		{
			SpPtr->spID = i;
			SpPtr->spStackPtr = 1;		/* actually SpPtr->spParamData, 1 = disable */
			piSetSRsrcState(SpPtr);
			piSUpdateSRT(SpPtr);
		}
	}
}
	
/*
 * piEraseScrn()
 */
piEraseScrn(base, color)               /* Newest Screen Init Routine */
unsigned long	base;
unsigned long	color;
{
	register short			i,j;
	register unsigned long	*to;
	char					mmu_mode;
	mmu_mode = true32b;	/* 32 bit mode */
	piSwapMMUMode(&mmu_mode);
  
	/*
	 * blank the screen
	 */
	to = (unsigned long *) base;
	for (i=0;i<480;i++) {
		for (j=0;j<640;j++) {
			*to++=color;
		}
		to += (MemWidth - 640);
	}
	
	piSwapMMUMode(&mmu_mode);
}
#if MAKINGTV
/*
 * GradScrn24()
 */
void piGradScrn24(base, color)               /* Newest Screen Init Routine */
unsigned long	base;
long	color;
{
	register short			i,j;
	register unsigned long	*to;
	char					mmu_mode;
 	long			rHigh;
 	long			gHigh;
 	long			bHigh;
 	long			rLow;
 	long			gLow;
 	long			bLow;
 	long			rDelta;
 	long			gDelta;
 	long			bDelta;
	register unsigned long	col;
	
	rHigh = (color & 0x00ff0000) >> 16L;
	gHigh = (color & 0x0000ff00) >> 8L;
	bHigh = color & 0x000000ff;
	rLow = rHigh * 20L / 100L;
	gLow = gHigh * 20L / 100L;
	bLow = bHigh * 20L / 100L;
	rDelta = rHigh - rLow;
	gDelta = gHigh - gLow;
	bDelta = bHigh - bLow;
	mmu_mode = 1;	/* 32 bit mode */
	pmySwapMMUMode(&mmu_mode);
  
	/*
	 * grad the screen
	 */
	to = (unsigned long *)(base);
	for (i=0;i<480;i++) {
		col = RGB2Long((short) (rLow + rDelta*(480-i)/480),
					   (short) (gLow + gDelta*(480-i)/480),
					   (short) (bLow + bDelta*(480-i)/480));
		for (j=0;j<640;j++) {
			*to++=col;
		}
		to += (MemWidth - 640);
	}
	pmySwapMMUMode(&mmu_mode);
}
/*
 * RGB2Long()
 */
unsigned long	RGB2Long(r, g, b)
short	r;
short	g;
short	b;
{
	unsigned long	col;
	
	col =  (unsigned long) (((long) r << 16L) | ((long) g << 8L) | (long) b);
	return col;
}
#endif
/*
 * GetPRAM()
 */
piGetPRAM(SpPtr, PRAMPtr)
register SpBlock		*SpPtr;			/* our sp block pointer to make the slot manager call */
register SPRAMRecord	*PRAMPtr;		/* where to store the PRAM record */
{
	/* set up parameters for slot manager call */
	SpPtr->spResult = (unsigned long) PRAMPtr;
	piSReadPRAMRec(SpPtr);
}
	
/*
 * SetPRAM()
 */
piSetPRAM(SpPtr, PRAMPtr)
register SpBlock		*SpPtr;			/* our sp block pointer to make the slot manager call */
register SPRAMRecord	*PRAMPtr;		/* where to store the PRAM record */
{
	/* set up params for slot manager call */
	SpPtr->spsPointer = (char *) PRAMPtr;
	piSPutPRAMRec(SpPtr);
}
/*
 * piSReadPRAMRec(spPtr)
 */
#asm
_piSReadPRAMRec
	MOVE.L	4(SP),A0
	MOVEQ	#$11,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * piSPutPRAMRec(spPtr)
 */
#asm
_piSPutPRAMRec
	MOVE.L	4(SP),A0
	MOVEQ	#$12,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SetSRsrcState(spPtr)
 */
#asm
_piSetSRsrcState
	MOVE.L	4(SP),A0
	MOVEQ	#$09,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SUpdateSRT(spPtr) Glue
 */
#asm
_piSUpdateSRT
	MOVE.L	4(SP),A0
	_SUpdateSRT
	RTS
#endasm 
#asm
;__________________________________________________________________________________________________
; Subroutine waits for one millisecond	
_pi_wait_one
	CLR.L	D0
	MOVE.W	$D00,D0		; Get TimeDBRA Global
more_dbras			; Loop for 1 ms
	DBRA	D0,more_dbras
	RTS
#endasm
/*
 * SwapMMUMode(spPtr) Glue
 */
#asm
;__________________________________________________________________________________________________
; Subroutine Swaps MMU Mode
; expects pointer to new mode (char *) on stack
; returns old mode in place of new mode with pointer still on the stack
_piSwapMMUMode
	MOVE.L	4(SP),A0
	MOVE.B	(A0),D0
	_SwapMMUMode		; SwapMMUMode $A05D
	MOVE.L	4(SP),A0
	MOVE.B	D0,(A0)
	RTS
#endasm
/*
 * sVersion(SpPtr)
 */
#asm
_pisVersion
	MOVE.L	4(SP),A0
	MOVEQ	#8,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SRsrcInfo(spPtr) Glue
 */
#asm
_piSRsrcInfo
	MOVE.L	4(SP),A0
	MOVEQ	#$16,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SFindStruct(spPtr) Glue
 */
#asm
_piSFindStruct
	MOVE.L	4(SP),A0
	_SFindStruct
	RTS
#endasm 
#if MAKINGROPS
/*
 * ColorCube()
 */
ColorCube(base, PRAMPtr)
long		base;
SPRAMRecord	*PRAMPtr;		/* where to store the PRAM record */
{
/*
#define	S_WIDTH		640
#define	S_HEIGHT	480
#define	HEXSIZE		140
#define	HEXMAX		(HEXSIZE-1)
*/
#define	TOTAL_SHADES	256
#define true_shade(shade)	((TOTAL_SHADES * shade) / HEXSIZE)
	short	S_WIDTH;
	short	S_HEIGHT;
	short	HEXSIZE;
	short	HEXMAX;
	register unsigned long	i, j;
	unsigned long	rowmax, midpoint;
	unsigned long	red, green, blue;
	register unsigned long	*dest;
	unsigned char	mmu_mode;
	register unsigned long	color;
	
	if(piISUNDERSCAN(PRAMPtr)) {		/* 576x432 */
		S_WIDTH = 576;
		S_HEIGHT = 432;
		HEXSIZE = 128;
	}
	else {
		S_WIDTH = 640;
		S_HEIGHT = 480;
		HEXSIZE = 140;
	}
	HEXMAX = (HEXSIZE-1);
	
	mmu_mode = true32b;		/* prepare to change to 32 bit mode */
	piSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	
	*(long *)(base + FAT_SLOT)		= 1;		/*  1RW	0 = skinny, 1 = fat slot decoding */
	/* Background color */
	dest = (unsigned long *)base;
	for(i=0; i<S_HEIGHT; i++)
	{
		color = ((S_HEIGHT-1 - i)*255L) / ((long) S_HEIGHT-1);
		color = (color << 16) | (color << 8) | color;
		j = S_WIDTH;
		while(j--) {
			*dest++ = color;
		}
		dest += 1024-S_WIDTH;
	}
	dest = (unsigned long *)base;
	dest += ((S_HEIGHT*9/16 - HEXSIZE) *1024L);
	dest += S_WIDTH/2;
	/* Section 1 is 1/4 of display */
	for(i=0; i<HEXSIZE/2; i++) /* For each Row */
	{
		red =   0;
		green = 2*i;
		blue =  HEXMAX;
		rowmax = 4*i;
		for(j=0; j<=rowmax; j++) /* For each column */
		{
			*dest++ = true_shade(red)<<16 | true_shade(green)<<8 | true_shade(blue);
			/* Red */
			 if(j&1) red++;
			/* Green */
			if((j&1)==0) green--;
			/* Blue */
		}
		dest += 1024-j-2;
	}
	dest += 1;
	/* Section 2 is 1/4 of display */
	for(i=0; i<HEXSIZE/2; i++) /* For each Row */
	{
		red =   0;
		green = HEXMAX;
		blue =  HEXMAX-i;
		for(j=0; j<2*HEXSIZE-1; j++) /* For each column */
		{
			*dest++ = true_shade(red)<<16 | true_shade(green)<<8 | true_shade(blue);
			/* Red */
			if(j<i*2) red++;
			else if(j<2*(HEXMAX-i)) if(j&1) red++;
			/* Green */
			if(j>=2*(HEXMAX-i)) green--;
			else if(j>=i*2) if(j&1) green--;
			/* Blue */
			if(j<i*2)
				if(j&1) blue++;
			if(j>=2*(HEXMAX-i))
				if(j&1) blue--;
		}
		dest += 1024-(2*HEXSIZE-1);
	}
	/* Section 3 is 1/4 of display */
	for(i=0; i<HEXSIZE/2; i++) /* For each Row */
	{
		red =   0;
		green = HEXMAX;
		blue =  HEXMAX/2-i;
		for(j=0; j<2*HEXSIZE-1; j++) /* For each column */
		{
			*dest++ = true_shade(red)<<16 | true_shade(green)<<8 | true_shade(blue);
			/* Red */
			if(j<HEXMAX) red++;
			/* Green */
			if(j>HEXMAX) green--;
			/* Blue */
			if(j<HEXMAX)
				if(j&1) blue++;
			if(j>HEXMAX)
				if(j&1) blue--;
		}
		dest += 1024-(2*HEXSIZE-1);
	}
	dest += 2;
	/* Section 4 is 1/4 of display */
	for(i=HEXMAX/2; i>0; i--) /* For each Row */
	{
		red =   2*(1+HEXMAX/2-i);
		green = HEXMAX;
		blue =  0;
		rowmax = 4*i-1;
		midpoint = rowmax/2;
		for(j=0; j<rowmax; j++) /* For each column */
		{
			*dest++ = true_shade(red)<<16 | true_shade(green)<<8 | true_shade(blue);
			/* Red */
			if(j<midpoint) red++;
			/* Green */
			if(j>midpoint) green--;
			/* Blue */
			if(j<midpoint)
				if(j&1) blue++;
			if(j>midpoint)
				if(j&1) blue--;
		}
		dest += 1024-j+2;
	}
	piSwapMMUMode(&mmu_mode);
}
#endif
/*
 * pi_show()
 */
pi_show(base)
unsigned long	base;
{
	char			mmu_mode;	
	register short	i;
	
	mmu_mode = true32b;	/* 32 bit mode */
	piSwapMMUMode(&mmu_mode);
	/* Create linear-ramp lookup tables for all 4 DACs (xxrrggbb) */
	*(long *)(base + PAGE_CTL) = 0;	/*  2RW	PAGE control 0 = DAC, 1 = ADC, 2 = PIP Regs */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	*((unsigned char *)(base + bt473_p_addr)) = 0;   /* Address $0 */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	for(i=0; i<256; i++)
	{
		*((unsigned char *)(base + bt473_palette)) = i;   /* LUT Color for red */
		*((unsigned char *)(base + bt473_palette)) = i;   /* LUT Color for green */
		*((unsigned char *)(base + bt473_palette)) = i;   /* LUT Color for blue */
	}
  
    /* 
	 * make it visible
	 */
	*((unsigned char *)(base + bt473_mask)) = 0xFF;   /* DAC read mask */
	/*** tmp fix for Mode32 ???? */
	/*** *(long *)(base + FAT_SLOT) = 0;		/* put it in skinny mode */
	piSwapMMUMode(&mmu_mode);
}
/*
 * pi_draw_bm24()
 */
pi_draw_bm24(base, name, xcenter, ycenter, color)
unsigned long	base;
char			*name;
unsigned long	color;
{
	register char			*bm;
	register short			k;
	register char			c;
	register short			j;
	register short			i;
	register short			len;
	register short			count;
	register unsigned long	*to;
	short					xstart, ystart;
	short					p_width, p_height;
	char					mmu_mode;
	BMHeader23				*headerptr;
	
	if(!piFindBitmap(base, name, &headerptr))
		return;
		
	mmu_mode = true32b;	/* 32 bit mode */
	piSwapMMUMode(&mmu_mode);
  		
	bm = (char *)headerptr + sizeof(BMHeader23);
	if(color < 0)
		color = ((long) (headerptr->colorH) << 16L) | headerptr->colorL;
	p_width = headerptr->width;
	p_height = headerptr->height;
	
	*(long *)(base + FAT_SLOT) = 1;		/*  1RW	0 = skinny, 1 = fat slot decoding */
  
	/*
	 * calculate starting point
	 */
	if((xcenter == 0) && (ycenter == 0)) {
		xstart = DEF_WIDTH/2 - p_width/2;
		ystart = DEF_HEIGHT/3 - p_height/2;
	}
	else {
		xstart = xcenter - p_width/2;
		ystart = ycenter - p_height/2;
	}
	if(xstart < 0)
		xstart = 0;
	if(ystart < 0)
		ystart = 0;
	
	/*
	 * draw the bitmap
	 */
	to = (unsigned long *)(base);
	to += (ystart * 1024L + xstart);
	if(!(headerptr->flags & BITCOMPRESSED)) {		/* non-compressed bit map */
		bm += 2;	/* because we are using byte lanes 2,3 */
		for (i=0;i<p_height;i++)
		{
			for (j=0;j<p_width/8;j++)
			{
				if (c = *bm)
				{
					for (k=0;k<8;k++)
					{
						if (c & 0x80)
							*to++ = color;
						else
							to++;
						c <<= 1;
					}
				}
				else {
					to+=8;
				}
				
				if(((long) bm & 1) == 0) {
					bm++;
				}
				else {
					bm += 3;
				}
			}
			to += (1024-p_width);
		}
	}
	else {							/* compressed bit map */
		bm += 2;	/* because we are using byte lanes 2,3 */
		for (i=0;i<p_height;i++) {
			count = p_width/8;
			while(count > 0) {
				len = (*bm & 0x00ff);
				bm += (((long) bm & 0x1) ? 3 : 1);
				if(len <= 0x7f) {
					count -= len;
					while(len--) {
						c = *bm;
						for(k = 0; k < 8; k++) {
							if(c < 0)
								*to++ = color;
							else
								to++;
							
							c <<= 1;
						}
					}
					bm += (((long) bm & 0x1) ? 3 : 1);
				}
				else {
					len -= 0x7f;
					count -= len;
					while(len--) {
						c = *bm;
						bm += (((long) bm & 0x1) ? 3 : 1);
						for(k = 0; k < 8; k++) {
							if(c < 0)
								*to++ = color;
							else
								to++;
							
							c <<= 1;
						}
					}
				}
			}
			to += (MemWidth-p_width);
		}
	}
	
	
	piSwapMMUMode(&mmu_mode);
}
/*
 * piFindBitmap(base, name, headeraddr)
 */
short piFindBitmap(base, name, headeraddr)
char			*base;
register char	*name;
BMHeader23		**headeraddr;
{
	register BMHeader23	*ptr;
	long				size;
	short				rc;
	char				mmu_mode;
	extern char			logo;
	
	ptr = (BMHeader23 *) (base + 0x00ff0000);
/*	ptr = (BMHeader *) (&logo); */
	mmu_mode = true32b;	/* 32 bit mode */
	piSwapMMUMode(&mmu_mode);
  	
	*(long *)(base + FAT_SLOT) = 1;		/*  1RW	0 = skinny, 1 = fat slot decoding */
	rc = 0;
	while(size = (((long) ptr->filesizeH << 16L) +  ptr->filesizeL)) {
		if ((name[0] == ptr->filename0[0]) &&
			(name[1] == ptr->filename0[1]) &&
			(name[2] == ptr->filename1[0]) &&
			(name[3] == ptr->filename1[1]) &&
			(name[4] == ptr->filename2[0]) &&
			(name[5] == ptr->filename2[1]) &&
			(name[6] == ptr->filename3[0]) &&
			(name[7] == ptr->filename3[1])
		   ) {
			*headeraddr = ptr;
			rc = 1;
			break;
		}
		else {
			ptr = (BMHeader23 *) ((unsigned long) ptr + size * 2);		/* *2 because we use byte lanes 2,3 */
		}
	}
	piSwapMMUMode(&mmu_mode);
	return rc;
}
/*__________________________________________________________________________________________________*/
initscrn(base, pram)               /* Newest Screen Init Routine */
unsigned long	base;
SPRAMRecord		*pram;
{
	char					mmu_mode;
	short					resolution;
	register unsigned char	*reg_ptr;
	register unsigned char	*table_ptr;
	extern unsigned char 	timing_tables;
	
	mmu_mode = true32b;	/* 32 bit mode */
	piSwapMMUMode(&mmu_mode);
	
	*(long *)(base + FAT_SLOT)		= 1;		/*  1RW	0 = skinny, 1 = fat slot decoding */
	*(long *)(base + NMRQ_DISABLE)	= 1;		/*  1RW	1 disables Interrupts */
	
	/* Now make all this invisible by telling it to inhibit  all bits in the DACs. */
	*(long *)(base + PAGE_CTL)		= 0;		/*  2RW	PAGE control 0 = DAC, 1 = ADC, 2 = PIP Regs */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	reg_ptr = ((unsigned char *)(base + bt473_p_addr));   /* DAC Address Register */
	*reg_ptr = 0;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	reg_ptr = ((unsigned char *)(base + bt473_palette));   /* DAC Data Register */
	*reg_ptr = 0;   /* DAC Data r */
	*reg_ptr = 0;   /* DAC Data g */
	*reg_ptr = 0;   /* DAC Data b */
	reg_ptr = ((unsigned char *)(base + bt473_mask));   /* DAC read mask */
	*reg_ptr = 0;   /* DAC read mask off */
	reg_ptr = ((unsigned char *)(base + bt473_command));   /* DAC Command Register */
	if(piISPAL(pram) && ISINTERLACEDID(pram))
		*reg_ptr = 0x10;
	else
		*reg_ptr = 0x30;
	*(long *)(base + CMODE)		= 4;			/* 3RW	1xx(4-7) 24 Bit Mode */
	*(long *)(base + EXT_SYNC_ENABLE)	= 0;	/*  1RW	1 enables External sync (for GENLOCK) */
	*(long *)(base + VID_RESET)		= 1;		/*  1RW	1 holds all video counters reset */
	load_timingtable(base, pram);
	*(long *)(base + XCASTAP)		= 0;		/*  9RW	X Zoom */
	*(long *)(base + YPANTAP)		= 0;		/*  9RW	Y Pan */
	*(long *)(base + VID_RESET)		= 0;		/*  1RW	0 frees all video counters */
	*(long *)(base + NMRQ_DISABLE)	= 1;		/*  1RW	1 disables Interrupts ????*/
							/*  (must be written once to start interrupts) */
	*(long *)(base + TRANS_ENABLE)	= 1;		/*  1RW	1 enables transfer cycles */
	*(long *)(base + SYNC_ENABLE)		= 1;	/*  1RW	1 enables sync */
	*(long *)(base + DISPLAY_ENABLE)	= 1;	/*  1RW	0 forces blanked display */
	/* load the crystal selector bit in control_3 */
	*(long *)(base + PAGE_CTL) = 3;					/* 2RW	DAC control 0 = DAC, 1 = ADC, 2 = counters, 3 = control */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	if(piISPAL(pram))
		*(short *)(base + pip_control_3) |= 0x0020;		/* Pip Control register 3 */
	else
		*(short *)(base + pip_control_3) &= 0xFFDF;		/* Pip Control register 3 */
	*(long *)(base + PAGE_CTL)		= 0;			/*  2RW	PAGE control 0 = DAC, 1 = ADC, 2 = PIP Regs */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	piSwapMMUMode(&mmu_mode);
} /* end of initscrn */
/*
 * load_timingtable()
 */
load_timingtable(base, pram)
unsigned long	base;
SPRAMRecord		*pram;
{
	register unsigned long	*reg;
	register unsigned long	*table_ptr;
	register short			count;
	register char			flags;
	short					resNum;
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	long					saved_page;
	char					mmu_mode;
	
	mmu_mode = true32b;	/* 32 bit mode */
	piSwapMMUMode(&mmu_mode);
	
	saved_page = *((long *)(base + PAGE_CTL));
	/*
	 * build flag word depending on
	 * 1. interlaced <-> non-interlaced
	 * 2. pal <-> ntsc
	 * 3. genlock <-> non-genlock
	 * 4. regular size <-> underscan
	 */
	flags = 0;
	if(ISINTERLACEDID(pram))
		flags |= BIT_INTERLACED;
	
	if(piISPAL(pram))
		flags |= BIT_PAL;
	
	*(long *)(base + PAGE_CTL) = 3;		/* 2RW	DAC control 0 = DAC, 1 = ADC, 2 = counters, 3 = control */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	if(ISGENLOCK(base))
		flags |= BIT_GENLOCK;
	
	if(piISUNDERSCAN(pram))
		flags |= BIT_UNDERSCAN;
	piSwapMMUMode(&mmu_mode);
	/*
	 * find out the table to load, depending on the flags
	 * BIT_INTERLACED	1000
	 * BIT_PAL			0100
	 * BIT_GENLOCK		0010
	 * BIT_UNDERSCAN	0001
	 */
	switch(flags) {
		case 0x0:			/* 0000 */
		case 0x2:			/* 0010 */
		case 0x4:			/* 0100 */
		case 0x6:			/* 0110 */
				resNum = ID_6x4;
				break;
	
		case 0x1:			/* 0001 */
		case 0x3:			/* 0011 */
		case 0x5:			/* 0101 */
		case 0x7:			/* 0111 */
				resNum = ID_5x4;
				break;
	
		case 0x8:			/*1000 */
				resNum = ID_6x4ntsc;
				break;
				
		case 0x9:			/*1001 */
				resNum = ID_5x4ntsc;
				break;
				
		case 0xa:			/*1010 */
				resNum = ID_6x4ntscGL;
				break;
				
		case 0xb:			/*1011 */
				resNum = ID_5x4ntscGL;
				break;
				
		case 0xc:			/*1100 */
				resNum = ID_6x4pal;
				break;
				
		case 0xd:			/*1101 */
				resNum = ID_5x4pal;
				break;
				
		case 0xe:			/*1110 */
				resNum = ID_6x4palGL;
				break;
				
		case 0xf:			/*1111 */
				resNum = ID_5x4palGL;
				break;
	}
	
	/* Find parameter resource */
	SpPtr->spSlot = (base >> 24) & 0x0F;
	SpPtr->spExtDev = 0;
	SpPtr->spID = sRsrcBoard;		/* Find Board Resource */
	piSRsrcInfo(SpPtr);
	SpPtr->spID = sTimingTableDir;	/* Find Resoulution Directory */
	piSFindStruct(SpPtr);
	SpPtr->spID = resNum;			/* Find Parameters */
	piSFindStruct(SpPtr);
	
	table_ptr = (unsigned long *)(SpPtr->spsPointer + 8 - 2); /* skip count and adjust byte lane for long access */
		
	/*
	 * now load the registers from the table
	 */
	 
	mmu_mode = true32b;	/* 32 bit mode */
	piSwapMMUMode(&mmu_mode);
	
    *((unsigned long *)(base + OSC_SEL)) = *table_ptr++;
    *((unsigned long *)(base + EXT_SYNC_ENABLE)) = *table_ptr++;
	reg = (unsigned long *) (base + V_END_SYNC);
	count = 10;
	while(count--)
		*reg++ = *table_ptr++;
	/*
	 * set crystal select
	 */
	/**** do this in initsrcn() after init of all pip registers
	*(long *)(base + PAGE_CTL) = 3;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	if(flags & BIT_PAL)
		*(short *)(base + pip_control_3) |= 0x0020;
	else
		*(short *)(base + pip_control_3) &= 0xFFDF;
	*/
	/*
	 * if PAL set bit 5 of DAC command register to 0, else 1
	 */
	*(long *)(base + PAGE_CTL) = 0;		/* 2RW	DAC control 0 = DAC, 1 = ADC, 2 = counters, 3 = control */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	if((flags & BIT_INTERLACED) && (flags & BIT_PAL))
		*(unsigned char *)(base + bt473_command) &= 0xDF;
	else
		*(unsigned char *)(base + bt473_command) |= 0x20;
	/*
	 * restore page_ctl
	 */
	*((long *)(base + PAGE_CTL)) = saved_page;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	piSwapMMUMode(&mmu_mode);
}
#asm
; ==================END OF PRIMARY INIT BLOCK=====================
endprimaryinit
#endasm
#asm
secondaryinit
;
; ==================BEGINNING OF SECONDARY INIT BLOCK=====================
;
    dc.l  endsecondaryinit-secondaryinit    ; Length of seBlock
    dc.b  2                                 ; Revision Level 2 (The Slot Manager REQUIRES this to be 2!)
    dc.b  2                                 ; CPU ID 2 (68020)
    dc.w  0                                 ; Reserved
    dc.l  4                                 ; Code Offset 4  (In other words, next!)
;
; 2ND INIT CODE
; On Entry:  A0 -> Slot Manager SEBlock
;
	MOVEM.L A0-A5/D0-D7,-(SP)  	; save nearly all registers	
	MOVE.L	A0,-(SP)			; push SeBlock pointer
	JSR		_cSecondaryInit		; call our c routine
	LEA		4(SP),SP			; repair stack caused by c call
	MOVEM.L (SP)+,A0-A5/D0-D7	; Restore nearly all registers
	RTS
#endasm
cSecondaryInit(SeBlkPtr)
SEBlock	*SeBlkPtr;									/* pointer to SeBlock passed to us */
{
	register unsigned short	slot;					/* slot number */
	register unsigned long	base;					/* address of our frame buffer */
	register unsigned short	pram6;					/* control panel soft setting */
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	SPRAMRecord				PRAMRec;				/* temp storage for pram record */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	register SPRAMRecord	*PRAMPtr = &PRAMRec;	/* temp storage for pram record */
	char					mmu_mode;
	
	/*
	 * set status to 1 (success)
	 * get slot number
	 * contruct 32 bit address of our frame buffer
	 * set up sp block slot number and ext device to be used in all slot manager calls
	 */
	SeBlkPtr->seStatus = 1;
	slot = SeBlkPtr->seSlot;
	base = 0xf0000000 | (((unsigned long) slot) << 24L);
	SpPtr->spSlot = slot;
	SpPtr->spExtDev = 0;	
	
	/*
	 * if cmd-sht-opt are pressed, cycle thru, otherwise just do the resource
	 * insertion
	 *
	 * cycleIt() WILL CAUSE A RESTART
	 *
	 * DONT DO THIS ON AUX
	 */
	if(!siAUXRunning())
	{ 
		if(cmdoptsht())
		{
			cycleIt(base, SpPtr);
		}
	}
}
/*
 * AUXRunning()
 */
siAUXRunning()
{
	register short	flags;
	
	flags  = *((short *)0x0b22);
	return (flags & 0x0200);
}
/*
 * GetPRAM()
 */
siGetPRAM(SpPtr, PRAMPtr)
register SpBlock		*SpPtr;			/* our sp block pointer to make the slot manager call */
register SPRAMRecord	*PRAMPtr;		/* where to store the PRAM record */
{
	/* set up parameters for slot manager call */
	SpPtr->spResult = (unsigned long) PRAMPtr;
	siSReadPRAMRec(SpPtr);
}
	
/*
 * SetPRAM()
 */
siSetPRAM(SpPtr, PRAMPtr)
register SpBlock		*SpPtr;			/* our sp block pointer to make the slot manager call */
register SPRAMRecord	*PRAMPtr;		/* where to store the PRAM record */
{
	/* set up params for slot manager call */
	SpPtr->spsPointer = (char *) PRAMPtr;
	siSPutPRAMRec(SpPtr);
}
/*
 * cmdoptsht()
 *
 * check to see if cmd-opt-sht are pressed
 */
short cmdoptsht()
{
	KeyMap	km;
	
/*	ADBReInit(); */
	piDelay(15L);
	
	GetKeys(km);
/* myDebugStr("\Pcmdoptsht"); */
/*	if((km[1] & 0x00008005) == 0x00008005) */
	if((km[1] | 0xffff0002) == 0xffff8007)	/* dont know why some keys got stuck sometimes */
		return true;
	else
		return false;
}
#define DO_60Hz	0
#define DO_NTSC	1
#define DO_PAL	2
/*
 * cycleIt()
 */
cycleIt(base, SpPtr)
register unsigned long	base;
register SpBlock		*SpPtr;		/* our sp block to make the slot manager call */
{
	/*
	 * 0. draw picture (use 1bit mode)
	 * 1. load NTSC timing
	 * 2. poll keyboard for 5 seconds
	 * 3. if key pressed or mouse down, break
	 * 4. load PAL timing
	 * 5. poll keyboard for 5 seconds
	 * 6. if key pressed or mouse down, break
	 * 7. repeat 1-6
	 */
	set1bit(base);
	draw_si_logo(base);
	
	while(1)
	{
		show60Hz(base);
		if (poll(base))
		{
			setPram56((short) 0x0080, SpPtr);
			break;
		}	
		showNTSC(base);
		if (poll(base))
		{
			setPram56((short) 0x0081, SpPtr);
			break;
		}	
		showPAL(base);
		if (poll(base))
		{
			setPram56((short) 0x0082, SpPtr);
			break;
		}	
	}
	
	/*
	 * reboot, primary init will pick up from pram and use the right timing
	 */
/* This doesn't work on cx
#asm
;	ShutDwnStart();
    dc.w	$3f3c
	dc.w	$0002
	dc.w	$a895
#endasm
*/
#asm
ROMBase 	EQU 	$2AE					; ROM base address [pointer]
	move.l	ROMBase,a0
	jmp		$0a(a0)
#endasm
}
/*
 * set1bit()
 */
set1bit(base)
unsigned long	base;
{
	char	mmu_mode;
	long	saved_page;
	
	mmu_mode = true32b;
	siSwapMMUMode(&mmu_mode);  
	
	*(long *)(base + FAT_SLOT) = 0;
	*(long *)(base + CMODE) = 0;
	
	saved_page = *((long *)(base + PAGE_CTL));
	*(long *)(base + PAGE_CTL) = 0;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	*((unsigned char *)(base + bt473_command)) |= 0x08;
	*((unsigned char *)(base + bt473_p_addr)) = 0;   /* Address $0 */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	*((unsigned char *)(base + bt473_palette)) = 0;   /* LUT Color for red */
	*((unsigned char *)(base + bt473_palette)) = 0;   /* LUT Color for green */
	*((unsigned char *)(base + bt473_palette)) = 0;   /* LUT Color for blue */
	*((unsigned char *)(base + bt473_p_addr)) = 0x80;   /* Address $80 */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	*((unsigned char *)(base + bt473_palette)) = ((long) COLOR_ROPS >> 16) & 0x000000ff;   /* LUT Color for red */
	*((unsigned char *)(base + bt473_palette)) = ((long) COLOR_ROPS >> 8) & 0x000000ff;   /* LUT Color for red */
	*((unsigned char *)(base + bt473_palette)) = ((long) COLOR_ROPS) & 0x000000ff;   /* LUT Color for red */
	*((long *)(base + PAGE_CTL)) = saved_page;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	siSwapMMUMode(&mmu_mode);
}
/*
 * draw_si_logo()
 */
draw_si_logo(base)               /* Newest Screen Init Routine */
unsigned long	base;
{
	extern char		si_logo;
	eraseScrn(base);
	si_draw_bm1(base, &si_logo, (short) (DEF_WIDTH/2) , (short) (DEF_HEIGHT/3 + 39));	
}
/*
 * eraseScrn()
 */
eraseScrn(base)               /* Newest Screen Init Routine */
unsigned long	base;
{
	register short			i,j;
	register unsigned char	*to;
	char					mmu_mode;
	mmu_mode = true32b;	/* 32 bit mode */
	siSwapMMUMode(&mmu_mode);
  
	*(long *)(base + FAT_SLOT)		= 0;		/*  1RW	0 = skinny, 1 = fat slot decoding */
	*(long *)(base + NMRQ_DISABLE)	= 1;		/*  1RW	1 disables Interrupts */
  
	/*
	 * blank the screen
	 */
	for (i=0;i<480;i++) {
		to = (unsigned char *) (base + 1024L * i);
		for (j=0;j<640/8;j++) {
			*to++=0;
		}
	}
	
	siSwapMMUMode(&mmu_mode);
}
/*
 * si_draw_bm1()
 */
si_draw_bm1(base, bm, xcenter, ycenter)
unsigned long	base;
register char	*bm;
short			xcenter;
short			ycenter;
{
	register short			i,j,k;
	register unsigned char	*to;
	register char			c;
	short					xstart, ystart;
	short					p_width, p_height;
	char					mmu_mode;	
  
	mmu_mode = true32b;	/* 32 bit mode */
	siSwapMMUMode(&mmu_mode);
  
	*(long *)(base + FAT_SLOT)		= 0;		/*  1RW	0 = skinny, 1 = fat slot decoding */
	*(long *)(base + NMRQ_DISABLE)	= 1;		/*  1RW	1 disables Interrupts */
  
 	/*
 	 * the first two words are p_width and p_height
 	 */
 	p_width = *(short *)(bm);
 	p_height = *(short *) (bm + 2);
 	
	/*
	 * calculate starting point
	 */
	if((xcenter == 0) && (ycenter == 0)) {
		xstart = DEF_WIDTH/2 - p_width/2;
		ystart = DEF_HEIGHT/3 - p_height/2;
	}
	else {
		xstart = xcenter - p_width/2;
		ystart = ycenter - p_height/2;
	}
	if(xstart < 0)
		xstart = 0;
	if(ystart < 0)
		ystart = 0;
	
	/*
	 * draw the bitmap
	 */
	to = (unsigned char *)(base);
	to += (ystart * 1024L + xstart/8);
	for (i=0;i<p_height;i++) {
		for (j=0;j<p_width/8;j++) {
			*to++ = bm[4+i*(p_width/8)+j];
		}
		to += (1024L - p_width/8);
	}
  
	siSwapMMUMode(&mmu_mode);
}
/*
 * show60Hz()
 */
show60Hz(base)
unsigned long	base;
{
	extern char	bm6x4_67hz;
	short		xcenter;
	short		ycenter;
	
/* myDebugStr("\PDO_60Hz"); */
	si_load_timingtable(base, (short) DO_60Hz);
	xcenter = DEF_WIDTH/2 - 256/2 + 84;
	ycenter = DEF_HEIGHT/3 - 128/2 + 104;
	si_draw_bm1(base, &bm6x4_67hz, xcenter, ycenter); 
}
/*
 * showNTSC()
 */
showNTSC(base)
unsigned long	base;
{
	extern char	bm6x4ntsc;
	short		xcenter;
	short		ycenter;
	
/* myDebugStr("\PDO_NTSC"); */
	si_load_timingtable(base, (short) DO_NTSC);
	xcenter = DEF_WIDTH/2 - 256/2 + 84;
	ycenter = DEF_HEIGHT/3 - 128/2 + 104;
	si_draw_bm1(base, &bm6x4ntsc, xcenter, ycenter); 
}
/*
 * showPAL()
 */
showPAL(base)
unsigned long	base;
{
	extern char	bm6x4pal;
	short		xcenter;
	short		ycenter;
	
/* myDebugStr("\PDO_PAL"); */
	si_load_timingtable(base, (short) DO_PAL);
	xcenter = DEF_WIDTH/2 - 256/2 + 84;
	ycenter = DEF_HEIGHT/3 - 128/2 + 104;
	si_draw_bm1(base, &bm6x4pal, xcenter, ycenter); 
}
/*
 * loop wait for key pressed or mouse down
 * quit after 5000 tries (about 5 seconds)
 */
short poll(base)
unsigned long	base;
{
	KeyMap	km;
	short	count;
	
	count = 4096;	/* 0x1000 */
	while(count--) {	
		GetKeys(&km);
		km[1] &= 0xffff7ff0;		/* mask off cmd-opt-sht and cap */
		if(km[0] || km[1] || km[2] || km[3] || Button()) {
			return true;
		}
		else {
			si_wait_one();
			if( (count & 0x01FF) == 0)		/* toggle every 512 miliseconds */
				toggle_icons(base);
		}
	}
		
	return false;
}
/*
 * loop wait for key pressed or mouse down
 * quit after 4096 tries (about 5 seconds)
 */
toggle_icons(base)
unsigned long	base;
{
	register unsigned char	*dest1;
	register unsigned char	*dest2;
	register short			i;
	register short			j;
	short					logox;
	short					logoy;
	
	char					mmu_mode;	
  
	mmu_mode = true32b;	/* 32 bit mode */
	siSwapMMUMode(&mmu_mode);
  
	*(long *)(base + FAT_SLOT)		= 0;		/*  1RW	0 = skinny, 1 = fat slot decoding */
	*(long *)(base + NMRQ_DISABLE)	= 1;		/*  1RW	1 disables Interrupts */
	logox = DEF_WIDTH/2 - 256/2;
	logoy = DEF_HEIGHT/3 - 128/2;
	
	dest1 = (unsigned char *) base;
	dest2 = (unsigned char *) base;
	
	dest1 += (1024L * (logoy + 88)) + (logox + 160L)/8;
	dest2 += (1024L * (logoy + 88)) + (logox + 200L)/8;
	
	for(i = 0; i < 32; i++) {
		for(j = 0; j < 32/8; j++) {
			*dest1 = ~(*dest1);
			*dest2 = ~(*dest2);
			dest1++;
			dest2++;
		}
		dest1 += (1024 - 32/8);
		dest2 += (1024 - 32/8);
	}
	
	siSwapMMUMode(&mmu_mode);
}
/*
 * setPram56()
 */
setPram56(n, SpPtr)
short		n;
SpBlock		*SpPtr;				/* our sp block pointer to make the slot manager call */
{
	SPRAMRecord	PRAMRec;		/* temp storage for pram record */
	
	siGetPRAM(SpPtr, &PRAMRec);
	PRAMRec.vendorUse5 = n;
	PRAMRec.vendorUse6 = n;
	siSetPRAM(SpPtr, &PRAMRec);
}
/*
 * GetVersion()
 */
siGetVersion(SpPtr)
register SpBlock		*SpPtr;			/* our sp block pointer to make the slot manager call */
{
	long	rc;
	
	rc = sisVersion(SpPtr);
	if(rc < 0)
		return 0L;
	else
		return (SpPtr->spResult);
}
/*
 * si_load_timingtable()
 */
si_load_timingtable(base, ntsc_pal)
unsigned long	base;
short			ntsc_pal;
{
	register unsigned long	*reg;
	register unsigned long	*table_ptr;
	register short			count;
	register char			flags;
	short					resNum;
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	long					saved_page;
	char					mmu_mode;
	
	mmu_mode = true32b;	/* 32 bit mode */
	siSwapMMUMode(&mmu_mode);
	
	saved_page = *((long *)(base + PAGE_CTL));
	flags = 0;
	
	if(ntsc_pal != DO_60Hz)
		flags = BIT_INTERLACED;
	
	if(ntsc_pal == DO_PAL)
		flags |= BIT_PAL;
	*(long *)(base + PAGE_CTL) = 3;		/* 2RW	DAC control 0 = DAC, 1 = ADC, 2 = counters, 3 = control */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	if(ISGENLOCK(base))
		flags |= BIT_GENLOCK;
	siSwapMMUMode(&mmu_mode);
	/*
	 * find out the table to load, depending on the flags
	 * BIT_INTERLACED	1000
	 * BIT_PAL			0100
	 * BIT_GENLOCK		0010
	 * BIT_UNDERSCAN	0001
	 */
	switch(flags) {
		case 0x0:			/* 0000 */
		case 0x2:			/* 0010 */
		case 0x4:			/* 0100 */
		case 0x6:			/* 0110 */
				resNum = ID_6x4;
				break;
	
		case 0x1:			/* 0001 */
		case 0x3:			/* 0011 */
		case 0x5:			/* 0101 */
		case 0x7:			/* 0111 */
				resNum = ID_5x4;
				break;
	
		case 0x8:			/*1000 */
				resNum = ID_6x4ntsc;
				break;
				
		case 0x9:			/*1001 */
				resNum = ID_5x4ntsc;
				break;
				
		case 0xa:			/*1010 */
				resNum = ID_6x4ntscGL;
				break;
				
		case 0xb:			/*1011 */
				resNum = ID_5x4ntscGL;
				break;
				
		case 0xc:			/*1100 */
				resNum = ID_6x4pal;
				break;
				
		case 0xd:			/*1101 */
				resNum = ID_5x4pal;
				break;
				
		case 0xe:			/*1110 */
				resNum = ID_6x4palGL;
				break;
				
		case 0xf:			/*1111 */
				resNum = ID_5x4palGL;
				break;
	}
	
	/* Find parameter resource */
	SpPtr->spSlot = (base >> 24) & 0x0F;
	SpPtr->spExtDev = 0;
	SpPtr->spID = sRsrcBoard;		/* Find Board Resource */
	siSRsrcInfo(SpPtr);
	SpPtr->spID = sTimingTableDir;	/* Find Resoulution Directory */
	siSFindStruct(SpPtr);
	SpPtr->spID = resNum;			/* Find Parameters */
	siSFindStruct(SpPtr);
	
	table_ptr = (unsigned long *)(SpPtr->spsPointer + 8 - 2); /* skip count and adjust byte lane for long access */
		
	/*
	 * now load the registers from the table
	 */
	 
	mmu_mode = true32b;	/* 32 bit mode */
	siSwapMMUMode(&mmu_mode);
	
    *((unsigned long *)(base + OSC_SEL)) = *table_ptr++;
    *((unsigned long *)(base + EXT_SYNC_ENABLE)) = *table_ptr++;
	reg = (unsigned long *) (base + V_END_SYNC);
	count = 10;
	while(count--)
		*reg++ = *table_ptr++;
	/*
	 * set crystal select
	 */
	*(long *)(base + PAGE_CTL) = 3;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	if(flags & BIT_PAL)
		*(short *)(base + pip_control_3) |= 0x0020;
	else
		*(short *)(base + pip_control_3) &= 0xFFDF;
		
	/*
	 * if PAL set bit 5 of DAC command register to 0, else 1
	 */
	*(long *)(base + PAGE_CTL) = 0;		/* 2RW	DAC control 0 = DAC, 1 = ADC, 2 = counters, 3 = control */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	if((flags & BIT_INTERLACED) && (flags & BIT_PAL))
		*(unsigned char *)(base + bt473_command) &= 0xDF;
	else
		*(unsigned char *)(base + bt473_command) |= 0x20;
	/*
	 * restore page_ctl
	 */
	*((long *)(base + PAGE_CTL)) = saved_page;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	siSwapMMUMode(&mmu_mode);
}
/*
 * _si_wait_one()
 */
#asm
_si_wait_one
	CLR.L	D0
	MOVE.W	$D00,D0			; Get TimeDBRA Global
si_more_dbras				; Loop for 1 ms
	DBRA	D0,si_more_dbras
	RTS
#endasm 
/*
 * _siSwapMMUMode()
 */
#asm
;__________________________________________________________________________________________________
; Subroutine Swaps MMU Mode
; expects pointer to new mode on stack
; returns old mode in place of new mode with pointer still on the stack
_siSwapMMUMode
	MOVE.L	4(SP),A0
	MOVE.B	(A0),D0
	_SwapMMUMode		; SwapMMUMode $A05D
	MOVE.L	4(SP),A0
	MOVE.B	D0,(A0)
	RTS
#endasm 
/*
 * SRsrcInfo(spPtr) Glue
 */
#asm
_siSRsrcInfo
	MOVE.L	4(SP),A0
	MOVEQ	#$16,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SFindStruct(spPtr) Glue
 */
#asm
_siSFindStruct
	MOVE.L	4(SP),A0
	_SFindStruct
	RTS
#endasm 
/*
 * sVersion(SpPtr)
 */
#asm
_sisVersion
	MOVE.L	4(SP),A0
	MOVEQ	#8,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * sisInsertSRTRec(spPtr)
 */
#asm
_sisInsertSRTRec
	MOVE.L	4(SP),A0
	MOVEQ	#$A,D0
	DC.W	$A06E
	RTS
#endasm
/*
 * siSReadPRAMRec(spPtr)
 */
#asm
_siSReadPRAMRec
	MOVE.L	4(SP),A0
	MOVEQ	#$11,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * siSPutPRAMRec(spPtr)
 */
#asm
_siSPutPRAMRec
	MOVE.L	4(SP),A0
	MOVEQ	#$12,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * siSDeleteSRTRec(spPtr)
 */
#asm
_siSDeleteSRTRec
	MOVE.L	4(SP),A0
	MOVEQ	#$31,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * Delay(Ticks) Glue
 */
#asm
_piDelay
	MOVE.L	4(SP),A0
	_Delay
	RTS
#endasm 
#asm
_si_logo
	dc.w	$100,$32
	dc.w	$ffff,$ffff,$ffff,$ffff,$ffff,$ffff,$ffff,$ffff
	dc.w	$ffff,$ffff,$ffff,$ffff,$ffff,$ffff,$ffff,$ffff
	dc.w	$ffff,$ffff,$ffff,$ffff,$ffff,$ffff,$ffff,$ffff
	dc.w	$ffff,$ffff,$ffff,$ffff,$ffff,$ffff,$ffff,$ffff
     dc.w     		$C000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
     dc.w     		$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0003
     dc.w     		$C000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
     dc.w     		$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0003
     dc.w     		$C000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
     dc.w     		$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0003
     dc.w     		$C000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
     dc.w     		$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0003
     dc.w     		$C000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
     dc.w     		$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0003
     dc.w     		$C000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
     dc.w     		$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0003
     dc.w     		$C000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
     dc.w     		$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0003
     dc.w     		$C000,$0000,$01FF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF
     dc.w     		$8000,$0001,$FFFF,$FFFF,$81FF,$FFFF,$FF80,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$0000,$0000,$C100,$0000,$00C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$125E,$0000,$C100,$0000,$00C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$0001,$0000,$C100,$0000,$00C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$0000,$8000,$C100,$0000,$00C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$0001,$E000,$C100,$0000,$00C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$0000,$0000,$C100,$0000,$00C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$0003,$F000,$C100,$0000,$00C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$0004,$0800,$C100,$0000,$00C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$0078,$0780,$C13F,$FFFF,$FCC0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$0080,$0040,$C140,$0000,$02C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$008F,$FC40,$C15A,$AAAA,$AAC0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$00B8,$0740,$C140,$0180,$02C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$00A8,$0540,$C155,$5655,$5AC0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$00A8,$0540,$C140,$0240,$02C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$00A8,$0540,$C15A,$AA6A,$AAC0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$00AF,$FD40,$C140,$0240,$02C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$00A0,$0140,$C145,$7E7F,$52C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$00A0,$0140,$C140,$0240,$02C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$00A0,$0140,$C140,$0270,$02C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$00A0,$0140,$C13F,$FE4D,$FCC0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$00A0,$0140,$C100,$1A03,$00C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$00A0,$0140,$C100,$2600,$80C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$00A0,$0140,$C100,$1600,$80C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$00A0,$0140,$C100,$1200,$80C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$00A0,$0140,$C100,$0800,$80C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$00A0,$0140,$C100,$0800,$80C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$00A0,$0140,$C100,$0400,$80C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$009F,$FE40,$C100,$0201,$00C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$0080,$0040,$C100,$0101,$00C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$0080,$0040,$C100,$0101,$00C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$007F,$FF80,$C100,$0101,$00C0,$0003
     dc.w     		$C000,$0000,$0100,$0000,$0000,$0000,$0000,$0000
     dc.w     		$C000,$0001,$0000,$0000,$C100,$03FF,$00C0,$0003
     dc.w     		$C000,$0000,$01FF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF
     dc.w     		$C000,$0001,$FFFF,$FFFF,$C1FF,$FFFF,$FFC0,$0003
     dc.w     		$C000,$0000,$00FF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF
     dc.w     		$C000,$0000,$FFFF,$FFFF,$C0FF,$FFFF,$FFC0,$0003
     dc.w     		$C000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
     dc.w     		$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0003
     dc.w     		$C000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
     dc.w     		$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0003
     dc.w     		$C000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
     dc.w     		$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0003
     dc.w     		$C000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
     dc.w     		$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0003
     dc.w     		$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF
     dc.w     		$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF
     dc.w     		$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF
     dc.w     		$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF
#endasm
#asm
_bm6x4_67hz    
	dc.w	$0048,$0025		; width,height
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$18,$18,$78,$00,$03,$0f,$87,$80
	dc.b	$00,$e0,$38,$cc,$00,$07,$18,$cc,$c0
	dc.b	$01,$c0,$38,$cc,$00,$07,$38,$cc,$c0
	dc.b	$03,$80,$79,$ce,$00,$0f,$38,$dc,$e0
	dc.b	$03,$80,$f9,$ce,$00,$1f,$3c,$9c,$e0
	dc.b	$07,$f0,$b9,$ce,$ff,$97,$1f,$1c,$e0
	dc.b	$07,$39,$39,$ce,$72,$27,$0f,$9c,$e0
	dc.b	$07,$3a,$39,$ce,$3c,$47,$1f,$dc,$e0
	dc.b	$07,$3b,$fd,$ce,$1c,$7f,$b3,$dc,$e0
	dc.b	$07,$3b,$fd,$ce,$1c,$7f,$b1,$dc,$e0
	dc.b	$03,$38,$38,$cc,$2e,$07,$31,$cc,$c0
	dc.b	$03,$30,$38,$cc,$47,$07,$39,$8c,$c0
	dc.b	$01,$e0,$38,$78,$ef,$87,$0f,$07,$80
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$02,$03,$3f,$9f,$3e,$00,$80,$00
	dc.b	$00,$04,$1c,$3f,$0e,$1c,$00,$40,$00
	dc.b	$00,$08,$38,$7f,$0e,$1c,$00,$20,$00
	dc.b	$00,$10,$70,$41,$0e,$1c,$00,$10,$00
	dc.b	$00,$10,$70,$02,$0e,$1c,$00,$10,$00
	dc.b	$00,$30,$fe,$02,$0e,$1c,$fe,$18,$00
	dc.b	$00,$30,$e7,$02,$0f,$fc,$9e,$18,$00
	dc.b	$00,$30,$e7,$04,$0e,$1c,$9c,$18,$00
	dc.b	$00,$30,$e7,$04,$0e,$1c,$38,$18,$00
	dc.b	$00,$30,$e7,$04,$0e,$1c,$38,$18,$00
	dc.b	$00,$30,$67,$08,$0e,$1c,$72,$18,$00
	dc.b	$00,$10,$66,$08,$0e,$1c,$f2,$10,$00
	dc.b	$00,$10,$3c,$08,$1f,$3e,$fe,$10,$00
	dc.b	$00,$08,$00,$00,$00,$00,$00,$20,$00
	dc.b	$00,$04,$00,$00,$00,$00,$00,$40,$00
	dc.b	$00,$02,$00,$00,$00,$00,$00,$80,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00
#endasm
	
#asm
_bm6x4ntsc
	dc.w	$0048,$0025		; width,height
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$18,$18,$78,$00,$03,$0f,$87,$80
	dc.b	$00,$e0,$38,$cc,$00,$07,$18,$cc,$c0
	dc.b	$01,$c0,$38,$cc,$00,$07,$38,$cc,$c0
	dc.b	$03,$80,$79,$ce,$00,$0f,$38,$dc,$e0
	dc.b	$03,$80,$f9,$ce,$00,$1f,$3c,$9c,$e0
	dc.b	$07,$f0,$b9,$ce,$ff,$97,$1f,$1c,$e0
	dc.b	$07,$39,$39,$ce,$72,$27,$0f,$9c,$e0
	dc.b	$07,$3a,$39,$ce,$3c,$47,$1f,$dc,$e0
	dc.b	$07,$3b,$fd,$ce,$1c,$7f,$b3,$dc,$e0
	dc.b	$07,$3b,$fd,$ce,$1c,$7f,$b1,$dc,$e0
	dc.b	$03,$38,$38,$cc,$2e,$07,$31,$cc,$c0
	dc.b	$03,$30,$38,$cc,$47,$07,$39,$8c,$c0
	dc.b	$01,$e0,$38,$78,$ef,$87,$0f,$07,$80
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$27,$0f,$7f,$f0,$e8,$07,$94,$00
	dc.b	$00,$43,$82,$67,$31,$98,$1c,$72,$00
	dc.b	$00,$83,$c2,$47,$13,$08,$38,$31,$00
	dc.b	$01,$03,$e2,$47,$13,$88,$30,$10,$80
	dc.b	$01,$02,$e2,$07,$03,$c0,$70,$00,$80
	dc.b	$03,$02,$72,$07,$01,$e0,$70,$00,$c0
	dc.b	$03,$02,$3a,$07,$01,$f8,$70,$00,$c0
	dc.b	$03,$02,$3e,$07,$00,$7c,$70,$00,$c0
	dc.b	$03,$02,$1e,$07,$00,$1c,$70,$00,$c0
	dc.b	$03,$02,$0e,$07,$02,$0c,$30,$00,$c0
	dc.b	$03,$02,$06,$07,$02,$0c,$38,$30,$c0
	dc.b	$01,$02,$06,$07,$03,$18,$1c,$60,$80
	dc.b	$01,$07,$82,$1f,$c2,$f0,$07,$80,$80
	dc.b	$00,$80,$00,$00,$00,$00,$00,$01,$00
	dc.b	$00,$40,$00,$00,$00,$00,$00,$02,$00
	dc.b	$00,$20,$00,$00,$00,$00,$00,$04,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00
#endasm
#asm
_bm6x4pal
	dc.w	$0048,$0025		; width,height
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$18,$18,$78,$00,$03,$0f,$87,$80
	dc.b	$00,$e0,$38,$cc,$00,$07,$18,$cc,$c0
	dc.b	$01,$c0,$38,$cc,$00,$07,$38,$cc,$c0
	dc.b	$03,$80,$79,$ce,$00,$0f,$38,$dc,$e0
	dc.b	$03,$80,$f9,$ce,$00,$1f,$3c,$9c,$e0
	dc.b	$07,$f0,$b9,$ce,$ff,$97,$1f,$1c,$e0
	dc.b	$07,$39,$39,$ce,$72,$27,$0f,$9c,$e0
	dc.b	$07,$3a,$39,$ce,$3c,$47,$1f,$dc,$e0
	dc.b	$07,$3b,$fd,$ce,$1c,$7f,$b3,$dc,$e0
	dc.b	$07,$3b,$fd,$ce,$1c,$7f,$b1,$dc,$e0
	dc.b	$03,$38,$38,$cc,$2e,$07,$31,$cc,$c0
	dc.b	$03,$30,$38,$cc,$47,$07,$39,$8c,$c0
	dc.b	$01,$e0,$38,$78,$ef,$87,$0f,$07,$80
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00,$00,$9f,$c0,$10,$1f,$82,$00,$00
	dc.b	$00,$01,$0e,$60,$30,$0e,$01,$00,$00
	dc.b	$00,$02,$0e,$70,$38,$0e,$00,$80,$00
	dc.b	$00,$04,$0e,$70,$38,$0e,$00,$40,$00
	dc.b	$00,$04,$0e,$70,$5c,$0e,$00,$40,$00
	dc.b	$00,$0c,$0e,$70,$5c,$0e,$00,$60,$00
	dc.b	$00,$0c,$0e,$e0,$9e,$0e,$00,$60,$00
	dc.b	$00,$0c,$0f,$c0,$8e,$0e,$00,$60,$00
	dc.b	$00,$0c,$0e,$00,$ff,$0e,$00,$60,$00
	dc.b	$00,$0c,$0e,$01,$07,$0e,$08,$60,$00
	dc.b	$00,$0c,$0e,$01,$07,$0e,$08,$60,$00
	dc.b	$00,$04,$0e,$03,$07,$8e,$10,$40,$00
	dc.b	$00,$04,$1f,$07,$8f,$df,$f0,$40,$00
	dc.b	$00,$02,$00,$00,$00,$00,$00,$80,$00
	dc.b	$00,$01,$00,$00,$00,$00,$01,$00,$00
	dc.b	$00,$00,$80,$00,$00,$00,$02,$00,$00
	dc.b	$00,$00,$00,$00,$00,$00,$00,$00,$00
	dc.b	$00
#endasm
#if 0
#asm
_ntsc_bm
	dc.w	$58,$20
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0001,$fc07
	dc.w	$cfff,$fc1f,$1003,$e100,$007c,$038e,$1e1c,$60f0
	dc.w	$1c1f,$0000,$3e01,$0c1e,$0cc0,$7078,$0f00,$003f
	dc.w	$0108,$1e05,$c030,$f007,$0000,$2f81,$081e,$05c0
	dc.w	$30f0,$0300,$002f,$c108,$1e05,$e011,$e001,$0000
	dc.w	$27e1,$001e,$01f0,$01e0,$0000,$0023,$e100,$1e00
	dc.w	$fe03,$e000,$0000,$21f1,$001e,$00ff,$83e0,$0000
	dc.w	$0020,$f900,$1e00,$7fc3,$e000,$0000,$20fd,$001e
	dc.w	$001f,$e3e0,$0000,$0020,$7f00,$1e00,$07f3,$e000
	dc.w	$0000,$203f,$001e,$0001,$f1e0,$0000,$0020,$1f00
	dc.w	$1e01,$00f1,$e000,$0000,$200f,$001e,$0180,$71f0
	dc.w	$0000,$0020,$0700,$1e01,$8070,$f003,$0000,$2007
	dc.w	$001e,$01c0,$6078,$0600,$0070,$0300,$3f01,$e1c0
	dc.w	$3c1c,$0000,$f801,$00ff,$c1ff,$0007,$f000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
#endasm
#asm
_pal_bm
	dc.w	$58,$20
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0ffc,$0010,$0ff0
	dc.w	$0000,$0000,$0003,$c700,$1003,$c000,$0000,$0000
	dc.w	$03c3,$8038,$03c0,$0000,$0000,$0003,$c3c0,$3803
	dc.w	$c000,$0000,$0000,$03c3,$c07c,$03c0,$0000,$0000
	dc.w	$0003,$c3c0,$7c03,$c000,$0000,$0000,$03c3,$c05c
	dc.w	$03c0,$0000,$0000,$0003,$c380,$9e03,$c000,$0000
	dc.w	$0000,$03c7,$009e,$03c0,$0000,$0000,$0003,$fe01
	dc.w	$0f03,$c000,$0000,$0000,$03c0,$010f,$03c0,$0000
	dc.w	$0000,$0003,$c001,$ff03,$c020,$0000,$0000,$03c0
	dc.w	$0207,$83c0,$2000,$0000,$0003,$c002,$0383,$c040
	dc.w	$0000,$0000,$03c0,$0603,$c3c0,$c000,$0000,$0003
	dc.w	$c006,$03c3,$c1c0,$0000,$0000,$0ff0,$1f0f,$ffff
	dc.w	$c000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
#endasm
#endif
#asm
; ==================END OF SECONDARY INIT BLOCK=====================
endsecondaryinit
#endasm
/* My 68020 Driver sBlock */
#asm
mydrvr
; ==================BEGINNING OF DRIVER BLOCK=====================
	dc.l  endmydrvr-mydrvr      	; Length of sBlock
#endasm
/* RasterOps 1.0 24MTV                            */
#asm
_main
	dc.w    $4C00         	; driver responds to Control and Status, NeedsLock
	dc.w    0             	; NOT A DA (was "update every x seconds")
	dc.w    0             	; NOT A DA (was "detect events")
	dc.w    0             	; NOT A DA (was "menu ID number")
	dc.w    _myopen-_main	; open routine
	dc.w    _main-_main  	; prime routine (not needed for this driver)
	dc.w    _control-_main 	; control routine
	dc.w    _status-_main	; status routine
	dc.w    _myclose-_main	; close routine
	dc.b    _titleend-_title
_title
		     	;  Be sure to use this format:  ".RasterOps VVV BBBBB xxx..."
		     	;  Where VVV = Version number of the driver,
		     	;        BBBBB = Board model
		     	;        xxx... = Anything else you want to say.
		     	;  The "Ops ", and BBBBB are checked by the 24-bit environment installer
		     	;  to determine if this hardware can support that environment, so be
		     	;  sure to include them in this format if you want the environment to
		     	;  recognize your hardware.
	dc.b    ".RasterOps 2.0 MediaTime Video Driver"
_titleend
	ds      0            	;for alignment
#endasm
#asm
_save
	move.l    8(sp),a2
	move.l    a0,(a2)    	; save pb pointer
	move.l    4(sp),a2
	move.l    a1,(a2)    	; save DCE pointer
	rts
#endasm 
/*
 * SReadPRAMRec(spPtr)
 */
#asm
_drSReadPRAMRec
	MOVE.L	4(SP),A0
	MOVEQ	#$11,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SPutPRAMRec(spPtr)
 */
#asm
_drSPutPRAMRec
	MOVE.L	4(SP),A0
	MOVEQ	#$12,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SIntInstall (spPtr) Glue
 */
#asm
_drSIntInstall
	move.w    8(sp),d0
	move.l    4(sp),a0
	_SIntInstall         	; SIntInstall $A075
	rts
#endasm 
/*
 * SIntRemove (spPtr) Glue
 */
#asm
_drSIntRemove
	move.w    8(sp),d0
	move.l    4(sp),a0
	_SIntRemove          	; SIntRemove $A076
	rts
#endasm 
/*
 * SwapMMUMode Glue
 */
#asm
_drSwapMMUMode
	MOVE.L  4(SP),A0
	MOVE.B  (A0),D0
	_SwapMMUMode         	; SwapMMUMode $A05D
	MOVE.L  4(SP),A0
	MOVE.B  D0,(A0)
	RTS
#endasm 
/*
 * SetSRsrcState(spPtr)
 */
#asm
_drSetSRsrcState
	MOVE.L	4(SP),A0
	MOVEQ	#$09,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SRsrcInfo(spPtr) Glue
 */
#asm
_drSRsrcInfo
	MOVE.L	4(SP),A0
	MOVEQ	#$16,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SFindStruct(spPtr) Glue
 */
#asm
_drSFindStruct
	MOVE.L	4(SP),A0
	_SFindStruct
	RTS
#endasm 
/*
 * SUpdateSRT(spPtr) Glue
 */
#asm
_drSUpdateSRT
	MOVE.L	4(SP),A0
	_SUpdateSRT
	RTS
#endasm 
struct TMTask {
    QElemPtr qLink;
    short qType;
    ProcPtr tmAddr;
    long tmCount;
    long tmWakeUp;
    long tmReserved;
};
typedef struct TMTask TMTask;
typedef TMTask *TMTaskPtr;
/*
 * InsTime(QElemPtr tmTaskPtr) Glue
 */
#asm
_drInsTime
	MOVE.L	4(SP),A0
	DC.W	$A058
	RTS
#endasm 
/*
 * InsXTime(QElemPtr tmTaskPtr) Glue
 */
#asm
_drInsXTime
	MOVE.L	4(SP),A0
	DC.W	$A458
	RTS
#endasm 
/*
 * PrimeTime(QElemPtr tmTaskPtr) Glue
 */
#asm
_drPrimeTime
	MOVE.L	4(SP),A0
	MOVE.L	8(SP),D0
	DC.W	$A05A
	RTS
#endasm 
/*
 * RmvTime(QElemPtr tmTaskPtr) Glue
 */
#asm
_drRmvTime
	MOVE.L	4(SP),A0
	DC.W	$A059
	RTS
#endasm 
#asm
;
;	Do full screen dithered gray for bit depth determined by mode:
;         80 - 1
;         81 - 2
;         82 - 4
;         83 - 8
;         84 - 24
;
_grayscrn	; grayscrn(base,mode)
			; long base
			; short mode
	MOVEM.L	D0-D7/A0-A1,-(SP)	; save all registers	40 bytes
	MOVEQ   #1,D0
	DC.W    $A05D				; SwapMMUMode to 32 bit
	MOVE.B  D0,D3				; save previous mmu mode in D3
	MOVE.W	48(SP),D1			; get the mode		40 + 8	off SP
	ANDI.L	#7,D1				; make it 0 based
	LEA	ModeTbl,A1				; point to tables
	MOVE.L	0(A1,D1*8),D0		; D0 = the 1st long of pattern
	MOVE.W	4(A1,D1*8),D4		; D4 = bytes/row for the mode
	MOVE.W	6(A1,D1*8),D5		; D5 = screen height
	SUBQ	#1,D5				; make it 0 based
	MOVE.L	D0,D2				; get copy of pattern
	MOVE.L	#$400,D6			; set rowbytes to 1k for 1-8 bit
	CMP.L	#4,D1				; if 24 bit screen mode (84)
	BNE	not24					; then
	NOT.L	D2					; invert the copy
	LSL	#2,D6					; and set rowbytes to 4k for 24 bit
not24							; else leave 1k rowbytes and use pattern as is
	MOVE.L	D2,D1				; get 2nd long of pattern
	
	AND.L	#$FF0FFFFF,44(SP)	; need to mask off second s of fss ?????????
	MOVE.L	44(SP),A1			; point to start of screen		40 + 4	off SP
NxtRow2	
	MOVE.L	A1,A0				; get next row
	MOVE.W	D4,D2				; get bytes per row
	LSR	#3,D2					; get pairs of longs per row
	SUBQ	#1,D2				; make count 0 based
NxtLong2
	MOVE.L	D0,(A0)+			; write gray
	MOVE.L	D1,(A0)+			; write gray
	DBF	D2,NxtLong2				; for entire width of row
	NOT.L	D0					; get inverse gray for next row
	NOT.L	D1					; for alternate lines
	ADDA.W	D6,A1				; bump to next row
	DBF	D5,NxtRow2				; until no more rows
	MOVE.B  D3,D0				; restore previous mmu mode
	DC.W    $A05D				; SwapMMUMode
	MOVEM.L	(SP)+,D0-D7/A0-A1	; restore all registers
	RTS							; and return
			
; Mode info: 	    Pattern,Bytes/Row,Height
ModeTbl	
	DC.W	$AAAA,$AAAA,$0400,$0200		; one bit per pixel ???? all heights 512 for now ????
	DC.W	$CCCC,$CCCC,$0400,$0200		; two bit per pixel
	DC.W	$F0F0,$F0F0,$0400,$0200		; four bit per pixel
	DC.W	$FF00,$FF00,$0400,$0200		; eight bit per pixel
	DC.W	$0000,$0000,$1000,$0200		; 32 bit per pixel
#endasm
#asm
TimeDBRA EQU	$0D00         /* (word) number of iterations of DBRA per millisecond*/
#endasm
/******************************************************************/
/* delay(short:time)     Delay by 'time' milliseconds             */
/******************************************************************/
delay(time)
short	time;
{
#asm
	MOVE.W	8(A6),D0	; Get the time
	MULS.W	TimeDBRA,D0	; times the TimeDBRA Global
some_dbras			; Loop for 1 ms
	DBRA	D0,some_dbras
#endasm
}
/******************************************************************/
/* Set dacs to all gray to avoid flashes when changing bit depths */
/******************************************************************/
graytable(base)
unsigned long base;  	/* Must be Fs000000 not Fss00000 */
{
	long	i;
	unsigned char *dac_addr, *dac_data;
	char mmu_mode;		/* MMU Mode (0=24-bit addressing 1=32-bit addressing) */
	long saved_page;
	
	dac_addr = ((unsigned char *)(base + bt473_p_addr));
	dac_data = ((unsigned char *)(base + bt473_palette));
	
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	
	saved_page = *(long *)(base + PAGE_CTL);
	*(long *)(base + PAGE_CTL) = 0;	/*  2RW	PAGE control 0 = DAC, 1 = ADC, 2 = PIP Regs */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	/* Set LUT $00-$FF -> $80 */
	waitvblank(base);         /* Wait for blanking???? */ /* turn off interrupts???? */
	*dac_addr = 0x00;       /* Address 0 */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	for(i=0;i<256;i++)
	{
		*dac_data = 0x80;   /* LUT Color for red channel ???? use gamma corrected gray */
		*dac_data = 0x80;   /* LUT Color for green channel */
		*dac_data = 0x80;   /* LUT Color for blue channel */
	}
	*(long *)(base + PAGE_CTL) = saved_page;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	drSwapMMUMode(&mmu_mode);
}
/************************************************************************************/
/* Called with a word (OSErr error) on the stack indicating an error code */
#asm
_checkiodone
	move.w  4(sp),D0  	; Return error code for now
	BTST    #1,6(A0)  	; Check ioTrap field of the paramblock if it has the "NoQueue" bit set.
	BEQ.S   _goiodone 	; The bit wasn't set, so it has a queue element allocated for it.  Go do jIODone.
	RTS               	; Go back for a normal return since no queue element was allocated.
_goiodone
	add.l   #6,sp     	; Pop our return address away, and error code
	unlk    a6        	; Unlink the subroutine (Return address is now on top of stack)
	MOVEA.L $8FC,A0   	; Load address of jIODone routine
	JMP     (A0)      	; Use it to exit with
#endasm
/*еееее Energy Star (((((*/
#define	POWER_ON		0
#define	POWER_OFF		1
#define	POWER_STANDBY	2
typedef struct
{
	short		ves;	/* vertical end sync		*/
	short		vsb;	/* vertical start blank		*/
	short		veb;	/* vertical end blank		*/
	short		vtot;	/* vertical total			*/
	short		hes;	/* horizontal end sync		*/
	short		hsb;	/* horizontal start blank	*/
	short		heb;	/* horizontal end blank		*/
	short		htot;	/* horizontal total			*/
} _264family_data;
#define	_264family_energy_saving_ves	0x000F
#define	_264family_energy_saving_vsb	(_264family_energy_saving_ves - 2)
#define	_264family_energy_saving_vtot	(_264family_energy_saving_ves - 1)
/*еееее Energy Star )))))*/
/*еееее Display Manager (((((*/
struct VDSwitchInfoRec {
	unsigned short				csMode;							/* (word) mode depth */
	unsigned long				csData;							/* (long) functional sResource of mode */
	unsigned short				csPage;							/* (word) page to switch in */
	Ptr							csBaseAddr;						/* (long) base address of page (return value) */
	unsigned long				csReserved;						/* (long) Reserved (set to 0) */
};
typedef struct VDSwitchInfoRec VDSwitchInfoRec;
typedef VDSwitchInfoRec *VDSwitchInfoPtr;
struct VDTimingInfoRec {
	unsigned long				csTimingMode;					/* LONGINT - (long) timing mode (a la InitGDevice) */
	unsigned long				csTimingReserved;				/* LONGINT - (long) reserved */
	unsigned long				csTimingFormat;					/* LONGINT - (long) what format is the timing info */
	unsigned long				csTimingData;					/* LONGINT - (long) data supplied by driver */
	unsigned long				csTimingFlags;					/* LONGINT - (long) mode within device */
};
typedef struct VDTimingInfoRec VDTimingInfoRec;
typedef VDTimingInfoRec *VDTimingInfoPtr;
struct VDDisplayConnectInfoRec {
	unsigned short				csDisplayType;					/* INTEGER - (word) Type of display connected */
	unsigned short				csConnectTagged;				/* INTEGER - (word) Display is currently "it" (tagged to identify component) */
	unsigned long				csConnectFlags;					/* LONGINT - (long) tell us about the connection */
	unsigned long				csDisplayComponent;				/* LONGINT - (long) if the card has a direct connection to the display, it returns the display component here (FUTURE) */
	unsigned long				csConnectReserved;				/* LONGINT - (long) reserved */
};
typedef struct VDDisplayConnectInfoRec VDDisplayConnectInfoRec;
typedef VDDisplayConnectInfoRec *VDDisplayConnectInfoPtr;
#define kDeclROMtables 'decl'
enum  {
	kAllModesValid				= 0,							/* All modes not trimmed by primary init are good close enough to try */
	kAllModesSafe				= 1,							/* All modes not trimmed by primary init are know to be safe */
	kReportsTagging				= 2,							/* Can detect tagged displays (to identify smart monitors) */
	kHasDirectConnect			= 3,							/* True implies that driver can talk directly to device (e.g. serial data link via sense lines) */
	kIsMonoDev					= 4,	/*jwh					/* this display does not support color */
	kUncertainConnect			= 5		/*jwh					/* there may not be a display; user must confirm some operations  */
};
/* csDisplayType values in VDDisplayConnectInfo */
enum  {
	kUnknownConnect				= 1,
	kPanelConnect				= 2,
	kFixedModeCRTConnect		= 3,
	kMultiModeCRT1Connect		= 4,							/* 320x200 maybe, 12" maybe, 13" (default), 16" certain, 19" maybe, 21" maybe */
	kMultiModeCRT2Connect		= 5,							/* 320x200 maybe, 12" maybe, 13" certain, 16" (default), 19" certain, 21" maybe */
	kMultiModeCRT3Connect		= 6,							/* 320x200 maybe, 12" maybe, 13" certain, 16" certain, 19" default, 21" certain */
	kMultiModeCRT4Connect		= 7,							/* Expansion to large multi mode (not yet used) */
	kModelessConnect			= 8								/* Expansion to modeless model (not yet used) */
};
enum  {
/*	kModeSafe					= 0,							/*  This mode does not need confirmation */
/*	kModeDefault				= 1								/* This is the default mode for this type of connection */
	kModeValid					= 0,								/* This is the default mode for this type of connection */
	kModeSafe					= 1,							/*  This mode does not need confirmation */
	kModeDefault				= 2								/* This is the default mode for this type of connection */
};
/*еееее Display Manager )))))*/
typedef struct GammaTable
{
	short	gVersion;
	short	gType;
	short	gFormulaSize;
	short	gChanCnt;
	short	gDataCnt;
	short	gDataWidth;
/*  char gFormulaData[0];	/*gFormulaData[????]; Variable size array so not included in struct. */
/*  char gData[0];		/*gData[????]; Variable size array so not included in struct. */
} GammaTable;
typedef struct VDGammaRecord
{
	GammaTable	*csGTable;
}  VDGammaRecord, *VDGamRecPtr;
/* Apple Gamma data (Temporary until we use gamma directory) */
#asm
_applegamma
	DC.B	$00,$05,$09,$0B,$0E,$10,$13,$15,$17,$19,$1B,$1D,$1E,$20,$22,$24
	DC.B	$25,$27,$28,$2A,$2C,$2D,$2F,$30,$31,$33,$34,$36,$37,$38,$3A,$3B
	DC.B	$3C,$3E,$3F,$40,$42,$43,$44,$45,$47,$48,$49,$4A,$4B,$4D,$4E,$4F
	DC.B	$50,$51,$52,$54,$55,$56,$57,$58,$59,$5A,$5B,$5C,$5E,$5F,$60,$61
	DC.B	$62,$63,$64,$65,$66,$67,$68,$69,$6A,$6B,$6C,$6D,$6E,$6F,$70,$71
	DC.B	$72,$73,$74,$75,$76,$77,$78,$79,$7A,$7B,$7C,$7D,$7E,$7F,$80,$81
	DC.B	$81,$82,$83,$84,$85,$86,$87,$88,$89,$8A,$8B,$8C,$8C,$8D,$8E,$8F
	DC.B	$90,$91,$92,$93,$94,$95,$95,$96,$97,$98,$99,$9A,$9B,$9B,$9C,$9D
	DC.B	$9E,$9F,$A0,$A1,$A1,$A2,$A3,$A4,$A5,$A6,$A6,$A7,$A8,$A9,$AA,$AB
	DC.B	$AB,$AC,$AD,$AE,$AF,$B0,$B0,$B1,$B2,$B3,$B4,$B4,$B5,$B6,$B7,$B8
	DC.B	$B8,$B9,$BA,$BB,$BC,$BC,$BD,$BE,$BF,$C0,$C0,$C1,$C2,$C3,$C3,$C4
	DC.B	$C5,$C6,$C7,$C7,$C8,$C9,$CA,$CA,$CB,$CC,$CD,$CD,$CE,$CF,$D0,$D0
	DC.B	$D1,$D2,$D3,$D3,$D4,$D5,$D6,$D6,$D7,$D8,$D9,$D9,$DA,$DB,$DC,$DC
	DC.B	$DD,$DE,$DF,$DF,$E0,$E1,$E1,$E2,$E3,$E4,$E4,$E5,$E6,$E7,$E7,$E8
	DC.B	$E9,$E9,$EA,$EB,$EC,$EC,$ED,$EE,$EE,$EF,$F0,$F1,$F1,$F2,$F3,$F3
	DC.B	$F4,$F5,$F5,$F6,$F7,$F8,$F8,$F9,$FA,$FA,$FB,$FC,$FC,$FD,$FE,$FF
#endasm
/* Default resolution mode struct */
typedef struct VDDefaultInfo
{
	char csMode;
} VDDefaultInfo, *VDDefaultInfoPtr;
/*еееее Energy Star (((((*/
typedef unsigned char	*VDFlagPtr;
/* Time manager task record with slot number attached for faking VBL tasks */
typedef struct fakeVBL
{
	TMTask	tmtask;
	short	slot;
} fakeVBL, *fakeVBLPtr;
/*еееее Energy Star )))))*/
/* ееее WARNING:    There are hard coded offsets to the PZE struct members in Center()!
	Do NOT change the ordering or content of private storage without making sure the PZE
	members haven't changed their positions from the top of the struct! 
	ееее
*/
typedef struct mystorage 
{
	SlotIntQElement	*myslotqeleptr;	/* saved on open for use in closing */
	unsigned char	clut[768];		/* lut copy wouldn't be required if Bt-478 were really dual ported ???? */
	unsigned long	dacdata[256];	/* buffer for data to be sent to DACs during blanking ???? */
	unsigned short	bwmapping;		/* gray mapping flag; 0 = off, 1 = on */
	unsigned short	newmode;		/* semaphore for SetGamma to know if called between SetMode and GrayPage */
	unsigned short	mode;			/* current video mode (bit depth) */
	unsigned short  pages;
	unsigned short	screensize;
	unsigned long	screenbase;		/* frame buffer base address */
	unsigned short	intflag;		/* interrupts enabled flag; 0 = off, 1 = on */
	GammaTable		*mygammaptr;	/* pointer to my gamma table */
	unsigned short	pip_reserved;	/* flag set if PIP reserved by driver call */
	/* PZ */
	unsigned short	zoom;
	short 			slot;			/* Slot and driver refNum of the Colorboard 108+ */
	short 			refNum;
	short 			currentRate;	/* The proportional value for scaling x/y pan rates  */
	short 			currentZoom;	/* Zoom state: 1 = 1X, 2 = 2X, 3 = 4X  */
	short 			fastSpeed;		/* Fast multiplier for the pan rate  */
	short 			slowSpeed;		/* Slow multiplier for the pan rate  */
	short 			currentX;		/* The value in the pan register */
	short 			currentY;		/* Aggregate number from the two y-registers  */
	short 			xSize;			/* 1024 x 768, 800 x 600, 680 x 480 */
	short 			ySize;
	short 			theMode;		/* The pixel depth: 0 = 1 bit, 1 = 2 bit, 2 = 4 bit, 3 = 8 bit */
	short 			border;			/* The border constant which defines the panRect */
	Rect 			theRect;		/* The rect of our GDevice */
	Rect 			panRect;		/* The border of the active panning area */
	Rect 			currentScreen;	/* The active screen rect  */
	Boolean 		enablePZ;		/* True if pan & zoom are enabled, false otherwise */
	Boolean 		zCenter;		/* True if screen centered, false if mouse centered zoom */
	Boolean 		enableVD;		/* True if the Extended DeskTop option is in effect, else false */
	short 			xResolution;	/* Holds the x-screen size if Extended DeskTop is enabled */
	short 			yResolution;	/* Holds the y-screen size if Extended DeskTop is enabled */
	unsigned long	base;			/* base address */
/*еееее Energy Star (((((*/
	char			sync_state;		/* 0 = enabled, 1 = h or v disabled, 2 = h and v disabled */
	_264family_data	save_timing;	/* for restoring timing after energy saving */
	fakeVBL			taskrec;		/* Time Manager task record to fake VBL interrupts while energy saving */
/*еееее Energy Star )))))*/
	short			desk_sRsrcId;
	short			mon_sRsrcId;
/* ????  unsigned short	hsize;		/* ???? used only by test window */
/* ????  unsigned short	vsize;		/* ???? used only by test window */
} mystorage, *mystoragePtr;
/* PZ */
/********************************************************************************************/
/* 
	void calcRects()
	
	Set up our fastSpeed & slowSpeed pan rectangles. Any mouse movement inside the
	panRect does NOT generate pan commands. Any mouse movement outside the panRect,
	but inside the currentScreen generates a slowSpeed pan command. Any mouse movement
	outside the currentScreen generates a fastSpeed pan command.
	Input:	msp			pointer to our globals			
	
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
	theTop.v = msp->currentY + msp->theRect.top;
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
	The Colorboard 24MTV pan (x) register (9-bit) is at: 0xFsFE6078. 
	The pan (y) register (9-bit) is at 0xFsFE607C. 
	Input:	x	The 'x' coordinate at the top left of the view screen.
			y	The 'y' coordinate at the top left of the view screen.
			msp     Auxiliary Device Control Entry pointer.
*/
void PanTo(x,y,msp)
short x,y;
mystoragePtr msp;
{
	register unsigned long devbase = 0;
	register unsigned long xBase;
	register unsigned long yBase;
	register short totalSpeed;
	unsigned char mmuMode;
	
	devbase  = devBase(msp->slot);
	xBase    = devbase | XCASTAP;
	yBase    = devbase | YPANTAP;
	totalSpeed = (msp->theMode == 4) ? 5-msp->theMode: 4-msp->theMode;
#asm
	MOVE	SR,-(SP)		; Save state
	MOVE.W	#$2200,SR		; Disable interrupts
#endasm
	mmuMode = 1;	/* 32 bit addressing mode */
	drSwapMMUMode(&mmuMode);
	*(long *)xBase = (x>>totalSpeed) & 0x01FF;
	*(long *)yBase = y & 0x001FF;
	drSwapMMUMode(&mmuMode);
#asm
	MOVE	(SP)+,SR		; Restore interrupts
#endasm
}
/************************************************************************************************/
/* 
  void Center(msp, direction)
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
	register unsigned long xBase;
	register unsigned long yBase;
	unsigned long base = 0;
	unsigned char mmuMode;
	mystoragePtr sp;
  
	base = devBase(msp->slot);
	xBase = base | XCASTAP;
	yBase = base | YPANTAP;
				
	tempX = ((long) msp->xResolution) >> (long) (msp->currentZoom-1);
	tempY = ((long) msp->yResolution) >> (long) (msp->currentZoom-1);
		
	xBounds = msp->xSize - tempX;
	yBounds = msp->ySize - tempY;
	
	tempX >>= 1;
	tempY >>= 1;
	if (msp->zCenter)
	{
		sp = (mystoragePtr)StripAddress((long)msp);
		mmuMode = 1;							/* 32 bit addressing mode */
		drSwapMMUMode(&mmuMode);
		sp->currentX = *(long *)xBase & 0x01FF;	/* Get our current x location */
		sp->currentX <<= (sp->theMode == 4) ? (5-sp->theMode) : (4-sp->theMode);  		/* Adjust x-direction for the pixel depth */
		sp->currentY = *(long *)yBase & 0x01FF;
		drSwapMMUMode(&mmuMode);
		
		if (direction)
			msp->currentX -= tempX >> 1;
		else
			msp->currentX += tempX;
			
		if (msp->currentX < 0)
			msp->currentX = 0;		/* Stay on the screen */
		if (msp->currentX > xBounds)
			msp->currentX = xBounds;
		
		if (direction)
			msp->currentY -= tempY >> 1;
		else
			msp->currentY += tempY;
			
		if (msp->currentY < 0)
			msp->currentY = 0;		/* Stay on the screen */      		
		if (msp->currentY > yBounds)
			msp->currentY = yBounds;	
	}
	else
	{
		GetMouse(&mouseLoc);
		LocalToGlobal(&mouseLoc);
		
		/* Adjust for multiple monitors */
		/* Check left/right */
		if ((mouseLoc.h < 0) || (mouseLoc.h > msp->xSize))
			mouseLoc.h -= msp->theRect.left;
		/* Check up/down */
		if ((mouseLoc.v < 0) || (mouseLoc.v > msp->ySize))
			mouseLoc.v -= msp->theRect.top;
		
		/* Do X coordinate */
		msp->currentX = mouseLoc.h - tempX;
		if (msp->currentX < 0)
			msp->currentX = 0;		/* Stay on the screen */
		if (msp->currentX > xBounds)
			msp->currentX = xBounds;
		
		/* Do Y coordinate */
		msp->currentY = mouseLoc.v - tempY;
		if (msp->currentY < 0)
			msp->currentY = 0;
		if (msp->currentY > yBounds)
			msp->currentY = yBounds;		
	}   
}
/********************************************************************************************/
/* 
	void ZoomIn()
	
	Zoom In.
	
	Input:	msp             Auxiliary Device Control Entry pointer.
	Uses:	xSize		(global) determines the "x" boundary
		slot		(global) determines the hardware addresses
				
	Assigns:	currentRate	(global) 1 << ((4 - msp->theMode) + currentZoom)
			currentZoom	(global) 1 = zoom 1X, 2 = zoom 2X, 3 = zoom 4X
			currentX	(global) the top left of our new viewing screen
			currentY	(global) the bottom right of new current viewing screen
	Calls:	PanTo()		Go to the new x,y of our current viewing screen
			PanY()		Adjust the panning rectangles correctly
			calcRects()	Both currentX & currentY have changed
	
*/
void ZoomIn(msp)
mystoragePtr msp;
{
	register unsigned long devbase = 0;
	register unsigned long xBase, yBase;
	register unsigned long pageMode;
	register unsigned long tempY;
	register mystoragePtr m = msp;
	unsigned long sUtilValue,  utilValue;
	short ctrl2Value;
	short pageValue = 0;
	unsigned char mmuMode=1;
	void PanY();
	
	devbase     = devBase(msp->slot);
	pageMode    = devbase | PAGE_CTL;
	xBase       = devbase | bt473_command;
	yBase       = devbase | BLOCK_ENABLE;
	drSwapMMUMode(&mmuMode);
	pageValue         = (short)(*(long *)pageMode); /* Save the existing page value */
	*(long *)pageMode = 0;  		  /* Set to page zero */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	sUtilValue  = (unsigned long)(*(char *)xBase);	/* bits 0-1 is the x-zoom */
	utilValue   = sUtilValue & 0x000000FC;
	drSwapMMUMode(&mmuMode);
	switch((short)((unsigned long)(sUtilValue & 3L)))
	{
	case 0x0000:
		utilValue  	|= 0x00000001;
		ctrl2Value  	 = 1;
		msp->currentRate = 1 << (msp->theMode == 4) ? (6 - msp->theMode) * 2 : (6 - msp->theMode);
		msp->currentZoom = 2;
		Center(msp, 0);
		break;
	case 0x0001:
		utilValue  	|= 0x00000002;
		ctrl2Value  	 = 2;
		msp->currentRate = 1 << (msp->theMode == 4) ? (7 - msp->theMode) * 2 : (7 - msp->theMode);
		msp->currentZoom = 3;
		Center(msp, 0);
		break;
	case 0x0002:
		return;
	}
	waitvblank(devbase);
	mmuMode=1;
	drSwapMMUMode(&mmuMode);
	*(char *)xBase  = (char)utilValue;
	tempY = *(long *)yBase;					/* Get the current value */
	tempY &= (long)0xFFFFFFF9;				/* Clear the zoom bits */
	tempY |= (long)(ctrl2Value << 1);		/* Set up the current zoom bits */
	*(long *)yBase = tempY;					/* Zoom */
	*(long *)pageMode = (long)(pageValue & 3);  	/* restore contents */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	drSwapMMUMode(&mmuMode);
	PanTo(msp->currentX,msp->currentY,msp);
	/* PanY(-1,0,msp); */
	calcRects(msp);
}
/********************************************************************************************/
/* 
	void ZoomOut()
	
	Zoom Out.
	
	Input:	msp             Auxiliary Device Control Entry pointer.
	Uses:	xSize		(global) determines the "x" boundary
			slot		(global) determines the hardware addresses
	Assigns:	currentRate	(global) 0 = zoom 1X, 1 << (7 - theMode) = zoom 2X
				currentZoom	(global) 1 = zoom 1X, 2 = zoom 2X
				currentX	(global) the top left of our new viewing screen
				currentY	(global) the bottom right of our new viewing screen
	Calls:	PanTo()		Go to the x,y of our new viewing screen
	        PanY()		Adjust the panning rectangles correctly
			calcRects()	Both currentX & currentY have changed				
*/
void ZoomOut(msp)
mystoragePtr msp;
{
	register unsigned long devbase = 0;
	register unsigned long xBase, yBase;
	register unsigned long pageMode;
	register unsigned long tempY;
	unsigned long sUtilValue;
	unsigned long utilValue;
	short ctrl2Value;
	short pageValue = 0;
	unsigned char mmuMode=1;
	void PanY();
	devbase     = devBase(msp->slot);
	pageMode    = devbase | PAGE_CTL;
	xBase       = devbase | bt473_command;
	yBase       = devbase | BLOCK_ENABLE;
	drSwapMMUMode(&mmuMode);
	pageValue         = (short)(*(long *)pageMode); /* Save the existing page value */
	*(long *)pageMode = 0;  		  	/* Set to page zero */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	sUtilValue  = (unsigned long)(*(char *)xBase);	/* Lo 2 bits is the x-zoom */
	utilValue   = sUtilValue & 0x000000FC;
	drSwapMMUMode(&mmuMode);
	switch((short)((unsigned long)(sUtilValue & 3L)))
	{
	case 0x0000:  
	case 0x0001:
		utilValue &= 0x0000FFFC;
		ctrl2Value = 0;
		msp->currentRate = (msp->enableVD) ? 1 << (6 - msp->theMode) : 0;
		msp->currentZoom = 1;
		Center(msp, 1);
		break;
			  
	case 0x0002:
		utilValue  	|= 0x00000001;
		ctrl2Value  	 = 1;
		msp->currentRate = 1 << (msp->theMode == 4) ? (7 - msp->theMode) * 2 : (7 - msp->theMode);
		msp->currentZoom = 2;
		Center(msp, 1);
		break;
	}
	waitvblank(devbase);
	mmuMode=1;
	drSwapMMUMode(&mmuMode);
	*(char *)xBase  = (char)utilValue;
	tempY = *(long *)yBase;				/* Get the current value */
	tempY &= (long)0xFFFFFFF9;			/* Clear the zoom bits */
	tempY |= (long)(ctrl2Value << 1);	/* Set up the current zoom bits */
	*(long *)yBase = tempY;				/* Zoom */
	*(long *)pageMode = (long)(pageValue & 3);  	/* restore contents */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	drSwapMMUMode(&mmuMode);
	PanTo(msp->currentX,msp->currentY,msp);
	/* PanY(-1,0,msp); */
	calcRects(msp);
}
/************************************************************************************************/
/* 
	void PanX(direction, speed, msp)
	
	Pan in the x-direction.
	The Colorboard 264 pan register (9-bit) is addressed as a longword at: 0xFsFE6078.
	
	Input:	direction		(-1) = pan left, 0 = pan right.
			speed			fastSpeed or slowSpeed
			msp			pointer to our private storage
				
	Uses: 	slot 			(panRecord) to compute the hardware addresses.
			currentZoom		(panRecord) return if we are at zoom = 1X.
			xSize			(panRecord) to calculate the boundary of our view screen.
	Assigns: 	currentX   	(panRecord) top left of our view screen rectangle.
	Calls:	calcRects()		currentX was changed.
*/
void PanX(direction, speed, msp)
short direction, speed;
mystoragePtr msp;
{
	register unsigned long devbase = 0;
	register unsigned long xBase;
	register short *xPtr;
	register short xBounds;
	register short adjustedSpeed;
	unsigned char mmuMode;
	devbase  = devBase(msp->slot);
	xBase    = devbase | XCASTAP;
	xPtr     = &msp->currentX;
	if (msp->enableVD)
		xBounds = (msp->currentZoom == 1) ? msp->xSize - msp->xResolution :
			                             msp->xSize - (msp->xResolution >> (msp->currentZoom - 1));
	else
		xBounds = msp->xSize - (msp->xSize >> (msp->currentZoom-1));
	adjustedSpeed = (msp->theMode == 4) ? 5-msp->theMode : 4-msp->theMode;
	mmuMode = 1;	/* 32 bit addressing mode */
	drSwapMMUMode(&mmuMode);
	if (direction)
	{
		if ((msp->currentX - (speed<<adjustedSpeed)) > 0)
		{
			*(long *)xBase -= speed;
			*xPtr -= speed<<adjustedSpeed;
		}
		else
		{
			*(long *)xBase = 0;
			*xPtr = 0;
		}
	}
	else if ((msp->currentX + (speed<<adjustedSpeed)) > xBounds)
	{
		*(long *)xBase = xBounds>>adjustedSpeed;
		*xPtr = xBounds;
	}
	else
	{
		*(long *)xBase += speed;
		*xPtr += speed<<adjustedSpeed;
	}
	drSwapMMUMode(&mmuMode);      
	calcRects(msp);
}
/************************************************************************/
/* 
	void PanY(direction, speed, msp)
	
	Pan in the y-direction.
	The Colorboard 264 pan (y) register (9-bits) is addressed as a longword at: 0xFsFE607C.
			
	Input:	direction		(-1) = pan down, 0 = pan up.
			speed			fastSpeed or slowSpeed
		msp			pointer to our private storage
	Uses: 	slot 			(panRecord) to compute the hardware addresses.
			currentRate		(panRecord) used to determine the pan rate of speed
			ySize			(panRecord) to calculate the boundary of our view screen.
			currentZoom		(panRecord) return if we are at zoom = 1X.
	Assigns: 	currentY   		(panRecord) bottom right of our view screen rectangle.
	Calls:	calcRects()		currentY was changed.
*/
void PanY(direction, speed, msp)
short direction, speed;
mystoragePtr msp;
{
	register unsigned long devbase = 0;
	register unsigned long yBase;
	register unsigned short videoStart;
	register short tempStart;
	register short yBounds;
	short yValue;
	unsigned char mmuMode;
	devbase = devBase(msp->slot);
	yBase   = (unsigned long )(devbase | YPANTAP);
	mmuMode = 1;	/* 32 bit addressing mode */
	drSwapMMUMode(&mmuMode);
	yValue  = (short)(*(long *)yBase);
	drSwapMMUMode(&mmuMode);
	videoStart  = yValue;
	switch(msp->currentZoom)
	{
		case 1:
				yBounds = msp->ySize;
				break;
		case 2:
				yBounds = msp->ySize >> 1;
				break;
		case 3:
				yBounds = (msp->ySize >> 2) + (msp->ySize >> 1);
	}
	if ((msp->enableVD) && (msp->yResolution == 480))
	switch(msp->currentZoom)
	{
		case 1 : yBounds = (msp->ySize - msp->yResolution) << 2;
			   break;
		case 2 : yBounds = 1056;
			   break;
		case 3 : yBounds = 864;
			   break;
	}
	if ((msp->ySize == 512) && (msp->yResolution == 480))
	switch(msp->currentZoom)
	{
		case 1 : yBounds = 0x440;		/* 512, yBounds = 1088 */
			   break;
		case 2 : yBounds = 0x310;		/* 512, yBounds = 784 */
			   break;
		case 3 : yBounds = 0x25A;		/* 512, yBounds = 602 */
			   break;
	}
	
	tempStart =  (direction) ? tempStart = videoStart - (speed>>1) : videoStart + (speed>>1);
	if ( (tempStart > 0) && (tempStart < yBounds) ) videoStart = (unsigned short) tempStart;
	if (tempStart >= yBounds) videoStart = yBounds;
	else if (tempStart <= 0) videoStart = 0;
	mmuMode = 1;	/* 32 bit addressing mode */
	drSwapMMUMode(&mmuMode);
	*(long *)yBase = (long)(videoStart & 0x1FF);
	drSwapMMUMode(&mmuMode);
	msp->currentY = videoStart * msp->currentRate;
	calcRects(msp);
}
/********************************************************************************************/
/*
 * SetPRAM()
 */
drSetPRAM(slot, PRAMPtr)
short					slot;
register SPRAMRecord	*PRAMPtr;		/* where to store the PRAM record */
{
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	/* set up params for slot manager call */
	SpPtr->spSlot = slot;	
	SpPtr->spExtDev = 0;	
	SpPtr->spsPointer = (char *) PRAMPtr;
	drSPutPRAMRec(SpPtr);
}
/*
 * SetPRAM5()
 */
short drSetPRAM5(slot, val)
short	slot;
short	val;
{
	SPRAMRecord				PRAMRec;				/* temp storage for pram record */
	register SPRAMRecord	*PRAMPtr = &PRAMRec;	/* temp storage for pram record */
	/*
	 * set up parameters for slot manager call
	 */
	drGetPRAM(slot, PRAMPtr);
	PRAMPtr->vendorUse5 = val;
	drSetPRAM(slot, PRAMPtr);
}
/*
 * SetPRAM6()
 */
short drSetPRAM6(slot, val)
short	slot;
short	val;
{
	SPRAMRecord				PRAMRec;				/* temp storage for pram record */
	register SPRAMRecord	*PRAMPtr = &PRAMRec;	/* temp storage for pram record */
	/*
	 * set up parameters for slot manager call
	 */
	drGetPRAM(slot, PRAMPtr);
	PRAMPtr->vendorUse6 = val;
	drSetPRAM(slot, PRAMPtr);
}
/********************************************************************************************/
/* Had to do this myself due to a bug in the Aztec C compiler (3.6B) */
/*
 * GetPRAM()
 */
drGetPRAM(slot, PRAMPtr)
short					slot;
register SPRAMRecord	*PRAMPtr;		/* where to store the PRAM record */
{
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	/* set up parameters for slot manager call */
	SpPtr->spSlot = slot;	
	SpPtr->spExtDev = 0;	
	SpPtr->spResult = (unsigned long) PRAMPtr;
	drSReadPRAMRec(SpPtr);
}
	
/*
 * GetPRAM5()
 */
short drGetPRAM5(slot)
short	slot;
{
	SPRAMRecord				PRAMRec;				/* temp storage for pram record */
	register SPRAMRecord	*PRAMPtr = &PRAMRec;	/* temp storage for pram record */
	/*
	 * set up parameters for slot manager call
	 */
	drGetPRAM(slot, PRAMPtr);
	return ((short) PRAMPtr->vendorUse5 & 0x00ff);
}
	
/*
 * GetPRAM6()
 */
short drGetPRAM6(slot)
short	slot;
{
	SPRAMRecord				PRAMRec;				/* temp storage for pram record */
	register SPRAMRecord	*PRAMPtr = &PRAMRec;	/* temp storage for pram record */
	/*
	 * set up parameters for slot manager call
	 */
	drGetPRAM(slot, PRAMPtr);
	return ((short) PRAMPtr->vendorUse6 & 0x00ff);
}
/*----------------------------------------------------*/
/* set_control_bit                                    */
/*----------------------------------------------------*/
set_control_bit(base, page, register_offset, bit, state)
long	base;
short	page;
long	register_offset;
short	bit;		/* 0-15 (16 Bits) */
short	state;		/* state is 0 for off, nonzero for on */
{
	unsigned short	*reg_ptr;
	long			*page_ctl_ptr;
	long			saved_page;
	char			mmu_mode;     /* MMU Mode (0=24-bit addressing 1=32-bit addressing) */
	
	reg_ptr = (unsigned short *)(base + register_offset);
	page_ctl_ptr = (long *)(base + PAGE_CTL);
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	
	saved_page = *page_ctl_ptr;
	*page_ctl_ptr = page;	/*  2RW	PAGE control 0 = DAC, 1 = ADC, 2 = PIP Reg1, 3 = PIP reg2 */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	if(state)
		*reg_ptr |= 0x0001 << bit;
	else
		*reg_ptr &= ~(0x0001 << bit);
	*page_ctl_ptr = saved_page;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	drSwapMMUMode(&mmu_mode);
}
/* Status checking functions */
/*------------------------------------------*/
/* get_PIP_register                         */
/*------------------------------------------*/
short
get_PIP_register(base, page, register_offset, validmask)
long	base;
short	page;
long	register_offset;
short	validmask;
{
	unsigned short	value;
	long			*page_ctl_ptr;
	long			saved_page;
	char			mmu_mode;     /* MMU Mode (0=24-bit addressing 1=32-bit addressing) */
	page_ctl_ptr = (long *)(base + PAGE_CTL);
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	saved_page = *page_ctl_ptr;
	*page_ctl_ptr = page;	/*  2RW	PAGE control 0 = DAC, 1 = ADC, 2 = PIP Reg1, 3 = PIP reg2 */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	value = *((unsigned short *)(base + register_offset));
	*page_ctl_ptr = saved_page;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	drSwapMMUMode(&mmu_mode);
	return value & validmask;
}
void set_reg(base, register_offset, val)
long	base;
long	register_offset;
short	val;
{
	unsigned long	*reg_ptr;
	char			mmu_mode;     /* MMU Mode (0=24-bit addressing 1=32-bit addressing) */
	
	reg_ptr = (unsigned long *)(base + register_offset);
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	
	*reg_ptr = val;
	drSwapMMUMode(&mmu_mode);
}
short get_reg(base, register_offset)
long	base;
long	register_offset;
{
	unsigned long	*reg_ptr;
	short			val;
	char			mmu_mode;     /* MMU Mode (0=24-bit addressing 1=32-bit addressing) */
	
	reg_ptr = (unsigned long *)(base + register_offset);
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	
	val = *reg_ptr;
	drSwapMMUMode(&mmu_mode);
	return val;
}
/*
 *	set_energy_save_state_264family
 */
void	set_energy_save_state_264family(new_state, msp)
unsigned char	new_state;
mystoragePtr	msp;
{
	unsigned long	temp;
	unsigned long	base;
	_264family_data	*save_timing;
	
	save_timing = &msp->save_timing;
	base = msp->base;
	
	switch(new_state)
	{
		case POWER_ON:
			switch(msp->sync_state)
			{
				case POWER_OFF:
/*myDebugStr("\PPOWER_OFF to POWER_ON");*/
					/* Restore original vertical timing */
					set_reg(base, V_END_SYNC, save_timing->ves);
					set_reg(base, V_TOTAL, save_timing->vtot);
					set_reg(base, V_START_BLANK, save_timing->vsb);
					/* Turn Interrupts on */
				case POWER_STANDBY:
/*myDebugStr("\PPOWER_STANDBY to POWER_ON");*/
					/* Restore original horizontal timing */
					set_reg(base, H_END_SYNC, save_timing->hes);
				case POWER_ON:
					break;
			}
			break;
		
		case POWER_STANDBY:
			switch(msp->sync_state)
			{
				case POWER_OFF:
/*myDebugStr("\PPOWER_OFF to POWER_STANDBY");*/
					/* Restore original vertical timing */
					set_reg(base, V_END_SYNC, save_timing->ves);
					set_reg(base, V_TOTAL, save_timing->vtot);
					set_reg(base, V_START_BLANK, save_timing->vsb);
					/* Turn Interrupts on */
					break;
				case POWER_ON:
/*myDebugStr("\PPOWER_ON to POWER_STANDBY");*/
					/* Save original horizontal timing */
					save_timing->hes = get_reg(base, H_END_SYNC);
					save_timing->htot = get_reg(base, H_TOTAL);
					/* Set new horizontal timing */
					set_reg(base, H_END_SYNC, save_timing->htot + 2);
				case POWER_STANDBY:
					break;
			}
			break;
		
		case POWER_OFF:
			switch(msp->sync_state)
			{
				case POWER_ON:
/*myDebugStr("\PPOWER_ON to POWER_OFF");*/
					/* Save original horizontal timing */
					save_timing->hes = get_reg(base, H_END_SYNC);
					save_timing->htot = get_reg(base, H_TOTAL);
					/* Set new horizontal timing */
					set_reg(base, H_END_SYNC, save_timing->htot + 2);
				case POWER_STANDBY:
/*myDebugStr("\PPOWER_STANDBY to POWER_OFF");*/
					/* Save original vertical timing */
					save_timing->ves = get_reg(base, V_END_SYNC);
					save_timing->vsb = get_reg(base, V_START_BLANK);
					save_timing->vtot = get_reg(base, V_TOTAL);
					/* Turn Interrupts off */
					/* Set new vertical timing */
					set_reg(base, V_END_SYNC, _264family_energy_saving_ves);
					set_reg(base, V_TOTAL, _264family_energy_saving_vtot);
					set_reg(base, V_START_BLANK, _264family_energy_saving_vsb);
				case POWER_OFF:
					break;
			}
			break;
	}
}
void	handle_VBL()
{
#asm
TMTaskSize	EQU	22
;		_Debugger
    	MOVEM.L A0-A5/D0-D7,-(SP)   ; Save registers
		
		MOVE.L	A1,-(SP)
		CLR.L	D0
		MOVE.W	TMTaskSize(A1),D0		; D0 is now: $0000000s, the slot number
		MOVEA.L	$D28,A0			; get the address of the VBL task manager
		JSR	(A0)				; go service the interrupt with slot number in D0
		MOVE.L	(SP)+,A0
		MOVEQ	#16,D0
		_PrimeTime
	    MOVEM.L (SP)+,A0-A5/D0-D7   ; Restore registers
#endasm
}
/*
 * dr_set_sizes() 
 */
void	dr_set_sizes(msp)
mystoragePtr	msp;
{
	short 			theID5;
	theID5 = drGetPRAM5(msp->slot) & 0x008F;		/* Get the monitor sResource */
	/* Check for the type of Extended DeskTop selected */
	switch(msp->desk_sRsrcId)
	{
	case 0x0080:
	case 0x0081:
	case 0x0082:
				msp->xSize = 640;
				msp->ySize = 480;
				break;
	case 0x0083:
	case 0x0084:
	case 0x0085:
				msp->xSize = 576;
				msp->ySize = 432;
			   	break;
	case 0x0086:
				msp->xSize = 1008;
				msp->ySize = 512;
			   	break;
	case 0x0087:
				msp->xSize = 2032;
				msp->ySize = 512;
			   	break;
	default:
				msp->xSize = 640;
				msp->ySize = 480;
				break;
	}
	switch(theID5)
	{
	case 0x0080:
	case 0x0081:
	case 0x0082:
				msp->xResolution = 640;
				msp->yResolution = 480;
				msp->screensize = 640;
				break;
	case 0x0083:
	case 0x0084:
	case 0x0085:
				msp->xResolution = 576;
				msp->yResolution = 432;
				msp->screensize = 576;
			   	break;
	}
}
/*
 * dr_load_timingtable()
 */
dr_load_timingtable(base, msp)
unsigned long	base;
mystoragePtr	msp;
{
	register unsigned long	*reg;
	register unsigned long	*table_ptr;
	register short			count;
	register char			flags;
	short					resNum;
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	long					saved_page;
	unsigned long			saved_interrupt_control;
	char					mmu_mode;
	
	resNum = msp->desk_sRsrcId;
	
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	
	saved_page = *((long *)(base + PAGE_CTL));
	flags = 0;
	
	if((resNum != 0x80) && (resNum != 0x83))
		flags |= BIT_INTERLACED;
	if((resNum == 0x83) || (resNum == 0x84) || (resNum == 0x85))
		flags |= BIT_UNDERSCAN;
	
	if((resNum == 0x82) || (resNum == 0x85))
		flags |= BIT_PAL;
	*(long *)(base + PAGE_CTL) = 3;		/* 2RW	DAC control 0 = DAC, 1 = ADC, 2 = counters, 3 = control */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	if(ISGENLOCK(base))
		flags |= BIT_GENLOCK;
	drSwapMMUMode(&mmu_mode);
	/*
	 * find out the table to load, depending on the flags
	 * BIT_INTERLACED	1000
	 * BIT_PAL			0100
	 * BIT_GENLOCK		0010
	 * BIT_UNDERSCAN	0001
	 */
	switch(flags) {
		case 0x0:			/* 0000 */
		case 0x2:			/* 0010 */
		case 0x4:			/* 0100 */
		case 0x6:			/* 0110 */
				resNum = ID_6x4;
				break;
	
		case 0x1:			/* 0001 */
		case 0x3:			/* 0011 */
		case 0x5:			/* 0101 */
		case 0x7:			/* 0111 */
				resNum = ID_5x4;
				break;
	
		case 0x8:			/*1000 */
				resNum = ID_6x4ntsc;
				break;
				
		case 0x9:			/*1001 */
				resNum = ID_5x4ntsc;
				break;
				
		case 0xa:			/*1010 */
				resNum = ID_6x4ntscGL;
				break;
				
		case 0xb:			/*1011 */
				resNum = ID_5x4ntscGL;
				break;
				
		case 0xc:			/*1100 */
				resNum = ID_6x4pal;
				break;
				
		case 0xd:			/*1101 */
				resNum = ID_5x4pal;
				break;
				
		case 0xe:			/*1110 */
				resNum = ID_6x4palGL;
				break;
				
		case 0xf:			/*1111 */
				resNum = ID_5x4palGL;
				break;
	}
	
	/* Find parameter resource */
	SpPtr->spSlot = (base >> 24) & 0x0F;
	SpPtr->spExtDev = 0;
	SpPtr->spID = sRsrcBoard;		/* Find Board Resource */
	drSRsrcInfo(SpPtr);
	SpPtr->spID = sTimingTableDir;	/* Find Resoulution Directory */
	drSFindStruct(SpPtr);
	SpPtr->spID = resNum;			/* Find Parameters */
	drSFindStruct(SpPtr);
	
	table_ptr = (unsigned long *)(SpPtr->spsPointer + 8 - 2); /* skip count and adjust byte lane for long access */
		
	/*
	 * now load the registers from the table
	 */
	 
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	
	saved_interrupt_control = *(long *)(base + NMRQ_DISABLE);
    *((unsigned long *)(base + OSC_SEL)) = *table_ptr++;
    *((unsigned long *)(base + EXT_SYNC_ENABLE)) = *table_ptr++;
	reg = (unsigned long *) (base + V_END_SYNC);
	count = 10;
	while(count--)
		*reg++ = *table_ptr++;
	*(long *)(base + XCASTAP)		= 0;		/*  9RW	X Zoom */
	*(long *)(base + YPANTAP)		= 0;		/*  9RW	Y Pan */
	/*
	 * set crystal select
	 */
	*(long *)(base + PAGE_CTL) = 3;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	if(flags & BIT_PAL)
		*(short *)(base + pip_control_3) |= 0x0020;
	else
		*(short *)(base + pip_control_3) &= 0xFFDF;
		
	/*
	 * if PAL set bit 5 of DAC command register to 0, else 1
	 */
	*(long *)(base + PAGE_CTL) = 0;		/* 2RW	DAC control 0 = DAC, 1 = ADC, 2 = counters, 3 = control */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	if((flags & BIT_INTERLACED) && (flags & BIT_PAL))
		*(unsigned char *)(base + bt473_command) &= 0xDF;
	else
		*(unsigned char *)(base + bt473_command) |= 0x20;
	/*
	 * restore page_ctl
	 */
	*((long *)(base + PAGE_CTL)) = saved_page;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	*(long *)(base + NMRQ_DISABLE) = saved_interrupt_control;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	*((unsigned long *)(base | NMRQ)) = 0;	/* Must be written once to start interrupts */
	drSwapMMUMode(&mmu_mode);
}
/*
 * dr_switch_mode()
 *
 *  Mode 80		640 X 480 67Hz
 *  Mode 81		640 X 480 NTSC
 *  Mode 82		640 X 480 PAL
 *  Mode 83		556 X 432 67Hz
 *  Mode 84		556 X 432 NTSC
 *  Mode 85		556 X 432 PAL
 *  Mode 86		1008 X 512 Extended Desktop
 *  Mode 87		2032 X 512 Extended Desktop
	
 */
void	dr_switch_mode(msp)
mystoragePtr	msp;
{
 	unsigned long			base;
	unsigned char			*mode_register;
	unsigned char			*dac_ctrl_reg;
	register unsigned long	*table_ptr;
	register short			i;
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	char					mmu_mode;
	unsigned short			mode;
/*	myDebugStr("\Pdr_switch_mode"); */
	/* Local copy of base address */
	base =  ((unsigned long)(msp->base) & (unsigned long)0xFF000000L);
	/* Make pointers to control registers */
	mode_register = (unsigned char *)(base + CMODE + 3);
	dac_ctrl_reg = (unsigned char *)(base + bt473_command);
	/* Get Mode while in 24 bit addressing mode */
	mode = msp->mode & 7;
	msp->theMode = mode;	/* for pz */
	if(mode == 4)
		mode = 7;
        /* Set Hardware */		
	graytable(base);		/* Set dacs to all gray to avoid flashes when changing bit depths */
	#asm
		MOVE	SR,-(SP)		; Save state
		MOVE.W	#$2200,SR		; Disable interrupts
	#endasm    
	/* Load timing if not extended desktop ID */
	if(msp->desk_sRsrcId < FirstExtended)
	{
		dr_load_timingtable(base, msp);
		msp->mon_sRsrcId = msp->desk_sRsrcId;
	}
	else
	{
/*		adjust_pitch(base, msp->desk_sRsrcId);*/
		;
	}
	/* Turn off PIP for less than 24 bit */
	if(mode < 7)
		set_control_bit(base, page3, pip_control_2, bit5, 0);
	/* Wait for vertical blanking time. */
	waitvblank(base);
	/* Set mode register */
	mmu_mode = true32b;	/* 32 bit mmu mode */
	drSwapMMUMode(&mmu_mode);
	if(mode == 7)
	{
		*(long *)(base + FAT_SLOT) = 1;  /*  1RW	0 = skinny, 1 = fat slot decoding */
	}
	else
	{
		*(long *)(base + FAT_SLOT) = 0;  /*  1RW	0 = skinny, 1 = fat slot decoding */
	}
	*mode_register = mode;  /* set bit mode */
	*(long *)(base + PAGE_CTL) = 0;	/*  2RW	PAGE control 0 = DAC, 1 = ADC, 2 = PIP Regs */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	{ 
		short dacValue = *dac_ctrl_reg;	/* ???? */
  
		dacValue &= 0xFFF7;  			/* Strip out the mode bits */
		dacValue |= (mode > 3 ? 0x00 : 0x08); 	/* OR in our new mode bits, preserving the contents */
		*dac_ctrl_reg = dacValue;		/* Set the new value in the DAC command register */
	}
	drSwapMMUMode(&mmu_mode);
	#asm
		MOVE	(SP)+,SR		; Restore interrupts
	#endasm
}
/****************************************************************************************/
/* OSErr myopen                                                                         */
/****************************************************************************************/
#define openErr	-23
OSErr myopen()
{
	register		mystoragePtr msp;	/* pointer to my private storage */
	AuxDCEPtr		dcep;			/* Auxiliary Device Control Entry pointer. */
	CntrlParam		*pbp;			/* Application-passed parameter block pointer. */
	THz				oldzone;		/* Previous heap zone */
	long			merror;			/* Memory error */
	SlotIntQElement *sqeptr;		/* Slot queue element pointer */
	GammaTable		*gammaptr;		/* Gamma Table Block pointer */
	long			i;				/* Loop counter */
	extern long		intrpthandler;	/* Define the interrupt handling routine as external; */
	unsigned char	mmu_mode;		/* MMU Mode (0=24-bit addressing 1=32-bit addressing) */
	unsigned long	base;			/* Slot base address */
	unsigned char	*mode_register, *dac_ctrl_reg;
	unsigned char	*dac_addr_reg, *dac_data_reg, *dac_mask_reg;
	extern unsigned char	applegamma[];
#asm
	MOVEM.L A0-A5/D0-D7,-(sp)   ; Save nearly all registers
#endasm
	/* Get pointers passed in A0, A1 by caller */
	save(&dcep,&pbp);          /* A0 -> pbp, A1 -> dcep */
	/* Get local copy of base address */
	base =  ((unsigned long)(dcep->dCtlDevBase) & 0xFF000000L);
	/* Reserve space in system heap for private storage */
	oldzone = GetZone();             /* Get current heap zone */
	SetZone(SystemZone());           /* Force memory operations to the System Heap. */
	/* Get a handle for our private storage. */
	/*  ResrvMem((long)sizeof(struct mystorage)); ???? */
	if (!(dcep->dCtlStorage = NewHandle((long)sizeof(struct mystorage))))
	{
		SetZone(oldzone);              /* Force memory operations to the original heap. */
#asm
	MOVEM.L (SP)+,A0-A5/D0-D7   ; Restore nearly all registers
#endasm
		return(openErr);                   /* Return that we couldn't open successfully. */
	}
	/* Lock private storage as long as driver is open */
	HLock(dcep->dCtlStorage);
	/* Dereference locked handle to private storage */
	msp = (mystoragePtr)(*(dcep->dCtlStorage));
		
	/* Install Interrupts */
	/* ------------------ */
	/* Get a pointer block for slot interrupt queque element */
	if (!(msp->myslotqeleptr = (SlotIntQElement *)NewPtr((long)sizeof(SlotIntQElement))))
	{
		SetZone(oldzone);              /* Force memory operations to the original heap. */
		/* Release system heap storage and return openErr */
		DisposHandle(dcep->dCtlStorage);
#asm
	MOVEM.L (SP)+,A0-A5/D0-D7   ; Restore nearly all registers
#endasm
		return(openErr);                   /* Return that we couldn't open successfully. */
	}
	SetZone(oldzone);                /* Force memory operations to the original heap. */
	/* Set up the fields of the slot queue element block. */
	sqeptr = msp->myslotqeleptr;
	sqeptr->sqLink = 0;
	sqeptr->sqType = 6;
	sqeptr->sqPrio = 0;
	sqeptr->sqAddr = (ProcPtr)(StripAddress((long)&intrpthandler));
	sqeptr->sqParm = dcep->dCtlDevBase;
	/* Install that slot queue element into the interrupt table. */
	if(drSIntInstall(sqeptr,dcep->dCtlSlot))
	{
		/* Release system heap storage and return openErr */
		DisposPtr(msp->myslotqeleptr);
		DisposHandle(dcep->dCtlStorage);
#asm
	MOVEM.L (SP)+,A0-A5/D0-D7	; Restore nearly all registers
#endasm
		return(openErr);		/* Return that we couldn't open successfully. */
	}
	/* -----------------------------End Install Interrupts------------------------------ */
	/* Allocate Gamma starage in system heap and Initialize Gamma table ???? do before interrupt stuff? */
	/* gamma table size = data size (256 or 768) + GFormulaData size (0) + header size (struct w/no data & formula)???? */
	/* Reserve space in system heap for gamma table */
	oldzone = GetZone();             /* Get current heap zone */
	SetZone(SystemZone());           /* Force memory operations to the System Heap. */
	/* Get a pointer block for maximum size gamma table. */
	if (!(msp->mygammaptr = (GammaTable *)NewPtr((long)(sizeof(struct GammaTable) + 768))))
	{
		SetZone(oldzone);              /* Force memory operations to the original heap. */
		/* Pull our interrupts out. */
		drSIntRemove(msp->myslotqeleptr,dcep->dCtlSlot);
		/* Release system heap storage and return openErr */
		DisposPtr(msp->myslotqeleptr);
		DisposHandle(dcep->dCtlStorage);
#asm
	MOVEM.L (SP)+,A0-A5/D0-D7   ; Restore nearly all registers
#endasm
		return(openErr);                   /* Return that we couldn't open successfully. */
	}
	SetZone(oldzone);                /* Force memory operations to the original heap. */
	/* Initialize Gamma Table for no correction */
	gammaptr = msp->mygammaptr;
	gammaptr->gVersion = 0;      /* Currently 0 for all cards */
	gammaptr->gType = DrHwRasterOps24MTV;    /* DrHwTFB = 0, DrHwRasterOps24MTV  */
	gammaptr->gFormulaSize = 0;  /* Formula size = 0, no formula data */
	gammaptr->gChanCnt = 1;      /* One table for all of r,g, & b, could be 3 for separate r,g, & b tables */
	gammaptr->gDataCnt = 256;    /* 256 entries per table */
	gammaptr->gDataWidth = 8;    /* 8 bits per entry */
	((char *)gammaptr) += sizeof(struct GammaTable);
#if noncorrected
	/* Values in initial Gamma Table are linear */
	for(i=0; i<256; i++)
		*((char *)gammaptr)++ = i;
#endif
	/* Values in initial Gamma Table are same as Apple's, for now */
	for(i=0; i<256; i++)
		*((char *)gammaptr)++ = applegamma[i];
	
	/* PZ */
	msp->base = base;
	msp->slot = dcep->dCtlSlot;
	msp->mon_sRsrcId = drGetPRAM5(msp->slot);
	msp->desk_sRsrcId = 0x00FF & dcep->dCtlSlotId; /* used by dr_set_sizes */
	
	dr_set_sizes(msp); /* uses msp->desk_sRsrcId */
	/* Initialize the pan and zoom globals */
	msp->zoom         =  1;		/* Zoom x1 													*/
	msp->currentRate  =  0;		/* No panning until zoomed or Virtual DeskTop is enabled 	*/
	msp->currentZoom  =  1;		/* No zooming until chosen by a key 				*/
	msp->currentX 	  =  0;		/* 0,0 								*/
	msp->currentY 	  =  0;
	msp->border 	  = 10;		/* Ten pixels difference between fast and slow panning 		*/
	msp->refNum	  = dcep->dCtlRefNum;
	msp->zCenter      = true;	/* Zoom to screen center is default.				*/
	msp->theMode	  = msp->mode & 0x0F;	/* Strip out the hi-bits of the pixel mode. 		*/
	msp->slowSpeed    =  1;		/* One pixel per pan for all modes.							*/
	msp->fastSpeed    =  2 << msp->theMode;	/* 8-bit = Sixteen pixels per pan.			*/
					/* 4-bit = Eight pixels per pan.			*/
					/* 2-bit = Four pixels per pan.				*/
					/* 1-bit = Two pixels per pan.				*/
	msp->enablePZ = false;		/* Pan & zoom not enabled 					*/
	msp->enableVD = false;		/* Enlarged panning not enabled 				*/
	
	/* Make pointers to control registers */
	mode_register = (unsigned char *)(base + CMODE + 3);
	dac_ctrl_reg = (unsigned char *)(base + bt473_command);
	dac_addr_reg = (unsigned char *)(base + bt473_p_addr);
	dac_data_reg = (unsigned char *)(base + bt473_palette);
	dac_mask_reg = (unsigned char *)(base + bt473_mask);
	/* Set our private values for mode and base address */
	msp->mode = 0x80;
	msp->newmode = 0;
	msp->screenbase = SCREEN_OFFSET + (unsigned long)(dcep->dCtlDevBase);
	/* Init time manager task pointer for fake vbls disabled */
	msp->taskrec.tmtask.tmAddr = nil;
	/* Set dacs to all gray to avoid flashes when changing bit depths */
	graytable(base);
	/* Set Hardware mode */
	mmu_mode = true32b;	/* 32 bit mmu mode */
	drSwapMMUMode(&mmu_mode);
	*mode_register = 0;  /* force 1 bit mode */
	*(long *)(base + PAGE_CTL) = 0;	/*  2RW	PAGE control 0 = DAC, 1 = ADC, 2 = PIP Regs */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	*dac_ctrl_reg |= 0x08;		/* Set the new value in the DAC command register */
	drSwapMMUMode(&mmu_mode);
	/* Gray the screen */
	grayscrn(msp->screenbase,0x80);
	
	/* Now make dither visible by loading the DACs. ?????*/
	mmu_mode = true32b;	/* 32 bit mmu mode */
	drSwapMMUMode(&mmu_mode);
	/* White */
	*dac_addr_reg = 0x00;   /* DAC address */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	*dac_data_reg = 0xFF;   /* DAC Red data */
	*dac_data_reg = 0xFF;   /* DAC Green data */
	*dac_data_reg = 0xFF;   /* DAC Blue data */
	/* Black */
	*dac_addr_reg = 0x80;   /* DAC address */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	*dac_data_reg = 0x00;   /* DAC Red data */
	*dac_data_reg = 0x00;   /* DAC Green data */
	*dac_data_reg = 0x00;   /* DAC Blue data */
	drSwapMMUMode(&mmu_mode);
	/* Turn on interrupts ???? */
	mmu_mode = true32b;	/* 32 bit addressing mode */
	drSwapMMUMode(&mmu_mode);
	*((unsigned long *)(base | NMRQ_DISABLE)) = 0;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	*((unsigned long *)(base | NMRQ)) = 0;	/* Must be written once to start interrupts */
	drSwapMMUMode(&mmu_mode);
	/* Set flag to show interrupts enabled */
	msp->intflag = 1;
	/* Set Gray mapping off */
	msp->bwmapping = 0;
	/* Clear PIP-reserved flag */
	msp->pip_reserved = false;
	/* Set initial energy saver state */
	msp->sync_state = (unsigned char)POWER_ON;
#asm
	MOVEM.L (SP)+,A0-A5/D0-D7   ; Restore nearly all registers
#endasm
	return(noErr);             /* Successful Open */
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of open^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/****************************************************************************************/
/* This routine is run whenever the driver is told to close. */
/****************************************************************************************/
OSErr myclose()
{
	mystorage	*msp;		/* pointer to my private storage */
	AuxDCEPtr dcep;			/* Auxiliary Device Control Entry pointer. */
	CntrlParam *pbp;		/* Application-passed parameter block pointer. */
	unsigned char mmu_mode;	/* MMU Mode (0=24-bit addressing 1=32-bit addressing) */
	unsigned long base;		/* Slot base address */
	register unsigned char *reg_ptr;
#asm
	MOVEM.L A0-A5/D0-D7,-(sp)   ; Save nearly all registers
#endasm
	save(&dcep,&pbp);      /* A0 -> pbp, A1 -> dcep */
	/* Get local copy of base address */
	base =  ((unsigned long)(dcep->dCtlDevBase) & 0xFF000000L);
	/* Dereference locked handle to private storage */
	msp = (struct mystorage *)*(dcep->dCtlStorage);
	/* Now make all video invisible by telling it to inhibit  all bits in the DACs. ?????*/
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	*(long *)(base + PAGE_CTL) = 0;	/*  2RW	PAGE control 0 = DAC, 1 = ADC, 2 = PIP Regs */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	reg_ptr = ((unsigned char *)(base + bt473_p_addr));   /* DAC Address Register */
	*reg_ptr = 0;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	reg_ptr = ((unsigned char *)(base + bt473_palette));   /* DAC Data Register */
	*reg_ptr = 0;   /* DAC Data r */
	*reg_ptr = 0;   /* DAC Data g */
	*reg_ptr = 0;   /* DAC Data b */
	reg_ptr = ((unsigned char *)(base + bt473_mask));   /* DAC read mask */
	*reg_ptr = 0;   /* DAC read mask off */
	drSwapMMUMode(&mmu_mode);
	/* Turn our interrupts off.  ????  47/43 for ntsc & pal */
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	*((unsigned long *)(base | NMRQ_DISABLE)) = 1;
	drSwapMMUMode(&mmu_mode);
	/* Pull our interrupts out. */
	drSIntRemove(msp->myslotqeleptr,dcep->dCtlSlot);
	/* Nuke our slot queue element block. */
	DisposPtr(msp->myslotqeleptr);
	/* Nuke our gamma table block. */
	DisposPtr(msp->mygammaptr);
	/* Nuke our variable storage block. */
	DisposHandle(dcep->dCtlStorage);
	
#asm
	MOVEM.L (SP)+,A0-A5/D0-D7   ; Restore nearly all registers
#endasm
	return(noErr);             /* Successful Close */
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of close^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*
         1         2         3         4         5         6         7         8
12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/
/****************************************************************************************/
/* Control calls
/*
/*   (0)  Reset
/*          csMode <- short
/*          csPage <- short
/*          csBaseAddr <- pointer
/*   (1)  Kill I/O
/*   (2)  SetMode
/*          csMode -> short
/*          csPage -> short
/*          csBaseAddr <- pointer
/*   (3)  SetEntries  -  error if direct mode
/*          csTable -> pointer
/*          csStart -> short
/*          csCount -> short
/*   (4)  SetGamma
/*          csTable -> pointer
/*   (5)  GrayScreen
/*          csPage -> pointer
/*   (6)  SetGray
/*          csMode -> short  (0 for color) (1 for gray)
/*   (7)  SetInterrupt
/*          csMode -> short  (0 for disable) (1 for enable)
/*   (8)  DirectSetEntries  -  error if indexed mode
/*          csTable -> pointer
/*          csStart -> short
/*          csCount -> short
/*   (9)  SetDefaultMode
/*          csMode -> char
/*
/*   Entry:
/*      A0 - Parameter Block Pointer
/*      A1 - DCE Pointer
/*
/*   Exit
/*      D0 - Error Code
/*
/****************************************************************************************/
#define controlErr	-17
#define	QD32Trap	0xAB03
#define	Unimplemented	0xA89F
OSErr control()
{
	register mystoragePtr	msp;	/* pointer to my private storage */
	AuxDCEPtr		dcep;			/* Auxiliary Device Control Entry pointer. */
	CntrlParam		*pbp;			/* Application-passed parameter block pointer. */
	Ptr				paramptr;		/* Local copy of pointer to csParam */
	SlotIntQElement *sqeptr;		/* Slot queue element pointer */
	THz				oldzone;		/* Previous heap zone */
	OSErr			errorflag;		/* flag for bad control call */
	unsigned char	mmu_mode;		/* MMU Mode (0=24-bit addressing 1=32-bit addressing) */
	unsigned char	*mode_register, *dac_ctrl_reg;
	unsigned char	*dac_addr_reg, *dac_data_reg, *dac_mask_reg;
	unsigned short	mode;
	unsigned long	base;			/* Slot base address */
	short			temp1;
	short			temp2;
	short			source_width;
	short			source_height;
	GDHandle 		dev;
	OSErr 			error = noErr;
	zoomCtrlParam	*zp;     /* Application-passed zoom & pan parameter block pointer. 	*/
	panInfoParam	*pp;
	unsigned short	defStart;
#asm
	MOVEM.L A0-A5/D0-D7,-(sp)   ; Save nearly all registers
#endasm
	save(&dcep,&pbp);      /* A0 -> pbp, A1 -> dcep */
	/* Dereference locked handle to private storage */
	msp = (mystoragePtr)(*(dcep->dCtlStorage));
	/* Set up our pan-status block pointer      */
	zp  = (panCtrlParam *)pbp;
	pp  = (panInfoParam *)pbp;
	errorflag = 0;
	/* Local copy of pointer passed in csParam */
	paramptr = *((Ptr *)(pbp->csParam));
	
	/* Local copy of base address */
	base =  ((unsigned long)(dcep->dCtlDevBase) & 0xFF000000L);
	/* Make pointers to control registers */
	mode_register = (unsigned char *)(base + CMODE + 3);
	dac_ctrl_reg = (unsigned char *)(base + bt473_command);
	mmu_mode = true32b;	/* 32 bit mmu mode */
	drSwapMMUMode(&mmu_mode);
	*(long *)(base + PAGE_CTL) = 0;	/*????  2RW	PAGE control 0 = DAC, 1 = ADC, 2 = PIP Regs */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	drSwapMMUMode(&mmu_mode);
	dac_addr_reg = (unsigned char *)(base + bt473_p_addr);
	dac_data_reg = (unsigned char *)(base + bt473_palette);
	dac_mask_reg = (unsigned char *)(base + bt473_mask);
#asm
;	DC.W	$A9FF	; debugger trap
#endasm
	/* Switch on the type of the type of action we are to respond to or do. */
	switch(pbp->csCode)
	{
	case 0:         /* Reset the video card. (Init) */
		/* Set our private values for mode and base address */
		msp->mode = 0x80;
		msp->newmode = 0;
		msp->screenbase = SCREEN_OFFSET + (unsigned long)(dcep->dCtlDevBase);
		/* Set return values */
		((VDPgInfoPtr)paramptr)->csMode = 0x80;         /* Return that we're in 1-Bit mode. */
		((VDPgInfoPtr)paramptr)->csPage = 0;
		((VDPgInfoPtr)paramptr)->csBaseAddr = (Ptr)(msp->screenbase);
		/* Set dacs to all gray to avoid flashes when changing bit depths */
		graytable(base);
		/* turn off interrupts???? */
#asm
	MOVE	SR,-(SP)		; Save state
	MOVE.W	#$2200,SR		; Disable interrupts
#endasm
		/* Set Hardware mode */
		mmu_mode = true32b;	/* 32 bit mmu mode */
		drSwapMMUMode(&mmu_mode);
		*mode_register = 0;  /* force 1 bit mode */
		*(long *)(base + PAGE_CTL) = 3;	/*  2RW	PAGE control 0 = DAC, 1 = ADC, 2 = PIP Regs */
#asm
		NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		if(isrISPAL(base) && WASINTERLACED(base)) {		/* this macro needs page_ctl==3 */
			*(long *)(base + PAGE_CTL) = 0;	/* dont take this out of the condition */
#asm
		NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
			*dac_ctrl_reg = 0x18;
		}
		else {
			*(long *)(base + PAGE_CTL) = 0;	/* dont take this out of the condition */
#asm
			NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
			*dac_ctrl_reg = 0x38;
		}
		*((unsigned long *)(base | NMRQ_DISABLE)) = 0;
		/* PIP stuff ???? */
		drSwapMMUMode(&mmu_mode);
#asm
	MOVE	(SP)+,SR		; Restore interrupts
#endasm
		/* Gray the screen */
		grayscrn(msp->screenbase,0x80);
	
		/* Now make dither visible by loading the DACs. ?????*/
		mmu_mode = true32b;	/* 32 bit mmu mode */
		drSwapMMUMode(&mmu_mode);
		/* White */
		*dac_addr_reg = 0x00;   /* DAC address */
#asm
		NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		*dac_data_reg = 0xFF;   /* DAC Red data */
		*dac_data_reg = 0xFF;   /* DAC Green data */
		*dac_data_reg = 0xFF;   /* DAC Blue data */
		/* Black */
		*dac_addr_reg = 0x80;   /* DAC address */
#asm
		NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		*dac_data_reg = 0x00;   /* DAC Red data */
		*dac_data_reg = 0x00;   /* DAC Green data */
		*dac_data_reg = 0x00;   /* DAC Blue data */
		drSwapMMUMode(&mmu_mode);
		break;
	case 1:         /* Remove all pending I/O. (KillIO) */
		break;
	case 2:         /* Set the card's video mode. (SetMode) if set already just return the baseAddr */
		/* If set already do nothing */
		if(((VDPgInfoPtr)paramptr)->csMode == msp->mode)
		{
			((VDPgInfoPtr)paramptr)->csBaseAddr = (Ptr)(msp->screenbase);
			break;
		}
	
		/* Check for valid mode ???? 84 not valid if no JP present */
		if(((VDPgInfoPtr)paramptr)->csMode < 0x80 || ((VDPgInfoPtr)paramptr)->csMode > 0x84)
		{
			errorflag = controlErr;    /* Return that we couldn't do it. */
			break;
		}
		/* Set private storage */
		msp->mode = ((VDPgInfoPtr)paramptr)->csMode;
		msp->screenbase = SCREEN_OFFSET + (unsigned long)(dcep->dCtlDevBase);
		
		/* Set Hardware */
		/* Set dacs to all gray to avoid flashes when changing bit depths */
		graytable(base);
		/* Get Mode while in 24 bit addressing mode */
		mode = (((VDPgInfoPtr)paramptr)->csMode) & 7;
		
		msp->theMode = mode;
		if(mode == 4)
			mode = 7;
		/* Turn off PIP for less than 24 bit */
		if(mode < 7)
			set_control_bit(base, page3, pip_control_2, bit5, 0);
		/* Wait for vertical blanking time. */
		waitvblank(base);
		/* Set mode register */
		mmu_mode = true32b;	/* 32 bit mmu mode */
		drSwapMMUMode(&mmu_mode);
		if(mode == 7)
		{
			*(long *)(base + FAT_SLOT) = 1;  /*  1RW	0 = skinny, 1 = fat slot decoding */
		}
		else
		{
			*(long *)(base + FAT_SLOT) = 0;  /*  1RW	0 = skinny, 1 = fat slot decoding */
		}
		*mode_register = mode;  /* set bit mode */
		*(long *)(base + PAGE_CTL) = 0;	/*  2RW	PAGE control 0 = DAC, 1 = ADC, 2 = PIP Regs */
#asm
		NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		{ 
			short dacValue = *dac_ctrl_reg;	/* ???? */
	  
			dacValue &= 0xFFF7;  			/* Strip out the mode bits */
			dacValue |= (mode > 3 ? 0x00 : 0x08); 	/* OR in our new mode bits, preserving the contents */
			*dac_ctrl_reg = dacValue;		/* Set the new value in the DAC command register */
		}
		drSwapMMUMode(&mmu_mode);
	/* Return the base address */
		((VDPgInfoPtr)paramptr)->csBaseAddr = (Ptr)(msp->screenbase);
		break;
	case 3:         /* Change card's color lookup table(s). (SetEntries) */
		if(msp->mode == 0x84)	/* For 24 bit screen mode, SetEntries DAC load not allowed. Use DirectSetEntries. */
		{
			errorflag = controlErr;          /* No room, return that we couldn't do it. */
			break;
		}
		errorflag = setlut(((VDSetEntryPtr)paramptr)->csTable,((VDSetEntryPtr)paramptr)->csStart,
			               ((VDSetEntryPtr)paramptr)->csCount,dcep);
		break;
	case 4:         /* Change card's gamma table. (SetGamma) */
		errorflag = setgamma(((VDGamRecPtr)paramptr)->csGTable,dcep);
		/* Set ramp lut only if direct mode, no gamma error, and not switching modes ???? */
		/* If switching modes, a lut load now would flash and grayPage is sure to be called */
		if((msp->mode == 0x84) && !errorflag && !(msp->newmode))
		errorflag = setdirect(dcep);
		break;
	case 5:         /* Gray the video page with dithered gray. (GrayScreen) ???? use private storage mode and passed page ptr */
		grayscrn(msp->screenbase,msp->mode);
		msp->newmode = 0;	/* tell setgamma that direct ramps have been loaded */
		/* If 24 bit mode, set gamma corrected linear ramp in DACs */
		if(msp->mode == 0x84)	/* Set direct DAC load for 24 bit screen mode */
		{
			setdirect(dcep);
		}
		break;
	case 6:         /* Map color lookup table(s) to color or grayscale. (SetGray) */
		msp->bwmapping = ((VDPgInfoPtr)paramptr)->csMode & 0x0100;
		break;
	case 7:         /* Enable/Disable Interrupts.  (SetInterrupt) */
		/* Do nothing if request matches current state. */
		if(((VDPgInfoPtr)paramptr)->csMode != msp->intflag)
		{
			/* a change is requested */
			/* Get the slot queue element block pointer from private storage */
			sqeptr = msp->myslotqeleptr;
			if(((VDPgInfoPtr)paramptr)->csMode)
			{
				/* Set interrupts on */
				/* Turn on interrupts ????  47/43 for ntsc & pal ???? */
				mmu_mode = true32b;	/* 32 bit addressing mode */
				drSwapMMUMode(&mmu_mode);
				*((unsigned long *)(base + NMRQ_DISABLE)) = 0;
#asm
				NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
				*((unsigned long *)(base + NMRQ)) = 0;	/* Must be written once to start interrupts */
				drSwapMMUMode(&mmu_mode);
	
				/* Set flag to show interrupts enabled */
				msp->intflag = 1;
			}
			else
			{
				/* Set interrupts off */
				/* Turn our interrupts off.  ????  47/43 for ntsc & pal */
				mmu_mode = true32b;	/* 32 bit mode */
				drSwapMMUMode(&mmu_mode);
				*((unsigned long *)(base + NMRQ_DISABLE)) = 1;
				drSwapMMUMode(&mmu_mode);
		
				/* Set flag to show interrupts disabled */
				msp->intflag = 0;
			}
		}
		break;
	case 8:         /* Change card's color lookup table(s). (DirectSetEntries) */
		if(msp->mode != 0x84)	/* For indexed screen mode, DirectSetEntries DAC load not allowed. Use SetEntries. */
		{
			errorflag = controlErr;          /* No room, return that we couldn't do it. */
			break;
		}
		errorflag = setlut(((VDSetEntryPtr)paramptr)->csTable,((VDSetEntryPtr)paramptr)->csStart,
			               ((VDSetEntryPtr)paramptr)->csCount,dcep);
		break;
	/* PZ */
	case 9:         /* Set default mode (SetDefault)*/
		DBS_CONTROL("\PSetDefault");
		defStart = (unsigned char)((VDDefaultInfoPtr)paramptr)->csMode;
		if ((defStart < FirstResource) || (defStart > LastResource))
			defStart = FirstResource;
		drSetPRAM6(msp->slot,(unsigned short)((VDDefaultInfoPtr)paramptr)->csMode);
		
		if(defStart <= LastMonitor)
			drSetPRAM5(msp->slot,(unsigned short)((VDDefaultInfoPtr)paramptr)->csMode);
		break;
		
	case 10:         /* Switch Resolution and Bit Depth.  (SwitchMode) */
		DBS_CONTROL("\PSwitchMode");
		if(((0x008F & ((VDSwitchInfoPtr)paramptr)->csData) < FirstResource) ||
		   ((0x008F & ((VDSwitchInfoPtr)paramptr)->csData) > LastResource))
		{
			errorflag = controlErr;	/* Return that we couldn't do it. */
		}
		else if(((0x00FF & ((VDSwitchInfoPtr)paramptr)->csMode) < 0x80) ||
				((0x00FF & ((VDSwitchInfoPtr)paramptr)->csMode) > 0x84))
		{
			errorflag = controlErr;	/* Return that we couldn't do it. */
		}
		else
		{
			SpBlock	spdata;
			OSErr	iErr;
			
			/* Get new sResource and bit depth ids & Update AuxDCE */
			dcep->dCtlSlotId = 0x00FF & ((VDSwitchInfoPtr)paramptr)->csData;
			msp->mode = 0x00FF & ((VDSwitchInfoPtr)paramptr)->csMode;
			/* Disable old sResource */
			spdata.spSlot = msp->slot;
			spdata.spID = msp->desk_sRsrcId;	/* old ID */
			spdata.spExtDev = 0;
			spdata.spRefNum = 0;
			spdata.spReserved = 0;
			spdata.spIOReserved = 0;
/*				iErr = SRsrcInfo(&spdata);	/* get RefNum */
/*				spdata.spParamData = 1;		/* disable */
			spdata.spStackPtr = 1;		/* disable (old field name for spParamData) */
			iErr = drSetSRsrcState(&spdata);
			iErr = drSUpdateSRT(&spdata);
			msp->desk_sRsrcId = 0x00FF & dcep->dCtlSlotId;
			dr_set_sizes(msp); /* uses msp->desk_sRsrcId */
			/* Enable new sResource */
			spdata.spSlot = msp->slot;
			spdata.spID = msp->desk_sRsrcId;	/* new ID */
			spdata.spExtDev = 0;
/*				spdata.spParamData = 0;		/* enable */
			spdata.spStackPtr = 0;		/* enable (old field name for spParamData) */
			spdata.spReserved = 0;
			spdata.spIOReserved = 0;
			spdata.spRefNum = 0;
			iErr = drSetSRsrcState(&spdata);
			iErr = drSUpdateSRT(&spdata);
			/* Return Base address of Page 0 */
			((VDSwitchInfoPtr)paramptr)->csBaseAddr = (Ptr)(msp->screenbase);
			/* Switch the hardware */
			dr_switch_mode(msp);
		}
		break;
	case 11:         /* Enable/Disable Syncs.  (SetSync) */
		DBS_CONTROL("\PSetSync");
		#asm
			MOVE	SR,-(SP)		; Save state
			MOVE.W	#$2200,SR		; Disable interrupts
		#endasm    
		if(*((VDFlagPtr)paramptr) == POWER_ON)	/* Set energy save state (Power On); H and V syncs enabled */
		{
/*			myDebugStr("\PPOWER_ON"); */
			/* If fake VBLs are on, Stop them */
			if(msp->taskrec.tmtask.tmAddr != nil)
			{
				/* Kill fake VBLs */
				drRmvTime((QElemPtr)&(msp->taskrec));
				msp->taskrec.tmtask.tmAddr = nil;
			}
			/* Set sync hardware */
			set_energy_save_state_264family((unsigned char)POWER_ON, msp);
			/* If interrupt flag is on and interrupts are off, restart interrupts */
			if((msp->intflag != 0) && (msp->sync_state == POWER_OFF))
			{
				/* Turn on interrupts */
				mmu_mode = true32b;	/* 32 bit addressing mode */
				drSwapMMUMode(&mmu_mode);
				*((unsigned long *)(base + NMRQ_DISABLE)) = 0;
#asm
				NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
				*((unsigned long *)(base + NMRQ)) = 0;	/* Must be written once to start interrupts */
				drSwapMMUMode(&mmu_mode);
			}
			msp->sync_state = (unsigned char)POWER_ON;
		}
		else if(*((VDFlagPtr)paramptr) == POWER_OFF)	/* Set energy save state (Power Off); H and V sync disabled */
		{
/*			myDebugStr("\PPOWER_OFF"); */
			/* Turn our interrupts off. */
			mmu_mode = 1;	/* 32 bit mode */
			drSwapMMUMode(&mmu_mode);
			*((unsigned long *)(base + NMRQ_DISABLE)) = 1;
			drSwapMMUMode(&mmu_mode);
			/* Set sync hardware */
			set_energy_save_state_264family((unsigned char)POWER_OFF, msp);
			/* If fake VBLs are not already on, Start them only if interrupt flag is on */
			if((msp->taskrec.tmtask.tmAddr == nil) && (msp->intflag != 0))
			{
/*			myDebugStr("\PVBLs"); */
				/* Start fake VBLs */
				msp->taskrec.tmtask.tmAddr = (ProcPtr)StripAddress((Ptr)handle_VBL);
				msp->taskrec.tmtask.tmWakeUp = 0;
				msp->taskrec.tmtask.tmReserved = 0;
				msp->taskrec.slot = msp->slot;
				drInsTime((QElemPtr)StripAddress((Ptr)&(msp->taskrec)));
				drPrimeTime((QElemPtr)StripAddress((Ptr)&(msp->taskrec)), (long)16);
			}
			msp->sync_state = (unsigned char)POWER_OFF;
		}
		else	/* Set energy save state (Standby); H or V sync disabled */
		{
			/* If fake VBLs are on, Stop them */
			if(msp->taskrec.tmtask.tmAddr != nil)
			{
				/* Kill fake VBLs */
				drRmvTime((QElemPtr)&(msp->taskrec));
				msp->taskrec.tmtask.tmAddr = nil;
			}
			/* Set sync hardware */
			set_energy_save_state_264family((unsigned char)POWER_STANDBY, msp);
			/* If interrupt flag is on and interrupts are off, restart interrupts */
			if((msp->intflag != 0) && (msp->sync_state == POWER_OFF))
			{
				/* Turn on interrupts */
				mmu_mode = true32b;	/* 32 bit addressing mode */
				drSwapMMUMode(&mmu_mode);
				*((unsigned long *)(base + NMRQ_DISABLE)) = 0;
#asm
				NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
				*((unsigned long *)(base + NMRQ)) = 0;	/* Must be written once to start interrupts */
				drSwapMMUMode(&mmu_mode);
			}
			msp->sync_state = (unsigned char)POWER_STANDBY;
		}
		#asm
			MOVE	(SP)+,SR		; Restore interrupts
		#endasm
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
		         	short zp->csParam[1] = speed			
		zp = (zoomCtrlParam *)pbp;
		PanX(zp->csParam[0],zp->csParam[1], msp); */
		break;
		
	case 8195:	   /* Pan Y according to the paramblock sent:
			      	The paramBlock specifies:
			      	short zp->csParam[0] = direction
		         	short zp->csParam[1] = speed			
		zp = (zoomCtrlParam *)pbp;
		PanY(zp->csParam[0], zp->csParam[1], msp); */
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
		}	while(dev = (GDHandle)(*dev)->gdNextGD);
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
		    /**** this should be set at open and never changed
			msp->xResolution = 640;
		    msp->yResolution = 480;
			*/
		}
		break;
	case -1:		/* Goodbye condition. */
		myclose();	/* Clean up things before leaving. */
		break;
	default:		/* Illegal csCode. */
		errorflag = controlErr;	/* Return that we couldn't do it. */
		break;
	}
#asm
	MOVEM.L (SP)+,A0-A5/D0-D7   ; Restore nearly all registers
#endasm
	checkiodone(errorflag);
	return(errorflag);
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of control^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/****************************************************************************************/
/* Status calls
/*
/*   (0)  Error
/*   (1)  Error
/*   (2)  GetMode
/*          csMode <- short
/*          csPage <- short
/*          csBaseAddr <- pointer
/*   (3)  GetEntries  -  valid for indexed and direct
/*          csTable <-> pointer
/*          csStart -> short
/*          csCount -> short
/*   (4)  GetPages
/*          csMode -> short
/*          csPage <- short  (number of pages)
/*   (5)  GetBaseAddr
/*          csPage -> short
/*          csBaseAddr <- pointer
/*   (6)  GetGray
/*          csMode <- short  (0 for color) (1 for gray)
/*   (7)  GetInterrupt
/*          csMode >- short  (0 for disabled) (1 for enabled)
/*   (8)  GetGamma
/*          csTable <- pointer
/*   (9)  GetDefaultMode
/*          csMode -> char
/*
/*   Entry:
/*      A0 - Parameter Block Pointer
/*      A1 - DCE Pointer
/*
/*   Exit
/*      D0 - Error Code
/*
/****************************************************************************************/
#define statusErr	-18
OSErr status()
{
	register		mystoragePtr msp;	/* pointer to my private storage */
	AuxDCEPtr		dcep;		/* Auxiliary Device Control Entry pointer. */
	CntrlParam		*pbp;		/* Application-passed parameter block pointer. */
	Ptr				paramptr;		/* Local copy of pointer to csParam */
	OSErr			errorflag;	/* flag for bad control call */
	unsigned long	base;	/* Slot base address */
	short			temp1;
	short			temp2;
	zoomCtrlParam	*zp;
	panInfoParam	*pp;
	GDHandle		dev;
	unsigned short	defStart;		/* Default startup configuration */  
#asm
	MOVEM.L A0-A5/D0-D7,-(sp)   ; Save nearly all registers
#endasm
	save(&dcep,&pbp);      /* A0 -> pbp, A1 -> dcep */
/* PZ */
	msp = (mystoragePtr)(*(dcep->dCtlStorage));
	zp  = (panCtrlParam *)pbp; 		    /* Set up our pan-status block pointer      */
	pp  = (panInfoParam *)pbp;
	errorflag = 0;
	/* Local copy of pointer passed in csParam */
	paramptr = *((Ptr *)(pbp->csParam));
	
	/* Dereference locked handle to private storage */
	msp = (struct mystorage *)*(dcep->dCtlStorage);
	/* Local copy of base address */
	base =  ((unsigned long)(dcep->dCtlDevBase) & 0xFF000000L);
#asm
;	DC.W	$A9FF	; debugger trap
#endasm
	/* Switch on the type of the type of action we are to repond to or do. */
	switch(pbp->csCode)
	{
	case 2:   /* Get the card's video mode. (GetMode) */
		((VDPgInfoPtr)paramptr)->csMode = msp->mode;
		((VDPgInfoPtr)paramptr)->csPage = 0;
		((VDPgInfoPtr)paramptr)->csBaseAddr = (Ptr)(msp->screenbase);
		break;
	case 3:   /* Get values from card's color lookup table(s). (GetEntries) */
		errorflag = getlut(((VDSetEntryPtr)paramptr)->csTable,((VDSetEntryPtr)paramptr)->csStart,
		((VDSetEntryPtr)paramptr)->csCount,dcep);
		break;
	case 4:   /* Get the total number of video pages on the card. (GetPages) */
		((VDPgInfoPtr)paramptr)->csPage = 1;
		break;
	case 5:   /* Get base address of specified page in current mode. (GetBaseAddr) */
		((VDPgInfoPtr)paramptr)->csBaseAddr = (Ptr)(msp->screenbase);
		break;
	case 6:   /* Get mapping mode (color or grayscale) of color lookup table(s). (GetGray) */
		((VDPgInfoPtr)paramptr)->csMode = msp->bwmapping;
		break;
	case 7:   /* Get Interrupt enable state ???? */
		((VDPgInfoPtr)paramptr)->csMode = msp->intflag;
		break;
	case 8:   /* Get pointer to current gamma table ???? */
		((VDGamRecPtr)paramptr)->csGTable = msp->mygammaptr;
		break;
	/* PZ */
	case 9:   /* Get default mode */
		DBS_STATUS("\PGetDefaultMode");
		defStart = drGetPRAM6(msp->slot); /* Get the default startup mode */
		((VDDefaultInfoPtr)paramptr)->csMode = defStart;	/* Return the default */
		break;
	case 10:         /* Get Current Resolution and Bit Depth.  (GetCurrMode) */
		DBS_STATUS("\PGetCurrMode");
		((VDSwitchInfoPtr)paramptr)->csMode = (unsigned short)msp->mode;
		((VDSwitchInfoPtr)paramptr)->csData = (unsigned long)msp->desk_sRsrcId;
		((VDSwitchInfoPtr)paramptr)->csPage = (unsigned short)0;
		((VDSwitchInfoPtr)paramptr)->csBaseAddr = (Ptr)(msp->screenbase);
/*			((VDSwitchInfoPtr)paramptr)->csReserved = (unsigned long)0; */
		break;
		
	case 11:         /* (GetSync) */
			DBS_STATUS("\PGetSync");
		*((VDFlagPtr)paramptr) = msp->sync_state;
		break;
	case 12:         /* Get Connection info.  (GetConnection) */
		DBS_STATUS("\PGetConnection");
		((VDDisplayConnectInfoPtr)paramptr)->csDisplayType = (unsigned short)kUnknownConnect;	/*kFixedModeCRTConnect;	//kUnknownConnect;	//kMultiModeCRT2Connect; */
/*			((VDDisplayConnectInfoPtr)paramptr)->csConnectTagged = (unsigned short)0; */
		((VDDisplayConnectInfoPtr)paramptr)->csConnectFlags = (1<<kAllModesValid);	/*+(1<<kAllModesSafe)+(1<<kUncertainConnect);*/
/*			((VDDisplayConnectInfoPtr)paramptr)->csDisplayComponent = (unsigned long)0; */
/*			((VDDisplayConnectInfoPtr)paramptr)->csConnectReserved = (unsigned long)0; */
		break;
	case 13:         /* Get Mode Timing info.  (GetModeTiming) */
		DBS_STATUS("\PGetModeTiming");
#if 0
		errorflag = statusErr;
		break;
#else
		{
			unsigned long	resid;
			unsigned long	timing;
			unsigned long	flags;
			
			resid = ((VDTimingInfoPtr)paramptr)->csTimingMode & 0x8F;
			if(resid < FirstResource || resid > LastResource)
			{
				errorflag = statusErr;
				break;
			}
			switch((short)resid & 0x008F)
			{
				case 0x80:
					timing = timingApple13;	/* 640x480 67Hz */
					break;
				case 0x81:
					timing = timingAppleNTSC_FF;	/* 640x480 NTSC */
					break;
				case 0x82:
					timing = timingUnknown;			/*timingApplePAL_FF;		/* 640x480 PAL? (timingApplePAL_FF is 768x576) */
					break;
				case 0x83:
					timing = timingUnknown;			/*timingUnknown;			/* 556x432 67Hz underscan? */
					break;
				case 0x84:
					timing = timingUnknown;			/*timingAppleNTSC_ST;	/* 556 X 432 NTSC underscan? (timingAppleNTSC_ST is 512x384) */
					break;
				case 0x85:
					timing = timingUnknown;			/*timingApplePAL_ST;		/* 556 X 432 PAL underscan? (timingApplePAL_ST is 640x480) */
					break;
				case 0x86:
					timing = timingUnknown;			/* 1008 x 512 ext */
					break;
				case 0x87:
					timing = timingUnknown;			/* 2032 x 512 ext */
					break;
			}
/*			((VDTimingInfoPtr)paramptr)->csTimingReserved = ((unsigned long)0; */
			((VDTimingInfoPtr)paramptr)->csTimingFormat = (unsigned long)kDeclROMtables;
			((VDTimingInfoPtr)paramptr)->csTimingData = timing;
			/* all modes are valid */
			flags = (1<<kModeValid);
			/* underscan/overscan and extended are all safe */
			if((resid == msp->mon_sRsrcId) ||
				(resid == msp->mon_sRsrcId + 3) ||
				(resid + 3 == msp->mon_sRsrcId) ||
				(resid >= FirstExtended))
			{
				flags |= (1<<kModeSafe);
			}
			((VDTimingInfoPtr)paramptr)->csTimingFlags = flags;
		}
		break;
#endif
	/* Pan and Zoom status calls */
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
		}	while(dev = (GDHandle)(*dev)->gdNextGD);
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
		}	while(dev = (GDHandle)(*dev)->gdNextGD);
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
	default:
		errorflag = statusErr;
	}
#asm
	MOVEM.L (SP)+,A0-A5/D0-D7   ; Restore nearly all registers
#endasm
	checkiodone(errorflag);
	return(errorflag);
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of status^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*_______________________________________________________________________________________
	setgamma
_______________________________________________________________________________________*/
OSErr setgamma(thetable,dcep)
GammaTable *thetable;
AuxDCEPtr dcep;        /* Auxiliary Device Control Entry pointer. */
{
	mystorage	*msp;	/* pointer to my private storage */
	GammaTable	*gammaptr;
	Ptr		mynewptr;
	THz		oldzone;	/* Previous heap zone */
	short		i;
	
	/* Dereference locked handle to private storage */
	msp = (struct mystorage *)*(dcep->dCtlStorage);
	/* Get pointer to my gamma table */
	gammaptr = msp->mygammaptr;
	/* For nil or -1 set a default linear table */
	if(thetable == nil ||	thetable == -1)
	{
		/* Initialize Gamma Table for no correction */
		gammaptr->gVersion = 0;      /* Currently 0 for all cards */
		gammaptr->gType = DrHwRasterOps24MTV;    /* DrHwTFB = 0, DrHwRasterOps24MTV  */
		gammaptr->gFormulaSize = 0;  /* Formula size = 0, no formula data */
		gammaptr->gChanCnt = 1;      /* One table for all of r,g, & b, could be 3 for separate r,g, & b tables */
		gammaptr->gDataCnt = 256;    /* 256 entries per table */
		gammaptr->gDataWidth = 8;    /* 8 bits per entry */
		((char *)gammaptr) += sizeof(struct GammaTable);
			/* Values in initial Gamma Table are linear */
		for(i=0; i<256; i++)
			*((char *)gammaptr)++ = i;
		
		return(0);	/* Successful completion. */
	}
	/* Check thetable (the new table) and make sure it is the right type ???? */
	if(thetable->gVersion != 0 ||					/* Version must be 0 */
		(thetable->gType != 0 && thetable->gType != DrHwRasterOps24MTV) ||	/* Type must be Apple or RasterOps 24MTV */
		thetable->gFormulaSize != 0 ||				/* Formula size must be 0 ???? */
		(thetable->gChanCnt != 1 && thetable->gChanCnt != 3) ||	/* Must be 1 table for all or 3 separate RGB tables */
		thetable->gDataCnt != 256 ||				/* Must be 256 entries per table */
		thetable->gDataWidth != 8)					/* Entry size must be 8 bits */
	return(controlErr);
	
	/* Copy the table header ???? */
	gammaptr->gVersion     = thetable->gVersion;      /* Currently 0 for all cards */
	gammaptr->gType        = thetable->gType;         /* DrHwTFB = 0, DrHwRasterOpsCB264 = ???? */
	gammaptr->gFormulaSize = thetable->gFormulaSize;  /* Formula size = 0, no formula data */
	gammaptr->gChanCnt     = thetable->gChanCnt;      /* One table for all of r,g, & b, could be 3 for separate r,g, & b tables */
	gammaptr->gDataCnt     = thetable->gDataCnt;      /* 256 entries per table */
	gammaptr->gDataWidth   = thetable->gDataWidth;    /* 8 bits per entry */
	/* Copy the data */
	if(thetable->gChanCnt == 3)
	{
		((char *)gammaptr) += sizeof(struct GammaTable);
		((char *)thetable) += sizeof(struct GammaTable);
		for(i=0; i<256*3; i++)
			*((char *)gammaptr)++ = *((char *)thetable)++;
	}
	else
	{
		((char *)gammaptr) += sizeof(struct GammaTable);
		((char *)thetable) += sizeof(struct GammaTable);
		for(i=0; i<256; i++)
			*((char *)gammaptr)++ = *((char *)thetable)++;
	}
	
	return(0);	/* Successful completion. */
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of setgamma^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*_______________________________________________________________________________________
	setdirect()
_______________________________________________________________________________________*/
OSErr setdirect(dcep)
AuxDCEPtr dcep;			/* Auxiliary Device Control Entry pointer. */
{
	mystorage		*msp;		/* pointer to my private storage */
	register short	i;
	unsigned char		*clutbackupbase;
	unsigned char		*clutbackup;
	unsigned char 	*base;
	register unsigned short *table;
	unsigned char		mmu_mode;		/* MMU Mode (0=24-bit addressing 1=32-bit addressing) */
	register unsigned long xrgb, *clutbufptr;
	GammaTable		*gammaptr;				/* Gamma Table block pointer */
	unsigned char		*gammaptr_r,*gammaptr_g,*gammaptr_b;	/* Gamma Table data pointers */
	unsigned long		index;
	long saved_page;
	
	/* Dereference locked handle to private storage */
	msp = (struct mystorage *)*(dcep->dCtlStorage);
	clutbufptr = (unsigned long *)((unsigned long)(&(msp->dacdata)));
	base = (unsigned char *)(((unsigned long)(dcep->dCtlDevBase)) & 0xFF000000L);
	clutbackupbase = (unsigned char *)((unsigned long)(&(msp->clut)));
	clutbackupbase = (unsigned char *)(StripAddress((unsigned long)clutbackupbase));  /* mask possible master pointer flag bits */
	gammaptr = (GammaTable *)(msp->mygammaptr);
	gammaptr = (GammaTable *)(StripAddress((unsigned long)gammaptr));  /* mask possible master pointer flag bits */
	/* get pointers to r,g,b gamma table or tables ???? */
	gammaptr_r = gammaptr_g = gammaptr_b = (unsigned char *)gammaptr + sizeof(struct GammaTable) + gammaptr->gFormulaSize;
	if(gammaptr->gChanCnt == 3) /* must be 1 or 3 */
	{
		gammaptr_g += gammaptr->gDataCnt;  /* Assuming gammaptr->gDataWidth = 8 */
		gammaptr_b += 2* gammaptr->gDataCnt;
	}
	
	for (i=0;i<256;i++)
	{
		clutbackup = clutbackupbase + i * 3;
		
		/* Regardless of mapping, write the real corrected???? values to our backup table. */
		clutbackup[0] = gammaptr_r[i];
		clutbackup[1] = gammaptr_g[i];
		clutbackup[2] = gammaptr_b[i];
	
		xrgb = ((unsigned long)clutbackup[0] << 16) |
		    ((unsigned long)clutbackup[1] << 8) |
		    ((unsigned long)clutbackup[2]);
	
		*clutbufptr++ = ((unsigned long)i << 24) | xrgb;  /* index -> 8 bits of high byte */
		table += 4;
	}
	/* Send buffered data to the DACs */
	clutbufptr = (unsigned long *)(StripAddress((unsigned long)(&(msp->dacdata))));
	/* Too big to send in one blanking period? ???? may not be necessary */
	/* turn off interrupts???? */
#asm
	MOVE	SR,-(SP)		; Save state
	MOVE.W	#$2200,SR		; Disable interrupts
#endasm
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	saved_page = *((long *)(base + PAGE_CTL));
	*((long *)(base + PAGE_CTL)) = 0;	/*  2RW	PAGE control 0 = DAC, 1 = ADC, 2 = PIP Regs */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	drSwapMMUMode(&mmu_mode);
#if 1
	/* Send entire buffer. */
	/* turn off interrupts???? */
	waitvblank(base);
	sendlut(base + bt473, clutbufptr, 256);
#else
	/* Send first half. */
	/* turn off interrupts???? */
	waitvblank(base);
	sendlut(base + bt473, clutbufptr, 128);
	clutbufptr +=128;
	/* Send remaining buffer. */
	waitvblank(base);
	sendlut(base + bt473, clutbufptr, 128);
#endif
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	*((long *)(base + PAGE_CTL)) = saved_page;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	drSwapMMUMode(&mmu_mode);
#asm
	MOVE	(SP)+,SR		; Restore interrupts
#endasm
	return(0);	/* Successful completion. */  
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of setdirect^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#if 0
/*_______________________________________________________________________________________
	set332()
_______________________________________________________________________________________*/
OSErr set332(state,dcep)
short		state;
AuxDCEPtr	dcep;			/* Auxiliary Device Control Entry pointer. */
{
	mystorage		*msp;		/* pointer to my private storage */
	register short	i, j;
	unsigned char		*clutbackupbase;
	unsigned char		*clutbackup;
	unsigned char 	*base;
	unsigned char		mmu_mode;		/* MMU Mode (0=24-bit addressing 1=32-bit addressing) */
	register unsigned long xrgb, *clutbufptr;
	GammaTable		*gammaptr;				/* Gamma Table block pointer */
	unsigned char		*gammaptr_r,*gammaptr_g,*gammaptr_b;	/* Gamma Table data pointers */
	unsigned long		index;
	long saved_page;
	
	/* Dereference locked handle to private storage */
	msp = (struct mystorage *)*(dcep->dCtlStorage);
	clutbufptr = (unsigned long *)((unsigned long)(&(msp->dacdata)));
	base = (unsigned char *)(((unsigned long)(dcep->dCtlDevBase)) & 0xFF000000L);
	clutbackupbase = (unsigned char *)((unsigned long)(&(msp->clut)));
	clutbackupbase = (unsigned char *)(StripAddress((unsigned long)clutbackupbase));  /* mask possible master pointer flag bits */
	gammaptr = (GammaTable *)(msp->mygammaptr);
	gammaptr = (GammaTable *)(StripAddress((unsigned long)gammaptr));  /* mask possible master pointer flag bits */
	/* get pointers to r,g,b gamma table or tables ???? */
	gammaptr_r = gammaptr_g = gammaptr_b = (unsigned char *)gammaptr + sizeof(struct GammaTable) + gammaptr->gFormulaSize;
	if(gammaptr->gChanCnt == 3) /* must be 1 or 3 */
	{
		gammaptr_g += gammaptr->gDataCnt;  /* Assuming gammaptr->gDataWidth = 8 */
		gammaptr_b += 2* gammaptr->gDataCnt;
	}
#if norestore  
	for (i=0;i<256;i++)
	{
		clutbackup = clutbackupbase + i * 3;
		
		/* Regardless of mapping, write the real corrected???? values to our backup table. */
		clutbackup[0] = gammaptr_r[(255*((i >> 5) & 7))/7];
		clutbackup[1] = gammaptr_g[(255*((i >> 2) & 7))/7];
		clutbackup[2] = gammaptr_b[(255*((i >> 0) & 3))/3];
	
		xrgb = ((unsigned long)clutbackup[0] << 16) |
		    ((unsigned long)clutbackup[1] << 8) |
		    ((unsigned long)clutbackup[2]);
	
		*clutbufptr++ = ((unsigned long)i << 24) | xrgb;  /* index -> 8 bits of high byte */
		table += 4;
	}
#endif
	if(state)
	{
		/* Set 3-3-2 Lookup Table */
		for (i=0;i<256;i++)
		{
			j = 255 - i;
			xrgb = ((unsigned long)gammaptr_r[(255*((j >> 5) & 7))/7] << 16) |
				 ((unsigned long)gammaptr_g[(255*((j >> 2) & 7))/7] << 8) |
				 ((unsigned long)gammaptr_b[(255*((j >> 0) & 3))/3]);
	
			*clutbufptr++ = ((unsigned long)i << 24) | xrgb;  /* index -> 8 bits of high byte */
		}
	}
	else
	{
		/* Restore the last Set Entries Table */
		for (i=0;i<256;i++)
		{
			clutbackup = clutbackupbase + i * 3;
		
			xrgb = ((unsigned long)clutbackup[0] << 16) |
			    ((unsigned long)clutbackup[1] << 8) |
			    ((unsigned long)clutbackup[2]);
	
			*clutbufptr++ = ((unsigned long)i << 24) | xrgb;  /* index -> 8 bits of high byte */
		}
	}
	
/* Send buffered data to the DACs */
	clutbufptr = (unsigned long *)(StripAddress((unsigned long)(&(msp->dacdata))));
	/* Too big to send in one blanking period? ???? may not be necessary */
	/* turn off interrupts???? */
#asm
	MOVE	SR,-(SP)		; Save state
	MOVE.W	#$2200,SR		; Disable interrupts
#endasm
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	saved_page = *((long *)(base + PAGE_CTL));
	*((long *)(base + PAGE_CTL)) = 0;	/*  2RW	PAGE control 0 = DAC, 1 = ADC, 2 = PIP Regs */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	drSwapMMUMode(&mmu_mode);
#if 1
	/* Send entire buffer. */
	/* turn off interrupts???? */
	waitvblank(base);
	sendlut(base + bt473, clutbufptr, 256);
#else
	/* Send first half. */
	/* turn off interrupts???? */
	waitvblank(base);
	sendlut(base + bt473, clutbufptr, 128);
	clutbufptr +=128;
	/* Send remaining buffer. */
	waitvblank(base);
	sendlut(base + bt473, clutbufptr, 128);
#endif
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	*((long *)(base + PAGE_CTL)) = saved_page;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	drSwapMMUMode(&mmu_mode);
#asm
	MOVE	(SP)+,SR		; Restore interrupts
#endasm
	return(0);	/* Successful completion. */  
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of set332^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#endif
/*_______________________________________________________________________________________
	setlut()
_______________________________________________________________________________________*/
OSErr setlut(thetable,start,count,dcep)
unsigned short *thetable;
short start,count;
AuxDCEPtr dcep;			/* Auxiliary Device Control Entry pointer. */
{
	mystorage		*msp;		/* pointer to my private storage */
	short			addr,mapmode,buffcount;
	register short	color,i;
	unsigned char		*clutbackupbase;
	unsigned char		*clutbackup;
	unsigned char 	*base;
	register unsigned short *table;
	unsigned char		mmu_mode;		/* MMU Mode (0=24-bit addressing 1=32-bit addressing) */
	register unsigned long xrgb, *clutbufptr;
	GammaTable		*gammaptr;				/* Gamma Table block pointer */
	unsigned char		*gammaptr_r,*gammaptr_g,*gammaptr_b;	/* Gamma Table data pointers */
	short			shift_amount;
	long saved_page;
	
	if(thetable == nil)	/* Must have  valid pointer to continue */
	return(controlErr);
	
	/* Dereference locked handle to private storage */
	msp = (struct mystorage *)*(dcep->dCtlStorage);
	clutbufptr = (unsigned long *)((unsigned long)(&(msp->dacdata)));
	base = (unsigned char *)(((unsigned long)(dcep->dCtlDevBase)) & (unsigned long)0xFF000000);
	/* Check for valid start and count range. */
	if (start != -1)
	{
	if (start < 0 || start + count > 255)
		return(controlErr);
	}
	table = thetable;
	
	/* ???? */
	if (start == -1)
	{
	for (i = 0; i <= count; i++)
	{
		addr = table[i*4];
		if (addr < 0 || addr > 255)
		return (controlErr);
	}
	}
	
	clutbackupbase = (unsigned char *)((unsigned long)(&(msp->clut)));
	clutbackupbase = (unsigned char *)(StripAddress((unsigned long)clutbackupbase));  /* mask possible master pointer flag bits */
	gammaptr = (GammaTable *)(msp->mygammaptr);
	gammaptr = (GammaTable *)(StripAddress((unsigned long)gammaptr));  /* mask possible master pointer flag bits */
	mapmode = ((msp->bwmapping) && (msp->mode != 0x84));       /* disable gray mapping for direct mode */
	table = (unsigned short *)(StripAddress((unsigned long)thetable));  /* mask possible master pointer flag bits */
	/* get pointers to r,g,b gamma table or tables */
	gammaptr_r = gammaptr_g = gammaptr_b = (unsigned char *)gammaptr + sizeof(struct GammaTable) + gammaptr->gFormulaSize;
	if(gammaptr->gChanCnt == 3) /* must be 1 or 3 */
	{
	gammaptr_g += gammaptr->gDataCnt;  /* Assuming gammaptr->gDataWidth = 8 */
	gammaptr_b += 2* gammaptr->gDataCnt;
	}
	
	switch(msp->mode)
	{
	case 0x80:	/* 1 bit mode */
		i = 1;
		shift_amount = 7+24;	/* 1 bit mode  -  indices *= $80 */
		break;
	case 0x81:	/* 2 bit mode */
		i = 3;
		shift_amount = 6+24;	/* 2 bit mode  -  indices *= $40 */
		break;
	case 0x82:	/* 4 bit mode */
		i = 15;
		shift_amount = 4+24;	/* 4 bit mode  -  indices *= $10 */
		break;
	case 0x83:	/* 8 bit mode */
	case 0x84:	/* 32 bit mode */
		i = 255;
		shift_amount = 0+24;	/* 8 bit mode  -  index *= 1 */
		break;			/* 24 bit mode is same as 8 bit, but only allowed from DirectSetEntries */
		/* This can't ever happen */
	default:	/* bad mode - refuse service */
		return(controlErr);
		break;
	}
	
	if (start != -1)
	{
		if (start < 0 || start + count > i)
			return(controlErr);
	}
	
	buffcount  = 0;
	for (i=0;i<=count;i++)
	{
		if (start == -1)
			addr = table[0] & (unsigned short)0x00FF;
		else
			addr = (start+i) & (unsigned short)0x00FF;
		clutbackup = clutbackupbase + addr * 3;
	
		if (mapmode)     /* Convert to grayscale. */
		{
			/* Convert to grayscale using the sum of 30% red, 60% green, 10% blue. */
			color = (((unsigned long)table[1] & 0xFF00)*3 +
					((unsigned long)table[2] & 0xFF00)*6 +
					((unsigned long)table[3] & 0xFF00))/10;
			if (color & 0x0080)
				color = 1+(color >> 8);   /* Round up if there's enough remainder. */
			else
				color >>= 8;
			color &= (unsigned short)0x00FF;
			clutbackup[0] = gammaptr_r[color];
			clutbackup[1] = gammaptr_g[color];
			clutbackup[2] = gammaptr_b[color];
		}
		else  /* Just send the bytes to the DAC's. */
		{
			clutbackup[0] = gammaptr_r[table[1]>>8];
			clutbackup[1] = gammaptr_g[table[2]>>8];
			clutbackup[2] = gammaptr_b[table[3]>>8];
		}
		xrgb = ((unsigned long)clutbackup[0] << 16)
				| ((unsigned long)clutbackup[1] << 8)
				| ((unsigned long)clutbackup[2]);      /* use gamma corrected value */
		*clutbufptr++ = ((long)addr << shift_amount) | xrgb;  /* index -> high bit of high byte */
		buffcount++;
		table += 4;
	}
#asm
;	DC.W	$A9FF	; debugger trap
#endasm
	/* Send buffered data to the DACs */
	clutbufptr = (unsigned long *)(StripAddress((unsigned long)(&(msp->dacdata))));
	/* turn off interrupts */
#asm
	MOVE	SR,-(SP)		; Save state
	MOVE.W	#$2200,SR		; Disable interrupts
#endasm
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	saved_page = *((long *)(base + PAGE_CTL));
	*((long *)(base + PAGE_CTL)) = 0;	/*  2RW	PAGE control 0 = DAC, 1 = ADC, 2 = PIP Regs */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	drSwapMMUMode(&mmu_mode);
#if 1
	/* Send entire buffer. */
	waitvblank(base);
	sendlut(base + bt473, clutbufptr, buffcount);
#else
	/* Send first half if necessary. */
	if(buffcount > 128) /* Too big to send in one blanking period? */
	{
		waitvblank(base);
		sendlut(base + bt473, clutbufptr, 128);
		buffcount -= 128;
		clutbufptr +=128;
	}
	/* Send remaining buffer. */
	waitvblank(base);
	sendlut(base + bt473, clutbufptr, buffcount);
#endif
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	*((long *)(base + PAGE_CTL)) = saved_page;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	drSwapMMUMode(&mmu_mode);
#asm
	MOVE	(SP)+,SR		; Restore interrupts
#endasm
	return(0);	/* Successful completion. */  
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of setlut^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*_______________________________________________________________________________________
	sendlut
_______________________________________________________________________________________*/
sendlut(base, clutbufptr, buffcount)
unsigned long *base, clutbufptr;
short buffcount;
{
#asm
	MOVEM.L	A0-A5/D0-D7,-(sp)	; Save nearly all registers
	MOVEQ   #1,D0
	DC.W    $A05D			; SwapMMUMode to 32 bit
	MOVE.B  D0,D3			; save previous mmu mode in D3
	MOVE.L	8(A6),A0		; Get DAC base address
	MOVE.L	12(A6),A1		; Get buffer address
	MOVE.W	16(A6),D0		; Get buffer count
	EXT.L	D0
	SUBQ.L	#1,D0			; adjust for DBF
lutloop	
	MOVE.B	(A1)+,(A0)		; index to address register
	MOVE.B	(A1)+,4(A0)		; red data to data register
	MOVE.B	(A1)+,4(A0)		; green data to data register
	MOVE.B	(A1)+,4(A0)		; blue data to data register
	DBF	D0,lutloop		; loop for count
	
;	MOVE.B	#$FF,8(A0)		; enable read mask register
	
	MOVE.B  D3,D0			; restore previous mmu mode
	DC.W    $A05D			; SwapMMUMode
	MOVEM.L	(SP)+,A0-A5/D0-D7	; Restore nearly all registers
#endasm
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of sendlut^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*____________________________________________________________________________________________
	waitvblank
____________________________________________________________________________________________*/
waitvblank(base)
unsigned long base;
{
	unsigned long *status_reg;
	unsigned char mmu_mode;     /* MMU Mode (0=24-bit addressing 1=32-bit addressing) */
	status_reg = (unsigned long *)(base + V_COUNT_END);
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	while((*status_reg & 1) == 1); /* wait for no blanking */
	while((*status_reg & 1) == 0);  /* wait for start of blanking */
	drSwapMMUMode(&mmu_mode);
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of waitvblank^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*____________________________________________________________________________________________
	getlut
____________________________________________________________________________________________*/
OSErr getlut(thetable,start,count,dcep)
unsigned short *thetable;
short start,count;
AuxDCEPtr dcep;        /* Auxiliary Device Control Entry pointer. */
{
	mystorage		*msp;		/* pointer to my private storage */
	register short color,addr,i;
	register unsigned char *clutbackup;
	register unsigned short *table;
	unsigned short end;
	
	/* Check for valid table address. */	
	if (thetable == nil)
		return (statusErr);
	
	/* Dereference locked handle to private storage */
	msp = (struct mystorage *)*(dcep->dCtlStorage);
	/* Check for valid start and count range. */	
	if (start < -1 || start > 255 || count < 0)
		return (statusErr);
	if (start != -1 && (start+count) > 255)
		return (statusErr);
	if (start == -1)
	{
		for (i = 0; i <= count; i++)
		{
			addr = table[i*4];
			if (addr < 0 || addr > 255)
				return (statusErr);
		}
	}
	clutbackup = (unsigned char *)(&(msp->clut));
	table = thetable;
	if (start == -1)
	{
		for (i=0;i<=count;i++)               /* Yank the values in order from our byte table (R,G,B). */
		{
			addr = table[i*4];
			color = clutbackup[addr*3];
			table[i*4+1] = ((color << 8) & 0xff00) + (color & 0x00ff);
			color = clutbackup[addr*3+1];
			table[i*4+2] = ((color << 8) & 0xff00) + (color & 0x00ff);
			color = clutbackup[addr*3+2];
			table[i*4+3] = ((color << 8) & 0xff00) + (color & 0x00ff);
		}
	}
	else
	{
		end = start+count;
		for (addr=start;addr<=end;addr++)  /* Yank the values in order from our byte table (R,G,B). */
		{
			color = clutbackup[addr*3];
			table[addr*4+1] = ((color << 8) & 0xff00) + (color & 0x00ff);
			color = clutbackup[addr*3+1];
			table[addr*4+2] = ((color << 8) & 0xff00) + (color & 0x00ff);
			color = clutbackup[addr*3+2];
			table[addr*4+3] = ((color << 8) & 0xff00) + (color & 0x00ff);
		}
	}
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of getlut^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*______________________________________________________________________________________________
 Board Interrupt Handler
 On entry:  A1 contains the slot base address
            D0-D3/A0-A3 have already been preserved
            (But *not* in AUX, so save them anyway!)
	d0 - scratch
	d1 - save return value
	d2 - saves Genlock connected (control/status 2 register) for 364
	                             (option bit) for 8S/24S	
	d3 - saved mmu mode
	d4 - saved PAGE_CTL mode
	d5 - saved cache control
	d6 - flags for current config (interlaced? genlock?)
	d7 - falgs for prev config (interlaced? genlock?)
______________________________________________________________________________________________*/
#asm
_intrpthandler
	MOVEM.L	A0-A5/D1-D7,-(sp) ; Save nearly all registers
	MOVEQ	#1,D0
	DC.W	$A05D				; SwapMMUMode
	MOVE.W	D0,D3				;save previous mmu mode
	MOVE.L	A1,D2				; get slot base address in D2
	ANDI.L	#$FF000000,D2		; 32 bit slot base address in D2
	MOVE.L	D2,A0				; stow slot base address in A0
	
	MOVE.L	(PAGE_CTL,A0),D4	; save PAGE_CTL mode
	MOVE.L	#3,(PAGE_CTL,A0)	; page 3
	NOP							; syncio
	
;еееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
; check to see if it is ours, if not, just return
;еееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
	MOVE.W	(AUDIO_CONTROL,A0),D0
	BTST	#3,D0
	BEQ		video_int			; if the bit is zero, do video interr
	
	MOVE.L	D4,(PAGE_CTL,A0)	; restore page_ctl	
	MOVE.W	D3,D0				; restore previous mmu mode
	DC.W	$A05D				; SwapMMUMode
	MOVEC	D5,CACR				; restore cache control
	MOVEM.L	(SP)+,A0-A5/D1-D7	; Restore nearly all registers
	MOVEQ	#0,D0				; we did not serve the interrupt
	RTS							; return to caller
;	
; set flags for current config and prev config then compare
;
video_int
	CLR.L	D6
	CLR.L	D7
isInt
;	MOVE.L	(MON_TYPE,A0),D0	; Ignore pin 4, make its state always = OSC_SEL state
;	AND.L	#$02,D0
;	BEQ		wasInt
;	OR.W	#1,D6
wasInt
	MOVE.L	(OSC_SEL,A0),D0
	AND.L	#$03,D0
	BEQ		isGenlock
	OR.W	#1,D7
	OR.W	#1,D6		; Ignore pin 4, make its state always = OSC_SEL state
isGenlock
	MOVE.W	(pip_status_2,A0),D0
	BTST	#6,D0
	BNE		wasGenlock
	OR.W	#2,D6
wasGenlock
	MOVE.L	(EXT_SYNC_ENABLE,A0),D0
	BTST	#0,D0
	BEQ		compare_config
	OR.W	#2,D7
compare_config
	CMP.W	D6,D7
	BEQ		nochange
;
;	if non-interlaced before and after, ignore
;
;	AND.W	#1,D6		; Ignoring pin 4, D6 = D7 always
	AND.W	#1,D7		; if currently noninterlaced, ignore change in genlock
;	OR.W	D6,D7
	BEQ		nochange
	
;	
; something has changed, call c routine to reload the timing table
;
	MOVEM.L	A0-A2/D0-D3,-(sp)	; Save nearly all registers
	MOVE.L	A0,-(SP)			; push SeBlock pointer
	JSR		_cInterrupt			; call our c routine
	LEA		4(SP),SP			; repair stack caused by c call
	MOVEM.L	(SP)+,A0-A2/D0-D3 	; Restore nearly all registers
nochange
	MOVE.L	D4,(PAGE_CTL,A0)	; restore page_ctl
	
	MOVE.L	#1,(NMRQ_CLR,A0)	; write to NMRQ clear register clear interrupts
	MOVE.W	D3,D0				; restore previous mmu mode
	DC.W	$A05D				; SwapMMUMode
	MOVE.L	A1,D0				; stow slot base address in D0
 								; D0 is currently: $Fs0xxxxx, we need: $0000000s
	ROL.L 	#8,D0				; D0 is now: $0xxxxxFs
	ANDI.L	#$F,D0				; D0 is now: $0000000s, the slot number
	MOVEA.L	$D28,A0				; get the address of the VBL task manager
	JSR		(A0)				; go service the interrupt with slot number in D0
	MOVEM.L	(SP)+,A0-A5/D1-D7	; Restore nearly all registers
	MOVEQ	#1,D0				; signal that the interrupt was serviced
	RTS							; return to caller
#endasm
cInterrupt(base)
unsigned long	base;
{
	register unsigned long	*reg;
	register unsigned long	*table_ptr;
	register short		count;
	register short		flags;
	short				resNum;
	SpBlock				SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock	*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	long				saved_page;
	char				mmu_mode;
	
#ifdef DEBUG
	myDebugStr("\PcInterrupt: enter");
	return;
#endif
	
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	
	saved_page = *((long *)(base + PAGE_CTL));
	
	flags = 0;
	
	if(WASINTERLACED(base))			/* changed from ISINTERLACED to ingnore bit 4 */
		flags |= BIT_INTERLACED;
	*(long *)(base + PAGE_CTL) = 3;		/* 2RW	DAC control 0 = DAC, 1 = ADC, 2 = counters, 3 = control */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	if(ISGENLOCK(base))
		flags |= BIT_GENLOCK;
	if(isrISPAL(base))
		flags |= BIT_PAL;
	if(isrISUNDERSCAN(base))
		flags |= BIT_UNDERSCAN;
	drSwapMMUMode(&mmu_mode);
	
	/*
	 * find out the table to load, depending on the flags
	 * BIT_INTERLACED	1000
	 * BIT_PAL			0100
	 * BIT_GENLOCK		0010
	 * BIT_UNDERSCAN	0001
	 */
	switch(flags) {
		case 0x0:			/* 0000 */
		case 0x2:			/* 0010 */
		case 0x4:			/* 0100 */
		case 0x6:			/* 0110 */
				resNum = ID_6x4;
				break;
	
		case 0x1:			/* 0001 */
		case 0x3:			/* 0011 */
		case 0x5:			/* 0101 */
		case 0x7:			/* 0111 */
				resNum = ID_5x4;
				break;
	
		case 0x8:			/*1000 */
				resNum = ID_6x4ntsc;
				break;
				
		case 0x9:			/*1001 */
				resNum = ID_5x4ntsc;
				break;
				
		case 0xa:			/*1010 */
				resNum = ID_6x4ntscGL;
				break;
				
		case 0xb:			/*1011 */
				resNum = ID_5x4ntscGL;
				break;
				
		case 0xc:			/*1100 */
				resNum = ID_6x4pal;
				break;
				
		case 0xd:			/*1101 */
				resNum = ID_5x4pal;
				break;
				
		case 0xe:			/*1110 */
				resNum = ID_6x4palGL;
				break;
				
		case 0xf:			/*1111 */
				resNum = ID_5x4palGL;
				break;
	}
	
	/* Find parameter resource */
	SpPtr->spSlot = (base >> 24) & 0x0F;
	SpPtr->spExtDev = 0;
	SpPtr->spID = sRsrcBoard;		/* Find Board Resource */
	drSRsrcInfo(SpPtr);
	SpPtr->spID = sTimingTableDir;	/* Find Resoulution Directory */
	drSFindStruct(SpPtr);
	SpPtr->spID = resNum;			/* Find Parameters */
	drSFindStruct(SpPtr);
	
	table_ptr = (unsigned long *)(SpPtr->spsPointer + 8 - 2); /* skip count and adjust byte lane for long access */
		
	/*
	 * now load the registers from the table
	 */
	 
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	
    *((unsigned long *)(base + OSC_SEL)) = *table_ptr++;
    *((unsigned long *)(base + EXT_SYNC_ENABLE)) = *table_ptr++;
	reg = (unsigned long *) (base + V_END_SYNC);
	count = 10;
	while(count--)
		*reg++ = *table_ptr++;
		
	/*
	 * if PAL set bit 5 of DAC command register to 0, else 1
	 */
	*(long *)(base + PAGE_CTL) = 0;		/* 2RW	DAC control 0 = DAC, 1 = ADC, 2 = counters, 3 = control */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	if((flags & BIT_INTERLACED) && (flags & BIT_PAL))
		*(unsigned char *)(base + bt473_command) &= ~0x20;
	else
		*(unsigned char *)(base + bt473_command) |= 0x20;
	/*
	 * restore page_ctl
	 */
	*((long *)(base + PAGE_CTL)) = saved_page;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	drSwapMMUMode(&mmu_mode);
}
#asm
_intrptend
;^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of Board Interrupt Handler^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
; ==================END OF DRIVER BLOCK=====================
    public endmydrvr
#endasm
	
	
