/*
	File:		LibWind.c
	Contains:	xxx put contents here xxx
	Written by:	xxx put writers here xxx
	Copyright:	й 1994 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
		 <1>	 1/27/94	ek		first checked in
*/
#include "LibWind.h"
#include "LibStd.h"
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						prototypes
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
void		CenterAtMouseGdev(WindowPtr w);
void		CenterWindow(WindowPtr w, GDHandle g);
short		Confirm(short, char *, short);
void		DisableControl(DialogPtr, short);
void		EnableControl(DialogPtr, short);
short		FlipCheckBox(DialogPtr, short);
void		FrameItem(DialogPtr, short, short);
short		GetControl(DialogPtr, short);
GDHandle	GetMouseGdev(void);
void		PlotSicn(DialogPtr, short, short);
void		SetControl(DialogPtr, short, short);
void		ShadowRect(Rect *);
void 		ShowModalDlg(short, short, short);
DialogPtr	ShowModelessDlg(short, Point, short, short);
void		TraceMouseRect(Rect *);
void 		BuildRect(Rect *, Point *, Point *);
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						routines
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// CenterAtMouseGdev()
//
void CenterAtMouseGdev(WindowPtr w)
{
	GDHandle	gd;
	
	gd = GetMouseGdev();
	if(gd)
		CenterWindow(w, gd);
}
	
//
// CenterWindow()
//
void CenterWindow(WindowPtr w, GDHandle g)
{
	Rect	r;
	short	mymidx, mymidy;
	short	xpos, ypos;
	
	if (w == NIL || g == NIL)
		return;
		
	r = (*g)->gdRect;
	mymidx = r.left + (r.right - r.left) / 2;
	mymidy = r.top + (r.bottom - r.top) / 2;	
	xpos = mymidx - (w->portRect.right - w->portRect.left) / 2;
	ypos = mymidy - (w->portRect.bottom - w->portRect.top) / 2;
	if(ypos < r.top)
		ypos = r.top;
	MoveWindow(w, xpos, ypos, false);
}
//
// Confirm()
//
short Confirm(dlgID, str, itemDefault)
short	dlgID;
char	*str;
short	itemDefault;
{
	short		itemHit;
	DialogPtr	dialog;
	ParamText((unsigned char *)str, 0, 0, 0);
	dialog = GetNewDialog( dlgID, 0L, (WindowPtr) -1 );
	CenterAtMouseGdev(dialog);
	ShowWindow(dialog);
	OutlineButton(dialog, itemDefault);
	ModalDialog(0L, &itemHit);
	DisposDialog( dialog );
	return itemHit;
}
//
// DisableControl()
//
void DisableControl(dlg, item)
DialogPtr	dlg;
short		item;
{
	short	iType;
	Handle	iHandle;
	Rect	iRect;
	GetDItem(dlg, item, &iType, &iHandle, &iRect);
	HiliteControl((ControlHandle) iHandle, 255);
}
//
// EnableControl()
//
void EnableControl(dlg, item)
DialogPtr	dlg;
short		item;
{
	short	iType;
	Handle	iHandle;
	Rect	iRect;
	GetDItem(dlg, item, &iType, &iHandle, &iRect);
	HiliteControl((ControlHandle) iHandle, 0);
}
//
// FlipCheckBox()
//
short FlipCheckBox(dlg, item)
DialogPtr	dlg;
short		item;
{
	short	iType;
	Handle	iHandle;
	Rect	iRect;
	short	val;
	
	GetDItem(dlg, item, &iType, &iHandle, &iRect);
	val = GetCtlValue((ControlHandle) iHandle);
	val = 1 - val;
	SetCtlValue((ControlHandle) iHandle, val);
	return val;
}
//
// FrameItem()
//
void FrameItem(wptr, item, penSize)
DialogPtr	wptr;
short		item;
short		penSize;
{
	short	iType;
	Handle	iHandle;
	Rect	iRect;
	
	GetDItem(wptr, item, &iType, &iHandle, &iRect);
	PenSize(penSize, penSize);
	FrameRect(&iRect);
	PenSize(1, 1);
}
//
// GetControl()
//
short GetControl(wptr, item)
DialogPtr	wptr;
short		item;
{
	short	iType;
	Handle	iHandle;
	Rect	iRect;
	short	value;
	GetDItem(wptr, item, &iType, &iHandle, &iRect);
	value = GetCtlValue((ControlHandle) iHandle);
	return (value);
}
//
// GetMouseGdev()
//
GDHandle GetMouseGdev()
{
	Point		thePoint;
	GDHandle	gd;
	Rect		r;
	
	GetMouse(&thePoint);
	LocalToGlobal(&thePoint);
	gd = GetDeviceList();
	while(gd != 0) {
		r = (**gd).gdRect;
		if(PtInRect(thePoint, &r)) {
			return gd;
		}
		gd = GetNextDevice(gd);
	}
	
	return 0;
}
//
// PlotSicn()
//
void PlotSicn(dlg, userItem, sicnID)
DialogPtr	dlg;
short		userItem;
short		sicnID;
{
	GrafPtr	port;
	Handle	hIcon;
	BitMap	iconMap;
	short	type;
	Handle	h;
	Rect	r;
	
	GetDItem(dlg, userItem, &type, &h, &r);
	
	hIcon = GetResource('SICN', sicnID);
	HLock(hIcon);
	iconMap.baseAddr = *hIcon;
	iconMap.rowBytes = 2;
	SetRect(&iconMap.bounds, 0, 0, 16, 16);
	
	port = (WindowPtr) dlg;
	CopyBits(&iconMap, &port->portBits,
			&iconMap.bounds, &r, srcCopy, port->clipRgn);
	HUnlock(hIcon);
}
	
//
// SetControl()
//
void SetControl(wptr, item, value)
DialogPtr	wptr;
short		item;
short		value;
{
	short	iType;
	Handle	iHandle;
	Rect	iRect;
	GetDItem(wptr, item, &iType, &iHandle, &iRect);
	SetCtlValue((ControlHandle) iHandle, value);
}
//
// ShadowRect()
//
void ShadowRect(r)
Rect		*r;
 {
	FrameRect(r);
	MoveTo(r->right, r->top+2);
	LineTo(r->right, r->bottom);
	LineTo(r->left+2, r->bottom);
}
//
// ShowModalDlg()
//
void ShowModalDlg(dlgRsrcID, font, size)
short	dlgRsrcID;
short	font;
short	size;
{
	DialogPtr	dialog;
	short		itemHit;
	GrafPtr		oldPort;
	
	dialog = GetNewDialog(dlgRsrcID, 0L, (WindowPtr) -1);
	//CenterAtMouseGdev(dialog);
	SelectWindow(dialog);
	GetPort(&oldPort);
	SetPort(dialog);
	TextFont(font);
	TextSize(size);
	ShowWindow(dialog);
	ModalDialog(0L, &itemHit);
	SetPort(oldPort);
	DisposDialog( dialog );
}
//
// ShowModelessDlg()
//
DialogPtr ShowModelessDlg(dlgRsrcID, pt, font, size)
short	dlgRsrcID;
Point	pt;
short	font;
short	size;
{
	DialogPtr	dialog;
	GrafPtr		oldPort;
	dialog = GetNewDialog(dlgRsrcID, 0L, (WindowPtr) -1);
	CenterAtMouseGdev(dialog);
	//SelectWindow(dialog);
	GetPort(&oldPort);
	SetPort(dialog);
	TextFont(font);
	TextSize(size);
	MoveWindow(dialog, pt.h, pt.v, true);
	ShowWindow(dialog);
	SetPort(oldPort);
	return dialog;
}
//
// TraceMouseRect()
//
void TraceMouseRect(r)
Rect	*r;
{
	EventRecord	event;
	Point		pt1;
	Point		pt2;
	Point		pt2Save;
	
	//myPortPtr = (GrafPtr) NewPtr(sizeof(GrafPort));
	//OpenPort(myPortPtr);
	
	PenMode(patXor);
	//
	// detect mouseDown, read coord, dectect mouseUp, read coord
	//
	while(1) {
		GetOSEvent(everyEvent,&event);
		if(event.what == mouseDown) {
			break;
		}
	}
	GetMouse(&pt1);
		pt2Save = pt1;
		BuildRect(r, &pt1, &pt2Save);
		////FrameRect(r);
	
	while(StillDown()) {
		GetMouse(&pt2);
		if((pt2.h != pt2Save.h) || (pt2.v != pt2Save.v)) {
			////FrameRect(r);
			pt2Save = pt2;
			BuildRect(r, &pt1, &pt2);
			////FrameRect(r);
		}
	}
	
	BuildRect(r, &pt1, &pt2);
	////FrameRect(r);
	
	LocalToGlobal(&pt1);
	LocalToGlobal(&pt2);
	BuildRect(r, &pt1, &pt2);
	PenMode(patCopy);
	//ClosePort(myPortPtr);
}
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						routines
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// BuildRect()
//
void BuildRect(r, pt1, pt2)
Rect	*r;
Point	*pt1;
Point	*pt2;
{
	if(pt1->h < pt2->h) {
		r->left = pt1->h;
		r->right = pt2->h;
	}
	else {
		r->left = pt2->h;
		r->right = pt1->h;
	}
	
	if(pt1->v < pt2->v) {
		r->top = pt1->v;
		r->bottom = pt2->v;
	}
	else {
		r->top = pt2->v;
		r->bottom = pt1->v;
	}
}
//
// Set