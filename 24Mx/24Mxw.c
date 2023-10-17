 *
 * RasterOps 24Mx Board Declaration ROM
 *
 * COPYRIGHT 1991 by RasterOps Inc.
 */
/*
 * This is written in Aztec C, version 3.6B
 *
 * 11/27/91: converted from 24XL(i/TV) source, 
 * 5/27/94 2:43:04 PM	v2.0d1: Display Manager/Energy saver support - jwh
 * 6/13/94 2:18:51 PM	v2.0d2: energy saver, switchmode to interlace bugs - jwh
 * 6/28/94 9:29:01 AM	v2.0d3: fix bugs, missing nonextended choice and hanging,
 								energy saver refresh, 1 VBL load luts, syncio nops - jwh
 * 7/13/94 11:55:11 AM	v2.0b4: GetMode Timing Return error for Id out of range, PAL Table - jwh
 * 7/19/94 3:27:43 PM	v2.0b5: Genlock bug, Ext to non-Ext bug, 8x6 show 1152x870ext - jwh
 * 7/20/94 3:07:20 PM	v2.0: remove b5 from board name string - jwh
 *
 * 8/11/94 5:19:40 PM	v2.1b1: Fix Set/GetEntries for 16 bit - jwh
 */
#define _DRIVER           	;tells the compiler that we are doing a driver
#asm
ROMBase 	EQU 	$2AE					; ROM base address [pointer]
#endasm
#define DEBUG		0
#define DEBUGZOOM	0
#define tmpDEBUG	0
pascal myDebugStr() = 0xABFF;
pascal ADBReInit() = 0xA07B;
#include "zoom.h"
#define AUTOSWITCHING	1
/*
 * determine which rom we are doing, be careful with the order of defs
 */
#if (MAKINGIZUMIYA | MAKINGGENERIC | MAKINGLTD | MAKINGRGB | MAKINGMT)
	#define MAKINGCUSTOM	1
	#define MAKINGROPS		0
#else
	#define MAKINGCUSTOM	0
	#define MAKINGROPS		1
#endif
#if MAKINGCUSTOM
#asm
MAKINGCUSTOM EQU 1
#endasm
#else
#asm
MAKINGCUSTOM EQU 0
#endasm
#endif
#if MAKINGROPS
#asm
MAKINGROPS EQU 1
#endasm
#else
#asm
MAKINGROPS EQU 0
#endasm
#endif
/*
 * defs
 */
#if MAKING24MXI
#asm
MAKING24MXI EQU 1
#endasm
#else
#asm
MAKING24MXI EQU 0
#endasm
#endif
#if MAKING24MXTV
#asm
MAKING24MXTV EQU 1
#endasm
#else
#asm
MAKING24MXTV EQU 0
#endasm
#endif
#if MAKING24MXRGB
#asm
MAKING24MXRGB EQU 1
#endasm
#else
#asm
MAKING24MXRGB EQU 0
#endasm
#endif
#if MAKINGIZUMIYA
#asm
MAKINGIZUMIYA EQU 1
#endasm
#else
#asm
MAKINGIZUMIYA EQU 0
#endasm
#endif
#if MAKINGRGB
#asm
MAKINGRGB EQU 1
#endasm
#else
#asm
MAKINGRGB EQU 0
#endasm
#endif
#if MAKINGMT
#asm
MAKINGMT EQU 1
#endasm
#else
#asm
MAKINGMT EQU 0
#endasm
#endif
#if AUTOSWITCHING
#asm
AUTOSWITCHING EQU 1
#endasm
#else
#asm
AUTOSWITCHING EQU 0
#endasm
#endif
#if TESTING
#asm
TESTING EQU 1
#endasm
#else
#asm
TESTING EQU 0
#endasm
#endif
/**************************************************************************************
 * 24Mxi Hardware definitions
 **************************************************************************************/
 
/*
 * Offsets from base address to Registers
 */
#define MASKRAM			0x00800000L		/* Mask RAM offset */
#define COMPRESSION		0x00800000L		/* Compression Board offset */
#define PIP				0x00D00000L		/* PIP offset */
#define ACCELERATOR		0x00E00000L		/* Accelerator offset */
#define EEPROM			0x00F70000L		/* EE Prom address */
#define ADDRMODE1		0x00F80000L		/* address mode, 0:pip, 1: accelerator */
#define ADDRMODE2		0x00F60000L		/* address mode, 0:pip, 1: accelerator */
#define FATSLOT			0x00F90000L		/* Read=Fat/Write=Skinny slot control offset */
#define BT473			0x00FA0000L		/* BT473 offset */
#define RGS14188		0x00FB0000L		/* TMS34061 offset */
#define BT473_P_ADDR	(BT473 + 0x00L)	/* BT473 Palette Address register */
#define BT473_PALETTE	(BT473 + 0x04L)	/* BT473 Palette Data register */
#define BT473_MASK		(BT473 + 0x08L)	/* BT473 Read Mask register */
#define BT473_O_ADDR	(BT473 + 0x10L)		/* BT473 Overlay Address register */
#define BT473_OVERLAY	(BT473 + 0x14L)		/* BT473 Overlay Data register */
#define BT473_COMMAND	(BT473 + 0x18L)		/* BT473 Command register */
#define	RGS14188_BASE		RGS14188
#define	DAC_BASE			BT473
#define BITGD	0x0020				/* GD bit in gio lo */
#define BIT_PAL			0x4
#define BIT_GENLOCK		0x2
#define BIT_UNDERSCAN	0x1
#define ISGENLOCK(base) \
	((*((char *) (base + GIOREGLOW)) & BITGD) == 0)
/*
 * software register in venus chip
 * bit 0: 0=ntsc 1=pal
 * bit 1: 0=normal 1=underscan
 */
#define ISUNDERSCAN(base) \
	(*((char *) (base + SOFTREG)) & 0x01)
#define ISPAL(base) \
	(*((char *) (base + SOFTREG)) & 0x02)
	
#define SETSOFTREG_USCAN(base) \
	(*((char *) (base + SOFTREG)) |= 0x01)
#define SETSOFTREG_PAL(base) \
	(*((char *) (base + SOFTREG)) |= 0x02)
/* Offsets to RGS14188 Registers */
enum
{
	control_1 = 0,
	control_2 = 1,
	control_3 = 2,
	control_4 = 3,
	status_ = 4,
	refresh_interval = 5,
	gio_config = 6,
	gio_config_Hi = 6,
	gio_config_Lo = 7,
	display_start = 8,
	display_start_Hi = 9,
	display_start_Mid = 10,
	display_start_Lo = 11,
	half_row_inc = 12,
	half_row_inc_Hi = 13,
	half_row_inc_Mid = 14,
	half_row_inc_Lo = 15,
	display_pitch = 16,
	display_pitch_Hi = 17,
	display_pitch_Mid = 18,
	display_pitch_Lo = 19,
	CAS_mask = 20,
	horiz_latency = 21,
	horiz_end_sync = 22,
	horiz_end_sync_Hi = 22,
	horiz_end_sync_Lo = 23,
	horiz_end_blank = 24,
	horiz_end_blank_Hi = 24,
	horiz_end_blank_Lo = 25,
	horiz_start_blank = 26,
	horiz_start_blank_Hi = 26,
	horiz_start_blank_Lo = 27,
	horiz_total = 28,
	horiz_total_Hi = 28,
	horiz_total_Lo = 29,
	horiz_half_line = 30,
	horiz_half_line_Hi = 30,
	horiz_half_line_Lo = 31,
	horiz_count_load = 32,
	horiz_count_load_Hi = 32,
	horiz_count_load_Lo = 33,
	vert_end_sync = 34,
	vert_end_blank = 35,
	vert_start_blank = 36,
	vert_start_blank_Hi = 36,
	vert_start_blank_Lo = 37,
	vert_total = 38,
	vert_total_Hi = 38,
	vert_total_Lo = 39,
	vert_count_load = 40,
	vert_count_load_Hi = 40,
	vert_count_load_Lo = 41,
	vert_int_line = 42,
	vert_int_line_Hi = 42,
	vert_int_line_Lo = 43,
	gio_reg = 44,
	gio_reg_Hi = 44,
	gio_reg_Lo = 45,
	y_zoom = 46,
	soft_reg = 47
};
#define clk107mhz	0x1A
#define clk100mhz	0x19
#define clk80mhz	0x17
#define clk64mhz	0x16
#define clk50mhz	0x14
#define clk30mhz	0x13
#define clkPALmhz	0x11
#define clkNTSCmhz	0x10
#define pix_over32	0x80
#define pix_over16	0x00
#define pix_over8	0xC0
#define pix_over4	0x40
#define pix_1	0x00
#define pix_2	0x04
#define pix_4	0x08
#define pix_8	0x0C
#define pix_16	0x0D
#define pix_24	0x0E
#define alpha_8		0x00
#define alpha_16	0x00
#define alpha_24	0x80
#define soft_reset_off	0x40
#define VENUS_CTL1		(0xFB0000 + 3)
#define VENUS_CTL2		(0xFB0004 + 3)
#define VENUS_CTL3		(0xFB0008 + 3)
#define VENUS_CTL4		(0xFB000C + 3)
#define GIOREGHIGH		(0xFB00B0 + 3)
#define GIOREGLOW		(0xFB00B4 + 3)
#define YZOOMREG		(0xFB00B8 + 3)
#define SOFTREG			(0xFB00BC + 3)
#define DISP_PITCH_LOW	(0xFB004C + 3)
#define DISP_PITCH_MID	(0xFB0048 + 3)
#define DISP_PITCH_HIGH	(0xFB0044 + 3)
#define DISP_START_LOW	(0xFB002C + 3)
#define DISP_START_MID	(0xFB0028 + 3)
#define DISP_START_HIGH	(0xFB0024 + 3)
#define FATMODE		1
#define SKINNYMODE	0
#asm
VENUS_CTL1	EQU		$00FB0003
VENUS_CTL2	EQU		$00FB0007
VENUS_CTL3	EQU		$00FB000B
VENUS_CTL4	EQU		$00FB000F
GIOREGHIGH	EQU		$00FB00B3
GIOREGLOW	EQU		$00FB00B7
#endasm
/*
 * Macros
 */
#define GET_YZOOM(base)		(*(unsigned char *) (base | YZOOMREG))
#define SET_XZOOM(base, val) \
	*((unsigned char *) (base | GIOREGHIGH)) = (*((unsigned char *) (base | GIOREGHIGH)) & 0xCF) | (val << 4)	
#define SET_YZOOM(base, val)	(*((unsigned char *) (base | YZOOMREG)) = val)
#define pi_get_disp_pitch(base) \
	(pi_get_rgs(base, (short) display_pitch, (short) 4) & 0x00ffffff)
#define dr_get_disp_pitch(base) \
	(dr_get_rgs(base, (short) display_pitch, (short) 4) & 0x00ffffff)	
	
#define VRAMXFR_ON(base) \
	(*(unsigned long *) (base + RGS14188 + control_1 * 4) |= 0x20)
#define VRAMXFR_OFF(base) \
	(*(unsigned long *) (base + RGS14188 + control_1 * 4) &= ~0x20)
#define REFRESH_ON(base) \
	(*(unsigned long *) (base + RGS14188 + control_1 * 4) |= 0x10)
#define REFRESH_OFF(base) \
	(*(unsigned long *) (base + RGS14188 + control_1 * 4) &= ~0x10)
	
#define devBase(slot) (((unsigned long) (slot) << 24) | 0xF0000000L)
/*****************************************************************************
 * EEPROM defs and Macros (24Mxi)
 *****************************************************************************/
#define OP_EWEN		0x0
#define OP_EWDS		0x0
#define OP_ERAL		0x0
#define OP_WRAL		0x0
#define OP_WRITE	0x1
#define OP_READ		0x2
#define OP_ERASE	0x3
#define ADDR_EWEN	0x3F
#define ADDR_ERAL	0x2F
#define ADDR_WRAL	0x1F
#define ADDR_EWDS	0x0F
/*
 * for primary init
 */
#define piEEPoke(eep, SK, CS, DIO) \
	{ pieePoke(eep, (short) ((SK << 1) | (CS << 2) | (DIO)));}
	
#define piEEPeek(eep)	pieePeek(eep)
#define piEEProlog(eep) \
	{piEEPoke(eep, 0, 0, 0); \
	 piEEPoke(eep, 0, 1, 0); \
	 piEEPoke(eep, 1, 1, 0); \
	 piEEPoke(eep, 0, 1, 1); \
	 piEEPoke(eep, 1, 1, 1);}
	 
#define piEEEpilog(eep) \
	piEEPoke(eep, 0, 0, 0)
#define piEEDiscardBit(eep) \
	{piEEPoke(eep, 0, 1, 0); \
	 piEEPoke(eep, 1, 1, 0);}
	
#define piEESendOpcode(eep, opcode) \
	piEESendBitStream(eep, opcode, (short) 2)
#define piEESendAddr(eep, addr) \
	piEESendBitStream(eep, addr, (short) 6)
#define piEESendData(eep, data) \
	piEESendBitStream(eep, data, (short) 16)
void pieeEnable();
void pieeDisable();
void pieeEraseAll();
short pieeReadWord();
void pieeWriteWord();
short piEEPollReady();
short piEEReadBitStream();
void piEESendBitStream();
void piEESendStartOpAddr();
void pieePoke();
short pieePeek();
/*
 * for secondary init
 */
#define siEEPoke(eep, SK, CS, DIO) \
	{ sieePoke(eep, (short) ((SK << 1) | (CS << 2) | (DIO)));}
	
#define siEEPeek(eep)	sieePeek(eep)
#define siEEProlog(eep) \
	{siEEPoke(eep, 0, 0, 0); \
	 siEEPoke(eep, 0, 1, 0); \
	 siEEPoke(eep, 1, 1, 0); \
	 siEEPoke(eep, 0, 1, 1); \
	 siEEPoke(eep, 1, 1, 1);}
	 
#define siEEEpilog(eep) \
	siEEPoke(eep, 0, 0, 0)
#define siEEDiscardBit(eep) \
	{siEEPoke(eep, 0, 1, 0); \
	 siEEPoke(eep, 1, 1, 0);}
	
#define siEESendOpcode(eep, opcode) \
	siEESendBitStream(eep, opcode, (short) 2)
#define siEESendAddr(eep, addr) \
	siEESendBitStream(eep, addr, (short) 6)
#define siEESendData(eep, data) \
	siEESendBitStream(eep, data, (short) 16)
void sieeEnable();
void sieeDisable();
void sieeEraseAll();
short sieeReadWord();
void sieeWriteWord();
short siEEPollReady();
short siEEReadBitStream();
void siEESendBitStream();
void siEESendStartOpAddr();
void sieePoke();
short sieePeek();
/*
 * for driver
 */
#define drEEPoke(eep, SK, CS, DIO) \
	{ dreePoke(eep, (short) ((SK << 1) | (CS << 2) | (DIO)));}
	
#define drEEPeek(eep)	dreePeek(eep)
#define drEEProlog(eep) \
	{drEEPoke(eep, 0, 0, 0); \
	 drEEPoke(eep, 0, 1, 0); \
	 drEEPoke(eep, 1, 1, 0); \
	 drEEPoke(eep, 0, 1, 1); \
	 drEEPoke(eep, 1, 1, 1);}
	 
#define drEEEpilog(eep) \
	drEEPoke(eep, 0, 0, 0)
#define drEEDiscardBit(eep) \
	{drEEPoke(eep, 0, 1, 0); \
	 drEEPoke(eep, 1, 1, 0);}
	
#define drEESendOpcode(eep, opcode) \
	drEESendBitStream(eep, opcode, (short) 2)
#define drEESendAddr(eep, addr) \
	drEESendBitStream(eep, addr, (short) 6)
#define drEESendData(eep, data) \
	drEESendBitStream(eep, data, (short) 16)
void dreeEnable();
void dreeDisable();
void dreeEraseAll();
short dreeReadWord();
void dreeWriteWord();
short drEEPollReady();
short drEEReadBitStream();
void drEESendBitStream();
void drEESendStartOpAddr();
void dreePoke();
short dreePeek();
/*****************************************************************************
 * i2cEEPROM defs and Macros (24MxTV)
 *****************************************************************************/
/*
 * constants
 */
#define pip				0x00D00000L		/* PIP offset */
#define	pip_control_1 	0x0031		/* Pip control register 1 */
#define pip_i2c			(pip + pip_control_1 * 4)		/* I2C Control */
#define pip_i2c_clock	0x0080		/* SCL - Serial Clock */
#define pip_i2c_data	0x0040		/* SDA - Serial Data */
#define pip_i2c_drst	0x0020		/* DMSD - Serial Data */
#define I2CADDR		0x00a0
#define I2CWRITE	0x0
#define I2CREAD		0x1
#define tLOW		0
#define tHIGH		0
/*
 * i2c for Primary Init
 */
/*
 * macros
 */
#define piSCL0_SDA0(base)		pii2cSetSCLSDA(base,0,0)
#define piSCL0_SDA1(base)		pii2cSetSCLSDA(base,0,1)
#define piSCL1_SDA0(base)		pii2cSetSCLSDA(base,1,0)
#define piSCL1_SDA1(base)		pii2cSetSCLSDA(base,1,1)
#define piSCL0(base)		pii2cSetSCL(base,0)
#define piSCL1(base)		pii2cSetSCL(base,1)
#define piSDA0(base)		pii2cSetSDA(base,0)
#define piSDA1(base)		pii2cSetSDA(base,1)
#define pii2cSendData(base,v)			pii2cSendByte(base,v)
#define pii2cSendSlaveAddr(base,v)		pii2cSendByte(base,v)
#define pii2cSendWordAddr(base,v)		pii2cSendByte(base,v)
#define piDelaySCL0() piclock_wait(tLOW)
#define piDelaySCL1() piclock_wait(tHIGH)
/*
 * prototype
 */
short pii2cGetSCL();
short pii2cGetSDA();
/*
 * i2c for Secondary Init
 */
/*
 * macros
 */
#define siSCL0_SDA0(base)		sii2cSetSCLSDA(base,0,0)
#define siSCL0_SDA1(base)		sii2cSetSCLSDA(base,0,1)
#define siSCL1_SDA0(base)		sii2cSetSCLSDA(base,1,0)
#define siSCL1_SDA1(base)		sii2cSetSCLSDA(base,1,1)
#define siSCL0(base)		sii2cSetSCL(base,0)
#define siSCL1(base)		sii2cSetSCL(base,1)
#define siSDA0(base)		sii2cSetSDA(base,0)
#define siSDA1(base)		sii2cSetSDA(base,1)
#define sii2cSendData(base,v)			sii2cSendByte(base,v)
#define sii2cSendSlaveAddr(base,v)		sii2cSendByte(base,v)
#define sii2cSendWordAddr(base,v)		sii2cSendByte(base,v)
#define siDelaySCL0() siclock_wait(tLOW)
#define siDelaySCL1() siclock_wait(tHIGH)
/*
 * prototype
 */
short sii2cGetSCL();
short sii2cGetSDA();
/*
 * i2c for Driver
 */
/*
 * macros
 */
#define drSCL0_SDA0(base)		dri2cSetSCLSDA(base,0,0)
#define drSCL0_SDA1(base)		dri2cSetSCLSDA(base,0,1)
#define drSCL1_SDA0(base)		dri2cSetSCLSDA(base,1,0)
#define drSCL1_SDA1(base)		dri2cSetSCLSDA(base,1,1)
#define drSCL0(base)		dri2cSetSCL(base,0)
#define drSCL1(base)		dri2cSetSCL(base,1)
#define drSDA0(base)		dri2cSetSDA(base,0)
#define drSDA1(base)		dri2cSetSDA(base,1)
#define dri2cSendData(base,v)			dri2cSendByte(base,v)
#define dri2cSendSlaveAddr(base,v)		dri2cSendByte(base,v)
#define dri2cSendWordAddr(base,v)		dri2cSendByte(base,v)
#define drDelaySCL0() drclock_wait(tLOW)
#define drDelaySCL1() drclock_wait(tHIGH)
/*
 * prototype
 */
short dri2cGetSCL();
short dri2cGetSDA();
/*****************************************************************************
 * program constants and macros
 *****************************************************************************/
#define	sRsrcBoard			1
#define	sTimingTableDir		0x0080
/* Timing Resource IDs */
#define	TIMING_ID_11x8		0x0080
#define	TIMING_ID_10x7_75	0x0081
#define	TIMING_ID_10x7_60	0x0082
#define	TIMING_ID_8x6		0x0083
#define	TIMING_ID_6x4		0x0084
#define	TIMING_ID_6x8		0x0085
#define	TIMING_ID_6x4ntsc	0x0086
#define	TIMING_ID_6x4ntscGL	0x0087
#define	TIMING_ID_7x5pal	0x0088
#define	TIMING_ID_7x5palGL	0x0089
#define	TIMING_ID_5x4ntsc	0x008A
#define	TIMING_ID_5x4ntscGL	0x008B
#define	TIMING_ID_6x5pal	0x008C
#define	TIMING_ID_6x5palGL	0x008D
	 
/* Functional sResource IDs */
#define	RES_ID_11x8			0x0080
#define	RES_ID_10x7_75		0x0081
#define	RES_ID_10x7_60		0x0082
#define	RES_ID_8x6			0x0083
#define	RES_ID_6x4			0x0084
#define	RES_ID_6x8			0x0085
#define	RES_ID_6x4ntsc		0x0086
#define	RES_ID_7x5pal		0x0087
#define	RES_ID_5x4ntsc		0x0088
#define	RES_ID_6x5pal		0x0089
#define	RES_ID_1152x870ext	0x008A
#define	RES_ID_1600x1200ext	0x008B
#define	RES_ID_2304x1740ext	0x008C
#define	RES_ID_3200x2400ext	0x008D
 
#define FirstResource		((unsigned short) 0x0083)
#define LastResource		((unsigned short) 0x008c)
#define FirstMonitor		((unsigned short) 0x0083)
#define LastMonitor			((unsigned short) 0x0089)
#define FirstExtended		((unsigned short) 0x008a)
#define LasttExtended		((unsigned short) 0x008c)
#define FirstNonInterlaced	((unsigned short) 0x0083)
#define LastNonInterlaced	((unsigned short) 0x0085)
#define FirstInterlaced		((unsigned short) 0x0086)
#define LastInterlaced		((unsigned short) 0x0089)
#define DefaultResource		((unsigned short) 0x0083)
#define NITEMS_VBLANK		((short) 128)		/* number of items to load on each vertical blanking */	
#define RES_APD				((unsigned short) 0x0085)
#define DEF_WIDTH		640
#define DEF_HEIGHT		480
#define DEF_ROWBYTES	832
/*
 * COLORS & INDEXES
 */
#define COLOR_ROPS			0x0000dfaaL
#define COLOR_ROPS_AA		0x0060d8b8L
#define COLOR_ROPS_90		0x0000c899L
#define COLOR_ROPS_50		0x00006f55L
#define COLOR_ROPS_GS		0x00d0d0d0L
#define COLOR_ROPS_GS_AA	0x00808080L
#define COLOR_SLOGAN		0x00c0c0c0L
#define COLOR_SLOGAN_AA		0x00707070L
#define COLOR_SLOGAN_50		0x00606060L
#define COLOR_VER			0x00606060L
#define COLOR_VER_AA		0x00d0d0d0L
#define COLOR_VER_50		0x00303030L
#define COLOR_VER_IZ		0x00c0c0c0L
#define COLOR_VER_AA_IZ		0x00707070L
#define COLOR_LTD			0x00eeeeeeL
#define COLOR_GRAY224		0x00e0e0e0
#define COLOR_RGBtech		0x003366cc
#define COLOR_BLACK			0x00000000L
#define COLOR_GRAY			0x00a0a0a0L
#define COLOR_RED			0x00ff0000L
#define COLOR_GREEN			0X0000ff00L
#define COLOR_BLUE			0x000000ffL
#define COLOR_WHITE			0x00ffffffL
#define COLOR_CYAN			0x0000ffffL
#define COLOR_YELLOW		0x00ffff00L
#define COLOR_MAGENTA		0x00ff00ffL
#define COLOR_GRAY_25		0x00404040L
#define COLOR_GRAY_50		0x00808080L
#define COLOR_GRAY_75		0x00c0c0c0L
#define COLOR_GRAY_90		0x00e6e6e6L
#define INDEX_ROPS			((short) 1)
#define INDEX_ROPS_AA		((short) 2)
#define INDEX_ROPS_90		((short) 3)
#define INDEX_ROPS_50		((short) 4)
#define INDEX_ROPS_GS		((short) 5)
#define INDEX_ROPS_GS_AA	((short) 6)
#define INDEX_SLOGAN		((short) 7)
#define INDEX_SLOGAN_AA		((short) 8)
#define INDEX_SLOGAN_50		((short) 9)
#define INDEX_VER			((short) 10)
#define INDEX_VER_AA		((short) 11)
#define INDEX_VER_50		((short) 12)
#define INDEX_VER_IZ		((short) 13)
#define INDEX_VER_AA_IZ		((short) 14)
#define INDEX_LTD			((short) 15)
#define INDEX_BLACK			((short) 0)
#define INDEX_GRAY			((short) 128)
#define INDEX_RED			((short) 129)
#define INDEX_GREEN			((short) 130)
#define INDEX_BLUE			((short) 131)
#define INDEX_GRAY_25		((short) 132)
#define INDEX_GRAY_50		((short) 133)
#define INDEX_GRAY_75		((short) 134)
#define INDEX_GRAY_90		((short) 135)
#define INDEX_WHITE			((short) 255)
/* pan directions */
#define PANDOWN		-1
#define PANUP		0
#define PANLEFT		-1
#define PANRIGHT	0
#define ADJUST_RIGHT	1
#define ADJUST_LEFT		-1
#define ADJUST_NONE		0
/*
 * Data Structures
 */
/* The structure of PRAM */
typedef char SignedByte;
typedef struct SPRAMRecord
{
	short boardID;
	SignedByte vendorUse1;
	SignedByte vendorUse2;
	SignedByte vendorUse3;
	SignedByte vendorUse4;
	SignedByte vendorUse5;
	SignedByte vendorUse6;
} SPRAMRecord, *SPRAMRecPtr;
    
enum ZoomDefs
{
  x1 = 0,
  x2,
  x4,
  x8
};
/*
 * BMHeader: bitmap header structure
 */
typedef struct BMHeader {
	long	filesize;
	char	filename[8];
	short	width;
	short	height;
	long	color;
	char	flags;
	char	flags2;
} BMHeader;
typedef char ThreeBytes[3];
typedef struct FileName {
	ThreeBytes	filler;
	char		c;
} FileName;
typedef struct BMHeader3 {		/* header for boards using byte lanes 3 */
	ThreeBytes	filler0;
	char		filesize0;
	ThreeBytes	filler1;
	char		filesize1;
	ThreeBytes	filler2;
	char		filesize2;
	ThreeBytes	filler3;
	char		filesize3;
	
	FileName	filename[8];
	ThreeBytes	filler12;
	char		widthHi;
	ThreeBytes	filler13;
	char		widthLo;
	ThreeBytes	filler14;
	char		heightHi;
	ThreeBytes	filler15;
	char		heightLo;
	ThreeBytes	filler16;
	char		color0;
	ThreeBytes	filler17;
	char		color1;
	ThreeBytes	filler18;
	char		color2;
	ThreeBytes	filler19;
	char		color3;
	ThreeBytes	filler20;
	char		flags;
	ThreeBytes	filler21;
	char		flags2;
} BMHeader3;
#define BITCOMPRESSED	0x80
#define BITDEPTH		0x07
	#define BITDEPTH1		0x00
	#define BITDEPTH2		0x01
	#define BITDEPTH4		0x02
	#define BITDEPTH8		0x03
	#define BITDEPTH16		0x04
	#define BITDEPTH24		0x05
/*
 * bit map header for the fonts
 */
typedef struct ASCIIHeader {
	long	filesize;				/* number of bytes including this header */
	char	filename[8];			/* file name */
	short	width;					/* width of the bit map */
	short	height;					/* height of the bit map */
	long	color;					/* color, can be override by the routine */
	char	flags;					/* bit7:	0 - regular
												1 - compressed
									   bit210:	000 - 1bit
									   			001 - 2bit
									   			010 - 4bit
									   			011 - 8bit
									   			100 - 16bit
									   			101 - 24bit */
	char	flags2;					/* bit7:	0 - regular bit map
												1 - font data */
	
	/*
	 * this part is particular to 'font'
	 */
	unsigned char	charWidths[64];			/* char width */
} ASCIIHeader;
typedef struct ASCIIHeader3 {
	ThreeBytes	filler0;
	char		filesize0;
	ThreeBytes	filler1;
	char		filesize1;
	ThreeBytes	filler2;
	char		filesize2;
	ThreeBytes	filler3;
	char		filesize3;
	
	FileName	filename[8];
	ThreeBytes	filler12;
	char		widthHi;
	ThreeBytes	filler13;
	char		widthLo;
	ThreeBytes	filler14;
	char		heightHi;
	ThreeBytes	filler15;
	char		heightLo;
	ThreeBytes	filler16;
	char		color0;
	ThreeBytes	filler17;
	char		color1;
	ThreeBytes	filler18;
	char		color2;
	ThreeBytes	filler19;
	char		color3;
	ThreeBytes	filler20;
	char		flags;
	ThreeBytes	filler21;
	char		flags2;
	/*
	 * this part is particular to 'font'
	 */
	unsigned long	charWidths[64];			/* char width */
} ASCIIHeader3;
/* Driver control parameter block for panning rectangles and speeds */
typedef struct panInfoParam
{
  ParamBlockHeader;
  short ioRefNum;
  short csCode;
  Rect fastRect, slowRect;
}panInfoParam, *panInfoParamPtr;
/* Driver control zoom & pan parameter block */
typedef struct zoomCtrlParam
{
  ParamBlockHeader;
  short ioRefNum;
  short csCode;
  short csParam[22];
} zoomCtrlParam, panCtrlParam;
enum panStatusTypes
{
  getPanRate = 8192,	/* GetPanRate()	get the scaling factor for the x/y panning rate.     */
  getSlow,				/* GetSlow()	get the slow panning speed. 			     */
  getFast,				/* GetFast()	get the fast panning speed. 			     */
  getMargin,			/* GetMargin()	get the width (in pixels) of the slow panning area.  */
  getZoom,				/* GetZoom()	get the current zoom state (1 = x1, 2 = x2, 3 = x4.) */
  getRects,				/* GetRects()	get the fast and slow panning rectangles and speeds. */
  getXY,				/* GetXY()      get the currentX and currentY screen positions.	     */
  getAll,				/* GetAll()	get all the various parameters			     */
  getPZMode,			/* GetPZMode()  get the pixel mode				     */
  getPZ					/* GetPZ()	get the pan & zoom enable flag			     */
};
enum panControlTypes
{
  zoomIn = 8192,		/* ZoomIn()	zoom in.     	 	     			     */
  zoomOut,				/* ZoomOut()	zoom out. 			     		     */
  panX,					/* PanX()	pan in the x direction. 	  		     */
  panY,					/* PanY()	pan in the y direction.  	   		     */
  panTo,				/* PanTo()	pan to x,y  			 		     */
  setRects, 			/* SetRects()	set the fast and slow panning rectangles. 	     */
  setXY,				/* SetXY()	set the X,Y coordinates (screen top left)	     */
  setSlow,				/* SetSlow()	set the slow panning rate			     */
  setFast,				/* SetFast()	set the fast panning rate			     */
  setBorder,			/* SetBorder()  set the panning border width			     */
  setPZ,				/* SetPZ()	enable panning and zooming			     */
};
#asm
; General equates
Slot          EQU    0	; Offset in SeBlock
SlotNum       EQU   49	; Offset in SpBlock
sResource     EQU   50  ; sResource ID Offset in spBlock
ExtDev        EQU   51	; External Device Offset in SpBlock
SpsResult     EQU    0	; SpsResult Offset in SpBlock
SpsPointer    EQU    4	; SpsPointer Offset in SpBlock
SReadPRAMRec  EQU   17	; routine selector to the Slot Manager
SPutPRAMRec   EQU   18 	; routine selector to the Slot Manager
SDeleteSRTRec EQU   49	; routine selector to the Slot Manager
AppleError    EQU    2  ; the number Apple uses to show a slot manager error
#endasm
/*еееее Energy Star (((((*/
#define	POWER_ON		0
#define	POWER_OFF		1
#define	POWER_STANDBY	2
typedef struct
{
	short		ves;	/* vertical end sync		*/
	short		vsb;	/* vertical start blank		*/
	short		veb;	/* vertical end blank		*/
	short		vtot;	/* vertical total			*/
	short		vil;	/* vertical interrupt line	*/
	short		hes;	/* horizontal end sync		*/
	short		hsb;	/* horizontal start blank	*/
	short		heb;	/* horizontal end blank		*/
	short		htot;	/* horizontal total			*/
} rgs14188_data;
#define	rgs14188_energy_saving_ves	0x000000FFL
#define	rgs14188_energy_saving_vsb	(rgs14188_energy_saving_ves - 15)
#define	rgs14188_energy_saving_vtot	(rgs14188_energy_saving_ves - 1)
#define	rgs14188_energy_saving_vil	0x00000000L
/*еееее Energy Star )))))*/
/*еееее Display Manager (((((*/
struct VDSwitchInfoRec {
	unsigned short				csMode;							/* (word) mode depth */
	unsigned long				csData;							/* (long) functional sResource of mode */
	unsigned short				csPage;							/* (word) page to switch in */
	Ptr							csBaseAddr;						/* (long) base address of page (return value) */
	unsigned long				csReserved;						/* (long) Reserved (set to 0) */
};
typedef struct VDSwitchInfoRec VDSwitchInfoRec;
typedef VDSwitchInfoRec *VDSwitchInfoPtr;
struct VDTimingInfoRec {
	unsigned long				csTimingMode;					/* LONGINT - (long) timing mode (a la InitGDevice) */
	unsigned long				csTimingReserved;				/* LONGINT - (long) reserved */
	unsigned long				csTimingFormat;					/* LONGINT - (long) what format is the timing info */
	unsigned long				csTimingData;					/* LONGINT - (long) data supplied by driver */
	unsigned long				csTimingFlags;					/* LONGINT - (long) mode within device */
};
typedef struct VDTimingInfoRec VDTimingInfoRec;
typedef VDTimingInfoRec *VDTimingInfoPtr;
struct VDDisplayConnectInfoRec {
	unsigned short				csDisplayType;					/* INTEGER - (word) Type of display connected */
	unsigned short				csConnectTagged;				/* INTEGER - (word) Display is currently "it" (tagged to identify component) */
	unsigned long				csConnectFlags;					/* LONGINT - (long) tell us about the connection */
	unsigned long				csDisplayComponent;				/* LONGINT - (long) if the card has a direct connection to the display, it returns the display component here (FUTURE) */
	unsigned long				csConnectReserved;				/* LONGINT - (long) reserved */
};
typedef struct VDDisplayConnectInfoRec VDDisplayConnectInfoRec;
typedef VDDisplayConnectInfoRec *VDDisplayConnectInfoPtr;
#define kDeclROMtables 'decl'
enum  {
	kAllModesValid				= 0,							/* All modes not trimmed by primary init are good close enough to try */
	kAllModesSafe				= 1,							/* All modes not trimmed by primary init are know to be safe */
	kReportsTagging				= 2,							/* Can detect tagged displays (to identify smart monitors) */
	kHasDirectConnect			= 3,							/* True implies that driver can talk directly to device (e.g. serial data link via sense lines) */
	kIsMonoDev					= 4,	/*jwh					/* this display does not support color */
	kUncertainConnect			= 5		/*jwh					/* there may not be a display; user must confirm some operations  */
};
/* csDisplayType values in VDDisplayConnectInfo */
enum  {
	kUnknownConnect				= 1,
	kPanelConnect				= 2,
	kFixedModeCRTConnect		= 3,
	kMultiModeCRT1Connect		= 4,							/* 320x200 maybe, 12" maybe, 13" (default), 16" certain, 19" maybe, 21" maybe */
	kMultiModeCRT2Connect		= 5,							/* 320x200 maybe, 12" maybe, 13" certain, 16" (default), 19" certain, 21" maybe */
	kMultiModeCRT3Connect		= 6,							/* 320x200 maybe, 12" maybe, 13" certain, 16" certain, 19" default, 21" certain */
	kMultiModeCRT4Connect		= 7,							/* Expansion to large multi mode (not yet used) */
	kModelessConnect			= 8								/* Expansion to modeless model (not yet used) */
};
enum  {
/*	kModeSafe					= 0,							/*  This mode does not need confirmation */
/*	kModeDefault				= 1								/* This is the default mode for this type of connection */
	kModeValid					= 0,								/* This is the default mode for this type of connection */
	kModeSafe					= 1,							/*  This mode does not need confirmation */
	kModeDefault				= 2								/* This is the default mode for this type of connection */
};
/*еееее Display Manager )))))*/
/* Gamma Data struct */
typedef struct GammaData
{
	unsigned char gRTable[256];
	unsigned char gGTable[256];
	unsigned char gBTable[256];
} GammaData, *GammaDataPtr;
/* Gamma Table struct */
typedef struct GammaTable
{
	short	gVersion;
	short	gType;
	short	gFormulaSize;
	short	gChanCnt;
	short	gDataCnt;
	short	gDataWidth;
	/*  char gFormulaData[0];	/*gFormulaData[????]; Variable size array so not included in struct. */
	GammaData gData;
} GammaTable, *GammaTablePtr;
/* Gamma Record struct */
typedef struct VDGammaRecord
{
	GammaTablePtr	csGTablePtr;
} VDGammaRecord, *VDGamRecPtr;
/* Default resolution mode struct */
typedef struct VDDefaultInfo
{
	char csMode;
} VDDefaultInfo, *VDDefaultInfoPtr;
/*еееее Energy Star (((((*/
typedef unsigned char	*VDFlagPtr;
/*еееее Energy Star )))))*/
typedef struct mystorage /* mode */
{
	unsigned char	clut[768];		/* lut copy wouldn't be required if Bt-478 were really dual ported ???? */
	SlotIntQElement	*myslotqeleptr;	/* saved on open for use in closing */
	unsigned char	*myintrptcode;	/* pointer to my interrupt code */
	unsigned short	bwmapping;		/* gray mapping flag; 0 = off, 1 = on */
	unsigned short	newmode;		/* semaphore for SetGamma to know if called between SetMode and GrayPage */
	unsigned short	mode;			/* current video mode (bit depth) */
	unsigned short	pages;
	unsigned short	zoom;
	unsigned short	screensize;
	unsigned long	screenbase;		/* frame buffer base address */
	unsigned short	intflag;		/* interrupts enabled flag; 0 = off, 1 = on */
	GammaTable		*mygammaptr;	/* pointer to my gamma table */
	Ptr             lutBuffer;      /* Buffer for setlut() */
	
	short			slot;			/* Slot and driver refNum of the Colorboard 108+				*/
	short			refNum;
	short			currentRate;	/* The proportional value for scaling x/y pan rates 			*/
	short			currentZoom;	/* Zoom state: 1 = 1X, 2 = 2X, 3 = 4X 							*/
	short			fastSpeed;		/* Fast multiplier for the pan rate 							*/
	short			slowSpeed;		/* Slow multiplier for the pan rate 							*/
	short			currentX;		/* The value in the pan register 								*/
	short			currentY;		/* Aggregate number from the two y-registers 					*/
	short			xSize;			/* desktop size x												*/
	short			ySize;			/* desktop size y												*/
	short			theMode;		/* The pixel depth: 0 = 1 bit, 1 = 2 bit, 2 = 4 bit, 3 = 8 bit 	*/
	short			border;			/* The border constant which defines the panRect 				*/
	Rect			theRect;		/* The rect of our GDevice										*/
	Rect			panRect;		/* The border of the active panning area						*/
	Rect			currentScreen;	/* The active screen rect 										*/
	Boolean			enablePZ;		/* True if pan & zoom are enabled, false otherwise 				*/
	Boolean			zCenter;		/* True if screen centered, false if mouse centered zoom 		*/
	Boolean			enableVD;		/* True if the Extended DeskTop option is in effect, else false */
	short			xResolution;	/* screen size x												*/
	short			yResolution;	/* screen size y												*/
	unsigned short	pip_reserved;	/* flag set if PIP reserved by driver call */
	unsigned long	disp_pitch;		/* display pitch in Venus chip */
	unsigned long	base;			/* base address */
/*еееее Energy Star (((((*/
	char			sync_state;		/* 0 = enabled, 1 = h or v disabled, 2 = h and v disabled */
	rgs14188_data	save_timing;	/* for restoring timing after energy saving */
/*еееее Energy Star )))))*/
	short			desk_sRsrcId;
	short			monitor_sRsrcId;
} mystorage, *mystoragePtr;
  
#asm
;*************************************************************
; SlotManager equates
	include	"azTraps.asm"
	include	"azSlotEqu.asm"
;*************************************************************
#endasm
#include "24MxsRes.c"
/*
 * prototype
 */
unsigned long pi_get_rgs();
#asm
;******************************************************************************
;  Primary Init Code Block
;******************************************************************************
primaryinit even
; Header information
    DC.L  endprimaryinit-primaryinit        ; Length of seBlock
    DC.B  2                     ; Revision Level 2 (The Slot Manager REQUIRES this to be 2!)
    DC.B  2                     ; CPU ID 2 (68020)
    DC.W  0                     ; Reserved
    DC.L  4                     ; Code Offset 4  (In other words, next!)
;
; PRIMARY INIT CODE
;
; On Entry:  A0 -> Slot Manager seBlock
;
	MOVEM.L A0-A5/D0-D7,-(SP)  	; save nearly all registers	
	MOVE.L	A0,-(SP)			; push SeBlock pointer
	JSR		_cPrimaryInit		; call our c routine
	LEA		4(SP),SP			; repair stack caused by c call
	MOVEM.L (SP)+,A0-A5/D0-D7	; Restore nearly all registers
	RTS
#endasm
#if MAKINGLTD
#include "MessageMxTVw.c"
#endif
/*
 * This is the C version of the primary init
 */
cPrimaryInit(SeBlkPtr)
SEBlock	*SeBlkPtr;									/* pointer to SeBlock passed to us */
{
	register unsigned short	slot;					/* slot number */
	register unsigned long	base;					/* address of our frame buffer */
	register unsigned short	pram5;					/* parameter ram 5 */
	register unsigned short	pram6;					/* parameter ram 6 */
	unsigned short			pram5save;				/* parameter ram 5 save */
	unsigned short			pram6save;				/* parameter ram 6 save */
	char					is24bit;
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	SpBlock					*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	
	/*
	 * set status to 1 (success)
	 * get slot number
	 * contruct 32 bit address of our frame buffer
	 * set up sp block slot number and ext device to be used in all slot manager calls
	 */
	
	pisVersion(SpPtr);
	if(SpPtr->spResult < 2)	/* QD32 must be in ROM or we don't fly! */
	{
		SeBlkPtr->seStatus = -1;
		return;
	}
	else
	{
		SeBlkPtr->seStatus = 1;
	}
	slot = SeBlkPtr->seSlot;
	base = 0xf0000000 | (((unsigned long) slot) << 24L);
	/*
	 * set the board to fat slot mode, also set the correct address mode
	 * this needs to be done before accessing the board (including ee prom)
	 */
	piSetFatSkinny(base, (short) FATMODE);
	
	/*
	 * 1. Get monitor type and desktop size from EEProm
	 * 2. Adjust the number and check consistency
	 * 3. if there is an inconsistency, modify EEPROM
	 * 4. store the numbers in p-ram
	 *
	 * the EEPROM always stores 0x8?
	 * the p-ram can store 0x9? in pram6
	 */	
	piSetupEEPROM(slot);	
	piGetEEPROM56(slot, &pram5save, &pram6save);	
	pram5save &= 0x008f;
	pram6save &= 0x008f;
	pram5 = pram5save;
	pram6 = pram6save;
	
#if MAKING24MXI
		if((pram5 < FirstMonitor) || (pram5 > LastNonInterlaced)) {
			pram5 = DefaultResource;
		}
		
		if((pram6 < FirstResource) || (pram6 > LastResource)) {
			pram6 = pram5;
		}
	
		if((pram6 <= LastMonitor) && (pram6 != pram5)) {
			pram6 = pram5;
		}
#else
		if((pram5 < FirstMonitor) || (pram5 > LastMonitor)) {
			pram5 = DefaultResource;
		}
		
		if((pram6 < FirstResource) || (pram6 > LastResource)) {
			pram6 = pram5;
		}
	
		if((pram6 <= LastMonitor) && (pram6 != pram5)) {
			pram6 = pram5;
		}
#endif
	if((pram5 != pram5save) || (pram6 != pram6save)) {
		piSetEEPROM56(slot, pram5, pram6);
	}
	
	pram6 |= 0x0090;
	piSetPRAM56(slot, pram5, pram6);
	
	/*
	 * delete all other resources except the one selected
	 */
	piDeleteExcept(slot, pram6);
	/*
	 * init the board
	 * draw color cube, logo, rom version
	 */
	if(!piAUXRunning()) {
		piSetFatSkinny(base, (short) FATMODE);
		piInitScrn(base, pram5, pram6, 24);
		piPutLogo24(base, pram5);
		pi_show(base);
		/* 
		 * wait for 2 seconds
		 * if control key pressed, pause
		 */
	
		piwaitnms(2000);
		
		/*
		 * change to skinny mode
		 */
		piSetFatSkinny(base, (short) SKINNYMODE);
	}
	else {	
		pi_show(base);
	}
}
/*
 * AUXRunning()
 *
 * returns true(non-zero) if AUX is running, otherwise 0
 */
piAUXRunning()
{
	register short	flags;
	
	flags  = *((short *) (0x0b22));
	return (flags & (0x0200));
}
 
#if MAKINGROPS
/*
 * piColorCube()
 */
piColorCube(base, pram5)
long	base;
short	pram5;
{
/*
#define	S_WIDTH		640
#define	S_HEIGHT	480
#define	HEXSIZE		140
#define	HEXMAX		(HEXSIZE-1)
*/
#define	TOTAL_SHADES	256
#define true_shade(shade)	((TOTAL_SHADES * shade) / HEXSIZE)
	short	S_WIDTH;
	short	S_HEIGHT;
	short	HEXSIZE;
	short	HEXMAX;
	register unsigned long	i, j;
	unsigned long			rowmax, midpoint;
	unsigned long			red, green, blue;
	register unsigned long	*dest;
	unsigned char			mmu_mode;
	register unsigned long	color;
	register unsigned long	memWidth;
	short					dummy;
	/*
	 * determine the width and height
	 */
	piGetWH(pram5, &S_WIDTH, &S_HEIGHT);
	switch(pram5 & 0x000f) {
		case 0x00:
		case 0x01:
		case 0x02:
				HEXSIZE = 180;
				break;
		case 0x03:
				HEXSIZE = 140;
				break;
		case 0x04:
		case 0x06:
		case 0x05:
		case 0x07:
				HEXSIZE = 128;
				break;
		case 0x08:
				HEXSIZE = 120;
				break;
		case 0x09:
				HEXSIZE = 128;
				break;
		default:
				HEXSIZE = 128;
				break;
	}
	HEXMAX = (HEXSIZE-1);
	
	memWidth = pi_get_disp_pitch(base) * 4;
	
	mmu_mode = true32b;			/* prepare to change to 32 bit mode */
	piSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	
/*	SET_FATMODE(base, dummy); */
	/* Background color */
	dest = (unsigned long *)base;
	for(i=0; i<S_HEIGHT; i++)
	{
		color = ((S_HEIGHT-1 - i)*255L) / ((long) S_HEIGHT-1);
		color = (color << 16) | (color << 8) | color;
		j = S_WIDTH;
		while(j--) {
			*dest++ = color;
		}
		dest += memWidth-S_WIDTH;
	}
	dest = (unsigned long *)base;
	dest += ((S_HEIGHT*9/16 - HEXSIZE) * memWidth);
	dest += S_WIDTH/2;
	/* Section 1 is 1/4 of display */
	for(i=0; i<HEXSIZE/2; i++) /* For each Row */
	{
		red =   0;
		green = 2*i;
		blue =  HEXMAX;
		rowmax = 4*i;
		for(j=0; j<=rowmax; j++) /* For each column */
		{
			*dest++ = true_shade(red)<<16 | true_shade(green)<<8 | true_shade(blue);
			/* Red */
			 if(j&1) red++;
			/* Green */
			if((j&1)==0) green--;
			/* Blue */
		}
		dest += memWidth-j-2;
	}
	dest += 1;
	/* Section 2 is 1/4 of display */
	for(i=0; i<HEXSIZE/2; i++) /* For each Row */
	{
		red =   0;
		green = HEXMAX;
		blue =  HEXMAX-i;
		for(j=0; j<2*HEXSIZE-1; j++) /* For each column */
		{
			*dest++ = true_shade(red)<<16 | true_shade(green)<<8 | true_shade(blue);
			/* Red */
			if(j<i*2) red++;
			else if(j<2*(HEXMAX-i)) if(j&1) red++;
			/* Green */
			if(j>=2*(HEXMAX-i)) green--;
			else if(j>=i*2) if(j&1) green--;
			/* Blue */
			if(j<i*2)
				if(j&1) blue++;
			if(j>=2*(HEXMAX-i))
				if(j&1) blue--;
		}
		dest += memWidth-(2*HEXSIZE-1);
	}
	/* Section 3 is 1/4 of display */
	for(i=0; i<HEXSIZE/2; i++) /* For each Row */
	{
		red =   0;
		green = HEXMAX;
		blue =  HEXMAX/2-i;
		for(j=0; j<2*HEXSIZE-1; j++) /* For each column */
		{
			*dest++ = true_shade(red)<<16 | true_shade(green)<<8 | true_shade(blue);
			/* Red */
			if(j<HEXMAX) red++;
			/* Green */
			if(j>HEXMAX) green--;
			/* Blue */
			if(j<HEXMAX)
				if(j&1) blue++;
			if(j>HEXMAX)
				if(j&1) blue--;
		}
		dest += memWidth-(2*HEXSIZE-1);
	}
	dest += 2;
	/* Section 4 is 1/4 of display */
	for(i=HEXMAX/2; i>0; i--) /* For each Row */
	{
		red =   2*(1+HEXMAX/2-i);
		green = HEXMAX;
		blue =  0;
		rowmax = 4*i-1;
		midpoint = rowmax/2;
		for(j=0; j<rowmax; j++) /* For each column */
		{
			*dest++ = true_shade(red)<<16 | true_shade(green)<<8 | true_shade(blue);
			/* Red */
			if(j<midpoint) red++;
			/* Green */
			if(j>midpoint) green--;
			/* Blue */
			if(j<midpoint)
				if(j&1) blue++;
			if(j>midpoint)
				if(j&1) blue--;
		}
		dest += memWidth-j+2;
	}
	piSwapMMUMode(&mmu_mode);
}
#endif
/*
 * DeleteExcept(slot, ResourceNumber) Deletes or Disables all but one sResource
 */
piDeleteExcept(slot, ResourceNumber)
register short	slot;			/* our sp block pointer to make the slot manager call */
register unsigned short	ResourceNumber;
{
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	register unsigned short	start;
	register unsigned short	end;
	register unsigned short	i;
	register unsigned short	mask;
	
	SpPtr->spSlot = slot;
	SpPtr->spExtDev = 0;
	SpPtr->spsPointer = 0;		/* not ram sRsrc */
	SpPtr->spRefNum = 0;		/* dont update dCtlDevBase */
	for(mask = 0x0090; mask <= 0x00a0; mask+=0x0010)
	{
		start = (FirstResource & 0x000f) | mask;
		end = (LastResource & 0x000f) | mask;
		for(i = start; i <= end; i++)
		{
			SpPtr->spID = i;
			if ((ResourceNumber & 0xF0) != mask)	/* if not in the chosen group, delete it */
			{
/*	myDebugStr("\PDeleteExcept - delete"); */
				piSDeleteSRTRec(SpPtr);
			}
			else if (i != ResourceNumber)	/* if not the chosen one, disable it */
			{
/*	myDebugStr("\PDeleteExcept - disable"); */
				SpPtr->spStackPtr = 1;		/* actually SpPtr->spParamData, 1 = disable */
				piSetSRsrcState(SpPtr);
			}
		}
	}
}
	
/*
 * pi_draw_bm24()
 */
pi_draw_bm24(base, name, xcenter, ycenter, color)
unsigned long	base;
char			*name;
short			xcenter;
short			ycenter;
unsigned long	color;
{
	register unsigned long	*to;
	register char			*bm;
	register short			k;
	register char			c;
	register short			j;
	register short			i;
	register short			len;
	register short			count;
	short					xstart, ystart;
	short					p_width, p_height;
	short					p_width8;
	char					mmu_mode;
	BMHeader3				*headerptr;
	unsigned long			memWidth;
	short					dummy;
	
	if(!piFindBitmap(base, name, &headerptr))
		return;
		
	mmu_mode = 1;	/* 32 bit mode */
	piSwapMMUMode(&mmu_mode);
  		
	memWidth = pi_get_disp_pitch(base) * 4;
	bm = (char *)headerptr + sizeof(BMHeader3);
	if(color < 0) {
		color = (((long) (headerptr->color0) << 24L) & 0xff000000L) | 
				(((long) (headerptr->color1) << 16L) & 0x00ff0000L) |
				(((long) (headerptr->color2) <<  8L) & 0x0000ff00L) |
				((long) (headerptr->color3) & 0x000000ffL);
	}
	p_width = ((long) headerptr->widthHi << 8L) | ((long) headerptr->widthLo & 0x00ff);
	p_height = ((long) headerptr->heightHi << 8L) | ((long) headerptr->heightLo & 0x00ff);
	p_width8 = p_width/8;
	
/*	SET_FATMODE(base, dummy); */
  
	/*
	 * calculate starting point
	 */
	if((xcenter == 0) && (ycenter == 0)) {
		xstart = DEF_WIDTH/2 - p_width/2;
		ystart = DEF_HEIGHT/3 - p_height/2;
	}
	else {
		xstart = xcenter - p_width/2;
		ystart = ycenter - p_height/2;
	}
	if(xstart < 0)
		xstart = 0;
	if(ystart < 0)
		ystart = 0;
	
	/*
	 * draw the bitmap
	 */
	to = (unsigned long *)(base);
	to += (ystart * memWidth + xstart);
	if(!(headerptr->flags & BITCOMPRESSED)) {
		bm += 3;	/* because we are using byte lanes 3 */
		i = p_height;
		while(i--)
		{
			j = p_width8;
			while(j--)
			{
				if (c = *bm)
				{
					k = 8;
					while(k--)
					{
						if (c & 0x80)
							*to++ = color;
						else
							to++;
						c <<= 1;
					}
				}
				else {
					to+=8;
				}
				
				bm += 4;
			}
			to += (memWidth-p_width);
		}
	}
	else {							/* compressed bit map */
		bm += 3;	/* because we are using byte lanes 3 */
		for (i=0;i<p_height;i++) {
			count = p_width/8;
			while(count > 0) {
				len = (*bm & 0x00ff);
				bm += 4;
				if(len <= 0x7f) {
					count -= len;
					while(len--) {
						c = *bm;
						for(k = 0; k < 8; k++) {
							if(c < 0)
								*to++ = color;
							else
								to++;
							
							c <<= 1;
						}
					}
					bm += 4;
				}
				else {
					len -= 0x7f;
					count -= len;
					while(len--) {
						c = *bm;
						bm += 4;
						for(k = 0; k < 8; k++) {
							if(c < 0)
								*to++ = color;
							else
								to++;
							
							c <<= 1;
						}
					}
				}
			}
			to += (memWidth-p_width);
		}
	}
  
	piSwapMMUMode(&mmu_mode);
}
#if MAKING24MXI
/*
 * pi_draw_bm8()
 */
pi_draw_bm8(base, name, xcenter, ycenter, color, index)
unsigned long	base;
char			*name;
short			xcenter;
short			ycenter;
unsigned long	color;
short			index;
{
}
#endif
#if MAKINGIZUMIYA
/*
 * pi_draw_bm8Gc()
 */
pi_draw_bm8Gc(base, name, xcenter, ycenter, color)
unsigned long	base;
char			*name;
short			xcenter;
short			ycenter;
unsigned long	color;
{
	register unsigned long	*to;
	register char			*bm;
	register short			k;
	register char			c;
	register short			j;
	register short			i;
	register short			count;
	register short			len;
	short					xstart, ystart;
	short					p_width, p_height;
	short					p_width8;
	char					mmu_mode;
	BMHeader3				*headerptr;
	unsigned long			memWidth;
	short					dummy;
		
	if(!piFindBitmap(base, name, &headerptr))
		return;
		
	mmu_mode = 1;	/* 32 bit mode */
	piSwapMMUMode(&mmu_mode);
  		
	memWidth = pi_get_disp_pitch(base) * 4;
	bm = (char *)headerptr + sizeof(BMHeader3);
	p_width = ((long) headerptr->widthHi << 8L) | ((long) headerptr->widthLo & 0x00ff);
	p_height = ((long) headerptr->heightHi << 8L) | ((long) headerptr->heightLo & 0x00ff);
	p_width8 = p_width/8;
	
/*	SET_FATMODE(base, dummy); */
  
	/*
	 * calculate starting point
	 */
	if((xcenter == 0) && (ycenter == 0)) {
		xstart = DEF_WIDTH/2 - p_width/2;
		ystart = DEF_HEIGHT/3 - p_height/2;
	}
	else {
		xstart = xcenter - p_width/2;
		ystart = ycenter - p_height/2;
	}
	if(xstart < 0)
		xstart = 0;
	if(ystart < 0)
		ystart = 0;
	
	/*
	 * draw the bitmap
	 */
	to = (unsigned long *)(base);
	to += (ystart * memWidth + xstart);
 	bm += 3;	/* because we are using byte lanes 3 */
	i = p_height;
	while(i--)
	{
		count = p_width;
		while(count > 0) {
			len = (*bm & 0x00ff);
			bm += 4;
			if(len <= 0x7f) {
				count -= len;
				c = *bm;
				bm += 4;
				while(len--) {
					*to++ = (c << 8L) & 0x0000ff00L;
				}
			}
			else {
				len -= 0x7f;
				count -= len;
				while(len--) {
					c = *bm;
					bm += 4;
					*to++ = (c << 8L) & 0x0000ff00L;
				}
			}
		}
		to += (memWidth-p_width);
	}
  
	piSwapMMUMode(&mmu_mode);
}
#endif
/*
 * piEraseScrn24()
 */
piEraseScrn24(base, pram5, color)
unsigned long	base;
short			pram5;
unsigned long	color;
{
	register short			i;
	register short			j;
	register unsigned long	*to;
	short					width;
	short					height;
	register unsigned long	memWidth;
	char					mmu_mode;
	piGetWH(pram5, &width, &height);
	memWidth = pi_get_disp_pitch(base) * 4;
	/*
	 * blank the screen
	 */
	mmu_mode = 1;	/* 32 bit mode */
	piSwapMMUMode(&mmu_mode);
    
	to = (unsigned long *) (base);
	i = height;
	while(i--) {
		j = width;
		while(j--) {
			*to++ = color;
		}
		to += memWidth - width;
	}
	piSwapMMUMode(&mmu_mode);
}
#if MAKING24MXI
/*
 * piEraseScrn8()
 */
piEraseScrn8(base, pram5, color, index)
unsigned long	base;
short			pram5;
unsigned long	color;
short			index;
{
}
#endif
/*
 * piFindBitmap(base, name, headeraddr)
 */
short piFindBitmap(base, name, headeraddr)
char			*base;
char			*name;
BMHeader3		**headeraddr;
{
	register BMHeader3	*ptr;
	long				size;
	short				rc;
	char				mmu_mode;
	short				dummy;
	
	/**** use 0x00fc0000 when we using 512K rom */
	/**** use 0x00fe0000 when we using 256K rom */
	ptr = (BMHeader3 *) (base + 0x00fc0000);
	mmu_mode = 1;	/* 32 bit mode */
	piSwapMMUMode(&mmu_mode);
  	
/*	SET_FATMODE(base, dummy); */
	rc = 0;
	while( size = (((long) (ptr->filesize0) << 24L) & 0xff000000L) | 
				  (((long) (ptr->filesize1) << 16L) & 0x00ff0000L) |
				  (((long) (ptr->filesize2) <<  8L) & 0x0000ff00L) |
				  ((long) (ptr->filesize3) & 0x000000ffL)) {
		if ((name[0] == ptr->filename[0].c) &&
			(name[1] == ptr->filename[1].c) &&
			(name[2] == ptr->filename[2].c) &&
			(name[3] == ptr->filename[3].c) &&
			(name[4] == ptr->filename[4].c) &&
			(name[5] == ptr->filename[5].c) &&
			(name[6] == ptr->filename[6].c) &&
			(name[7] == ptr->filename[7].c)
		   ) {
			*headeraddr = ptr;
			rc = 1;
			break;
		}
		else {
			ptr = (BMHeader3 *) ((unsigned long) ptr + size * 4);		/* *4 because we use byte lane 3 */
		}
	}
	piSwapMMUMode(&mmu_mode);
	return rc;
}
/*
 * get 14188 registers
 */
unsigned long pi_get_rgs(base, reg, bytes)
long	base;
short	reg;
register short	bytes;
{
	unsigned long	val;
	register unsigned char	*here;
	register unsigned long	*there;
	unsigned char	mmu_mode;
	
	val = 0;
	here = ((unsigned char *)&val) + 3;
	/**** here = (unsigned char *) StripAddress(here); */
	there = (unsigned long *)(base + RGS14188) + reg;
	switch(bytes)
	{
		case 2:	there += 1;
			break;
		case 3:
		case 4:	there += 3;
			break;
	}
	mmu_mode = true32b;		/* Prepare to change to 32 bit mode */
	piSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	while(bytes-- > 0)
		*here-- = *there--;
	piSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
	return val;
}
/*
 * GetEEPROM56()
 */
piGetEEPROM56(slot, ptr5, ptr6)
short	slot;
short	*ptr5;
short	*ptr6;
{
#if MAKING24MXI
	long	*eep;
	short	w;
	
	eep = (long *) ((unsigned long) devBase(slot) | EEPROM);
	w = pieeReadWord(eep, (short) 3);
	*ptr5 = (w >> 8) & 0x00ff;
	*ptr6 = w & 0x00ff;
#else
	unsigned long	base;
	
	base = ((unsigned long) devBase(slot));
	*ptr5 = pii2cReadByte(base,6);
	*ptr6 = pii2cReadByte(base,7);
#endif
}
	
/*
 * GetPRAM()
 */
piGetPRAM(slot, PRAMPtr)
short					slot;
register SPRAMRecord	*PRAMPtr;		/* where to store the PRAM record */
{
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	/* set up parameters for slot manager call */
	SpPtr->spSlot = slot;	
	SpPtr->spExtDev = 0;	
	SpPtr->spResult = (unsigned long) PRAMPtr;
	piSReadPRAMRec(SpPtr);
}
/*
 * piGetWH()
 */
piGetWH(resNum, width, height)
register short	resNum;
register short	*width;
register short	*height;
{
	
	/*
	 * determine the width and height
	 */
	switch(resNum & 0x000f) {
		case 0x00:
				*width = 1152;
				*height = 870;
				break;
		case 0x01:
		case 0x02:
				*width = 1024;
				*height = 768;
				break;
		case 0x03:
				*width = 832;
				*height = 624;
				break;
		case 0x04:
		case 0x06:
				*width = 640;
				*height = 480;
				break;
		case 0x05:
				*width = 640;
				*height = 870;
				break;
		case 0x07:
				*width = 768;
				*height = 576;
				break;
		case 0x08:
				*width = 576;
				*height = 432;
				break;
		case 0x09:
				*width = 684;
				*height = 512;
				break;
		case 0x0a:
				*width = 1152;
				*height = 870;
				break;
		case 0x0b:
				*width = 1600;
				*height = 1200;
				break;
		case 0x0c:
				*width = 2304;
				*height = 1740;
				break;
		case 0x0d:
				*width = 3200;
				*height = 2400;
				break;
	}
}
/*
 * piInitScrn(base, pram5, pram6, bitdepth)
 *
 * 1. force fat slot mode on board
 * 2. set appropriate address mode (Mxi or MxTV
 * 3. init DAC
 * 4. load timming table
 * 5. enable
 */
piInitScrn(base, pram5, pram6, bitdepth)
register unsigned long	base;
register short	pram5;
short			pram6;
short			bitdepth;
{
	register unsigned long	*rgs14188_ptr;
	register unsigned long	*dac_ptr;
	char					mmu_mode;
	register short			i;
	
	rgs14188_ptr = (unsigned long *)(base + RGS14188);
	
	mmu_mode = true32b;		/* prepare to change to 32 bit mode */
	piSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	
	/*
	 * Initialize the BT-473 DAC
	 */
	dac_ptr = (unsigned long *)(base + BT473_MASK);
	*dac_ptr = 0x00;		/* Read Mask off - force address 0 */
/*	*dac_ptr = 0xFF;		/* Read Mask on for debug */
	dac_ptr = (unsigned long *)(base + BT473_COMMAND);
/*
/*	if(((pram5 & 0x008f) == 0x0087) || ((pram5 & 0x008f) == 0x0089))
/*		*dac_ptr = 0x33;		/* Command Register for other PAL (0 IRE) */
/*	else
*/
		*dac_ptr = 0x32;		/* Command Register for other than PAL (7.5 IRE) */
	/*
	 * Create linear-ramp lookup tables for all 4 DACs (xxrrggbb)
	 */
	*((unsigned long *)(base + BT473_P_ADDR)) = 0x00000000;   /* Address $0 */
	dac_ptr = (unsigned long *)(base + BT473_PALETTE);
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	
	if(bitdepth == 24) {
		for(i=0; i<256; i++)
		{
			*dac_ptr = i;   /* LUT Color for red */
			*dac_ptr = i;   /* LUT Color for green */
			*dac_ptr = i;   /* LUT Color for blue */
		}
	}
	else {
		for(i=0; i<256; i++)
		{
			*dac_ptr = 0;   /* LUT Color for red */
			*dac_ptr = 0;   /* LUT Color for green */
			*dac_ptr = 0;   /* LUT Color for blue */
		}
	}
	piSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
  
	/*
	 * Send Initialization Table out to RGS14188
	 */
	pi_load_timingtable(base, pram5);
	mmu_mode = true32b;		/* prepare to change to 32 bit mode */
	piSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	
	if(bitdepth == 8) {
		rgs14188_ptr[gio_reg_Lo] &= 0xBF;		/* BAC reset on */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		rgs14188_ptr[gio_reg_Hi] &= (long)0xF0;	/* force 1-8 bit modes (bit 4,5 = 0) and Reset (bit 7 lo) */
		rgs14188_ptr[gio_reg_Hi] |= 0x0C;		/* set 8 bit mode */
		dac_ptr = (unsigned long *)(base + BT473_COMMAND);
		*dac_ptr |= 0x01;					/* Command Register for other than PAL (7.5 IRE) */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		rgs14188_ptr[gio_reg_Lo] |= 0x40;		/* BAC reset off */
	}
	/*
	 * Turn on refresh, transfer enable, and sync
	 */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	rgs14188_ptr[control_1] |= 0x91;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	rgs14188_ptr[control_3] |= 0x72;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	rgs14188_ptr[control_1] |= 0xB1;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
#if MAKING24MXTV
	/* non-interlaced && 1x zoom && non-extended needs to have refresh off */
	if(((pram5 & 0x8f) < FirstInterlaced) && ((pram6 & 0x8f) < FirstExtended))
	 	REFRESH_OFF(base);
#endif
		
	rgs14188_ptr[gio_reg_Lo] |= soft_reset_off;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	
	piSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
}
/*
 * load_timingtable()
 *
 * 14 Tables of 48 bytes each, corresponding to the
 * registers on the RGS14188.
 * X Table 80	1152 X 870 75Hz
 * X Table 81	1024 X 768 75Hz
 * X Table 82	1024 X 768 60Hz
 *  Table 83	832 X 624
 *  Table 84	640 X 480 67hz
 * X Table 85	640 X 870
 *  Table 86	640 X 480 NTSC
 *  Table 87	640 X 480 NTSC GenLock
 *  Table 88	768 X 576 PAL
 *  Table 89	768 X 576 PAL GenLock
 *  Table 8A	576 X 432 NTSC
 *  Table 8B	576 X 432 NTSC GenLock
 *  Table 8C	684 X 512 PAL underscan
 *  Table 8D	684 X 512 PAL Genlock underscan
 */
pi_load_timingtable(base, resNum)
unsigned long	base;
register short		resNum;
{
	register unsigned long	*rgs14188_ptr;
	register unsigned long	*table_ptr;
	register short			i;
	unsigned short			timingNum;
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	char					mmu_mode;
	short					GenLock;
	
	mmu_mode = true32b;		/* prepare to change to 32 bit mode */
	piSwapMMUMode(&mmu_mode);
	GenLock = ISGENLOCK(base);
	piSwapMMUMode(&mmu_mode);
	rgs14188_ptr = (unsigned long *)(base + RGS14188);
	switch(resNum & 0x008F)
	{
		case RES_ID_11x8:
			timingNum = TIMING_ID_11x8;
			break;
		case RES_ID_10x7_75:
			timingNum = TIMING_ID_10x7_75;
			break;
		case RES_ID_10x7_60:
			timingNum = TIMING_ID_10x7_60;
			break;
		case RES_ID_8x6:
			timingNum = TIMING_ID_8x6;
			break;
		case RES_ID_6x4:
			timingNum = TIMING_ID_6x4;
			break;
		case RES_ID_6x8:
			timingNum = TIMING_ID_6x8;
			break;
#if MAKING24MXTV	
		case RES_ID_6x4ntsc:
			if(!GenLock)
				timingNum = TIMING_ID_6x4ntsc;
			else
				timingNum = TIMING_ID_6x4ntscGL;
			break;
		case RES_ID_7x5pal:
			if(!GenLock)
				timingNum = TIMING_ID_7x5pal;
			else
				timingNum = TIMING_ID_7x5palGL;
			break;
		case RES_ID_5x4ntsc:
			if(!GenLock)
				timingNum = TIMING_ID_5x4ntsc;
			else
				timingNum = TIMING_ID_5x4ntscGL;
			break;
		case RES_ID_6x5pal:
			if(!GenLock)
				timingNum = TIMING_ID_6x5pal;
			else
				timingNum = TIMING_ID_6x5palGL;
			break;
#endif
	}
	
	/* Find parameter resource */
	SpPtr->spSlot = (base >> 24) & 0x0F;
	SpPtr->spExtDev = 0;
	SpPtr->spID = sRsrcBoard;		/* Find Board Resource */
	piSRsrcInfo(SpPtr);
	SpPtr->spID = sTimingTableDir;	/* Find Resoulution Directory */
	piSFindStruct(SpPtr);
	SpPtr->spID = timingNum;			/* Find Parameters */
	piSFindStruct(SpPtr);
	
	table_ptr = (unsigned long *)(SpPtr->spsPointer + 16 - 3); /* skip count and adjust byte lane for long access */
		
	mmu_mode = true32b;		/* prepare to change to 32 bit mode */
	piSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	
	/*
	 * Send Initialization Table out to RGS14188
	 */
	for(i = control_1; i <= soft_reg; i++)
		rgs14188_ptr[i] = table_ptr[i];
		
	piSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
}
#if MAKINGROPS
/*
 * piPutLogo24()
 */
piPutLogo24(base, pram5)
register long		base;
short	pram5;
{
	short			width;
	short			height;
	register short	xcenter;
	
	piColorCube(base, pram5);
	/*
	 * determine the width and height
	 */
	piGetWH(pram5, &width, &height);
	xcenter = width / 2;
	
	pi_draw_bm24(base, "logo    ", (short) xcenter, (short) (height*17L/100L), (long) COLOR_ROPS);
	pi_draw_bm24(base, "logo_aa ", (short) xcenter, (short) (height*17/100), (long) COLOR_ROPS_AA);
#if MAKING24MXI
	pi_draw_bm24(base, "b24Mxi  ", (short) xcenter, (short) (height*17/100 + 45), (long) COLOR_ROPS_90);
#else
	#if MAKING24MXRGB
		pi_draw_bm24(base, "MxRGB   ", (short) xcenter, (short) (height*17/100 + 45), (long) COLOR_ROPS_90);
	#else
		pi_draw_bm24(base, "b24MxTV ", (short) xcenter, (short) (height*17/100 + 45), (long) COLOR_ROPS_90);
	#endif
#endif
	pi_draw_bm24(base, "slogan  ", (short) xcenter, (short) (height*92L/100L), (long) COLOR_SLOGAN);
	pi_draw_bm24(base, "sloganaa", (short) xcenter, (short) (height*92L/100L), (long) COLOR_SLOGAN_AA);
	pi_draw_bm24(base, "ver     ", (short) (width*93L/100L), (short) (height*4L/100L), (long) COLOR_GRAY_50);
}
#endif
#if MAKINGIZUMIYA
/*
 * piPutLogo24()
 */
piPutLogo24(base, pram5)
register long		base;
short	pram5;
{
	short			width;
	short			height;
	register short	xcenter;
	
	piEraseScrn24(base, pram5, (long) COLOR_BLACK);
	/*
	 * determine the width and height
	 */
	piGetWH(pram5, &width, &height);
	xcenter = width / 2;
	
	pi_draw_bm8Gc(base, "izumiya ", (short) xcenter, (short) (height*30L/100L), (long) 0);
	pi_draw_bm24(base, "ver     ", (short) (width*93L/100L), (short) (height*4L/100L), (long) COLOR_GRAY_50);
}
#endif
#if MAKINGRGB
/*
 * piPutLogo24()
 */
piPutLogo24(base, pram5)
register long		base;
short	pram5;
{
	short			width;
	short			height;
	register short	xcenter;
	register short	ycenter;
	
	piEraseScrn24(base, pram5, (long) COLOR_GRAY224);
	
	/*
	 * determine the width and height
	 */
	piGetWH(pram5, &width, &height);
	xcenter = width / 2;
	ycenter = height/2;
	pi_draw_bm24(base, "RGBArc1 ", (short) (xcenter - 54), (short) (ycenter - 46), (long) COLOR_RED);
	pi_draw_bm24(base, "RGBArc2 ", (short) (xcenter + 54), (short) (ycenter - 47), (long) COLOR_GREEN);
	pi_draw_bm24(base, "RGBArc3 ", (short) (xcenter-1), (short) (ycenter + 87-46), (long) COLOR_BLUE);
	pi_draw_bm24(base, "RGBTop  ", (short) (xcenter), (short) (height*15L/100L), (long) COLOR_BLUE);
	pi_draw_bm24(base, "RGBBot  ", (short) (xcenter), (short) (height*74L/100L), (long) COLOR_BLUE);
	pi_draw_bm24(base, "ver     ", (short) (width*93L/100L), (short) (height*4L/100L), (long) COLOR_GRAY_75);
}
#endif
#if MAKINGMT
/*
 * piPutLogo24()
 */
piPutLogo24(base, pram5)
register long		base;
short	pram5;
{
	short			width;
	short			height;
	register short	xlogo;
	register short	ylogo;
	register short	xvision;
	register short	yvision;
	
	piEraseScrn24(base, pram5, (long) COLOR_WHITE);
	
	/*
	 * determine the width and height
	 */
	piGetWH(pram5, &width, &height);
	/*
	 * draw logo
	 */
	xlogo = width / 8;
	if(xlogo < 86)
		xlogo = 86;
	ylogo = xlogo;
	pi_draw_bm24(base, "square  ", xlogo, ylogo, (long) COLOR_BLACK);
	pi_draw_bm24(base, "swave   ", xlogo, ylogo, (long) COLOR_CYAN);
	pi_draw_bm24(base, "MTModel ", (short) (xlogo+98), (short) (ylogo+54), (long) COLOR_BLACK);
	/*
	 * display the rainbow last
	 */
	xvision = width/2;
	yvision = height/2;
	if(height <= 480)
		yvision += 40;
	pi_draw_bm24(base, "vision  ", xvision, yvision, (long) COLOR_BLACK);
	pi_draw_bm24(base, "MTrm    ", xvision+270, yvision+72, (long) COLOR_BLACK);
	pi_show(base);
	MTRainbow(base, xvision, yvision);
}
/*
 * piPutLogo8()
 */
piPutLogo8(base, pram5)
register long		base;
short	pram5;
{
}
/*
 * MacTel Logo
 */
MTRainbow(base, xcenter, ycenter)
unsigned long	base;
short			xcenter;
short			ycenter;
{
	long			x;
	long			y;
	short			w;
	short			h;
	register short	i;
	register short	j;
	long			r;
	long			g;
	long			b;
	long			color;
	register long	*to;
	register unsigned long	memWidth;
	char			mode;
	short			n;
	
	w = 432;
	h = 25;
	x = xcenter - w/2;
	y = ycenter - h/2 - 48;
	n = get1ms();	
	memWidth = pi_get_disp_pitch(base) * 4;
	mode = 1;
	piSwapMMUMode(&mode);
	for(i = 0; i < w/2; i++) {
		b = 255;
		r = i * 255L * 2L / w;
		g = 255 - r;
		color = (r << 16L) | (g << 8L) | b;
		
		to = (long *) (base + y * memWidth * 4L + x++ *4L);
		for(j = 0; j < h; j++) {
			*to = color;
			to += memWidth;
			{
				short tmp = n >> 5;
				while(tmp--)
					;
			}
		}
	}
	
	for(i = 0; i < w/2; i++) {
		r = 255;
		g = i * 255L * 2L / w;
		b = 255 - g;
		color = (r << 16L) | (g << 8L) | b;
		
		to = (long *) (base + y * memWidth * 4L + x++ *4L);
		for(j = 0; j < h; j++) {
			*to = color;
			to += memWidth;
			{
				short tmp = n >> 5;
				while(tmp--)
					;
			}
		}
	}
	piSwapMMUMode(&mode);
}
get1ms()
{
	return *((short *) 0xd00);
}
	
#endif
#if MAKINGGENERIC
/*
 * piPutLogo24()
 */
piPutLogo24(base, pram5)
register long		base;
short	pram5;
{
	short			width;
	short			height;
	register short	xcenter;
	
	piEraseScrn24(base, pram5, (long) COLOR_GRAY);
	/*
	 * determine the width and height
	 */
	piGetWH(pram5, &width, &height);
	xcenter = width / 2;
	
	pi_draw_bm24(base, "ver     ", (short) (width*93L/100L), (short) (height*4L/100L), (long) COLOR_BLACK);
}
#endif
#if MAKINGLTD
/*
 * piPutLogo24()
 */
piPutLogo24(base, pram5)
register long		base;
short	pram5;
{
	short			width;
	short			height;
	register short	xcenter;
	
	/*
	 * determine the width and height
	 */
	piGetWH(pram5, &width, &height);
	
	if(!Display_LTD(base, width, height, pram5)) {
		piEraseScrn24(base, pram5, (long) COLOR_BLACK);
		pi_show(base);
		xcenter = width / 2;
		pi_draw_bm24(base, "logo    ", (short) xcenter, (short) (height*17L/100L), (long) COLOR_ROPS);
		pi_draw_bm24(base, "b24MxTV ", (short) xcenter, (short) (height*17L/100L + 45), (long) COLOR_ROPS_90);
		pi_draw_bm24(base, "limited ", (short) xcenter, (short) (height*40L/100L), (long) COLOR_GRAY_90);
		pi_draw_bm24(base, "slogan  ", (short) xcenter, (short) (height*92L/100L), (long) COLOR_GRAY_90);
	}
	pi_draw_bm24(base, "ver     ", (short) (width*93L/100L), (short) (height*4L/100L), (long) COLOR_GRAY_75);
}
#endif
#if MAKING24MXI
#if MAKINGROPS
/*
 * piPutLogo8()
 */
piPutLogo8(base, pram5)
register long		base;
short	pram5;
{
	short			width;
	short			height;
	register short	xcenter;
	
	piEraseScrn8(base, pram5, (long) COLOR_BLACK, INDEX_BLACK);
	/*
	 * determine the width and height
	 */
	piGetWH(pram5, &width, &height);
	xcenter = width / 2;
	
	pi_draw_bm8(base, "logo    ", (short) xcenter, (short) (height*17L/100L), (long) COLOR_ROPS, INDEX_ROPS);
	pi_draw_bm8(base, "logo_aa ", (short) xcenter, (short) (height*17/100), (long) COLOR_ROPS_50, INDEX_ROPS_50);
	pi_draw_bm8(base, "24Mxi", (short) xcenter, (short) (height*17/100 + 45), (long) COLOR_ROPS, INDEX_ROPS);
	pi_draw_bm8(base, "slogan  ", (short) xcenter, (short) (height*92L/100L), (long) COLOR_SLOGAN, INDEX_SLOGAN);
	pi_draw_bm8(base, "sloganaa", (short) xcenter, (short) (height*92L/100L), (long) COLOR_SLOGAN_50, INDEX_SLOGAN_50);
	pi_draw_bm8(base, "ver     ", (short) (width*93L/100L), (short) (height*4L/100L), (long) COLOR_GRAY, INDEX_GRAY);
}
#endif
#if MAKINGGENERIC
/*
 * piPutLogo8()
 */
piPutLogo8(base, pram5)
register long		base;
short	pram5;
{
	short			width;
	short			height;
	register short	xcenter;
	
	piEraseScrn8(base, pram5, (long) COLOR_GRAY, INDEX_GRAY);
	/*
	 * determine the width and height
	 */
	piGetWH(pram5, &width, &height);
	
	pi_draw_bm8(base, "ver     ", (short) (width*93L/100L), (short) (height*4L/100L), (long) COLOR_BLACK, INDEX_BLACK);
}
#endif
#endif
#if 0
/*
 * QD32()
 */
#asm
_piQD32
	MOVE.L	#$AB03,D0			; get address of a new QD32 trap
	_NGetTrapAddress	newTool	; $A746
	MOVE.L	A0,A1
	MOVE.L	#$A89F,D0			; get address of unimplemented trap
	_NGetTrapAddress	newOS	; $A346
	MOVE.L	#0,D0				; assume they are the same, that is QD32 not there
	CMPA.L	A0,A1				; are they the same?
	BEQ	piQDfini
	MOVE.L	#1,D0				;
piQDfini
	RTS
#endasm
#endif
/*
 * SetEEPROM56()
 */
piSetEEPROM56(slot, pram5, pram6)
short	slot;
short	pram5;
short	pram6;
{
#if MAKING24MXI
	register long	*eep;
	short	w;
	
	eep = (long *) ((unsigned long) devBase(slot) | EEPROM);
	w = (pram5 << 8) | (pram6 & 0x00ff);
	pieeWriteWord(eep, (short) 3, w);
#else
	register unsigned long	base;
	
	base = ((unsigned long) devBase(slot));
	pii2cWriteByte(base, 6, pram5);
	pii2cWriteByte(base, 7, pram6);
#endif
}
/*
 * piSetFatSkinny()
 */
piSetFatSkinny(base, mode)
unsigned long	base;
short			mode;
{
	char	mmu_mode;
	short	dummy;
	
	mmu_mode = true32b;
	piSwapMMUMode(&mmu_mode);
	if(mode == FATMODE) {
		dummy = *(long *)(base + FATSLOT);
		#if MAKING24MXI
		dummy = *(unsigned long *)(base + ADDRMODE1);	/* address mode for Mx */
		#else
		*(unsigned long *)(base + ADDRMODE1) = dummy;	/* address mode for MxTV */
		#endif
		#if MAKING24MXI
		dummy = *(unsigned long *)(base + ADDRMODE2);	/* address mode for Mx */
		#endif
	}
	else {
		*(long *)(base + FATSLOT) = 0;
	}
	piSwapMMUMode(&mmu_mode);
}
/*
 * SetPRAM()
 */
piSetPRAM(slot, PRAMPtr)
short					slot;
register SPRAMRecord	*PRAMPtr;		/* where to store the PRAM record */
{
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	/* set up params for slot manager call */
	SpPtr->spSlot = slot;	
	SpPtr->spExtDev = 0;	
	SpPtr->spsPointer = (char *) PRAMPtr;
	piSPutPRAMRec(SpPtr);
}
/*
 * SetPRAM56()
 */
short piSetPRAM56(slot, val5, val6)
short	slot;
short	val5;
short	val6;
{
	SPRAMRecord				PRAMRec;				/* temp storage for pram record */
	register SPRAMRecord	*PRAMPtr = &PRAMRec;	/* temp storage for pram record */
	/*
	 * set up parameters for slot manager call
	 */
	piGetPRAM(slot, PRAMPtr);
	PRAMPtr->vendorUse5 = val5;
	PRAMPtr->vendorUse6 = val6;
	piSetPRAM(slot, PRAMPtr);
}
/*
 * piSetupEEPROM()
 */
piSetupEEPROM(slot)
short	slot;
{
#if MAKING24MXTV
	unsigned long	base;
	
	base = ((unsigned long) devBase(slot));
	pii2cInit(base);
#endif
}
/*
 * pi_show()
 * make it visible
 */
pi_show(base)
unsigned long	base;
{
	char			mmu_mode;	
	
	mmu_mode = 1;	/* 32 bit mode */
	piSwapMMUMode(&mmu_mode);
	*((unsigned long *)(base + BT473_MASK)) = 0xFF;   /* DAC read mask */
	piSwapMMUMode(&mmu_mode);
}
/*
 * piwaitnms
 */
piwaitnms(n)
register short	n;
{
	while(n-- > 0) {
		piwait1ms();
	}
}
/*
 * _piwait1ms
 */
#asm
_piwait1ms
	CLR.L	D0
	MOVE.W	$D00,D0		; Get TimeDBRA Global
pimore_dbras			; Loop for 1 ms
	DBRA	D0,pimore_dbras
	RTS
#endasm 
/******************************************************************************
 *  glue for Slot Manager calls
 ******************************************************************************/
/*
 * SReadPRAMRec(spPtr)
 */
#asm
_piSReadPRAMRec
	MOVE.L	4(SP),A0
	MOVEQ	#$11,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SPutPRAMRec(spPtr)
 */
#asm
_piSPutPRAMRec
	MOVE.L	4(SP),A0
	MOVEQ	#$12,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SetSRsrcState(spPtr)
 */
#asm
_piSetSRsrcState
	MOVE.L	4(SP),A0
	MOVEQ	#$09,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SDeleteSRTRec(spPtr)
 */
#asm
_piSDeleteSRTRec
	MOVE.L	4(SP),A0
	MOVEQ	#$31,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * sVersion(SpPtr) Glue
 */
#asm
_pisVersion
	MOVE.L	4(SP),A0
	MOVEQ	#8,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SRsrcInfo(spPtr) Glue
 */
#asm
_piSRsrcInfo
	MOVE.L	4(SP),A0
	MOVEQ	#$16,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SFindStruct(spPtr) Glue
 */
#asm
_piSFindStruct
	MOVE.L	4(SP),A0
	_SFindStruct
	RTS
#endasm 
/*
 * SwapMMUMode(spPtr) Glue
 */
#asm
_piSwapMMUMode
	MOVE.L	4(SP),A0
	MOVE.B	(A0),D0
	_SwapMMUMode		; SwapMMUMode $A05D
	MOVE.L	4(SP),A0
	MOVE.B	D0,(A0)
	RTS
#endasm
#if MAKING24MXI
/*****************************************************************************
 * piEEPROM code (24Mxi)
 *****************************************************************************/
/*
 * pieeEnable()
 */
void pieeEnable(eep)
register long	*eep;	/* address of EE Prom */
{
	piEESendStartOpAddr(eep, (short) OP_EWEN, (short) ADDR_EWEN);
	piEEEpilog(eep);
}
/*
 * pieeDisable()
 */
void pieeDisable(eep)
register long	*eep;	/* address of EE Prom */
{
	piEESendStartOpAddr(eep, (short) OP_EWDS, (short) ADDR_EWDS);
	piEEEpilog(eep);
}
/*
 * pieeReadWord()
 */
short pieeReadWord(eep, addr)
register long	*eep;	/* address of EE Prom */
short			addr;
{
	short	w;
	
	piEESendStartOpAddr(eep, (short) OP_READ, addr);
	piEEDiscardBit(eep);
	w = piEEReadBitStream(eep);
	piEEEpilog(eep);
	return w;
}
/*
 * pieeWriteWord()
 */
void pieeWriteWord(eep, addr, data)
register long	*eep;	/* address of EE Prom */
short			addr;
short			data;
{	
	pieeEnable(eep);
	piEESendStartOpAddr(eep, (short) OP_WRITE, addr);
	piEESendData(eep, data);
	piEEPollReady(eep);
	piEEEpilog(eep);
	pieeDisable(eep);
}	
/*
 * piEEPollReady()
 *
 * wait till data written is ready
 * quit after 10 ms no matter what
 */
short piEEPollReady(eep)
register long	*eep;	/* address of EE Prom */
{
	long	bits;
	short	i;
	piEEPoke(eep, 0, 0, 0);
	piEEPoke(eep, 1, 0, 0);
	piwait1ms();
	
	i = 10;
	while(i--) {
		bits = piEEPeek(eep);
		if(bits & 0x01) {
			return 1;
		}
		piwait1ms();
	}
	return 0;
}
/*
 * piEEReadBitStream()
 */
short piEEReadBitStream(eep)
register long	*eep;	/* address of EE Prom */
{
	register short	w;
	register short	count;
	register long	bit;
	
	w = 0;
	count = 16;
	
	while(count--) {
		piEEPoke(eep, 0, 1, 0);
		bit = piEEPeek(eep);
		piEEPoke(eep, 1, 1, 0);
		w = (w << 1) | (bit & 0x01);
	}
	return w;
}
/*
 * piEESendBitStream()
 */
void piEESendBitStream(eep, bits, n)
register long	*eep;	/* address of EE Prom */
register short	bits;	/* bits to send to eep */
register short	n;		/* number of bits to send, bits are right justified */
{
	bits <<= (16 - n);
	while(n--) {
		if(bits >= 0) {
			piEEPoke(eep, 0, 1, 0);
			piEEPoke(eep, 1, 1, 0);
		}
		else {
			piEEPoke(eep, 0, 1, 1);
			piEEPoke(eep, 1, 1, 1);
		}
		bits <<= 1;
	}
}
/*
 * piEESendStartOpAddr()
 */
void piEESendStartOpAddr(eep, opcode, addr)
register long	*eep;	/* address of EE Prom */
register short	opcode;
register short	addr;
{
	piEEProlog(eep);	 	
	piEESendOpcode(eep, opcode);
	piEESendAddr(eep, addr);
}
/*
 * pieePoke()
 */
void pieePoke(eep, bits)
long	*eep;	/* address of EE Prom */
short	bits;
{
	char	mmu_mode;
	
	mmu_mode = true32b;
	piSwapMMUMode(&mmu_mode);
	*eep = (long) bits;
	piSwapMMUMode(&mmu_mode);
}
/*
 * pieePeek()
 */
short pieePeek(eep)
long	*eep;	/* address of EE Prom */
{
	char			mmu_mode;
	register long	w;
	
	mmu_mode = true32b;
	piSwapMMUMode(&mmu_mode);
	w = *eep;
	piSwapMMUMode(&mmu_mode);
	return ((short) w);
}
#endif
#if MAKING24MXTV
/*****************************************************************************
 * i2cEEPROM code (24MxTV)
 *****************************************************************************/
/*
 * pieeReadWord()
 */
short pieeReadWord(eep, addr)
register long	*eep;	/* address of EE Prom */
register short			addr;
{
	register long	base;
	register short	lo;
	register short	hi;
	
	base = ((long) eep) & 0xff000000;
	hi = pii2cReadByte(base, (short) (addr * 2));
	lo = pii2cReadByte(base, (short) (addr * 2 + 1));
	return ((short) ((hi << 8) | (lo & 0x00ff)));
}
/*
 * i2cGetSCL()
 */
short
pii2cGetSCL(base)
long	base;
{
	unsigned char	mmu_mode;
	register unsigned short	the_data;
	
	mmu_mode = 1;		/* prepare to change to 32 bit mode */
	piSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	the_data = (*((unsigned long *)(base + pip_i2c)) & pip_i2c_clock) ? 1:0;
	piSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
	return the_data;
}
/*
 * i2cGetSDA()
 */
short
pii2cGetSDA(base)
long	base;
{
	unsigned char	mmu_mode;
	register unsigned short	the_data;
	
	mmu_mode = 1;		/* prepare to change to 32 bit mode */
	piSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	the_data = (*((unsigned long *)(base + pip_i2c)) & pip_i2c_data) ? 1:0;
	piSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
	return the_data;
}
/*
 * pii2cInit(base)
 *
 * This routine is to fix the problem with Philips chip which holds down the data line
 * at cold start (occasionally). We make it active then set it to reset mode to make it
 * release the line.
 */
pii2cInit(base)
register long	base;
{
	register unsigned long	i2cState;
	unsigned char	mmu_mode;
	
	mmu_mode = 1;		/* prepare to change to 32 bit mode */
	piSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	i2cState = *((unsigned long *)(base + pip_i2c));
	i2cState |= (pip_i2c_clock | pip_i2c_data | pip_i2c_drst);
	*((unsigned long *)(base + pip_i2c)) = i2cState;
	piSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
	
	piwaitnms(100);
	
	mmu_mode = 1;		/* prepare to change to 32 bit mode */
	piSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	i2cState &= ~pip_i2c_drst;
	*((unsigned long *)(base + pip_i2c)) = i2cState;
	piSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
}
/*
 * i2cReadByte(base,addr)
 */
short
pii2cReadByte(base,addr)
register long	base;
short	addr;
{
	short	rc;
	
	pii2cSendStartBit(base);
	pii2cSendSlaveAddr(base, (short) (I2CADDR | I2CWRITE));
	pii2cWaitAck(base);
	pii2cSendWordAddr(base, addr);
	pii2cWaitAck(base);
	pii2cSendStartBit(base);
	pii2cSendSlaveAddr(base, (short) (I2CADDR | I2CREAD));
	pii2cWaitAck(base);
	rc = pii2cReadData(base);
	pii2cSendBit(base, 1);	
	pii2cSendStopBit(base);
	return rc;
}
/*
 * i2cReadData()
 */
short
pii2cReadData(base)
register long	base;
{
	register short	rc;
	register short	i;
	
	rc = 0;
	i = 8;
	while(i--) {
		piSCL0_SDA1(base);
		piSCL1_SDA1(base);
		rc = (rc << 1) | pii2cGetSDA(base);
	}
	return rc;
}
/*
 * i2cSendBit()
 */
pii2cSendBit(base, bit)
register long	base;
register short	bit;
{
	register unsigned long	i2cState;
	unsigned char	mmu_mode;
	
	if(!bit) {
		piSCL0_SDA0(base);
		piSCL1_SDA0(base);
	}
	else {
		piSCL0_SDA1(base);
		piSCL1_SDA1(base);
	}
}
/*
 * i2cSendByte()
 */
pii2cSendByte(base, s)
register long	base;
short	s;
{
	register char	b;
	register short	k;
	
	b = (char) s;
	k = 8;
	while(k--) {
		if(b >= 0)
			pii2cSendBit(base, 0);
		else
			pii2cSendBit(base, 1);
		b <<= 1;
	}
}
		
/*
 * i2cSendStartBit()
 */
short
pii2cSendStartBit(base)
register long	base;
{
	register short	i;
	register short	j;
	
	for(i = 0; i < 20; i++) {
		for(j = 0; j < 100; j++) {
			if((pii2cGetSCL(base) && pii2cGetSDA(base))) {
				goto getout;
			}
		}
		pii2cSendStopBit(base);
	}
	return -1;
getout:
	piSDA0(base);
	piSCL0(base);
	return 0;
}
/*
 * i2cSendStopBit()
 */
pii2cSendStopBit(base)
register long	base;
{
/*
	piSCL0_SDA0(base);
	piSCL0_SDA0(base);
	piSCL1_SDA0(base);
	piSCL1_SDA1(base);
*/
	piSDA1(base);
	piSCL0(base);
	piSCL1(base);
	
	piSCL0(base);
	piSDA0(base);
	piSCL1(base);
	piSDA1(base);
}
/*
 * i2cSetSCL()
 */
pii2cSetSCL(base, clock)
register long	base;
short	clock;
{
	register unsigned long	i2cState;
	unsigned char	mmu_mode;
	
	mmu_mode = 1;		/* prepare to change to 32 bit mode */
	piSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	i2cState = *((unsigned long *)(base + pip_i2c));
	
	if(clock)
		i2cState |= pip_i2c_clock;
	else
		i2cState &= ~pip_i2c_clock;
		
	*((unsigned long *)(base + pip_i2c)) = i2cState;
	piSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
	
	/*
	if(clock)
		piDelaySCL1();
	else
		piDelaySCL0();
	*/
}
/*
 * i2cSetSDA()
 */
pii2cSetSDA(base, data)
register long	base;
short	data;
{
	register unsigned long	i2cState;
	unsigned char	mmu_mode;
	
	mmu_mode = 1;		/* prepare to change to 32 bit mode */
	piSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	i2cState = *((unsigned long *)(base + pip_i2c));
	
	if(data)
		i2cState |= pip_i2c_data;
	else
		i2cState &= ~pip_i2c_data;
		
	*((unsigned long *)(base + pip_i2c)) = i2cState;
	piSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
}
/*
 * i2cSetSCLSDA()
 */
pii2cSetSCLSDA(base, clock, data)
register long	base;
register short	clock;
register short	data;
{
	register unsigned long	i2cState;
	unsigned char	mmu_mode;
	
	mmu_mode = 1;		/* prepare to change to 32 bit mode */
	piSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	i2cState = *((unsigned long *)(base + pip_i2c));
	
	if(clock == 1)
		i2cState |= pip_i2c_clock;
	else
		i2cState &= ~pip_i2c_clock;
	if(data == 1)
		i2cState |= pip_i2c_data;
	else
		i2cState &= ~pip_i2c_data;
		
	*((unsigned long *)(base + pip_i2c)) = i2cState;
	piSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
	
	/*
	if(clock)
		piDelaySCL1();
	else
		piDelaySCL0();
	*/
}
/*
 * i2cWaitAck()
 */
pii2cWaitAck(base)
register long	base;
{
	piSCL0_SDA1(base);
	pii2cWaitSDA0(base);
	piSCL1_SDA1(base);
	pii2cWaitSCL1(base);
}
/*
 * i2cWaitSCL1()
 */
short
pii2cWaitSCL1(base)
register long	base;
{
	register short	i;
	
	for(i = 3000; i > 0; i--) {
		if(pii2cGetSCL(base) == 1)
			return 0;
		else 
			piDelaySCL1();
	}
	return -1;
}
/*
 * i2cWaitSDA0()
 */
short
pii2cWaitSDA0(base)
register long	base;
{
	register short	i;
	
	for(i = 3000; i > 0; i--) {
		if(pii2cGetSDA(base) == 0)
			return 0;
		else 
			piDelaySCL0();
	}
	return -1;
}
/*
 * i2cWriteByte(base, addr, data)
 */
pii2cWriteByte(base, addr, data)
register long	base;
register short	addr;
register short	data;
{	
	pii2cSendStartBit(base);
	pii2cSendSlaveAddr(base, (short) (I2CADDR | I2CWRITE));
	pii2cWaitAck(base);
	pii2cSendWordAddr(base, addr);
	pii2cWaitAck(base);
	pii2cSendData(base, data);
	pii2cWaitAck(base);
	pii2cSendStopBit(base);
	
	/*
	 * wait for 30 ms
	 */
	piwaitnms(30);
}
/*
 * piclock_wait()
 */
piclock_wait(count)
register short	count;
{	
	count--;
	while(count-- >= 0)
		;
}
#endif
#asm
; ==================END OF PRIMARY INIT BLOCK=====================
endprimaryinit
#endasm
#asm
;
; ==================BEGINNING OF SECONDARY INIT BLOCK=====================
;
secondaryinit
    dc.l  endsecondaryinit-secondaryinit    ; Length of seBlock
    dc.b  2                                 ; Revision Level 2 (The Slot Manager REQUIRES this to be 2!)
    dc.b  2                                 ; CPU ID 2 (68020)
    dc.w  0                                 ; Reserved
    dc.l  4                                 ; Code Offset 4  (In other words, next!)
;
; 2ND INIT CODE
; On Entry:  A0 -> Slot Manager SEBlock
;
	MOVEM.L A0-A5/D0-D7,-(SP)  	; save nearly all registers	
	MOVE.L	A0,-(SP)			; push SeBlock pointer
	JSR		_cSecondaryInit		; call our c routine
	LEA		4(SP),SP			; repair stack caused by c call
	MOVEM.L (SP)+,A0-A5/D0-D7	; Restore nearly all registers
	RTS
#endasm
cSecondaryInit(SeBlkPtr)
SEBlock	*SeBlkPtr;									/* pointer to SeBlock passed to us */
{
	register unsigned short	slot;					/* slot number */
	register unsigned long	base;					/* address of our frame buffer */
#if 0
	register unsigned short	pram6;					/* control panel soft setting */
	register unsigned short	pram5;					/* control panel soft setting */
	unsigned short			dpram6;					/* control panel soft setting */
	unsigned short			dpram5;					/* control panel soft setting */
#endif
	char					is24bit;
#if DEBUG
	myDebugStr("\PcSecondaryInit: enter");
#endif
	/*
	 * set status to 1 (success)
	 * get slot number
	 * contruct 32 bit address of our frame buffer
	 * set up sp block slot number and ext device to be used in all slot manager calls
	 */
	SeBlkPtr->seStatus = 1;
	slot = SeBlkPtr->seSlot;
	base = 0xf0000000 | (((unsigned long) slot) << 24L);
	/*
	 * force Fat Slot address map
	 */
	siSetFatSkinny(base, (short) FATMODE);
#if 0	
	siGetPRAM56(slot, &dpram5, &dpram6);
	pram5 = dpram5 & 0x008f;
	pram6 = dpram6 & 0x00ff;
#endif
	/*
	 * if cmd-sht-opt are pressed, cycle thru, otherwise just do the resource
	 * insertion
	 *
	 * cycleIt() WILL CAUSE A RESTART
	 *
	 * DONT DO THIS ON AUX
	 */
	
	if(!siAUXRunning()) { 
		if(cmdoptsht()) {
			cycleIt(slot);
		}
	}
#if 0			
	/*
	 * if (QD32 | AUX) then
	 *	1. insert other resouces of the form $9x
	 *	2. if existing resource is $8x then replace with $9x and patch the Gdev
	 *
	 * if not then
	 *	insert other resources of the form $8x
	 *
	 */
		
	if(siQD32() || siAUXRunning()) {
		unsigned short	mask;
		
		mask = 0x0090;
		
		InsertExcept(slot, (unsigned short)((pram6  & 0x008f) | mask),
					(unsigned short)(FirstResource | mask), (unsigned short)(LastResource | mask));
		if(pram5 == FirstResource) {		/* if 11x8 monitor dont show 11x8 extended */
			siDeleteResource(slot, (short) (FirstExtended | mask));
		}
		if((pram6 & 0x00f0) == 0x0080) {	/* THIS WILL NOT HAPPEN IF AUX RUNNING */			
			Del80Ins90a0(slot, pram6, mask);
			pram6 |= mask;
			siSetPRAM6(slot, pram6);
			if(siGetRefNum(slot)) {			/* this is the boot board */
				PatchGDev(base);
			}
		}
		
#if MAKING24MXI
		/*
		 * no interlaced for 24Mxi
		 */
		{
			short	i;
			for(i = FirstInterlaced; i <= LastInterlaced; i++)
				siDeleteResource(slot, (short) (i | mask));
		}
#endif
	}
	else {
		InsertExcept(slot, pram6,
					(unsigned short)(FirstResource | 0x0080), (unsigned short)(LastResource | 0x0080));
#if MAKING24MXI
		/*
		 * no interlaced for 24Mxi
		 */
		{
			short	i;
			for(i = FirstInterlaced; i <= LastInterlaced; i++)
				siDeleteResource(slot, (short) (i));
		}
#endif
	}
	
	/*
	 * we dont support Apple Portrait as we only have 0.5M of ram
	 */
	siDeleteResource(slot, (short) 0x0085);
	siDeleteResource(slot, (short) 0x0095);
	siDeleteResource(slot, (short) 0x00a5);
#endif
}
/*
 * AUXRunning()
 */
siAUXRunning()
{
	register short	flags;
	
	flags  = *((short *) (0x0b22));
	return (flags & (0x0200));
}
/*
 * cmdoptsht()
 *
 * check to see if cmd-opt-sht are pressed
 * the only other key that can be down is capLock
 */
short cmdoptsht()
{
	KeyMap	km;
	
/*	ADBReInit(); */
	siDelay(25L);
	
	GetKeys(km);
/*	myDebugStr("\Pcmdoptsht"); */
/*	if((km[1] & 0x00008005) == 0x00008005) */
	if((km[1] | 0xffff0002) == 0xffff8007)	/* dont know why some keys got stuck sometimes */
		return true;
	else
		return false;
}
/*
 * cycleIt()
 */
cycleIt(slot)
short	slot;
{
	register unsigned long	base;
	short			width;
	short			height;
	register short	resNum;
	
	/*
	 * 0. draw picture (use 1bit mode)
	 * 1. load NTSC timing
	 * 2. poll keyboard for 5 seconds
	 * 3. if key pressed or mouse down, break
	 * 4. load PAL timing
	 * 5. poll keyboard for 5 seconds
	 * 6. if key pressed or mouse down, break
	 * 7. repeat 1-6
	 */
	base = devBase(slot);
	set1bit(base);
	
	while(1) {
#if MAKING24MXI
		for(resNum = FirstResource; resNum <= LastNonInterlaced; resNum++) {
#else
		for(resNum = FirstResource; resNum <= LastMonitor; resNum++) {
#endif
			if(resNum == RES_APD)		/* we dont support Apple Portrait */
				continue;
			siGetWH(resNum, &width, &height);
			showResolution(base, resNum, width, height);
			if (poll(base, width, height)) {
				siSetEEPROM56(slot, resNum, resNum);
				goto gotit;
			}	
		}
	}
gotit:
	resNum = resNum;
	/*
	 * reboot, primary init will pick up from pram and use the right timing
	 */
	{
		SpBlock		SpBlk;					/* our sp block to make the slot manager call */
		SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	
		sisVersion(SpPtr);
		if(SpPtr->spResult >= 2) {
			/****  This doesn't work on cx (old rom) */
			#asm
			;	ShutDwnStart();
				dc.w	$3f3c
				dc.w	$0002
				dc.w	$a895
			#endasm
		}
		else {
			#asm
				move.l	ROMBase,a0
				jmp		$0a(a0)
			#endasm
		}
	}
}
#if 0
/*
 * Del80Ins90a0(slot, ResourceNumber, mask)
 */
Del80Ins90a0(slot, ResourceNumber, mask)
short					slot;
register unsigned short	ResourceNumber;
short					mask;
{
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	SpPtr->spSlot = slot;
	SpPtr->spExtDev = 0;
	SpPtr->spID = ResourceNumber;
	siSRsrcInfo(SpPtr);		/* want to get spRefNum, to be used in insert */
	siSDeleteSRTRec(SpPtr);
	SpPtr->spsPointer = 0;		/* not ram sRsrc */
	SpPtr->spStackPtr = 0;		/* enable it, (actually SpPtr->spParamData) */
	SpPtr->spID = ResourceNumber | mask;
	sisInsertSRTRec(SpPtr);
}
/*
 * siDeleteResource(slot, ResourceNumber)
 */
siDeleteResource(slot, ResourceNumber)
short			slot;
unsigned short	ResourceNumber;
{
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	SpPtr->spSlot = slot;
	SpPtr->spExtDev = 0;
	SpPtr->spID = ResourceNumber;
	siSDeleteSRTRec(SpPtr);
}
#endif
			
/*
 * si_draw_bm1()
 */
si_draw_bm1(base, name, xcenter, ycenter, color)
unsigned long	base;
char			*name;
short			xcenter;
short			ycenter;
unsigned long	color;
{
	register unsigned char	*to;
	register char			*bm;
	register short			k;
	register char			c;
	register short			j;
	register short			i;
	short					xstart, ystart;
	short					p_width, p_height;
	short					p_width8;
	char					mmu_mode;
	BMHeader3				*headerptr;
  
#if DEBUG
	myDebugStr("\Psi_draw_bm1: enter");
#endif
	if(!siFindBitmap(base, name, &headerptr))
		return;
		
	mmu_mode = 1;	/* 32 bit mode */
	siSwapMMUMode(&mmu_mode);
  		
	bm = (char *)headerptr + sizeof(BMHeader3);
	p_width = ((long) headerptr->widthHi << 8L) | ((long) headerptr->widthLo & 0x00ff);
	p_height = ((long) headerptr->heightHi << 8L) | ((long) headerptr->heightLo & 0x00ff);
 	p_width8 = p_width / 8;
	
	/*
	 * calculate starting point
	 */
	if((xcenter == 0) && (ycenter == 0)) {
		xstart = DEF_WIDTH/2 - p_width/ 2;
		ystart = DEF_HEIGHT/3 - p_height/2;
	}
	else {
		xstart = xcenter - p_width/2;
		ystart = ycenter - p_height/2;
	}
	if(xstart < 0)
		xstart = 0;
	if(ystart < 0)
		ystart = 0;
	
	/*
	 * draw the bitmap
	 */
	to = (unsigned char *)(base);
	to += (ystart * (long) DEF_ROWBYTES + xstart/8);
	bm += 3;		/* we are using byte lane 3 */
	for (i=0;i<p_height;i++) {
		for (j=0;j<p_width8;j++) {
			*to++ = *bm;
			bm += 4;
		}
		to += (DEF_ROWBYTES - p_width8);
	}
  
	siSwapMMUMode(&mmu_mode);
}
/*
 * eraseScrn()
 */
eraseScrn(base, width, height)
unsigned long	base;
short	width;
short	height;
{
	register short			i,j;
	register unsigned long	*to;
	char					mmu_mode;
	mmu_mode = 1;	/* 32 bit mode */
	siSwapMMUMode(&mmu_mode);
    
	/*
	 * blank the screen
	 */
	to = (unsigned long *) (base);
	i = 624;
	while(i--) {
		j = 832L/4;
		while(j--) {
			*to++ = 0;
		}
	}
	
	/****
	for (i=0;i<height;i++) {
		to = (unsigned char *) (base + 832L * i);
		for (j=0;j<width/8;j++) {
			*to++=0;
		}
	}
	*/
	
	siSwapMMUMode(&mmu_mode);
}
/*
 * siFindBitmap(base, name, headeraddr)
 */
short siFindBitmap(base, name, headeraddr)
char			*base;
register char	*name;
BMHeader3		**headeraddr;
{
	register BMHeader3	*ptr;
	long				size;
	short				rc;
	char				mmu_mode;
	short				dummy;
	
	
	/**** use 0x00fc0000 when we using 512K rom */
	/**** use 0x00fe0000 when we using 256K rom */
	ptr = (BMHeader3 *) (base + 0x00fc0000);
	mmu_mode = 1;	/* 32 bit mode */
	siSwapMMUMode(&mmu_mode);
  	
/*	SET_FATMODE(base, dummy); */
	rc = 0;
	while( size = (((long) (ptr->filesize0) << 24L) & 0xff000000L) | 
				  (((long) (ptr->filesize1) << 16L) & 0x00ff0000L) |
				  (((long) (ptr->filesize2) <<  8L) & 0x0000ff00L) |
				  ((long) (ptr->filesize3) & 0x000000ffL)) {
		if ((name[0] == ptr->filename[0].c) &&
			(name[1] == ptr->filename[1].c) &&
			(name[2] == ptr->filename[2].c) &&
			(name[3] == ptr->filename[3].c) &&
			(name[4] == ptr->filename[4].c) &&
			(name[5] == ptr->filename[5].c) &&
			(name[6] == ptr->filename[6].c) &&
			(name[7] == ptr->filename[7].c)
		   ) {
			*headeraddr = ptr;
			rc = 1;
			break;
		}
		else {
			ptr = (BMHeader3 *) ((unsigned long) ptr + size * 4);		/* *4 because we use byte lane 3 */
		}
	}
	siSwapMMUMode(&mmu_mode);
	return rc;
}
#if 0
/*
 * GetPRAM()
 */
siGetPRAM(slot, PRAMPtr)
short					slot;
register SPRAMRecord	*PRAMPtr;		/* where to store the PRAM record */
{
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	/* set up parameters for slot manager call */
	SpPtr->spSlot = slot;	
	SpPtr->spExtDev = 0;	
	SpPtr->spResult = (unsigned long) PRAMPtr;
	siSReadPRAMRec(SpPtr);
}
/*
 * GetPRAM56()
 */
siGetPRAM56(slot, ptr5, ptr6)
short	slot;
short	*ptr5;
short	*ptr6;
{
	SPRAMRecord				PRAMRec;				/* temp storage for pram record */
	register SPRAMRecord	*PRAMPtr = &PRAMRec;	/* temp storage for pram record */
	siGetPRAM(slot, PRAMPtr);
	*ptr5 = PRAMPtr->vendorUse5;
	*ptr6 = PRAMPtr->vendorUse6;
}
/*
 * siGetRefNum(slot, ResourceNumber)
 */
siGetRefNum(slot, ResourceNumber)
short					slot;
register unsigned short	ResourceNumber;
{
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	SpPtr->spSlot = slot;
	SpPtr->spExtDev = 0;
	SpPtr->spID = ResourceNumber;
	siSRsrcInfo(SpPtr);		/* want to get spRefNum, to be used in insert */
	return (SpPtr->spRefNum);
}
#endif
/*
 * siGetWH()
 */
siGetWH(resNum, width, height)
register short	resNum;
register short	*width;
register short	*height;
{
	
	/*
	 * determine the width and height
	 */
	switch(resNum & 0x000f) {
		case 0x00:
				*width = 1152;
				*height = 870;
				break;
		case 0x01:
		case 0x02:
				*width = 1024;
				*height = 768;
				break;
		case 0x03:
				*width = 832;
				*height = 624;
				break;
		case 0x04:
		case 0x06:
				*width = 640;
				*height = 480;
				break;
		case 0x05:
				*width = 640;
				*height = 870;
				break;
		case 0x07:
				*width = 768;
				*height = 576;
				break;
		case 0x08:
				*width = 576;
				*height = 432;
				break;
		case 0x09:
				*width = 684;
				*height = 512;
				break;
		case 0x0a:
				*width = 1152;
				*height = 870;
				break;
		case 0x0b:
				*width = 1600;
				*height = 1200;
				break;
		case 0x0c:
				*width = 2304;
				*height = 1740;
				break;
		case 0x0d:
				*width = 3200;
				*height = 2400;
				break;
	}
}
#if 0
/*
 * InsertExcept(slot, ResourceNumber, start, end)
 */
InsertExcept(slot, ResourceNumber, start, end)
short					slot;
register unsigned short	ResourceNumber;
register unsigned short	start;
register unsigned short	end;
{
	register unsigned short	i;
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	SpPtr->spSlot = slot;
	SpPtr->spExtDev = 0;
	SpPtr->spsPointer = 0;		/* not ram sRsrc */
	SpPtr->spRefNum = 0;		/* dont update dCtlDevBase */
	SpPtr->spStackPtr = 1;		/* disable it, (actually SpPtr->spParamData) */
	for(i = start; i <= end; i++) {
		if (i != ResourceNumber) {
			SpPtr->spID = i;
			sisInsertSRTRec(SpPtr);
		}
	}
}
#endif
	
/*
 * si_load_timingtable()
 *
 * 14 Tables of 48 bytes each, corresponding to the
 * registers on the RGS14188.
 * X Table 80	1152 X 870 75Hz
 * X Table 81	1024 X 768 75Hz
 * X Table 82	1024 X 768 60Hz
 *  Table 83	832 X 624
 *  Table 84	640 X 480 67hz
 * X Table 85	640 X 870
 *  Table 86	640 X 480 NTSC
 *  Table 87	640 X 480 NTSC GenLock
 *  Table 88	768 X 576 PAL
 *  Table 89	768 X 576 PAL GenLock
 *  Table 8A	576 X 432 NTSC
 *  Table 8B	576 X 432 NTSC GenLock
 *  Table 8C	684 X 512 PAL underscan
 *  Table 8D	684 X 512 PAL Genlock underscan
 */
si_load_timingtable(base, resNum)
unsigned long	base;
short			resNum;
{
	register unsigned long	*rgs14188_ptr;
	register unsigned long	*table_ptr;
	register short			i;
	unsigned short			timingNum;
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	char					mmu_mode;
	short					GenLock;
	
	mmu_mode = true32b;		/* prepare to change to 32 bit mode */
	siSwapMMUMode(&mmu_mode);
	GenLock = ISGENLOCK(base);
	siSwapMMUMode(&mmu_mode);
	rgs14188_ptr = (unsigned long *)(base + RGS14188);
	switch(resNum & 0x008F)
	{
		case RES_ID_11x8:
			timingNum = TIMING_ID_11x8;
			break;
		case RES_ID_10x7_75:
			timingNum = TIMING_ID_10x7_75;
			break;
		case RES_ID_10x7_60:
			timingNum = TIMING_ID_10x7_60;
			break;
		case RES_ID_8x6:
			timingNum = TIMING_ID_8x6;
			break;
		case RES_ID_6x4:
			timingNum = TIMING_ID_6x4;
			break;
		case RES_ID_6x8:
			timingNum = TIMING_ID_6x8;
			break;
#if MAKING24MXTV	
		case RES_ID_6x4ntsc:
			if(!GenLock)
				timingNum = TIMING_ID_6x4ntsc;
			else
				timingNum = TIMING_ID_6x4ntscGL;
			break;
		case RES_ID_7x5pal:
			if(!GenLock)
				timingNum = TIMING_ID_7x5pal;
			else
				timingNum = TIMING_ID_7x5palGL;
			break;
		case RES_ID_5x4ntsc:
			if(!GenLock)
				timingNum = TIMING_ID_5x4ntsc;
			else
				timingNum = TIMING_ID_5x4ntscGL;
			break;
		case RES_ID_6x5pal:
			if(!GenLock)
				timingNum = TIMING_ID_6x5pal;
			else
				timingNum = TIMING_ID_6x5palGL;
			break;
#endif
	}
	/* Find parameter resource */
	SpPtr->spSlot = (base >> 24) & 0x0F;
	SpPtr->spExtDev = 0;
	SpPtr->spID = sRsrcBoard;		/* Find Board Resource */
	siSRsrcInfo(SpPtr);
	SpPtr->spID = sTimingTableDir;	/* Find Resoulution Directory */
	siSFindStruct(SpPtr);
	SpPtr->spID = timingNum;			/* Find Parameters */
	siSFindStruct(SpPtr);
	
	table_ptr = (unsigned long *)(SpPtr->spsPointer + 16 - 3); /* skip count and adjust byte lane for long access */
	
	/*
	 * Send Initialization Table out to RGS14188
	 */
	mmu_mode = true32b;		/* prepare to change to 32 bit mode */
	siSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	
	for(i = control_1; i <= soft_reg; i++)
		rgs14188_ptr[i] = table_ptr[i];
		
	/*
	 * set 1 bit mode
	 */
	rgs14188_ptr[gio_reg_Hi] &= (long)0xF0;  /* force 1-8 bit modes (bit 4,5 = 0) and Reset (bit 7 lo) */
	rgs14188_ptr[gio_reg_Hi] |= 0x00;  /* set 1 bit mode */
	/*
	 * Turn on refresh, transfer enable, and sync
	 */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	rgs14188_ptr[control_1] |= 0x91;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	rgs14188_ptr[control_3] |= 0x72;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	rgs14188_ptr[control_1] |= 0xB1;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	rgs14188_ptr[gio_reg_Lo] |= soft_reset_off;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	siSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
}
	
#if 0
/*
 * PatchGDev(base)
 */
PatchGDev(base)
unsigned long	base;		/* address of our frame buffer */
{
#asm
	; Patch gDevice
	CLR.L	-(SP)			; space for handle
	DC.W	$AA32			; GetGDevice
	MOVEA.L	(SP)+,A0		; gDevice Handle
	MOVEA.L	(A0),A0			; gDevice Pointer
	MOVEA.L	22(A0),A0		; gdPMap (PixMapHandle)
	MOVEA.L	(A0),A0			; PixMapPtr
	
	MOVE.L	(A0),D0			; get pmBaseAddr
	ANDI.L	#$FF000000,D0	; check if it's us
	CMP.L	8(A6),D0
	BNE	notboot2			; no, leave it as is
	ANDI.L	#$FF0FFFFF,(A0)	; yes, pmBaseAddr gets Fs0XXXXX in place of FssXXXXX
notboot2
#endasm
}
#endif
	
/*
 * loop wait for key pressed or mouse down
 * quit after 4000 tries (about 4 seconds)
 */
short poll(base, width, height)
unsigned long	base;
short			width;
short			height;
{
	KeyMap			km;
	register short	count;
	
	count = 4096;
	while(count--) {	
		GetKeys(&km);
		km[1] &= 0xffff7ff0;		/* mask off cmd-opt-sht and cap */
		if(km[0] || km[1] || km[2] || km[3] || Button()) {
			return true;
		}
		else {
			siwait1ms();
			if( (count & 0x01FF) == 0)		/* toggle every 512 miliseconds */
				toggle_icons(base, width, height);
		}
	}
		
	return false;
}
#if 0
/*
 * QD32()
 */
#asm
_siQD32
	MOVE.L	#$AB03,D0			; get address of a new QD32 trap
	_NGetTrapAddress	newTool	; $A746
	MOVE.L	A0,A1
	MOVE.L	#$A89F,D0			; get address of unimplemented trap
	_NGetTrapAddress	newOS	; $A346
	MOVE.L	#0,D0			; assume they are the same, that is QD32 not there
	CMPA.L	A0,A1			; are they the same?
	BEQ	siQDfini
	MOVE.L	#1,D0			;
siQDfini
	RTS
#endasm
#endif
/*
 * set1bit()
 */
set1bit(base)
register unsigned long	base;
{
	register unsigned long	*rgs14188_ptr;
	char					mmu_mode;
	rgs14188_ptr = (unsigned long *)(base + RGS14188);
	
	mmu_mode = 1;
	siSwapMMUMode(&mmu_mode);  
/*	siSetFatSkinny(base, (short) SKINNYMODE); */
	rgs14188_ptr[gio_reg_Lo] &= 0xBF;	/* BAC reset on */
	
	rgs14188_ptr[gio_reg_Hi] &= (long)0xF0;  /* force 1-8 bit modes (bit 4,5 = 0) and Reset (bit 7 lo) */
	rgs14188_ptr[gio_reg_Hi] |= 0x00;  /* set 1 bit mode */
	*((unsigned long *)(base + BT473_COMMAND)) = 0x33;
	*((unsigned long *)(base + BT473_P_ADDR)) = 0;   /* Address $0 */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	*((unsigned long *)(base + BT473_PALETTE)) = 0;   /* LUT Color for red */
	*((unsigned long *)(base + BT473_PALETTE)) = 0;   /* LUT Color for green */
	*((unsigned long *)(base + BT473_PALETTE)) = 0;   /* LUT Color for blue */
	*((unsigned long *)(base + BT473_P_ADDR)) = 0x80;   /* Address $80 */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	*((unsigned long *)(base + BT473_PALETTE)) = ((long) COLOR_ROPS >> 16) & 0x000000ff;   /* LUT Color for red */
	*((unsigned long *)(base + BT473_PALETTE)) = ((long) COLOR_ROPS >> 8) & 0x000000ff;   /* LUT Color for red */
	*((unsigned long *)(base + BT473_PALETTE)) = ((long) COLOR_ROPS) & 0x000000ff;   /* LUT Color for red */
	rgs14188_ptr[gio_reg_Lo] |= 0x40;	/* BAC reset off */
	siSwapMMUMode(&mmu_mode);
}
/*
 * SetEEPROM56()
 */
siSetEEPROM56(slot, pram5, pram6)
short	slot;
short	pram5;
short	pram6;
{
#if MAKING24MXI
	register long	*eep;
	short	w;
	
	eep = (long *) ((unsigned long) devBase(slot) | EEPROM);
	w = (pram5 << 8) | (pram6 & 0x00ff);
	sieeWriteWord(eep, (short) 3, w);
#else
	register unsigned long	base;
	
	base = ((unsigned long) devBase(slot));
	sii2cWriteByte(base, 6, pram5);
	sii2cWriteByte(base, 7, pram6);
#endif
}
/*
 * siSetFatSkinny()
 */
siSetFatSkinny(base, mode)
register unsigned long	base;
short			mode;
{
	char	mmu_mode;
	register short	dummy;
	
	mmu_mode = true32b;
	siSwapMMUMode(&mmu_mode);
	if(mode == FATMODE) {
		dummy = *(long *)(base + FATSLOT);
		#if MAKING24MXI
		dummy = *(unsigned long *)(base + ADDRMODE1);	/* address mode for Mx */
		#else
		*(unsigned long *)(base + ADDRMODE1) = dummy;	/* address mode for MxTV */
		#endif
		#if MAKING24MXI
		dummy = *(unsigned long *)(base + ADDRMODE2);	/* address mode for Mx */
		#endif
	}
	else {
		*(long *)(base + FATSLOT) = 0;
	}
	siSwapMMUMode(&mmu_mode);
}
#if 0
/*
 * SetPRAM()
 */
siSetPRAM(slot, PRAMPtr)
short					slot;
register SPRAMRecord	*PRAMPtr;		/* where to store the PRAM record */
{
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	/* set up params for slot manager call */
	SpPtr->spSlot = slot;	
	SpPtr->spExtDev = 0;	
	SpPtr->spsPointer = (char *) PRAMPtr;
	siSPutPRAMRec(SpPtr);
}
/*
 * SetPRAM6()
 */
short siSetPRAM6(slot, val)
short	slot;
short	val;
{
	SPRAMRecord				PRAMRec;				/* temp storage for pram record */
	register SPRAMRecord	*PRAMPtr = &PRAMRec;	/* temp storage for pram record */
	/*
	 * set up parameters for slot manager call
	 */
	siGetPRAM(slot, PRAMPtr);
	PRAMPtr->vendorUse6 = val;
	siSetPRAM(slot, PRAMPtr);
}
#endif
/*
 * showResolution()
 */
showResolution(base, resNum, width, height)
unsigned long	base;
register short	resNum;
register short	width;
register short	height;
{
	register char	*name;
	short			xcenter;
	short			ycenter;
	
	
	eraseScrn(base, width, height);
	si_load_timingtable(base, (short) resNum);
	switch(resNum) {
		case 0x0080:
				name = "s11x8   ";
				break;
		case 0x0081:
				name = "s10x7_75";
				break;
		case 0x0082:
				name = "s10x7_60";
				break;
		case 0x0083:
				name = "s8x6    ";
				break;
		case 0x0084:
				name = "s6x4_67 ";
				break;
		case 0x0085:
				name = "s6x8    ";
				break;
		case 0x0086:
				name = "s6x4ntsc";
				break;
		case 0x0087:
				name = "s7x5pal ";
				break;
		case 0x0088:
				name = "s5x4ntsc";
				break;
		case 0x0089:
				name = "s6x5pal ";
				break;
	}
	
/****	si_draw_bm1(base, "logoMxi ", (short) (width/2), (short) (height/2-24), (long) COLOR_ROPS); */
	si_draw_bm1(base, "panel   ", (short) (width/2), (short) (height/2 /* +39 */), (long) COLOR_ROPS);	
	xcenter = width/2 - 256/2 + 84;
	ycenter = height/2 - 128/2 + 65; /*104;*/
	si_draw_bm1(base, name, xcenter, ycenter, (long) COLOR_ROPS); 
}
/*
 * toggle the icons
 */
toggle_icons(base, width, height)
unsigned long	base;
short			width;
short			height;
{
	register unsigned char	*dest1;
	register unsigned char	*dest2;
	register short			i;
	register short			j;
	short					logox;
	short					logoy;
	
	char					mmu_mode;	
  
	mmu_mode = 1;	/* 32 bit mode */
	siSwapMMUMode(&mmu_mode);
  
/*	siSetFatSkinny(base, (short) SKINNYMODE); */
	logox = width/2 - 256/2;
	logoy = height/2 - 128/2;
	
	dest1 = (unsigned char *) base;
	dest2 = (unsigned char *) base;
	
	dest1 += ((long) DEF_ROWBYTES * (logoy + (88 - 39))) + (logox + 160L)/8;
	dest2 += ((long) DEF_ROWBYTES * (logoy + (88 - 39))) + (logox + 200L)/8;
	
	for(i = 0; i < 32; i++) {
		for(j = 0; j < 32/8; j++) {
			*dest1 = ~(*dest1);
			*dest2 = ~(*dest2);
			dest1++;
			dest2++;
		}
		dest1 += (DEF_ROWBYTES - 32/8);
		dest2 += (DEF_ROWBYTES - 32/8);
	}
	
	siSwapMMUMode(&mmu_mode);
}
/*
 * _siwaitnms()
 */
siwaitnms(n)
register short	n;
{
	while(n-- > 0) {
		siwait1ms();
	}
}
/*
 * _siwait1ms()
 */
#asm
_siwait1ms
	CLR.L	D0
	MOVE.W	$D00,D0			; Get TimeDBRA Global
simore_dbras				; Loop for 1 ms
	DBRA	D0,simore_dbras
	RTS
#endasm 
/*
 * _siSwapMMUMode()
 */
#asm
;__________________________________________________________________________________________________
; Subroutine Swaps MMU Mode
; expects pointer to new mode on stack
; returns old mode in place of new mode with pointer still on the stack
_siSwapMMUMode
	MOVE.L	4(SP),A0
	MOVE.B	(A0),D0
	_SwapMMUMode		; SwapMMUMode $A05D
	MOVE.L	4(SP),A0
	MOVE.B	D0,(A0)
	RTS
#endasm 
/*
 * Delay(Ticks) Glue
 */
#asm
_siDelay
	MOVE.L	4(SP),A0
	_Delay
	RTS
#endasm 
#if 0
/*
 * SReadPRAMRec(spPtr)
 */
#asm
_siSReadPRAMRec
	MOVE.L	4(SP),A0
	MOVEQ	#$11,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SPutPRAMRec(spPtr)
 */
#asm
_siSPutPRAMRec
	MOVE.L	4(SP),A0
	MOVEQ	#$12,D0
	DC.W	$A06E
	RTS
#endasm 
#endif
/*
 * sVersion(SpPtr) Glue
 */
#asm
_sisVersion
	MOVE.L	4(SP),A0
	MOVEQ	#8,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SRsrcInfo(spPtr) Glue
 */
#asm
_siSRsrcInfo
	MOVE.L	4(SP),A0
	MOVEQ	#$16,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SFindStruct(spPtr) Glue
 */
#asm
_siSFindStruct
	MOVE.L	4(SP),A0
	_SFindStruct
	RTS
#endasm 
/*****************************************************************************
 * siEEPROM code
 *****************************************************************************/
#if MAKING24MXI
/*
 * sieeEnable()
 */
void sieeEnable(eep)
register long	*eep;	/* address of EE Prom */
{
	siEESendStartOpAddr(eep, (short) OP_EWEN, (short) ADDR_EWEN);
	siEEEpilog(eep);
}
/*
 * sieeDisable()
 */
void sieeDisable(eep)
register long	*eep;	/* address of EE Prom */
{
	siEESendStartOpAddr(eep, (short) OP_EWDS, (short) ADDR_EWDS);
	siEEEpilog(eep);
}
/*
 * sieeWriteWord()
 */
void sieeWriteWord(eep, addr, data)
register long	*eep;	/* address of EE Prom */
short			addr;
short			data;
{	
	sieeEnable(eep);
	siEESendStartOpAddr(eep, (short) OP_WRITE, addr);
	siEESendData(eep, data);
	siEEPollReady(eep);
	siEEEpilog(eep);
	sieeDisable(eep);
}	
/*
 * siEEPollReady()
 *
 * wait till data written is ready
 * quit after 10 ms no matter what
 */
short siEEPollReady(eep)
register long	*eep;	/* address of EE Prom */
{
	long	bits;
	short	i;
	siEEPoke(eep, 0, 0, 0);
	siEEPoke(eep, 1, 0, 0);
	siwait1ms();
	
	i = 10;
	while(i--) {
		bits = siEEPeek(eep);
		if(bits & 0x01) {
			return 1;
		}
		siwait1ms();
	}
	return 0;
}
/*
 * siEESendBitStream()
 */
void siEESendBitStream(eep, bits, n)
register long	*eep;	/* address of EE Prom */
register short	bits;	/* bits to send to eep */
register short	n;		/* number of bits to send, bits are right justified */
{
	bits <<= (16 - n);
	while(n--) {
		if(bits >= 0) {
			siEEPoke(eep, 0, 1, 0);
			siEEPoke(eep, 1, 1, 0);
		}
		else {
			siEEPoke(eep, 0, 1, 1);
			siEEPoke(eep, 1, 1, 1);
		}
		bits <<= 1;
	}
}
/*
 * siEESendStartOpAddr()
 */
void siEESendStartOpAddr(eep, opcode, addr)
register long	*eep;	/* address of EE Prom */
register short	opcode;
register short	addr;
{
	siEEProlog(eep);	 	
	siEESendOpcode(eep, opcode);
	siEESendAddr(eep, addr);
}
/*
 * sieePoke()
 */
void sieePoke(eep, bits)
long	*eep;	/* address of EE Prom */
short	bits;
{
	char	mmu_mode;
	
	mmu_mode = true32b;
	siSwapMMUMode(&mmu_mode);
	*eep = (long) bits;
	siSwapMMUMode(&mmu_mode);
}
/*
 * sieePeek()
 */
short sieePeek(eep)
long	*eep;	/* address of EE Prom */
{
	char			mmu_mode;
	register long	w;
	
	mmu_mode = true32b;
	siSwapMMUMode(&mmu_mode);
	w = *eep;
	siSwapMMUMode(&mmu_mode);
	return ((short) w);
}
#endif
#if MAKING24MXTV
/*****************************************************************************
 * i2cEEPROM code (24MxTV)
 *****************************************************************************/
/*
 * i2cGetSCL()
 */
short
sii2cGetSCL(base)
long	base;
{
	unsigned char	mmu_mode;
	register unsigned short	the_data;
	
	mmu_mode = 1;		/* prepare to change to 32 bit mode */
	siSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	the_data = (*((unsigned long *)(base + pip_i2c)) & pip_i2c_clock) ? 1:0;
	siSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
	return the_data;
}
/*
 * i2cGetSDA()
 */
short
sii2cGetSDA(base)
long	base;
{
	unsigned char	mmu_mode;
	register unsigned short	the_data;
	
	mmu_mode = 1;		/* prepare to change to 32 bit mode */
	siSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	the_data = (*((unsigned long *)(base + pip_i2c)) & pip_i2c_data) ? 1:0;
	siSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
	return the_data;
}
/*
 * i2cSendBit()
 */
sii2cSendBit(base, bit)
register long	base;
register short	bit;
{
	if(!bit) {
		siSCL0_SDA0(base);
		siSCL1_SDA0(base);
	}
	else {
		siSCL0_SDA1(base);
		siSCL1_SDA1(base);
	}
}
/*
 * i2cSendByte()
 */
sii2cSendByte(base, s)
register long	base;
short	s;
{
	register char	b;
	register short	k;
	
	b = (char) s;
	k = 8;
	while(k--) {
		if(b >= 0)
			sii2cSendBit(base, 0);
		else
			sii2cSendBit(base, 1);
		b <<= 1;
	}
}
		
/*
 * i2cSendStartBit()
 */
short
sii2cSendStartBit(base)
register long	base;
{
	register short	i;
	register short	j;
	
	for(i = 0; i < 20; i++) {
		for(j = 0; j < 100; j++) {
			if((sii2cGetSCL(base) && sii2cGetSDA(base))) {
				goto getout;
			}
		}
		sii2cSendStopBit(base);
	}
	return -1;
getout:
	siSDA0(base);
	siSCL0(base);
	return 0;
}
/*
 * i2cSendStopBit()
 */
sii2cSendStopBit(base)
register long	base;
{
/*
	siSCL0_SDA0(base);
	siSCL0_SDA0(base);
	siSCL1_SDA0(base);
	siSCL1_SDA1(base);
*/
	siSDA1(base);
	siSCL0(base);
	siSCL1(base);
	
	siSCL0(base);
	siSDA0(base);
	siSCL1(base);
	siSDA1(base);
}
/*
 * i2cSetSCL()
 */
sii2cSetSCL(base, clock)
register long	base;
short	clock;
{
	register unsigned long	i2cState;
	unsigned char	mmu_mode;
	
	mmu_mode = 1;		/* prepare to change to 32 bit mode */
	siSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	i2cState = *((unsigned long *)(base + pip_i2c));
	
	if(clock)
		i2cState |= pip_i2c_clock;
	else
		i2cState &= ~pip_i2c_clock;
		
	*((unsigned long *)(base + pip_i2c)) = i2cState;
	siSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
	
	if(clock)
		siDelaySCL1();
	else
		siDelaySCL0();
}
/*
 * i2cSetSDA()
 */
sii2cSetSDA(base, data)
register long	base;
short	data;
{
	register unsigned long	i2cState;
	unsigned char	mmu_mode;
	
	mmu_mode = 1;		/* prepare to change to 32 bit mode */
	siSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	i2cState = *((unsigned long *)(base + pip_i2c));
	
	if(data)
		i2cState |= pip_i2c_data;
	else
		i2cState &= ~pip_i2c_data;
		
	*((unsigned long *)(base + pip_i2c)) = i2cState;
	siSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
}
/*
 * i2cSetSCLSDA()
 */
sii2cSetSCLSDA(base, clock, data)
register long	base;
register short	clock;
register short	data;
{
	register unsigned long	i2cState;
	unsigned char	mmu_mode;
	
	mmu_mode = 1;		/* prepare to change to 32 bit mode */
	siSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	i2cState = *((unsigned long *)(base + pip_i2c));
	
	if(clock == 1)
		i2cState |= pip_i2c_clock;
	else
		i2cState &= ~pip_i2c_clock;
	if(data == 1)
		i2cState |= pip_i2c_data;
	else
		i2cState &= ~pip_i2c_data;
		
	*((unsigned long *)(base + pip_i2c)) = i2cState;
	siSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
	
	if(clock)
		siDelaySCL1();
	else
		siDelaySCL0();
}
/*
 * i2cWaitAck()
 */
sii2cWaitAck(base)
register long	base;
{
	siSCL0_SDA1(base);
	sii2cWaitSDA0(base);
	siSCL1_SDA1(base);
	sii2cWaitSCL1(base);
}
/*
 * i2cWaitSCL1()
 */
short
sii2cWaitSCL1(base)
register long	base;
{
	register short	i;
	
	for(i = 3000; i > 0; i--) {
		if(sii2cGetSCL(base) == 1)
			return 0;
		else 
			siDelaySCL1();
	}
	return -1;
}
/*
 * i2cWaitSDA0()
 */
short
sii2cWaitSDA0(base)
register long	base;
{
	register short	i;
	
	for(i = 3000; i > 0; i--) {
		if(sii2cGetSDA(base) == 0)
			return 0;
		else 
			siDelaySCL0();
	}
	return -1;
}
/*
 * i2cWriteByte(base, addr, data)
 */
sii2cWriteByte(base, addr, data)
register long	base;
register short	addr;
register short	data;
{	
	sii2cSendStartBit(base);
	sii2cSendSlaveAddr(base, (short) (I2CADDR | I2CWRITE));
	sii2cWaitAck(base);
	sii2cSendWordAddr(base, addr);
	sii2cWaitAck(base);
	sii2cSendData(base, data);
	sii2cWaitAck(base);
	sii2cSendStopBit(base);
	
	/*
	 * wait for 30 ms
	 */
	siwaitnms(30);
}
/*
 * siclock_wait()
 */
siclock_wait(count)
register short	count;
{	
	count--;
	while(count-- >= 0)
		;
}
#endif
#asm
; ==================END OF SECONDARY INIT BLOCK=====================
endsecondaryinit
#endasm
/* My 68020 Driver sBlock */
#asm
mydrvr
; ==================BEGINNING OF DRIVER BLOCK=====================
    dc.l  endmydrvr-mydrvr          ; Length of sBlock
#endasm
/* RasterOps Video Driver */
#asm
_main
    dc.w    $4C00             ; driver responds to Control and Status, NeedsLock
    dc.w    0                 ; NOT A DA (was "update every x seconds")
    dc.w    0                 ; NOT A DA (was "detect events")
    dc.w    0                 ; NOT A DA (was "menu ID number")
    dc.w    _open-_main    ; open routine
    dc.w    _prime-_main     ; prime routine (not needed for this driver)
    dc.w    _control-_main   ; control routine
    dc.w    _status-_main    ; status routine
    dc.w    _close-_main   ; close routine
    dc.b    _titleend-_title
_title
                 ;  Be sure to use this format:  ".RasterOps VVV BBBBB xxx..."
                 ;  Where VVV = Version number of the driver,
                 ;        BBBBB = Board model
                 ;        xxx... = Anything else you want to say.
                 ;  The "Ops ", and BBBBB are checked by the 24-bit environment installer
                 ;  to determine if this hardware can support that environment, so be
                 ;  sure to include them in this format if you want the environment to
                 ;  recognize your hardware.
 if MAKING24MXI
    dc.b    ".RasterOps 2.1 24Mxi Video Driver"
 else
	if MAKING24MXRGB
  		dc.b    ".RasterOps 2.1 24MxRGB Video Driver"
	else
  		dc.b    ".RasterOps 2.1 24MxTV Video Driver"
	endc
 endc
_titleend
    ds      0                ;for alignment
_save
    move.l    8(sp),a2
    move.l    a0,(a2)        ; save pb +-pointer
    move.l    4(sp),a2
    move.l    a1,(a2)        ; save DCE pointer
    rts
_mysintinstall               ; Had to do this myself due to bug in library
    move.w    8(sp),d0
    move.l    4(sp),a0
    dc.w      $A075          ; SIntInstall
    rts
_mysintremove                ; Had to do this myself due to bug in library
    move.w    8(sp),d0
    move.l    4(sp),a0
    dc.w      $A076          ; SIntRemove
    rts
_drSwapMMUMode
    MOVE.L  4(SP),A0
    MOVE.B  (A0),D0
    DC.W    $A05D         ; SwapMMUMode
    MOVE.L  4(SP),A0
    MOVE.B  D0,(A0)
    RTS
_drwait1ms
	CLR.L	D0
	MOVE.W	$D00,D0		; Get TimeDBRA Global
drmore_dbras			; Loop for 1 ms
	DBRA	D0,drmore_dbras
	RTS
#endasm
/*
 * drwaitnms
 */
drwaitnms(n)
register short	n;
{
	while(n-- > 0) {
		drwait1ms();
	}
}
/*
 * grayscrn()
 */
grayscrn(base, mode, msp)
unsigned long	base;
short			mode;
mystoragePtr	msp;
{
	register short			i;
	register short			j;
	register long			pattern;
	register long			black;
	register unsigned long	*to;
	short					width;
	short					height;
	register unsigned long	memWidth;
	char					mmu_mode;
	
	/*
	 * black screen
	 */
	/*drBlackMem(base, (short) (1 << (mode&0x7)));*/
	width = msp->xSize;
	height = msp->ySize;
	memWidth = msp->disp_pitch * 4;
	switch(mode & 0x7) {
		case 0:			/* 1bit */
			width >>= 5;			/* we use number of longs */
			memWidth >>= 2;
			pattern = 0xaaaaaaaa;
			black = 0xffffffff;
			break;
		case 1:			/* 2bit */
			width >>= 4;
			memWidth >>= 2;
			pattern = 0xcccccccc;
			black = 0xffffffff;
			break;
		case 2:			/* 4bit */
			width >>= 3;
			memWidth >>= 2;
			pattern = 0xf0f0f0f0;
			black = 0xffffffff;
			break;
		case 3:			/* 8bit */
			width >>= 2;
			memWidth >>= 2;
			pattern = 0xff00ff00;
			black = 0xffffffff;
			break;
		case 4:			/* 16bit */
			width >>= 1;
			memWidth >>= 1;
			pattern = 0x0000ffff;
			black = 0x0;
			break;
		case 5:			/* 32bit */
			pattern = 0x00000000;
			black = 0x0;
			break;
	}
		
	/*
	 * paint black on the right handside of the screen
	 * then paint gray the visible part of the screen
	 */
	mmu_mode = 1;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
    
	to = (unsigned long *) (base);
	i = height;
	if((mode & 0x7) != 5) {		/* 1bit - 16bit mode */
		while(i--) {
			/* paint gray */
			j = width;
			while(j--) {
				*to++ = pattern;
			}
			/* paint black */
			j = memWidth - width;
			while(j--) {
				*to++ = black;
			}
			
			pattern = ~pattern;
		}
	}
	else {						/* 32bit mode */
		while(i--) {
			/* paint gray */
			j = width/2;
			while(j--) {
				*to++ = pattern;
				*to++ = ~pattern;
			}
			/* paint black */
			j = memWidth - width;
			while(j--) {
				*to++ = black;
			}
			pattern = ~pattern;
		}
	}
	drSwapMMUMode(&mmu_mode);
}
/******************************************************************/
/* Set dacs to all gray to avoid flashes when changing bit depths */
/******************************************************************/
graytable(base)
unsigned long base;
{
#asm
	BRA.S	grayStart
grayRegs
	DC.L	0,0,0,0
	
grayStart
	MOVE.L	A0,D0
	LEA		grayRegs,A0
	MOVE.L	D1,(A0)+
	MOVE.L	D2,(A0)+
	MOVE.L	D3,(A0)+
	MOVE.L	D0,(A0)+
	MOVEA.L	8(SP),A0
	ADDA.L	#$FA0000,A0
	MOVEQ	#1,D0
	_SwapMMUMode
	MOVE.L	D0,D3
	MOVE.L	#$FF,D0
	CLR.L	(A0)+
	
grayLoop
    MOVE.L	#$B0,(A0)
    MOVE.L	#$B0,(A0)
    MOVE.L	#$B0,(A0)
	DBRA	D0,grayLoop
	MOVE.L	D3,D0
	_SwapMMUMode
	LEA		grayRegs,A0
	MOVE.L	(A0)+,D1
	MOVE.L	(A0)+,D2
	MOVE.L	(A0)+,D3
	MOVE.L	(A0)+,D0
	MOVEA.L	D0,A0
#endasm
}
/************************************************************************************/
/* Called with a word (OSErr error) on the stack indicating an error code */
#asm
_checkiodone
   move.w  4(sp),D0      ; Return error code for now
   BTST    #1,6(A0)      ; Check ioTrap field of the paramblock if it has the "NoQueue" bit set.
   BEQ.S   _goiodone     ; The bit wasn't set, so it has a queue element allocated for it.  Go do jIODone.
   RTS                   ; Go back for a normal return since no queue element was allocated.
_goiodone
   add.l   #6,sp         ; Pop our return address away, and error code
   unlk    a6            ; Unlink the subroutine (Return address is now on top of stack)
   MOVEA.L $8FC,A0       ; Load address of jIODone routine
   JMP     (A0)          ; Use it to exit with
#endasm
/*
 * declarations
 */
unsigned long adjust_pan();
void PanTo();
void ZoomIn();
void ZoomOut();
void PanY();
void calcRects();
unsigned char get_zoom();
void set_zoom();
void get_disp_start();
void set_disp_start();
unsigned long dr_get_rgs();
void set_rgs();
void CheckPip();
Boolean PipIsOff();
void TurnPipOff();
/*
 * GetPRAM()
 */
drGetPRAM(slot, PRAMPtr)
short					slot;
register SPRAMRecord	*PRAMPtr;		/* where to store the PRAM record */
{
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	/* set up parameters for slot manager call */
	SpPtr->spSlot = slot;	
	SpPtr->spExtDev = 0;	
	SpPtr->spResult = (unsigned long) PRAMPtr;
	drSReadPRAMRec(SpPtr);
}
	
/*
 * GetPRAM5()
 */
short drGetPRAM5(slot)
short	slot;
{
	SPRAMRecord				PRAMRec;				/* temp storage for pram record */
	register SPRAMRecord	*PRAMPtr = &PRAMRec;	/* temp storage for pram record */
	/*
	 * set up parameters for slot manager call
	 */
	drGetPRAM(slot, PRAMPtr);
	return ((short) PRAMPtr->vendorUse5 & 0x00ff);
}
	
/*
 * GetPRAM6()
 */
short drGetPRAM6(slot)
short	slot;
{
	SPRAMRecord				PRAMRec;				/* temp storage for pram record */
	register SPRAMRecord	*PRAMPtr = &PRAMRec;	/* temp storage for pram record */
	/*
	 * set up parameters for slot manager call
	 */
	drGetPRAM(slot, PRAMPtr);
	return ((short) PRAMPtr->vendorUse6 & 0x00ff);
}
/*
 * SetEEPROM56()
 */
drSetEEPROM56(slot, pram5, pram6)
short	slot;
short	pram5;
short	pram6;
{
#if MAKING24MXI
	register long	*eep;
	short	w;
	
	eep = (long *) ((unsigned long) devBase(slot) | EEPROM);
	w = (pram5 << 8) | (pram6 & 0x00ff);
	dreeWriteWord(eep, (short) 3, w);
#else
	register unsigned long	base;
	
	base = ((unsigned long) devBase(slot));
	dri2cWriteByte(base, 6, pram5);
	dri2cWriteByte(base, 7, pram6);
#endif
}
/*
 * SetPRAM()
 */
drSetPRAM(slot, PRAMPtr)
short					slot;
register SPRAMRecord	*PRAMPtr;		/* where to store the PRAM record */
{
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	/* set up params for slot manager call */
	SpPtr->spSlot = slot;	
	SpPtr->spExtDev = 0;	
	SpPtr->spsPointer = (char *) PRAMPtr;
	drSPutPRAMRec(SpPtr);
}
/*
 * SetPRAM5()
 */
short drSetPRAM5(slot, val)
short	slot;
short	val;
{
	SPRAMRecord				PRAMRec;				/* temp storage for pram record */
	register SPRAMRecord	*PRAMPtr = &PRAMRec;	/* temp storage for pram record */
	/*
	 * set up parameters for slot manager call
	 */
	drGetPRAM(slot, PRAMPtr);
	PRAMPtr->vendorUse5 = val;
	drSetPRAM(slot, PRAMPtr);
}
/*
 * SetPRAM6()
 */
short drSetPRAM6(slot, val)
short	slot;
short	val;
{
	SPRAMRecord				PRAMRec;				/* temp storage for pram record */
	register SPRAMRecord	*PRAMPtr = &PRAMRec;	/* temp storage for pram record */
	/*
	 * set up parameters for slot manager call
	 */
	drGetPRAM(slot, PRAMPtr);
	PRAMPtr->vendorUse6 = val;
	drSetPRAM(slot, PRAMPtr);
}
/*
 * SReadPRAMRec(spPtr)
 */
#asm
_drSReadPRAMRec
	MOVE.L	4(SP),A0
	MOVEQ	#$11,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SPutPRAMRec(spPtr)
 */
#asm
_drSPutPRAMRec
	MOVE.L	4(SP),A0
	MOVEQ	#$12,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SetSRsrcState(spPtr)
 */
#asm
_drSetSRsrcState
	MOVE.L	4(SP),A0
	MOVEQ	#$09,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SRsrcInfo(spPtr) Glue
 */
#asm
_drSRsrcInfo
	MOVE.L	4(SP),A0
	MOVEQ	#$16,D0
	DC.W	$A06E
	RTS
#endasm 
/*
 * SFindStruct(spPtr) Glue
 */
#asm
_drSFindStruct
	MOVE.L	4(SP),A0
	_SFindStruct
	RTS
#endasm 
/*
 * SUpdateSRT(spPtr) Glue
 */
#asm
_drSUpdateSRT
	MOVE.L	4(SP),A0
	_SUpdateSRT
	RTS
#endasm 
/********************************************************************************************/
/* V1.43 */
/********
void modPRAM(slot)
short slot;
{
#asm
    BRA.S   modPRAM
modPRAMRec
    DC.W    0
    DC.W    0
    DC.W    0
    DC.W    0
modPRAM
    MOVE.W   8(A6),D0			; Get the slot number
    LEA     -56(SP),SP          ; Allocate a SpBlock on the stack
    MOVE.L  SP,A0               ; Get the address of the SpBlock in A0 (required by slot manager calls)
    MOVE.B  D0,49(A0)           ; Poke the slot number
    CLR.B   51(A0)              ; Poke the external device number (we don't have one, so zero)
    LEA     modPRAMRec,A1
    MOVE.L  A1,0(A0)
    MOVEQ   #17,D0              ; Use the sReadPRAMRec call of the slot manager
    DC.W    $A06E               ; _SlotManager
    LEA     modPRAMRec,A1		; Get the address of our PRAM record
    CMP.B  	#$88,7(A1)			; check for Extended Desktop 1024x1024 or greater
	BLT.S   modDone
; We have the Extended Desktop in effect
    CMP.B	#$80,2(A1)			; what is the requested pixel depth?
	BEQ.S	modDone				; B/W
; We have both the Extended DeskTop and a request to set the desktop to color pixel depth
    MOVE.B	#$80,2(A1)			; save the new pixel depth	
    MOVE.L  SP,A0               ; Get the address of the SpBlock in A0 (required by slot manager calls)
    MOVE.L  A1,4(A0)			; put a pointer to the pRAM record in the SpsPointer field
    MOVEQ   #18,D0              ; Use the sPutPRAMRec call of the slot manager
    DC.W    $A06E               ; _SlotManager
modDone
    LEA     56(SP),SP           ;We don't check errors, so just repair the stack and exit
#endasm
}
*/
/*
 *	set_energy_save_state_rgs14188
 */
void	set_energy_save_state_rgs14188(new_state, msp)
unsigned char	new_state;
mystoragePtr	msp;
{
	unsigned long	temp;
	unsigned long	base;
	rgs14188_data	*save_timing;
	char			mmu_mode;
	
	save_timing = &msp->save_timing;
	base = msp->base;
	
#if MAKING24MXTV
	/* non-interlaced && 1x zoom && non-extended needs to have refresh off */
	if(new_state != POWER_ON)
	{
		mmu_mode = 1;	/* 32 bit mode */
		drSwapMMUMode(&mmu_mode);
	 	REFRESH_ON(base);
		drSwapMMUMode(&mmu_mode);
	}
#endif
	switch(new_state)
	{
		case POWER_ON:
			switch(msp->sync_state)
			{
				case POWER_OFF:
/*DebugStr("\Pset_energy_save_state_s3_86c805 POWER_OFF to POWER_ON");*/
					/* Restore original vertical timing */
					set_rgs(base, vert_end_sync, (long)save_timing->ves, (short)1);
					set_rgs(base, vert_total, (long)save_timing->vtot, (short)2);
					set_rgs(base, vert_start_blank, (long)save_timing->vsb, (short)2);
					set_rgs(base, vert_int_line, (long)save_timing->vil, (short)2);
					/* Restore original horizontal timing */
					set_rgs(base, horiz_total, (long)save_timing->htot, (short)2);
				case POWER_STANDBY:
/*DebugStr("\Pset_energy_save_state_s3_86c805 POWER_STANDBY to POWER_ON");*/
					/* Restore original horizontal timing */
					set_rgs(base, horiz_end_sync, (long)save_timing->hes, (short)2);
				case POWER_ON:
					break;
			}
			break;
		
		case POWER_STANDBY:
			switch(msp->sync_state)
			{
				case POWER_OFF:
/*DebugStr("\Pset_energy_save_state_s3_86c805 POWER_OFF to POWER_STANDBY");*/
					/* Restore original horizontal timing */
					set_rgs(base, horiz_total, (long)save_timing->htot, (short)2);
					/* Set new horizontal timing */
					set_rgs(base, horiz_end_sync, (long)save_timing->htot + 2, (short)2);
					/* Restore original vertical timing */
					set_rgs(base, vert_end_sync, (long)save_timing->ves, (short)1);
					set_rgs(base, vert_total, (long)save_timing->vtot, (short)2);
					set_rgs(base, vert_start_blank, (long)save_timing->vsb, (short)2);
					set_rgs(base, vert_int_line, (long)save_timing->vil, (short)2);
					break;
				case POWER_ON:
/*DebugStr("\Pset_energy_save_state_s3_86c805 POWER_ON to POWER_STANDBY");*/
					/* Save original horizontal timing */
					save_timing->hes = dr_get_rgs(base, horiz_end_sync, (short)2);
					save_timing->htot = dr_get_rgs(base, horiz_total, (short)2);
					/* Set new horizontal timing */
					set_rgs(base, horiz_end_sync, (long)save_timing->htot + 2, (short)2);
				case POWER_STANDBY:
					break;
			}
			break;
		
		case POWER_OFF:
			switch(msp->sync_state)
			{
				case POWER_ON:
/*DebugStr("\Pset_energy_save_state_s3_86c805 POWER_ON to POWER_OFF");*/
					/* Save original horizontal timing */
					save_timing->hes = dr_get_rgs(base, horiz_end_sync, (short)2);
					save_timing->htot = dr_get_rgs(base, horiz_total, (short)2);
				case POWER_STANDBY:
/*DebugStr("\Pset_energy_save_state_s3_86c805 POWER_STANDBY to POWER_OFF");*/
					/* Save original vertical timing */
					save_timing->ves = dr_get_rgs(base, vert_end_sync, (short)1);
					save_timing->vsb = dr_get_rgs(base, vert_start_blank, (short)2);
					save_timing->vtot = dr_get_rgs(base, vert_total, (short)2);
					save_timing->vil = dr_get_rgs(base, vert_int_line, (short)2);
					/* Set new vertical timing */
					set_rgs(base, vert_end_sync, rgs14188_energy_saving_ves, (short)1);
					set_rgs(base, vert_total, rgs14188_energy_saving_vtot, (short)2);
					set_rgs(base, vert_start_blank, rgs14188_energy_saving_vsb, (short)2);
					set_rgs(base, vert_int_line, rgs14188_energy_saving_vil, (short)2);
					/* Set new horizontal timing */
					temp = (long)save_timing->htot * (long)save_timing->vtot;
					temp = temp/rgs14188_energy_saving_vtot;
					set_rgs(base, horiz_end_sync, temp + 2, (short)2);
					set_rgs(base, horiz_total, temp, (short)2);
				case POWER_OFF:
					break;
			}
			break;
	}
#if MAKING24MXTV
	/* non-interlaced && 1x zoom && non-extended needs to have refresh off */
	if((new_state == POWER_ON) && ((msp->monitor_sRsrcId & 0x8f) < FirstInterlaced) && ((msp->desk_sRsrcId & 0x8f) < FirstExtended))
	{
		mmu_mode = 1;	/* 32 bit mode */
		drSwapMMUMode(&mmu_mode);
	 	REFRESH_OFF(base);
		drSwapMMUMode(&mmu_mode);
	}
#endif
}
/*
 * dr_switch_mode()
 *
 * 14 Tables of 48 bytes each, corresponding to the
 * registers on the RGS14188.
 *  Table 80	1152 X 870 75Hz
 *  Table 81	1024 X 768 75Hz
 *  Table 82	1024 X 768 60Hz
 *  Table 83	832 X 624
 *  Table 84	640 X 480 67hz
 *  Table 85	640 X 870
 *  Table 86	640 X 480 NTSC
 *  Table 87	640 X 480 NTSC GenLock
 *  Table 88	768 X 576 PAL
 *  Table 89	768 X 576 PAL GenLock
 *  Table 8A	576 X 432 NTSC
 *  Table 8B	576 X 432 NTSC GenLock
 *  Table 8C	684 X 512 PAL underscan
 *  Table 8D	684 X 512 PAL Genlock underscan
 */
void	dr_switch_mode(msp)
mystoragePtr	msp;
{
 	unsigned long			base;
 	unsigned long			*rgs14188_ptr;
 	unsigned long			*dac_cmd_reg;
	unsigned long			saved_interrupt_control;
	register unsigned long	*table_ptr;
	register short			i;
	unsigned short			timingNum;
	SpBlock					SpBlk;					/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;		/* our sp block to make the slot manager call */
	char					mmu_mode;
	short					GenLock;
/*	myDebugStr("\Pdr_switch_mode"); */
	/* Local copy of base address */
	base =  ((unsigned long)(msp->base) & (unsigned long)0xFF000000);
 	mmu_mode = true32b;		/* prepare to change to 32 bit mode */
	drSwapMMUMode(&mmu_mode);
	GenLock = ISGENLOCK(base);
	drSwapMMUMode(&mmu_mode);
    /* Make pointers to control registers */
	rgs14188_ptr = (unsigned long *)(base + (unsigned long)RGS14188);
	dac_cmd_reg = (unsigned long *)(base + (unsigned long)BT473_COMMAND);
	graytable(base);		/* Set dacs to all gray to avoid flashes when changing bit depths */
	/* Load timing if not extended desktop ID */
	if((msp->desk_sRsrcId & 0x008f) < FirstExtended)
	{
		switch(msp->desk_sRsrcId & 0x008F)
		{
			case RES_ID_11x8:
				timingNum = TIMING_ID_11x8;
				break;
			case RES_ID_10x7_75:
				timingNum = TIMING_ID_10x7_75;
				break;
			case RES_ID_10x7_60:
				timingNum = TIMING_ID_10x7_60;
				break;
			case RES_ID_8x6:
				timingNum = TIMING_ID_8x6;
				break;
			case RES_ID_6x4:
				timingNum = TIMING_ID_6x4;
				break;
			case RES_ID_6x8:
				timingNum = TIMING_ID_6x8;
				break;
	#if MAKING24MXTV	
			case RES_ID_6x4ntsc:
				if(!GenLock)
					timingNum = TIMING_ID_6x4ntsc;
				else
					timingNum = TIMING_ID_6x4ntscGL;
				break;
			case RES_ID_7x5pal:
				if(!GenLock)
					timingNum = TIMING_ID_7x5pal;
				else
					timingNum = TIMING_ID_7x5palGL;
				break;
			case RES_ID_5x4ntsc:
				if(!GenLock)
					timingNum = TIMING_ID_5x4ntsc;
				else
					timingNum = TIMING_ID_5x4ntscGL;
				break;
			case RES_ID_6x5pal:
				if(!GenLock)
					timingNum = TIMING_ID_6x5pal;
				else
					timingNum = TIMING_ID_6x5palGL;
				break;
	#endif
		}
	
		/* Find parameter resource */
		SpPtr->spSlot = (base >> 24) & 0x0F;
		SpPtr->spExtDev = 0;
	
		SpPtr->spID = sRsrcBoard;		/* Find Board Resource */
		drSRsrcInfo(SpPtr);
	
		SpPtr->spID = sTimingTableDir;	/* Find Resoulution Directory */
		drSFindStruct(SpPtr);
	
		SpPtr->spID = timingNum;		/* Find Parameters */
		drSFindStruct(SpPtr);
		
		table_ptr = (unsigned long *)(SpPtr->spsPointer + 16 - 3); /* skip count and adjust byte lane for long access */
		
		/*
		 * Send Initialization Table out to RGS14188
		 */
		mmu_mode = true32b;		/* prepare to change to 32 bit mode */
		drSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
		
		saved_interrupt_control = rgs14188_ptr[control_4] & 0x0007;
		for(i = control_1; i <= soft_reg; i++)
			rgs14188_ptr[i] = table_ptr[i];
			
		/*
		 * Turn on refresh, transfer enable, and sync
		 */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		rgs14188_ptr[control_1] |= 0x91;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		rgs14188_ptr[control_3] |= 0x72;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		rgs14188_ptr[control_1] |= 0xB1;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		rgs14188_ptr[gio_reg_Lo] |= soft_reset_off;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	
		rgs14188_ptr[status_] = 0;	/* clear any pending interrupt */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		rgs14188_ptr[control_4] |= saved_interrupt_control;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
#if MAKING24MXTV
/*	myDebugStr("\Pdr_switch_mode"); */
		/* non-interlaced && 1x zoom && non-extended needs to have refresh off */
		if((msp->desk_sRsrcId & 0x8f) < FirstInterlaced)
			REFRESH_OFF(base);
#endif
		drSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
		msp->monitor_sRsrcId = msp->desk_sRsrcId;
	}
	else
	{
		adjust_pitch(base, msp->desk_sRsrcId);
#if MAKING24MXTV
		mmu_mode = true32b;		/* prepare to change to 32 bit mode */
		drSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
		REFRESH_ON(base);
		drSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
#endif
	}
	msp->disp_pitch = dr_get_disp_pitch(base);
	/* Set mode registers */
	mmu_mode = true32b;		/* prepare to change to 32 bit mode */
	drSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	rgs14188_ptr[gio_reg_Lo] &= 0xBF;	/* BAC reset on */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	rgs14188_ptr[gio_reg_Hi] &= (long)0xF0;  /* force 1-8 bit modes (bit 4,5 = 0) and Reset (bit 7 lo) */
	switch(msp->mode & 0x7)
	{
		case 0:
			rgs14188_ptr[gio_reg_Hi] |= 0x00;  /* set 1 bit mode */
			*dac_cmd_reg |= 0x01;	/* Command Register for other than PAL (7.5 IRE) */
			break;
		case 1:
			rgs14188_ptr[gio_reg_Hi] |= 0x04;  /* set 2 bit mode */
			*dac_cmd_reg |= 0x01;	/* Command Register for other than PAL (7.5 IRE) */
			break;
		case 2:
			rgs14188_ptr[gio_reg_Hi] |= 0x08;  /* set 4 bit mode */
			*dac_cmd_reg |= 0x01;	/* Command Register for other than PAL (7.5 IRE) */
			break;
		case 3:
			rgs14188_ptr[gio_reg_Hi] |= 0x0C;  /* set 8 bit mode */
			*dac_cmd_reg |= 0x01;	/* Command Register for other than PAL (7.5 IRE) */
			break;
		case 4:
			rgs14188_ptr[gio_reg_Hi] |= 0x0D;  /* set 24 bit mode */
			*dac_cmd_reg &= ~0x01;	/* Command Register for other than PAL (7.5 IRE) */
			break;
		case 5:
			rgs14188_ptr[gio_reg_Hi] |= 0x0E;  /* set 24 bit mode */
			*dac_cmd_reg &= ~0x01;	/* Command Register for other than PAL (7.5 IRE) */
			break;
	}
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	rgs14188_ptr[gio_reg_Lo] |= 0x40;	/* BAC reset off */
	drSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
}
/****************************************************************************************/
/* OSErr open                                                                               */
/****************************************************************************************/
#define openErr	-23
#asm
_AppleGamma even
    DC.B	$00,$05,$09,$0B,$0E,$10,$13,$15,$17,$19,$1B,$1D,$1E,$20,$22,$24
	DC.B	$25,$27,$28,$2A,$2C,$2D,$2F,$30,$31,$33,$34,$36,$37,$38,$3A,$3B
	DC.B	$3C,$3E,$3F,$40,$42,$43,$44,$45,$47,$48,$49,$4A,$4B,$4D,$4E,$4F
	DC.B	$50,$51,$52,$54,$55,$56,$57,$58,$59,$5A,$5B,$5C,$5E,$5F,$60,$61
	DC.B	$62,$63,$64,$65,$66,$67,$68,$69,$6A,$6B,$6C,$6D,$6E,$6F,$70,$71
	DC.B	$72,$73,$74,$75,$76,$77,$78,$79,$7A,$7B,$7C,$7D,$7E,$7F,$80,$81
	DC.B	$81,$82,$83,$84,$85,$86,$87,$88,$89,$8A,$8B,$8C,$8C,$8D,$8E,$8F
	DC.B	$90,$91,$92,$93,$94,$95,$95,$96,$97,$98,$99,$9A,$9B,$9B,$9C,$9D
	DC.B	$9E,$9F,$A0,$A1,$A1,$A2,$A3,$A4,$A5,$A6,$A6,$A7,$A8,$A9,$AA,$AB
	DC.B	$AB,$AC,$AD,$AE,$AF,$B0,$B0,$B1,$B2,$B3,$B4,$B4,$B5,$B6,$B7,$B8
	DC.B	$B8,$B9,$BA,$BB,$BC,$BC,$BD,$BE,$BF,$C0,$C0,$C1,$C2,$C3,$C3,$C4
	DC.B	$C5,$C6,$C7,$C7,$C8,$C9,$CA,$CA,$CB,$CC,$CD,$CD,$CE,$CF,$D0,$D0
	DC.B	$D1,$D2,$D3,$D3,$D4,$D5,$D6,$D6,$D7,$D8,$D9,$D9,$DA,$DB,$DC,$DC
	DC.B	$DD,$DE,$DF,$DF,$E0,$E1,$E1,$E2,$E3,$E4,$E4,$E5,$E6,$E7,$E7,$E8
	DC.B	$E9,$E9,$EA,$EB,$EC,$EC,$ED,$EE,$EE,$EF,$F0,$F1,$F1,$F2,$F3,$F3
	DC.B	$F4,$F5,$F5,$F6,$F7,$F8,$F8,$F9,$FA,$FA,$FB,$FC,$FC,$FD,$FE,$FF
#endasm
OSErr open()
{
	AuxDCEPtr				dcep;		/* Auxiliary Device Control Entry pointer. */
	register mystoragePtr	msp; /* pointer to my private storage (pan & zoom use) */
	CntrlParam				*pbp;		/* Application-passed parameter block pointer. */
	THz						oldzone;	/* Previous heap zone */
	long					merror;		/* Memory error */
	SlotIntQElement 		*sqeptr;	/* Slot queue element pointer */
	GammaTable				*gammaptr;	/* Gamma Table Block pointer */
	long					i;			/* Loop counter */
	extern long				intrpthandler,	/* Define the interrupt handling routine as external; */
							intrptend;	/* As well as the end of the interrupt handler. */
	unsigned char			mmu_mode;	/* MMU Mode (0=24-bit addressing 1=32-bit addressing) */
	unsigned long			base;		/* Slot base address */
	unsigned long			*mode_reg1, *mode_reg2, *dac_addr_reg, *dac_data_reg, *dac_mask_reg;
	extern char 			AppleGamma[];	/* The Apple Gamma table */
	short 					theID;
	short 					theID6;
	
	SpBlock sp;
	SPRAMRecord spRec;
	unsigned long basePtr;
	unsigned short rawsize;
	
	#asm
	MOVEM.L A0-A5/D0-D7,-(sp)   ; Save nearly all registers
	#endasm
#if DEBUG
	myDebugStr("\POpen call: enter");
#endif
    /* Get pointers passed in A0, A1 by caller */
	save(&dcep,&pbp);          /* A0 -> pbp, A1 -> dcep */
	/* Get local copy of base address */
	base =  ((unsigned long)(dcep->dCtlDevBase) & (unsigned long)0xFF000000);
	
	/* Reserve space in system heap for private storage */
	oldzone = GetZone();             /* Get current heap zone */
	SetZone(SystemZone());           /* Force memory operations to the System Heap. */
	
	/* Get a handle for our private storage. */
	ResrvMem((long)sizeof(struct mystorage));
	if (!(dcep->dCtlStorage = NewHandle((long)sizeof(struct mystorage))))
	{
		SetZone(oldzone);              /* Force memory operations to the original heap. */
		#asm
		MOVEM.L (SP)+,A0-A5/D0-D7   ; Restore nearly all registers
		#endasm
		return(openErr);                   /* Return that we couldn't open successfully. */
	}
	/* Lock private storage as long as driver is open */
	HLock(dcep->dCtlStorage);
    /* Dereference locked handle to private storage */
	msp = (mystoragePtr)(*(dcep->dCtlStorage));
	msp = (mystoragePtr) StripAddress(msp);
#if 0
	/* Install Interrupts */
	/* ------------------ */
	/* Get a pointer block to hold a copy of our interrupt code */
	if (!(msp->myintrptcode =
	(unsigned char *)NewPtr((unsigned long)&intrptend-(unsigned long)&intrpthandler)))
	{
		/* Release system heap storage and return openErr */
		DisposHandle(dcep->dCtlStorage);
		SetZone(oldzone);              /* Force memory operations to the original heap. */
		#asm
		MOVEM.L (SP)+,A0-A5/D0-D7   ; Restore nearly all registers
		#endasm
		return(openErr);                   /* Return that we couldn't open successfully. */
	}
    /* Copy the code from ourself to a separate pointer block.  That way,
    if the driver needs to be replaced, (as when the 24-bit environment is installed)
    then interrupts never have to be altered since the code is external from
    the old driver (this one) that would be removed in such a replacement.
    Of course, a pointer to the external block is stored in the external
    variable section block (dcep->dCtlStorage) so you can still find it if
    you do, in fact, need to alter it. */
	BlockMove(&intrpthandler,msp->myintrptcode,
		(unsigned long)&intrptend-(unsigned long)&intrpthandler);
#endif
	/* Get a pointer block for slot interrupt queue element */
	if (!(sqeptr = (SlotIntQElement *)NewPtr((long)sizeof(SlotIntQElement))))
	{
		/* Release system heap storage and return openErr */
		/*    DisposPtr(msp->myintrptcode); */
		DisposHandle(dcep->dCtlStorage);
		SetZone(oldzone);              /* Force memory operations to the original heap. */
		#asm
		MOVEM.L (SP)+,A0-A5/D0-D7   ; Restore nearly all registers
		#endasm
		return(openErr);                   /* Return that we couldn't open successfully. */
	}
	SetZone(oldzone);                	/* Force memory operations to the original heap. */
	/* Set up the fields of the slot queue element block. */
	sqeptr->sqLink = 0;
	sqeptr->sqType = 6;
	sqeptr->sqPrio = 0;
	sqeptr->sqAddr = (ProcPtr)&intrpthandler;
	sqeptr->sqParm = dcep->dCtlDevBase;
	/* Install that slot queue element into the interrupt table. */
	if(mysintinstall(sqeptr,dcep->dCtlSlot))
	{
		/* Release system heap storage and return openErr */
		DisposPtr(sqeptr);
		/*    DisposPtr(msp->myintrptcode); */
		DisposHandle(dcep->dCtlStorage);
		#asm
		MOVEM.L (SP)+,A0-A5/D0-D7	; Restore nearly all registers
		#endasm
		return(openErr);				/* Return that we couldn't open successfully. */
	}
	/* Save the slot queue element block pointer for disposal in close */
	msp->myslotqeleptr = sqeptr;
	msp->myintrptcode = (unsigned char *)&intrpthandler;
	
	msp->slot = dcep->dCtlSlot;
	msp->base = base;
	msp->screenbase = (dcep->dCtlDevBase);;
	theID     = drGetPRAM5(msp->slot);		/* Get the sResource formed from the switches */
	theID6    = drGetPRAM6(msp->slot);		/* Get the Extended or NTSC/PAL sResource */
	theID    &= 0xFF;
	theID6   &= 0xFF;
	
	/* Turn on interrupts */
	mmu_mode = 1;						/* 32 bit addressing mode */
	drSwapMMUMode(&mmu_mode);
	((unsigned long *)(base + RGS14188))[control_4] |= 5; 
	drSwapMMUMode(&mmu_mode);			/* Swap back */
	
	/* Set flag to show interrupts enabled */
	msp->intflag = 1;
	/* -----------------------------End Install Interrupts------------------------------ */
	
	/* Allocate Gamma starage in system heap and Initialize Gamma table */
	/* Reserve space in system heap for the gamma table */
	oldzone = GetZone();             	/* Get current heap zone */
	SetZone(SystemZone());           	/* Force memory operations to the System Heap. */
	
	/* Get a pointer block for our default gamma table. */
	if (!(gammaptr = (GammaTablePtr)NewPtr((unsigned long)sizeof(struct GammaTable))))
	{
		mysintremove(sqeptr,dcep->dCtlSlot);	/* Pull our interrupts out. */      
		DisposPtr(sqeptr);					/* Release system heap storage and return openErr */
		DisposPtr(msp->myintrptcode);
		DisposHandle(dcep->dCtlStorage);
		SetZone(oldzone);              		/* Force memory operations to the original heap. */
		#asm
		MOVEM.L (SP)+,A0-A5/D0-D7   ; Restore nearly all registers
		#endasm
		return(openErr);                   		/* Return that we couldn't open successfully. */
	}
	SetZone(oldzone);                	/* Force memory operations to the original heap. */
	
	msp->mygammaptr = gammaptr;	/* Save the gamma table block pointer for disposal in close */
	
	/* Initialize Gamma Table */
	gammaptr->gVersion 	 = 0;      	/* Currently 0 for all cards */
	gammaptr->gType 		 = DrHw;	/* DrHwTFB = 0 */
	gammaptr->gFormulaSize = 0;  		/* Formula size = 0, no formula data */
	gammaptr->gChanCnt 	 = 1;      	/* One table for all of r,g, & b, could be 3 for separate r,g, & b tables */
	gammaptr->gDataCnt 	 = 256;  	/* 256 entries per table */
	gammaptr->gDataWidth 	 = 8;    	/* 8 bits per entry */
	
	/* Values in initial Gamma Table are the Apple Gamma Table (ROM) values */
	for (i=0;i<256;i++)
		gammaptr->gData.gRTable[i] = gammaptr->gData.gGTable[i] = gammaptr->gData.gBTable[i] = AppleGamma[i];
	/* Allocate lutBuffer storage in system heap. */
	oldzone = GetZone();             /* Get current heap zone */
	SetZone(SystemZone());           /* Force memory operations to the System Heap. */
	
	/* Get a pointer block for our default gamma table. */
	if (!(msp->lutBuffer = NewPtr(1024L)))
	{
		/* Pull our interrupts out. */
		mysintremove(sqeptr,dcep->dCtlSlot);
		
		/* Release system heap storage and return openErr */
		DisposPtr(sqeptr);
		DisposPtr(gammaptr);
		DisposPtr(msp->myintrptcode);
		DisposHandle(dcep->dCtlStorage);
		SetZone(oldzone);              /* Force memory operations to the original heap. */
		#asm
		MOVEM.L (SP)+,A0-A5/D0-D7   ; Restore nearly all registers
		#endasm
		return(openErr);               /* Return that we couldn't open successfully. */
	}
	SetZone(oldzone);                /* Force memory operations to the original heap. */
	msp->bwmapping = 0;			/* Set Gray mapping off */
	
	/* Set flag to tell gamma that new mode is set and graypage will set lut ramp (below)*/
	msp->newmode = 0;
	msp->mode    = 0; 		/* to be sure first control 2 mode change happens */
#if DEBUG
	myDebugStr("\Open call: set resolutions");
#endif
	drGetWH(theID, &msp->xResolution, &msp->yResolution);
	msp->screensize = msp->xResolution;
	/* Check PRAM vendorUse6 for the type of Extended DeskTop selected */
	drGetWH(theID6, &msp->xSize, &msp->ySize);
	/* Initialize the pan and zoom globals */
	msp->zoom         = x1;		/* Zoom x1 													*/
	msp->currentRate  =  0;		/* No panning until zoomed or Virtual DeskTop is enabled 	*/
	msp->currentZoom  =  1;		/* No zooming until chosen by a key 						*/
	msp->currentX 	  =  0;		/* 0,0 														*/
	msp->currentY 	  =  0;
	msp->border 	  = 10;		/* Ten pixels difference between fast and slow panning 		*/
	msp->refNum	  	  = dcep->dCtlRefNum;
	msp->zCenter      = true;	/* Zoom to screen center is default.						*/
	msp->theMode	  = msp->mode & 0x0F;	/* Strip out the hi-bits of the pixel mode. 	*/
	msp->slowSpeed    =  0;		/* One pixel per pan for all modes.							*/
	msp->fastSpeed    =  3;
	msp->enablePZ = false;		/* Pan & zoom not enabled 									*/
	msp->enableVD = false;		/* Enlarged panning not enabled 							*/
	msp->pip_reserved = 0;
	/*
	* if desktop size is extended and > 1152x870
	* then need to adjust the rowbytes (display_pitch)
	*/
	if((theID6 & 0x008f) > FirstExtended)
		adjust_pitch(base, theID6);
	msp->disp_pitch = dr_get_disp_pitch(base);
	msp->monitor_sRsrcId = theID;
	msp->desk_sRsrcId = theID6;
	msp->sync_state = (unsigned char)POWER_ON;
#if DEBUG
	myDebugStr("\Open call: return");
#endif
	#asm
	MOVEM.L (SP)+,A0-A5/D0-D7   ; Restore nearly all registers
	#endasm
	return(noErr);             /* Successful Open */
}
/*
 * adjust_pitch()
 *
 * handle the extended desktop sizes
 *
 * all non-extended desktop has row byte of 1152
 * rowbytes for extended desktop are:
 * 1152 x 870:	1152
 * 1600 x 1200:	800
 * 2304 x 1740:	576
 * 3200 x 2400:	400
 */
adjust_pitch(base, pram6)
register unsigned long	base;
short	pram6;				/* parameter ram 6 */
{
	unsigned long			pitch;
	char					mmu_mode;
	
#if DEBUG
	myDebugStr("\Padjust_pitch:...");
#endif
	switch(pram6 & 0x008f) {
		case 0x008a:
				pitch = (1152/2) / 4;
				break;
		case 0x008b:
				pitch = (1600/4) / 4;
				break;
		case 0x008c:
				pitch = (2304/8) / 4;
				break;
	}
	mmu_mode = true32b;	
	drSwapMMUMode(&mmu_mode);
	VRAMXFR_OFF(base);
	drSwapMMUMode(&mmu_mode);
	set_rgs(base, (short) display_pitch, (long) pitch, (short) 4);
	mmu_mode = true32b;	
	drSwapMMUMode(&mmu_mode);
	VRAMXFR_ON(base);
	drSwapMMUMode(&mmu_mode);
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of open^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
OSErr prime()
{
}
/****************************************************************************************/
/* This routine is run whenever the driver is told to close. */
/****************************************************************************************/
OSErr close()
{
  mystorage	*msp;		/* pointer to my private storage */
  AuxDCEPtr dcep;        	/* Auxiliary Device Control Entry pointer. */
  CntrlParam *pbp;     		/* Application-passed parameter block pointer. */
  unsigned char mmu_mode;   /* MMU Mode (0=24-bit addressing 1=32-bit addressing) */
  unsigned long base;       /* Slot base address */
  register unsigned short *reg_ptr;
#asm
    MOVEM.L A0-A5/D0-D7,-(sp)   ; Save nearly all registers
#endasm
  save(&dcep,&pbp);      	/* A0 -> pbp, A1 -> dcep */
  base =  ((unsigned long)(dcep->dCtlDevBase) & (unsigned long)0xFF000000);
  /* Dereference locked handle to private storage */  
  msp = (struct mystorage *)*(dcep->dCtlStorage);
  msp = (mystoragePtr) StripAddress(msp);
  
  /* Make dac pointer */
  reg_ptr = ((unsigned short *)(base + (long)(0xF70000 + 2)));
  
  /* Change mode to 32-bit addressing */
  mmu_mode = 1;	/* 32 bit mode */
  drSwapMMUMode(&mmu_mode);
  /* Now make all video invisible by telling it to inhibit  all bits in the DACs. ?????*/
  reg_ptr = ((unsigned short *)(base + (long)(0xFA0000 + 2)));   /* DAC Address Register */
  *reg_ptr = 0;
  reg_ptr = ((unsigned short *)(base + (long)(0xFA0004 + 2)));   /* DAC Data Register */
  *reg_ptr = 0;   /* DAC Data r */
  *reg_ptr = 0;   /* DAC Data g */
  *reg_ptr = 0;   /* DAC Data b */
  reg_ptr = ((unsigned short *)(base + (long)(0xFA0008 + 2)));   /* DAC read mask */
  *reg_ptr = 0;   /* DAC read mask off */
  /* Turn off interrupts */
  ((unsigned long *)(base + RGS14188))[control_4] &= 0xFA;
  /* Change mode back to whatever we were before the last swap */
  drSwapMMUMode(&mmu_mode);
    
  mysintremove(msp->myslotqeleptr,dcep->dCtlSlot);	/* Pull our interrupts out. */    
  DisposPtr(msp->myslotqeleptr);					/* Nuke our slot queue element block. */
/*  DisposPtr(msp->myintrptcode);					/* Nuke our interrupt code block. */
  DisposPtr(msp->mygammaptr);						/* Nuke our gamma table block. */    
  DisposPtr(msp->lutBuffer);						/* Nuke our clut buffer */    
  DisposHandle(dcep->dCtlStorage);						/* Nuke our variable storage block. */
    
#asm
    MOVEM.L (SP)+,A0-A5/D0-D7   ; Restore nearly all registers
#endasm
  return(0);             /* Successful Close */
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of close^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*
         1         2         3         4         5         6         7         8
12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/
/****************************************************************************************/
/* Control calls
/*
/*   (0)  Reset
/*          csMode <- short
/*          csPage <- short
/*          csBaseAddr <- pointer
/*   (1)  Kill I/O
/*   (2)  SetMode
/*          csMode -> short
/*          csPage -> short
/*          csBaseAddr <- pointer
/*   (3)  SetEntries  -  error if direct mode
/*          csTable -> pointer
/*          csStart -> short
/*          csCount -> short
/*   (4)  SetGamma
/*          csTable -> pointer
/*   (5)  GrayScreen
/*          csPage -> pointer
/*   (6)  SetGray
/*          csMode -> short  (0 for color) (1 for gray)
/*   (7)  SetInterrupt
/*          csMode -> short  (0 for disable) (1 for enable)
/*   (8)  DirectSetEntries  -  error if indexed mode
/*          csTable -> pointer
/*          csStart -> short
/*          csCount -> short
/*   (9)  SetDefaultMode
/*          csMode -> char
/*
/*  Pan and zoom specifics
/*    8192 - Zoom In
/*    8193 - Zoom Out
/*    8194 - Pan X
/*    8195 - Pan Y
/*    8196 - Pan To
/*    8197 - SetRects
/*    8198 - SetXY
/*    8199 - SetSlow
/*    8200 - SetFast
/*    8201 - SetBorder
/*    8202 - SetPZ
/*    8203 - SetCenter
/*    8204 - SetVD
/*
/*
/*   Entry:
/*      A0 - Parameter Block Pointer
/*      A1 - DCE Pointer
/*
/*   Exit
/*      D0 - Error Code
/*
/****************************************************************************************/
#define controlErr	-17
#define	QD32Trap	0xAB03
#define	Unimplemented	0xA89F
OSErr control()
{
	AuxDCEPtr				dcep;			/* Auxiliary Device Control Entry pointer. */
	register mystoragePtr	msp;
	register unsigned long	*dacaddr, *dacdata, *modereg;
	CntrlParam				*pbp;			/* Application-passed parameter block pointer. */
	Ptr						paramptr;		/* Local copy of pointer to csParam */
	SlotIntQElement			*sqeptr;		/* Slot queue element pointer */
	THz						oldzone;		/* Previous heap zone */
	OSErr					errorflag;		/* flag for bad control call */
	unsigned char			mmu_mode;		/* MMU Mode (0=24-bit addressing 1=32-bit addressing) */
	unsigned long			*rgs14188_ptr;
	unsigned long			*dac_cmd_reg;
	unsigned short 			mode;
	unsigned long			base;			/* Slot base address */
	unsigned long			i,j;
	GDHandle 				dev;
	OSErr 					error = noErr;
	zoomCtrlParam 			*zp;     		/* Application-passed zoom & pan parameter block pointer. 	*/
	panInfoParam 			*pp;
	short 					defStart;
  
#asm
    MOVEM.L A0-A5/D0-D7,-(sp)   ; Save nearly all registers
#endasm
  save(&dcep,&pbp);      /* A0 -> pbp, A1 -> dcep */
msp = (mystoragePtr)(*(dcep->dCtlStorage));
msp = (mystoragePtr) StripAddress(msp);
zp  = (panCtrlParam *)pbp; 		    /* Set up our pan-status block pointer      */
pp  = (panInfoParam *)pbp;
  errorflag = 0;
    /* Local copy of pointer to csParam */
  paramptr = *((Ptr *)(pbp->csParam));
  
    /* Local copy of base address */
  base =  ((unsigned long)(dcep->dCtlDevBase) & (unsigned long)0xFF000000);
    /* Make pointers to control registers */
  rgs14188_ptr = (unsigned long *)(base + (unsigned long)RGS14188);
  dac_cmd_reg = (unsigned long *)(base + (unsigned long)BT473_COMMAND);
#asm
;	DC.W	$A9FF	; Debugger()
#endasm
#if tmpDEBUG
	switch(pbp->csCode) {
	case 0: myDebugStr("\PInit");
			break;
	case 1: myDebugStr("\PKillIO");
			break;
	case 2: myDebugStr("\PSetMode");
			break;
	case 3: myDebugStr("\PSetEntries");
			break;
	case 4: myDebugStr("\PSetGamma");
			break;
	case 5: myDebugStr("\PGrayScreen");
			break;
	case 6: myDebugStr("\PSetGray");
			break;
	case 7: myDebugStr("\PSetInterrupt");
			break;
	case 8: myDebugStr("\PDirectSetEntries");
			break;
	case 9: myDebugStr("\PSetDefault");
			break;
	case 10: myDebugStr("\PSwitchMode");
			break;
	case 11: myDebugStr("\PSetSync");
			break;
	case 8192: myDebugStr("\PZoomIn");
			break;
	case 8196: myDebugStr("\PPanTo");
			break;
	case 8202: myDebugStr("\PSetPZ");
			break;
	case -1: myDebugStr("\PClose");
			break;
	}
#endif
/* Switch on the type of the type of action we are to respond to or do. */
  switch(pbp->csCode)
  {
    case 0:         /* Reset the video card. (Init) */
        /* Set return values */
      ((VDPgInfoPtr)paramptr)->csMode = 0x80;         /* Return that we're in 1-Bit mode. */
      ((VDPgInfoPtr)paramptr)->csPage = 0;
      ((VDPgInfoPtr)paramptr)->csBaseAddr = (Ptr)(dcep->dCtlDevBase);
        /* Set our private values for mode and base address */
      msp->mode = 0x80;
      msp->newmode = 0x80;
	  msp->theMode = msp->mode & 0x0F;
      msp->screenbase = (dcep->dCtlDevBase);;
      /* Fix for A\UX */
      dacaddr = ((unsigned long *)(base + (long)0xFA0000));
      dacdata = ((unsigned long *)(base + (long)0xFA0004));
	  waitvblank(base);		/* Wait for vertical blanking time. */
	  mmu_mode = 1;
      drSwapMMUMode(&mmu_mode);
      *dacaddr = 0;
      for(i=0;i<256;i++)
        {
          *dacdata = 0xB0;
          *dacdata = 0xB0;
          *dacdata = 0xB0;
        }
      *dacaddr = 0;
      *dacdata = 0xFF;
      *dacdata = 0xFF;
      *dacdata = 0xFF;
      *dacaddr = 0x80;
      *dacdata = 0;
      *dacdata = 0;
      *dacdata = 0;
		/* Set 1 bit mode */
      rgs14188_ptr[gio_reg_Hi] = 0x30;
      drSwapMMUMode(&mmu_mode);
      grayscrn(base,0x80, msp);
      break;
    case 1:         /* Remove all pending I/O. (KillIO) */
      break;
    case 2:         /* Set the card's video mode. (SetMode) if set already do nothing */
/****
myDebugStr("\PSetMode");
****/
        /* Check for valid mode ???? 84 not valid if no JP present */
      if(((VDPgInfoPtr)paramptr)->csMode < 0x80 || ((VDPgInfoPtr)paramptr)->csMode > 0x85)
      {
        errorflag = controlErr;    /* Return that we couldn't do it. */
		break;
      }
        /* Check for 32-bit Quickdraw */
      if((((VDPgInfoPtr)paramptr)->csMode >= 0x84) && (NGetTrapAddress(QD32Trap, ToolTrap) == GetTrapAddress(Unimplemented)))
      {
        errorflag = controlErr;    /* Return that we couldn't do it. */
		break;
      }
        /* If set already do nothing */
      if(((VDPgInfoPtr)paramptr)->csMode == msp->mode)
		break;
#if MAKING24MXTV
 	  /* if going from 24bit or 16bit to 8bit or less, turn off pip */
 	  CheckPip(base, msp->mode, ((VDPgInfoPtr)paramptr)->csMode);
#endif
        /* Set private storage */
      msp->mode = ((VDPgInfoPtr)paramptr)->csMode;
      msp->theMode = msp->mode & 0x0F;
        /* Get Mode while in 24 bit addressing mode */
      mode = (((VDPgInfoPtr)paramptr)->csMode);
 
        /* Set Hardware */		
      waitvblank(base);		/* Wait for vertical blanking time. */
      graytable(base);		/* Set dacs to all gray to avoid flashes when changing bit depths */
        /* Set Hardware */		
      waitvblank(base);		/* Wait for vertical blanking time. */
	  
#asm
	MOVE	SR,-(SP)		; Save state
	MOVE.W	#$2200,SR		; Disable interrupts
#endasm    
        /* Set mode registers */
      mmu_mode = 1;	/* 32 bit mode */
      drSwapMMUMode(&mmu_mode);
      rgs14188_ptr[gio_reg_Lo] &= 0xBF;	/* BAC reset on */
      rgs14188_ptr[gio_reg_Hi] &= (long)0xF0;  /* force 1-8 bit modes (bit 4,5 = 0) and Reset (bit 7 lo) */
      switch(mode & 0x7)
      {
        case 0:
		  rgs14188_ptr[gio_reg_Hi] |= 0x00;  /* set 1 bit mode */
		  *dac_cmd_reg |= 0x01;	/* Command Register for other than PAL (7.5 IRE) */
 	      break;
        case 1:
		  rgs14188_ptr[gio_reg_Hi] |= 0x04;  /* set 2 bit mode */
		  *dac_cmd_reg |= 0x01;	/* Command Register for other than PAL (7.5 IRE) */
	      break;
        case 2:
		  rgs14188_ptr[gio_reg_Hi] |= 0x08;  /* set 4 bit mode */
		  *dac_cmd_reg |= 0x01;	/* Command Register for other than PAL (7.5 IRE) */
	      break;
        case 3:
		  rgs14188_ptr[gio_reg_Hi] |= 0x0C;  /* set 8 bit mode */
		  *dac_cmd_reg |= 0x01;	/* Command Register for other than PAL (7.5 IRE) */
		  break;
        case 4:
		  rgs14188_ptr[gio_reg_Hi] |= 0x0D;  /* set 24 bit mode */
		  *dac_cmd_reg &= ~0x01;	/* Command Register for other than PAL (7.5 IRE) */
	      break;
        case 5:
		  rgs14188_ptr[gio_reg_Hi] |= 0x0E;  /* set 24 bit mode */
		  *dac_cmd_reg &= ~0x01;	/* Command Register for other than PAL (7.5 IRE) */
	      break;
      }
      rgs14188_ptr[gio_reg_Lo] |= 0x40;	/* BAC reset off */
      drSwapMMUMode(&mmu_mode);
#asm
	MOVE	(SP)+,SR		; Restore interrupts
#endasm
	/* Return the base address */
      ((VDPgInfoPtr)paramptr)->csBaseAddr = (Ptr)(dcep->dCtlDevBase);
	  ((VDPgInfoPtr)paramptr)->csPage     = 1;	/* All we allow */
      break;
    case 3:         /* Change card's color lookup table(s). (SetEntries) */
/* myDebugStr("\PSetEntries"); */
      if (msp->mode >= 0x84) errorflag = controlErr; /* Must use (DirectSetEntries) for millions of colors! */
      else errorflag = setlut(((VDSetEntryPtr)paramptr)->csTable,((VDSetEntryPtr)paramptr)->csStart,
                           ((VDSetEntryPtr)paramptr)->csCount,dcep);
      break;
    case 4:         /* Change card's gamma table. (SetGamma) */
/* myDebugStr("\PSetGamma"); */
      errorflag = setgamma(((VDGamRecPtr)paramptr)->csGTablePtr,msp,dcep);
        /* Set ramp lut only if direct mode, no gamma error, and not switching modes */
		/* If switching modes, a lut load now would flash and grayPage is sure to be called */
      if((msp->mode >= 0x84) && !errorflag && !(msp->newmode))
        errorflag = setdirect(dcep);
      break;
    case 5:         /* Gray the video page with dithered gray. (GrayScreen) ???? use private storage mode and passed page ptr */
/* myDebugStr("\PGrayScreen"); */
      grayscrn(base, msp->mode, msp);
      msp->newmode = 0;	/* tell setgamma that direct ramps have been loaded */
        /* If 24 bit mode, set gamma corrected linear ramp in DACs */
      if(msp->mode >= 0x84)	/* Set direct DAC load for 24 bit screen mode */
      {
	setdirect(dcep); /* needs 1024 bytes stackspace */
      }
      break;
    case 6:         /* Map color lookup table(s) to color or grayscale. (SetGray) */
/* myDebugStr("\PSetGray"); */
      msp->bwmapping = ((VDPgInfoPtr)paramptr)->csMode & 0x0100;
      break;
    case 7:         /* Enable/Disable Interrupts.  (SetInterrupt) */
        /* Do nothing if request matches current state. */
		if(((VDPgInfoPtr)paramptr)->csMode != msp->intflag)
		{
			/* a change is requested */
			if(((VDPgInfoPtr)paramptr)->csMode)
			{
				/* Set interrupts on */
				/* Turn on interrupts 47/43 for ntsc & pal */
				mmu_mode = 1;	/* 32 bit addressing mode */
				drSwapMMUMode(&mmu_mode);
				
				/* Turn on interrupts */
				((unsigned long *)(base + RGS14188))[control_4] |= 5;
				
				drSwapMMUMode(&mmu_mode);
				
				/* Set flag to show interrupts enabled */
				msp->intflag = 1;
			}
			else
			{
				/* Set interrupts off */
				/* Turn our interrupts off. */
				mmu_mode = 1;	/* 32 bit mode */
				drSwapMMUMode(&mmu_mode);
				
				/* Turn off interrupts */
				((unsigned long *)(base + RGS14188))[control_4] &= 0xFA;
				
				drSwapMMUMode(&mmu_mode);
				
				/* Set flag to show interrupts disabled */
				msp->intflag = 0;
			}
		}
		break;
    case 8:         /* Change card's color lookup table(s). (DirectSetEntries) */
		if(msp->mode < 0x84 || msp->mode > 0x85)	/* For indexed screen mode, DirectSetEntries DAC load not allowed. Use SetEntries. */
		{
			errorflag = controlErr;          /* No room, return that we couldn't do it. */
			break;
		}
		errorflag = setlut(((VDSetEntryPtr)paramptr)->csTable,((VDSetEntryPtr)paramptr)->csStart,
			((VDSetEntryPtr)paramptr)->csCount,dcep);
		break;
    case 9:         /* Set default mode (SetDefault)*/
/*		myDebugStr("\PSetDefault"); */
		defStart = ((VDDefaultInfoPtr)paramptr)->csMode;
		defStart &= 0x008F;
		if ((defStart < FirstResource) || (defStart > LastResource))
			defStart = FirstResource;
		drSetPRAM6(msp->slot, ((VDDefaultInfoPtr)paramptr)->csMode);
		
		if(defStart <= LastMonitor)
			drSetPRAM5(msp->slot, ((VDDefaultInfoPtr)paramptr)->csMode);
			
		{
			short	pram5,pram6;
			pram5 = drGetPRAM5(msp->slot) & 0x008f;
			pram6 = drGetPRAM6(msp->slot) & 0x008f;
			drSetEEPROM56(msp->slot, pram5, pram6);
		}
		break;
      
	case 10:         /* Switch Resolution and Bit Depth.  (SwitchMode) */
/*		myDebugStr("\PSwitchMode"); */
		if(((0x008F & ((VDSwitchInfoPtr)paramptr)->csData) < FirstResource) ||
		   ((0x008F & ((VDSwitchInfoPtr)paramptr)->csData) > LastResource))
		{
			errorflag = controlErr;	/* Return that we couldn't do it. */
		}
		else if(((0x00FF & ((VDSwitchInfoPtr)paramptr)->csMode) < 0x80) ||
				((0x00FF & ((VDSwitchInfoPtr)paramptr)->csMode) > 0x85))
		{
			errorflag = controlErr;	/* Return that we couldn't do it. */
		}
		else
		{
			SpBlock	spdata;
			OSErr	iErr;
			
			/* Get new sResource and bit depth ids & Update AuxDCE */
			dcep->dCtlSlotId = 0x00FF & ((VDSwitchInfoPtr)paramptr)->csData;
			msp->mode = 0x00FF & ((VDSwitchInfoPtr)paramptr)->csMode;
			#asm
				MOVE	SR,-(SP)		; Save state
				MOVE.W	#$2200,SR		; Disable interrupts
			#endasm    
			/* Disable old sResource */
			spdata.spSlot = msp->slot;
			spdata.spID = msp->desk_sRsrcId;	/* old ID */
			spdata.spExtDev = 0;
			spdata.spReserved = 0;
			spdata.spIOReserved = 0;
			spdata.spRefNum = 0;
/*				iErr = SRsrcInfo(&spdata);	/* get RefNum */
/*				spdata.spParamData = 1;		/* disable */
			spdata.spStackPtr = 1;		/* disable (old field name for spParamData) */
			iErr = drSetSRsrcState(&spdata);
			iErr = drSUpdateSRT(&spdata);
			msp->desk_sRsrcId = 0x00FF & dcep->dCtlSlotId;
			/* Enable new sResource */
			spdata.spSlot = msp->slot;
			spdata.spID = msp->desk_sRsrcId;	/* new ID */
			spdata.spExtDev = 0;
/*				spdata.spParamData = 0;		/* enable */
			spdata.spStackPtr = 0;		/* enable (old field name for spParamData) */
			spdata.spReserved = 0;
			spdata.spIOReserved = 0;
			spdata.spRefNum = 0;
			iErr = drSetSRsrcState(&spdata);
			iErr = drSUpdateSRT(&spdata);
			/* Return Base address of Page 0 */
			((VDSwitchInfoPtr)paramptr)->csBaseAddr = (Ptr)(msp->screenbase);
			/* Switch the hardware */
			dr_switch_mode(msp);
			/* Initialize the pan and zoom globals */
			msp->theMode = msp->mode & 0x0F;
			drGetWH(msp->monitor_sRsrcId, &msp->xResolution, &msp->yResolution);
			msp->screensize = msp->xResolution;
			drGetWH(msp->desk_sRsrcId, &msp->xSize, &msp->ySize);
			msp->zoom         = x1;		/* Zoom x1 													*/
			msp->currentRate  =  0;		/* No panning until zoomed or Virtual DeskTop is enabled 	*/
			msp->currentZoom  =  1;		/* No zooming until chosen by a key 						*/
			msp->currentX 	  =  0;		/* 0,0 														*/
			msp->currentY 	  =  0;
	
			#asm
				MOVE	(SP)+,SR		; Restore interrupts
			#endasm
		}
		break;
	case 11:         /* Enable/Disable Syncs.  (SetSync) */
/*		myDebugStr("\PSetSync"); */
		if(*((VDFlagPtr)paramptr) == POWER_ON)	/* Set energy save state (Power On); H and V syncs enabled */
		{
			/* Set sync hardware */
			set_energy_save_state_rgs14188((unsigned char)POWER_ON, msp);
			msp->sync_state = (unsigned char)POWER_ON;
		}
		else if(*((VDFlagPtr)paramptr) == POWER_OFF)	/* Set energy save state (Power Off); H and V sync disabled */
		{
			/* Set sync hardware */
			set_energy_save_state_rgs14188((unsigned char)POWER_OFF, msp);
			msp->sync_state = (unsigned char)POWER_OFF;
		}
		else	/* Set energy save state (Standby); H or V sync disabled */
		{
			/* Set sync hardware */
			set_energy_save_state_rgs14188((unsigned char)POWER_STANDBY, msp);
			msp->sync_state = (unsigned char)POWER_STANDBY;
		}
		break;
    case 8192:	   /* Zoom in */
      	if (msp->enablePZ) ZoomIn(msp);
		break;      
    case 8193:	   /* Zoom Out */
		if (msp->enablePZ) ZoomOut(msp);
		break;
		
    case 8194:	   /* Pan X according to the paramblock sent:
       		          The paramBlock specifies:
    		              short zp->csParam[0] = direction
		                  short zp->csParam[1] = speed			*/
		zp = (zoomCtrlParam *)pbp;
		/* PanX(zp->csParam[0],zp->csParam[1], msp); */
		break;
		
    case 8195:	   /* Pan Y according to the paramblock sent:
    		          The paramBlock specifies:
    		              short zp->csParam[0] = direction
		         		  short zp->csParam[1] = speed			*/
		zp = (zoomCtrlParam *)pbp;
      	PanY(zp->csParam[0], zp->csParam[1], msp);
		break;
      
    case 8196:	   /* Pan To 
    		      The paramBlock specifies:
    		          short zp->csParam[0] = x
		          	  short zp->csParam[1] = y			*/
			zp = (zoomCtrlParam *)pbp;
      		PanTo(zp->csParam[0], zp->csParam[1], msp);
		break;
		
    case 8197:	   /* SetRects */ 
		dev = GetDeviceList();
		do
  		  {
    		if (msp->refNum == (*dev)->gdRefNum) 
       		  {
         		msp->theRect = (*dev)->gdRect;
         		break;
       		  }
  		  }
		while(dev = (GDHandle)(*dev)->gdNextGD);
		calcRects(msp);		/* Calculate our panning region.		*/
		break;
    case 8198:	    /* SetXY */
    	msp->currentX = zp->csParam[0];
		msp->currentY = zp->csParam[1];
		break;
    case 8199:	    /* SetSlow */
    	msp->slowSpeed = zp->csParam[0];
		break;
    case 8200:	    /* SetFast */
    	msp->fastSpeed = zp->csParam[0];
		break;
    case 8201:	    /* SetBorder */
    	msp->border = zp->csParam[0];
		break;
    case 8202:	    /* SetPZ */
    	msp->enablePZ = (zp->csParam[0]) ? true : false;
		break;
    case 8203:	    /* SetCenter */
    	msp->zCenter = (zp->csParam[0]) ? true : false;
		break;
    case 8204:	    /* SetVD */
    	msp->enableVD = (zp->csParam[0]) ? true : false;
		if (msp->enableVD)
		  {
		    msp->currentRate = 1; /* not used in 24Mx */
		  }
		break;
      case -1:  /* Goodbye condition.  Done when the "GoodBye Kiss" is given. */
			close();      /* Clean up things before leaving. */
      break;
      default:  /* Illegal csCode. */
			errorflag = controlErr;                   /* Return that we couldn't do it. */
      break;
  }
#asm
    MOVEM.L (SP)+,A0-A5/D0-D7   ; Restore nearly all registers
#endasm
  checkiodone(errorflag);
  return(errorflag);
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of control^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/****************************************************************************************/
/* Status calls
/*
/*   (0)  Error
/*   (1)  Error
/*   (2)  GetMode
/*          csMode <- short
/*          csPage <- short
/*          csBaseAddr <- pointer
/*   (3)  GetEntries  -  valid for indexed and direct
/*          csTable <-> pointer
/*          csStart -> short
/*          csCount -> short
/*   (4)  GetPages
/*          csMode -> short
/*          csPage <- short  (number of pages)
/*   (5)  GetBaseAddr
/*          csPage -> short
/*          csBaseAddr <- pointer
/*   (6)  GetGray
/*          csMode <- short  (0 for color) (1 for gray)
/*   (7)  GetInterrupt
/*          csMode >- short  (0 for disabled) (1 for enabled)
/*   (8)  GetGamma
/*          csTable <- pointer
/*   (9)  GetDefaultMode
/*          csMode -> char
/*
/*  Pan and Zoom specifics
/*    8192		GetPanRate()	get the scaling factor for the x/y panning rate.
/*    8193		GetSlow()	get the slow panning speed.
/*    8194		GetFast()	get the fast panning speed.
/*    8195		GetMargin()	get the width (in pixels) of the slow panning area.
/*    8196		GetZoom()	get the current zoom state (1 = x1, 2 = x2, 3 = x4.)
/*    8197		GetRects()	get the fast and slow panning rectangles.
/*    8198		GetXY()		get the currentX and currentY screen coordinates.
/*    8199		GetAll()	get all the various pan and zoom variables
/*    8200		GetPZMode()	get the pixel mode
/*    8201		GetPZ()		get the pan and zoom enable flag
/*
/*
/*   Entry:
/*      A0 - Parameter Block Pointer
/*      A1 - DCE Pointer
/*
/*   Exit
/*      D0 - Error Code
/*
/****************************************************************************************/
#define statusErr	-18
OSErr status()
{
  AuxDCEPtr				dcep;		/* Auxiliary Device Control Entry pointer. */
  register mystoragePtr	msp;
  CntrlParam			*pbp;		/* Application-passed parameter block pointer. */
  Ptr					paramptr;	/* Local copy of pointer to csParam */
  OSErr 				error = noErr;
  unsigned long			base;		/* Slot base address */
  panCtrlParam 			*zp;	 /* Application-passed pan-status parameter block pointer. 	*/
  panInfoParam 			*pp;	 /* Application-passed pan-info parameter block pointer. 	*/	
  GDHandle 				dev;
  short 				defStart;	/* Default startup configuration */  
  
#asm
    MOVEM.L A0-A5/D0-D7,-(sp)   ; Save nearly all registers
#endasm
  save(&dcep,&pbp);      /* A0 -> pbp, A1 -> dcep */
msp = (mystoragePtr)(*(dcep->dCtlStorage)); /* Set up our pointer to the globals 	*/
msp = (mystoragePtr) StripAddress(msp);
zp  = (panCtrlParam *)pbp; 		    /* Set up our pan-status block pointer      */
pp  = (panInfoParam *)pbp;
    /* Local copy of pointer to csParam */
  paramptr = *((Ptr *)(pbp->csParam));
  
    /* Local copy of base address */
  base =  ((unsigned long)(dcep->dCtlDevBase) & (unsigned long)0xFF000000);
#if tmpDEBUG
	switch(pbp->csCode) {
	case 2: myDebugStr("\PGetMode");
			break;
	case 3: myDebugStr("\PGetEntries");
			break;
	case 4: myDebugStr("\PGetPages");
			break;
	case 5: myDebugStr("\PGetBaseAddr");
			break;
	case 6: myDebugStr("\PGetGray");
			break;
	case 7: myDebugStr("\PGet Interrupt");
			break;
	case 9: myDebugStr("\PGetdefault");
			break;
	case 10: myDebugStr("\PGetCurrMode");
			break;
	case 11: myDebugStr("\PGetSync");
			break;
	case 12: myDebugStr("\PGetConnection");
			break;
	case 13: myDebugStr("\PGetModeTiming");
			break;
	case 8196: myDebugStr("\PGetZoom");
			break;
	case 8199: myDebugStr("\PGetAll");
			break;
	}
#endif
     /* Switch on the type of the type of action we are to repond to or do. */
  switch(pbp->csCode)
  {
    case 2:   /* Get the card's video mode. (GetMode) */
      ((VDPgInfoPtr)paramptr)->csMode = msp->mode;
      ((VDPgInfoPtr)paramptr)->csPage = 0;
      ((VDPgInfoPtr)paramptr)->csBaseAddr = (Ptr)(dcep->dCtlDevBase);
      break;
    case 3:   /* Get values from card's color lookup table(s). (GetEntries) */
      getlut(((VDSetEntryPtr)paramptr)->csTable,((VDSetEntryPtr)paramptr)->csStart,
             ((VDSetEntryPtr)paramptr)->csCount,dcep);
      break;
    case 4:   /* Get the total number of video pages on the card. (GetPages) */
      ((VDPgInfoPtr)paramptr)->csPage = 1;
      break;
    case 5:   /* Get base address of specified page in current mode. (GetBaseAddr) */
      ((VDPgInfoPtr)paramptr)->csBaseAddr = (Ptr)(dcep->dCtlDevBase);
      break;
    case 6:   /* Get mapping mode (color or grayscale) of color lookup table(s). (GetGray) */
      ((VDPgInfoPtr)paramptr)->csMode = msp->bwmapping;
      break;
    case 7:   /* Get Interrupt enable state ???? */
      ((VDPgInfoPtr)paramptr)->csMode = msp->intflag;
      break;
    case 8:   /* Get pointer to current gamma table */
      ((VDGamRecPtr)paramptr)->csGTablePtr = msp->mygammaptr;
      break;
    case 9:   /* GetDefaultMode */
/*		myDebugStr("\PGetDefaultMode");*/
		defStart = drGetPRAM6(msp->slot); /* Get the default startup mode */
		((VDDefaultInfoPtr)paramptr)->csMode = defStart;	/* Return the default */
		break;
		
	case 10:         /* Get Current Resolution and Bit Depth.  (GetCurrMode) */
/*			DBS_STATUS("\PGetCurrMode"); */
		((VDSwitchInfoPtr)paramptr)->csMode = (unsigned short)msp->mode;
		((VDSwitchInfoPtr)paramptr)->csData = (unsigned long)msp->desk_sRsrcId;
		((VDSwitchInfoPtr)paramptr)->csPage = (unsigned short)0;
		((VDSwitchInfoPtr)paramptr)->csBaseAddr = (Ptr)(msp->screenbase);
/*			((VDSwitchInfoPtr)paramptr)->csReserved = (unsigned long)0; */
		break;
		
	case 11:         /* (GetSync) */
/*			DBS_STATUS("\PGetSync"); */
		*((VDFlagPtr)paramptr) = msp->sync_state;
		break;
	case 12:         /* Get Connection info.  (GetConnection) */
/*			DBS_STATUS("\PGetConnection"); */
		((VDDisplayConnectInfoPtr)paramptr)->csDisplayType = (unsigned short)kUnknownConnect;	/*kFixedModeCRTConnect;	//kUnknownConnect;	//kMultiModeCRT2Connect; */
/*			((VDDisplayConnectInfoPtr)paramptr)->csConnectTagged = (unsigned short)0; */
		((VDDisplayConnectInfoPtr)paramptr)->csConnectFlags = (1<<kUncertainConnect); /* (unsigned long)(1<<kAllModesValid); /*+(1<<kAllModesSafe)+(1<<kUncertainConnect);*/
/*			((VDDisplayConnectInfoPtr)paramptr)->csDisplayComponent = (unsigned long)0; */
/*			((VDDisplayConnectInfoPtr)paramptr)->csConnectReserved = (unsigned long)0; */
		break;
	case 13:         /* Get Mode Timing info.  (GetModeTiming) */
/*			DBS_STATUS("\PGetModeTiming"); */
#if 0
		error = statusErr;
		break;
#else
		{
			register unsigned long	resid;
			register unsigned long	flags;
			unsigned long			timing;
			
			resid = ((VDTimingInfoPtr)paramptr)->csTimingMode & 0x008F;
			if(resid < FirstResource || resid > LastResource)
			{
				error = statusErr;
				break;
			}
			switch((short)resid)
			{
#if 0
				case RES_ID_11x8:
					timing = timingApple21;	/* 1152x870 */
					break;
				case RES_ID_10x7_75:
					timing = timingApple19;	/* 1024x768 75hz */
					break;
				case RES_ID_10x7_60:
					timing = timingApple1ka;	/* 1024x768 75hz */
					break;
#endif
				case RES_ID_8x6:
					timing = timingApple16;	/* 832x624 */
					break;
				case RES_ID_6x4:
					timing = timingApple13;	/* 640x480 */
					break;
				case RES_ID_6x8:
					timing = timingApple15;	/* 640x870 */
					break;
				case RES_ID_6x4ntsc:
					timing = timingAppleNTSC_FF;	/* 640x480 NTSC */
					break;
				case RES_ID_7x5pal:
					timing = timingApplePAL_FF;	/* 768x576 PAL */
					break;
				case RES_ID_5x4ntsc:
					timing = timingAppleNTSC_ST;	/* 576 X 432 NTSC underscan? 512x384 ST */
					break;
				case RES_ID_6x5pal:
					timing = timingApplePAL_ST;	/* 684 X 512 PAL underscan? 640x480 ST */
					break;
				case RES_ID_1152x870ext:
					timing = timingApple21;		/* 1152 X 870 ext */
					break;
				case RES_ID_1600x1200ext:
					timing = timingUnknown;		/* 1600 x 1200 ext */
					break;
				case RES_ID_2304x1740ext:
					timing = timingUnknown;		/* 2304 x 1740 ext */
					break;
#if 0
				case RES_ID_3200x2400ext:
					timing = timingUnknown;		/* 3200 x 2400 ext */
					break;
#endif
			}
/*			((VDTimingInfoPtr)paramptr)->csTimingReserved = ((unsigned long)0; */
			((VDTimingInfoPtr)paramptr)->csTimingFormat = (unsigned long)kDeclROMtables;
			((VDTimingInfoPtr)paramptr)->csTimingData = timing;
/* myDebugStr("\PGetModeTiming"); */
			/* first assume all modes are valid */
			flags = (1<<kModeValid);
			if(resid == (msp->monitor_sRsrcId & 0x008F))
			{
				flags |= (1<<kModeSafe);
			}
			else if(resid >= FirstExtended)
			{
/*
				if((resid == FirstExtended) && ((msp->monitor_sRsrcId & 0x008F) == FirstMonitor))
					flags = 0;
				else
*/
					flags |= (1<<kModeSafe);
			}
			((VDTimingInfoPtr)paramptr)->csTimingFlags = flags;
		}
		break;
#endif
    /* Pan and Zoom status calls */
    case 8192:  /* GetPanRate() */
      		zp->csParam[0] = msp->currentRate;
    		break;
		
    case 8193:  /* GetSlow() */
      		zp->csParam[0] = msp->slowSpeed;
    		break;
		
    case 8194:  /* GetFast() */
      		zp->csParam[0] = msp->fastSpeed;
    		break;
		
    case 8195:  /* GetMargin() */
      		zp->csParam[0] = msp->border;
    		break;
		
    case 8196:  /* GetZoom() */
      		zp->csParam[0] = msp->currentZoom;
    		break;
		
    case 8197:  /* GetRects() */
			dev = GetDeviceList();
			do
  		  	  {
    			if (msp->refNum == (*dev)->gdRefNum) 
       		  	  {
         			msp->theRect = (*dev)->gdRect;
         			break;
       		  	  }
  		  	  }
			while(dev = (GDHandle)(*dev)->gdNextGD);
			calcRects(msp);		/* Calculate our panning region.		*/
			pp->fastRect = msp->theRect;
			pp->slowRect = msp->panRect; 
    		break;
    case 8198:  /* GetXY() */
      		zp->csParam[0] = msp->currentX;
      		zp->csParam[1] = msp->currentY;
			break;
    case 8199:  /* GetAll() */
			dev = GetDeviceList();
			do
  		  	  {
    		    if (msp->refNum == (*dev)->gdRefNum) 
       		      {
         			msp->theRect = (*dev)->gdRect;
         			break;
       		      }
  		  	  }
			while(dev = (GDHandle)(*dev)->gdNextGD);
			calcRects(msp);		/* Calculate our panning region.		*/
      		zp->csParam[ 0] = msp->currentZoom;
      		zp->csParam[ 1] = msp->currentX;
      		zp->csParam[ 2] = msp->currentY;
      		zp->csParam[ 3] = msp->theMode;
      		zp->csParam[ 4] = msp->border;
      		zp->csParam[ 5] = msp->fastSpeed;
      		zp->csParam[ 6] = msp->slowSpeed;
      		zp->csParam[ 7] = msp->slot;
      		zp->csParam[ 8] = msp->panRect.top;
      		zp->csParam[ 9] = msp->panRect.left;
      		zp->csParam[10] = msp->panRect.bottom;
      		zp->csParam[11] = msp->panRect.right;
      		zp->csParam[12] = msp->theRect.top;
      		zp->csParam[13] = msp->theRect.left;
      		zp->csParam[14] = msp->theRect.bottom;
      		zp->csParam[15] = msp->theRect.right;
      		zp->csParam[16] = msp->xSize;
      		zp->csParam[17] = msp->ySize;
      		zp->csParam[18] = msp->currentRate;
			zp->csParam[19] = msp->enableVD;
			zp->csParam[20] = msp->xResolution;
			zp->csParam[21] = msp->yResolution;
			break;
    case 8200:  /* GetPZMode() */
			zp->csParam[0] = msp->theMode;
			break;
		
    case 8201:  /* GetPZ() */
    		zp->csParam[0] = (msp->enablePZ) ? 1 : 0;
			break;
		
    case 8202:  /* GetCenter() */
    		zp->csParam[0] = (msp->zCenter) ? 1 : 0;
			break;
    default: error = statusErr;
  }
#asm
    MOVEM.L (SP)+,A0-A5/D0-D7   ; Restore nearly all registers
#endasm
  checkiodone(error);
  return(error);
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of status^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#if MAKING24MXTV
#define PIP_CNTL0	0x00D000C3
void CheckPip(base, oldmode, newmode)
unsigned long	base;
unsigned short	oldmode;
unsigned short	newmode;
{
	short	n;
	
	/*
	 * 1. if not going from 16bit or 24 bit to 8bit or less, return
	 * 2. if pip already off, return
	 * 3. turn pip off, wait till off, 
	 * 4. if not off in 1/25 second, return anyway
	 */
	oldmode &= 0x000f;
	newmode &= 0x000f;
	 
	if(!((oldmode >= 4) && (newmode <= 3)))
	 	return;
	
	if(PipIsOff(base))
		return;
		
	TurnPipOff(base);
	n = 40;
	while(n--) {
		if(PipIsOff(base))
			return;
		drwait1ms();
	}
}
Boolean PipIsOff(base)
unsigned long	base;
{
	char	mmu_mode;
	char	v;
	
	mmu_mode = 1;
	drSwapMMUMode(&mmu_mode);
	v = *((char *) (base | PIP_CNTL0));
	drSwapMMUMode(&mmu_mode);
	if(v & 0x60)
		return false;
	else
		return true;
}
void TurnPipOff(base)
unsigned long	base;
{
	char	mmu_mode;
	char	v;
	
	mmu_mode = 1;
	drSwapMMUMode(&mmu_mode);
	v = *((char *) (base | PIP_CNTL0));
	*((char *) (base | PIP_CNTL0)) = v & 0x9f;
	drSwapMMUMode(&mmu_mode);
}
#endif
#if NEVER
/*
 * drBlackMem()
 */
drBlackMem(base, bitdepth)
unsigned long	base;
short			bitdepth;
{
	register short			i,j;
	register long			value;
	register unsigned long	*to;
	char					mmu_mode;
	if(bitdepth <= 8)		/* for bit depth <= 8, 0xff is black */
		value = 0xffffffff;
	else					/* for bit depth > 8, 0x00 is black */
		value = 0;
		
	/*
	 * blank the screen
	 */
	mmu_mode = 1;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
    
	to = (unsigned long *) (base);
	i = 1024;
	while(i--) {
		if(bitdepth <= 8)
			j = 1024/4;
		else
			j = 1024;
		while(j--) {
			*to++ = value;
		}
	}
	drSwapMMUMode(&mmu_mode);
}
#endif
/*
 * drGetWH()
 */
drGetWH(resNum, width, height)
register short	resNum;
register short	*width;
register short	*height;
{
	
	/*
	 * determine the width and height
	 */
	switch(resNum & 0x000f) {
		case 0x00:
				*width = 1152;
				*height = 870;
				break;
		case 0x01:
		case 0x02:
				*width = 1024;
				*height = 768;
				break;
		case 0x03:
				*width = 832;
				*height = 624;
				break;
		case 0x04:
		case 0x06:
				*width = 640;
				*height = 480;
				break;
		case 0x05:
				*width = 640;
				*height = 870;
				break;
		case 0x07:
				*width = 768;
				*height = 576;
				break;
		case 0x08:
				*width = 576;
				*height = 432;
				break;
		case 0x09:
				*width = 684;
				*height = 512;
				break;
		case 0x0a:
				*width = 1152;
				*height = 870;
				break;
		case 0x0b:
				*width = 1600;
				*height = 1200;
				break;
		case 0x0c:
				*width = 2304;
				*height = 1740;
				break;
		case 0x0d:
				*width = 3200;
				*height = 2400;
				break;
	}
}
 
#asm
_LinearTable even
    DC.B	$00,$01,$02,$03,$04,$05,$06,$07,$08,$09,$0A,$0B,$0C,$0D,$0E,$0F
    DC.B	$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$1A,$1B,$1C,$1D,$1E,$1F
    DC.B	$20,$21,$22,$23,$24,$25,$26,$27,$28,$29,$2A,$2B,$2C,$2D,$2E,$2F
    DC.B	$30,$31,$32,$33,$34,$35,$36,$37,$38,$39,$3A,$3B,$3C,$3D,$3E,$3F
    DC.B	$40,$41,$42,$43,$44,$45,$46,$47,$48,$49,$4A,$4B,$4C,$4D,$4E,$4F
    DC.B	$50,$51,$52,$53,$54,$55,$56,$57,$58,$59,$5A,$5B,$5C,$5D,$5E,$5F
    DC.B	$60,$61,$62,$63,$64,$65,$66,$67,$68,$69,$6A,$6B,$6C,$6D,$6E,$6F
    DC.B	$70,$71,$72,$73,$74,$75,$76,$77,$78,$79,$7A,$7B,$7C,$7D,$7E,$7F
    DC.B	$80,$81,$82,$83,$84,$85,$86,$87,$88,$89,$8A,$8B,$8C,$8D,$8E,$8F
    DC.B	$90,$91,$92,$93,$94,$95,$96,$97,$98,$99,$9A,$9B,$9C,$9D,$9E,$9F
    DC.B	$A0,$A1,$A2,$A3,$A4,$A5,$A6,$A7,$A8,$A9,$AA,$AB,$AC,$AD,$AE,$AF
    DC.B	$B0,$B1,$B2,$B3,$B4,$B5,$B6,$B7,$B8,$B9,$BA,$BB,$BC,$BD,$BE,$BF
    DC.B	$C0,$C1,$C2,$C3,$C4,$C5,$C6,$C7,$C8,$C9,$CA,$CB,$CC,$CD,$CE,$CF
    DC.B	$D0,$D1,$D2,$D3,$D4,$D5,$D6,$D7,$D8,$D9,$DA,$DB,$DC,$DD,$DE,$DF
    DC.B	$E0,$E1,$E2,$E3,$E4,$E5,$E6,$E7,$E8,$E9,$EA,$EB,$EC,$ED,$EE,$EF
    DC.B	$F0,$F1,$F2,$F3,$F4,$F5,$F6,$F7,$F8,$F9,$FA,$FB,$FC,$FD,$FE,$FF
#endasm
OSErr setgamma(thetable,msp,dcep)
GammaTablePtr thetable;
mystoragePtr msp;
AuxDCEPtr dcep;
{
  register GammaTablePtr gammaptr;
  register short i;
  register unsigned char *dp;
  extern unsigned char LinearTable[];
  
gammaptr = msp->mygammaptr;
/* Check for a linear table request */
if ((thetable == 0) || (thetable == -1)) 
  {
    /* Initialize the table header */  
    gammaptr->gVersion     = 0;    	/* Currently 0 for all cards */
    gammaptr->gType        = DrHw;	/* DrHwTFB = 0, DrHwRasterOps24Mxi = ? */
    gammaptr->gFormulaSize = 0;  	/* Formula size = 0, no formula data */
    gammaptr->gChanCnt     = 1;   	/* Can be 1 or 3 for separate r,g, & b tables */
    gammaptr->gDataCnt     = 256;	/* 256 entries per table maximum */
    gammaptr->gDataWidth   = 8;		/* 8 bits per entry */
    dp 					   = LinearTable;
  }
else
  {    
    /* Check for the presence of formula data or an incorrect version (non-zero) */
    if ((thetable->gFormulaSize) || (thetable->gVersion != 0)) return(controlErr);
    /* Check for a valid ID - either our ID (DrHwRasterOpsCB224) or Apple's ID (DrHwTFB) */ 
    if ((thetable->gType) && (thetable->gType != DrHw)) return(controlErr);
    /* Check for more 8-bit entries in the table than we can handle (256 is MAX) */
    if ((thetable->gDataCnt != 256) || (thetable->gDataWidth != 8)) return(controlErr);
    /* Check for a valid number of tables (1 or 3) */
    if ((thetable->gChanCnt != 1) && (thetable->gChanCnt != 3)) return(controlErr);
    /* Copy the table header */  
    gammaptr->gVersion     = thetable->gVersion;      /* Currently 0 for all cards */
    gammaptr->gType        = thetable->gType;         /* DrHwTFB = 0,  DrHwRasterOps24Mxi = ? */
    gammaptr->gFormulaSize = thetable->gFormulaSize;  /* Formula size = 0, no formula data */
    gammaptr->gChanCnt     = thetable->gChanCnt;      /* Can be 1 or 3 for separate r,g, & b tables */
    gammaptr->gDataCnt     = thetable->gDataCnt;      /* 256 entries per table maximum */
    gammaptr->gDataWidth   = thetable->gDataWidth;    /* 8 bits per entry */
    dp                     = (unsigned char *)&(thetable->gData);
  }
  
if (gammaptr->gChanCnt == 3) 
  {
    for (i=0;i<256;i++) gammaptr->gData.gRTable[i] = *dp++;
    for (i=0;i<256;i++) gammaptr->gData.gGTable[i] = *dp++;
    for (i=0;i<256;i++) gammaptr->gData.gBTable[i] = *dp++;
  }
else for (i=0;i<256;i++) 
   gammaptr->gData.gBTable[i] = gammaptr->gData.gGTable[i] = gammaptr->gData.gRTable[i] = *dp++;
return(noErr);
}
/*_______________________________________________________________________________________
  setdirect()
_______________________________________________________________________________________*/
OSErr setdirect(dcep)
AuxDCEPtr dcep;			/* Auxiliary Device Control Entry pointer. */
{
  mystorage		*msp;		/* pointer to my private storage */
  register short	i;
  unsigned char		*clutbackupbase;
  unsigned char		*clutbackup;
  register unsigned long *base;
  unsigned short	*table;
  unsigned char		mmu_mode;		/* MMU Mode (0=24-bit addressing 1=32-bit addressing) */
  register unsigned long xrgb;
  register unsigned long *clutbufptr;
  GammaTable		*gammaptr;				/* Gamma Table block pointer */
  unsigned char		*gammaptr_r,*gammaptr_g,*gammaptr_b;	/* Gamma Table data pointers */
  unsigned long		index;
  
  base = (unsigned long *)((dcep->dCtlDevBase | (long)0xFA0000));
    /* Dereference locked handle to private storage */
  msp = (struct mystorage *)*(dcep->dCtlStorage);
  msp = (mystoragePtr) StripAddress(msp);
  
    /* Use the buffer we allocated in Open() */
  clutbufptr = (unsigned long *)msp->lutBuffer;
  
  clutbackupbase = (unsigned char *)((unsigned long)(&(msp->clut)));
  clutbackupbase = (unsigned char *)StripAddress((Ptr)clutbackupbase);  /* mask possible master pointer flag bits */
  gammaptr = (GammaTable *)(msp->mygammaptr);
  gammaptr = (GammaTable *)StripAddress((Ptr)gammaptr);  /* mask possible master pointer flag bits */
  /* get pointers to r,g,b gamma table or tables */
  gammaptr_r = msp->mygammaptr->gData.gRTable;
  gammaptr_g = msp->mygammaptr->gData.gGTable;
  gammaptr_b = msp->mygammaptr->gData.gBTable;
  
  for (i=0;i<256;i++)
  {
    clutbackup = clutbackupbase + i * 3;
    
      /* Write the corrected values to our backup table. */
    clutbackup[0] = gammaptr_r[i];
    clutbackup[1] = gammaptr_g[i];
    clutbackup[2] = gammaptr_b[i];
    xrgb = ((unsigned long)clutbackup[0] << 16) |
	    ((unsigned long)clutbackup[1] << 8) |
	    ((unsigned long)clutbackup[2]);
    *clutbufptr++ = ((unsigned long)i << 24) | xrgb;  /* index -> 8 bits of high byte */
    table += 4;
  }
    /* Send buffered data to the DACs */
  clutbufptr = (unsigned long *)msp->lutBuffer;
#if 0  
  /* Too big to send in one blanking period? ???? may not be necessary */
    /* Send first half. */
  /* turn off interrupts???? */
  waitvblank((((unsigned long)(base)) & (unsigned long)0xFF000000));
  /* turn off interrupts???? */
#asm
	MOVE	SR,-(SP)		; Save state
	MOVE.W	#$2700,SR		; Disable interrupts
#endasm
  sendlut(base, clutbufptr, 128);
#asm
	MOVE	(SP)+,SR		; Restore interrupts
#endasm
  clutbufptr +=128;
  /* Send remaining buffer. */
  waitvblank((((unsigned long)(base)) & (unsigned long)0xFF000000));
  /* turn off interrupts???? */
#asm
	MOVE	SR,-(SP)		; Save state
	MOVE.W	#$2700,SR		; Disable interrupts
#endasm
  sendlut(base, clutbufptr, 128);
#asm
	MOVE	(SP)+,SR		; Restore interrupts
#endasm
#else
  /* Send in one blanking period? ???? */
  waitvblank((((unsigned long)(base)) & (unsigned long)0xFF000000));
  /* turn off interrupts???? */
#asm
	MOVE	SR,-(SP)		; Save state
	MOVE.W	#$2700,SR		; Disable interrupts
#endasm
  sendlut(base, clutbufptr, 256);
#asm
	MOVE	(SP)+,SR		; Restore interrupts
#endasm
#endif
  return(0);	/* Successful completion. */  
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of setdirect^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*_______________________________________________________________________________________
  setlut()
_______________________________________________________________________________________*/
OSErr setlut(thetable,start,count,dcep)
unsigned short *thetable;
short start,count;
AuxDCEPtr dcep;			/* Auxiliary Device Control Entry pointer. */
{
	mystorage				*msp;		/* pointer to my private storage */
	short					addr;
	short					mapmode;
	short					buffcount;
	register short			color;
	register short			i;
	unsigned char			*clutbackupbase;
	unsigned char			*clutbackup;
	register unsigned long	*base;
	unsigned short			*table;
	unsigned char			mmu_mode;	/* MMU Mode (0=24-bit addressing 1=32-bit addressing) */
	register unsigned char	*clutbufptr;
	GammaTable				*gammaptr;	/* Gamma Table block pointer */
	unsigned char			*gammaptr_r;	/* Gamma Table data pointers */
	unsigned char			*gammaptr_g;	/* Gamma Table data pointers */
	unsigned char			*gammaptr_b;	/* Gamma Table data pointers */
	short					index_shift;
	unsigned char			index;
	Boolean					depth16;
  
	if(thetable == nil)	/* Must have  valid pointer to continue */
		return(controlErr);
    
	base = (unsigned long *)((dcep->dCtlDevBase | (long)0xFA0000));
	/* Dereference locked handle to private storage */
	msp = (struct mystorage *)*(dcep->dCtlStorage);
	msp = (mystoragePtr) StripAddress(msp);
	/* Use the buffer we allocated during Open() */
	clutbufptr = (unsigned char *)msp->lutBuffer;
	clutbackupbase = (unsigned char *)((unsigned long)(&(msp->clut)));
	clutbackupbase = (unsigned char *)StripAddress((Ptr)clutbackupbase);  /* mask possible master pointer flag bits */
	gammaptr = (GammaTable *)(msp->mygammaptr);
	gammaptr = (GammaTable *)StripAddress((Ptr)gammaptr);  /* mask possible master pointer flag bits */
	mapmode = ((msp->bwmapping) && (msp->mode < 0x84));       /* disable gray mapping for direct mode */
	table = (unsigned short *)StripAddress((Ptr)thetable);  /* mask possible master pointer flag bits */
	/* get pointers to r,g,b gamma table or tables */
	gammaptr_r = msp->mygammaptr->gData.gRTable;
	gammaptr_g = msp->mygammaptr->gData.gGTable;
	gammaptr_b = msp->mygammaptr->gData.gBTable;
	
	switch(msp->mode)
	{
		case 0x80:	index_shift = 7;	/* 1 bit mode  -  indices *= $80 */
					break;
		case 0x81:	index_shift = 6;	/* 2 bit mode  -  indices *= $40 */
					break;
		case 0x82:	index_shift = 4;	/* 4 bit mode  -  indices *= $10 */
					break;
		case 0x83:
		default:	index_shift = 0;	/* 8 bit mode  -  indices *= $00 */
					break;
	}
	depth16 = (msp->mode == 0x84);
	
	buffcount  = 0;
	for (i=0;i<=count;i++)
	{
		addr = (start == -1) ? addr = table[0] & (unsigned short)0x00FF : (start+i) & (unsigned short)0x00FF;
		if(depth16)
			index = (addr << 3) | (addr >> 2);
		else
			index = addr;
		clutbackup = clutbackupbase + index * 3;
		if (mapmode)     /* Convert to grayscale. */
		{
			/* Convert to grayscale using the sum of 30% red, 60% green, 10% blue. */
			color = (((unsigned long)table[1] & 0xFF00)*3 +
					((unsigned long)table[2] & 0xFF00)*6 +
					((unsigned long)table[3] & 0xFF00))/10;
			
			/* Round up if there's enough remainder. */
			color  = (color & 0x0080) ? 1 + (color >> 8) : color >> 8;	    
			color &= (unsigned short)0x00FF;
			clutbackup[0] = gammaptr_r[color];
			clutbackup[1] = gammaptr_g[color];
			clutbackup[2] = gammaptr_b[color];
		}
		else  /* Just send the bytes to the DAC's. */
		{
			clutbackup[0] = gammaptr_r[table[1]>>8];
			clutbackup[1] = gammaptr_g[table[2]>>8];
			clutbackup[2] = gammaptr_b[table[3]>>8];
		}
		
		/* index -> high bit of high byte */
		*clutbufptr++ = index << index_shift;
		/* use gamma corrected value */
		*clutbufptr++ = clutbackup[0];
		*clutbufptr++ = clutbackup[1];
		*clutbufptr++ = clutbackup[2]; 
				
		buffcount++;
		table += 4;
	}
	/* Send buffered data to the DACs */
	clutbufptr = (unsigned char *)msp->lutBuffer;
	/* turn off interrupts */
#asm
	MOVE	SR,-(SP)		; Save state
	MOVE.W	#$2200,SR		; Disable interrupts
#endasm
#if 0
	/* Send in chunk of 64 per blanking period */
	while(buffcount > 64)
	{
		waitvblank((((unsigned long)(base)) & (unsigned long)0xFF000000));
		sendlut(base, clutbufptr, 64);
		buffcount -= 64;
		clutbufptr +=64;
	}
	/* Send remaining buffer. */
	if(buffcount > 0)
	{
		waitvblank((((unsigned long)(base)) & (unsigned long)0xFF000000));
		sendlut(base, clutbufptr, buffcount);
	}
#else
	/* Send in one chunk of up to 256 per blanking period */
    waitvblank((((unsigned long)(base)) & (unsigned long)0xFF000000));
    sendlut(base, clutbufptr, buffcount);
#endif
#asm
	MOVE	(SP)+,SR		; Restore interrupts
#endasm
	return(0);	/* Successful completion. */  
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of setlut^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*_______________________________________________________________________________________
	sendlut
_______________________________________________________________________________________*/
sendlut(base, clutbufptr, buffcount)
unsigned long *base, clutbufptr;
short buffcount;
{
#asm
	MOVEM.L	A0-A5/D0-D7,-(sp)	; Save nearly all registers
	MOVEQ   #1,D0
	DC.W    $A05D			; SwapMMUMode to 32 bit
	MOVE.B  D0,D3			; save previous mmu mode in D3
	MOVE.L	8(A6),A0		; Get DAC base address
	MOVE.L	12(A6),A1		; Get buffer address
	MOVE.W	16(A6),D0		; Get buffer count
	EXT.L	D0
	SUBQ.L	#1,D0			; adjust for DBF
lutloop	
	MOVE.B	(A1)+,3(A0)		; index to address register
	NOP 					;NOP acts as a syncio intruction on Power PC
	MOVE.B	(A1)+,7(A0)		; red data to data register
	MOVE.B	(A1)+,7(A0)		; green data to data register
	MOVE.B	(A1)+,7(A0)		; blue data to data register
	DBF	D0,lutloop		; loop for count
	
	MOVE.B  D3,D0			; restore previous mmu mode
	DC.W    $A05D			; SwapMMUMode
	MOVEM.L	(SP)+,A0-A5/D0-D7	; Restore nearly all registers
#endasm
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of sendlut^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*____________________________________________________________________________________________
	waitvblank
____________________________________________________________________________________________*/
waitvblank(base)
unsigned long base;
{
#asm
	BRA.S	waitStart
Regs
	DC.L	0,0,0
waitStart
	MOVE.L	A0,D0
	LEA		Regs,A0
	MOVE.L	D1,(A0)+
	MOVE.L	D2,(A0)+
	MOVE.L	D0,(A0)+
	MOVEA.L	8(SP),A0
	MOVE.L	#$FB0000,D2
	MOVE	SR,-(SP)		; Save state
	MOVE.W	#$2700,SR		; Disable interrupts
	MOVEQ	#1,D0
	_SwapMMUMode
	MOVE.L	D0,D1
waitNoBlank
	BTST.B	#4,$13(A0,D2.L)
	BNE.S	waitNoBlank
waitBlank
	BTST.B	#4,$13(A0,D2.L)
	BEQ.S	waitBlank
	
	MOVE.L	D1,D0
	_SwapMMUMode
	MOVE	(SP)+,SR		; Restore interrupts
	LEA		Regs,A0
	MOVE.L	(A0)+,D1
	MOVE.L	(A0)+,D2
	MOVE.L	(A0)+,D0
	MOVEA.L	D0,A0
	MOVEQ	#0,D0
#endasm
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of waitvblank^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*____________________________________________________________________________________________
	getlut
____________________________________________________________________________________________*/
getlut(thetable,start,count,dcep)
unsigned short *thetable;
short start,count;
AuxDCEPtr dcep;        /* Auxiliary Device Control Entry pointer. */
{
	mystorage				*msp;		/* pointer to my private storage */
	register short			color,addr,i;
	register unsigned char	*clutbackup;
	register unsigned short	*table;
	Boolean					depth16;
  
	/* Dereference locked handle to private storage */
	msp = (struct mystorage *)*(dcep->dCtlStorage);
	msp = (mystoragePtr) StripAddress(msp);
	
	clutbackup = (unsigned char *)(&(msp->clut));
	table = thetable;
	if (start == -1)
	{
		for (i=0;i<=count;i++)               /* Yank the values in order from our byte table (R,G,B). */
		{
			addr = table[i*4];
			if(depth16)
				addr = (addr << 3) | (addr >> 2);
			table[i*4+1] = clutbackup[addr*3];
			table[i*4+2] = clutbackup[addr*3+1];
			table[i*4+3] = clutbackup[addr*3+2];
		}
	}
	else
	{
		for (i=0;i<=count;i++)               /* Yank the values in order from our byte table (R,G,B). */
		{
			addr = start + i;
			if(depth16)
				addr = (addr << 3) | (addr >> 2);
			table[i*4+1] = clutbackup[addr*3];
			table[i*4+2] = clutbackup[addr*3+1];
			table[i*4+3] = clutbackup[addr*3+2];
		}
	}
}
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of getlut^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*______________________________________________________________________________________________
 Board Interrupt Handler
 On entry:  A1 contains the slot base address
            D0-D3/A0-A3 have already been preserved
            (But *not* in AUX, so save them anyway!)
______________________________________________________________________________________________*/
#asm
_intrpthandler
	MOVEM.L	A0-A5/D1-D7,-(sp) ; Save nearly all registers
	MOVEQ	#1,D0
	DC.W	$A05D			; SwapMMUMode
	MOVE.W	D0,D3			; save previous mmu mode
	MOVE.L	A1,D2			; get slot base address in A0
	ANDI.L	#$FF000000,D2	; 32 bit slot base address in D2
	MOVE.L	D2,A0			; stow slot base address in A0
	
 if AUTOSWITCHING
 if MAKING24MXTV
;
; if not interlaced skip
; if genlock changed goto c routine else skip
;
	MOVE.B	(VENUS_CTL3,A0),D0
	BTST	#3,D0
	BEQ		nochange
;
;	check gio register
;	GD(bit 5)		0: is genlock	1: is not genlock
;	SYNCOUT(bit 7)	0: was genlock	1: was not genlock
;
	MOVE.B	(GIOREGLOW,A0),D0
	ANDI	#$000000A0,D0
	BEQ		nochange			; was genlock and is genlock
	CMP.B	#$A0,D0
	BEQ		nochange			; was not genlock, is not genlock
;
;	genlock changed, goto c routine
;
	MOVE.L	D3,D0
	DC.W	$A05D			; SwapMMUMode
	MOVEM.L	A0-A2/D0-D3,-(sp)	; Save nearly all registers
	MOVE.L	A0,-(SP)			; push SeBlock pointer
	JSR		_cInterrupt			; call our c routine
	LEA		4(SP),SP			; repair stack caused by c call
	MOVEM.L	(SP)+,A0-A2/D0-D3 	; Restore nearly all registers
	
	MOVEQ	#1,D0
	DC.W	$A05D			; SwapMMUMode
	MOVE.W	D0,D3			; save previous mmu mode
 endc
 endc
 
nochange	
	ADDA.L	#$FB0000,A0 	; add offset to status register 1
	MOVE.L	$10(A0),D0
	ANDI.L	#$000000001,D0
	BNE.S	clearit
	MOVE.W	D3,D0
	DC.W	$A05D			; SwapMMUMode
	MOVEQ	#0,D0			; signal that the interrupt was not serviced
	BRA		out
	
clearit
	MOVE.L	#00000002,$10(A0)
	
	MOVE.W	D3,D0			; restore previous mmu mode
	DC.W	$A05D			; SwapMMUMode
	MOVE.L	A1,D0			; stow slot base address in D0
 							; D0 is currently: $Fs0xxxxx, we need: $0000000s
	ROL.L 	#8,D0			; D0 is now: $0xxxxxFs
	ANDI.L	#$F,D0			; D0 is now: $0000000s, the slot number
	MOVEA.L	$D28,A0			; get the address of the VBL task manager
	JSR	(A0)				; go service the interrupt with slot number in D0
	MOVEQ	#1,D0			; signal that the interrupt was serviced
out
	MOVEM.L	(SP)+,A0-A5/D1-D7 ; Restore nearly all registers
	RTS						; run home to mommy-caller
#endasm
#if AUTOSWITCHING
#if MAKING24MXTV
/*
 * cInterrupt()
 *
 */
cInterrupt(base)
unsigned long	base;
{
	register unsigned long	*rgs14188_ptr;
	register unsigned long	*table_ptr;
	register short			i;
	SpBlock					SpBlk;				/* our sp block to make the slot manager call */
	register SpBlock		*SpPtr = &SpBlk;	/* our sp block to make the slot manager call */
	short					flags;
	char					mmu_mode;
	
#if DEBUG
	myDebugStr("\PcInterrupt: enter");
#endif
	
	rgs14188_ptr = (unsigned long *)(base + RGS14188);
	mmu_mode = true32b;	/* 32 bit mode */
	drSwapMMUMode(&mmu_mode);
		
	flags = 0;
	
/*	if(ISGENLOCK(base)) /* rereading -GD may not be reliable???? */
	if(rgs14188_ptr[gio_reg_Lo] & 0x0080)	/* if sync out is high, -GD must have gone low */
		flags |= BIT_GENLOCK;
	if(ISPAL(base))
		flags |= BIT_PAL;
	if(ISUNDERSCAN(base))
		flags |= BIT_UNDERSCAN;
	
	drSwapMMUMode(&mmu_mode);
	/*
	 * find out the table to load, depending on the flags
	 * bit2: pal
	 * bit1: genlock
	 * bit0: underscan
	 */
	switch(flags) {
		case 0x0:			/*000 */
				i = TIMING_ID_6x4ntsc;
				break;
				
		case 0x1:			/*001 */
				i = TIMING_ID_5x4ntsc;
				break;
				
		case 0x2:			/*010 */
				i = TIMING_ID_6x4ntscGL;
				break;
				
		case 0x3:			/*011 */
				i = TIMING_ID_5x4ntscGL;
				break;
				
		case 0x4:			/*100 */
				i = TIMING_ID_7x5pal;
				break;
		case 0x5:			/*101 */
				i = TIMING_ID_6x5pal;
				break;
		case 0x6:			/*110 */
				i = TIMING_ID_7x5palGL;
				break;
				
		case 0x7:			/*111 */
				i = TIMING_ID_6x5palGL;
				break;
	}
	/* Find parameter resource */
	SpPtr->spSlot = (base >> 24) & 0x0F;
	SpPtr->spExtDev = 0;
	SpPtr->spID = sRsrcBoard;		/* Find Board Resource */
	drSRsrcInfo(SpPtr);
	SpPtr->spID = sTimingTableDir;	/* Find Resoulution Directory */
	drSFindStruct(SpPtr);
	SpPtr->spID = i;				/* Find Parameters */
	drSFindStruct(SpPtr);
	
	table_ptr = (unsigned long *)(SpPtr->spsPointer + 16 - 3); /* skip count and adjust byte lane for long access */
#define	NEW_CODE	1
#if NEW_CODE
	/*
	 * Send Initialization Table out to RGS14188
	 */
	mmu_mode = true32b;		/* prepare to change to 32 bit mode */
	drSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	
#if DEBUG
	myDebugStr("\PcInterrupt: do control3,gio");
#endif
	/*
	 * Turn on refresh, transfer enable, and sync
	 */
	if(flags & BIT_GENLOCK) {
/* myDebugStr("\Pto genlock"); */
		rgs14188_ptr[control_3] &= ~0x0010;					/* STG off */
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		rgs14188_ptr[control_3] |= 0x0080;					/* Change Venus syncs to inputs */
		rgs14188_ptr[gio_reg_Lo] &= ~0x0080;				/*  Change syncs to inputs */
		for(i = horiz_latency; i <= vert_int_line_Lo; i++)	/* Load timing */
			rgs14188_ptr[i] = table_ptr[i];
		rgs14188_ptr[gio_reg_Lo] = table_ptr[gio_reg_Lo];	/* Clock select, BAC reset */
		rgs14188_ptr[control_3] |= 0x0010;					/* STG on */
		rgs14188_ptr[gio_reg_Lo] |= 0x0040;					/*  BAC reset off */
	}
	else {
/* myDebugStr("\Pfrom genlock"); */
		rgs14188_ptr[control_3] &= ~0x0010;					/* STG off */
		rgs14188_ptr[gio_reg_Lo] &= ~0x0080;				/*  Change syncs to outputs */
		rgs14188_ptr[control_3] &= ~0x0080;					/* Change Venus syncs to outputs */
		for(i = horiz_latency; i <= vert_int_line_Lo; i++)	/* Load timing */
			rgs14188_ptr[i] = table_ptr[i];
		rgs14188_ptr[gio_reg_Lo] = table_ptr[gio_reg_Lo];	/* Clock select, BAC reset */
		rgs14188_ptr[control_3] |= 0x0010;					/* STG on */
		rgs14188_ptr[gio_reg_Lo] |= 0x0040;					/*  BAC reset off */
	}
	drSwapMMUMode(&mmu_mode);
#else
	/*
	 * Send Initialization Table out to RGS14188
	 */
	mmu_mode = true32b;		/* prepare to change to 32 bit mode */
	drSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	
	for(i = control_1; i <= control_4; i++)
		rgs14188_ptr[i] = table_ptr[i];
	for(i = horiz_latency; i <= vert_int_line_Lo; i++)
		rgs14188_ptr[i] = table_ptr[i];
		
#if DEBUG
	myDebugStr("\PcInterrupt: do control3,gio");
#endif
	/*
	 * Turn on refresh, transfer enable, and sync
	 */
	if(flags & BIT_GENLOCK) {
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		rgs14188_ptr[control_1] |= 0x91;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		rgs14188_ptr[control_3] |= 0x00f2;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		rgs14188_ptr[gio_reg_Lo] = table_ptr[gio_reg_Lo];
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		rgs14188_ptr[control_1] |= 0xB1;
	}
	else {
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		rgs14188_ptr[control_1] |= 0x91;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		rgs14188_ptr[gio_reg_Lo] = table_ptr[gio_reg_Lo];
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		rgs14188_ptr[control_3] |= 0x0072;
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
		rgs14188_ptr[control_1] |= 0xB1;
	}
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	rgs14188_ptr[gio_reg_Lo] |= soft_reset_off;
	
#asm
	NOP ;NOP acts as a syncio intruction on Power PC
#endasm 
	rgs14188_ptr[control_4] |= 5;		/* turn on interrupt */
		
	drSwapMMUMode(&mmu_mode);
#endif
}
#endif
#endif
#asm
_intrptend
;^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^end of Board Interrupt Handler^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#endasm
/********************************************************************************
 * PanZoom Code
 ********************************************************************************/
/* 
 *	void calcRects()
 *	
 *	Set up our fastSpeed & slowSpeed pan rectangles. Any mouse movement inside the
 *	panRect does NOT generate pan commands. Any mouse movement outside the panRect,
 *	but inside the currentScreen generates a slowSpeed pan command. Any mouse movement
 *	outside the currentScreen generates a fastSpeed pan command.
 *	
 *	Input:	msp				pointer to our globals			
 *	
 *	Uses:	currentY		(global) determines the "y" coordinates
 *			currentX		(global) determines the "x" coordinates
 *			currentZoom		(global) zoom state
 *			xSize			(global) virtual screen size
 *			ySize			(global) virtual screen size
 *			xResolution		(global) enlarged panning area real screen size
 *			yResolution		(global) enlarged panning area real screen size
 *			enableVD		(global) flag determining enlarged panning area
 *			Border			(global) determines the panning area
 *			
 *	Assigns:	currentScreen	(global) the rectangle of the current viewing screen
 *			panRect			(global) the rectangle enclosing the non-panning area
 */
void calcRects(msp)
mystoragePtr msp;
{
	Point theTop, theBottom;
		
	theTop.h = msp->currentX + msp->theRect.left; 
	theTop.v = msp->currentY + msp->theRect.top;
		
	theBottom.h = theTop.h + (msp->xResolution >> (msp->currentZoom - 1));
	theBottom.v = theTop.v + (msp->yResolution >> (msp->currentZoom - 1));
		
	SetRect(&msp->currentScreen, theTop.h, theTop.v, theBottom.h, theBottom.v);
	SetRect(&msp->panRect, msp->currentScreen.left, msp->currentScreen.top, msp->currentScreen.right, msp->currentScreen.bottom);
	InsetRect(&msp->panRect, msp->border, msp->border);
}
/************************************************************************************************/
/* 
 *	void Center(msp, direction)
 *	
 *	Center the zoom based on the global Boolean zCenter. 
 *	If zCenter is true we do a screen centered zoom.
 *	If zCenter is false we do a mouse based zoom.
 *	(Note: the top left of the screen is at 0,0 local coordinates
 *	the bottom right is at xSize-1,ySize-1 local coordinates)
 *	
 *	Input:	msp
 *			direction	In /Out (0/1)
 *	
 *	Uses:		zCenter 
 *			currentRate
 *			theMode
 *			currentZoom
 *	
 *	Assigns:	currentX
 *			currentY
 *		
 */
void Center(msp,direction)
register mystoragePtr msp;
short direction;
{
	Point mouseLoc;
	register short xBounds, yBounds;
	register short tempX, tempY;
 				
	tempX = ((long) msp->xResolution) >> (long) (msp->currentZoom-1);
	tempY = ((long) msp->yResolution) >> (long) (msp->currentZoom-1);
		
	xBounds = msp->xSize - tempX;
/****
	{
		short	granularity;
		short	mask;
		
		granularity = 1 << ((panPtr->theMode >= 3) ? 2 : (2+3-panPtr->theMode));
		mask = granularity - 1;
		xBounds = (xBounds + mask) & ~mask;
	}
*/
	yBounds = msp->ySize - tempY;
	
	tempX >>= 1;
	tempY >>= 1;
	if (msp->zCenter)
	{
		/*
		 * get the current x and y
		 */
		get_disp_start(msp);
		if (direction)
			msp->currentX -= tempX >> 1;
		else
			msp->currentX += tempX;
			
		if (msp->currentX < 0)
			msp->currentX = 0;		/* Stay on the screen */
		if (msp->currentX > xBounds)
			msp->currentX = xBounds;
		
		if (direction)
			msp->currentY -= tempY >> 1;
		else
			msp->currentY += tempY;
			
		if (msp->currentY < 0)
			msp->currentY = 0;		/* Stay on the screen */      		
		if (msp->currentY > yBounds)
			msp->currentY = yBounds;	
	}
	else
	{
		GetMouse(&mouseLoc);
		LocalToGlobal(&mouseLoc);
		
		/* Adjust for multiple monitors */
		/* Check left/right */
		if ((mouseLoc.h < 0) || (mouseLoc.h > msp->xSize))
			mouseLoc.h -= msp->theRect.left;
		/* Check up/down */
		if ((mouseLoc.v < 0) || (mouseLoc.v > msp->ySize))
			mouseLoc.v -= msp->theRect.top;
		
		/* Do X coordinate */
		msp->currentX = mouseLoc.h - tempX;
		if (msp->currentX < 0)
			msp->currentX = 0;		/* Stay on the screen */
		if (msp->currentX > xBounds)
			msp->currentX = xBounds;
		
		/* Do Y coordinate */
		msp->currentY = mouseLoc.v - tempY;
		if (msp->currentY < 0)
			msp->currentY = 0;
		if (msp->currentY > yBounds)
			msp->currentY = yBounds;		
	}   
}
	
/********************************************************************************************/
/* 
 *	void PanTo()
 *	
 *	Input:	msp             Auxiliary Device Control Entry pointer.
 *	
 *	Uses:	slot			(global) determines the hardware addresses
 */
void PanTo(x,y,msp)
short x,y;
mystoragePtr msp;
{
  	register unsigned long	val;
#if DEBUGZOOM  
	myDebugStr("\PPanTo: enter");
#endif
	msp->currentX = x;
	msp->currentY = y;
	
	set_disp_start(msp, (short) ADJUST_NONE);
}
/********************************************************************************************/
/* 
 *	void PanX()
 *	
 *	Pan in the x-direction.
 *	The Colorboard 108+ pan register (8-bit) is at: 0xD8000.
 *	
 *	Input:	direction	(-1) = pan left, 0 = pan right.
 *			speed		fastSpeed or slowSpeed
 *			msp             Auxiliary Device Control Entry pointer.
 *	
 *			
 *	Uses: 	slot 		(global) to compute the hardware addresses.
 *			currentZoom	(global) return if we are at zoom = 1X.
 *			enableVD	(global) enlarge panning option
 *		
 *	Assigns: currentX   	(global) top left of our view screen rectangle.
 *	
 *	Calls:	calcRects()	currentX was changed.
 */
void PanX(direction, amount, msp)
short					direction;
short					amount;
register mystoragePtr	msp;
{
	short xResolution;
	register short xBounds;
	register unsigned long	val;
	register unsigned long	x;
	
#asm
	MOVE	SR,-(SP)		; Save state
	MOVE.W	#$2200,SR		; Disable interrupts
#endasm
	get_disp_start(msp);
	
	if (direction == PANLEFT) {
		#if DEBUGZOOM
		myDebugStr("\PpanX24Mx: PANLEFT");
		#endif
		if(msp->currentX > 0) {
			msp->currentX -= amount;
			if(msp->currentX < 0)
				msp->currentX = 0;
			set_disp_start(msp, (short) ADJUST_LEFT);
		}
	}
	else {
		short	granularity;
		short	mask;
		short	saveX;
			
		xBounds = msp->xSize - (msp->xResolution >> (msp->currentZoom - 1));
		if(msp->currentX < xBounds) {
			msp->currentX += amount;
			if(msp->currentX > xBounds)
				msp->currentX = xBounds;
			/*
			 * This part is necessary because xBounds may not be a legal xstart.
			 * For example, if xResoultion=800, xSize=1152, zoom=2x, then xBound=752 which
			 * is not a legal xstart value for bitdepth=1, because an increment of 1 in
			 * display_start means a increment of 32 pixels and 752 is not a multiple of 32.
			 * Furthermore, we want to avoid odd values in display_start because of the bug
			 * in venus chip, that it may cause garbage lines to show up.
			 *
			 * granularity: number of pixels for an increment of 1 in display_start
			 * mask: to force to move to the next even boundary
			 */
			granularity = 1 << ((msp->theMode >= 3) ? 2 : (2+3-msp->theMode));
			mask = granularity - 1;
			msp->currentX = (msp->currentX + mask) & ~mask;
	
			set_disp_start(msp, (short) ADJUST_RIGHT);
		}
		else {	/* if (msp->currentX > xBounds) { */
			#if DEBUG
			myDebugStr("\PpanX24Mx: > xbound");
			#endif
			
			/*
			 * this part is to fix the bug that zoomin and out with cursor at corner
			 * sometimes throw it out of sync.
			 */
			saveX = msp->currentX;
			
			msp->currentX = xBounds;
			granularity = 1 << ((msp->theMode >= 3) ? 2 : (2+3-msp->theMode));
			mask = granularity - 1;
			msp->currentX = (msp->currentX + mask) & ~mask;
			{
				unsigned long	val;
				unsigned long	tmp;
				
				val = msp->currentY * msp->disp_pitch
				+ (msp->currentX >> ((msp->theMode >= 3) ? 2 : (2+3-msp->theMode)));
	
				tmp = adjust_pan(msp, (short) ADJUST_RIGHT, val);
				if(tmp > val)
					msp->currentX += granularity;
			}
			if(saveX != msp->currentX) {
				set_disp_start(msp, (short) ADJUST_RIGHT);
			}
		}
	}
	
	calcRects(msp);
#asm
	MOVE	(SP)+,SR		; Restore interrupts
#endasm
}
/********************************************************************************************/
/* 
 *	void PanY()
 *	
 *	Pan in the y-direction.
 *	
 *	The Colorboard 108+ pan (y) registerin the TMS34061 Display Start Register
 *	there are two byte locations: lo byte - 0xC0093 & hi-byte - 0xC009B which
 *	determine the row address of the starting video line.
 *		  
 *	Input:	direction		(-1) = pan down, 0 = pan up.
 *			speed			fastSpeed or slowSpeed
 *			msp             Auxiliary Device Control Entry pointer.
 *	
 *	Uses: 	slot 			(global) to compute the hardware addresses.
 *			currentRate		(global) used to determine the pan rate of speed
 *			ySize			(global) to calculate the boundary of our view screen.
 *			currentZoom		(global) return if we are at zoom = 1X.
 *	
 *	Assigns: currentY   		(global) bottom right of our view screen rectangle.
 *	
 *	Calls:	calcRects()		currentY was changed.
 */
void PanY(direction, amount, msp)
short direction, amount;
mystoragePtr msp;
{
	register short yBounds;
	register unsigned long	val;
	register unsigned long	y;
	
#asm
	MOVE	SR,-(SP)		; Save state
	MOVE.W	#$2200,SR		; Disable interrupts
#endasm
	get_disp_start(msp);
	
	if (direction == PANDOWN) {
		#if DEBUGZOOM
		myDebugStr("\PpanY24Mx: pandown");
		#endif
		if(msp->currentY > 0) {
			msp->currentY -= amount;
			if(msp->currentY < 0)
				msp->currentY = 0;
			set_disp_start(msp, (short) ADJUST_NONE);
		}
	}
	else {
  		#if DEBUGZOOM
		myDebugStr("\PpanY24Mx: panup");
		#endif
		yBounds = msp->ySize - (msp->yResolution >> (msp->currentZoom - 1));
		if(msp->currentY < yBounds) {
			msp->currentY += amount;
			if(msp->currentY > yBounds)
				msp->currentY = yBounds;
			set_disp_start(msp, (short) ADJUST_NONE);
		}
		else if(msp->currentY > yBounds) {
			msp->currentY = yBounds;
			set_disp_start(msp, (short) ADJUST_NONE);
		}
	}
	
	calcRects(msp);
#asm
	MOVE	(SP)+,SR		; Restore interrupts
#endasm
}
#if 0
/********************************************************************************************/
/*
 * trickyTiming()
 */
trickyTiming( VSB, vcrlo, vcrhi, xBase, dur, xValue, yValue)
short VSB;				/* Vertical Start Blank value */
long *vcrlo, *vcrhi; 	/* Vertical Count Registers */
long *xBase; 			/* X-Zoom Register */
long *dur; 				/* Display Update Register */
long xValue;			/* X Zoom values */
short yValue; 			/* Y Zoom values */
{
/****
#asm
	MOVEM.L	A1-A5/D1-D7,-(SP)	;save registers
; our return address is now at 4(SP) + (link A6= 4) + (5+7)*4 on the stack (4+48 = 56)
; VSB is at    56(SP)
; vcrlo is at  58(SP)
; vcrhi is at  62(SP)
; xBase is at  66(SP)
; dur is at    70(SP)
; xValue is at 74(SP)
; yValue is at 78(SP)
; Set up our local registers
; A0 <= option/status register
; A1 <= vcrlo
; A2 <= vcrhi
; A3 <= xBase
; A4 <= dur
; D0 <= Count1
; D1 <= Count2
; D2 <= VSB
; D3 <= xValue
; D4 <= yValue 
; D5 <= saved mmumode
	MOVE.L	58(SP),A1			; get vcrlo register address
	MOVE.L	62(SP),A2			; get vcrhi register address
	MOVE.L  A1,D0				; copy
	ANDI.L	#$FF000000,D0		; get our base address
	ORI.L	#$F70000,D0			; point to the option/status register
	MOVEA.L	D0,A0				; save it for later
	MOVE.L	66(SP),A3			; get the x-zoom register address
	MOVE.L	70(SP),A4			; get the display update register address
	MOVE	56(SP),D2			; VSB value
	MOVE.L	74(SP),D3			; x-zoom register value
	MOVE	78(SP),D4			; y-zoom register value
	MOVE	SR,-(SP)			; disable interrupt, added to fix pan around cursor problem
	MOVE	#$2200,SR
	MOVEQ	#1,D0				; 32-bit addressing mode
	_SwapMMUMode
	MOVE.L	D0,D5
vcrloop
	MOVE.B	(A2),D0				; get the vcrhi byte
	ROL.L	#8,D0				; shift it into the upper part of the word
	MOVE.B	(A1),D0				; get the vcrlo byte
	
	MOVE.B	(A2),D1				; get the vcrhi byte
	ROL.L	#8,D1				; shift it into the upper part of the word
	MOVE.B	(A1),D1				; get the vcrlo byte
	
	CMP		D0,D1				; are they the same?
	BNE.S	vcrloop				; no, try again
	
	CMP		D2,D0				; have we reached our terminal count?
	BMI.S	vcrloop				; nope, continue reading the count
	
hsyncloop
	MOVE.L	(A0),D0				; get the option/status register contents
	BTST	#6,D0				; are we in hsync
	BNE.S	hsyncloop			; nope, just loop
	BTST	#2,D0				; are we in vsync?
	BNE.S	done				; no, load 'em up
	
vsyncloop
	MOVE.L	(A0),D0				; get the option/status register contents
	BTST	#2,D0				; are we in vsync?
	BEQ.S	vsyncloop			; yes, wait until we are out of vsync
	BRA.S	vcrloop				; start all over again
	
done
	MOVE.L	D3,(A3)				; zoom in x
	MOVE	D4,(A4)				; zoom in y
	MOVE.L	D5,D0
	_SwapMMUMode
	MOVE	(SP)+,SR			; resotre the interrupts
	MOVEM.L	(SP)+,A1-A5/D1-D7	;restore registers
#endasm
*/
}
#endif
/********************************************************************************************/
/* 
 *	void ZoomIn()
 *	
 *	Input:	msp             Auxiliary Device Control Entry pointer.
 *	
 *	Uses:	slot			(global) determines the hardware addresses			
 */
void ZoomIn(msp)
mystoragePtr msp;
{
  	unsigned char	zoomval;
#if DEBUG 
	myDebugStr("\PZoomIn: enter");
#endif
#asm
	MOVE	SR,-(SP)		; Save state
	MOVE.W	#$2200,SR		; Disable interrupts
#endasm
	/*
	 * step1: get address
	 * step2: get current zoom value from yzoom register
	 * step3: zoom if possible
	 * step4: adjust screen by panning
	 */
	
	zoomval = get_zoom(msp->base);
		
	/*
	 * xzoom: 00: 1, 01: 2, 10:4, 11:8
	 */
	switch(zoomval) {
	case 1:
		set_zoom(msp, 2);
		msp->currentZoom = 2;
		Center(msp, 0);
		break;
		
	case 2:
		set_zoom(msp, 4);
		msp->currentZoom = 3;
		Center(msp, 0);
		break;
		
	case 4:
		set_zoom(msp, 8);
		msp->currentZoom = 4;
		Center(msp, 0);
		break;
		
	default:
		break;
	}
	PanTo(msp->currentX,msp->currentY,msp);
	PanY(PANUP,0,msp);
	PanX(PANRIGHT,0,msp);
	calcRects(msp);
#asm
	MOVE	(SP)+,SR		; Restore interrupts
#endasm
}
/********************************************************************************************/
/* 
 *	void ZoomOut()
 *	
 *	Input:	msp             Auxiliary Device Control Entry pointer.
 *	
 *	Uses:	slot			(global) determines the hardware addresses
 */
void ZoomOut(msp)
mystoragePtr msp;
{
  	unsigned char	zoomval;
#if DEBUG  
	myDebugStr("\PZoomOut: enter");
#endif
#asm
	MOVE	SR,-(SP)		; Save state
	MOVE.W	#$2200,SR		; Disable interrupts
#endasm
	/*
	 * step1: get address
	 * step2: get current zoom value from yzoom register
	 * step3: zoom if possible
	 * step4: adjust screen by panning
	 */
	
	zoomval = get_zoom(msp->base);
		
	/*
	 * xzoom: 00: 1, 01: 2, 10:4, 11:8
	 */
	switch(zoomval) {
		case 2:
			set_zoom(msp, 1);
			msp->currentZoom = 1;
			Center(msp, 1);
			break;
			
		case 4:
			set_zoom(msp, 2);
			msp->currentZoom = 2;
			Center(msp, 1);
			break;
			
		case 8:
			set_zoom(msp, 4);
			msp->currentZoom = 3;
			Center(msp, 1);
			break;
			
		default:
			break;
	}
	PanTo(msp->currentX,msp->currentY,msp);
	PanY(PANUP,0,msp);
	PanX(PANRIGHT,0,msp);
	calcRects(msp);
#asm
	MOVE	(SP)+,SR		; Restore interrupts
#endasm
}
/*
 * get_zoom()
 */
unsigned char get_zoom(base)
unsigned long base;
{
	unsigned char	mmuMode;
	unsigned char	rc;
	mmuMode = 1;	/* 32 bit addressing mode */
	drSwapMMUMode(&mmuMode);
	rc = (*(unsigned char *) (base | YZOOMREG));
	drSwapMMUMode(&mmuMode);
	return rc;
}
	
/*
 * set_zoom()
 *
 * factor:	1	2	4	8
 *
 * xzoom:	0	1	2	3	
 * yzoom:	1	2	4	8
 */
void set_zoom(msp, zoomfactor)
register mystoragePtr	msp;
short					zoomfactor;
{
	register unsigned long	base;
	unsigned char			mmuMode;
	short					xzoom;
#if MAKING24MXTV
	short					pram5;
	pram5 = drGetPRAM5(msp->slot);
#endif
	base = msp->base;
	switch(zoomfactor) {
		case 1:
			xzoom = 0;
			break;
		case 2:
			xzoom = 1;
			break;
		case 4:
			xzoom = 2;
			break;
		case 8:
			xzoom = 3;
			break;
	}
			
	mmuMode = 1;	/* 32 bit addressing mode */
	drSwapMMUMode(&mmuMode);
	SET_XZOOM(base, xzoom);
	SET_YZOOM(base, zoomfactor);
#if MAKING24MXTV
	/* non-interlaced && 1x zoom && non-extended needs to have refresh off */
	if(((pram5 & 0x8f) < FirstInterlaced) && ((msp->desk_sRsrcId & 0x8f) < FirstExtended))
	{
		if (zoomfactor == 1)
			REFRESH_OFF(base);
		else
			REFRESH_ON(base);
	}
#endif
	drSwapMMUMode(&mmuMode);
}
	
/*
 * get_disp_start()
 */
void get_disp_start(msp)
mystoragePtr msp;
{
	unsigned long			base;
	register unsigned long	*rgs14188_ptr;
	register unsigned char	*ptr;
	unsigned long			val;
	char					mmu_mode;
	register unsigned long	x;
	register unsigned long	y;
	
#asm
	MOVE	SR,-(SP)		; Save state
	MOVE.W	#$2200,SR		; Disable interrupts
#endasm
	base = msp->base;
	rgs14188_ptr = (unsigned long *)(base + RGS14188);
	rgs14188_ptr += display_start;
	ptr = (unsigned char *) &val;
	
	mmu_mode = true32b;		/* prepare to change to 32 bit mode */
	drSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	*ptr++ = *rgs14188_ptr++;
	*ptr++ = *rgs14188_ptr++;
	*ptr++ = *rgs14188_ptr++;
	*ptr++ = *rgs14188_ptr++;
	drSwapMMUMode(&mmu_mode);
	val &= 0x00ffffff;
	y = val / msp->disp_pitch;
	x = val - msp->disp_pitch * y;
	x <<= ((msp->theMode >= 3) ? 2 : (2+3-msp->theMode));
	msp->currentX = x;
	msp->currentY = y;
#asm
	MOVE	(SP)+,SR		; Restore interrupts
#endasm
}
		
/*
 * set_disp_start()
 */
void set_disp_start(msp, adjust)
register mystoragePtr	msp;
short					adjust;
{
	register unsigned long	val;
	
	#if DEBUG
	myDebugStr("\Pset_disp_start: enter");
	#endif
#asm
	MOVE	SR,-(SP)		; Save state
	MOVE.W	#$2200,SR		; Disable interrupts
#endasm
	val = msp->currentY * msp->disp_pitch
			+ (msp->currentX >> ((msp->theMode >= 3) ? 2 : (2+3-msp->theMode)));
	val = adjust_pan(msp, adjust, val);
		
	set_rgs(msp->base, (short) display_start, (long) val, (short) 4);
#asm
	MOVE	(SP)+,SR		; Restore interrupts
#endasm
}
/*
 * adjust_pan(msp, adjust, val)
 */
unsigned long
adjust_pan(msp, adjust, val)
register mystoragePtr	msp;
short					adjust;
unsigned long			val;
{
	register short	mask;
	register short	pitch;
	
	/*
	 * avoid the value
	 */
	if(adjust != ADJUST_NONE) {
		pitch = msp->disp_pitch;
		mask = 0;
		while((pitch & 0x1) == 0) {
			mask = (mask << 1) + 1;
			pitch >>= 1;
		}
		if((val & mask) == mask) {
		
			#if DEBUG
			myDebugStr("\Padjust_pan: adjust");
			#endif
		
			if(adjust == ADJUST_RIGHT)
				val += 1;
			else if(adjust == ADJUST_LEFT)
				val -= 1;
		}
	}
	return (unsigned long) val;
}
/*
 * get 14188 registers
 */
unsigned long dr_get_rgs(base, reg, bytes)
long	base;
short	reg;
register short	bytes;
{
	unsigned long	val;
	register unsigned char	*here;
	register unsigned long	*there;
	unsigned char	mmu_mode;
	
	val = 0;
	here = ((unsigned char *)&val) + 3;
	here = (unsigned char *) StripAddress(here);
	there = (unsigned long *)(base + RGS14188) + reg;
	switch(bytes)
	{
		case 2:	there += 1;
			break;
		case 3:
		case 4:	there += 3;
			break;
	}
	mmu_mode = true32b;		/* Prepare to change to 32 bit mode */
	drSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	while(bytes-- > 0)
		*here-- = *there--;
	drSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
	return val;
}
/*
 * set 14188 registers
 */
void set_rgs(base, reg, val, bytes)
long	base;
short	reg;
long	val;
register short	bytes;
{
	register unsigned char	*here;
	register unsigned long	*there;
	unsigned char	mmu_mode;
	
	here = ((unsigned char *)&val) + 3;
	here = (unsigned char *) StripAddress(here);
	there = (unsigned long *)(base + RGS14188) + reg;
	switch(bytes)
	{
		case 2:	there += 1;
			break;
		case 3:
		case 4:	there += 3;
			break;
	}
	mmu_mode = true32b;		/* Prepare to change to 32 bit mode */
	drSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	while(bytes-- > 0)
		*there-- = *here--;
	drSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
}
/*****************************************************************************
 * drEEPROM code
 *****************************************************************************/
#if MAKING24MXI
/*
 * dreeEnable()
 */
void dreeEnable(eep)
register long	*eep;	/* address of EE Prom */
{
	drEESendStartOpAddr(eep, (short) OP_EWEN, (short) ADDR_EWEN);
	drEEEpilog(eep);
}
/*
 * dreeDisable()
 */
void dreeDisable(eep)
register long	*eep;	/* address of EE Prom */
{
	drEESendStartOpAddr(eep, (short) OP_EWDS, (short) ADDR_EWDS);
	drEEEpilog(eep);
}
/*
 * dreeWriteWord()
 */
void dreeWriteWord(eep, addr, data)
register long	*eep;	/* address of EE Prom */
short			addr;
short			data;
{	
#if eeDEBUG
	myDebugStr("\PdreeWriteWord");
#endif
	dreeEnable(eep);
	drEESendStartOpAddr(eep, (short) OP_WRITE, addr);
	drEESendData(eep, data);
	drEEPollReady(eep);
	drEEEpilog(eep);
	dreeDisable(eep);
}	
/*
 * drEEPollReady()
 *
 * wait till data written is ready
 * quit after 10 ms no matter what
 */
short drEEPollReady(eep)
register long	*eep;	/* address of EE Prom */
{
	long	bits;
	short	i;
	drEEPoke(eep, 0, 0, 0);
	drEEPoke(eep, 1, 0, 0);
	drwait1ms();
	
	i = 10;
	while(i--) {
		bits = drEEPeek(eep);
		if(bits & 0x01) {
			return 1;
		}
		drwait1ms();
	}
	return 0;
}
/*
 * drEESendBitStream()
 */
void drEESendBitStream(eep, bits, n)
register long	*eep;	/* address of EE Prom */
register short	bits;	/* bits to send to eep */
register short	n;		/* number of bits to send, bits are right justified */
{
#if eeDEBUG
	myDebugStr("\PdrEESendBitStream");
#endif
	bits <<= (16 - n);
	while(n--) {
		if(bits >= 0) {
			drEEPoke(eep, 0, 1, 0);
			drEEPoke(eep, 1, 1, 0);
		}
		else {
			drEEPoke(eep, 0, 1, 1);
			drEEPoke(eep, 1, 1, 1);
		}
		bits <<= 1;
	}
}
/*
 * drEESendStartOpAddr()
 */
void drEESendStartOpAddr(eep, opcode, addr)
register long	*eep;	/* address of EE Prom */
register short	opcode;
register short	addr;
{
#if eeDEBUG
	myDebugStr("\PdrEESendStartOpAddr");
#endif
	drEEProlog(eep);	 	
	drEESendOpcode(eep, opcode);
	drEESendAddr(eep, addr);
}
/*
 * dreePoke()
 */
void dreePoke(eep, bits)
long	*eep;	/* address of EE Prom */
short	bits;
{
	char	mmu_mode;
	
	mmu_mode = true32b;
	drSwapMMUMode(&mmu_mode);
	*eep = (long) bits;
	drSwapMMUMode(&mmu_mode);
}
/*
 * dreePeek()
 */
short dreePeek(eep)
long	*eep;	/* address of EE Prom */
{
	char			mmu_mode;
	register long	w;
	
	mmu_mode = true32b;
	drSwapMMUMode(&mmu_mode);
	w = *eep;
	drSwapMMUMode(&mmu_mode);
	return ((short) w);
}
#endif
#if MAKING24MXTV
/*****************************************************************************
 * i2cEEPROM code (24MxTV)
 *****************************************************************************/
/*
 * i2cGetSCL()
 */
short
dri2cGetSCL(base)
long	base;
{
	unsigned char	mmu_mode;
	register unsigned short	the_data;
	
	mmu_mode = 1;		/* prepare to change to 32 bit mode */
	drSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	the_data = (*((unsigned long *)(base + pip_i2c)) & pip_i2c_clock) ? 1:0;
	drSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
	return the_data;
}
/*
 * i2cGetSDA()
 */
short
dri2cGetSDA(base)
long	base;
{
	unsigned char	mmu_mode;
	register unsigned short	the_data;
	
	mmu_mode = 1;		/* prepare to change to 32 bit mode */
	drSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	the_data = (*((unsigned long *)(base + pip_i2c)) & pip_i2c_data) ? 1:0;
	drSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
	return the_data;
}
/*
 * i2cSendBit()
 */
dri2cSendBit(base, bit)
register long	base;
register short	bit;
{
	if(!bit) {
		drSCL0_SDA0(base);
		drSCL1_SDA0(base);
	}
	else {
		drSCL0_SDA1(base);
		drSCL1_SDA1(base);
	}
}
/*
 * i2cSendByte()
 */
dri2cSendByte(base, s)
register long	base;
short	s;
{
	register char	b;
	register short	k;
	
	b = (char) s;
	k = 8;
	while(k--) {
		if(b >= 0)
			dri2cSendBit(base, 0);
		else
			dri2cSendBit(base, 1);
		b <<= 1;
	}
}
		
/*
 * i2cSendStartBit()
 */
short
dri2cSendStartBit(base)
register long	base;
{
	register short	i;
	register short	j;
	
	for(i = 0; i < 20; i++) {
		for(j = 0; j < 100; j++) {
			if((dri2cGetSCL(base) && dri2cGetSDA(base))) {
				goto getout;
			}
		}
		dri2cSendStopBit(base);
	}
	return -1;
getout:
	drSDA0(base);
	drSCL0(base);
	return 0;
}
/*
 * i2cSendStopBit()
 */
dri2cSendStopBit(base)
register long	base;
{
/*
	drSCL0_SDA0(base);
	drSCL0_SDA0(base);
	drSCL1_SDA0(base);
	drSCL1_SDA1(base);
*/
	drSDA1(base);
	drSCL0(base);
	drSCL1(base);
	
	drSCL0(base);
	drSDA0(base);
	drSCL1(base);
	drSDA1(base);
}
/*
 * i2cSetSCL()
 */
dri2cSetSCL(base, clock)
register long	base;
short	clock;
{
	register unsigned long	i2cState;
	unsigned char	mmu_mode;
	
	mmu_mode = 1;		/* prepare to change to 32 bit mode */
	drSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	i2cState = *((unsigned long *)(base + pip_i2c));
	
	if(clock)
		i2cState |= pip_i2c_clock;
	else
		i2cState &= ~pip_i2c_clock;
		
	*((unsigned long *)(base + pip_i2c)) = i2cState;
	drSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
	
	if(clock)
		drDelaySCL1();
	else
		drDelaySCL0();
}
/*
 * i2cSetSDA()
 */
dri2cSetSDA(base, data)
register long	base;
short	data;
{
	register unsigned long	i2cState;
	unsigned char	mmu_mode;
	
	mmu_mode = 1;		/* prepare to change to 32 bit mode */
	drSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	i2cState = *((unsigned long *)(base + pip_i2c));
	
	if(data)
		i2cState |= pip_i2c_data;
	else
		i2cState &= ~pip_i2c_data;
		
	*((unsigned long *)(base + pip_i2c)) = i2cState;
	drSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
}
/*
 * i2cSetSCLSDA()
 */
dri2cSetSCLSDA(base, clock, data)
register long	base;
register short	clock;
register short	data;
{
	register unsigned long	i2cState;
	unsigned char	mmu_mode;
	
	mmu_mode = 1;		/* prepare to change to 32 bit mode */
	drSwapMMUMode(&mmu_mode);	/* change to 32 bit mode */
	i2cState = *((unsigned long *)(base + pip_i2c));
	
	if(clock == 1)
		i2cState |= pip_i2c_clock;
	else
		i2cState &= ~pip_i2c_clock;
	if(data == 1)
		i2cState |= pip_i2c_data;
	else
		i2cState &= ~pip_i2c_data;
		
	*((unsigned long *)(base + pip_i2c)) = i2cState;
	drSwapMMUMode(&mmu_mode);	/* change back to 24 bit mode */
	
	if(clock)
		drDelaySCL1();
	else
		drDelaySCL0();
}
/*
 * i2cWaitAck()
 */
dri2cWaitAck(base)
register long	base;
{
	drSCL0_SDA1(base);
	dri2cWaitSDA0(base);
	drSCL1_SDA1(base);
	dri2cWaitSCL1(base);
}
/*
 * i2cWaitSCL1()
 */
short
dri2cWaitSCL1(base)
register long	base;
{
	register short	i;
	
	for(i = 3000; i > 0; i--) {
		if(dri2cGetSCL(base) == 1)
			return 0;
		else 
			drDelaySCL1();
	}
	return -1;
}
/*
 * i2cWaitSDA0()
 */
short
dri2cWaitSDA0(base)
register long	base;
{
	register short	i;
	
	for(i = 3000; i > 0; i--) {
		if(dri2cGetSDA(base) == 0)
			return 0;
		else 
			drDelaySCL0();
	}
	return -1;
}
/*
 * i2cWriteByte(base, addr, data)
 */
dri2cWriteByte(base, addr, data)
register long	base;
register short	addr;
register short	data;
{	
	dri2cSendStartBit(base);
	dri2cSendSlaveAddr(base, (short) (I2CADDR | I2CWRITE));
	dri2cWaitAck(base);
	dri2cSendWordAddr(base, addr);
	dri2cWaitAck(base);
	dri2cSendData(base, data);
	dri2cWaitAck(base);
	dri2cSendStopBit(base);
	
	/*
	 * wait for 30 ms
	 */
	drwaitnms(30);
}
/*
 * drclock_wait()
 */
drclock_wait(count)
register short	count;
{	
	count--;
	while(count-- >= 0)
		;
}
#endif
#asm
; ==================END OF DRIVER BLOCK=====================
    public endmydrvr
#endasm
