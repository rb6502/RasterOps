/*
	File:		Thermo.c
	Contains:	xxx put contents here xxx
	Written by:	xxx put writers here xxx
	Copyright:	© 1994 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
		 <3>	 2/10/94	ek		change file type to 'MPS '
		 <2>	 1/27/94	ek		nothing
		 <1>	 1/27/94	ek		first checked in
*/
#include "Thermo.h"
//
// globals
//
void		CloseThermo(DialogPtr);
DialogPtr	OpenThermo(short, Str255, short);
void		UpdateThermo(DialogPtr, short, short);
//
// CloseThermo()
//
void CloseThermo(dialog)
DialogPtr	dialog;
{
	DisposDialog( dialog );
}
//
// OpenThermo()
//
DialogPtr OpenThermo(resID, str, itemBar)
short	resID;
Str255	str;
short	itemBar;
{
	short	iType;
	Handle	iHandle;
	Rect	r;
	GrafPtr	savePort;
	DialogPtr	dialog;
	ParamText(str, 0, 0, 0);
	dialog = GetNewDialog( resID, 0L, (WindowPtr) -1 );
	SelectWindow(dialog);
	ShowWindow(dialog);
	DrawDialog(dialog);
	GetPort(&savePort);
	SetPort(dialog);
	//GetDItem(dialog, ITEM_TEXT, &iType, &iHandle, &r);
	//SetIText(iHandle, str);
	
	GetDItem(dialog, itemBar, &iType, &iHandle, &r);
	InsetRect(&r, -2, -2);
	FrameRect(&r);
	SetPort(savePort);
	return dialog;
}
//
// UpdateThermo()
//
void UpdateThermo(dialog, perc, itemBar)
DialogPtr	dialog;
short		perc;
short		itemBar;
{
	short	iType;
	Handle	iHandle;
	Rect	r;
	GrafPtr	savePort;
	
	GetPort(&savePort);
	SetPort(dialog);
	GetDItem(dialog, itemBar, &iType, &iHandle, &r);
	r.right = (r.right - r.left) * perc / 100 + r.left;
	PaintRect(&r);
	SetPort(savePort);
}
