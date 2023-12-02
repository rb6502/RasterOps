/*
	File:		Thermo.h
	Contains:	xxx put contents here xxx
	Written by:	Eric Kuo
	Copyright:	© 1994 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
		 <2>	 2/10/94	ek		change file type to 'MPS '
		 <1>	 1/27/94	ek		first checked in
*/
#ifndef	_THERMO_
#define _THERMO_	1
#ifndef __THINK__
#include "mpw.h"
#endif
#if __cplusplus
extern "C" {void		CloseThermo(DialogPtr);};
extern "C" {DialogPtr	OpenThermo(short, Str255, short);};
extern "C" {void		UpdateThermo(DialogPtr, short, short);};
#else
void		CloseThermo(DialogPtr);
DialogPtr	OpenThermo(short, Str255, short);
void		UpdateThermo(DialogPtr, short, short);
#endif
#endif