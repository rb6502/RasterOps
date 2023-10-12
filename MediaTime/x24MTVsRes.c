#asm
;*************************************************************
;Macros
;*************************************************************
;=============================================================
; Offset List Entry
;=============================================================
    MACRO  OSLstEntry
X%2
      DC.L          (%1<<24)+%2-X%2
    ENDM
;=============================================================
; Offset List Entry 80  640 x 480
;=============================================================
    MACRO  OSLstEntry80
X0%2
      DC.L          (%1<<24)+%2-X0%2
    ENDM
; PZ
;=============================================================
; Offset List Entry 81  1022 x 512
;=============================================================
    MACRO  OSLstEntry81
X1%2
      DC.L          (%1<<24)+%2-X1%2
    ENDM
;=============================================================
; Offset List Entry 82  2046 x 512
;=============================================================
    MACRO  OSLstEntry82
X2%2
      DC.L          (%1<<24)+%2-X2%2
    ENDM
 
;=============================================================
; Offset List Entry 83
;=============================================================
    MACRO  OSLstEntry83
X3%2
      DC.L          (%1<<24)+%2-X3%2
    ENDM
 
;=============================================================
; Offset List Entry 84
;=============================================================
    MACRO  OSLstEntry84
X4%2
      DC.L          (%1<<24)+%2-X4%2
    ENDM
 
;=============================================================
; Offset List Entry 85
;=============================================================
    MACRO  OSLstEntry85
X5%2
      DC.L          (%1<<24)+%2-X5%2
    ENDM
 
;=============================================================
; Offset List Entry 86
;=============================================================
    MACRO  OSLstEntry86
X6%2
      DC.L          (%1<<24)+%2-X6%2
    ENDM
 
;=============================================================
; Offset List Entry 87
;=============================================================
    MACRO  OSLstEntry87
X7%2
      DC.L          (%1<<24)+%2-X7%2
    ENDM
 
;=============================================================
; Offset List Entry 90  640 x 480
;=============================================================
    MACRO  OSLstEntry90
Y0%2
      DC.L          (%1<<24)+%2-Y0%2
    ENDM
; PZ
;=============================================================
; Offset List Entry 91  1022 x 512
;=============================================================
    MACRO  OSLstEntry91
Y1%2
      DC.L          (%1<<24)+%2-Y1%2
    ENDM
;=============================================================
; Offset List Entry 92  2046 x 512
;=============================================================
    MACRO  OSLstEntry92
Y2%2
      DC.L          (%1<<24)+%2-Y2%2
    ENDM
;=============================================================
; Offset List Entry 93
;=============================================================
    MACRO  OSLstEntry93
Y3%2
      DC.L          (%1<<24)+%2-Y3%2
    ENDM
 
 
;=============================================================
; Offset List Entry 94
;=============================================================
    MACRO  OSLstEntry94
Y4%2
      DC.L          (%1<<24)+%2-Y4%2
    ENDM
 
 
;=============================================================
; Offset List Entry 95
;=============================================================
    MACRO  OSLstEntry95
Y5%2
      DC.L          (%1<<24)+%2-Y5%2
    ENDM
 
 
;=============================================================
; Offset List Entry 96
;=============================================================
    MACRO  OSLstEntry96
Y6%2
      DC.L          (%1<<24)+%2-Y6%2
    ENDM
 
 
;=============================================================
; Offset List Entry 97
;=============================================================
    MACRO  OSLstEntry97
Y7%2
      DC.L          (%1<<24)+%2-Y7%2
    ENDM
 
 
 
;=============================================================
; Data List Entry
;=============================================================
    MACRO  DatLstEntry
      DC.L          (%1<<24)+%2
    ENDM
;*************************************************************
;Constants
;*************************************************************
CatDisplay		EQU	$0003	;
TypVideo		EQU	$0001	;
DrSwApple		EQU	$0001	;
DrSwAUX			EQU	$0003	;
;DrHwColorBoard364	EQU	$026F	;Assigned by Apple
;CB364BoardId		EQU	$028A 	;Assigned by Apple
DrHwRasterOps24STV	EQU	$02AD	;Assigned by Apple
CB24STVBoardId		EQU	$03A5 	;Assigned by Apple
DrHwRasterOps24MTV	EQU	$02CC	;Assigned by Apple
CB24MTVBoardId		EQU	$0406 	;Assigned by Apple
allSlaveBlockSizes	EQU	$0000800F 	;
#endasm
#define DrHwRasterOps24MTV	0x02CC
#define CB24MTVBoardId		0x0406
/* Offsets from base address to Registers */
#define CMODE		0x00FE6004L	/* 3RW	000(0) 1 Bit Mode */
					/* 		001(1) 2 Bit Mode */
					/* 		010(2) 4 Bit Mode */
					/* 		011(3) 8 Bit Mode */
					/* 		1xx(4-7) 24 Bit Mode */
#define OSC_SEL		0x00FE600CL	/* Oscillator select 0 = 60hz, 1 = 30hz */
#define NMRQ		0x00FE6010L	/*  1RW	Interrupt Request */
#define PAGE_CTL	0x00FE6018L	/*  2RW	PAGE control 0 = DAC, 1 = ADC, 2 = PIP Regs, 3 = PIP Control */
#define DISPLAY_ENABLE	0x00FE601CL	/*  1RW	0 forces blanked display */
#define EXT_SYNC_ENABLE	0x00FE6020L	/*  1RW	1 enables External sync */
#define FAT_SLOT	0x00FE6024L	/*  1RW	0 = skinny, 1 = fat slot decoding */
#define MON_TYPE	0x00FE6028L	/*  1R 	monitor present/type */
#define SYNC_ENABLE	0x00FE602CL	/*  1RW	1 enables sync */
#define TRANS_ENABLE	0x00FE6030L	/*  1RW	1 enables transfer cycles */
#define V_COUNT_END	0x00FE6034L	/*  1R 	1 if vertical count matches vertical total */
#define VID_RESET	0x00FE6038L	/*  1RW	1 holds all video counters reset */
#define NMRQ_DISABLE	0x00FE603CL	/*  1RW	1 disables Interrupts */
#define V_END_SYNC	0x00FE6040L	/*  4RW	Vertical End Sync count */
#define V_START_BLANK	0x00FE6044L	/* 10RW	Vertical Start Blank count */
#define V_TOTAL		0x00FE6048L	/* 10RW	Vertical Total count */
#define H_END_SYNC	0x00FE604CL	/*  9RW	Horizontal End Sync count */
#define H_END_BLANK	0x00FE6050L	/*  9RW	Horizontal End Blank count */
#define H_START_BLANK	0x00FE6054L	/*  9RW	Horizontal Start Blank count */
#define H_TOTAL		0x00FE6058L	/*  9RW	Horizontal Total count */
#define H_HALF_LINE	0x00FE605CL	/*  9RW	Horizontal Halfline count */
#define V_END_BLANK	0x00FE6060L	/*  6RW	Vertical End Blank count */
#define BLOCK_ENABLE	0x00FE6064L	/*  7RW	Enables Block Mode */
					/*    6 - En Syn Out  */
					/*    5 - Tri Mem     */
					/*    4 - En Option   */
					/*    3 - Xtra Rom    */
					/*    2 - YZ Mode (1) */
					/*    1 - YZ Mode (0) */
					/*    0 - BTEST       */
#define XCASTAP		0x00FE6078L	/*  9RW	Column Address during transfer cycles */
#define YPANTAP		0x00FE607CL	/*  9RW	Row Address counter reload value */
/* PAGE_CTL = 0 */
#define bt473		0x00FE7000L	/* BT473 base address */
#define bt473_p_addr	0x00FE7000L	/* BT473 Palette Address register (write) */
#define bt473_palette	0x00FE7004L	/* BT473 Palette Data register */
#define bt473_mask	0x00FE7008L	/* BT473 Read Mask register */
#define bt473_o_addr	0x00FE7010L	/* BT473 Overlay Address register (write) */
#define bt473_overlay	0x00FE7014L	/* BT473 Overlay Data register */
#define bt473_command	0x00FE7018L	/* BT473 Command register */
					/* 0011 00xx = 24 Bit */
					/* 0011 10xx = 1-8 Bit */
					/* 0011 xx00 = 1x Zoom */
					/* 0011 xx01 = 2x Zoom */
					/* 0011 xx10 = 4x Zoom */
					/* 0011 xx11 = 8x Zoom */
/* PAGE_CTL = 1 */
  /* Not Used */
/* PAGE_CTL = 2 */
#define pip_x_start	0x00FE7000L	/* Pip X - Start register */
#define pip_y_start	0x00FE7004L	/* Pip Y - Start register */
#define pip_y_end	0x00FE7008L	/* Pip Y - End register */
#define pip_x_end	0x00FE700CL	/* Pip X - End register */
#define pip_x_size	0x00FE7010L	/* Pip X - Size register */
#define pip_y_size	0x00FE701CL	/* Pip Y - Size register */
#define pip_x_end_address	0x00FE7014L	/* Pip X - End Address register (Don't read right!) */
#define pip_y_end_address	0x00FE7018L	/* Pip Y - End Address register (Don't read right!) */
/* PAGE_CTL = 3 */
#define pip_x_address	0x00FE7000L	/* Pip X - Address register */
#define pip_holdoff	0x00FE7004L	/* Pip NuBus Holdoff register */
#define pip_control_1	0x00FE7008L	/* Pip Control register 1 */
#define pip_status_1	0x00FE7008L	/* Pip Status register 1 */
#define pip_field_swap	  0x0020		/* 1 = swap fields in the frame */
#define pip_x_mirror	  0x0010		/* 0 = mirror horizontally */
#define pip_y_mirror	  0x0008		/* 0 = mirror vertically */
#define pip_red_inhibit	  0x0004		/* 0 = stop pip writes to red */
#define pip_grn_inhibit	  0x0002		/* 0 = stop pip writes to green */
#define pip_blu_inhibit	  0x0001		/* 0 = stop pip writes to blue */
#define pip_y_address	0x00FE700CL	/* Pip Y - Address register */
#define pip_control_2	0x00FE7010L	/* Pip Control register 2 */
#define pip_status_2	0x00FE7010L	/* Pip Status register 2 */
#define pip_skip_type	  0x0200		/* 1 = ???? */
#define pip_overide	  0x0100		/* 1 = shut off pip video immediately */
#define pip_connected	  0x0080		/* 1 = input device connected */
#define pip_genlock	  0x0040		/* 0 = genlock device connected */
#define pip_go		  0x0020		/* 1 = pip video on */
#define pip_oneshot	  0x0004		/* 0 = one shot enabled */
#define pip_half_speed	  0x0002		/* 0 = 15 frames/sec */
#define pip_active	  0x0001		/* 1 = pip video active */
#define pip_control_3	0x00FE7014L	/* Pip Control register 3 */
#define pip_status_3	0x00FE7014L	/* Pip Status register 3 */
#define pip_ntsc_out	  0x0020		/* 1 = ntsc if gdc and if osc select = 1 */
#define pip_dmsd_reset	  0x0010		/* 0 = reset DMSD chip set */
#define pip_y_window	  0x0008		/* 1 = Y window active */
#define pip_y_window_bit  bit3
#define pip_x_window	  0x0004		/* 1 = X window active */
#define pip_x_window_bit  bit2
#define pip_compress	  0x0002		/* 1 = pip source from daughter card */
#define pip_compress_bit1
#define pip_vlut_bypass	  0x0001		/* 1 = use SAA7192 tables */
#define pip_vlut_bypass_bit  bit0
#define AUDIO_CONTROL		0x00FE7018L	/* audio Control */
#define pip_i2c		0x00FE701CL	/* I2C Control */
#define pip_i2c_clock	  2			/* SCL - Serial Clock */
#define pip_i2c_data	  1			/* SDA - Serial Data */
#define saa7191		  0x0045		/* SAA7191 - Serial address */
#define saa7192		  0x0070		/* SAA7192 - Serial address */
#if MAKING364PAL
 #define	pip_x_start_offset	6	/* For PAL version, the real X start is 6 past register value which is now X reload */
 #define	min_X_start	0x0088		/* 136 */
 #define	max_X_end	0x0388		/* 904 */
 #define	max_X_lines	654		/* Max lines that can be digitized */
 #define	min_Y_start	0x0004		/* 4 (8) */
 #define	max_Y_end	0x012C		/* 300 (600) */
 #define	max_Y_lines	510		/* Max lines that can be digitized */
#else
 #define	min_X_start	0x0065		/* 101 */
 #define	max_X_end	0x02F3		/* 755 */
 #define	min_Y_start	0x0001		/* 1 (2) */
 #define	max_Y_end	0x00FB		/* 251 (502) */
#endif
 #define	max_holdoff	0x00E0		/* 224 */
#define	page0	0
#define	page1	1
#define	page2	2
#define	page3	3
#define	bit0	0
#define	bit1	1
#define	bit2	2
#define	bit3	3
#define	bit4	4
#define	bit5	5
#define	bit6	6
#define	bit7	7
#define SCREEN_OFFSET	0		/* Offset to beginning of screen */
#asm
CMODE		EQU	$00FE6004	; 3RW	000(0) 1 Bit Mode
OSC_SEL		EQU	$00FE600C	; Oscillator select 0 = 60hz, 1 = 30hz
NMRQ		EQU	$00FE6010	;  1RW	Interrupt Request
NMRQ_CLR	EQU	$00FE6014	;  1C	Interrupt Request Clear
PAGE_CTL	EQU	$00FE6018	;  2RW	PAGE control 0 = DAC, 1 = ADC, 2 = PIP Regs */
DISPLAY_ENABLE	EQU	$00FE601C	;  1RW	0 forces blanked display
EXT_SYNC_ENABLE	EQU	$00FE6020	;  1RW	1 enables External sync
FAT_SLOT	EQU	$00FE6024	;  1RW	0 = skinny, 1 = fat slot decoding
MON_TYPE	EQU	$00FE6028	;  3R 	monitor present/type/option
SYNC_ENABLE	EQU	$00FE602C	;  1RW	1 enables sync
TRANS_ENABLE	EQU	$00FE6030	;  1RW	1 enables transfer cycles
V_COUNT_END	EQU	$00FE6034	;  1R 	1 if vertical count matches vertical total
VID_RESET	EQU	$00FE6038	;  1RW	1 holds all video counters reset
NMRQ_DISABLE	EQU	$00FE603C	;  1RW	1 disables Interrupts
V_END_SYNC	EQU	$00FE6040	;  4RW	Vertical End Sync count
V_START_BLANK	EQU	$00FE6044	; 10RW	Vertical Start Blank count
V_TOTAL		EQU	$00FE6048	; 10RW	Vertical Total count
H_END_SYNC	EQU	$00FE604C	;  9RW	Horizontal End Sync count
H_END_BLANK	EQU	$00FE6050	;  9RW	Horizontal End Blank count
H_START_BLANK	EQU	$00FE6054	;  9RW	Horizontal Start Blank count
H_TOTAL		EQU	$00FE6058	;  9RW	Horizontal Total count
H_HALF_LINE	EQU	$00FE605C	;  9RW	Horizontal Halfline count
V_END_BLANK	EQU	$00FE6060	;  6RW	Vertical End Blank count
BLOCK_ENABLE	EQU	$00FE6064	;  1RW	Enables Block Mode
XCASTAP		EQU	$00FE6078	;  9RW	Column Address during transfer cycles */
YPANTAP		EQU	$00FE607C	;  9RW	Row Address counter reload value */
SCREEN_OFFSET	EQU	$0		;Offset to beginning of screen
pip_status_2	EQU	$00FE7010	; Pip Status register 2
AUDIO_CONTROL	EQU	$00FE7018	; audio control register
#endasm
#asm
;2345678901234567890123456789012345678901234567890123456789012345678901234567890
#endasm
/*__________________________________________________________________________________________________*/
/* sResource Directory */
#asm
    public  directory
directory
    OSLstEntry  1,boardsreslist       ; Board sResource List Offset
    ; Skinny slot frame buffer ( 32-bit Quickdraw not required)
    OSLstEntry  $80,mysreslist80        ; My sResource List Offset - 640 X 480
    OSLstEntry  $81,mysreslist81        ; My sResource List Offset - 640 X 480
    OSLstEntry  $82,mysreslist82        ; My sResource List Offset - 576 X 432
    OSLstEntry  $83,mysreslist83        ; My sResource List Offset - 576 X 432
    OSLstEntry  $84,mysreslist84        ; My sResource List Offset - 1008 X 512
    OSLstEntry  $85,mysreslist85        ; My sResource List Offset - 1008 X 512
    OSLstEntry  $86,mysreslist86        ; My sResource List Offset - 2032 X 512
    OSLstEntry  $87,mysreslist87        ; My sResource List Offset - 2032 X 512
 
    ; Fat slot frame buffer ( 32-bit Quickdraw required)
    OSLstEntry  $90,mysreslist90        ; My sResource List Offset - 640 X 480
    OSLstEntry  $91,mysreslist91        ; My sResource List Offset - 640 X 480
    OSLstEntry  $92,mysreslist92        ; My sResource List Offset - 576 X 432
    OSLstEntry  $93,mysreslist93        ; My sResource List Offset - 576 X 432
    OSLstEntry  $94,mysreslist94        ; My sResource List Offset - 1008 X 512
    OSLstEntry  $95,mysreslist95        ; My sResource List Offset - 1008 X 512
    OSLstEntry  $96,mysreslist96        ; My sResource List Offset - 2032 X 512
    OSLstEntry  $97,mysreslist97        ; My sResource List Offset - 2032 X 512
 
    DatLstEntry $FF,0                   ; End
#endasm
/*__________________________________________________________________________________________________*/
/* Board sResource List */
#asm
boardsreslist
	OSLstEntry	1,boardtype		; Board sResource Type Format Offset
	OSLstEntry	2,boardname		; Board sResource Name Offset
 if MAKINGROPS
	OSLstEntry	16,boardicon		; Board sResource Icon Offset
 endc
	OSLstEntry	20,boardBTInfo		; Board sResource block transfer info Offset
	DatLstEntry	$20,CB24MTVBoardId	; Board ID assigned by Apple
	OSLstEntry	$22,primaryinit		; Primary Initialization Code seBlock Offset
	OSLstEntry	$24,vendorinfo		; Vendor Info List Offset
	OSLstEntry	$26,secondaryinit	; Secondary Initialization Code seBlock Offset ????
	OSLstEntry  $41,modenamesdir	; Video family mode names
 	DatLstEntry	$FF,0			; End
#endasm
/*__________________________________________________________________________________________________*/
/* Block Transfer Info */
#asm
boardBTInfo	even
	DC.L	allSlaveBlockSizes
#endasm
/*__________________________________________________________________________________________________*/
/* Video family mode names directory */
#asm
modenamesdir
	OSLstEntry	$80,s640x480n
	OSLstEntry	$81,s640x480p
	OSLstEntry	$82,s556x416n
	OSLstEntry	$83,s556x416p
	OSLstEntry	$84,s1008x512n		; 1008 x 512 Extended Desktop
	OSLstEntry	$85,s1008x512p		; 1008 x 512 Extended Desktop
	OSLstEntry	$86,s2032x512n		; 2032 x 512 Extended Desktop
	OSLstEntry	$87,s2032x512p		; 2032 x 512 Extended Desktop
	
	OSLstEntry	$90,f640x480n
	OSLstEntry	$91,f640x480p
	OSLstEntry	$92,f556x416n
	OSLstEntry	$93,f556x416p
	OSLstEntry	$94,f1008x512n		; 1008 x 512 Extended Desktop
	OSLstEntry	$95,f1008x512p		; 1008 x 512 Extended Desktop
	OSLstEntry	$96,f2032x512n		; 2032 x 512 Extended Desktop
	OSLstEntry	$97,f2032x512p		; 2032 x 512 Extended Desktop
	DatLstEntry	$FF,0			; End
#endasm
#asm
s640x480n even
	DC.L ends640x480n-s640x480n
	DC.W $80
	DC.B '640 X 480 (NTSC)'
	DC.W 0
ends640x480n
s640x480p even
	DC.L ends640x480p-s640x480p
	DC.W $81
	DC.B '640 X 480 (PAL)'
	DC.W 0
ends640x480p
s556x416n even
	DC.L ends556x416n-s556x416n
	DC.W $82
	DC.B '576 X 432 (NTSC)'
	DC.W 0
ends556x416n
s556x416p even
	DC.L ends556x416p-s556x416p
	DC.W $83
	DC.B '576 X 432 (PAL)'
	DC.W 0
ends556x416p
s1008x512n even
	DC.L ends1008x512n-s1008x512n
	DC.W $84
	DC.B '1008 X 512 Extended (NTSC)'
	DC.W 0
ends1008x512n
s1008x512p even
	DC.L ends1008x512p-s1008x512p
	DC.W $85
	DC.B '1008 X 512 Extended (PAL)'
	DC.W 0
ends1008x512p
s2032x512n even
	DC.L ends2032x512n-s2032x512n
	DC.W $86
	DC.B '2032 X 512 Extended (NTSC)'
	DC.W 0
ends2032x512n
s2032x512p even
	DC.L ends2032x512p-s2032x512p
	DC.W $87
	DC.B '2032 X 512 Extended (PAL)'
	DC.W 0
ends2032x512p
f640x480n even
	DC.L endf640x480n-f640x480n
	DC.W $90
	DC.B '640 X 480 (NTSC)'
	DC.W 0
endf640x480n
f640x480p even
	DC.L endf640x480p-f640x480p
	DC.W $91
	DC.B '640 X 480 (PAL)'
	DC.W 0
endf640x480p
f556x416n even
	DC.L endf556x416n-f556x416n
	DC.W $92
	DC.B '576 X 432 (NTSC)'
	DC.W 0
endf556x416n
f556x416p even
	DC.L endf556x416p-f556x416p
	DC.W $93
	DC.B '576 X 432 (PAL)'
	DC.W 0
endf556x416p
f1008x512n even
	DC.L endf1008x512n-f1008x512n
	DC.W $94
	DC.B '1008 X 512 Extended (NTSC)'
	DC.W 0
endf1008x512n
f1008x512p even
	DC.L endf1008x512p-f1008x512p
	DC.W $95
	DC.B '1008 X 512 Extended (PAL)'
	DC.W 0
endf1008x512p
f2032x512n even
	DC.L endf2032x512n-f2032x512n
	DC.W $96
	DC.B '2032 X 512 Extended (NTSC)'
	DC.W 0
endf2032x512n
f2032x512p even
	DC.L endf2032x512p-f2032x512p
	DC.W $97
	DC.B '2032 X 512 Extended (PAL)'
	DC.W 0
endf2032x512p
#endasm
 
/*__________________________________________________________________________________________________*/
/* Board sResource Type Format */
#asm
boardtype
    dc.w  1        ; Category: Board
    dc.w  0        ; Type:     Board
    dc.w  0        ; 0 for Board
    dc.w  0        ; 0 for Board
#endasm
/*__________________________________________________________________________________________________*/
/* Board sResource Name */
#if MAKINGRGB
#asm
boardname		; Official Product Name
	dc.b	'ImageBoss 2000'
	dc.w	0	; For Alignment
#endasm
#endif
#if MAKINGROPS
#asm
boardname		; Official Product Name
	dc.b	'RasterOps MediaTime'
	dc.w	0	; For Alignment
#endasm
#endif
#if MAKINGTV
#asm
boardname		; Official Product Name
	dc.b	'Truevision Bravado24'
	dc.w	0	; For Alignment
#endasm
#endif
/*__________________________________________________________________________________________________*/
/* Board sResource Icon */
#if MAKINGROPS
#asm
boardicon
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$6d,$6d,$6d
    DC.B $6d,$6d,$6d,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$6d
    DC.B $6d,$6d,$6d,$6d,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d
    DC.B $6d,$6d,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d
    DC.B $6d,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d
    DC.B $6d,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff
    DC.B $ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff
    DC.B $ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$6d,$6d,$6d
    DC.B $6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$6d,$6d,$6d
    DC.B $6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff
    DC.B $6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff
    DC.B $6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff
    DC.B $ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff
    DC.B $ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$6d,$6d,$6d,$6d,$6d,$6d,$6d,$6d,$6d,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
    DC.B $ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff,$ff
#endasm
#endif
/* Vendor Info List */
#asm
vendorinfo
    OSLstEntry  1,vendordesign    	; Vendor Design ID Offset
    OSLstEntry  3,cardrevision    	; Card's Revision Level Offset
    OSLstEntry  4,cardpartnumber  	; Card Part Number Offset
    OSLstEntry  5,cardrevisiondate	; Card Revision Date
    DatLstEntry $FF,0             	; End
#endasm
/* Actual Vendor Info */
#if MAKINGRGB
#asm
vendordesign
    dc.b  'RGB Technology'
    dc.w  0            ; For Alignment
cardrevision
    dc.b  'ROM Version: 1.2 PZE'
    dc.w  0            ; For Alignment
cardpartnumber
    dc.b  'ImageBoss 2000'
    dc.w  0            ; For Alignment
cardrevisiondate
    dc.b  'July 29, 1991'
    dc.w  0	       ; For Alignment
#endasm
#endif
#if MAKINGTV
#asm
vendordesign
    dc.b  'Truevision'
    dc.w  0            ; For Alignment
cardrevision
    dc.b  'ROM Version: 1.2 PZE'
    dc.w  0            ; For Alignment
cardpartnumber
    dc.b  'Bravado24'
    dc.w  0            ; For Alignment
cardrevisiondate
    dc.b  'Oct 29, 1992'
    dc.w  0	       ; For Alignment
#endasm
#endif
#if MAKINGROPS
#asm
vendordesign
    dc.b  'RasterOps'
    dc.w  0            ; For Alignment
cardrevision
    dc.b  'ROM Version: 1.2 PZE'
    dc.w  0            ; For Alignment
	if MAKINGVERB
cardpartnumber
		dc.b  'MediaTimeb'		; non-square pixel version (pip)
		dc.w  0				; For Alignment
	else
cardpartnumber
		dc.b  'MediaTime'
		dc.w  0				; For Alignment
	endc
cardrevisiondate
    dc.b  'July 29, 1991'
    dc.w  0	       ; For Alignment
#endasm
#endif
/* My sResource List 80 */
#asm
    even
mysreslist80
mysreslist81
    OSLstEntry80  1,mytype            ; My sResource Type Format Offset
    OSLstEntry80  2,myname            ; My sResource Name Offset
    OSLstEntry80  4,mydrvrdir         ; My sResource Driver Directory Offset
    DatLstEntry   8,1                 ; sRsrcHWDevId = 1
    OSLstEntry80  $A,minorbase        ; MinorBase Offset
    OSLstEntry80  $B,minorlen8         ; MinorLength Offset
;    OSLstEntry80  $40,gammadirectory   ; Gamma correction table directory ????
    OSLstEntry80  $80,bits1parmlist   ; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry80  $81,bits2parmlist   ; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry80  $82,bits4parmlist   ; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry80  $83,bits8parmlist   ; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               ; End
#endasm
/* My sResource List 82 */
#asm
    even
mysreslist82
mysreslist83
    OSLstEntry82  1,mytype            ; My sResource Type Format Offset
    OSLstEntry82  2,myname            ; My sResource Name Offset
    OSLstEntry82  4,mydrvrdir         ; My sResource Driver Directory Offset
    DatLstEntry   8,1                 ; sRsrcHWDevId = 1
    OSLstEntry82  $A,minorbase        ; MinorBase Offset
    OSLstEntry82  $B,minorlen8         ; MinorLength Offset
;    OSLstEntry82  $40,gammadirectory   ; Gamma correction table directory ????
    OSLstEntry82  $80,bits1parmlist4   ; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry82  $81,bits2parmlist4   ; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry82  $82,bits4parmlist4   ; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry82  $83,bits8parmlist4   ; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               ; End
#endasm
/* PZ */
/* My sResource List 84 */
#asm
    even
mysreslist84
mysreslist85
    OSLstEntry84  1,mytype            ; My sResource Type Format Offset
    OSLstEntry84  2,myname            ; My sResource Name Offset
    OSLstEntry84  4,mydrvrdir         ; My sResource Driver Directory Offset
    DatLstEntry   8,1                 ; sRsrcHWDevId = 1
    OSLstEntry84  $A,minorbase        ; MinorBase Offset
    OSLstEntry84  $B,minorlen8         ; MinorLength Offset
;    OSLstEntry84  $40,gammadirectory   ; Gamma correction table directory ????
    OSLstEntry84  $80,bits1parmlist1   ; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry84  $81,bits2parmlist1   ; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry84  $82,bits4parmlist1   ; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry84  $83,bits8parmlist1   ; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               ; End
#endasm
/* My sResource List 86 */
#asm
    even
mysreslist86
mysreslist87
    OSLstEntry86  1,mytype            ; My sResource Type Format Offset
    OSLstEntry86  2,myname            ; My sResource Name Offset
    OSLstEntry86  4,mydrvrdir         ; My sResource Driver Directory Offset
    DatLstEntry   8,1                 ; sRsrcHWDevId = 1
    OSLstEntry86  $A,minorbase        ; MinorBase Offset
    OSLstEntry86  $B,minorlen8         ; MinorLength Offset
;    OSLstEntry86  $40,gammadirectory   ; Gamma correction table directory ????
    OSLstEntry86  $80,bits1parmlist2   ; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry86  $81,bits2parmlist2   ; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry86  $82,bits4parmlist2   ; Four-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               ; End
#endasm
/* My sResource List 90 */
#asm
    even
mysreslist90
mysreslist91
    OSLstEntry90  1,mytype            ; My sResource Type Format Offset
    OSLstEntry90  2,myname            ; My sResource Name Offset
    OSLstEntry90  4,mydrvrdir         ; My sResource Driver Directory Offset
    DatLstEntry   7,6                 ; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 ; sRsrcHWDevId = 1
    OSLstEntry90  $A,minorbase        ; MinorBase Offset
    OSLstEntry90  $B,minorlen9         ; MinorLength Offset
;    OSLstEntry90  $40,gammadirectory   ; Gamma correction table directory ????
    OSLstEntry90  $80,bits1parmlist   ; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry90  $81,bits2parmlist   ; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry90  $82,bits4parmlist   ; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry90  $83,bits8parmlist   ; Eight-Bit-Per-Pixel Parameter List Offset
    OSLstEntry90  $84,bits24parmlist  ; Twenty-Four-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               ; End
#endasm
/* My sResource List 92 */
#asm
    even
mysreslist92
mysreslist93
    OSLstEntry92  1,mytype            ; My sResource Type Format Offset
    OSLstEntry92  2,myname            ; My sResource Name Offset
    OSLstEntry92  4,mydrvrdir         ; My sResource Driver Directory Offset
    DatLstEntry   7,6                 ; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 ; sRsrcHWDevId = 1
    OSLstEntry92  $A,minorbase        ; MinorBase Offset
    OSLstEntry92  $B,minorlen9         ; MinorLength Offset
;    OSLstEntry92  $40,gammadirectory   ; Gamma correction table directory ????
    OSLstEntry92  $80,bits1parmlist4   ; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry92  $81,bits2parmlist4   ; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry92  $82,bits4parmlist4   ; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry92  $83,bits8parmlist4   ; Eight-Bit-Per-Pixel Parameter List Offset
    OSLstEntry92  $84,bits24parmlist4  ; Twenty-Four-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               ; End
#endasm
/* Extended Desktop */
/* My sResource List 94  1008 X 512 */
#asm
    even
mysreslist94
mysreslist95
    OSLstEntry94  1,mytype            ; My sResource Type Format Offset
    OSLstEntry94  2,myname            ; My sResource Name Offset
    OSLstEntry94  4,mydrvrdir         ; My sResource Driver Directory Offset
    DatLstEntry   7,6                 ; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 ; sRsrcHWDevId = 1
    OSLstEntry94  $A,minorbase        ; MinorBase Offset
    OSLstEntry94  $B,minorlen9         ; MinorLength Offset
;    OSLstEntry94  $40,gammadirectory   ; Gamma correction table directory ????
    OSLstEntry94  $80,bits1parmlist1   ; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry94  $81,bits2parmlist1   ; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry94  $82,bits4parmlist1   ; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry94  $83,bits8parmlist1   ; Eight-Bit-Per-Pixel Parameter List Offset
    OSLstEntry94  $84,bits24parmlist1  ; Twenty-Four-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               ; End
#endasm
/* My sResource List 96  2032 X 512 */
#asm
    even
mysreslist96
mysreslist97
    OSLstEntry96  1,mytype            ; My sResource Type Format Offset
    OSLstEntry96  2,myname            ; My sResource Name Offset
    OSLstEntry96  4,mydrvrdir         ; My sResource Driver Directory Offset
    DatLstEntry   7,6                 ; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 ; sRsrcHWDevId = 1
    OSLstEntry96  $A,minorbase        ; MinorBase Offset
    OSLstEntry96  $B,minorlen9         ; MinorLength Offset
;    OSLstEntry96  $40,gammadirectory   ; Gamma correction table directory ????
    OSLstEntry96  $80,bits1parmlist2   ; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry96  $81,bits2parmlist2   ; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry96  $82,bits4parmlist2   ; Four-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               ; End
#endasm
/* My sResource Type Format */
#asm
    even
mytype
	dc.w	CatDisplay		; Category:  catDisplay
	dc.w	TypVideo		; Type:      typVideo
	dc.w	DrSwApple		; DrvrSw:    drSwApple
	dc.w	DrHwRasterOps24MTV	; DrvrHw:    RasterOps 24MTV
#endasm
/* My sResource Name */
#if MAKINGTV
#asm
myname
    dc.b  'Display_Video_Apple_TruevisionBravado24'
    dc.w  0        ; For Alignment
#endasm
#else
#asm
myname
    dc.b  'Display_Video_Apple_RasterOpsMediaTime'
    dc.w  0        ; For Alignment
#endasm
#endif
/* MinorBase */
#asm
minorbase
    dc.l  0        ; No offset from normal beginning of slot space
#endasm
/* MinorLength for Skinny Slots */
#asm
minorlen8
    dc.l  512*1024   ; 512K of Video RAM	????
#endasm
/* MinorLength for Fat Slots */
#asm
minorlen9
    dc.l  512*1024*4   ; 2M of Video RAM	????
#endasm
/*-----------------------*/
/* sVideo Resources */
/*-----------------------*/
/* One-Bit-Per-Pixel Parameter List */
#asm
bits1parmlist
    OSLstEntry  1,bits1parms     ; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              ; Number of Pages: 1
    DatLstEntry 4,0              ; Device Type: 0
    DatLstEntry $FF,0            ; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bits1parms
    dc.l  endbits1parms-bits1parms  ; Length of sBlock
    dc.l  SCREEN_OFFSET             ; Offset to Page 0 of Video RAM: 
    dc.w  $400                      ; RowBytes 1024
    dc.l  0                         ; BoundsRect: (0,0,480,640)
    dc.l  $01E00280                 ;
    dc.w  0                         ; PixMap Version Number
    dc.w  0                         ; unused
    dc.l  0                         ; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 ; Horizontal Res
    dc.l  $00480000                 ; Vertical Res
    dc.w  0                         ; Pixel Type (0=Chunky)
    dc.w  1                         ; Pixel Size
    dc.w  1                         ; Components in Pixel
    dc.w  1                         ; Bits Per Component
    dc.l  0                         ; PlaneBytes Offset
endbits1parms
#endasm
/* Two-Bit-Per-Pixel Parameter List */
#asm
bits2parmlist
    OSLstEntry  1,bits2parms     ; Two-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              ; Number of Pages: 1
    DatLstEntry 4,0              ; Device Type: 0
    DatLstEntry $FF,0            ; End
#endasm
/* Two-Bit-Per-Pixel Parameters sBlock */
#asm
bits2parms
    dc.l  endbits2parms-bits2parms  ; Length of sBlock
    dc.l  SCREEN_OFFSET             ; Offset to Page 0 of Video RAM: 
    dc.w  $400                      ; RowBytes 1024
    dc.l  0                         ; BoundsRect: (0,0,480,640)
    dc.l  $01E00280                 ;
    dc.w  0                         ; PixMap Version Number
    dc.w  0                         ; unused
    dc.l  0                         ; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 ; Horizontal Res
    dc.l  $00480000                 ; Vertical Res
    dc.w  0                         ; Pixel Type (0=Chunky)
    dc.w  2                         ; Pixel Size
    dc.w  1                         ; Components in Pixel
    dc.w  2                         ; Bits Per Component
    dc.l  0                         ; PlaneBytes Offset
endbits2parms
#endasm
/* Four-Bit-Per-Pixel Parameter List */
#asm
bits4parmlist
    OSLstEntry  1,bits4parms     ; Four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              ; Number of Pages: 1
    DatLstEntry 4,0              ; Device Type: 0
    DatLstEntry $FF,0            ; End
#endasm
/* Four-Bit-Per-Pixel Parameters sBlock */
#asm
bits4parms
    dc.l  endbits4parms-bits4parms  ; Length of sBlock
    dc.l  SCREEN_OFFSET             ; Offset to Page 0 of Video RAM: 
    dc.w  $400                      ; RowBytes 1024
    dc.l  0                         ; BoundsRect: (0,0,480,640)
    dc.l  $01E00280                 ;
    dc.w  0                         ; PixMap Version Number
    dc.w  0                         ; unused
    dc.l  0                         ; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 ; Horizontal Res
    dc.l  $00480000                 ; Vertical Res
    dc.w  0                         ; Pixel Type (0=Chunky)
    dc.w  4                         ; Pixel Size
    dc.w  1                         ; Components in Pixel
    dc.w  4                         ; Bits Per Component
    dc.l  0                         ; PlaneBytes Offset
endbits4parms
#endasm
/* Eight-Bit-Per-Pixel Parameter List */
#asm
bits8parmlist
    OSLstEntry  1,bits8parms    ; Eight-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              ; Number of Pages: 1
    DatLstEntry 4,0              ; Device Type: 0
    DatLstEntry $FF,0            ; End
#endasm
/* Eight-Bit-Per-Pixel Parameters sBlock */
#asm
bits8parms
    dc.l  endbits8parms-bits8parms  ; Length of sBlock
    dc.l  SCREEN_OFFSET             ; Offset to Page 0 of Video RAM: 
    dc.w  $400                      ; RowBytes 1024
    dc.l  0                         ; BoundsRect: (0,0,480,640)
    dc.l  $01E00280                 ;
    dc.w  0                         ; PixMap Version Number
    dc.w  0                         ; unused
    dc.l  0                         ; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 ; Horizontal Res
    dc.l  $00480000                 ; Vertical Res
    dc.w  0                         ; Pixel Type (0=Chunky)
    dc.w  8                         ; Pixel Size
    dc.w  1                         ; Components in Pixel
    dc.w  8                         ; Bits Per Component
    dc.l  0                         ; PlaneBytes Offset
endbits8parms
#endasm
/* Twenty-four-Bit-Per-Pixel Parameter List */
#asm
bits24parmlist
    OSLstEntry  1,bits24parms    ; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              ; Number of Pages: 1
    DatLstEntry 4,2              ; Device Type: 2 - DirectType
    DatLstEntry $FF,0            ; End
#endasm
/* Twenty-four-Bit-Per-Pixel Parameters sBlock */
#asm
bits24parms
    dc.l  endbits24parms-bits24parms  ; Length of sBlock
    dc.l  SCREEN_OFFSET             ; Offset to Page 0 of Video RAM: 
    dc.w  $1000                     ; RowBytes 4096
    dc.l  0                         ; BoundsRect: (0,0,480,640)
    dc.l  $01E00280                 ;
    dc.w  0                         ; PixMap Version Number
    dc.w  0                         ; unused
    dc.l  0                         ; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 ; Horizontal Res
    dc.l  $00480000                 ; Vertical Res
    dc.w  $10                       ; Pixel Type ($10=ChunkyDirect)
    dc.w  32                        ; Pixel Size (must be power of 2)
    dc.w  3                         ; Components in Pixel
    dc.w  8                         ; Bits Per Component
    dc.l  0                         ; PlaneBytes Offset
endbits24parms
#endasm
/* PZ */
/*-------------------------------------------------------*/
/* sVideo Resources for Extended Desktop 1008 X 512 */
/*-------------------------------------------------------*/
/* One-Bit-Per-Pixel Parameter List */
#asm
bits1parmlist1
    OSLstEntry  1,bits1parms1     ; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              ; Number of Pages: 1
    DatLstEntry 4,0              ; Device Type: 0
    DatLstEntry $FF,0            ; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bits1parms1
    dc.l  endbits1parms1-bits1parms1  ; Length of sBlock
    dc.l  SCREEN_OFFSET             ; Offset to Page 0 of Video RAM: 
    dc.w  $400                      ; RowBytes 1024
    dc.l  0                         ; BoundsRect: (0,0,512,1008)
    dc.l  $020003f0                 ;
    dc.w  0                         ; PixMap Version Number
    dc.w  0                         ; unused
    dc.l  0                         ; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 ; Horizontal Res
    dc.l  $00480000                 ; Vertical Res
    dc.w  0                         ; Pixel Type (0=Chunky)
    dc.w  1                         ; Pixel Size
    dc.w  1                         ; Components in Pixel
    dc.w  1                         ; Bits Per Component
    dc.l  0                         ; PlaneBytes Offset
endbits1parms1
#endasm
/* Two-Bit-Per-Pixel Parameter List */
#asm
bits2parmlist1
    OSLstEntry  1,bits2parms1     ; Two-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              ; Number of Pages: 1
    DatLstEntry 4,0              ; Device Type: 0
    DatLstEntry $FF,0            ; End
#endasm
/* Two-Bit-Per-Pixel Parameters sBlock */
#asm
bits2parms1
    dc.l  endbits2parms1-bits2parms1  ; Length of sBlock
    dc.l  SCREEN_OFFSET             ; Offset to Page 0 of Video RAM: 
    dc.w  $400                      ; RowBytes 1024
    dc.l  0                         ; BoundsRect: (0,0,512,1008)
    dc.l  $020003f0                 ;
    dc.w  0                         ; PixMap Version Number
    dc.w  0                         ; unused
    dc.l  0                         ; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 ; Horizontal Res
    dc.l  $00480000                 ; Vertical Res
    dc.w  0                         ; Pixel Type (0=Chunky)
    dc.w  2                         ; Pixel Size
    dc.w  1                         ; Components in Pixel
    dc.w  2                         ; Bits Per Component
    dc.l  0                         ; PlaneBytes Offset
endbits2parms1
#endasm
/* Four-Bit-Per-Pixel Parameter List */
#asm
bits4parmlist1
    OSLstEntry  1,bits4parms1     ; Four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              ; Number of Pages: 1
    DatLstEntry 4,0              ; Device Type: 0
    DatLstEntry $FF,0            ; End
#endasm
/* Four-Bit-Per-Pixel Parameters sBlock */
#asm
bits4parms1
    dc.l  endbits4parms1-bits4parms1  ; Length of sBlock
    dc.l  SCREEN_OFFSET             ; Offset to Page 0 of Video RAM: 
    dc.w  $400                      ; RowBytes 1024
    dc.l  0                         ; BoundsRect: (0,0,512,1008)
    dc.l  $020003f0                 ;
    dc.w  0                         ; PixMap Version Number
    dc.w  0                         ; unused
    dc.l  0                         ; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 ; Horizontal Res
    dc.l  $00480000                 ; Vertical Res
    dc.w  0                         ; Pixel Type (0=Chunky)
    dc.w  4                         ; Pixel Size
    dc.w  1                         ; Components in Pixel
    dc.w  4                         ; Bits Per Component
    dc.l  0                         ; PlaneBytes Offset
endbits4parms1
#endasm
/* Eight-Bit-Per-Pixel Parameter List */
#asm
bits8parmlist1
    OSLstEntry  1,bits8parms1    ; Eight-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              ; Number of Pages: 1
    DatLstEntry 4,0              ; Device Type: 0
    DatLstEntry $FF,0            ; End
#endasm
/* Eight-Bit-Per-Pixel Parameters sBlock */
#asm
bits8parms1
    dc.l  endbits8parms1-bits8parms1  ; Length of sBlock
    dc.l  SCREEN_OFFSET             ; Offset to Page 0 of Video RAM: 
    dc.w  $400                      ; RowBytes 1024
    dc.l  0                         ; BoundsRect: (0,0,512,1008)
    dc.l  $020003f0                 ;
    dc.w  0                         ; PixMap Version Number
    dc.w  0                         ; unused
    dc.l  0                         ; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 ; Horizontal Res
    dc.l  $00480000                 ; Vertical Res
    dc.w  0                         ; Pixel Type (0=Chunky)
    dc.w  8                         ; Pixel Size
    dc.w  1                         ; Components in Pixel
    dc.w  8                         ; Bits Per Component
    dc.l  0                         ; PlaneBytes Offset
endbits8parms1
#endasm
/* Twenty-four-Bit-Per-Pixel Parameter List */
#asm
bits24parmlist1
    OSLstEntry  1,bits24parms1   ; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              ; Number of Pages: 1
    DatLstEntry 4,2              ; Device Type: 2 - DirectType
    DatLstEntry $FF,0            ; End
#endasm
/* Twenty-four-Bit-Per-Pixel Parameters sBlock */
#asm
bits24parms1
    dc.l  endbits24parms1-bits24parms1  ; Length of sBlock
    dc.l  SCREEN_OFFSET             ; Offset to Page 0 of Video RAM: 
    dc.w  $1000                     ; RowBytes 4096
    dc.l  0                         ; BoundsRect: (0,0,512,1008)
    dc.l  $020003f0                 ;
    dc.w  0                         ; PixMap Version Number
    dc.w  0                         ; unused
    dc.l  0                         ; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 ; Horizontal Res
    dc.l  $00480000                 ; Vertical Res
    dc.w  $10                       ; Pixel Type ($10=ChunkyDirect)
    dc.w  32                        ; Pixel Size (must be power of 2)
    dc.w  3                         ; Components in Pixel
    dc.w  8                         ; Bits Per Component
    dc.l  0                         ; PlaneBytes Offset
endbits24parms1
#endasm
/*-------------------------------------------------------*/
/* sVideo Resources for Extended Desktop 2032 X 512 */
/*-------------------------------------------------------*/
/* One-Bit-Per-Pixel Parameter List */
#asm
bits1parmlist2
    OSLstEntry  1,bits1parms2     ; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              ; Number of Pages: 1
    DatLstEntry 4,0              ; Device Type: 0
    DatLstEntry $FF,0            ; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bits1parms2
    dc.l  endbits1parms2-bits1parms2  ; Length of sBlock
    dc.l  SCREEN_OFFSET             ; Offset to Page 0 of Video RAM: 
    dc.w  $400                      ; RowBytes 1024
    dc.l  0                         ; BoundsRect: (0,0,512,2032)
    dc.l  $020007f0                 ;
    dc.w  0                         ; PixMap Version Number
    dc.w  0                         ; unused
    dc.l  0                         ; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 ; Horizontal Res
    dc.l  $00480000                 ; Vertical Res
    dc.w  0                         ; Pixel Type (0=Chunky)
    dc.w  1                         ; Pixel Size
    dc.w  1                         ; Components in Pixel
    dc.w  1                         ; Bits Per Component
    dc.l  0                         ; PlaneBytes Offset
endbits1parms2
#endasm
/* Two-Bit-Per-Pixel Parameter List */
#asm
bits2parmlist2
    OSLstEntry  1,bits2parms2     ; Two-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              ; Number of Pages: 1
    DatLstEntry 4,0              ; Device Type: 0
    DatLstEntry $FF,0            ; End
#endasm
/* Two-Bit-Per-Pixel Parameters sBlock */
#asm
bits2parms2
    dc.l  endbits2parms2-bits2parms2  ; Length of sBlock
    dc.l  SCREEN_OFFSET             ; Offset to Page 0 of Video RAM: 
    dc.w  $400                      ; RowBytes 1024
    dc.l  0                         ; BoundsRect: (0,0,512,2032)
    dc.l  $020007f0                 ;
    dc.w  0                         ; PixMap Version Number
    dc.w  0                         ; unused
    dc.l  0                         ; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 ; Horizontal Res
    dc.l  $00480000                 ; Vertical Res
    dc.w  0                         ; Pixel Type (0=Chunky)
    dc.w  2                         ; Pixel Size
    dc.w  1                         ; Components in Pixel
    dc.w  2                         ; Bits Per Component
    dc.l  0                         ; PlaneBytes Offset
endbits2parms2
#endasm
/* Four-Bit-Per-Pixel Parameter List */
#asm
bits4parmlist2
    OSLstEntry  1,bits4parms2     ; Four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              ; Number of Pages: 1
    DatLstEntry 4,0              ; Device Type: 0
    DatLstEntry $FF,0            ; End
#endasm
/* Four-Bit-Per-Pixel Parameters sBlock */
#asm
bits4parms2
    dc.l  endbits4parms2-bits4parms2  ; Length of sBlock
    dc.l  SCREEN_OFFSET             ; Offset to Page 0 of Video RAM: 
    dc.w  $400                      ; RowBytes 1024
    dc.l  0                         ; BoundsRect: (0,0,512,2032)
    dc.l  $020007f0                 ;
    dc.w  0                         ; PixMap Version Number
    dc.w  0                         ; unused
    dc.l  0                         ; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 ; Horizontal Res
    dc.l  $00480000                 ; Vertical Res
    dc.w  0                         ; Pixel Type (0=Chunky)
    dc.w  4                         ; Pixel Size
    dc.w  1                         ; Components in Pixel
    dc.w  4                         ; Bits Per Component
    dc.l  0                         ; PlaneBytes Offset
endbits4parms2
#endasm
/**** еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее */
/* еееееееееееееееее NTSC 576 X 432 Underscan ееееееееееееееееееее */
/* One-Bit-Per-Pixel Parameter List */
#asm
bits1parmlist4
    OSLstEntry  1,bits1parms4     		; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bits1parms4
    dc.l  endbits1parms4-bits1parms4  	; Length of sBlock
    dc.l  SCREEN_OFFSET                 ; Offset to Page 0 of Video RAM: 0
    dc.w  $400                      	; RowBytes 1024
    dc.l  0                         	; BoundsRect: (0,0,432,576)
    dc.l  $01B00240                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  0                         	; Pixel Type (0=Chunky)
    dc.w  1                         	; Pixel Size
    dc.w  1                         	; Components in Pixel
    dc.w  1                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits1parms4
#endasm
/* Two-Bit-Per-Pixel Parameter List */
#asm
bits2parmlist4
    OSLstEntry  1,bits2parms4     		; Two-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Two-Bit-Per-Pixel Parameters sBlock */
#asm
bits2parms4
    dc.l  endbits2parms4-bits2parms4  	; Length of sBlock
    dc.l  SCREEN_OFFSET               	; Offset to Page 0 of Video RAM: 0
    dc.w  $400                      	; RowBytes 1024
    dc.l  0                         	; BoundsRect: (0,0,432,576)
    dc.l  $01B00240                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  0                         	; Pixel Type (0=Chunky)
    dc.w  2                         	; Pixel Size
    dc.w  1                         	; Components in Pixel
    dc.w  2                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits2parms4
#endasm
/* Four-Bit-Per-Pixel Parameter List */
#asm
bits4parmlist4
    OSLstEntry  1,bits4parms4     		; Four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Four-Bit-Per-Pixel Parameters sBlock */
#asm
bits4parms4
    dc.l  endbits4parms4-bits4parms4  	; Length of sBlock
    dc.l  SCREEN_OFFSET                 ; Offset to Page 0 of Video RAM: 0
    dc.w  $400                      	; RowBytes 1024
    dc.l  0                         	; BoundsRect: (0,0,432,576)
    dc.l  $01B00240                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  0                         	; Pixel Type (0=Chunky)
    dc.w  4                         	; Pixel Size
    dc.w  1                         	; Components in Pixel
    dc.w  4                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits4parms4
#endasm
/* Eight-Bit-Per-Pixel Parameter List */
#asm
bits8parmlist4
    OSLstEntry  1,bits8parms4    		; Eight-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Eight-Bit-Per-Pixel Parameters sBlock */
#asm
bits8parms4
    dc.l  endbits8parms4-bits8parms4  	; Length of sBlock
    dc.l  SCREEN_OFFSET                 ; Offset to Page 0 of Video RAM: 0
    dc.w  $400                      	; RowBytes 1024
    dc.l  0                         	; BoundsRect: (0,0,432,576)
    dc.l  $01B00240                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  0                         	; Pixel Type (0=Chunky)
    dc.w  8                         	; Pixel Size
    dc.w  1                         	; Components in Pixel
    dc.w  8                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits8parms4
#endasm
/* Twenty-four-Bit-Per-Pixel Parameter List */
#asm
bits24parmlist4
    OSLstEntry  1,bits24parms4    		; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,2              		; Device Type: 2 - DirectType
    DatLstEntry $FF,0            		; End
#endasm
/* Twenty-four-Bit-Per-Pixel Parameters sBlock */
#asm
bits24parms4
    dc.l  endbits24parms4-bits24parms4  ; Length of sBlock
    dc.l  SCREEN_OFFSET                 ; Offset to Page 0 of Video RAM: 0
    dc.w  $1000                     	; RowBytes 4096
    dc.l  0                         	; BoundsRect: (0,0,432,576)
    dc.l  $01B00240                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  $10                       	; Pixel Type ($10=ChunkyDirect)
    dc.w  32                        	; Pixel Size (must be power of 2)
    dc.w  3                         	; Components in Pixel
    dc.w  8                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits24parms4
#endasm
/**** еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее */
#if WeEverWantAromTable
/*______________________________________________________________________________*/
/* My sResource Gamma Directory */
/*______________________________________________________________________________*/
#asm
gammadirectory
;    OSLstEntry  $80,mygamma         ; My ID 80 Gamma Table sBlock Offset
    OSLstEntry80  $80,applegamma      ; My ID 80 Gamma Table sBlock Offset
    OSLstEntry90  $90,applegamma      ; My ID 90 Gamma Table sBlock Offset
    DatLstEntry $FF,0               ; End
#endasm
/* My 264 Gamma sBlock */
#asm
mygamma
; ==================BEGINNING OF GAMMA BLOCK=====================
    dc.l  endmygamma-mygamma          ; Length of sBlock
#endasm
#asm
  if MAKINGTV
	DC.B	'Truevision Bravado24'	; Mode Name
  else
	DC.B	'RasterOps MediaTime'	; Mode Name
  endc
	DC.B	0			; end C String
	DC.W	0			; gVersion 0
	DC.W	DrHwRasterOps24MTV	; gType DrvrHw
	DC.W	0			; gFormulaSize 0
	DC.W	1			; gChanCnt 1
	DC.W	256			; gDataCnt 256
	DC.W	8			; gDataWidth 8
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
endmygamma
; ==================END OF GAMMA BLOCK=====================
#endasm
/* Apple Gamma sBlock */
#asm
applegamma
; ==================BEGINNING OF GAMMA BLOCK=====================
    dc.l  endapplegamma-applegamma          ; Length of sBlock
#endasm
#asm
	DC.W	$81			; Local ID
	DC.B	'MacII Std Gamma Table'		; Mode Name
	DC.B	0			; end C String
	DC.W	0			; gVersion 0
	DC.W	0			; gType DrvrHw = $00
	DC.W	0			; gFormulaSize 0
	DC.W	1			; gChanCnt 1
	DC.W	256			; gDataCnt 256
	DC.W	8			; gDataWidth 8
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
endapplegamma
; ==================END OF GAMMA BLOCK=====================
#endasm
#endif
/*______________________________________________________________________________*/
/* My sResource Driver Directory */
#asm
mydrvrdir
    OSLstEntry  2,mydrvr            ; My 68020 Driver sBlock Offset
    DatLstEntry $FF,0               ; End
#endasm
