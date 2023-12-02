#
#	File:		Makefile
#
#	Contains:	The is the makefile for the Studio ROM.
#
#	Written by:	Eric Kuo
#
#	Copyright:	© 1994-1995 by RasterOps, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#		<11>	 7/17/95	MJ		Add link dependency upon version.h
#		<10>	  6/1/95	MJ		Revise Studio references to TARGA
#		 <9>	 2/28/95	MJ		Add version string
#		 <7>	 8/17/94	ek		cleanup
#		 <6>	 4/15/94	TC		Add Studio Build Options
#		 <5>	 2/25/94	ek		delete .rsrc and use .r file
#		 <4>	 2/10/94	ek		Add header file dependencies
#		 <3>	 1/27/94	ek		Orphan target file
#		 <2>	 1/27/94	ek		Set LoadROM to type 'rsrc'
#		 <1>	 1/27/94	ek		first checked in
#
OBJDIR		= 	:Obj:
LSTDIR		=	:Listings:
INCDIR		=	:Includes:
RSCDIR		=	:Resources:
BUILDDIR	=	:BuildResults:
SRCDIR		=	:Source:
LIBINCDIR	=	::Lib:Includes:
LIBOBJDIR	=	::Lib:Obj:
COptions	=	{TARGACOptions} -i "{INCDIR}" -i {LIBINCDIR}
AOptions	=	{TARGAAOptions} 
ROptions	=	{TARGAROptions} 
TargetFile	=	"{BUILDDIR}LoadROM"
CHEADERS	= 						¶
		{INCDIR}FlashROM.h			¶
		{INCDIR}LibStd.h			¶
		{INCDIR}LibWind.h			¶
		{INCDIR}mpw.h				¶
		{INCDIR}Std.h				¶
		{INCDIR}Thermo.h			¶
		{LIBINCDIR}LibSlot.h		¶
		{LIBINCDIR}FlashEprom.h
		
OBJECTS		=								¶
		{OBJDIR}StdMain.c.o					¶
		{OBJDIR}FlashMain.c.o				¶
		{OBJDIR}FlashROM.c.o				¶
		{OBJDIR}LibStd.c.o					¶
		{OBJDIR}LibWind.c.o					¶
		{OBJDIR}StdInit.c.o					¶
		{OBJDIR}StdLoop.c.o					¶
		{OBJDIR}StdMenu.c.o					¶
		{OBJDIR}Thermo.c.o					¶
		{LIBOBJDIR}Libs.o
RESOURCES = {RSCDIR}LoadROM.r
Makefile	=	Makefile
All			Ä	{TargetFile}	
Clean		Ä
			ClearDirectory {OBJDIR}
			ClearDirectory {BUILDDIR}
{TargetFile} ÄÄ Makefile {OBJECTS} {RESOURCES} "{CIncludes}version.h"
	Link -t APPL -c '????' ¶
		{OBJECTS} ¶
		"{Libraries}"Runtime.o ¶
		"{Libraries}"Interface.o ¶
		-o {TargetFile}
	Rez {ROptions} -rd -i "{CIncludes}" -o {TargetFile} {RSCDIR}LoadROM.r -append
	OrphanFiles {TargetFile}
	SetFile {TargetFile} -c 'RSED' -t 'rsrc'
		
{OBJDIR}StdMain.c.o Ä :Source:StdMain.c {CHEADERS}
	 C -r {COptions} -o "{OBJDIR}StdMain.c.o" :Source:StdMain.c
{OBJDIR}FlashMain.c.o Ä :Source:FlashMain.c {CHEADERS}
	 C -r {COptions} -o "{OBJDIR}FlashMain.c.o" :Source:FlashMain.c
{OBJDIR}FlashROM.c.o Ä :Source:FlashROM.c {CHEADERS}
	 C -r {COptions} -o "{OBJDIR}FlashROM.c.o" :Source:FlashROM.c
{OBJDIR}LibStd.c.o Ä :Source:LibStd.c {CHEADERS}
	 C -r {COptions} -o "{OBJDIR}LibStd.c.o" :Source:LibStd.c
{OBJDIR}LibWind.c.o Ä :Source:LibWind.c {CHEADERS}
	 C -r {COptions} -o "{OBJDIR}LibWind.c.o" :Source:LibWind.c
{OBJDIR}StdInit.c.o Ä :Source:StdInit.c {CHEADERS}
	 C -r {COptions} -o "{OBJDIR}StdInit.c.o" :Source:StdInit.c
{OBJDIR}StdLoop.c.o Ä :Source:StdLoop.c {CHEADERS}
	 C -r {COptions} -o "{OBJDIR}StdLoop.c.o" :Source:StdLoop.c
{OBJDIR}StdMenu.c.o Ä :Source:StdMenu.c {CHEADERS}
	 C -r {COptions} -o "{OBJDIR}StdMenu.c.o" :Source:StdMenu.c
{OBJDIR}Thermo.c.o Ä :Source:Thermo.c {CHEADERS}
	 C -r {COptions} -o "{OBJDIR}Thermo.c.o" :Source:Thermo.c
