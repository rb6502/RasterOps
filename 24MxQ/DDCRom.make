#
#	File:		DDCRom.make
#
#	Contains:	Rules for building the DDCRom.
#
#	Written by:	Mike Puckett, July 2, 1991.
#
#	Copyright:	© 1991 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#
#		 <4>	12/18/91	jwh		removed from projector.
#		 <3>	11/11/91	jmp		Just cleaned up a little.
#		 <2>	11/06/91	jmp		Stopped worrying about assembler warnings.
#		 <1>	09/17/91	jmp		first checked in
AOptions	=	-w -l -f -font Monaco,9 -h
LOptions	=	-w -mf -sym off -opt on
ObjDir		= 	:Objects:
ProjName	=	"DDCRom"
"{ObjDir}{ProjName}".a.o	Ä		"{ProjName}".a		¶
									PrimaryInit.a		¶
									Driver.a			¶
									DepVideoEqu.a
	Asm			{AOPtions}											¶
				"{ProjName}".a										¶
				-o "{ObjDir}{ProjName}".a.o
"{ProjName}"				ÄÄ		"{ObjDir}{ProjName}".a.o
	Link		-w													¶
				-o	"{ProjName}"									¶
				-c	'RSED'											¶
				-t	'rsrc'											¶
				-rt	'CODE'=1										¶
				"{CurProjDir}{ObjDir}{ProjName}".a.o
	Duplicate	-y													¶
				"{ProjName}"										¶
				"{ProjName}".x
	CRCPatch	"{ProjName}".x
#	Data		"{ProjName}".x										¶
#				"{ProjName}".d
	DumpSRec	-rt CODE=1											¶
				"{ProjName}".x	>									¶
				"{ProjName}".S1
	Move		-y													¶
				"{ProjName}"										¶
				"{ObjDir}{ProjName}"
	Delete		-y													¶
				"{ProjName}".x
				
				