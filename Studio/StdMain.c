/*
	File:		StdMain.c
	Contains:	xxx put contents here xxx
	Written by:	xxx put writers here xxx
	Copyright:	й 1994 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
		 <1>	 1/27/94	ek		first checked in
*/
#include "Std.h"
#include <LibStd.h>
DialogPtr gDlgMain;
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						globals
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
Boolean		gDone;
EventRecord	gEvent;
MenuHandle	gAppleMenu;
MenuHandle	gFileMenu;
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						prototypes
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
void	main(void);
void	Init(void);
void	MainLoop(void);
void	DoDlogEvent(void);
void	HandleEvent(void);
extern Boolean	MyInit(void);
extern Boolean	MyFini(void);
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						main routines
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// main()
//
void main(void)
{
	Boolean	rc;
	
	ToolBoxInit();
	
#ifdef __THINK__
	OpenResFile("\p:Resources:LoadROM.╣.rsrc");
#endif
	Init();
	
	rc = MyInit();
	if(!rc)
		return;
		
	MainLoop();
	MyFini();
}
//
// Init()
//
void Init()
{
	WindowInit(DLG_MAIN);
	MenuInit();
}
//
// MainLoop()
//
void MainLoop()
{
	gDone = false;
	while(!gDone) {
		GetEvent(&gEvent);
		if(IsDialogEvent(&gEvent)) {
			DoDlogEvent();
		}
		else {
			HandleEvent();
		}
	}
}
//
// DoDlogEvent()
//
void DoDlogEvent()
{
	DialogPtr	whichDlog;
	short		itemHit;
	Boolean		rc;
	
	//
	// process cmd-shift first before calling DialogSelect()
	//
	if((gEvent.what == keyDown) && (gEvent.modifiers & cmdKey)) {
		HandleKey();
	}
	
	rc = DialogSelect(&gEvent, &whichDlog, &itemHit);
	
	if(rc) {
		if(whichDlog == gDlgMain) {
			switch(itemHit) {
				case ok:
					//gDone = true;
					MyHit(itemHit);
					break;
				default:
					MyHit(itemHit);
					break;
			}
		}
	}
	else {
		if(whichDlog == gDlgMain) {
			HandleEvent();
		}
	}
}
//
// HandleEvent()
//
void HandleEvent()
{
	switch(gEvent.what) {
		case mouseDown:
			HandleMouse();
			break;
			
		case keyDown:
		case autoKey:
			HandleKey();
			break;
			
		case updateEvt:
			HandleUpdate();
			break;
			
		case activateEvt:
			HandleActivate();
			break;
			
		case nullEvent:
			break;
	}
}
