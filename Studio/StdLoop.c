/*
	File:		StdLoop.c
	Contains:	xxx put contents here xxx
	Written by:	xxx put writers here xxx
	Copyright:	й 1994 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
		 <1>	 1/27/94	ek		first checked in
*/
#include <LibStd.h>
#include "Std.h"
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						prototypes
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
void	HandleAbout(void);
void	HandleActivate(void);
void	HandleKey(void);
void	HandleMouse(void);
void	HandleUpdate(void);
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						main routines
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// HandleAbout()
//
void HandleAbout()
{
	DialogPtr	dlg;
	short		itemHit;
	
	dlg = GetNewDialog(DLG_ABOUT, 0L, (WindowPtr) -1);
	ModalDialog(0L, &itemHit);
	DisposDialog( dlg );
}
//
// HandleActivate()
//
void HandleActivate()
{
}
//
// HandleKey()
//
void HandleKey()
{
	char	theChar;
	char	theKey;
	long	menuChoice;
	
	theChar = gEvent.message & charCodeMask;
	theKey = (gEvent.message & keyCodeMask) >> 8;
	if(gEvent.modifiers & cmdKey) {
		menuChoice = MenuKey(theChar);
		HandleMenu(HiWord(menuChoice), LoWord(menuChoice));
	}
	else if ((theKey == 0x24) || (theKey == 0x4c)) {
		////gDone = true;
		MyHit(1);	// hit item 1
	}
}
//
// HandleMouse()
//
void HandleMouse()
{
	Rect		r;
	short		whichPart;
	Point		where;
	WindowPtr	wptr;
	long		menuChoice;
	
	where = gEvent.where;
	whichPart = FindWindow(where, &wptr);
	switch(whichPart) {
		case inMenuBar:
			menuChoice = MenuSelect(where);
			if(menuChoice)
				HandleMenu(HiWord(menuChoice), LoWord(menuChoice));
			break;
			
		case inContent:
			SelectWindow(wptr);
			////HandleInContent(wptr);
			break;
			
		case inDrag:
			r.left = -32768;
			r.right = 32767;
			r.top = -32768;
			r.bottom = 32767;
			
			DragWindow(wptr, where, &r);
			break;
			
		case inGoAway:
			if(TrackBox(wptr, where, whichPart))
				gDone = true;
			break;
			
		case inGrow:
			break;
			
		case inSysWindow:
			SystemClick(&gEvent, wptr);
			break;
			
		case inZoomIn:
		case inZoomOut:
			break;
	}
}
//
// HandleUpdate()
//
void HandleUpdate()
{
	OutlineButton(gDlgMain, 1);
}
