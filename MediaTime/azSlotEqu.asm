; Version: 1.05
; Created: Friday, October 21, 1988 at 5:15:35 PM
;
; File: SlotEqu.a
;
; Assembler Interface to the Macintosh Libraries
; Copyright Apple Computer, Inc. 1986-1988
; All Rights Reserved
;
;--------------------------------------------------------------------
; sInfo Array status flags (StatusFlags).
fCardIsChanged	EQU 		$01 					;Card is Changed field in StatusFlags field of sInfoArray
; spBlock flags (spFlags).
fCkForNext		EQU 		$00 					;For SearchSRT. Flag to check for NEXT sResource in the table.
fCkReserved 	EQU 		$01 					;For ReadPBSize. Flag to check reserved field for zero.
fWarmStart		EQU 		$02 					;If this bit is set then warm start, else cold start.
fClear			EQU 		$03 					;If this bit is set then clear the memory
fSys			EQU 		$04 					;If this bit is set then allocate memory on the system heap.
fConsecBytes	EQU 		$05 					;If this bit is set then Calculate step value for consecutive bytes.
; sResource flags (sRsrc_Flags).
fOpenAtStart	EQU 		$01 					;If this bit is set then open the driver at start time, else do not.
f32BitMode		EQU 		$02 					;If this bit is set then a 32-bit address will be put into dctlDevBase.
;State constants
stateNil		EQU 		0						;State :Nil
stateSDMInit	EQU 		1						; :Slot declaration manager Init
statePRAMInit	EQU 		2						; :sPRAM record init
statePInit		EQU 		3						; :Primary init
stateSInit		EQU 		4						; :Secondary init
;Misc constants 
sizeSPRAMRec	EQU 		8						;Size of sPRAM record
smPRAMTop		EQU 		$46 					;Address of top of slot mgr PRAM area.
sNumSlots		EQU 		6						;number of slots
sFirstSlot		EQU 		$9						;First slot
sLastSlot		EQU 		sFirstSlot+sNumSlots-1	  ;The last slot.
LastSlot		EQU 		$E						; last valid NuMac slot
lastSDMSelt 	EQU 		$34 					;The last SDM selector.
slotQSize		EQU 		6						; # of slots to support
;Data Structures
;SlotIntQElement
sqLink			EQU			0						; Ptr - ptr to next element
sqType			EQU			4						; INTEGER - queue type ID for validity
sqPrio			EQU			6						; INTEGER - priority
sqAddr			EQU			8						; ProcPtr - interrupt service routine
sqParm			EQU			12						; LONGINT - optional A1 parameter
sqHDSize		EQU 		16						; size of slot queue header element
;SpBlock 											;SDM parameter block.
spResult		EQU 		0						; FUNCTION Result. [Used by: every function]
spSPointer		EQU 		4						; Structure pointer (A structure is a list, long, logical block, ...)
spSize			EQU 		8						; Size of structure
spOffsetData	EQU 		12						; Offset/Data field. [Used by:sOffsetData]
spIOFileName	EQU 		16						; Pointer to IOFile name. [Used by sDisDrvrName]
spSExecPBlk 	EQU 		20						; Pointer to sExec parameter block. <C468>
spStackPtr		EQU 		24						; Old Stack pointer. <C468>
spParamData		EQU 		24						; Was Old Stack pointer. Replaced by ParamData (a long)
spMisc			EQU 		28						; Misc field for SDM. <C468>
spReserved		EQU 		32						; Reserved for future expansion
spIOReserved	EQU 		36						; Reserved field of Slot Resource Table <C663>
spRefNum		EQU 		38						; RefNum
spCategory		EQU 		40						; sType: Category <C663>
spCType 		EQU 		42						; Type <C663>
spDrvrSW		EQU 		44						; DrvrSW <C663>
spDrvrHW		EQU 		46						; DrvrHW <C663>
spTBMask		EQU 		48						; Type bit mask (Bits 0..3 determine which words 0..3 to mask). <C663>
spSlot			EQU 		49						; Slot number.
spId			EQU 		50						; Structure Id.
spExtDev		EQU 		51						; Id of the external device.
spHwDev 		EQU 		52						; Id of the hardware device.
spByteLanes 	EQU 		53						; Bytelanes value from FHeader in the declaration ROM.
spFlags 		EQU 		54						; Flags passed to various routine which require them (sSearchSRT,_InitSDeclMgr,...
spKey			EQU 		55						; Internal use only.
spBlockSize 	EQU 		56						; Size of spBlock
;--- Record data types
;SInfoRecord 										;Slot information record. sInfo Array[1..NumSlots]
siDirPtr		DS.L		0						; Pointer to directory
siInitStatusA	DS.W		4						; Fundamental Error
siInitStatusV	DS.W		6						; Status returned by vendor Init code
siState 		DS.B		8						; Initialization State (Primary, Secondary)
siCPUByteLanes	DS.B		9						; CPU Byte Lanes. Each bit set signifies a byte-lane used.
siTopOfROM		DS.B		10						; Top of ROM = $FssFFFFx, where x is TopOfROM.
siStatusFlags	DS.B		11						; Bit-0:Card is changed
siTOConst		DS.W		12						; Time Out Constant for BusErr
siReserved		DS.B		14						; Reserved, must be 0
sInfoRecSize	EQU 		16						; Size of sInfoRecord
;SDMRecord											;SDM information record. sInfo Array[0]
sdBEVSave		EQU 		0						; Save old BusErr vector.
sdBusErrProc	EQU 		4						; Go here to determine if it is a BusErr.
sdErrorEntry	EQU 		8						; Go here if BusErrProc determines it is really a BusErr.
sdReserved		EQU 		12						; Reserved
sdRecSize		EQU 		16						; Size of SDM information Record.
;FHeaderRec
fhDirOffset 	EQU 		0						;Offset to directory
fhLength		EQU 		4						;Length of ROM
fhCRC			EQU 		8						;CRC
fhROMRev		EQU 		12						;Revision of ROM
fhFormat		EQU 		13						;Format-2
fhTstPat		EQU 		14						;TestPattern
fhReserved		EQU 		18						;Reserved
fhByteLanes 	EQU 		19						;ByteLanes
fhBlockSize 	EQU 		20
;SEBlock 											;Parameter block for code executed by sExec.
;------- elements of all seBlocks ------
seSlot			EQU			0						; Slot number.
seSRsrcId		EQU			1						; sResource Id.
seStatus		EQU			2						; Status of code executed by sExec.
seFlags 		EQU			4						; Flags.
seFiller0		EQU			5						; Filler
seFiller1		EQU			6						; Filler
seFiller2		EQU			7						; Filler
;------- extensions for sLoad + sBoot ------
seResult		EQU			8						; Result of sLoad.
seIOFileName	EQU			12						; Pointer to IOFile name.
seDevice		EQU			16						; Which device to read from.
sePartition 	EQU			17						; The partition.
seOSType		EQU			18						; Type of OS.
seReserved		EQU			19						; Reserved field.
seRefNum		EQU			20						; RefNum of the driver.
;------- extensions for sBoot ------
seNumDevices	EQU			21						; Number of devices to load.
seBootState 	EQU			22						; State of StartBoot code.
seBlockSize 	EQU 		24						; Size of se parameter Block
;SPRAM
boardID			EQU			0						; Apple defined card identification
vendorUse1		EQU			2						; vendorUse5 byte Offset in pRAM record
vendorUse2		EQU			3						; vendorUse6 byte Offset in pRAM record
vendorUse3		EQU			4						; vendorUse5 byte Offset in pRAM record
vendorUse4		EQU			5						; vendorUse6 byte Offset in pRAM record
vendorUse5		EQU			6						; vendorUse5 byte Offset in pRAM record
vendorUse6		EQU			7						; vendorUse6 byte Offset in pRAM record
; Slot Manager Selectors:
;
; PRINCIPLE
sReadByte		EQU 		$00
sReadWord		EQU 		$01
sReadLong		EQU 		$02
sGetCString 	EQU 		$03
sGetBlock		EQU 		$05
sFindStruct 	EQU 		$06
sReadStruct 	EQU 		$07
; SPECIAL
sReadInfo		EQU 		$10
sReadPRAMRec	EQU 		$11
sPutPRAMRec 	EQU 		$12
sReadFHeader	EQU 		$13
sNextSRsrc		EQU 		$14
sNextTypeSRsrc	EQU 		$15
sRsrcInfo		EQU 		$16
sDisposePtr 	EQU 		$17
sCkCardStat 	EQU 		$18
sReadDrvrName	EQU 		$19
sFindDevBase	EQU 		$1B
sFindBigDevBase   EQU		$1C
; Advanced
initSDeclMgr	EQU 		$20
sPrimaryInit	EQU 		$21
sCardChanged	EQU 		$22
sExec			EQU 		$23
sOffsetData 	EQU 		$24
sInitPRAMRecs	EQU 		$25
sReadPBSize 	EQU 		$26
sCalcStep		EQU 		$28
sInitSRsrcTable   EQU		$29
sSearchSRT		EQU 		$2A
sUpdateSRT		EQU 		$2B
sCalcSPointer	EQU 		$2C
sGetDriver		EQU 		$2D
sPtrToSlot		EQU 		$2E
sFindSInfoRecPtr  EQU		$2F
sFindSRsrcPtr	EQU 		$30
sDeleteSRTRec	EQU 		$31
; 32-Bit Quickdraw
sVersion		EQU			$08
SetsRsrcState	EQU			$09
InsertSRTRec	EQU			$0A
sInsertSRTRec	EQU			$0A		; to match Wade's
GetsRsrc		EQU			$0B
GetTypesRsrc	EQU			$0C
;				MACRO		_SlotManager			
;				DC.W		$A06E
;				ENDM
;#####################################################################
; PRINCIPLE
;#####################################################################
				MACRO	_SReadByte
				MOVEQ		#sReadByte,D0
				_SlotManager
				ENDM
				MACRO	_SReadWord
				MOVEQ		#sReadWord,D0
				_SlotManager
				ENDM
				MACRO	_SReadLong
				MOVEQ		#sReadLong,D0
				_SlotManager
				ENDM
				MACRO	_SGetCString
				MOVEQ		#sGetCString,D0
				_SlotManager
				ENDM
				MACRO	_SGetBlock
				MOVEQ		#sGetBlock,D0
				_SlotManager
				ENDM
				MACRO	_SFindStruct
				MOVEQ		#sFindStruct,D0
				_SlotManager
				ENDM
				MACRO	_SReadStruct
				MOVEQ		#sReadStruct,D0
				_SlotManager
				ENDM
;#####################################################################
; SPECIAL
;#####################################################################
				MACRO	_SReadInfo
				MOVEQ		#sReadInfo,D0
				_SlotManager
				ENDM
				MACRO	_SReadPRAMRec
				MOVEQ		#sReadPRAMRec,D0
				_SlotManager
				ENDM
				MACRO	_SPutPRAMRec
				MOVEQ		#sPutPRAMRec,D0
				_SlotManager
				ENDM
				MACRO	_SReadFHeader
				MOVEQ		#sReadFHeader,D0
				_SlotManager
				ENDM
				MACRO	_SNextSRsrc
				MOVEQ		#sNextsRsrc,D0
				_SlotManager
				ENDM
				MACRO	_SNextTypeSRsrc
				MOVEQ		#sNextTypeSRsrc,D0
				_SlotManager
				ENDM
				MACRO	_SRsrcInfo
				MOVEQ		#sRsrcInfo,D0
				_SlotManager
				ENDM
				MACRO	_SDisposePtr
				MOVEQ		#sDisposePtr,D0
				_SlotManager
				ENDM
				MACRO	_SCkCardStat
				MOVEQ		#sCkCardStat,D0
				_SlotManager
				ENDM
				MACRO	_SReadDrvrName
				MOVEQ		#sReadDrvrName,D0
				_SlotManager
				ENDM
				MACRO	_SFindDevBase
				MOVEQ		#sFindDevBase,D0
				_SlotManager
				ENDM
				MACRO	_SFindBigDevBase
				MOVEQ		#sFindBigDevBase,D0
				_SlotManager
				ENDM
;#####################################################################
; Advanced
;#####################################################################
				MACRO	_InitSDeclMgr
				MOVEQ		#initSDeclMgr,D0
				_SlotManager
				ENDM
				MACRO	_SPrimaryInit
				MOVEQ		#sPrimaryInit,D0
				_SlotManager
				ENDM
				MACRO	_SCardChanged
				MOVEQ		#sCardChanged,D0
				_SlotManager
				ENDM
				MACRO	_SExec
				MOVEQ		#sExec,D0
				_SlotManager
				ENDM
				MACRO	_SOffsetData
				MOVEQ		#sOffsetData,D0
				_SlotManager
				ENDM
				MACRO	_SInitPRAMRecs
				MOVEQ		#sInitPRAMRecs,D0
				_SlotManager
				ENDM
				MACRO	_SReadPBSize
				MOVEQ		#sReadPBSize,D0
				_SlotManager
				ENDM
				MACRO	_SCalcStep
				MOVEQ		#sCalcStep,D0
				_SlotManager
				ENDM
				MACRO	_SInitSRsrcTable
				MOVEQ		#sInitSRsrcTable,D0
				_SlotManager
				ENDM
				MACRO	_SSearchSRT
				MOVEQ		#sSearchSRT,D0
				_SlotManager
				ENDM
				MACRO	_SUpdateSRT
				MOVEQ		#sUpdateSRT,D0
				_SlotManager
				ENDM
				MACRO	_SCalcSPointer
				MOVEQ		#sCalcSPointer,D0
				_SlotManager
				ENDM
				MACRO	_SGetDriver
				MOVEQ		#sGetDriver,D0
				_SlotManager
				ENDM
				MACRO	_SPtrToSlot
				MOVEQ		#sPtrToSlot,D0
				_SlotManager
				ENDM
				MACRO	_SFindSInfoRecPtr
				MOVEQ		#sFindSInfoRecPtr,D0
				_SlotManager
				ENDM
				MACRO	_SFindSRsrcPtr
				MOVEQ		#sFindSRsrcPtr,D0
				_SlotManager
				ENDM
				MACRO	_SDeleteSRTRec
				MOVEQ		#sDeleteSRTRec,D0
				_SlotManager
				ENDM
;#####################################################################
; 32-Bit Quickdraw
;#####################################################################
				MACRO	_sVersion
				MOVEQ		#sVersion,D0
				_SlotManager
				ENDM
				MACRO	_SetsRsrcState
				MOVEQ		#SetsRsrcState,D0
				_SlotManager
				ENDM
				MACRO	_InsertSRTRec
				MOVEQ		#InsertSRTRec,D0
				_SlotManager
				ENDM
				MACRO	_GetsRsrc
				MOVEQ		#GetsRsrc,D0
				_SlotManager
				ENDM
				MACRO	_GetTypesRsrc
				MOVEQ		#GetTypesRsrc,D0
				_SlotManager
				ENDM
