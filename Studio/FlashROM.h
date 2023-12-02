/*
	File:		FlashROM.h
	Contains:	FlashROM main includes
	Written by:	Eric Kuo
	Copyright:	й 1994-1995 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
		 <4>	 7/24/95	MJ		Remove Bndl bit
		 <2>	 2/10/94	ek		change file type to 'MPS '
		 <1>	 1/27/94	ek		first checked in
*/
#ifndef __FLASHROM__
#define __FLASHROM__
#include "FlashEprom.h"
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						defs
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
#define ITEM_OK			1
#define ITEM_CANCEL		2
#define ITEM_POPUP		3
#define DLOG_SUCCESS	2001
#define DLOG_FAIL		2002
#define L_JUSTIFY	0
#define R_JUSTIFY	1
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						prototypes
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
Boolean	FlashIt(short slot);
#endif