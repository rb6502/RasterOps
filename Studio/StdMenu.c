/*
	File:		StdMenu.c
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
void	HandleMenu(short, short);
void	HandleAppleMenu(short);
void	HandleFileMenu(short);
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						other routines
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// HandleMenu()
//
void HandleMenu(menuID, item)
short	menuID;
short	item;
{
	switch(menuID) {
		case MENU_APPLE:
				HandleAppleMenu(item);
				break;
				
		case MENU_FILE:
				HandleFileMenu(item);
				break;
	}
	HiliteMenu(0);
}
//
// HandleAppleMenu()
//
void HandleAppleMenu(item)
short		item;
{
	Str255	accName;
	short	refNum;
	
	switch(item) {
		case MITEM_ABOUT:
			HandleAbout();
			break;
			
		default:
			GetItem(gAppleMenu, item, accName);
			refNum = OpenDeskAcc(accName);
			break;
	}
}
//
// HandleFileMenu()
//
void HandleFileMenu(item)
short	item;
{
	switch(item) {
		case MITEM_QUIT:
			gDone = true;
			break;
			
		default:
			break;
	}
}
