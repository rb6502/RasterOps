/*
	File:		LibWind.h
	Contains:	xxx put contents here xxx
	Written by:	Eric Kuo
	Copyright:	й 1994 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
		 <2>	 2/10/94	ek		change file type to 'MPS '
		 <1>	 1/27/94	ek		first checked in
*/
#ifndef __LIBWIND__
#define __LIBWIND__
#ifndef __THINK__
#include "mpw.h"
#endif
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//						prototypes
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
#if __cplusplus
extern "C" {void		CenterAtMouseGdev(WindowPtr w);};
extern "C" {void		CenterWindow(WindowPtr w, GDHandle g);};
extern "C" {short		Confirm(short, char *, short);};
extern "C" {void		DisableControl(DialogPtr, short);};
extern "C" {void		EnableControl(DialogPtr, short);};
extern "C" {short		FlipCheckBox(DialogPtr, short);};
extern "C" {void		FrameItem(DialogPtr, short, short);};
extern "C" {short		GetControl(DialogPtr, short);};
extern "C" {GDHandle	GetMouseGdev(void);};
extern "C" {void		PlotSicn(DialogPtr, short, short);};
extern "C" {void		SetControl(DialogPtr, short, short);};
extern "C" {void		ShadowRect(Rect *);};
extern "C" {void 		ShowModalDlg(short, short, short);};
extern "C" {DialogPtr	ShowModelessDlg(short, Point, short, short);};
extern "C" {void		TraceMouseRect(Rect *);};
#else
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
#endif
#endif
