/*
	File:		FlashROM.c
	Contains:	ROM flasher
	Written by:	Eric Kuo
	Copyright:	й 1994-1995 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
		<13>	  6/1/95	MJ		Replace Fittipaldi references with TARGA
		<12>	 5/26/95	ek		back to version <10> now
		<11>	 5/25/95	ek		revert back to <9>
		<10>	 5/18/95	ek		add alignment parameter to FlashRsrc()
		 <9>	 3/25/95	ek		fix thermometer
		 <8>	  3/1/95	MJ		Replace "Studio" with "Targa"
		 <6>	 2/25/94	ek		remove dsp load
		 <5>	 2/11/94	ek		delete support for Aztec generated rom
		 <4>	 2/10/94	ek		move dsp to block 3
		 <3>	 2/10/94	ek		Preserve resolution after loading rom
		 <2>	  2/8/94	ek		Modify to work with new MPW rom
		 <1>	 1/27/94	ek		first checked in
*/
#include <stdio.h>
#include <globals.h>
#include "LibSlot.h"
#include "Thermo.h"
#include "FlashROM.h"
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						defs
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
#define ALIGNCODE	0
#define ALIGNDATA	1
#define k32K		32768L
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						globals
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
DialogPtr	gThermo;
short		gTotalPages;
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						prototypes
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
Boolean	FlashIt(short slot);
Boolean CombineDSPrsrc(void);
void	CopyToBuf32k(Ptr srcPtr, char *bufPtr, long count, short align);
Boolean	FlashRsrc(long resType, short resNumb, short blockNumb, short slot, short align);
Boolean	WriteBlock(short slot, short blockNumb, char *bufPtr);
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						main routines
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// FlashIt()
//
Boolean FlashIt(short slot)
{
	short		nBlockCode;
	short		nBlockBitmap;
	Handle		h;
	long		count;
	Boolean		rc;
	//
	// calc number of blocks needed for code and bitmap
	//
	h = GetResource('DRVR', 0);
	if(h == 0)
		return false;
	count = SizeResource(h);
	if(count > k32K)
		return false;
	nBlockCode = 1;
	
	h = GetResource('DRVR', 1);
	if(h == 0)
		return false;
		
	count = SizeResource(h);
	nBlockBitmap= (count + 32767L) / k32K;
	
	gTotalPages = (nBlockCode+nBlockBitmap) * NPAGESPBLOCK;
	
	//
	// flash the config rom and bitmap
	//
	rc = FlashRsrc('DRVR', 0, 0, slot, ALIGNCODE);		// ConfigRom
	if(!rc) {
		return false;
	}
	rc = FlashRsrc('DRVR', 1, nBlockCode, slot, ALIGNDATA);		// BitMap
	if(!rc) {
		return false;
	}
	
	//
	// preserve the resolution of the board
	//
	if(GetBoardID(slot) == kTARGABDid) {
		char		page[PAGESIZE];	// pram at beginning of page
		short		i;
		
		for(i = 0; i < PAGESIZE; i++) {
			page[i] = 0;
		}
		GetPRAM(slot, (SPRAMRecord *)page);
		rc = SetEEPROM(slot, page);
	}
	
	return rc;
}
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						util routines
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// CopyToBuf32k()
//
void	CopyToBuf32k(Ptr srcPtr, char *bufPtr, long count, short align)
{
	long	zeroCount;
	
	zeroCount = k32K - count;
	
	if(align == ALIGNCODE) {
		while(zeroCount--)
			*bufPtr++ = 0;
		while(count--) 
			*bufPtr++ = *srcPtr++;
	}
	else {
		while(count--) 
			*bufPtr++ = *srcPtr++;
		while(zeroCount--)
			*bufPtr++ = 0;
	}
}
//
// FlashRsrc()
//	1. get the code resource
//	2. alloc 32k buffer and copy to it
//	3. write buffer to eeprom
//
Boolean	FlashRsrc(long resType, short resNumb, short blockNumb, short slot, short align)
{
	Handle	h;
	char	*buf32k;
	Boolean	rc;
	long	count;
	
	//
	// get the code resource
	//
	h = GetResource(resType, resNumb);
	if(h == 0)
		return false;
	HLock(h);
	
	//
	// alloc 32k buffer and copy to it
	//
	buf32k = NewPtrClear(k32K);
	if(buf32k == 0) {
		HUnlock(h);
		DisposHandle(h);
		return false;
	}
	
	//
	// copy buffer and write buffer to eeprom
	//
	count = SizeResource(h);
	if(count <= k32K) {
		CopyToBuf32k(*h, buf32k, count, align);
		rc = WriteBlock(slot, blockNumb, buf32k);
	}
	else {
		CopyToBuf32k(*h, buf32k, k32K, align);
		rc = WriteBlock(slot, blockNumb, buf32k);
		CopyToBuf32k(*h + k32K, buf32k, count-k32K, align);
		rc = WriteBlock(slot, blockNumb+1, buf32k);
	}
	
	//
	// clean up
	//
	HUnlock(h);
	ReleaseResource(h);
	DisposPtr(buf32k);
	return rc;
}
//
// WriteBlock()
//
Boolean	WriteBlock(short slot, short blockNumb, char *bufPtr)
{
	short			pageNumb;
	short			i;
	unsigned char	*message = "\pLoading TARGA ROM╔";
	Boolean			rc;
	
	if(blockNumb == 0)
		gThermo = OpenThermo(1902, message, 2);
	
	pageNumb = blockNumb * NPAGESPBLOCK;
	
	//
	// write all pages in the block
	//
	for(i = 0; i < NPAGESPBLOCK; i++) {
		UpdateThermo(gThermo, pageNumb*100/gTotalPages, 2);
		rc = WritePage(slot, pageNumb, bufPtr);
		if(rc == false) {
			CloseThermo(gThermo);
			return false;
		}
		
		pageNumb++;
		bufPtr += PAGESIZE;
	}
	if(pageNumb >= gTotalPages)
		CloseThermo(gThermo);
	
	return true;
}
