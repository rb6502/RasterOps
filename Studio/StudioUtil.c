/*
	File:		StudioUtil.c
	Contains:	xxx put contents here xxx
	Written by:	xxx put writers here xxx
	Copyright:	й 1994 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
		 <1>	 1/27/94	ek		first checked in
*/
#include "StudioHW.h"
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						prototypes
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
void	InitPsBases(PSTORAGE *ps, short slot);
void	InitHW(PSTORAGE *ps);
void	BangHardware(PSTORAGE *ps);
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						routines
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// InitPsBases()
//
void	InitPsBases(PSTORAGE *ps, short slot)
{
	ps->slot = slot;
	ps->base = DEVBASE(slot);
	ps->vramBase = ps->base + 0x00700000;
	ps->superBase = SUPERBASE(slot);
	ps->hubBase  = ps->superBase + kHubBaseAddr;
	ps->bicBase  = ps->superBase + kBicBaseAddr;
	ps->becBase  = ps->superBase + kBecBaseAddr;
	ps->romBase  = ps->superBase + 0x07c00000L;
	ps->romSize  = 128L*1024L;
	ps->mode = 2;
	
	ps->bpp = kBpp32;	// 32 bit mode
	
	ps->xRes = 640;
	ps->yRes = 480;
	ps->rowBytes = 1152*4;
}
//
// InitHW()
//
void	InitHW(PSTORAGE *ps)
{
	BicInit(ps);
	BangHardware(ps);
}
//
// BangHardware(): Set hub and bec registers
//	this can be called from two places: inits and dynamic resolution change
//	which: called from init or from driver
//
void
BangHardware(PSTORAGE *ps, short which)
{
	HubPtr	hub;
	BecPtr	bec;
	int bpp;
	char	mmuMode;
	
	//
	// get pointers to the major chips
	//
	hub = ps->hub;
	bec = ps->bec;
	
	mmuMode = 1;
	SwapMMUMode(&mmuMode);
	
	SetBecSOFTWARE_RESET(bec, 1);		// have to reset the BEC before making reg changes
	if(which == DO_INIT) {
		SetBec_Zoom(bec, 0);
		SetBecHPHASE(bec, 1);
		SetBecGENLOCK(bec, 0x04);
		SetBecBGS_ALPHA(bec, 0);								// may change for NTSC and PAL	
		SetBecBGWIDTH(bec, 0);								// may change for NTSC and PAL	
	
		//
		// control1
		//
		SetBecCONTROL1(bec, 0);	
		SetBec_BlankEn(bec, 1);	
		SetBec_se(bec, 1);	
		SetBec_alvs(bec, 1);	
		SetBec_alhs(bec, 1);	
		SetBec_alcs(bec, 1);	
		SetBec_ial(bec, 1);	
		Disable_HblInt(bec);
		Enable_LineInt(bec);
		Disable_VblInt(bec);
	
		//
		// control2
		//
		SetBec_CurUpdate(bec, 0);
		SetBec_wr3cm(bec, 0);
		SetBec_sog(bec, 1);
		SetBec_Ire0(bec, 1);
		SetBec_BigEndian(bec, 1);
		SetBec_crqe(bec, 1);
	#if DO_SONIC
		SetHub_MCFG0(hub, 1);
		SetHub_MCFG1(hub, 1);
		SetHub_SCFG0(hub, 1);
		SetHub_SCFG1(hub, 1);
		SetHub_VEN(hub, 1);
		SetHub_RFEN(hub, 1);
	#else
		SetHub_MCFG0(hub, 0);
		SetHub_MCFG1(hub, 0);
		SetHub_SCFG0(hub, 0);
		SetHub_SCFG1(hub, 0);
		SetHub_VEN(hub, 1);
		SetHub_RFEN(hub, 1);
	#endif
	}
	
	if(which == DO_INIT) {
		ps->rowBytes = CalcRowBytes(ps->pram5, ps->depth);
		SetHub_FB_Pitch(hub, ps->rowBytes/4);
		
		SetHub_FB_VZoom(hub, 0);
		SetHub_FB_VZoomStart(hub, 0);
		SetHub_FB_Start(hub, SCRNSTART);
	}
	else {
		ps->rowBytes = CalcRowBytes(ps->pram6, ps->depth);
		SetHub_FB_Pitch(hub, ps->rowBytes/4);
		SetHub_FB_Start(hub, SCRNSTART);		// play safe
	}
	
	bpp = Log2(ps->depth);	// bpp: 0-5
	SetBec_BppMode(bec, bpp);
	//
	// Now bang on the registers that are dependent on the particular mode we are in.
	// We will use the sVidRsrcID from pram to let us know which mode was choosen.
	//
	switch( ps->pram5 & 0x000f )
	{
		case 1:			// 11x8 ??Hz
			SetBec_SgenDivider(bec, SGEND4);
			SetBec_Scroll(bec, 0x2);
			SetBecPIO(bec, 0x19);
			SetBecPRG_INT(bec, 0x410);
			SetBecHTOTAL(bec, 182);
			SetBecHBSTART(bec, 174);
			SetBecHBEND(bec, 68);
			SetBecVTOTAL(bec, 1830);
			SetBecVBSTART(bec, 1830);
			SetBecVBEND(bec, 90);
			SetBecSYNC_WIDTH(bec, 1552);
			SetBecACTIVE_DELAY(bec, 63);
			break;
			
		case 2:			// 10x7 75Hz
			SetBec_SgenDivider(bec, SGEND4);
			SetBec_Scroll(bec, 0x2);
			SetBecPIO(bec, 0x17);
			SetBecPRG_INT(bec, 0x3c0);
			SetBecHTOTAL(bec, 166);
			SetBecHBSTART(bec, 158);
			SetBecHBEND(bec, 68);
			SetBecVTOTAL(bec, 1606);
			SetBecVBSTART(bec, 1606);
			SetBecVBEND(bec, 70);
			SetBecSYNC_WIDTH(bec, 1548);
			SetBecACTIVE_DELAY(bec, 63);
			break;
			
		case 3:			// 10x7 60Hz
			SetBec_SgenDivider(bec, SGEND2);
			SetBec_Scroll(bec, 0x2);
			SetBecPIO(bec, 0x16);
			SetBecPRG_INT(bec, 0x440);
			SetBecHTOTAL(bec, 328);
			SetBecHBSTART(bec, 296);
			SetBecHBEND(bec, 112);
			SetBecVTOTAL(bec, 1626);
			SetBecVBSTART(bec, 1626);
			SetBecVBEND(bec, 90);
			SetBecSYNC_WIDTH(bec, 1560);
			SetBecACTIVE_DELAY(bec, 103);
			break;
			
		case 4:			// 8x6
			SetBec_SgenDivider(bec, SGEND2);
			SetBec_Scroll(bec, 0x0);
			SetBecPIO(bec, 0x15);
			SetBecPRG_INT(bec, 0x300);
			SetBecHTOTAL(bec, 288);
			SetBecHBSTART(bec, 272);
			SetBecHBEND(bec, 144);
			SetBecVTOTAL(bec, 1334);
			SetBecVBSTART(bec, 1334);
			SetBecVBEND(bec, 86);
			SetBecSYNC_WIDTH(bec, 1552);
			SetBecACTIVE_DELAY(bec, 135);
			break;
			
		case 5:			// 6x4
			SetBec_SgenDivider(bec, SGEND1);
			SetBec_Scroll(bec, 0x0);
			SetBecPIO(bec, 0x13);
			SetBecPRG_INT(bec, 0x290);
			SetBecHTOTAL(bec, 432);
			SetBecHBSTART(bec, 368);
			SetBecHBEND(bec, 160);
			SetBecVTOTAL(bec, 1050);
			SetBecVBSTART(bec, 1050);
			SetBecVBEND(bec, 90);
			SetBecSYNC_WIDTH(bec, 1568);
			SetBecACTIVE_DELAY(bec, 142);
			break;
			
		case 6:			// 6x8
			SetBec_SgenDivider(bec, SGEND2);
			SetBec_Scroll(bec, 0x0);
			SetBecPIO(bec, 0x15);
			SetBecPRG_INT(bec, 0x410);
			SetBecHTOTAL(bec, 208);
			SetBecHBSTART(bec, 192);
			SetBecHBEND(bec, 80);
			SetBecVTOTAL(bec, 1836);
			SetBecVBSTART(bec, 1836);
			SetBecVBEND(bec, 96);
			SetBecSYNC_WIDTH(bec, 1556);
			SetBecACTIVE_DELAY(bec, 71);
			break;
		default:			// 11x8
			SetBec_SgenDivider(bec, SGEND4);
			SetBec_Scroll(bec, 0x2);
			SetBecPIO(bec, 0x19);
			SetBecPRG_INT(bec, 0x410);
			SetBecHTOTAL(bec, 182);
			SetBecHBSTART(bec, 174);
			SetBecHBEND(bec, 68);
			SetBecVTOTAL(bec, 1830);
			SetBecVBSTART(bec, 1830);
			SetBecVBEND(bec, 90);
			SetBecSYNC_WIDTH(bec, 1552);
			SetBecACTIVE_DELAY(bec, 63);
			break;
	}
	SetBecINTCLR(bec, 0x7);		// start over with a clean slate
	SetBecSOFTWARE_RESET(bec, 0);	// clear the BEC reset state when done banging regs
	//
	// update some ps params
	//
	
	SwapMMUMode(&mmuMode);
}
//
// BicInit()
//
void	BicInit(PSTORAGE *ps)
{
	BicPtr	theBic;
	long	*addr;
	char	mmuMode;
	
	theBic = ps->bic;
	addr = (long *) AddressOf_reset(theBic);
	mmuMode = 1;
	SwapMMUMode(&mmuMode);
	*addr = 0x1400;
	SwapMMUMode(&mmuMode);
}
