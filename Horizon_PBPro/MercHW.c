/*
	File:		MercHW.c
	Contains:	Mercury hardware routines
	Written by:	Eric Kuo
	Copyright:	й 1994 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
	
		 <2>	 3/25/94	ek		new monitor sense code
		 <1>	 3/22/94	ek		first checked in
*/
#include "Rom.h"
//
// SetupHW()
//
void SetupHW(short slot)
{
	SetSwapBit(slot);
	SetupEEPROM();
}
/*
 * SetSwapBit()
 */
void SetSwapBit(short slot)
{
	long	*reg;
	char	mmu_mode;
	long	base;
	
	base = DEVBASE(slot);
	reg = (long *)(base + MERCURY + 0x4);
	mmu_mode = 1;
	SwapMMUMode(&mmu_mode);
	*reg = 0x04000004L;
	SwapMMUMode(&mmu_mode);
}
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//				Merccury operations
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
/*
 * BuildSrcPattern()
 *	32 bytes of 0xaa then 32 bytes of 0x55; repeate 4 times
 */
void	BuildSrcPattern(PARM_MONOFILL *p, long pat1, long pat2)
{
	register long	*dstPtr;
	register short	nLongs;
	register short	i, j;
	char			mmuMode;
	
	dstPtr = (long *) (p->base);
	nLongs = p->srcRowBytes/4;
	
	mmuMode = 1;
	SwapMMUMode(&mmuMode);
	for(i = 0; i < 4; i++) {
		for(j = 0; j < nLongs; j++) {
			*dstPtr++ = pat1;
		}
		for(j = 0; j < nLongs; j++) {
			*dstPtr++ = pat2;
		}
	}
	SwapMMUMode(&mmuMode);
}
/*
 * EraseScrn24HW()
 */
Boolean EraseScrn24HW(long base, short pram5, long color)
{
	PARM_MONOFILL	p;
	
	p.base = base;
	
	p.srcStart = 0;
	p.srcRowBytes = 32;
	
	p.vramStart = VRAMSTART;
	p.dstRowBytes = GETPITCH() * 16;
	p.depth = 32;
	p.r.left = p.r.top = 0;
	
	GetWH(pram5, &(p.r.right), &(p.r.bottom)); /* not used */
	{
		p.r.right = p.dstRowBytes / (p.depth/8);
		p.r.bottom = (long) (SCRN_VRAM - VRAMSTART) / (long) p.dstRowBytes;
	}
	p.fgd = color;
	BuildSrcPattern(&p, 0xffffffff, 0xffffffff);
	WaitTillDone(base);
	Monofill(&p);
	WaitTillDone(base);
	return true;
}
/*
 * GrayWipeHW()
 */
Boolean GrayWipeHW(MYSTORAGE *msp)
{
	PARM_MONOFILL	p;
	
	if(msp->mode < 0x83)
		return false;
	
	p.base = msp->base;
	
	p.srcStart = 0;
	p.srcRowBytes = 32;
	
	p.vramStart = msp->offset;
	p.dstRowBytes = GETPITCH() * 16;
	p.depth = 1 << (msp->mode & 0x0007);
	p.r.left = p.r.top = 0;
	{
		/*
		 * wipe the whole screen with black
		 */
		{
			p.r.right = p.dstRowBytes / (p.depth/8);
			p.r.bottom = (long) (SCRN_VRAM - VRAMSTART) / (long) p.dstRowBytes;
		}
		
		p.fgd = 0x00000000;
		p.bgd = 0x00000000;
		
		BuildSrcPattern(&p, 0xffffffffL, 0xffffffffL);
	
		WaitTillDone(msp->base);
		Monofill(&p);
	}
	
	/*
	 * now erase with gray
	 */
	GetWH(msp->pram6, &(p.r.right), &(p.r.bottom));
	
	p.fgd = 0x00ffffff;
	p.bgd = 0x00000000;
	if(p.depth <= 8) {
		BuildSrcPattern(&p, 0xaaaaaaaa, 0x55555555);
	}
	else {
		BuildSrcPattern(&p, 0x55555555, 0xaaaaaaaa);
	}
	WaitTillDone(msp->base);
	Monofill(&p);
	WaitTillDone(msp->base);
	return true;
}
/*
 * Monofill()
 */
void Monofill(PARM_MONOFILL *p)
{
	register long	base;
	long			dstStart;
	char			mmuMode;
	long			val;
	
	base = p->base;
	mmuMode = 1;
	SwapMMUMode(&mmuMode);
	*(long *) (base + MERCURY + M_S_Pitch) = p->srcRowBytes;
	*(long *) (base + MERCURY + M_D_Pitch) = p->dstRowBytes;
	*(long *) (base + MERCURY + M_Foregnd) = p->fgd;
	*(long *) (base + MERCURY + M_Backgnd) = p->bgd;
	
	*(long *) (base + MERCURY + M_S_Start) = p->srcStart;
	*(long *) (base + MERCURY + M_S_XEnd) = p->srcStart + p->srcRowBytes - 1;
	*(long *) (base + MERCURY + M_S_YEnd) = p->srcStart + (long) p->srcRowBytes * (long) (8);	/* why doesn't 7 work */
	dstStart = 	p->vramStart + (p->dstRowBytes * p->r.top) + (p->r.left * (p->depth/8));
	*(long *) (base + MERCURY + M_D_Start) = dstStart;
	*(long *) (base + MERCURY + M_D_XEnd) = dstStart + (long) (p->r.right - p->r.left) * (p->depth/8) - 1;
	*(long *) (base + MERCURY + M_D_YEnd) = dstStart + (long) (p->r.bottom - p->r.top - 1) * p->dstRowBytes;
	*(long *) (base + MERCURY + M_Offset) = 0;
	switch(p->depth) {
		case 16:
			val = 0x0100001b | 0x00040000;
			break;
		
		case 32:
			val = 0x0100001b | 0x00080000;
			break;
		default:				/* 8 bit */
			val = 0x0100001b;
			break;
	}
	*(long *) (base + MERCURY + M_BLTCtl) = val;
	SwapMMUMode(&mmuMode);
}
/*
 * WaitTillDone()
 */
void WaitTillDone(long base)
{
	char	mmuMode;
	long	val;
		
	mmuMode = 1;
	SwapMMUMode(&mmuMode);
loop:
	val = *(long *) (base + MERCURY + M_Status);
	if(val & (1L << 6))
		goto loop;	
	SwapMMUMode(&mmuMode);
}
