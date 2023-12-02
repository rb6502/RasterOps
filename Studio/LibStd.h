/*
	File:		LibStd.h
	Contains:	xxx put contents here xxx
	Written by:	Eric Kuo
	Copyright:	й 1994 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
		 <2>	 2/10/94	ek		change file type to 'MPS '
		 <1>	 1/27/94	ek		first checked in
*/
#ifndef __LIBSTD__
#define __LIBSTD__
#ifndef __THINK__
#include "mpw.h"
#endif
#include <string.h>
#include <stdio.h>
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						defs
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
#define NIL			0L
#define SBarWidth	15
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						prototypes
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// LibStd.c
//
#if __cplusplus
extern "C" {Boolean		CommandPressed(void);};
extern "C" {void		GetEvent(EventRecord *);};
extern "C" {Boolean		IsPressed(unsigned short);};
extern "C" {Boolean		OptionPressed(void);};
extern "C" {pascal void OutlineButton( WindowPtr, short);};
extern "C" {unsigned short	RangedRdm(unsigned short, unsigned short);};
extern "C" {void		ShowWatch(void);};
extern "C" {void		Sleep(short);};
extern "C" {void		ToolBoxInit(void);};
extern "C" {void		WaitNms(short);};
#else
Boolean		CommandPressed(void);
void		GetEvent(EventRecord *);
Boolean		IsPressed(unsigned short);
Boolean		OptionPressed(void);
pascal void OutlineButton( WindowPtr, short);
unsigned short	RangedRdm(unsigned short, unsigned short);
void		ShowWatch(void);
void		Sleep(short);
void		ToolBoxInit(void);
void		WaitNms(short);
#endif
#endif
