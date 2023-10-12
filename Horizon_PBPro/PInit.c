/*
	File:		PInit.c
	Contains:	Primary Init code
	Written by:	Eric Kuo
	Copyright:	й 1994 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
		 <1>	 03/21/94	ek		converted from Aztec to MPW C
*/
#include "Rom.h"
void	cPInit(SEBlock *SeBlkPtr);
void	AdjustHW(void);
void	DetermineRes(short slot, short *monitorID, short *DesktopID);
void	InitDac(long base);
void	InitScrn(long base, short pram5);
void	PutLogo24(long base, short pram5);
void	SetupHW(short slot);
void	SetupSW(short slot);
void	InitNorm(long base);
void	endPInit(void);
/*
 * This is the C version of the primary init
 */
void	cPInit(SEBlock *SeBlkPtr)
{
	short	slot;						/* slot number */
	long	base;						/* address of our frame buffer */
	short	monitorID;
	short	DesktopID;
	short	pram5;
	short	pram6;
	short	pram1;
	char	*scrnInval=0x0C2D;
	short	res;
		
	/*
	 * set status to 1 (success)
	 * get slot number
	 * contruct 32 bit address of our frame buffer
	 * set up sp block slot number and ext device to be used in all slot manager calls
	 */
	SeBlkPtr->seStatus = 1;
	slot = SeBlkPtr->seSlot;
	base = 0xf0000000 | (((long) slot) << 24L);
	/*
	 * setup minimum software and hardware
	 */
	SetupSW(slot);
	SetupHW(slot);
		
	/*
	 * determine the resolution and
	 * handle the resources
	 */
	DetermineRes(slot, &monitorID, &DesktopID);
	DeleteExcept(slot, DesktopID);
	/*
	 * init the board
	 * draw color cube, logo, rom version
	 */
	if(!AUXRunning()) {
		InitScrn(base, monitorID);
		PutLogo24(base, monitorID);
		BTSHOW();
		WaitNms(2000);
	}
	else {	
		BTSHOW();
	}
	
	/*
	 * This is a fat slot only board
	 */
	if(!IsNewSlotMgr()) {
		SeBlkPtr->seStatus = 0x8001;
		return;
	}
	/*
	 * if newRes or board just pluged in, default to 8 bit mode
	 */
	pram1 = GetPRAM1(slot);
	pram5 = GetPRAM5(slot);
	pram6 = GetPRAM6(slot);
	if((pram5 != monitorID) || (pram6 != DesktopID) || (pram1 == 0)) {
		SetPRAM5(slot, monitorID);
		SetPRAM6(slot, DesktopID);
		if(DesktopID < 0x008c) {	// do it only for non-extended desktop
			pram1 = 0x83;
			SetPRAM1(slot, pram1);
			*scrnInval = 0;
		}
	}
	
	//еееее Display Manager (((((
	for(res = FirstResource; res <= LastResource; res++) {
		if(res != DesktopID)
			InsertResource(slot, res);
	}
	//еееее Display Manager )))))
}
//
// AdjustHW()
// 	Adjustable venus delay, merc delay, refresh interval
//
void AdjustHW()
{
	//
	// adjustable venus delay, merc delay, refresh interval
	//
	long	venusDelay = 3;
	long	mercDelay = 1;
	long	refreshInterval = 0x0098L;
	
	SetVenus(V_CONTROL4, GetVenus(V_CONTROL4) & ~0x0070);
	SetVenus(V_CONTROL4, GetVenus(V_CONTROL4) | (venusDelay << 4L));
	SetVenus(V_REFRESH_INTERVAL, refreshInterval);
	
	SetMerc(M_SystemCtl, (mercDelay << 8L) | 0x0054);
}
/*
 * DetermineRes()
 */
void DetermineRes(short slot, short *monitorID, short *DesktopID)
{
	short	eep5;
	short	eep6;
	short	newSense;				// new sense line
	short	res;					// new resID
	Boolean	needUpdate = false;		// need to update eeprom
	
	/*
	 * 1. Get monitor type and desktop size from EEProm
	 * 2. Adjust the number and check consistency
	 * 3. if there is an inconsistency, modify EEPROM
	 * 4. store the numbers in p-ram
	 *
	 * the EEPROM always stores 0x8?
	 * the p-ram can store 0x9? in pram6
	 */
	GetEEPROM56(slot, &eep5, &eep6);
	if(SenseChanged(slot, &newSense)) {
		SaveSense(slot, newSense);
		res = Sense2Res(newSense);
		if(res == 0)
			res = RES_6X4;
		if((eep5 != res) || (eep6 != res)) {
			eep5 = res;
			eep6 = res;
			SetEEPROM56(slot, eep5, eep6);
		}
	}
	if((eep5 < FirstMonitor) || (eep5 > LastNonInterlaced)) {
		eep5 = DefaultResource;
		needUpdate = true;
	}
	
	if((eep6 < FirstResource) || (eep6 > LastResource)) {
		eep6 = eep5;
		needUpdate = true;
	}
	if((eep6 <= LastMonitor) && (eep6 != eep5)) {
		eep6 = eep5;
		needUpdate = true;
	}
	
	if(needUpdate) {
		SetEEPROM56(slot, eep5, eep6);
	}
	
	*monitorID = eep5;
	*DesktopID = eep6;
}
/*
 * InitDac()
 */
void InitDac(long base)
{
#pragma unused(base);
	SetBtReg(BT9046_COMMAND_0, (clk_over_8 | unpack_msb | 5));
	SetBtReg(BT9046_COMMAND_1, 0);
	SetBtReg(BT9046_COMMAND_2, 0x00c0);
	
	SetBtReg(BT9046_RED_MASK, 0);
	SetBtReg(BT9046_GRN_MASK, 0);
	SetBtReg(BT9046_BLU_MASK, 0);
	SetBtReg(BT9046_TEST, 0);
	
	LinearBtPalette();
	LoadCMYKtable();
}
/*
 * InitScrn(base, pram5)
 *
 * 1. force fat slot mode on board
 * 2. set appropriate address mode XLI or XLTV
 * 3. init DAC
 * 4. load timming table
 * 5. enable
 */
void InitScrn(long base, short pram5)
{
	SetVenus(V_CONTROL1, 0x01);
	SetVenus(V_REFRESH_INTERVAL, 0x98);
	SetVenus(V_CONTROL1, 0x11);
	SetVenus(V_CONTROL2, 0x31);
	SetVenus(V_CONTROL3, 0x00);
	SetVenus(V_CONTROL4, 0x00);
	
	LoadVenusTbl(pram5);
	/*
	 * Turn on refresh, transfer enable, and sync
	 */
	SetVenus(V_CONTROL1, 0x91);
	SetVenus(V_CONTROL3, 0x72);
	SetVenus(V_CONTROL1, 0xB5);
	set_frequency(base, pram5, MCLK);
	InitNorm(base);
	InitDac(base);
	InitMerc();
	AdjustHW();
	{
		short	slot;
		
		slot = DEVSLOT(base);
		if(GetSogFlag(slot) == 0)
			ClearSog(slot);
	}
}
/*
 * PutLogo24()
 */
void PutLogo24(long base, short pram5)
{
	short			width;
	short			height;
	register short	xcenter;
	register short	ycenter;
	
	EraseScrnMerc(base, VRAM_START, VRAM_END, GETPITCH()*16);
	////EraseScrn(base, VRAM_START, VRAM_END);
	if((pram5 & 0x008f) == 0x0080) {		// 12x10 has only 16bit max
		return;
	}
	/*
	 * draw logo
	 */
	GetWH(pram5, &width, &height);
	xcenter = width / 2;
	ycenter = height / 2;
#if MAKING_HORI24
	Draw24(base, "Hori24  ", (short) xcenter, (short) ycenter, 0L);
#endif
#if MAKING_PBP
	Draw24(base, "Pbp     ", (short) xcenter, (short) ycenter, 0L);
#endif
	Draw24(base, "ver     ", (short) (width*93L/100L), (short) (height*4L/100L), (long) COLOR_GRAY_75);
}
//
// SetupHW()
//
void SetupHW(short slot)
{
#pragma unused(slot);
	SetupEEPROM();
}
//
// SetupSW()
//
void SetupSW(short slot)
{
	OpenVenus(slot);
	OpenMerc(slot);
	OpenBtShort(slot);
}
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
// 				Norm stuff
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
#define rgs64845s64_1	0x00f00100L		/* Norm chip #1 offset */
#define rgs64845s64_2	0x00f00200L		/* Norm chip #2 offset */
enum
{
	rgs64845s64_data = 0,
	rgs64845s64_barg = 1
};
/* norm internal addressing */
#define t11_t21			0x0			/* address pointer */
#define t31_t41			0x1			/* address pointer */
#define t12_t22			0x2			/* address pointer */
#define t32_t42			0x3			/* address pointer */
#define t13_t23			0x4			/* address pointer */
#define t33_t43			0x5			/* address pointer */
#define t14_t24			0x6			/* address pointer */
#define t34_t44			0x7			/* address pointer */
#define o1_o2			0x8			/* address pointer */
#define o3_o4			0x9			/* address pointer */
#define norm_control	0xa			/* address pointer */
#define xform_bnds		0xb			/* address pointer */
#define x4_in_bnds		0xc			/* address pointer */
#define address_ptr		0xd			/* address pointer */
#define axis_devision	0xe			/* address pointer */
#define mapping_const	0xf			/* address pointer */
/*
 * InitNorm()
 */
void InitNorm(long base)
{
	long	*norm1_base;
	long	*norm2_base;
	char	mode;
	norm1_base = (long*)(base + rgs64845s64_1);
	norm2_base = (long*)(base + rgs64845s64_2);
	mode = 1;
	SwapMMUMode(&mode);
	norm1_base[rgs64845s64_barg] = norm_control;
	norm1_base[rgs64845s64_data] = 0x000020e0;
	norm2_base[rgs64845s64_barg] = norm_control;
	norm2_base[rgs64845s64_data] = 0x000020e0;
	SwapMMUMode(&mode);
}
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
// 				end of prim init
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// endPInit()
//
void endPInit()
{
}
