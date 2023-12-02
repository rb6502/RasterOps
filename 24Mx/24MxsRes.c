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
; Offset List Entry 80		1152 X 870
;=============================================================
    MACRO  OSLstEntry80
X0%2
      DC.L          (%1<<24)+%2-X0%2
    ENDM
;=============================================================
; Offset List Entry 81		1024 X 768 75Hz
;=============================================================
    MACRO  OSLstEntry81
X1%2
      DC.L          (%1<<24)+%2-X1%2
    ENDM
;=============================================================
; Offset List Entry 82		1024 X 768 60Hz 
;=============================================================
    MACRO  OSLstEntry82
X2%2
      DC.L          (%1<<24)+%2-X2%2
    ENDM
;=============================================================
; Offset List Entry 83		832 X 624
;=============================================================
    MACRO  OSLstEntry83
X3%2
      DC.L          (%1<<24)+%2-X3%2
    ENDM
;=============================================================
; Offset List Entry 84		640 X 480 Noninterlaced
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
; Offset List Entry 88 
;=============================================================
    MACRO  OSLstEntry88
X8%2
      DC.L          (%1<<24)+%2-X8%2
    ENDM
;=============================================================
; Offset List Entry 89 
;=============================================================
    MACRO  OSLstEntry89
X9%2
      DC.L          (%1<<24)+%2-X9%2
    ENDM
;=============================================================
; Offset List Entry 8a 
;=============================================================
    MACRO  OSLstEntry8a
Xa%2
      DC.L          (%1<<24)+%2-Xa%2
    ENDM
;=============================================================
; Offset List Entry 8b 
;=============================================================
    MACRO  OSLstEntry8b
Xb%2
      DC.L          (%1<<24)+%2-Xb%2
    ENDM
;=============================================================
; Offset List Entry 8c 
;=============================================================
    MACRO  OSLstEntry8c
Xc%2
      DC.L          (%1<<24)+%2-Xc%2
    ENDM
;=============================================================
; Offset List Entry 8d 
;=============================================================
    MACRO  OSLstEntry8d
Xd%2
      DC.L          (%1<<24)+%2-Xd%2
    ENDM
;=============================================================
; Offset List Entry 90		1152 X 870
;=============================================================
    MACRO  OSLstEntry90
Y0%2
      DC.L          (%1<<24)+%2-Y0%2
    ENDM
;=============================================================
; Offset List Entry 91		1024 X 768 75Hz
;=============================================================
    MACRO  OSLstEntry91
Y1%2
      DC.L          (%1<<24)+%2-Y1%2
    ENDM
;=============================================================
; Offset List Entry 92  	1024 X 768 60Hz
;=============================================================
    MACRO  OSLstEntry92
Y2%2
      DC.L          (%1<<24)+%2-Y2%2
    ENDM
;=============================================================
; Offset List Entry 93		832 X 624
;=============================================================
    MACRO  OSLstEntry93
Y3%2
      DC.L          (%1<<24)+%2-Y3%2
    ENDM
;=============================================================
; Offset List Entry 94		640 X 480 Noninterlaced
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
; Offset List Entry 98
;=============================================================
    MACRO  OSLstEntry98
Y8%2
      DC.L          (%1<<24)+%2-Y8%2
    ENDM
;=============================================================
; Offset List Entry 99
;=============================================================
    MACRO  OSLstEntry99
Y9%2
      DC.L          (%1<<24)+%2-Y9%2
    ENDM
;=============================================================
; Offset List Entry 9a
;=============================================================
    MACRO  OSLstEntry9a
Ya%2
      DC.L          (%1<<24)+%2-Ya%2
    ENDM
;=============================================================
; Offset List Entry 9b
;=============================================================
    MACRO  OSLstEntry9b
Yb%2
      DC.L          (%1<<24)+%2-Yb%2
    ENDM
;=============================================================
; Offset List Entry 9c
;=============================================================
    MACRO  OSLstEntry9c
Yc%2
      DC.L          (%1<<24)+%2-Yc%2
    ENDM
;=============================================================
; Offset List Entry 9d
;=============================================================
    MACRO  OSLstEntry9d
Yd%2
      DC.L          (%1<<24)+%2-Yd%2
    ENDM
;=============================================================
; Offset List Entry a0		1152 X 870
;=============================================================
    MACRO  OSLstEntrya0
Z0%2
      DC.L          (%1<<24)+%2-Z0%2
    ENDM
;=============================================================
; Offset List Entry a1		1024 X 768 75Hz
;=============================================================
    MACRO  OSLstEntrya1
Z1%2
      DC.L          (%1<<24)+%2-Z1%2
    ENDM
;=============================================================
; Offset List Entry a2  	1024 X 768 60Hz
;=============================================================
    MACRO  OSLstEntrya2
Z2%2
      DC.L          (%1<<24)+%2-Z2%2
    ENDM
;=============================================================
; Offset List Entry a3		832 X 624
;=============================================================
    MACRO  OSLstEntrya3
Z3%2
      DC.L          (%1<<24)+%2-Z3%2
    ENDM
;=============================================================
; Offset List Entry a4		640 X 480 Noninterlaced
;=============================================================
    MACRO  OSLstEntrya4
Z4%2
      DC.L          (%1<<24)+%2-Z4%2
    ENDM
;=============================================================
; Offset List Entry a5  	
;=============================================================
    MACRO  OSLstEntrya5
Z5%2
      DC.L          (%1<<24)+%2-Z5%2
    ENDM
;=============================================================
; Offset List Entry a6  	
;=============================================================
    MACRO  OSLstEntrya6
Z6%2
      DC.L          (%1<<24)+%2-Z6%2
    ENDM
;=============================================================
; Offset List Entry a7  
;=============================================================
    MACRO  OSLstEntrya7
Z7%2
      DC.L          (%1<<24)+%2-Z7%2
    ENDM
;=============================================================
; Offset List Entry a8
;=============================================================
    MACRO  OSLstEntrya8
Z8%2
      DC.L          (%1<<24)+%2-Z8%2
    ENDM
;=============================================================
; Offset List Entry a9
;=============================================================
    MACRO  OSLstEntrya9
Z9%2
      DC.L          (%1<<24)+%2-Z9%2
    ENDM
;=============================================================
; Offset List Entry aa
;=============================================================
    MACRO  OSLstEntryaa
Za%2
      DC.L          (%1<<24)+%2-Za%2
    ENDM
;=============================================================
; Offset List Entry ab
;=============================================================
    MACRO  OSLstEntryab
Zb%2
      DC.L          (%1<<24)+%2-Zb%2
    ENDM
;=============================================================
; Offset List Entry ac
;=============================================================
    MACRO  OSLstEntryac
Zc%2
      DC.L          (%1<<24)+%2-Zc%2
    ENDM
;=============================================================
; Offset List Entry ad
;=============================================================
    MACRO  OSLstEntryad
Zd%2
      DC.L          (%1<<24)+%2-Zd%2
    ENDM
;=============================================================
; Data List Entry
;=============================================================
    MACRO  DatLstEntry
      DC.L          (%1<<24)+%2
    ENDM
#endasm
/*__________________________________________________________________________________________________*/
/* sResource Directory */
#asm
    public  directory
directory
    OSLstEntry  1,boardsreslist         ; Board sResource List Offset
 if 0
    ; Skinny slot frame buffer ( 32-bit Quickdraw NOT required)
;;;    OSLstEntry  $80,mysreslist80        ; My sResource List Offset - 1152 X 870
;;;    OSLstEntry  $81,mysreslist81        ; My sResource List Offset - 1024 X 768 75Hz
;;;    OSLstEntry  $82,mysreslist82        ; My sResource List Offset - 1024 X 768 60Hz
    OSLstEntry  $83,mysreslist83        ; My sResource List Offset -  832 X 624
    OSLstEntry  $84,mysreslist84        ; My sResource List Offset -  640 X 480 non-interlaced
;;;    OSLstEntry  $85,mysreslist85        ; My sResource List Offset -  640 X 870
;; if MAKING24MXTV
    OSLstEntry  $86,mysreslist86        ; My sResource List Offset -  640 X 480 NTSC
    OSLstEntry  $87,mysreslist87        ; My sResource List Offset -  768 X 576 PAL
    OSLstEntry  $88,mysreslist88        ; My sResource List Offset -  576 X 432 NTSC underscan
    OSLstEntry  $89,mysreslist89        ; My sResource List Offset -  684 X 512 PAL underscan
;; endc
    OSLstEntry  $8a,mysreslist8a        ; My sResource List Offset -  1152 X 870 ext
    OSLstEntry  $8b,mysreslist8b        ; My sResource List Offset -  1600 x 1200 ext
    OSLstEntry  $8c,mysreslist8c        ; My sResource List Offset -  2304 x 1740 ext
;;;    OSLstEntry  $8d,mysreslist8d        ; My sResource List Offset -  3200 x 2400 ext
 endc
    ; Fat slot frame buffer ( 32-bit Quickdraw REQUIRED)
;;;    OSLstEntry  $90,mysreslist90        ; My sResource List Offset - 1152 X 870
;;;    OSLstEntry  $91,mysreslist91        ; My sResource List Offset - 1024 X 768 75Hz
;;;    OSLstEntry  $92,mysreslist92        ; My sResource List Offset - 1024 X 768 60Hz
    OSLstEntry  $93,mysreslist93        ; My sResource List Offset -  832 X 624
    OSLstEntry  $94,mysreslist94        ; My sResource List Offset -  640 X 480 non-interlaced
;;;    OSLstEntry  $95,mysreslist95        ; My sResource List Offset -  640 X 870
;; if MAKING24MXTV
    OSLstEntry  $96,mysreslist96        ; My sResource List Offset -  640 X 480 NTSC
    OSLstEntry  $97,mysreslist97        ; My sResource List Offset -  768 X 576 PAL
    OSLstEntry  $98,mysreslist98        ; My sResource List Offset -  576 X 432 NTSC underscan
    OSLstEntry  $99,mysreslist99        ; My sResource List Offset -  684 X 512 PAL underscan
;; endc
    OSLstEntry  $9a,mysreslist9a        ; My sResource List Offset -  1152 X 870 ext
    OSLstEntry  $9b,mysreslist9b        ; My sResource List Offset -  1600 x 1200 ext
    OSLstEntry  $9c,mysreslist9c        ; My sResource List Offset -  2304 x 1740 ext
;;;    OSLstEntry  $9d,mysreslist9d        ; My sResource List Offset -  3200 x 2400 ext
    ; Fat slot frame buffer ( 32-bit Quickdraw REQUIRED)
 if MAKING24MXI
;;;    OSLstEntry  $a0,mysreslista0        ; My sResource List Offset - 1152 X 870
;;;    OSLstEntry  $a1,mysreslista1        ; My sResource List Offset - 1024 X 768 75Hz
;;;    OSLstEntry  $a2,mysreslista2        ; My sResource List Offset - 1024 X 768 60Hz
    OSLstEntry  $a3,mysreslista3        ; My sResource List Offset -  832 X 624
    OSLstEntry  $a4,mysreslista4        ; My sResource List Offset -  640 X 480 non-interlaced
;;;    OSLstEntry  $a5,mysreslista5        ; My sResource List Offset -  640 X 870
    OSLstEntry  $a6,mysreslista6        ; My sResource List Offset -  640 X 480 NTSC
    OSLstEntry  $a7,mysreslista7        ; My sResource List Offset -  768 X 576 PAL
    OSLstEntry  $a8,mysreslista8        ; My sResource List Offset -  576 X 432 NTSC underscan
    OSLstEntry  $a9,mysreslista9        ; My sResource List Offset -  684 X 512 PAL underscan
    OSLstEntry  $aa,mysreslistaa        ; My sResource List Offset -  1152 X 870 ext
    OSLstEntry  $ab,mysreslistab        ; My sResource List Offset -  1600 x 1200 ext
    OSLstEntry  $ac,mysreslistac        ; My sResource List Offset -  2304 x 1740 ext
;;;    OSLstEntry  $ad,mysreslistad        ; My sResource List Offset -  3200 x 2400 ext
 endc
    DatLstEntry $FF,0                 ; End
#endasm
/*__________________________________________________________________________________________________*/
/* Board sResource List */
#asm
boardsreslist
	OSLstEntry	1,boardtype			; Board sResource Type Format Offset
	OSLstEntry	2,boardname			; Board sResource Name Offset
; if MAKINGROPS
; 	OSLstEntry	16,boardicon		; Board sResource Icon Offset
; endc
	OSLstEntry	20,boardBTInfo		; Board sResource block transfer info Offset
	DatLstEntry	$20,CB24MxBoardId	; Board ID assigned by Apple
	OSLstEntry	$22,primaryinit		; Primary Initialization Code seBlock Offset
	OSLstEntry	$24,vendorinfo		; Vendor Info List Offset
	OSLstEntry	$26,secondaryinit	; Secondary Initialization Code seBlock Offset
	OSLstEntry   65,modenamesdir	; Video family mode names
;//еееее Display Manager (((((
;	OSLstEntry  123,svidparmdir		; sVidParmDir
;	OSLstEntry  81,svidparmdir		; sVidParmDir
;//еееее Display Manager )))))
	OSLstEntry  $80,timingtabledir	; Timing Table directory
	DatLstEntry	$FF,0				; End
#endasm
/*__________________________________________________________________________________________________*/
/* Block Transfer Info */
#asm
boardBTInfo	even
	DC.L	allSlaveBlockSizes
#endasm
#asm
;================================================================
; Video Parameter directory (one entry per resolution)
;================================================================
timingtabledir
;	OSLstEntry	$80,t1152x870_75
;	OSLstEntry	$81,t1024x768_75
;	OSLstEntry	$82,t1024x768_60
    OSLstEntry	$83,t832x624_75
	OSLstEntry	$84,t640x480_67
;	OSLstEntry	$85,t640x870_75
	OSLstEntry	$86,t640x480_NTSC
	OSLstEntry	$87,t640x480_NTSCGL
	OSLstEntry	$88,t768x576_PAL
	OSLstEntry	$89,t768x576_PALGL
	OSLstEntry	$8A,t576x432_NTSC
	OSLstEntry	$8B,t576x432_NTSCGL
	OSLstEntry	$8C,t684x512_PAL
	OSLstEntry	$8D,t684x512_PALGL
	DatLstEntry	$FF,0
 if 0
	; Table 80	1152 X 870 75Hz
t1152x870_75 even
	DC.L	endt1152x870_75-t1152x870_75
	DC.B	$03		; control_1			- 0
	DC.B	$31		; control_2			- 1
	DC.B	$00		; control_3			- 2
	DC.B	$30		; control_4			- 3
	DC.B	$00		; status			- 4
	DC.B	$98		; refresh_interval	- 5
	DC.W	$FFDF	; gio_config		- 6
	DC.L	$000000	; display_start		- 8
	DC.L	$000080	; half_row_inc		- 12
	DC.L	$0000D0	; display_pitch		- 16 *
	DC.B	$3F		; CAS_mask			- 20
	DC.B	$04		; horiz_latency		- 21
	DC.W	$000E	; horiz_end_sync	- 22 *
;	DC.W	$001E	; horiz_end_blank	- 24 *
;	DC.W	$00AE	; horiz_start_blank	- 26 *
;	DC.W	$00B6	; horiz_total		- 28 *
	DC.W	$001D	; horiz_end_blank	- 24 *
	DC.W	$00AD	; horiz_start_blank	- 26 *
	DC.W	$00B4	; horiz_total		- 28 *
	DC.W	$0000	; horiz_half_line	- 30
	DC.W	$0000	; horiz_count_load	- 32
	DC.B	$02		; vert_end_sync		- 34 *
	DC.B	$29		; vert_end_blank	- 35 *
	DC.W	$038F	; vert_start_blank	- 36 *
	DC.W	$0392	; vert_total		- 38 *
	DC.W	$0000	; vert_count_load	- 40
	DC.W	$038F	; vert_int_line		- 42
	DC.W	$CE99	; gio_reg			- 44 * = pix over 8($C000), 24 bit pixels($0E80(, 100mhz($0019)
	DC.B	$01		; y_zoom			- 46
	DC.B	$00		; soft_reg			- 47
endt1152x870_75
	; Table 81	1024 X 768 75Hz
t1024x768_75 even
	DC.L	endt1024x768_75-t1024x768_75
	DC.B	$03		; control_1			- 0
	DC.B	$31		; control_2			- 1
	DC.B	$00		; control_3			- 2
	DC.B	$30		; control_4			- 3
	DC.B	$00		; status			- 4
	DC.B	$98		; refresh_interval	- 5
	DC.W	$FFDF	; gio_config		- 6
	DC.L	$000000	; display_start		- 8
	DC.L	$000080	; half_row_inc		- 12
	DC.L	$0000D0	; display_pitch		- 16 *
	DC.B	$3F		; CAS_mask			- 20
	DC.B	$05		; horiz_latency		- 21
	DC.W	$0008	; horiz_end_sync	- 22 *
	DC.W	$001A	; horiz_end_blank	- 24 *
	DC.W	$009A	; horiz_start_blank	- 26 *
	DC.W	$00A4	; horiz_total		- 28 *
	DC.W	$0000	; horiz_half_line	- 30
	DC.W	$0000	; horiz_count_load	- 32
	DC.B	$02		; vert_end_sync		- 34 *
	DC.B	$1F		; vert_end_blank	- 35 *
	DC.W	$031F	; vert_start_blank	- 36 *
	DC.W	$0322	; vert_total		- 38 *
	DC.W	$0000	; vert_count_load	- 40
	DC.W	$031F	; vert_int_line		- 42
	DC.W	$CE97	; gio_reg			- 44 * = pix over 8($C000), 24 bit pixels($0E80(, 80mhz($0017)
	DC.B	$01		; y_zoom			- 46
	DC.B	$00		; soft_reg			- 47
endt1024x768_75
	; Table 82	1024 X 768 60Hz
t1024x768_60 even
	DC.L	endt1024x768_60-t1024x768_60
	DC.B	$03		; control_1			- 0
	DC.B	$31		; control_2			- 1
	DC.B	$00		; control_3			- 2
	DC.B	$30		; control_4			- 3
	DC.B	$00		; status			- 4
	DC.B	$98		; refresh_interval	- 5
	DC.W	$FFDF	; gio_config		- 6
	DC.L	$000000	; display_start		- 8
	DC.L	$000080	; half_row_inc		- 12
	DC.L	$0000D0	; display_pitch		- 16 *
	DC.B	$3F		; CAS_mask			- 20
	DC.B	$07		; horiz_latency		- 21
	DC.W	$000A	; horiz_end_sync	- 22 *
	DC.W	$001A	; horiz_end_blank	- 24 *
	DC.W	$009A	; horiz_start_blank	- 26 *
	DC.W	$00A2	; horiz_total		- 28 *
	DC.W	$0000	; horiz_half_line	- 30
	DC.W	$0000	; horiz_count_load	- 32
	DC.B	$05		; vert_end_sync		- 34 *
	DC.B	$26		; vert_end_blank	- 35 *
	DC.W	$0326	; vert_start_blank	- 36 *
	DC.W	$032C	; vert_total		- 38 *
	DC.W	$0000	; vert_count_load	- 40
	DC.W	$0326	; vert_int_line		- 42
	DC.W	$CE96	; gio_reg			- 44 * = pix over 8($C000), 24 bit pixels($0E80(, 64mhz($0016)
	DC.B	$01		; y_zoom			- 46
	DC.B	$00		; soft_reg			- 47
endt1024x768_60
 endc
	; Table 83	832 X 624
t832x624_75 even
	DC.L	endt832x624_75-t832x624_75
	DC.B	$03		; control_1			- 0
	DC.B	$31		; control_2			- 1
	DC.B	$00		; control_3			- 2
	DC.B	$30		; control_4			- 3
	DC.B	$00		; status			- 4
	DC.B	$98		; refresh_interval	- 5
	DC.W	$FFDF	; gio_config		- 6
	DC.L	$000000	; display_start		- 8
	DC.L	$000080	; half_row_inc		- 12
	DC.L	$0000D0	; display_pitch		- 16 *
	DC.B	$3F		; CAS_mask			- 20
	DC.B	$08		; horiz_latency		- 21
	DC.W	$0006	; horiz_end_sync	- 22 *
	DC.W	$0022	; horiz_end_blank	- 24 *
	DC.W	$008a	; horiz_start_blank	- 26 *
;	DC.W	$0090	; horiz_total		- 28 *
	DC.W	$008E	; horiz_total		- 28 *
	DC.W	$0000	; horiz_half_line	- 30
	DC.W	$0000	; horiz_count_load	- 32
	DC.B	$02		; vert_end_sync		- 34 *
	DC.B	$29		; vert_end_blank	- 35 *
	DC.W	$0299	; vert_start_blank	- 36 *
	DC.W	$029A	; vert_total		- 38 *
	DC.W	$0000	; vert_count_load	- 40
	DC.W	$0299	; vert_int_line		- 42
	DC.W	$CE95	; gio_reg			- 44 * = pix over 8($C000), 24 bit pixels($0E80(, 50mhz($0014)
	DC.B	$01		; y_zoom			- 46
	DC.B	$00		; soft_reg			- 47
endt832x624_75
	; Table 84	640 X 480 67hz
t640x480_67	even
	DC.L	endt640x480_67-t640x480_67
	DC.B	$03		; control_1			- 0
	DC.B	$31		; control_2			- 1
	DC.B	$00		; control_3			- 2
	DC.B	$30		; control_4			- 3
	DC.B	$00		; status			- 4
	DC.B	$98		; refresh_interval	- 5
	DC.W	$FFDF	; gio_config		- 6
	DC.L	$000000	; display_start		- 8
	DC.L	$000080	; half_row_inc		- 12
	DC.L	$0000D0	; display_pitch		- 16 *
	DC.B	$3F		; CAS_mask			- 20
	DC.B	$0D		; horiz_latency		- 21
	DC.W	$0006	; horiz_end_sync	- 22 *
	DC.W	$0012	; horiz_end_blank	- 24 *
	DC.W	$0062	; horiz_start_blank	- 26 *
	DC.W	$006A	; horiz_total		- 28 *
	DC.W	$0000	; horiz_half_line	- 30
	DC.W	$0000	; horiz_count_load	- 32
	DC.B	$02		; vert_end_sync		- 34 *
	DC.B	$29		; vert_end_blank	- 35 *
	DC.W	$0209	; vert_start_blank	- 36 *
	DC.W	$020C	; vert_total		- 38 *
	DC.W	$0000	; vert_count_load	- 40
	DC.W	$0209	; vert_int_line		- 42
	DC.W	$CE93	; gio_reg			- 44 * = pix over 8($C000), 24 bit pixels($0E80(, 30mhz($0014)
	DC.B	$01		; y_zoom			- 46
	DC.B	$00		; soft_reg			- 47
endt640x480_67
 if 0
	; Table 85	640 X 870
t640x870_75 even
	DC.L	endt640x870_75-t640x870_75
	DC.B	$03		; control_1			- 0
	DC.B	$31		; control_2			- 1
	DC.B	$00		; control_3			- 2
	DC.B	$30		; control_4			- 3
	DC.B	$00		; status			- 4
	DC.B	$98		; refresh_interval	- 5
	DC.W	$FFDF	; gio_config		- 6
	DC.L	$000000	; display_start		- 8
	DC.L	$000080	; half_row_inc		- 12
	DC.L	$0000D0	; display_pitch		- 16 *
	DC.B	$3F		; CAS_mask			- 20
	DC.B	$07		; horiz_latency		- 21
	DC.W	$0008	; horiz_end_sync	- 22 *
	DC.W	$0010	; horiz_end_blank	- 24 *
	DC.W	$0060	; horiz_start_blank	- 26 *
	DC.W	$0066	; horiz_total		- 28 *
	DC.W	$0000	; horiz_half_line	- 30
	DC.W	$0000	; horiz_count_load	- 32
	DC.B	$02		; vert_end_sync		- 34 *
	DC.B	$2C		; vert_end_blank	- 35 *
	DC.W	$0392	; vert_start_blank	- 36 *
	DC.W	$0395	; vert_total		- 38 *
	DC.W	$0000	; vert_count_load	- 40
	DC.W	$0392	; vert_int_line		- 42
	DC.W	$CE95	; gio_reg			- 44 * = pix over 8($c000), 24 bit pixels($0E80(, 57mhz($0015)
	DC.B	$01		; y_zoom			- 46
	DC.B	$00		; soft_reg			- 47
endt640x870_75
 endc
	; Table 86	640 X 480 NTSC
t640x480_NTSC even
	DC.L	endt640x480_NTSC-t640x480_NTSC
	DC.B	$0B		; control_1			- 0
	DC.B	$31		; control_2			- 1
	DC.B	$08		; control_3			- 2
	DC.B	$30		; control_4			- 3
	DC.B	$00		; status			- 4
	DC.B	$98		; refresh_interval	- 5
	DC.W	$FFDF	; gio_config		- 6
	DC.L	$000000	; display_start		- 8
	DC.L	$000080	; half_row_inc		- 12
	DC.L	$0000D0	; display_pitch		- 16 *
	DC.B	$3F		; CAS_mask			- 20
	DC.B	$1B		; horiz_latency		- 21
	DC.W	$000F	; horiz_end_sync	- 22 *
	DC.W	$001C	; horiz_end_blank	- 24 *
	DC.W	$00BC	; horiz_start_blank	- 26 *
	DC.W	$00C1	; horiz_total		- 28 *
	DC.W	$0060	; horiz_half_line	- 30
	DC.W	$0000	; horiz_count_load	- 32
	DC.B	$02		; vert_end_sync		- 34 *
	DC.B	$12		; vert_end_blank	- 35 *
	DC.W	$0102	; vert_start_blank	- 36 *
	DC.W	$0105	; vert_total		- 38 *
	DC.W	$0000	; vert_count_load	- 40
	DC.W	$0102	; vert_int_line		- 42
	DC.W	$4E90	; gio_reg			- 44 * = pix over 4($8000), 24 bit pixels($0E80(, 57mhz($0015)
	DC.B	$01		; y_zoom			- 46
	DC.B	$00		; soft_reg			- 47
endt640x480_NTSC
	; Table 87	640 X 480 NTSC GenLock
t640x480_NTSCGL even
	DC.L	endt640x480_NTSCGL-t640x480_NTSCGL
	DC.B	$0B		; control_1			- 0
	DC.B	$31		; control_2			- 1
	DC.B	$88		; control_3			- 2
	DC.B	$30		; control_4			- 3
	DC.B	$00		; status			- 4
	DC.B	$98		; refresh_interval	- 5
	DC.W	$FFDF	; gio_config		- 6
	DC.L	$000000	; display_start		- 8
	DC.L	$000080	; half_row_inc		- 12
	DC.L	$0000D0	; display_pitch		- 16 *
	DC.B	$3F		; CAS_mask			- 20
	DC.B	$1B		; horiz_latency		- 21
	DC.W	$000F	; horiz_end_sync	- 22 *
	DC.W	$0013	; horiz_end_blank	- 24 *
	DC.W	$00B3	; horiz_start_blank	- 26 *
	DC.W	$FFFF	; horiz_total		- 28 *
	DC.W	$0060	; horiz_half_line	- 30
	DC.W	$0000	; horiz_count_load	- 32
	DC.B	$02		; vert_end_sync		- 34 *
	DC.B	$10		; vert_end_blank	- 35 *
	DC.W	$0100	; vert_start_blank	- 36 *
	DC.W	$FFFF	; vert_total		- 38 *
	DC.W	$0000	; vert_count_load	- 40
	DC.W	$0000	; vert_int_line		- 42
	DC.W	$4E00	; gio_reg			- 44 * = pix over 4($8000), 24 bit pixels($0E80(, 57mhz($0015)
	DC.B	$01		; y_zoom			- 46
	DC.B	$00		; soft_reg			- 47
endt640x480_NTSCGL
	; Table 88	768 X 576 PAL
t768x576_PAL even
	DC.L	endt768x576_PAL-t768x576_PAL
	DC.B	$0B		; control_1			- 0
	DC.B	$31		; control_2			- 1
	DC.B	$08		; control_3			- 2
	DC.B	$30		; control_4			- 3
	DC.B	$00		; status			- 4
	DC.B	$98		; refresh_interval	- 5
	DC.W	$FFDF	; gio_config		- 6
	DC.L	$000000	; display_start		- 8
	DC.L	$000080	; half_row_inc		- 12
	DC.L	$0000D0	; display_pitch		- 16 *
	DC.B	$3F		; CAS_mask			- 20
	DC.B	$21		; horiz_latency		- 21
	DC.W	$0010	; horiz_end_sync	- 22 *
	DC.W	$0026	; horiz_end_blank	- 24 *
	DC.W	$00e6	; horiz_start_blank	- 26 *
	DC.W	$00ea	; horiz_total		- 28 *
	DC.W	$0075	; horiz_half_line	- 30
	DC.W	$0000	; horiz_count_load	- 32
	DC.B	$02		; vert_end_sync		- 34 *
	DC.B	$15		; vert_end_blank	- 35 *
	DC.W	$0135	; vert_start_blank	- 36 *
	DC.W	$0138	; vert_total		- 38 *
	DC.W	$0000	; vert_count_load	- 40
	DC.W	$0135	; vert_int_line		- 42
	DC.W	$4E91	; gio_reg			- 44 * = pix over 8($c000), 24 bit pixels($0E80(, 57mhz($0015)
	DC.B	$01		; y_zoom			- 46
	DC.B	$02		; soft_reg			- 47
endt768x576_PAL
	; Table 89	768 X 576 PAL GenLock
t768x576_PALGL even
	DC.L	endt768x576_PALGL-t768x576_PALGL
	DC.B	$0B		; control_1			- 0
	DC.B	$31		; control_2			- 1
	DC.B	$88		; control_3			- 2
	DC.B	$30		; control_4			- 3
	DC.B	$00		; status			- 4
	DC.B	$98		; refresh_interval	- 5
	DC.W	$FFDF	; gio_config		- 6
	DC.L	$000000	; display_start		- 8
	DC.L	$000080	; half_row_inc		- 12
	DC.L	$0000D0	; display_pitch		- 16 *
	DC.B	$3F		; CAS_mask			- 20
	DC.B	$21		; horiz_latency		- 21
	DC.W	$0010	; horiz_end_sync	- 22 *
	DC.W	$001d	; horiz_end_blank	- 24 *
	DC.W	$00dd	; horiz_start_blank	- 26 *
	DC.W	$FFFF	; horiz_total		- 28 *
	DC.W	$0075	; horiz_half_line	- 30
	DC.W	$0000	; horiz_count_load	- 32
	DC.B	$02		; vert_end_sync		- 34 *
	DC.B	$15		; vert_end_blank	- 35 *
	DC.W	$0135	; vert_start_blank	- 36 *
	DC.W	$FFFF	; vert_total		- 38 *
	DC.W	$0000	; vert_count_load	- 40
	DC.W	$0000	; vert_int_line		- 42
	DC.W	$4E01	; gio_reg			- 44 * = pix over 8($c000), 24 bit pixels($0E80(, 57mhz($0015)
	DC.B	$01		; y_zoom			- 46
	DC.B	$02		; soft_reg			- 47
endt768x576_PALGL
	; Table 8A	576 X 432 NTSC
t576x432_NTSC even
	DC.L	endt576x432_NTSC-t576x432_NTSC
	DC.B	$0B		; control_1			- 0
	DC.B	$31		; control_2			- 1
	DC.B	$08		; control_3			- 2
	DC.B	$30		; control_4			- 3
	DC.B	$00		; status			- 4
	DC.B	$98		; refresh_interval	- 5
	DC.W	$FFDF	; gio_config		- 6
	DC.L	$000000	; display_start		- 8
	DC.L	$000080	; half_row_inc		- 12
	DC.L	$0000D0	; display_pitch		- 16 *
	DC.B	$3F		; CAS_mask			- 20
	DC.B	$1B		; horiz_latency		- 21
	DC.W	$000F	; horiz_end_sync	- 22 *
	DC.W	$0024	; horiz_end_blank	- 24 *
	DC.W	$00B4	; horiz_start_blank	- 26 *
	DC.W	$00C1	; horiz_total		- 28 *
	DC.W	$0060	; horiz_half_line	- 30
	DC.W	$0000	; horiz_count_load	- 32
	DC.B	$02		; vert_end_sync		- 34 *
	DC.B	$1E		; vert_end_blank	- 35 *
	DC.W	$00F6	; vert_start_blank	- 36 *
	DC.W	$0105	; vert_total		- 38 *
	DC.W	$0000	; vert_count_load	- 40
	DC.W	$00F6	; vert_int_line		- 42
	DC.W	$4E90	; gio_reg			- 44 * = pix over 4($8000), 24 bit pixels($0E80(, 57mhz($0015)
	DC.B	$01		; y_zoom			- 46
	DC.B	$01		; soft_reg			- 47
endt576x432_NTSC
	; Table 8B	576 X 432 NTSC GenLock
t576x432_NTSCGL even
	DC.L	endt576x432_NTSCGL-t576x432_NTSCGL
	DC.B	$0B		; control_1			- 0
	DC.B	$31		; control_2			- 1
	DC.B	$88		; control_3			- 2
	DC.B	$30		; control_4			- 3
	DC.B	$00		; status			- 4
	DC.B	$98		; refresh_interval	- 5
	DC.W	$FFDF	; gio_config		- 6
	DC.L	$000000	; display_start		- 8
	DC.L	$000080	; half_row_inc		- 12
	DC.L	$0000D0	; display_pitch		- 16 *
	DC.B	$3F		; CAS_mask			- 20
	DC.B	$1B		; horiz_latency		- 21
	DC.W	$000F	; horiz_end_sync	- 22 *
	DC.W	$001B	; horiz_end_blank	- 24 *
	DC.W	$00AB	; horiz_start_blank	- 26 *
	DC.W	$00C1	; horiz_total		- 28 *
	DC.W	$0060	; horiz_half_line	- 30
	DC.W	$0000	; horiz_count_load	- 32
	DC.B	$02		; vert_end_sync		- 34 *
	DC.B	$1C		; vert_end_blank	- 35 *
	DC.W	$00F4	; vert_start_blank	- 36 *
	DC.W	$0105	; vert_total		- 38 *
	DC.W	$0000	; vert_count_load	- 40
	DC.W	$0000	; vert_int_line		- 42
	DC.W	$4E00	; gio_reg			- 44 * = pix over 4($8000), 24 bit pixels($0E80(, 57mhz($0015)
	DC.B	$01		; y_zoom			- 46
	DC.B	$01		; soft_reg			- 47
endt576x432_NTSCGL
	; Table 8C	684 X 512 PAL underscan
t684x512_PAL even
	DC.L	endt684x512_PAL-t684x512_PAL
	DC.B	$0B		; control_1			- 0
	DC.B	$31		; control_2			- 1
	DC.B	$08		; control_3			- 2
	DC.B	$30		; control_4			- 3
	DC.B	$00		; status			- 4
	DC.B	$98		; refresh_interval	- 5
	DC.W	$FFDF	; gio_config		- 6
	DC.L	$000000	; display_start		- 8
	DC.L	$000080	; half_row_inc		- 12
	DC.L	$0000D0	; display_pitch		- 16 *
	DC.B	$3F		; CAS_mask			- 20
	DC.B	$21		; horiz_latency		- 21
	DC.W	$0010	; horiz_end_sync	- 22 *
	DC.W	$0032	; horiz_end_blank	- 24 *
	DC.W	$00DB	; horiz_start_blank	- 26 *
	DC.W	$00ea	; horiz_total		- 28 *
	DC.W	$0075	; horiz_half_line	- 30
	DC.W	$0000	; horiz_count_load	- 32
	DC.B	$02		; vert_end_sync		- 34 *
	DC.B	$25		; vert_end_blank	- 35 *
	DC.W	$0125	; vert_start_blank	- 36 *
	DC.W	$0138	; vert_total		- 38 *
	DC.W	$0000	; vert_count_load	- 40
	DC.W	$0125	; vert_int_line		- 42
	DC.W	$4E91	; gio_reg			- 44 * = pix over 8($c000), 24 bit pixels($0E80(, 57mhz($0015)
	DC.B	$01		; y_zoom			- 46
	DC.B	$03		; soft_reg			- 47
endt684x512_PAL
	; Table 8C	684 X 512 PAL Genlock underscan
t684x512_PALGL even
	DC.L	endt684x512_PALGL-t684x512_PALGL
	DC.B	$0B		; control_1			- 0
	DC.B	$31		; control_2			- 1
	DC.B	$88		; control_3			- 2
	DC.B	$30		; control_4			- 3
	DC.B	$00		; status			- 4
	DC.B	$98		; refresh_interval	- 5
	DC.W	$FFDF	; gio_config		- 6
	DC.L	$000000	; display_start		- 8
	DC.L	$000080	; half_row_inc		- 12
	DC.L	$0000D0	; display_pitch		- 16 *
	DC.B	$3F		; CAS_mask			- 20
	DC.B	$21		; horiz_latency		- 21
	DC.W	$0010	; horiz_end_sync	- 22 *
	DC.W	$0029	; horiz_end_blank	- 24 *
	DC.W	$00D2	; horiz_start_blank	- 26 *
	DC.W	$FFFF	; horiz_total		- 28 *
	DC.W	$0075	; horiz_half_line	- 30
	DC.W	$0000	; horiz_count_load	- 32
	DC.B	$02		; vert_end_sync		- 34 *
	DC.B	$25		; vert_end_blank	- 35 *
	DC.W	$0125	; vert_start_blank	- 36 *
	DC.W	$FFFF	; vert_total		- 38 *
	DC.W	$0000	; vert_count_load	- 40
	DC.W	$0000	; vert_int_line		- 42
	DC.W	$4E01	; gio_reg			- 44 * = pix over 8($c000), 24 bit pixels($0E80(, 57mhz($0015)
	DC.B	$01		; y_zoom			- 46
	DC.B	$03		; soft_reg			- 47
endt684x512_PALGL
#endasm
/*__________________________________________________________________________________________________*/
/* Video family mode names directory */
#asm
modenamesdir
 if 0
;;;	OSLstEntry	$80,s1152x870
;;;	OSLstEntry	$81,s1024x768_75
;;;	OSLstEntry	$82,s1024x768_60
    OSLstEntry	$83,s832x624
	OSLstEntry	$84,s640x480
	OSLstEntry	$85,s640x870
;; if MAKING24MXTV
	OSLstEntry	$86,s640x480n
	OSLstEntry	$87,s768x576p
	OSLstEntry	$88,s576x432n
	OSLstEntry	$89,s684x512p
;; endc
	OSLstEntry	$8a,s1152x870ext
	OSLstEntry	$8b,s1600x1200ext
	OSLstEntry	$8c,s2304x1740ext
;;;	OSLstEntry	$8d,s3200x2400ext
 endc
;;;	OSLstEntry	$90,f1152x870
;;;	OSLstEntry	$91,f1024x768_75
;;;	OSLstEntry	$92,f1024x768_60
	OSLstEntry	$93,f832x624
	OSLstEntry	$94,f640x480
	OSLstEntry	$95,f640x870
;; if MAKING24MXTV
	OSLstEntry	$96,f640x480n
	OSLstEntry	$97,f768x576p
	OSLstEntry	$98,f576x432n
	OSLstEntry	$99,f684x512p
;; endc
	OSLstEntry	$9a,f1152x870ext
	OSLstEntry	$9b,f1600x1200ext
	OSLstEntry	$9c,f2304x1740ext
;;;	OSLstEntry	$9d,f3200x2400ext
 if MAKING24MXI
;;;	OSLstEntry	$a0,g1152x870
;;;	OSLstEntry	$a1,g1024x768_75
;;;	OSLstEntry	$a2,g1024x768_60
	OSLstEntry	$a3,g832x624
	OSLstEntry	$a4,g640x480
	OSLstEntry	$a5,g640x870
	OSLstEntry	$a6,g640x480n
	OSLstEntry	$a7,g768x576p
	OSLstEntry	$a8,g576x432n
	OSLstEntry	$a9,g684x512p
	OSLstEntry	$aa,g1152x870ext
	OSLstEntry	$ab,g1600x1200ext
	OSLstEntry	$ac,g2304x1740ext
;;;	OSLstEntry	$ad,g3200x2400ext
 endc
	DatLstEntry	$FF,0
#endasm
#asm
s1152x870 even
f1152x870 even
g1152x870 even
	DC.L ends1152x870-s1152x870
	DC.W 20
	DC.B '1152 X 870'
	DC.W 0
ends1152x870
s1024x768_75 even
f1024x768_75 even
g1024x768_75 even
	DC.L ends1024x768_75-s1024x768_75
	DC.W 22
	DC.B '1024 X 768 (75Hz)'
	DC.W 0
ends1024x768_75
s1024x768_60 even
f1024x768_60 even
g1024x768_60 even
	DC.L ends1024x768_60-s1024x768_60
	DC.W 24
	DC.B '1024 X 768 (60Hz)'
	DC.W 0
ends1024x768_60
s832x624 even
f832x624 even
g832x624 even
	DC.L ends832x624-s832x624
	DC.W 26
	DC.B '832 X 624'
	DC.W 0
ends832x624
s640x480 even
f640x480 even
g640x480 even
	DC.L ends640x480-s640x480
	DC.W 28
	DC.B '640 X 480 (67Hz Noninterlaced)'
	DC.W 0
ends640x480
s640x870 even
f640x870 even
g640x870 even
	DC.L ends640x870-s640x870
	DC.W 30
	DC.B '640 X 870'
	DC.W 0
ends640x870
s640x480n even
f640x480n even
g640x480n even
	DC.L ends640x480n-s640x480n
	DC.W 32
	DC.B '640 X 480 (30Hz NTSC)'
	DC.W 0
ends640x480n
s768x576p even
f768x576p even
g768x576p even
	DC.L ends768x576p-s768x576p
	DC.W 34
	DC.B '768 X 576 (25Hz PAL)'
	DC.W 0
ends768x576p
s576x432n even
f576x432n even
g576x432n even
	DC.L ends576x432n-s576x432n
	DC.W 36
	DC.B '576 X 432 (30Hz NTSC Underscan)'
	DC.W 0
ends576x432n
s684x512p even
f684x512p even
g684x512p even
	DC.L ends684x512p-s684x512p
	DC.W 36
	DC.B '684 X 512 (25Hz PAL Underscan)'
	DC.W 0
ends684x512p
s1152x870ext even
f1152x870ext even
g1152x870ext even
	DC.L ends1152x870ext-s1152x870ext
	DC.W 38
	DC.B '1152 X 870  (Extended)'
	DC.W 0
ends1152x870ext
s1600x1200ext even
f1600x1200ext even
g1600x1200ext even
	DC.L ends1600x1200ext-s1600x1200ext
	DC.W 3a
	DC.B '1600 X 1200 (Extended)'
	DC.W 0
ends1600x1200ext
s2304x1740ext even
f2304x1740ext even
g2304x1740ext even
	DC.L ends2304x1740ext-s2304x1740ext
	DC.W 3c
	DC.B '2304 X 1740 (Extended)'
	DC.W 0
ends2304x1740ext
s3200x2400ext even
f3200x2400ext even
g3200x2400ext even
	DC.L ends3200x2400ext-s3200x2400ext
	DC.W 3e
	DC.B '3200 X 2400 (Extended)'
	DC.W 0
ends3200x2400ext
#endasm
/*еееее Display Manager ((((( */
/* Apple Scan Timings */
enum
{
	timingUnknown			= 0,	/* unknown timing */
	timingApple12			= 130,	/* 512x384 (60 Hz) 12" RGB */
	timingApple12x			= 135,	/* 560x384 (60 Hz) */
	timingApple13			= 140,	/* 640x480 (67 Hz) 13" RGB */
	timingApple13x			= 145,	/* 640x400 (67 Hz) */
	timingAppleVGA			= 150,	/* 640x480 (60 Hz) 12" VGA */
	timingApple15			= 160,	/* 640x870 (75 Hz) full page display */
	timingApple15x			= 165,	/* 640x818 (75 Hz) full page display 818 */
	timingApple16			= 170,	/* 832x624 (75 Hz) 16" RGB */
	timingAppleSVGA			= 180,	/* 800x600 (56 Hz) SVGA */
	timingApple1ka			= 190,	/* 1024x768 (60 Hz) VESA 1K-60Hz */
	timingApple1kb			= 200,	/* 1024x768 (70 Hz) VESA 1K-70Hz */
	timingApple19			= 210,	/* 1024x768 (75 Hz) Apple 19" RGB */
	timingApple21			= 220,	/* 1152x870 (75 Hz) Apple 21" RGB */
	timingAppleNTSC_ST		= 230,	/* 512x384 (60 Hz, interlaced, nonconvolved) */
	timingAppleNTSC_FF		= 232,	/* 640x480 (60 Hz, interlaced, nonconvolved) */
	timingAppleNTSC_STconv	= 234,	/* 512x384 (60 Hz, interlaced, convolved) */
	timingAppleNTSC_FFconv	= 236,	/* 640x480 (60 Hz, interlaced, convolved) */
	timingApplePAL_ST		= 238,	/* 640x480 (50 Hz, interlaced, nonconvolved) */
	timingApplePAL_FF		= 240,	/* 768x576 (50 Hz, interlaced, nonconvolved) */
	timingApplePAL_STconv	= 242,	/* 640x480 (50 Hz, interlaced, convolved) */
	timingApplePAL_FFconv	= 244	/* 768x576 (50 Hz, interlaced, convolved) */
};
#asm
timingUnknown			EQU	0		; unknown timing
timingApple12			EQU	130		;512x384 (60 Hz) 12" RGB
timingApple12x			EQU	135		; 560x384 (60 Hz)
timingApple13			EQU	140		; 640x480 (67 Hz) 13" RGB
timingApple13x			EQU	145		; 640x400 (67 Hz)
timingAppleVGA			EQU	150		; 640x480 (60 Hz) 12" VGA
timingApple15			EQU	160		; 640x870 (75 Hz) full page display 
timingApple15x			EQU	165		; 640x818 (75 Hz) full page display 818
timingApple16			EQU	170		; 832x624 (75 Hz) 16" RGB
timingAppleSVGA			EQU	180		; 800x600 (56 Hz) SVGA
timingApple1ka			EQU	190		; 1024x768 (60 Hz) VESA 1K-60Hz
timingApple1kb			EQU	200		; 1024x768 (70 Hz) VESA 1K-70Hz
timingApple19			EQU	210		; 1024x768 (75 Hz) Apple 19" RGB
timingApple21			EQU	220		; 1152x870 (75 Hz) Apple 21" RGB
timingAppleNTSC_ST		EQU	230		; 512x384 (60 Hz, interlaced, nonconvolved)
timingAppleNTSC_FF		EQU	232		; 640x480 (60 Hz, interlaced, nonconvolved)
timingAppleNTSC_STconv	EQU	234		; 512x384 (60 Hz, interlaced, convolved)
timingAppleNTSC_FFconv	EQU	236		; 640x480 (60 Hz, interlaced, convolved)
timingApplePAL_ST		EQU	238		; 640x480 (50 Hz, interlaced, nonconvolved)
timingApplePAL_FF		EQU	240		; 768x576 (50 Hz, interlaced, nonconvolved)
timingApplePAL_STconv	EQU	242		; 640x480 (50 Hz, interlaced, convolved)
timingApplePAL_FFconv	EQU	244		; 768x576 (50 Hz, interlaced, convolved)
#endasm
#if 0
/*__________________________________________________________________________________________________*/
/* Video Scan Timings directory */
#asm
svidparmdir
;	OSLstEntry	$80,v1152x870_75
;	OSLstEntry	$81,v1024x768_75
;	OSLstEntry	$82,v1024x768_60
    OSLstEntry	$83,v832x624_75
	OSLstEntry	$84,v640x480_67
;	OSLstEntry	$85,v640x870_75
	OSLstEntry	$86,v640x480_NTSC
	OSLstEntry	$87,v768x576_PAL
	OSLstEntry	$88,v576x432_NTSC
	OSLstEntry	$89,v684x512_PAL
	OSLstEntry	$8A,v1152x870_EXT
	OSLstEntry	$8B,v1600x1200_EXT
	OSLstEntry	$8C,v2304x1740_EXT
	OSLstEntry	$8D,v3200x2400_EXT
;	OSLstEntry	$90,v1152x870_75
;	OSLstEntry	$91,v1024x768_75
;	OSLstEntry	$92,v1024x768_60
    OSLstEntry	$93,v832x624_75
	OSLstEntry	$94,v640x480_67
;	OSLstEntry	$95,v640x870_75
	OSLstEntry	$96,v640x480_NTSC
	OSLstEntry	$97,v768x576_PAL
	OSLstEntry	$98,v576x432_NTSC
	OSLstEntry	$99,v684x512_PAL
	OSLstEntry	$9A,v1152x870_EXT
	OSLstEntry	$9B,v1600x1200_EXT
	OSLstEntry	$9C,v2304x1740_EXT
	OSLstEntry	$9D,v3200x2400_EXT
;	OSLstEntry	$A0,v1152x870_75
;	OSLstEntry	$A1,v1024x768_75
;	OSLstEntry	$A2,v1024x768_60
    OSLstEntry	$A3,v832x624_75
	OSLstEntry	$A4,v640x480_67
;	OSLstEntry	$A5,v640x870_75
	OSLstEntry	$A6,v640x480_NTSC
	OSLstEntry	$A7,v768x576_PAL
	OSLstEntry	$A8,v576x432_NTSC
	OSLstEntry	$A9,v684x512_PAL
	OSLstEntry	$AA,v1152x870_EXT
	OSLstEntry	$AB,v1600x1200_EXT
	OSLstEntry	$AC,v2304x1740_EXT
	OSLstEntry	$AD,v3200x2400_EXT
	DatLstEntry	$FF,0
#endasm
#asm
;v1152x870_75 even
;	DC.L timingApple21	; TimingData 1152x870 75Hz
;v1024x768_75 even
;	DC.L timingApple19	; TimingData 1024x768 75Hz
;v1024x768_60 even
;	DC.L timingApple1ka	; TimingData 1024x768 60Hz
v832x624_75 even
	DC.L timingApple16	; TimingData 832x624 75Hz
v640x480_67 even
	DC.L timingApple13	; TimingData 640x480 67Hz
;v640x870_75 even
;	DC.L timingApple15	; TimingData 640x870 75Hz
v640x480_NTSC even
	DC.L timingAppleNTSC_FF	; TimingData 640x480 NTSC
v768x576_PAL even
	DC.L timingApplePAL_FF	; TimingData 768x576 PAL
v576x432_NTSC even
	DC.L timingAppleNTSC_ST	; TimingData 576x432 NTSC Safe Title
v684x512_PAL even
	DC.L timingApplePAL_ST	; TimingData 684x512 PAL Safe Title
v1152x870_EXT even
	DC.L timingApple21	; TimingData  1152x870 Extended Desktop
v1600x1200_EXT even
	DC.L timingUnknown	; TimingData  1600x1200 Extended Desktop
v2304x1740_EXT even
	DC.L timingUnknown	; TimingData  2304x1740 Extended Desktop
v3200x2400_EXT even
	DC.L timingUnknown	; TimingData  3200x2400 Extended Desktop
#endasm
#endif
/*еееее Display Manager )))))*/
/*__________________________________________________________________________________________________*/
/* Board sResource Type Format */
#asm
boardtype even
    dc.w  1        	; Category: Board
    dc.w  0        	; Type:     Board
    dc.w  0        	; 0 for Board
    dc.w  0        	; 0 for Board
#endasm
/*__________________________________________________________________________________________________*/
/* Board sResource Name */
#if (MAKINGROPS | MAKINGGENERIC | MAKINGLTD)
#asm
boardname			; Official Product Name
	if MAKING24MXI
		dc.b	'RasterOps 24Mx 2.1b1'
	else
		if MAKING24MXRGB
			dc.b	'RasterOps 24MxRGB 2.1b1'
		else
			dc.b	'RasterOps 24MxTV 2.1b1'
		endc
	endc
	dc.w	0		; For Alignment
#endasm
#endif
#if MAKINGIZUMIYA
#asm
boardname			; Official Product Name
	dc.b	'IZUMIYA 24Xiz 2.1b1'
	dc.w	0		; For Alignment
#endasm
#endif
#if MAKINGRGB
#asm
boardname		; Official Product Name
	dc.b	'ImageBoss 2000 2.1b1'
	dc.w	0	; For Alignment
#endasm
#endif
#if MAKINGMT
#asm
boardname		; Official Product Name
	dc.b	'VisionPRO 2.1b1'
	dc.w	0	; For Alignment
#endasm
#endif
/*__________________________________________________________________________________________________*/
/* Board sResource Icon */
/****
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
*/
/* **********************   VENDOR INFO    ******************* */
/* Vendor Info List */
#asm
vendorinfo
    OSLstEntry  1,vendordesign    	; Vendor Design ID Offset
    OSLstEntry  3,cardrevision    	; Card's Revision Level Offset
    OSLstEntry  4,cardpartnumber  	; Card Part Number Offset
	OSLstEntry  5,cardrevisiondate	; Card Revison Date Offset
    DatLstEntry $FF,0             	; End
#endasm
/* Actual Vendor Info */
#if (MAKINGROPS | MAKINGGENERIC | MAKINGLTD | MAKINGIZUMIYA)
#asm
vendordesign
    dc.b  'RasterOps'
    dc.w  0            ; For Alignment
cardrevision
    dc.b  'ROM Version: 2.1 PZE'
    dc.w  0            ; For Alignment
cardpartnumber
 if MAKING24MXI
    dc.b  '24Mx'
 else
 	if MAKING24MXRGB
  	  dc.b  '24MxRGB'
	else
  	  dc.b  '24MxTV'
	endc
 endc
    dc.w  0            ; For Alignment
cardrevisiondate
    dc.b  'Aug 11, 1994'
	dc.w  0
#endasm
#endif
#if MAKINGRGB
#asm
vendordesign
    dc.b  'RGB Technology'
    dc.w  0            ; For Alignment
cardrevision
    dc.b  'ROM Version: 2.1 PZE'
    dc.w  0            ; For Alignment
cardpartnumber
    dc.b  'ImageBoss 2000'
    dc.w  0            ; For Alignment
cardrevisiondate
    dc.b  'Aug 11, 1994'
    dc.w  0	       ; For Alignment
#endasm
#endif
#if MAKINGMT
#asm
vendordesign
    dc.b  'MacTel'
    dc.w  0            ; For Alignment
cardrevision
    dc.b  'ROM Version: 2.1 PZE'
    dc.w  0            ; For Alignment
cardpartnumber
    dc.b  'VisionPRO'
    dc.w  0            ; For Alignment
cardrevisiondate
    dc.b  'Aug 11, 1994'
    dc.w  0	       ; For Alignment
#endasm
#endif
#if 0
/* My sResource List 80 - 1152 X 870 */
#asm
mysreslist80
    OSLstEntry80  1,mytype            	; My sResource Type Format Offset
    OSLstEntry80  2,myname				; My sResource Name Offset
    OSLstEntry80  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry80  $A,minorbase        	; MinorBase Offset
    OSLstEntry80  $B,minorlen8         	; MinorLength Offset
;    OSLstEntry80  $40,gammadirectory    ; Gamma correction table directory
    OSLstEntry80  $80,bits1parmlist0   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry80  $81,bits2parmlist0   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry80  $82,bits4parmlist0   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry    $83,bits8parmlist0   	; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 81 - 1024 X 768 75Hz */
#asm
mysreslist81
    OSLstEntry81  1,mytype            	; My sResource Type Format Offset
    OSLstEntry81  2,myname            	; My sResource Name Offset
    OSLstEntry81  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry81  $A,minorbase        	; MinorBase Offset
    OSLstEntry81  $B,minorlen8        	; MinorLength Offset
;    OSLstEntry81  $40,gammadirectory    ; Gamma correction table directory
    OSLstEntry81  $80,bits1parmlist1   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry81  $81,bits2parmlist1   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry81  $82,bits4parmlist1   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry81  $83,bits8parmlist1   	; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 82 - 1024 X 768 60Hz */
#asm
mysreslist82
    OSLstEntry82  1,mytype            	; My sResource Type Format Offset
    OSLstEntry82  2,myname            	; My sResource Name Offset
    OSLstEntry82  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry82  $A,minorbase        	; MinorBase Offset
    OSLstEntry82  $B,minorlen8        	; MinorLength Offset
;    OSLstEntry82  $40,gammadirectory    ; Gamma correction table directory
    OSLstEntry82  $80,bits1parmlist1   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry82  $81,bits2parmlist1   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry82  $82,bits4parmlist1   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry82  $83,bits8parmlist1   	; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 83 - 832 X 624 */
#asm
mysreslist83
    OSLstEntry83  1,mytype            	; My sResource Type Format Offset
    OSLstEntry83  2,myname            	; My sResource Name Offset
    OSLstEntry83  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry83  $A,minorbase        	; MinorBase Offset
    OSLstEntry83  $B,minorlen8         	; MinorLength Offset
;    OSLstEntry83  $40,gammadirectory  	 ; Gamma correction table directory
    OSLstEntry83  $80,bits1parmlist2   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry83  $81,bits2parmlist2   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry83  $82,bits4parmlist2   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry83  $83,bits8parmlist2   	; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 84 - 640 X 480 */
#asm
mysreslist84
mysreslist86
    OSLstEntry84  1,mytype            	; My sResource Type Format Offset
    OSLstEntry84  2,myname            	; My sResource Name Offset
    OSLstEntry84  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry84  $A,minorbase        	; MinorBase Offset
    OSLstEntry84  $B,minorlen8         	; MinorLength Offset
;    OSLstEntry84  $40,gammadirectory    ; Gamma correction table directory
    OSLstEntry84  $80,bits1parmlist3   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry84  $81,bits2parmlist3   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry84  $82,bits4parmlist3   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry84  $83,bits8parmlist3   	; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 85 - 640 X 870 */
#asm
mysreslist85
    OSLstEntry85  1,mytype            	; My sResource Type Format Offset
    OSLstEntry85  2,myname            	; My sResource Name Offset
    OSLstEntry85  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry85  $A,minorbase        	; MinorBase Offset
    OSLstEntry85  $B,minorlen8        	; MinorLength Offset
;    OSLstEntry85  $40,gammadirectory    ; Gamma correction table directory
    OSLstEntry85  $80,bits1parmlist7   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry85  $81,bits2parmlist7   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry85  $82,bits4parmlist7   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry85  $83,bits8parmlist7   	; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 87 - 768 X 576 */
#asm
mysreslist87
    OSLstEntry87  1,mytype            	; My sResource Type Format Offset
    OSLstEntry87  2,myname            	; My sResource Name Offset
    OSLstEntry87  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry87  $A,minorbase        	; MinorBase Offset
    OSLstEntry87  $B,minorlen8         	; MinorLength Offset
;    OSLstEntry87  $40,gammadirectory   ; Gamma correction table directory
    OSLstEntry87  $80,bits1parmlist10   ; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry87  $81,bits2parmlist10   ; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry87  $82,bits4parmlist10   ; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry87  $83,bits8parmlist10   ; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 88 - 576 x 432 ntsc underscan */
#asm
mysreslist88
    OSLstEntry88  1,mytype            	; My sResource Type Format Offset
    OSLstEntry88  2,myname            	; My sResource Name Offset
    OSLstEntry88  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry88  $A,minorbase        	; MinorBase Offset
    OSLstEntry88  $B,minorlen8         	; MinorLength Offset
;    OSLstEntry88  $40,gammadirectory    ; Gamma correction table directory
    OSLstEntry88  $80,bits1parmlist8   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry88  $81,bits2parmlist8   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry88  $82,bits4parmlist8   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry88  $83,bits8parmlist8   	; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 89 - 684 x 512 pal underscan */
#asm
mysreslist89
    OSLstEntry89  1,mytype            	; My sResource Type Format Offset
    OSLstEntry89  2,myname            	; My sResource Name Offset
    OSLstEntry89  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry89  $A,minorbase        	; MinorBase Offset
    OSLstEntry89  $B,minorlen8         	; MinorLength Offset
;    OSLstEntry89  $40,gammadirectory    ; Gamma correction table directory
    OSLstEntry89  $80,bits1parmlist9   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry89  $81,bits2parmlist9   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry89  $82,bits4parmlist9   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry89  $83,bits8parmlist9   	; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 8a - 1152 x 870 extended */
#asm
mysreslist8a
    OSLstEntry8a  1,mytype            	; My sResource Type Format Offset
    OSLstEntry8a  2,myname            	; My sResource Name Offset
    OSLstEntry8a  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry8a  $A,minorbase        	; MinorBase Offset
    OSLstEntry8a  $B,minorlen8        	; MinorLength Offset
;    OSLstEntry8a  $40,gammadirectory    ; Gamma correction table directory
    OSLstEntry8a  $80,bits1parmlist0   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry8a  $81,bits2parmlist0   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry8a  $82,bits4parmlist0   	; Four-Bit-Per-Pixel Parameter List Offset
;;;    OSLstEntry8a  $83,bits8parmlist0   	; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 8b - 1600 x 1200 extended */
#asm
mysreslist8b
    OSLstEntry8b  1,mytype            	; My sResource Type Format Offset
    OSLstEntry8b  2,myname            	; My sResource Name Offset
    OSLstEntry8b  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry8b  $A,minorbase        	; MinorBase Offset
    OSLstEntry8b  $B,minorlen8        	; MinorLength Offset
;    OSLstEntry8b  $40,gammadirectory    ; Gamma correction table directory 
    OSLstEntry8b  $80,bits1parmlist6   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry8b  $81,bits2parmlist6   	; Two-Bit-Per-Pixel Parameter List Offset
;;;    OSLstEntry8b  $82,bits4parmlist6   	; Four-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 8c - 2304 x 1740 extended */
#asm
mysreslist8c
    OSLstEntry8c  1,mytype            	; My sResource Type Format Offset
    OSLstEntry8c  2,myname            	; My sResource Name Offset
    OSLstEntry8c  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry8c  $A,minorbase        	; MinorBase Offset
    OSLstEntry8c  $B,minorlen8        	; MinorLength Offset
;    OSLstEntry8c  $40,gammadirectory    ; Gamma correction table directory 
    OSLstEntry8c  $80,bits1parmlist4   	; One-Bit-Per-Pixel Parameter List Offset
;;;    OSLstEntry8c  $81,bits2parmlist4   	; Two-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 8d - 3200 x 2400 extended */
#asm
mysreslist8d
    OSLstEntry8d  1,mytype            	; My sResource Type Format Offset
    OSLstEntry8d  2,myname            	; My sResource Name Offset
    OSLstEntry8d  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry8d  $A,minorbase        	; MinorBase Offset
    OSLstEntry8d  $B,minorlen8        	; MinorLength Offset
;    OSLstEntry8d  $40,gammadirectory    ; Gamma correction table directory 
    OSLstEntry8d  $80,bits1parmlist5   	; One-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
#endif
/* Fat slot resources */
/* My sResource List 90 - 1152 X 870 */
#asm
mysreslist90
    OSLstEntry90  1,mytype            	; My sResource Type Format Offset
    OSLstEntry90  2,myname            	; My sResource Name Offset
    OSLstEntry90  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry90  $A,minorbase        	; MinorBase Offset
    OSLstEntry90  $B,minorlen9         	; MinorLength Offset
;    OSLstEntry    $40,gammadirectory    ; Gamma correction table directory
    OSLstEntry90  $80,bits1parmlist0   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry90  $81,bits2parmlist0   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry90  $82,bits4parmlist0   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry90  $83,bits8parmlist0   	; Eight-Bit-Per-Pixel Parameter List Offset
    OSLstEntry90  $84,bits16parmlist0  	; Sixteen-Bit-Per-Pixel Parameter List Offset
    OSLstEntry90  $85,bits24parmlist0  	; Twenty-Four-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 91 - 1024 X 768 75Hz */
#asm
mysreslist91
    OSLstEntry91  1,mytype            	; My sResource Type Format Offset
    OSLstEntry91  2,myname            	; My sResource Name Offset
    OSLstEntry91  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry91  $A,minorbase        	; MinorBase Offset
    OSLstEntry91  $B,minorlen9         	; MinorLength Offset
;    OSLstEntry    $40,gammadirectory    ; Gamma correction table directory
    OSLstEntry91  $80,bits1parmlist1   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry91  $81,bits2parmlist1   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry91  $82,bits4parmlist1   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry91  $83,bits8parmlist1   	; Eight-Bit-Per-Pixel Parameter List Offset
    OSLstEntry91  $84,bits16parmlist1  	; Sixteen-Bit-Per-Pixel Parameter List Offset
    OSLstEntry91  $85,bits24parmlist1  	; Twenty-Four-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 92 1024 X 768 60Hz */
#asm
mysreslist92
    OSLstEntry92  1,mytype            	; My sResource Type Format Offset
    OSLstEntry92  2,myname            	; My sResource Name Offset
    OSLstEntry92  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry92  $A,minorbase        	; MinorBase Offset
    OSLstEntry92  $B,minorlen9        	; MinorLength Offset
;    OSLstEntry92  $40,gammadirectory    ; Gamma correction table directory
    OSLstEntry92  $80,bits1parmlist1  	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry92  $81,bits2parmlist1  	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry92  $82,bits4parmlist1  	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry92  $83,bits8parmlist1  	; Eight-Bit-Per-Pixel Parameter List Offset
    OSLstEntry92  $84,bits16parmlist1  	; Sixteen-Bit-Per-Pixel Parameter List Offset
    OSLstEntry92  $85,bits24parmlist1 	; Twenty-Four-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 93 - 832 X 624 */
#asm
mysreslist93
    OSLstEntry93  1,mytype            	; My sResource Type Format Offset
    OSLstEntry93  2,myname            	; My sResource Name Offset
    OSLstEntry93  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry93  $A,minorbase        	; MinorBase Offset
    OSLstEntry93  $B,minorlen9        	; MinorLength Offset
;    OSLstEntry93  $40,gammadirectory    ; Gamma correction table directory
    OSLstEntry93  $80,bits1parmlist2   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry93  $81,bits2parmlist2   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry93  $82,bits4parmlist2   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry93  $83,bits8parmlist2   	; Eight-Bit-Per-Pixel Parameter List Offset
    OSLstEntry93  $84,bits16parmlist2  	; Sixteen-Bit-Per-Pixel Parameter List Offset
    OSLstEntry93  $85,bits24parmlist2  	; Twenty-Four-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 94 - 640 X 480 */
#asm
mysreslist94
mysreslist96
    OSLstEntry94  1,mytype            	; My sResource Type Format Offset
    OSLstEntry94  2,myname            	; My sResource Name Offset
    OSLstEntry94  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry94  $A,minorbase        	; MinorBase Offset
    OSLstEntry94  $B,minorlen9         	; MinorLength Offset
;    OSLstEntry94  $40,gammadirectory    ; Gamma correction table directory
    OSLstEntry94  $80,bits1parmlist3   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry94  $81,bits2parmlist3   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry94  $82,bits4parmlist3   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry94  $83,bits8parmlist3   	; Eight-Bit-Per-Pixel Parameter List Offset
    OSLstEntry94  $84,bits16parmlist3  	; Sixteen-Bit-Per-Pixel Parameter List Offset
    OSLstEntry94  $85,bits24parmlist3  	; Twenty-Four-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 95 -  640 X 870 */
#asm
mysreslist95
    OSLstEntry95  1,mytype            	; My sResource Type Format Offset
    OSLstEntry95  2,myname            	; My sResource Name Offset
    OSLstEntry95  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry95  $A,minorbase        	; MinorBase Offset
    OSLstEntry95  $B,minorlen9        	; MinorLength Offset
;    OSLstEntry95  $40,gammadirectory  	 ; Gamma correction table directory
    OSLstEntry95  $80,bits1parmlist7  	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry95  $81,bits2parmlist7  	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry95  $82,bits4parmlist7  	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry95  $83,bits8parmlist7  	; Eight-Bit-Per-Pixel Parameter List Offset
    OSLstEntry95  $84,bits16parmlist7  	; Sixteen-Bit-Per-Pixel Parameter List Offset
    OSLstEntry95  $85,bits24parmlist7 	; Twenty-Four-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 97 - 768 X 576 */
#asm
mysreslist97
    OSLstEntry97  1,mytype            	; My sResource Type Format Offset
    OSLstEntry97  2,myname            	; My sResource Name Offset
    OSLstEntry97  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry97  $A,minorbase        	; MinorBase Offset
    OSLstEntry97  $B,minorlen9         	; MinorLength Offset
;    OSLstEntry97  $40,gammadirectory   ; Gamma correction table directory
    OSLstEntry97  $80,bits1parmlist10   ; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry97  $81,bits2parmlist10   ; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry97  $82,bits4parmlist10   ; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry97  $83,bits8parmlist10   ; Eight-Bit-Per-Pixel Parameter List Offset
    OSLstEntry97  $84,bits16parmlist10  ; Sixteen-Bit-Per-Pixel Parameter List Offset
    OSLstEntry97  $85,bits24parmlist10  ; Twenty-Four-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 98 - 576 X 432 */
#asm
mysreslist98
    OSLstEntry98  1,mytype            	; My sResource Type Format Offset
    OSLstEntry98  2,myname            	; My sResource Name Offset
    OSLstEntry98  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry98  $A,minorbase        	; MinorBase Offset
    OSLstEntry98  $B,minorlen9         	; MinorLength Offset
;    OSLstEntry98  $40,gammadirectory    ; Gamma correction table directory
    OSLstEntry98  $80,bits1parmlist8   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry98  $81,bits2parmlist8   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry98  $82,bits4parmlist8   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry98  $83,bits8parmlist8   	; Eight-Bit-Per-Pixel Parameter List Offset
    OSLstEntry98  $84,bits16parmlist8  	; Sixteen-Bit-Per-Pixel Parameter List Offset
    OSLstEntry98  $85,bits24parmlist8  	; Twenty-Four-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 99 - 684 X 512 */
#asm
mysreslist99
    OSLstEntry99  1,mytype            	; My sResource Type Format Offset
    OSLstEntry99  2,myname            	; My sResource Name Offset
    OSLstEntry99  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry99  $A,minorbase        	; MinorBase Offset
    OSLstEntry99  $B,minorlen9         	; MinorLength Offset
;    OSLstEntry99  $40,gammadirectory    ; Gamma correction table directory
    OSLstEntry99  $80,bits1parmlist9   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry99  $81,bits2parmlist9   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry99  $82,bits4parmlist9   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntry99  $83,bits8parmlist9   	; Eight-Bit-Per-Pixel Parameter List Offset
    OSLstEntry99  $84,bits16parmlist9  	; Sixteen-Bit-Per-Pixel Parameter List Offset
    OSLstEntry99  $85,bits24parmlist9  	; Twenty-Four-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 9a - 1152 x 870 extended */
#asm
mysreslist9a
    OSLstEntry9a  1,mytype            	; My sResource Type Format Offset
    OSLstEntry9a  2,myname            	; My sResource Name Offset
    OSLstEntry9a  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry9a  $A,minorbase        	; MinorBase Offset
    OSLstEntry9a  $B,minorlen9        	; MinorLength Offset
;    OSLstEntry9a  $40,gammadirectory  	 ; Gamma correction table directory
    OSLstEntry9a  $80,bits1parmlist0  	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry9a  $81,bits2parmlist0  	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntry9a  $82,bits4parmlist0  	; Four-Bit-Per-Pixel Parameter List Offset
;;;    OSLstEntry9a  $83,bits8parmlist0  	; Eight-Bit-Per-Pixel Parameter List Offset
;;;    OSLstEntry9a  $84,bits16parmlist0  	; Sixteen-Bit-Per-Pixel Parameter List Offset
;;;    OSLstEntry9a  $85,bits24parmlist0 	; Twenty-Four-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 9b - 1600 x 1200 extended */
#asm
mysreslist9b
mysreslistab
    OSLstEntry9b  1,mytype            	; My sResource Type Format Offset
    OSLstEntry9b  2,myname            	; My sResource Name Offset
    OSLstEntry9b  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry9b  $A,minorbase        	; MinorBase Offset
    OSLstEntry9b  $B,minorlen9        	; MinorLength Offset
;    OSLstEntry9b  $40,gammadirectory  	 ; Gamma correction table directory
    OSLstEntry9b  $80,bits1parmlist6  	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntry9b  $81,bits2parmlist6  	; Two-Bit-Per-Pixel Parameter List Offset
;;;    OSLstEntry9b  $82,bits4parmlist6  	; Four-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 9c - 2304 x 1740 extended */
#asm
mysreslist9c
mysreslistac
    OSLstEntry9c  1,mytype            	; My sResource Type Format Offset
    OSLstEntry9c  2,myname            	; My sResource Name Offset
    OSLstEntry9c  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry9c  $A,minorbase        	; MinorBase Offset
    OSLstEntry9c  $B,minorlen9        	; MinorLength Offset
;    OSLstEntry9c  $40,gammadirectory  	 ; Gamma correction table directory
    OSLstEntry9c  $80,bits1parmlist4  	; One-Bit-Per-Pixel Parameter List Offset
;;;    OSLstEntry9c  $81,bits2parmlist4  	; Two-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List 9d - 3200 x 2400 extended */
#asm
mysreslist9d
mysreslistad
    OSLstEntry9d  1,mytype            	; My sResource Type Format Offset
    OSLstEntry9d  2,myname            	; My sResource Name Offset
    OSLstEntry9d  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntry9d  $A,minorbase        	; MinorBase Offset
    OSLstEntry9d  $B,minorlen9        	; MinorLength Offset
;    OSLstEntry9d  $40,gammadirectory  	 ; Gamma correction table directory
    OSLstEntry9d  $80,bits1parmlist5  	; One-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* Fat slot resources for 8bit board of 24Mxi */
/* My sResource List a0 - 1152 X 870 */
#asm
mysreslista0
    OSLstEntrya0  1,mytype            	; My sResource Type Format Offset
    OSLstEntrya0  2,myname            	; My sResource Name Offset
    OSLstEntrya0  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntrya0  $A,minorbase        	; MinorBase Offset
    OSLstEntrya0  $B,minorlen9         	; MinorLength Offset
;    OSLstEntry    $40,gammadirectory    ; Gamma correction table directory
    OSLstEntrya0  $80,bits1parmlist0   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya0  $81,bits2parmlist0   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya0  $82,bits4parmlist0   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya0  $83,bits8parmlist0   	; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List a1 - 1024 X 768 75Hz */
#asm
mysreslista1
    OSLstEntrya1  1,mytype            	; My sResource Type Format Offset
    OSLstEntrya1  2,myname            	; My sResource Name Offset
    OSLstEntrya1  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntrya1  $A,minorbase        	; MinorBase Offset
    OSLstEntrya1  $B,minorlen9         	; MinorLength Offset
;    OSLstEntry    $40,gammadirectory    ; Gamma correction table directory
    OSLstEntrya1  $80,bits1parmlist1   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya1  $81,bits2parmlist1   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya1  $82,bits4parmlist1   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya1  $83,bits8parmlist1   	; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List a2 1024 X 768 60Hz */
#asm
mysreslista2
    OSLstEntrya2  1,mytype            	; My sResource Type Format Offset
    OSLstEntrya2  2,myname            	; My sResource Name Offset
    OSLstEntrya2  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntrya2  $A,minorbase        	; MinorBase Offset
    OSLstEntrya2  $B,minorlen9        	; MinorLength Offset
;    OSLstEntrya2  $40,gammadirectory    ; Gamma correction table directory
    OSLstEntrya2  $80,bits1parmlist1  	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya2  $81,bits2parmlist1  	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya2  $82,bits4parmlist1  	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya2  $83,bits8parmlist1  	; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List a3 - 832 X 624 */
#asm
mysreslista3
    OSLstEntrya3  1,mytype            	; My sResource Type Format Offset
    OSLstEntrya3  2,myname            	; My sResource Name Offset
    OSLstEntrya3  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntrya3  $A,minorbase        	; MinorBase Offset
    OSLstEntrya3  $B,minorlen9        	; MinorLength Offset
;    OSLstEntrya3  $40,gammadirectory    ; Gamma correction table directory
    OSLstEntrya3  $80,bits1parmlist2   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya3  $81,bits2parmlist2   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya3  $82,bits4parmlist2   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya3  $83,bits8parmlist2   	; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List a4 - 640 X 480 */
#asm
mysreslista4
mysreslista6
    OSLstEntrya4  1,mytype            	; My sResource Type Format Offset
    OSLstEntrya4  2,myname            	; My sResource Name Offset
    OSLstEntrya4  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntrya4  $A,minorbase        	; MinorBase Offset
    OSLstEntrya4  $B,minorlen9         	; MinorLength Offset
;    OSLstEntrya4  $40,gammadirectory    ; Gamma correction table directory
    OSLstEntrya4  $80,bits1parmlist3   	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya4  $81,bits2parmlist3   	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya4  $82,bits4parmlist3   	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya4  $83,bits8parmlist3   	; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List a5 -  640 X 870 */
#asm
mysreslista5
    OSLstEntrya5  1,mytype            	; My sResource Type Format Offset
    OSLstEntrya5  2,myname            	; My sResource Name Offset
    OSLstEntrya5  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntrya5  $A,minorbase        	; MinorBase Offset
    OSLstEntrya5  $B,minorlen9        	; MinorLength Offset
;    OSLstEntrya5  $40,gammadirectory  	 ; Gamma correction table directory
    OSLstEntrya5  $80,bits1parmlist7  	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya5  $81,bits2parmlist7  	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya5  $82,bits4parmlist7  	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntrya5  $83,bits8parmlist7  	; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
/* My sResource List aa - 1152 x 870 */
#asm
mysreslista7	; non-existent, just fake it
mysreslista8	; non-existent, just fake it
mysreslista9	; non-existent, just fake it
mysreslistaa
    OSLstEntryaa  1,mytype            	; My sResource Type Format Offset
    OSLstEntryaa  2,myname            	; My sResource Name Offset
    OSLstEntryaa  4,mydrvrdir         	; My sResource Driver Directory Offset
    DatLstEntry   7,6                 	; sRsrcFlags - fOpenAtStart,f32BitMode
    DatLstEntry   8,1                 	; sRsrcHWDevId = 1
    OSLstEntryaa  $A,minorbase        	; MinorBase Offset
    OSLstEntryaa  $B,minorlen9        	; MinorLength Offset
;    OSLstEntryaa  $40,gammadirectory  	 ; Gamma correction table directory
    OSLstEntryaa  $80,bits1parmlist0  	; One-Bit-Per-Pixel Parameter List Offset
    OSLstEntryaa  $81,bits2parmlist0  	; Two-Bit-Per-Pixel Parameter List Offset
    OSLstEntryaa  $82,bits4parmlist0  	; Four-Bit-Per-Pixel Parameter List Offset
    OSLstEntryaa  $83,bits8parmlist0  	; Eight-Bit-Per-Pixel Parameter List Offset
    DatLstEntry   $FF,0               	; End
#endasm
#asm
;*************************************************************
;Constants
;*************************************************************
CatDisplay			EQU	$0003	; Display type of card
TypVideo			EQU	$0001	; Video type of display
DrSwApple			EQU	$0001	; Apple compatable software
DrSwAUX				EQU	$0003	; AUX compatable software
DrHwRasterOps24Mxi	EQU	$03DE	; Hardware ID - assigned by Apple (DTS)
DrHwRasterOps24MxTV	EQU	$03DF	; Hardware ID - assigned by Apple (DTS)
DrHwRasterOps24MxRGB	EQU	$03FF	; Hardware ID - assigned by Apple (DTS)
CB24MxiBoardId		EQU $0445	; Board ID - assigned by Apple (DTS)
CB24MxTVBoardId		EQU $0446	; Board ID - assigned by Apple (DTS)
CB24MxRGBBoardId	EQU $051E	; Board ID - assigned by Apple (DTS)
sMacOS68020			EQU	2		; Mac OS, CPU type = 68020
sAUX68020			EQU	3		; AUX OS, CPU type = 68020
allSlaveBlockSizes	EQU	$0000800F 	;
#endasm
#asm
 if  MAKING24MXI
CB24MxBoardId		EQU	CB24MxiBoardId		; Hardware ID - assigned by Apple (DTS)
DrHwRasterOps24Mx	EQU	DrHwRasterOps24Mxi	; Hardware ID - assigned by Apple (DTS)
 else
 	if MAKING24MXRGB
CB24MxBoardId		EQU	CB24MxRGBBoardId		; Hardware ID - assigned by Apple (DTS)
DrHwRasterOps24Mx	EQU	DrHwRasterOps24MxRGB	; Hardware ID - assigned by Apple (DTS)
	else
CB24MxBoardId		EQU	CB24MxTVBoardId		; Hardware ID - assigned by Apple (DTS)
DrHwRasterOps24Mx	EQU	DrHwRasterOps24MxTV	; Hardware ID - assigned by Apple (DTS)
	endc
 endc
#endasm
#if  MAKING24MXI
#define DrHwRasterOps24Mx	0x03DE
#define DrHw				0x03DE
#else
	#if MAKING24MXRGB
		#define DrHwRasterOps24Mx	0x03DF
		#define DrHw				0x03DF
	#else
		#define DrHwRasterOps24Mx	0x03FF
		#define DrHw				0x03FF
	#endif
#endif
/* My sResource Type Format */
#asm
mytype even
	dc.w	CatDisplay					; Category:  catDisplay
	dc.w	TypVideo					; Type:      typVideo
	dc.w	DrSwApple					; DrvrSw:    drSwApple
    dc.w	DrHwRasterOps24Mx			; DrvrHw	 RasterOps 24Mx
#endasm
/* My sResource Name */
#asm
myname
 if MAKING24MXI
	dc.b  'Display_Video_Apple_RasterOps24Mx'
 else
 	if MAKING24MXRGB
		dc.b  'Display_Video_Apple_RasterOps24MxRGB'
	else
		dc.b  'Display_Video_Apple_RasterOps24MxTV'
	endc
 endc
	dc.w  0								; For Alignment - ends the 'C' string
#endasm
/* MinorBase */
#asm
minorbase even
    dc.l  0        						; No offset from normal beginning of slot space
#endasm
/* MinorLength for Skinny Slots */
#asm
minorlen8
    dc.l  $80000   					; 0.5M of Video RAM
#endasm
/* MinorLength for Fat Slots */
#asm
minorlen9
    dc.l  $180000   					; 1.5M of Video RAM
#endasm
/* еееееееееееееееее 1152 X 870 еееееееееееееееееее */
/* One-Bit-Per-Pixel Parameter List */
#asm
bits1parmlist0
    OSLstEntry  1,bits1parms0     		; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bits1parms0
    dc.l  endbits1parms0-bits1parms0  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $240                      	; RowBytes 1152/2
    dc.l  0                         	; BoundsRect: (0,0,870,1152)
    dc.l  $03660480                 	;
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
endbits1parms0
#endasm
/* Two-Bit-Per-Pixel Parameter List */
#asm
bits2parmlist0
    OSLstEntry  1,bits2parms0     		; Two-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Two-Bit-Per-Pixel Parameters sBlock */
#asm
bits2parms0
    dc.l  endbits2parms0-bits2parms0  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $240                      	; RowBytes 1152/2
    dc.l  0                         	; BoundsRect: (0,0,870,1152)
    dc.l  $03660480                 	;
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
endbits2parms0
#endasm
/* Four-Bit-Per-Pixel Parameter List */
#asm
bits4parmlist0
    OSLstEntry  1,bits4parms0     		; Four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Four-Bit-Per-Pixel Parameters sBlock */
#asm
bits4parms0
    dc.l  endbits4parms0-bits4parms0  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $240                      	; RowBytes 1152/2
    dc.l  0                         	; BoundsRect: (0,0,870,1152)
    dc.l  $03660480                 	;
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
endbits4parms0
#endasm
/* Eight-Bit-Per-Pixel Parameter List */
#asm
bits8parmlist0
    OSLstEntry  1,bits8parms0    		; Eight-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Eight-Bit-Per-Pixel Parameters sBlock */
#asm
bits8parms0
    dc.l  endbits8parms0-bits8parms0  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $240                      	; RowBytes 1152/2
    dc.l  0                         	; BoundsRect: (0,0,870,1152)
    dc.l  $03660480                 	;
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
endbits8parms0
#endasm
/* Sixteen-Bit-Per-Pixel Parameter List */
#asm
bits16parmlist0
    OSLstEntry  1,bits16parms0    		; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,2              		; Device Type: 2 - DirectType
    DatLstEntry $FF,0            		; End
#endasm
/* Sixteen-Bit-Per-Pixel Parameters sBlock */
#asm
bits16parms0
    dc.l  endbits16parms0-bits16parms0  ; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $0680                     	; RowBytes 4608
    dc.l  0                         	; BoundsRect: (0,0,870,1152)
    dc.l  $03660480                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  $10                       	; Pixel Type ($10=ChunkyDirect)
    dc.w  16                       	 	; Pixel Size (must be power of 2)
    dc.w  3                         	; Components in Pixel
    dc.w  5                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits16parms0
#endasm
/* Twenty-four-Bit-Per-Pixel Parameter List */
#asm
bits24parmlist0
    OSLstEntry  1,bits24parms0    		; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,2              		; Device Type: 2 - DirectType
    DatLstEntry $FF,0            		; End
#endasm
/* Twenty-four-Bit-Per-Pixel Parameters sBlock */
#asm
bits24parms0
    dc.l  endbits24parms0-bits24parms0  ; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $0D00                     	; RowBytes 4608
    dc.l  0                         	; BoundsRect: (0,0,870,1152)
    dc.l  $03660480                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  $10                       	; Pixel Type ($10=ChunkyDirect)
    dc.w  32                       	 	; Pixel Size (must be power of 2)
    dc.w  3                         	; Components in Pixel
    dc.w  8                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits24parms0
#endasm
/* еееееееееееееееее 1024 X 768 еееееееееееееееееее */
/* One-Bit-Per-Pixel Parameter List */
#asm
bits1parmlist1
    OSLstEntry  1,bits1parms1     		; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bits1parms1
    dc.l  endbits1parms1-bits1parms1  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,768,1024)
    dc.l  $03000400                 	;
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
endbits1parms1
#endasm
/* Two-Bit-Per-Pixel Parameter List */
#asm
bits2parmlist1
    OSLstEntry  1,bits2parms1     		; Two-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Two-Bit-Per-Pixel Parameters sBlock */
#asm
bits2parms1
    dc.l  endbits2parms1-bits2parms1  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,768,1024)
    dc.l  $03000400                 	;
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
endbits2parms1
#endasm
/* Four-Bit-Per-Pixel Parameter List */
#asm
bits4parmlist1
    OSLstEntry  1,bits4parms1     		; Four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Four-Bit-Per-Pixel Parameters sBlock */
#asm
bits4parms1
    dc.l  endbits4parms1-bits4parms1  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,768,1024)
    dc.l  $03000400                 	;
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
endbits4parms1
#endasm
/* Eight-Bit-Per-Pixel Parameter List */
#asm
bits8parmlist1
    OSLstEntry  1,bits8parms1    		; Eight-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Eight-Bit-Per-Pixel Parameters sBlock */
#asm
bits8parms1
    dc.l  endbits8parms1-bits8parms1  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,768,1024)
    dc.l  $03000400                 	;
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
endbits8parms1
#endasm
/* Sixteen-Bit-Per-Pixel Parameter List */
#asm
bits16parmlist1
    OSLstEntry  1,bits16parms1    		; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,2              		; Device Type: 2 - DirectType
    DatLstEntry $FF,0            		; End
#endasm
/* Sixteen-Bit-Per-Pixel Parameters sBlock */
#asm
bits16parms1
    dc.l  endbits16parms1-bits16parms1  ; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $0680                     	; RowBytes 4608
    dc.l  0                         	; BoundsRect: (0,0,768,1024)
    dc.l  $03000400                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  $10                       	; Pixel Type ($10=ChunkyDirect)
    dc.w  16                       	 	; Pixel Size (must be power of 2)
    dc.w  3                         	; Components in Pixel
    dc.w  5                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits16parms1
#endasm
/* Twenty-four-Bit-Per-Pixel Parameter List */
#asm
bits24parmlist1
    OSLstEntry  1,bits24parms1    		; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,2              		; Device Type: 2 - DirectType
    DatLstEntry $FF,0            		; End
#endasm
/* Twenty-four-Bit-Per-Pixel Parameters sBlock */
#asm
bits24parms1
    dc.l  endbits24parms1-bits24parms1  ; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $0D00                     	; RowBytes 4608
    dc.l  0                         	; BoundsRect: (0,0,768,1024)
    dc.l  $03000400                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  $10                       	; Pixel Type ($10=ChunkyDirect)
    dc.w  32                       	 	; Pixel Size (must be power of 2)
    dc.w  3                         	; Components in Pixel
    dc.w  8                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits24parms1
#endasm
/* еееееееееееееееее 832 X 624 ееееееееееееееееееее */
/* One-Bit-Per-Pixel Parameter List */
#asm
bits1parmlist2
    OSLstEntry  1,bits1parms2     		; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bits1parms2
    dc.l  endbits1parms2-bits1parms2  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,624,832)
    dc.l  $02700340                 	;
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
endbits1parms2
#endasm
/* Two-Bit-Per-Pixel Parameter List */
#asm
bits2parmlist2
    OSLstEntry  1,bits2parms2     		; Two-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Two-Bit-Per-Pixel Parameters sBlock */
#asm
bits2parms2
    dc.l  endbits2parms2-bits2parms2  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,624,832)
    dc.l  $02700340                 	;
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
endbits2parms2
#endasm
/* Four-Bit-Per-Pixel Parameter List */
#asm
bits4parmlist2
    OSLstEntry  1,bits4parms2     		; Four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Four-Bit-Per-Pixel Parameters sBlock */
#asm
bits4parms2
    dc.l  endbits4parms2-bits4parms2  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,624,832)
    dc.l  $02700340                 	;
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
endbits4parms2
#endasm
/* Eight-Bit-Per-Pixel Parameter List */
#asm
bits8parmlist2
    OSLstEntry  1,bits8parms2    		; Eight-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Eight-Bit-Per-Pixel Parameters sBlock */
#asm
bits8parms2
    dc.l  endbits8parms2-bits8parms2  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,624,832)
    dc.l  $02700340                 	;
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
endbits8parms2
#endasm
/* Sixteen-Bit-Per-Pixel Parameter List */
#asm
bits16parmlist2
    OSLstEntry  1,bits16parms2    		; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,2              		; Device Type: 2 - DirectType
    DatLstEntry $FF,0            		; End
#endasm
/* Sixteen-Bit-Per-Pixel Parameters sBlock */
#asm
bits16parms2
    dc.l  endbits16parms2-bits16parms2  ; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $0680                     	; RowBytes 4608
    dc.l  0                         	; BoundsRect: (0,0,624,832)
    dc.l  $02700340                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  $10                       	; Pixel Type ($10=ChunkyDirect)
    dc.w  16                       	 	; Pixel Size (must be power of 2)
    dc.w  3                         	; Components in Pixel
    dc.w  5                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits16parms2
#endasm
/* Twenty-four-Bit-Per-Pixel Parameter List */
#asm
bits24parmlist2
    OSLstEntry  1,bits24parms2    		; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,2              		; Device Type: 2 - DirectType
    DatLstEntry $FF,0            		; End
#endasm
/* Twenty-four-Bit-Per-Pixel Parameters sBlock */
#asm
bits24parms2
    dc.l  endbits24parms2-bits24parms2  ; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $0D00                     	; RowBytes 4608
    dc.l  0                         	; BoundsRect: (0,0,624,832)
    dc.l  $02700340                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  $10                       	; Pixel Type ($10=ChunkyDirect)
    dc.w  32                        	; Pixel Size (must be power of 2)
    dc.w  3                         	; Components in Pixel
    dc.w  8                         	; Bits Per Component
    dc.l  0                    FFFFF	; PlaneBytes Offset
endbits24parms2
#endasm
/* еееееееееееееееее 640 X 480 ееееееееееееееееееее */
/* One-Bit-Per-Pixel Parameter List */
#asm
bits1parmlist3
    OSLstEntry  1,bits1parms3     		; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bits1parms3
    dc.l  endbits1parms3-bits1parms3  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,480,640)
    dc.l  $01E00280                 	;
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
endbits1parms3
#endasm
/* Two-Bit-Per-Pixel Parameter List */
#asm
bits2parmlist3
    OSLstEntry  1,bits2parms3     		; Two-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Two-Bit-Per-Pixel Parameters sBlock */
#asm
bits2parms3
    dc.l  endbits2parms3-bits2parms3  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,480,640)
    dc.l  $01E00280                 	;
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
endbits2parms3
#endasm
/* Four-Bit-Per-Pixel Parameter List */
#asm
bits4parmlist3
    OSLstEntry  1,bits4parms3     		; Four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Four-Bit-Per-Pixel Parameters sBlock */
#asm
bits4parms3
    dc.l  endbits4parms3-bits4parms3  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,480,640)
    dc.l  $01E00280                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  0                         	; Pixel Type (0=Chunky)
    dc.w  4                         	; Pixel Size
    dc.w  1                         	; Components in Pixel
    dc.w  4                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits4parms3
#endasm
/* Eight-Bit-Per-Pixel Parameter List */
#asm
bits8parmlist3
    OSLstEntry  1,bits8parms3    		; Eight-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Eight-Bit-Per-Pixel Parameters sBlock */
#asm
bits8parms3
    dc.l  endbits8parms3-bits8parms3  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,480,640)
    dc.l  $01E00280                 	;
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
endbits8parms3
#endasm
/* Sixteen-Bit-Per-Pixel Parameter List */
#asm
bits16parmlist3
    OSLstEntry  1,bits16parms3    		; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,2              		; Device Type: 2 - DirectType
    DatLstEntry $FF,0            		; End
#endasm
/* Sixteen-Bit-Per-Pixel Parameters sBlock */
#asm
bits16parms3
    dc.l  endbits16parms3-bits16parms3  ; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $0680                     	; RowBytes 4608
    dc.l  0                         	; BoundsRect: (0,0,480,640)
    dc.l  $01E00280                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  $10                       	; Pixel Type ($10=ChunkyDirect)
    dc.w  16                       	 	; Pixel Size (must be power of 2)
    dc.w  3                         	; Components in Pixel
    dc.w  5                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits16parms3
#endasm
/* Twenty-four-Bit-Per-Pixel Parameter List */
#asm
bits24parmlist3
    OSLstEntry  1,bits24parms3    		; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,2              		; Device Type: 2 - DirectType
    DatLstEntry $FF,0            		; End
#endasm
/* Twenty-four-Bit-Per-Pixel Parameters sBlock */
#asm
bits24parms3
    dc.l  endbits24parms3-bits24parms3  ; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $0D00                     	; RowBytes 4608
    dc.l  0                         	; BoundsRect: (0,0,480,640)
    dc.l  $01E00280                 	;
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
endbits24parms3
#endasm
/* еееееееееееееееее 640 X 870 ееееееееееееееееееее */
/* One-Bit-Per-Pixel Parameter List */
#asm
bits1parmlist7
    OSLstEntry  1,bits1parms7     		; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bits1parms7
    dc.l  endbits1parms7-bits1parms7  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,480,640)
    dc.l  $03660280                 	;
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
endbits1parms7
#endasm
/* Two-Bit-Per-Pixel Parameter List */
#asm
bits2parmlist7
    OSLstEntry  1,bits2parms7     		; Two-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Two-Bit-Per-Pixel Parameters sBlock */
#asm
bits2parms7
    dc.l  endbits2parms7-bits2parms7  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,480,640)
    dc.l  $03660280                 	;
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
endbits2parms7
#endasm
/* Four-Bit-Per-Pixel Parameter List */
#asm
bits4parmlist7
    OSLstEntry  1,bits4parms7     		; Four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Four-Bit-Per-Pixel Parameters sBlock */
#asm
bits4parms7
    dc.l  endbits4parms7-bits4parms7  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,480,640)
    dc.l  $03660280                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  0                         	; Pixel Type (0=Chunky)
    dc.w  4                         	; Pixel Size
    dc.w  1                         	; Components in Pixel
    dc.w  4                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits4parms7
#endasm
/* Eight-Bit-Per-Pixel Parameter List */
#asm
bits8parmlist7
    OSLstEntry  1,bits8parms7    		; Eight-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Eight-Bit-Per-Pixel Parameters sBlock */
#asm
bits8parms7
    dc.l  endbits8parms7-bits8parms7  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,480,640)
    dc.l  $03660280                 	;
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
endbits8parms7
#endasm
/* Sixteen-Bit-Per-Pixel Parameter List */
#asm
bits16parmlist7
    OSLstEntry  1,bits16parms7    		; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,2              		; Device Type: 2 - DirectType
    DatLstEntry $FF,0            		; End
#endasm
/* Sixteen-Bit-Per-Pixel Parameters sBlock */
#asm
bits16parms7
    dc.l  endbits16parms7-bits16parms7  ; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $0680                     	; RowBytes 4608
    dc.l  0                         	; BoundsRect: (0,0,480,640)
    dc.l  $03660280                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  $10                       	; Pixel Type ($10=ChunkyDirect)
    dc.w  16                       	 	; Pixel Size (must be power of 2)
    dc.w  3                         	; Components in Pixel
    dc.w  5                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits16parms7
#endasm
/* Twenty-four-Bit-Per-Pixel Parameter List */
#asm
bits24parmlist7
    OSLstEntry  1,bits24parms7    		; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,2              		; Device Type: 2 - DirectType
    DatLstEntry $FF,0            		; End
#endasm
/* Twenty-four-Bit-Per-Pixel Parameters sBlock */
#asm
bits24parms7
    dc.l  endbits24parms7-bits24parms7  ; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $0D00                     	; RowBytes 4608
    dc.l  0                         	; BoundsRect: (0,0,480,640)
    dc.l  $03660280                 	;
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
endbits24parms7
#endasm
/* еееееееееееееееее 576 X 432 ntsc underscan ееееееееееееееееееее */
/* One-Bit-Per-Pixel Parameter List */
#asm
bits1parmlist8
    OSLstEntry  1,bits1parms8     		; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bits1parms8
    dc.l  endbits1parms8-bits1parms8  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
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
endbits1parms8
#endasm
/* Two-Bit-Per-Pixel Parameter List */
#asm
bits2parmlist8
    OSLstEntry  1,bits2parms8     		; Two-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Two-Bit-Per-Pixel Parameters sBlock */
#asm
bits2parms8
    dc.l  endbits2parms8-bits2parms8  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
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
endbits2parms8
#endasm
/* Four-Bit-Per-Pixel Parameter List */
#asm
bits4parmlist8
    OSLstEntry  1,bits4parms8     		; Four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Four-Bit-Per-Pixel Parameters sBlock */
#asm
bits4parms8
    dc.l  endbits4parms8-bits4parms8  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,432,576)
    dc.l  $01B00240                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  0                         	; Pixel Type (0=Chunky)
    dc.w  4                         	; Pixel Size
    dc.w  1                         	; Components in Pixel
    dc.w  4                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits4parms8
#endasm
/* Eight-Bit-Per-Pixel Parameter List */
#asm
bits8parmlist8
    OSLstEntry  1,bits8parms8    		; Eight-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Eight-Bit-Per-Pixel Parameters sBlock */
#asm
bits8parms8
    dc.l  endbits8parms8-bits8parms8  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
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
endbits8parms8
#endasm
/* Sixteen-Bit-Per-Pixel Parameter List */
#asm
bits16parmlist8
    OSLstEntry  1,bits16parms8    		; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,2              		; Device Type: 2 - DirectType
    DatLstEntry $FF,0            		; End
#endasm
/* Sixteen-Bit-Per-Pixel Parameters sBlock */
#asm
bits16parms8
    dc.l  endbits16parms8-bits16parms8  ; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $0680                     	; RowBytes 4608
    dc.l  0                         	; BoundsRect: (0,0,432,576)
    dc.l  $01B00240                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  $10                       	; Pixel Type ($10=ChunkyDirect)
    dc.w  16                       	 	; Pixel Size (must be power of 2)
    dc.w  3                         	; Components in Pixel
    dc.w  5                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits16parms8
#endasm
/* Twenty-four-Bit-Per-Pixel Parameter List */
#asm
bits24parmlist8
    OSLstEntry  1,bits24parms8    		; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,2              		; Device Type: 2 - DirectType
    DatLstEntry $FF,0            		; End
#endasm
/* Twenty-four-Bit-Per-Pixel Parameters sBlock */
#asm
bits24parms8
    dc.l  endbits24parms8-bits24parms8  ; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $0D00                     	; RowBytes 4608
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
endbits24parms8
#endasm
/* еееееееееееееееее 684 X 512 pal underscan ееееееееееееееееееее */
/* One-Bit-Per-Pixel Parameter List */
#asm
bits1parmlist9
    OSLstEntry  1,bits1parms9     		; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bits1parms9
    dc.l  endbits1parms9-bits1parms9  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,512,684)
    dc.l  $020002AC                 	;
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
endbits1parms9
#endasm
/* Two-Bit-Per-Pixel Parameter List */
#asm
bits2parmlist9
    OSLstEntry  1,bits2parms9     		; Two-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Two-Bit-Per-Pixel Parameters sBlock */
#asm
bits2parms9
    dc.l  endbits2parms9-bits2parms9  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,512,684)
    dc.l  $020002AC                 	;
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
endbits2parms9
#endasm
/* Four-Bit-Per-Pixel Parameter List */
#asm
bits4parmlist9
    OSLstEntry  1,bits4parms9     		; Four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Four-Bit-Per-Pixel Parameters sBlock */
#asm
bits4parms9
    dc.l  endbits4parms9-bits4parms9  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,512,684)
    dc.l  $020002AC                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  0                         	; Pixel Type (0=Chunky)
    dc.w  4                         	; Pixel Size
    dc.w  1                         	; Components in Pixel
    dc.w  4                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits4parms9
#endasm
/* Eight-Bit-Per-Pixel Parameter List */
#asm
bits8parmlist9
    OSLstEntry  1,bits8parms9    		; Eight-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Eight-Bit-Per-Pixel Parameters sBlock */
#asm
bits8parms9
    dc.l  endbits8parms9-bits8parms9  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,512,684)
    dc.l  $020002AC                 	;
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
endbits8parms9
#endasm
/* Sixteen-Bit-Per-Pixel Parameter List */
#asm
bits16parmlist9
    OSLstEntry  1,bits16parms9    		; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,2              		; Device Type: 2 - DirectType
    DatLstEntry $FF,0            		; End
#endasm
/* Sixteen-Bit-Per-Pixel Parameters sBlock */
#asm
bits16parms9
    dc.l  endbits16parms9-bits16parms9  ; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $0680                     	; RowBytes 4608
    dc.l  0                         	; BoundsRect: (0,0,512,684)
    dc.l  $020002AC                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  $10                       	; Pixel Type ($10=ChunkyDirect)
    dc.w  16                       	 	; Pixel Size (must be power of 2)
    dc.w  3                         	; Components in Pixel
    dc.w  5                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits16parms9
#endasm
/* Twenty-four-Bit-Per-Pixel Parameter List */
#asm
bits24parmlist9
    OSLstEntry  1,bits24parms9    		; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,2              		; Device Type: 2 - DirectType
    DatLstEntry $FF,0            		; End
#endasm
/* Twenty-four-Bit-Per-Pixel Parameters sBlock */
#asm
bits24parms9
    dc.l  endbits24parms9-bits24parms9  ; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $0D00                     	; RowBytes 4608
    dc.l  0                         	; BoundsRect: (0,0,512,684)
    dc.l  $020002AC                 	;
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
endbits24parms9
#endasm
/* еееееееееееееееее 768 X 576 pal  ееееееееееееееееееее */
/* One-Bit-Per-Pixel Parameter List */
#asm
bits1parmlist10
    OSLstEntry  1,bits1parms10     		; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bits1parms10
    dc.l  endbits1parms10-bits1parms10  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,576,768)
    dc.l  $02400300                 	;
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
endbits1parms10
#endasm
/* Two-Bit-Per-Pixel Parameter List */
#asm
bits2parmlist10
    OSLstEntry  1,bits2parms10     		; Two-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Two-Bit-Per-Pixel Parameters sBlock */
#asm
bits2parms10
    dc.l  endbits2parms10-bits2parms10  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,576,768)
    dc.l  $02400300                 	;
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
endbits2parms10
#endasm
/* Four-Bit-Per-Pixel Parameter List */
#asm
bits4parmlist10
    OSLstEntry  1,bits4parms10     		; Four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Four-Bit-Per-Pixel Parameters sBlock */
#asm
bits4parms10
    dc.l  endbits4parms10-bits4parms10  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,576,768)
    dc.l  $02400300                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  0                         	; Pixel Type (0=Chunky)
    dc.w  4                         	; Pixel Size
    dc.w  1                         	; Components in Pixel
    dc.w  4                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits4parms10
#endasm
/* Eight-Bit-Per-Pixel Parameter List */
#asm
bits8parmlist10
    OSLstEntry  1,bits8parms10    		; Eight-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Eight-Bit-Per-Pixel Parameters sBlock */
#asm
bits8parms10
    dc.l  endbits8parms10-bits8parms10  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $340                      	; RowBytes 1152
    dc.l  0                         	; BoundsRect: (0,0,576,768)
    dc.l  $02400300                 	;
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
endbits8parms10
#endasm
/* Sixteen-Bit-Per-Pixel Parameter List */
#asm
bits16parmlist10
    OSLstEntry  1,bits16parms10    		; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,2              		; Device Type: 2 - DirectType
    DatLstEntry $FF,0            		; End
#endasm
/* Sixteen-Bit-Per-Pixel Parameters sBlock */
#asm
bits16parms10
    dc.l  endbits16parms10-bits16parms10  ; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $0680                     	; RowBytes 4608
    dc.l  0                         	; BoundsRect: (0,0,576,768)
    dc.l  $02400300                 	;
    dc.w  0                         	; PixMap Version Number
    dc.w  0                         	; unused
    dc.l  0                         	; unused (normally, but we're going to use it for our 24-bit environment flags)
    dc.l  $00480000                 	; Horizontal Res
    dc.l  $00480000                 	; Vertical Res
    dc.w  $10                       	; Pixel Type ($10=ChunkyDirect)
    dc.w  16                       	 	; Pixel Size (must be power of 2)
    dc.w  3                         	; Components in Pixel
    dc.w  5                         	; Bits Per Component
    dc.l  0                         	; PlaneBytes Offset
endbits16parms10
#endasm
/* Twenty-four-Bit-Per-Pixel Parameter List */
#asm
bits24parmlist10
    OSLstEntry  1,bits24parms10    		; Twenty-four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,2              		; Device Type: 2 - DirectType
    DatLstEntry $FF,0            		; End
#endasm
/* Twenty-four-Bit-Per-Pixel Parameters sBlock */
#asm
bits24parms10
    dc.l  endbits24parms10-bits24parms10  ; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $0D00                     	; RowBytes 4608
    dc.l  0                         	; BoundsRect: (0,0,576,768)
    dc.l  $02400300                 	;
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
endbits24parms10
#endasm
/* еееееееееееееееее 1600 x 1200 ееееееееееееееееееее */
/* One-Bit-Per-Pixel Parameter List */
#asm
bits1parmlist6
    OSLstEntry  1,bits1parms6			; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bits1parms6
    dc.l  endbits1parms6-bits1parms6  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $190                      	; RowBytes 400
    dc.l  0                         	; BoundsRect: (0,0,1200,1600)
    dc.l  $04B00640                 	;
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
endbits1parms6
#endasm
/* Two-Bit-Per-Pixel Parameter List */
#asm
bits2parmlist6
    OSLstEntry  1,bits2parms6     		; Two-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Two-Bit-Per-Pixel Parameters sBlock */
#asm
bits2parms6
    dc.l  endbits2parms6-bits2parms6  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $190                      	; RowBytes 400
    dc.l  0                         	; BoundsRect: (0,0,1200,1600)
    dc.l  $04B00640                 	;
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
endbits2parms6
#endasm
/* Four-Bit-Per-Pixel Parameter List */
#asm
bits4parmlist6
    OSLstEntry  1,bits4parms6     		; Four-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* Four-Bit-Per-Pixel Parameters sBlock */
#asm
bits4parms6
    dc.l  endbits4parms6-bits4parms6  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $190                      	; RowBytes 400
    dc.l  0                         	; BoundsRect: (0,0,1200,1600)
    dc.l  $04B00640                 	;
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
endbits4parms6
#endasm
/* еееееееееееееееее 2304 x 1740 ееееееееееееееееееее */
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
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $120                      	; RowBytes 288
    dc.l  0                         	; BoundsRect: (0,0,1740,2304)
    dc.l  $06CC0900                 	;
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
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $120                      	; RowBytes 288
    dc.l  0                         	; BoundsRect: (0,0,1740,2304)
    dc.l  $06CC0900                 	;
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
/* еееееееееее 3200 x 2400 еееееееееее */
/* One-Bit-Per-Pixel Parameter List */
#asm
bits1parmlist5
    OSLstEntry  1,bits1parms5     		; One-Bit-Per-Pixel Parameters sBlock Offset
    DatLstEntry 3,1              		; Number of Pages: 1
    DatLstEntry 4,0              		; Device Type: 0
    DatLstEntry $FF,0            		; End
#endasm
/* One-Bit-Per-Pixel Parameters sBlock */
#asm
bits1parms5
    dc.l  endbits1parms5-bits1parms5  	; Length of sBlock
    dc.l  0                         	; Offset to Page 0 of Video RAM: 0
    dc.w  $190                      	; RowBytes 400
    dc.l  0                         	; BoundsRect: (0,0,2400, 3200)
    dc.l  $09600C80                 	;
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
endbits1parms5
#endasm
/*______________________________________________________________________________*/
/* My sResource Gamma Directory */
/*______________________________________________________________________________*/
#asm
gammadirectory
    OSLstEntry  $80,mygamma         ; My ID 80 Gamma Table sBlock Offset
    DatLstEntry $FF,0               ; End
#endasm
/* My 68020 Driver sBlock */
#asm
mygamma
; ==================BEGINNING OF GAMMA BLOCK=====================
    dc.l  endmygamma-mygamma          ; Length of sBlock
#endasm
#asm
	DC.W	0			; Local ID
 if MAKING24MXI
    DC.B	'RasterOps 24Mx'		; Mode Name
 else
 	if MAKING24MXRGB
 		DC.B	'RasterOps 24MxRGB'		; Mode Name
	else
 		DC.B	'RasterOps 24MxTV'		; Mode Name
	endc
 endc
 	DC.B	0			; end C String
	DC.W	0			; gVersion 0
    DC.W	DrHwRasterOps24Mx	;
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
/*______________________________________________________________________________*/
/* My sResource Driver Directory */
#asm
mydrvrdir
    OSLstEntry  2,mydrvr            ; My 68020 Driver sBlock Offset
    DatLstEntry $FF,0               ; End
#endasm
