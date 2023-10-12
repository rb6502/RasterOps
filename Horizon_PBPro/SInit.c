/*
	File:		SInit.c
	Contains:	secondary init routines
	Written by:	Eric Kuo
	Copyright:	й 1994 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
		 <1>	 3/21/94	ek		first checked in
*/
#include "Rom.h"
#include <DeskBus.h>
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//				prototypes
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
extern void	ShutDwnStartIIci(void);
extern void	ShutDwnStartIIcx(void);
void	cSInit(SEBlock *SeBlkPtr);
short	cmdoptsht(void);
void	cycleIt(short	slot);
short	poll(long base, short width, short height);
void	Set1Bit(long base);
void	showResolution(long base, short resNum, short width, short height, short sog);
void	ToggleIcon(long base, short width, short height);
void	endSInit();
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//				routines
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// cSInit()
//
void cSInit(SEBlock *SeBlkPtr)
{
	short	slot;					/* slot number */
	
	/*
	 * set status to 1 (success)
	 * get slot number
	 */
	SeBlkPtr->seStatus = 1;
	slot = SeBlkPtr->seSlot;
	OpenVenus(slot);
	OpenBtShort(slot);
	
	/*
	 * if cmd-sht-opt are pressed, cycle thru, otherwise just do the resource
	 * insertion
	 *
	 * cycleIt() WILL CAUSE A RESTART
	 *
	 * DONT DO THIS ON AUX
	 */
	if(!AUXRunning()) { 
		if(cmdoptsht()) {
			cycleIt(slot);
		}
	}
}
/*
 * cmdoptsht()
 *
 * check to see if cmd-opt-sht are pressed
 * cmd:8000, shift:0001, cap:0002, option:0004
 */
short cmdoptsht(void)
{
	KeyMap	km;
	
	ADBReInit();
	//WaitNTicks(15);	// this will do too
	GetKeys(&km);
	if((km[1] | 0xffff0002) == 0xffff8007)	/* dont know why some keys got stuck sometimes */
	//if((km[1] | 0x00000002) == 0x00008007)
		return true;
	else
		return false;
}
/*
 * cycleIt()
 */
void cycleIt(short	slot)
{
	register long	base;
	short			width;
	short			height;
	register short	resNum;
	
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
	base = DEVBASE(slot);
	Set1Bit(base);
	
	while(1) {
		for(resNum = FirstResource; resNum <= LastNonInterlaced; resNum++) {
			GetWH(resNum, &width, &height);
			showResolution(base, resNum, width, height, 0);
			if (poll(base, width, height)) {
				ClearSogFlag(slot);
				goto gotit;
			}	
			showResolution(base, resNum, width, height, 1);
			if (poll(base, width, height)) {
				SetSogFlag(slot);
				goto gotit;
			}
		}
	}
gotit:
	SetEEPROM56(slot, resNum, resNum);
	/*
	 * reboot, primary init will pick up from pram and use the right timing
	 */
	{
		SpBlock		SpBlk;					/* our sp block to make the slot manager call */
		SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	
		SVersion(SpPtr);
		if(SpPtr->spResult >= 2) {
			ShutDwnStartIIci();
		}
		else {
			ShutDwnStartIIcx();
		}
	}
}
/*
 * poll()
 * loop wait for key pressed or mouse down
 * quit after 5000 tries (about 5 seconds)
 */
short poll(long base, short width, short height)
{
	KeyMap			km;
	register short	count;
	
	count = 5 * 512;
	while(count--) {	
		GetKeys(&km);
		km[1] &= 0xffff7ff0;		/* mask off cmd-opt-sht and cap */
		if(km[0] || km[1] || km[2] || km[3] || Button()) {
			return true;
		}
		else {
			Wait1ms();
			if( (count & 0x01FF) == 0)		/* toggle every 512 miliseconds */
				ToggleIcon(base, width, height);
		}
	}
		
	return false;
}
/*
 * Set1Bit()
 */
void Set1Bit(long base)
{
#pragma unused(base);
	SetBtReg(BT9046_COMMAND_0, 0x40);		// set 1 bit
	
	SetOneColor(0, 0L);
	SetOneColor(1, (long) COLOR_WHITE);
}
/*
 * showResolution()
 */
void showResolution(long base, short resNum, short width, short height, short sog)
{
#if 1	
	register char	*name;
	short			xcenter;
	short			ycenter;
	
	if(sog)
		goto sog;
		
	EraseScrn(base, VRAM_START, VRAM_END);
	LoadVenusTbl(resNum);
	////Set1Bit(base);
	/*
	 * Turn on refresh, transfer enable, and sync
	 */
	SetVenus(V_CONTROL1, 0x91);
	SetVenus(V_CONTROL3, 0x72);
	SetVenus(V_CONTROL1, 0xB5);
	set_frequency(base, resNum, MCLK);
	ClearSog((short) DEVSLOT(base));
	switch(resNum) {
		case 0x0080:
				name = "s12x10  ";
				break;
		case 0x0081:
				name = "s11x8   ";
				break;
		case 0x0082:
				name = "s10x7_75";
				break;
		case 0x0083:
				name = "s10x7_60";
				break;
		case 0x0084:
				name = "s8x6    ";
				break;
		case 0x0085:
				name = "s6x4_67 ";
				break;
		case 0x0086:
				name = "s6x8    ";
				break;
	}
	
	xcenter = width/2;
	ycenter = height/2;
	DrawBm1(base, "panel   ", xcenter, ycenter);	
	DrawBm1(base, name, (short) (xcenter-256/2+84), (short) (ycenter-128/2+65));
	DrawBm1(base, "nosog   ", xcenter, (short) (ycenter+60));
	return;
	
sog:
	SetSog((short) DEVSLOT(base));
	DrawBm1(base, "sog     ", (short) (width/2), (short) (height/2+60));
#endif
}
/*
 * toggle the icons
 */
void ToggleIcon(long base, short width, short height)
{
	register char	*dest1;
	register char	*dest2;
	register short	i;
	register short	j;
	short			logox;
	short			logoy;
	long			rowBytes;
	char			mmu_mode;	
	/* rowBytes = 1152;	/* 24XL */
	/* rowBytes = 1152*4;	/* 32XL */
	rowBytes = GETPITCH()*16;	/* 32XLP */
	
	mmu_mode = 1;	/* 32 bit mode */
	SwapMMUMode(&mmu_mode);
  
	logox = width/2 - 256/2;
	logoy = height/2 - 128/2;
	
	dest1 = (char *) (base + VRAM_START);
	dest2 = (char *) (base + VRAM_START);
	
	dest1 += (rowBytes * (logoy + (88 - 39))) + (logox + 160L)/8;
	dest2 += (rowBytes * (logoy + (88 - 39))) + (logox + 200L)/8;
	
	for(i = 0; i < 32; i++) {
		for(j = 0; j < 32/8; j++) {
			*dest1 = ~(*dest1);
			*dest2 = ~(*dest2);
			dest1++;
			dest2++;
		}
		dest1 += (rowBytes - 32/8);
		dest2 += (rowBytes - 32/8);
	}
	
	SwapMMUMode(&mmu_mode);
}
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
// 				end of secondary init
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// endSInit()
//
void endSInit()
{
}
