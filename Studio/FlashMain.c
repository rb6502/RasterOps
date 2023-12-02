/*
	File:		FlashMain.c
	Contains:	xxx put contents here xxx
	Written by:	Eric Kuo
	Copyright:	й 1994 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
		 <3>	 8/19/94	ek		Search for either studio or sonic
		 <2>	 7/26/94	ek		look for either Studio or Sonic boards
		 <1>	 1/27/94	ek		first checked in
*/
#include <globals.h>
#include "Std.h"
#include "LibStd.h"
#include "LibWind.h"
#include "LibSlot.h"
#include "FlashROM.h"
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						globals
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
short	gSlot;
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						prototypes
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
short	FindStudioOrSonic(void);
void	SelectSlot(short slot);
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						main routines
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// MyInit()
//
Boolean MyInit(void)
{
	gSlot = FindStudioOrSonic();
	if(gSlot == 0)
		gSlot = 9;
	SelectSlot(gSlot);
	
	return true;
}
//
// MyFini()
//
Boolean MyFini(void)
{
	return true;
}
//
// MyHit()
//
void MyHit(itemHit)
short	itemHit;
{
	short	iType;
	Handle	iHandle;
	Rect	iRect;
	short	val;
	Boolean	rc;
	
	switch(itemHit) {
		case ITEM_OK:
			rc = FlashIt(gSlot);
			if(rc == true)
				ShowModalDlg(DLOG_SUCCESS, 0, 0);
			else
				ShowModalDlg(DLOG_FAIL, 0, 0);
			break;
			
		case ITEM_CANCEL:
			gDone = true;
			break;
			
		case ITEM_POPUP:
			GetDItem(gDlgMain, itemHit, &iType, &iHandle, &iRect);
			val = GetCtlValue((ControlHandle) iHandle);
			gSlot = val - 1 + 9;
			break;
	}
}
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						util routines
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// FindStudioOrSonic()
//
short	FindStudioOrSonic()
{
	short	slot;
	
	for(slot = 9; slot <= 0x0e; slot++) {
		if(FindBoardType(slot) == BOARDTYPE_STUDIO)
			return slot;
	}
	
	return 0;
}
//
// SelectSlot()
//
void	SelectSlot(short slot)
{
	short	iType;
	Handle	iHandle;
	Rect	iRect;
	
	GetDItem(gDlgMain, ITEM_POPUP, &iType, &iHandle, &iRect);
	SetCtlValue((ControlHandle) iHandle,(short) (slot-9+1));
}
