/*
	File:		StdInit.c
	Contains:	xxx put contents here xxx
	Written by:	xxx put writers here xxx
	Copyright:	й 1994 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
		 <1>	 1/27/94	ek		first checked in
*/
#include "Std.h"
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						prototypes
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
void	MenuInit(void);
void	WindowInit(short);
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						main routines
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// MenuInit()
//
void MenuInit()
{
	Handle hMbar;
	
	//
	// init menu
	//
	hMbar = GetNewMBar(MBAR);
	SetMenuBar(hMbar);
	gAppleMenu = GetMHandle(MENU_APPLE);
	AddResMenu(gAppleMenu, 'DRVR');
	DrawMenuBar();
}
//
// WindowInit(dlgMainID)
//
void WindowInit(dlgMainID)
short	dlgMainID;
{
	//
	// init window
	//
	gDlgMain = GetNewDialog(dlgMainID, 0L, (WindowPtr) -1);
	SelectWindow(gDlgMain);
	SetPort(gDlgMain);
	//TextFont(3);
	//TextSize(9);
	ShowWindow(gDlgMain);
	DrawDialog(gDlgMain);
}
