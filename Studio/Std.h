/*
	File:		Std.h
	Contains:	xxx put contents here xxx
	Written by:	Eric Kuo
	Copyright:	й 1994 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
		 <2>	 2/10/94	ek		change file type to 'MPS '
		 <1>	 1/27/94	ek		first checked in
*/
#ifndef __THINK__
#include "mpw.h"
#endif
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						defs
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
#define MBAR			1900
#define MENU_APPLE		1900
	#define	MITEM_ABOUT		1
#define MENU_FILE		1901
	#define	MITEM_QUIT		1
#define DLG_MAIN		1900
#define DLG_ABOUT		2000
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						globals
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
extern DialogPtr	gDlgMain;
extern Boolean		gDone;
extern EventRecord	gEvent;
extern MenuHandle	gAppleMenu;
extern MenuHandle	gFileMenu;
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						prototypes
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// StdInit.c
//
void	MenuInit(void);
void	WindowInit(short);
//
// StdLoop.c
//
void	HandleAbout(void);
void	HandleActivate(void);
void	HandleKey(void);
void	HandleMouse(void);
void	HandleUpdate(void);
//
// StdMenu.c
//
void	HandleMenu(short, short);
//
// MyRoutine.c
//
Boolean	MyFini(void);
void	MyHit(short);
Boolean	MyInit(void);
