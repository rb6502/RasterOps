/*
	File:		LoadROM.r
	Contains:	LoadROM resource file
	Written by:	Eric Kuo
	Copyright:	© 1994-1995 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
		 <4>	  3/1/95	MJ		Use resource templates and replace the word "Studio" with
									"Targa"
		 <3>	 2/28/95	MJ		Add version string
		 <2>	 8/18/94	ek		update version number
		 <1>	 2/25/94	ek		first checked in
*/
#include "Types.r"
#include "SysTypes.r"
#include "vers.r"
resource 'DLOG' (1900, "MainDialog") {
	{128, 237, 249, 485},
	noGrowDocProc,
	visible,
	goAway,
	0x0,
	1900,
	""
	/****** Extra bytes follow... ******/
	/* $"0028 0A"                                            /* .(. */
};
resource 'DLOG' (2000, "About") {
	{118, 207, 251, 481},
	plainDBox,
	visible,
	noGoAway,
	0x0,
	2000,
	""
	/****** Extra bytes follow... ******/
	/* $"0030 0A"                                            /* .0. */
};
resource 'DLOG' (1902, "Thermometer") {
	{105, 197, 179, 497},
	dBoxProc,
	visible,
	noGoAway,
	0x0,
	1902,
	""
	/****** Extra bytes follow... ******/
	/* $"0030 0A"                                            /* .0. */
};
resource 'DLOG' (2001, "Success") {
	{194, 210, 274, 453},
	dBoxProc,
	visible,
	goAway,
	0x0,
	2001,
	""
	/****** Extra bytes follow... ******/
	/* $"FF28 0A"                                            /* ÿ(. */
};
resource 'DLOG' (2002, "Fail") {
	{200, 213, 280, 456},
	dBoxProc,
	visible,
	goAway,
	0x0,
	2002,
	""
	/****** Extra bytes follow... ******/
	/* $"FF28 0A"                                            /* ÿ(. */
};
resource 'DITL' (1900, "MainDlg") {
	{	/* array DITLarray: 3 elements */
		/* [1] */
		{84, 142, 104, 200},
		Button {
			enabled,
			"OK"
		},
		/* [2] */
		{84, 58, 104, 116},
		Button {
			enabled,
			"Quit"
		},
		/* [3] */
		{32, 28, 54, 224},
		Control {
			enabled,
			2000
		}
	}
};
resource 'DITL' (2000, "About") {
	{	/* array DITLarray: 2 elements */
		/* [1] */
		{0, 0, 134, 274},
		UserItem {
			enabled
		},
		/* [2] */
		{49, 70, 83, 205},
		StaticText {
			enabled,
			"TARGA ROM Loader\n       1/19/94"
		}
	}
};
resource 'DITL' (1902, "Thermometer") {
	{	/* array DITLarray: 2 elements */
		/* [1] */
		{18, 22, 36, 272},
		StaticText {
			disabled,
			"^0"
		},
		/* [2] */
		{50, 22, 60, 272},
		UserItem {
			disabled
		}
	}
};
resource 'DITL' (2001, "Success") {
	{	/* array DITLarray: 2 elements */
		/* [1] */
		{27, 34, 49, 209},
		StaticText {
			enabled,
			"ROM loaded successfully."
		},
		/* [2] */
		{0, 0, 80, 244},
		UserItem {
			enabled
		}
	}
};
resource 'DITL' (2002, "Fail") {
	{	/* array DITLarray: 2 elements */
		/* [1] */
		{30, 64, 51, 178},
		StaticText {
			enabled,
			"Load ROM failed."
		},
		/* [2] */
		{0, 0, 80, 244},
		UserItem {
			enabled
		}
	}
};
resource 'MBAR' (1900, "MyMbar") {
	{	/* array MenuArray: 2 elements */
		/* [1] */
		1900,
		/* [2] */
		1901
	}
};
resource 'MENU' (1900) {
	1900,
	textMenuProc,
	0x7FFFFFFD,
	enabled,
	apple,
	{	/* array: 2 elements */
		/* [1] */
		"About TARGA ROMÉ", noIcon, noKey, noMark, plain,
		/* [2] */
		"-", noIcon, noKey, noMark, plain
	}
};
resource 'MENU' (1901) {
	1901,
	textMenuProc,
	allEnabled,
	enabled,
	"File",
	{	/* array: 1 elements */
		/* [1] */
		"Quit", noIcon, "Q", noMark, plain
	}
};
resource 'MENU' (2000, "Slots") {
	2000,
	textMenuProc,
	allEnabled,
	enabled,
	"Slots",
	{	/* array: 6 elements */
		/* [1] */
		"Slot 9", noIcon, noKey, noMark, plain,
		/* [2] */
		"Slot A", noIcon, noKey, noMark, plain,
		/* [3] */
		"Slot B", noIcon, noKey, noMark, plain,
		/* [4] */
		"Slot C", noIcon, noKey, noMark, plain,
		/* [5] */
		"Slot D", noIcon, noKey, noMark, plain,
		/* [6] */
		"Slot E", noIcon, noKey, noMark, plain
	}
};
resource 'ICN#' (128) {
	{	/* array: 2 elements */
		/* [1] */
		$"0000 0000 0000 0000 0000 0020 0000 00C0"
		$"0000 0140 0000 0280 0000 0500 0000 0900"
		$"0000 11FC 0000 2008 0000 3F10 0000 0220"
		$"0000 04C0 0000 0900 0000 1200 0000 2400"
		$"0000 5800 0000 A000 0001 4000 01FF FFF0"
		$"0F0F 01F0 3800 0F10 FFFF F810 8000 2030"
		$"8000 21F0 8000 2F90 FFFF FC90 9249 2490"
		$"9249 2490 9249 2000 9249 20",
		/* [2] */
		$"0000 0000 0000 0000 FFFF FFFC FFFF FFFC"
		$"FFFF FFFC FFFF FFFC FFFF FFFC FFFF FFFC"
		$"FFFF FFFC FFFF FFFC FFFF FFFC FFFF FFFC"
		$"FFFF FFFC FFFF FFFC FFFF FFFC FFFF FFFC"
		$"FFFF FFFC FFFF FFFC FFFF FFFC FFFF FFFC"
		$"FFFF FFFC FFFF FFFC FFFF FFFC FFFF FFFC"
		$"FFFF FFFC FFFF FFFC FFFF FFFC FFFF FFFC"
		$"FFFF FFFC FFFF FFFC FFFF FFFC"
	}
};
resource 'icl8' (128) {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 FF00 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 FFFF 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 00FF D8FF 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 FFD8 FF00 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 00FF D8FF 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 FFD8 D8FF 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 00FF D8D8 D8FF FFFF FFFF FFFF 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 FFD8 D8D8 D8D8 D8D8 D8D8 FF00 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 FFFF FFFF FFFF D8D8 D8FF 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 FFD8 D8D8 FF00 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 00FF D8D8 FFFF 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 FFD8 D8FF 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 00FF D8D8 FF00 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 FFD8 D8FF 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"00FF D8FF FF00 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"FFD8 FF00 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 00FF"
	$"D8FF 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 00FF FFFF FFFF FFFF FFFF"
	$"FFFF FFFF FFFF FFFF FFFF FFFF 0000 0000"
	$"0000 0000 FFFF FFFF 2B2B 2B2B FFFF FFFF"
	$"2B2B 2B2B 2B2B 2BFF FFFF FFFF 0000 0000"
	$"0000 FFFF FF2B 2B2B 2B2B 2B2B 2B2B 2B2B"
	$"2B2B 2B2B FFFF FFFF 2B2B 2BFF 0000 0000"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	$"FFFF FFFF FF2B 2B2B 2B2B 2BFF 0000 0000"
	$"FF2B 2B2B 2B2B 2B2B 2B2B 2B2B 2B2B 2B2B"
	$"2B2B FF2B 2B2B 2B2B 2B2B FFFF 0000 0000"
	$"FF2B 2B2B 2B2B 2B2B 2B2B 2B2B 2B2B 2B2B"
	$"2B2B FF2B 2B2B 2BFF FFFF FFFF 0000 0000"
	$"FF2B 2B2B 2B2B 2B2B 2B2B 2B2B 2B2B 2B2B"
	$"2B2B FF2B FFFF FFFF FF00 00FF 0000 0000"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	$"FFFF FFFF FFFF 0000 FF00 00FF 0000 0000"
	$"FF00 00FF 0000 FF00 00FF 0000 FF00 00FF"
	$"0000 FF00 00FF 0000 FF00 00FF 0000 0000"
	$"FF00 00FF 0000 FF00 00FF 0000 FF00 00FF"
	$"0000 FF00 00FF 0000 FF00 00FF 0000 0000"
	$"FF00 00FF 0000 FF00 00FF 0000 FF00 00FF"
	$"0000 FF00 0000 0000 0000 0000 0000 0000"
	$"FF00 00FF 0000 FF00 00FF 0000 FF00 00FF"
	$"0000 FF"
};
resource 'icl4' (128) {
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 00F0 0000"
	$"0000 0000 0000 0000 0000 0000 FF00 0000"
	$"0000 0000 0000 0000 0000 000F 0F00 0000"
	$"0000 0000 0000 0000 0000 00F0 F000 0000"
	$"0000 0000 0000 0000 0000 0F0F 0000 0000"
	$"0000 0000 0000 0000 0000 F00F 0000 0000"
	$"0000 0000 0000 0000 000F 000F FFFF FF00"
	$"0000 0000 0000 0000 00F0 0000 0000 F000"
	$"0000 0000 0000 0000 00FF FFFF 000F 0000"
	$"0000 0000 0000 0000 0000 00F0 00F0 0000"
	$"0000 0000 0000 0000 0000 0F00 FF00 0000"
	$"0000 0000 0000 0000 0000 F00F 0000 0000"
	$"0000 0000 0000 0000 000F 00F0 0000 0000"
	$"0000 0000 0000 0000 00F0 0F00 0000 0000"
	$"0000 0000 0000 0000 0F0F F000 0000 0000"
	$"0000 0000 0000 0000 F0F0 0000 0000 0000"
	$"0000 0000 0000 000F 0F00 0000 0000 0000"
	$"0000 000F FFFF FFFF FFFF FFFF FFFF 0000"
	$"0000 FFFF 0000 FFFF 0000 000F FFFF 0000"
	$"00FF F000 0000 0000 0000 FFFF 000F 0000"
	$"FFFF FFFF FFFF FFFF FFFF F000 000F 0000"
	$"F000 0000 0000 0000 00F0 0000 00FF 0000"
	$"F000 0000 0000 0000 00F0 000F FFFF 0000"
	$"F000 0000 0000 0000 00F0 FFFF F00F 0000"
	$"FFFF FFFF FFFF FFFF FFFF FF00 F00F 0000"
	$"F00F 00F0 0F00 F00F 00F0 0F00 F00F 0000"
	$"F00F 00F0 0F00 F00F 00F0 0F00 F00F 0000"
	$"F00F 00F0 0F00 F00F 00F0 0000 0000 0000"
	$"F00F 00F0 0F00 F00F 00F0"
};
data 'From' (0, "Owner resource") {
	$"0B46 6C61 7368 526F 6D31 2E30"                      /* .FlashRom1.0 */
};
data 'FREF' (128) {
	$"4150 504C 0000 7F"                                  /* APPL... */
};
resource 'BNDL' (128) {
	'From',
	0,
	{	/* array TypeArray: 2 elements */
		/* [1] */
		'FREF',
		{	/* array IDArray: 1 elements */
			/* [1] */
			0, 128
		},
		/* [2] */
		'ICN#',
		{	/* array IDArray: 1 elements */
			/* [1] */
			0, 128
		}
	}
};
resource 'CNTL' (2000, "Slots") {
	{50, 28, 72, 224},
	1,
	visible,
	120,
	2000,
	1008,
	0,
	"Load TARGA ROM:"
};
