/*
	File:		LibStd.c
	Contains:	xxx put contents here xxx
	Written by:	xxx put writers here xxx
	Copyright:	й 1994-1995 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
		 <2>	  6/1/95	MJ		Typecast for latest headers
		 <1>	 1/27/94	ek		first checked in
*/
#include "LibStd.h"
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						prototypes
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
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
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						routines
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
#define WNE_TRAP_NUM		0x60
#define UNIMPL_TRAP_NUM		0x9F
//
// CommandPressed()
//
Boolean CommandPressed()
{
	return (IsPressed(0x37));
}
//
// GetEvent()
//		get next event, use GetNextEvent or WaitNextEvent
//
void GetEvent(event)
EventRecord	*event;
{
	if(1) {	//NGetTrapAddress(WNE_TRAP_NUM, ToolTrap) != NGetTrapAddress(UNIMPL_TRAP_NUM, ToolTrap)) {
		WaitNextEvent(everyEvent, event, 0L, 0L);
	}
	else {
		SystemTask();
		GetNextEvent(everyEvent, event);
	}
}
//
// IsPressed()
//
Boolean IsPressed(k)
unsigned short	k;
{
	unsigned char	km[16];
	
	GetKeys((KeyMap) km);
	return ((km[k>>3] >> (k & 7)) & 1);
}
//
// OptionPressed()
//
Boolean OptionPressed()
{
	return (IsPressed(0x3a));
}
//
// OutlineButton()
//
pascal void OutlineButton(dialogPtr, item)
WindowPtr dialogPtr;
short item;
 {
	GrafPtr dPeek;
	short itemType;
	Handle itemHandle;
	Rect dispRect;
	GrafPtr	SavedPort; 
	dPeek = (GrafPtr) dialogPtr;
	GetPort(&SavedPort); 
	SetPort( dPeek );
	GetDItem( dialogPtr, item, &itemType, &itemHandle, &dispRect );	
	PenSize(3, 3); 
	InsetRect(&dispRect, -4, -4);
	FrameRoundRect(&dispRect, 16, 16);
	PenSize(1, 1); 
 	SetPort(SavedPort);  
}
//
// RangedRdm()
//
unsigned short	RangedRdm(min, max)
unsigned short	min, max;
{
	unsigned	qdRdm;
	long		range,t;
	
	qdRdm = Random();
	range = max - min + 1;
	t = (qdRdm * range) / 65536;
	t += min;
	if(t > max)		// not necessary
		t = max;
	return (t);
}
//
// ShowWatch()
//
void ShowWatch()
{
  CursHandle watch;        /* Handle to the watch cursor data. */
  watch = GetCursor(4);    /* Get the handle to the watch cursor. */
  SetCursor(*watch);       /* Set the cursor to the watch. */
  ReleaseResource((Handle) watch);
}
//
// Sleep()
//
void Sleep(n)
short	n;
{
	long	targetTick;
	
	targetTick = TickCount() + n;
	while(TickCount() <= targetTick)
		;
}
//
// ToolBoxInit()
//
void ToolBoxInit(void)
{
#ifdef __THINK__
	InitGraf(&thePort);
#else
	InitGraf(&qd.thePort);
#endif
	InitFonts();
	FlushEvents(everyEvent, 0);
	InitWindows();
	InitMenus();
	TEInit();
	InitDialogs(0L);
	InitCursor();
}
#ifdef __THINK__
//
// WaitNms()
//
void WaitNms(n)
register short	n;
{
	while(n-- > 0) {
		asm {
			clr.l	d0
			move.w	0x0d00,d0
		@loop
			dbra	d0,@loop
		}
	}
}
#else
//
// WaitNms()
//
void WaitNms(register short n)
{
	register short	t;
	
	while(n-- > 0) {
		t = *((short *) 0x0d00);
		t >>= 1;		// roughly twice as many cycles
		while(--t > 0)
			;
	}
}
#endif
