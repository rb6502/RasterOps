/*
	File:		Drvr.c
	Contains:	Driver code
	Written by:	Eric Kuo
	Copyright:	й 1994 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
	
		 <3>	 4/13/94	ek		added Energy Star calls
		 <2>	 3/28/94	ek		added Display Manager calls
		 <1>	 3/21/94	ek		first checked in
*/
#include "Rom.h"
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//				defs
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
#define openErr			-23
#define controlErr		-17
#define statusErr		-18
#define	sVidParmDir	123
typedef struct  {
	char	csMode;				// (byte) mode
} VDDefaultInfo, *VDDefaultInfoPtr;
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//				prototypes
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
extern void	GetDcePb(AuxDCEPtr *dcePtr, CntrlParam **pbp);
OSErr	cOpen(void);
OSErr	cPrime(void);
OSErr	cClose(void);
OSErr	cControl(void);
OSErr	cStatus(void);
void	AdjustPitch(short desktopID);
short	GetConnection(long base);
void	GetLut(short *thetable, short start, short count, AuxDCEPtr dcePtr);
long	GetVramOffset(void);
void	GrayScreen(long base, short mode, MYSTORAGE *msp);
void	InVBL(void);
OSErr	SetDirect(AuxDCEPtr dcePtr);
OSErr	SetGamma(GammaTablePtr thetable, MYSTORAGE *msp);
void	SetLinearGamma(GammaTablePtr gammaPtr);
OSErr	SetLut(short *thetable, short start,short count, AuxDCEPtr dcePtr);
void	SetDepth(short slot, short mode, short resID);
void	SwitchModeHW(MYSTORAGE *msp, short newMonitor);
void	WaitVBL(void);
/*еееее Energy Star (((((*/
void	set_energy_save_state_rgs14188();
/*еееее Energy Star )))))*/
void	endDrvr(void);
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//				cOpen()
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// 0. set to system zone
// 1. allocate private storage and hook up to DCE
// 2. init the storage
// 3. install isr slot queue
// 4. setup gamma table
// 5. adjust some hardware registers
// 6. turn on interrupt
// 7. set to old zone
//
OSErr cOpen(void)
{
	AuxDCEPtr			dcePtr;		/* Auxiliary Device Control Entry pointer. */
	CntrlParam			*pbp;		/* Application-passed parameter block pointer. */
	register MYSTORAGE	*msp; 		/* pointer to my private storage (pan & zoom use) */
	THz					oldzone;	/* Previous heap zone */
	SlotIntQElement 	*sqeptr;	/* Slot queue element pointer */
	long				base;		/* Slot base address */
	OSErr				rc;
	GetDcePb(&dcePtr,&pbp);		// get dce pointer and parameter block
	rc = noErr;
	
	/*
	 * Setup some parameters
	 */
	GetDcePb(&dcePtr,&pbp);					/* A0 -> pbp, A1 -> dcePtr */
	base = ((long)(dcePtr->dCtlDevBase) & (long)0xff000000);
	rc = noErr;
	/*
	 * allocate private storage
	 */
	{
		MYSTORAGE	**msh;
		
		oldzone = GetZone();
		SetZone(SystemZone());
		ResrvMem((long)sizeof(MYSTORAGE));
		msh = (MYSTORAGE **) NewHandle((long)sizeof(MYSTORAGE));
		if (msh == 0) {
			rc = openErr;
			goto out;
		}
		dcePtr->dCtlStorage = (Handle) msh;
		HLock(dcePtr->dCtlStorage);
		msp = *msh;
		msp = (MYSTORAGE *) StripAddress((Ptr) msp);
		OpenVenus(dcePtr->dCtlSlot);
		OpenMerc(dcePtr->dCtlSlot);
		OpenBtShort(dcePtr->dCtlSlot);
	}
	/*
	 * Install Interrupts
	 * Set up the fields of the slot queue element block.
	 */
	{
		extern long	isr;
		msp->isrAddr = (long) &isr;
		
		sqeptr = (SlotIntQElement *) NewPtr((long) sizeof(SlotIntQElement));
		if (sqeptr == 0)
		{
			DisposHandle((Handle) dcePtr->dCtlStorage);
			rc = openErr;
			goto out;
		}
		sqeptr->sqLink = 0;
		sqeptr->sqType = 6;
		sqeptr->sqPrio = 0;
		sqeptr->sqAddr = (ProcPtr)msp->isrAddr;
		sqeptr->sqParm = dcePtr->dCtlDevBase;
		if(SIntInstall(sqeptr,dcePtr->dCtlSlot)) {
			DisposPtr((Ptr) sqeptr);
			DisposHandle((Handle) dcePtr->dCtlStorage);
			rc = openErr;
			goto out;
		}
	
		msp->sqePtr = sqeptr;	/* Save the slot queue element block pointer for disposal in close */
	}
	/*
	 * set up gamma
	 */
	{
		register GammaTable		*gammaptr;		/* Gamma Table Block pointer */
		long					i;
		long					j;
		extern char				AppleGamma8[];	/* The Apple Gamma table */
		
		gammaptr = &(msp->gammaTbl);
		gammaptr->gVersion = 0;      	/* Currently 0 for all cards */
		gammaptr->gType = DrHw;			/* DrHwTFB = 0 */
		gammaptr->gFormulaSize = 0;  	/* Formula size = 0, no formula data */
		gammaptr->gChanCnt = 1;      	/* One table for all of r,g, & b, could be 3 for separate r,g, & b tables */
		gammaptr->gDataCnt = 512;  		/* 512 entries per table */
		gammaptr->gDataWidth = 9;    	/* 9 bits per entry */
		
		/*
		 * Values in initial Gamma Table are the Apple Gamma Table (ROM) values
		 */
		for (i=0;i<255;i++) {
			j = i * 2;
			gammaptr->gData.gRTable[j] =
			gammaptr->gData.gGTable[j] =
			gammaptr->gData.gBTable[j] =
				(short) AppleGamma8[i] * 2;
			
			gammaptr->gData.gRTable[j+1] =
			gammaptr->gData.gGTable[j+1] =
			gammaptr->gData.gBTable[j+1] =
				(short) AppleGamma8[i] + (short) AppleGamma8[i+1];
		}
		gammaptr->gData.gRTable[510] =
		gammaptr->gData.gGTable[510] =
		gammaptr->gData.gBTable[510] = 0x01fe;
		
		gammaptr->gData.gRTable[511] =
		gammaptr->gData.gGTable[511] =
		gammaptr->gData.gBTable[511] = 0x01ff;
	}
	
    /*
	 * set up some more msp paramters
	 */
	{
		short	eep5, eep6;
		
		msp->bwmapping = 0;		/* Set Gray mapping off */
		msp->newmode = 0;		/* Set flag to tell gamma that new mode is set and graypage will set lut ramp (below)*/
		msp->mode    = 0; 		/* to be sure first control 2 mode change happens */
		
		msp->slot = dcePtr->dCtlSlot;
		msp->base = base;
		GetEEPROM56(msp->slot, &eep5, &eep6);
		msp->eep6 = eep6;
		msp->offset = GetVramOffset();
		/*еееее Energy Star (((((*/
		msp->sync_state = POWER_ON;
		/*еееее Energy Star )))))*/
	}
	
	/*
	 * need to adjust some Venus registers as
	 * prim init alway uses 1280*2 rowbytes and 0 vramStart
	 * 
	 * Turn on Venus interrupts
	 */
	{
		if(msp->eep6 >= FirstExtended)
			AdjustPitch(msp->eep6);
			
		SetStart(msp->offset/16L);
		INTERRUPT_ON();
		msp->intflag = 1;	/* Set flag to show interrupts enabled */
	}
	/*
	 * finito
	 */
out:
	SetZone(oldzone);
	return(rc);             /* Successful Open */
}
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//				cPrime()
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
OSErr cPrime(void)
{
	return 0;
}
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//				close()
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//
// 1. turn off interrupt
// 2. remove isr queue element and dispose
// 3. dispose of private storage
//
OSErr cClose(void)
{
	MYSTORAGE	*msp;			/* pointer to my private storage */
	AuxDCEPtr	dcePtr;        	/* Auxiliary Device Control Entry pointer. */
	CntrlParam	*pbp;     		/* Application-passed parameter block pointer. */
	
	GetDcePb(&dcePtr,&pbp);      /* A0 -> pbp, A1 -> dcePtr */
	
	msp = (MYSTORAGE *)*(dcePtr->dCtlStorage);
	msp = (MYSTORAGE *) StripAddress(msp);
	
	/*
	 * Turn off interrupts, remove isr
	 * dispose queue element and private storage
	 */
	INTERRUPT_OFF();
	
	SIntRemove(msp->sqePtr,dcePtr->dCtlSlot);
	
	DisposPtr((Ptr) msp->sqePtr);					/* Nuke our slot queue element block. */
	DisposHandle((Handle) dcePtr->dCtlStorage);		/* Nuke our private storage block. */
	return(0);             /* Successful Close */
}
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//				cControl()
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//   Entry:
//      a0 - Parameter Block Pointer
//      a1 - DCE Pointer
//
//   Exit
//      d0 - Error Code
//
//
//   (0)  Reset
//			csMode <- short
//			csPage <- short
//			csBaseAddr <- pointer
//   (1)  Kill I/O
//   (2)  SetMode
//          csMode -> short
//          csPage -> short
//          csBaseAddr <- pointer
//   (3)  SetEntries
//          csTable -> pointer
//          csStart -> short
//          csCount -> short
//   (4)  SetGamma
//          csTable -> pointer
//   (5)  GrayScreen
//          csPage -> pointer
//   (6)  SetGray
//          csMode -> short  (0 for color) (1 for gray)
//   (7)  SetInterrupt
//          csMode -> short  (0 for disable) (1 for enable)
//   (8)  DirectSetEntries
//          csTable -> pointer
//          csStart -> short
//          csCount -> short
//   (9)  SetDefaultMode
//          csMode -> char
//
OSErr cControl(void)
{
	AuxDCEPtr				dcePtr;			/* Auxiliary Device Control Entry pointer. */
	register MYSTORAGE		*msp;
	CntrlParam				*pbp;			/* Application-passed parameter block pointer. */
	Ptr						paramptr;		/* Local copy of pointer to csParam */
	OSErr					errorflag;		/* flag for bad control call */
	long					base;			/* Slot base address */
  
	GetDcePb(&dcePtr,&pbp);		// a0 -> pbPtr, a1 -> dcePtr
	paramptr = *((Ptr *)(pbp->csParam));
	base = ((long)(dcePtr->dCtlDevBase) & (long)0xff000000);
	
	msp = (MYSTORAGE *)(*(dcePtr->dCtlStorage));
	msp = (MYSTORAGE *) StripAddress(msp);
	
	errorflag = 0;
#if 0
	switch(pbp->csCode) {
		case cscReset:
			DebugStr("\pControl: cscReset");
			break;
			
		case cscKillIO:
			DebugStr("\pControl: cscKillIO");
			break;
			
		case cscSetMode:
			DebugStr("\pControl: cscSetMode");
			break;
			
		case cscSetEntries:
			DebugStr("\pControl: cscSetEntries");
			break;
			
		case cscSetGamma:
			DebugStr("\pControl: cscSetGamma");
			break;
			
		case cscGrayScreen:
			DebugStr("\pControl: cscGrayScreen");
			break;
			
		case cscSetGray:
			DebugStr("\pControl: cscSetGray");
			break;
			
		case cscSetInterrupt:
			DebugStr("\pControl: cscSetInterrupt");
			break;
			
		case cscDirectSetEntries:
			DebugStr("\pControl: cscDirectSetEntries");
			break;
			
		case cscSetDefaultMode:
			DebugStr("\pControl: cscSetDefaultMode");
			break;
			
		case cscSwitchMode:
			DebugStr("\pControl: cscSwitchMode");
			break;
			
		case cscSetSync:
			DebugStr("\pControl: cscSetSync");
			break;
			
		default:
			DebugStr("\pControl: unknown");
			break;
	}			
#endif
	/*
	 * dispatch the control call
	 */
	switch(pbp->csCode)
	{
    	case cscReset:			//0: Reset the video card
			break;
		case cscKillIO:			// 1: Remove all pending I/O
			break;
		case cscSetMode:		// 2: Set the card's video mode
			/*
			 * check parameters &  32-bit Quickdraw
			 */
			if(((VDPgInfoPtr)paramptr)->csMode < 0x80 || ((VDPgInfoPtr)paramptr)->csMode > 0x85)
			{
				errorflag = controlErr;    /* Return that we couldn't do it. */
				break;
			}
			if(((VDPgInfoPtr)paramptr)->csMode == msp->mode)		/* same as before */
				break;
			msp->mode = ((VDPgInfoPtr)paramptr)->csMode; /* Set private storage */
			
			SetDepth(msp->slot, msp->mode, msp->eep6);
			////SetStart(msp->offset/16L);
			
			/*
			 * Return the base address
			 */
			((VDPgInfoPtr)paramptr)->csBaseAddr = (Ptr)(msp->base + msp->offset);
			((VDPgInfoPtr)paramptr)->csPage     = 1;	/* All we allow */
			break;
		case cscSetEntries:			// 3: Change card's color lookup table(s)
			if (msp->mode >= 0x84)
				errorflag = controlErr; /* Must use (DirectSetEntries) for millions of colors! */
			else
				errorflag = SetLut((short *) ((VDSetEntryPtr)paramptr)->csTable,
									(short) ((VDSetEntryPtr)paramptr)->csStart,
									(short) ((VDSetEntryPtr)paramptr)->csCount,
									dcePtr);
			break;
		case cscSetGamma:			// 4: Change card's gamma table
			errorflag = SetGamma((GammaTablePtr) (((VDGamRecPtr)paramptr)->csGTable),
								msp);
			/*
			 * Set ramp lut only if direct mode, no gamma error, and not switching modes
			 * If switching modes, a lut load now would flash and grayPage is sure to be called
			 */
			if((msp->mode >= 0x84) && !errorflag && !(msp->newmode))
				errorflag = SetDirect(dcePtr);
			break;
		case cscGrayScreen:			// 5: Gray the video page with dithered gray. ??? use private storage mode and passed page ptr
			GrayScreen(base, msp->mode, msp);
			msp->newmode = 0;	/* tell SetGamma that direct ramps have been loaded */
			
			/*
			 * If 16 or 24 bit mode, set gamma corrected linear ramp in DACs
			 */
			if(msp->mode >= 0x84) {
				SetDirect(dcePtr);
			}
			break;
		case cscSetGray:			// 6: Map color lookup table(s) to color or grayscale
			msp->bwmapping = ((VDPgInfoPtr)paramptr)->csMode & 0x0100;
			break;
		case cscSetInterrupt:		// 7: Enable/Disable Interrupts	
			if(((VDPgInfoPtr)paramptr)->csMode != msp->intflag)
			{
				if(((VDPgInfoPtr)paramptr)->csMode)		/* want it on */
				{
					INTERRUPT_ON();
					msp->intflag = 1;					/* Set flag */
				}
				else									/* want it off */
				{
					INTERRUPT_OFF();
					msp->intflag = 0;					/* Set flag */
				}
			}
			break;
			
		case cscDirectSetEntries:		// 8: Change card's color lookup table(s)	
			if(msp->mode < 0x84 || msp->mode > 0x85)	/* For indexed screen mode, DirectSetEntries DAC load not allowed. Use SetEntries. */
			{
				errorflag = controlErr;
				break;
			}
			errorflag = SetLut((short *) ((VDSetEntryPtr)paramptr)->csTable,
								(short) ((VDSetEntryPtr)paramptr)->csStart,
								(short) ((VDSetEntryPtr)paramptr)->csCount,
								dcePtr);
			break;
		case cscSetDefaultMode:		// 9: Set default mode
			{
				short	monitorID,desktopID;
				short 	eep5,eep6;
				
				desktopID = ((VDDefaultInfoPtr)paramptr)->csMode;
				desktopID &= 0x00ff;
				if ((desktopID < FirstResource) || (desktopID > LastResource))
					desktopID = FirstResource;
			
				GetEEPROM56(msp->slot, &eep5, &eep6);
				if(desktopID <= LastMonitor)
					monitorID = desktopID;
				else
					monitorID = eep5;
				
				if((desktopID != eep6) || (monitorID != eep5))
					SetEEPROM56(msp->slot, monitorID, desktopID);
				msp->eep6 = desktopID;		//еееее Display Manager
			}
			
			break;
      
		//еееее Display Manager (((((
		case cscSwitchMode:         /* Switch Resolution and Bit Depth.  (10) */
			if(((VDSwitchInfoPtr)paramptr)->csData < FirstResource ||
			   ((VDSwitchInfoPtr)paramptr)->csData > LastResource)
			{
				errorflag = controlErr;                   /* Return that we couldn't do it. */
			}
			else if(((VDSwitchInfoPtr)paramptr)->csMode < 0x80 ||
					((VDSwitchInfoPtr)paramptr)->csMode > 0x85)
			{
				errorflag = controlErr;                   /* Return that we couldn't do it. */
			}
			else
			{
				SpBlock			spdata;
				unsigned long	i;
				short			newDesktop;
				
				// Disable old sResource
				spdata.spSlot = msp->slot;
				spdata.spID = GetPRAM6(msp->slot);
				spdata.spExtDev = 0;
				i = SRsrcInfo(&spdata);
				spdata.spParamData = 1;
				i = SetSRsrcState(&spdata);
				// Get new sResource id
				newDesktop = 0x00FF & ((VDSwitchInfoPtr)paramptr)->csData;
				SetPRAM6(msp->slot, newDesktop);
				// Enable new sResource
				spdata.spSlot = msp->slot;
				spdata.spID = newDesktop;
				spdata.spExtDev = 0;
				spdata.spParamData = 0;
				i = SetSRsrcState(&spdata);
				i = SUpdateSRT(&spdata);
	
				// Return Base address of Page 0
				// Update AuxDCE
				((VDSwitchInfoPtr)paramptr)->csBaseAddr = (Ptr)(msp->base + msp->offset);
				dcePtr->dCtlSlotId = newDesktop;
				dcePtr->dCtlDevBase = msp->base;
				// Switch the hardware
				if(newDesktop <= LastMonitor) {
					SetPRAM5(msp->slot, newDesktop);
					SwitchModeHW(msp, newDesktop);
				}
				else {		// extended desktop
					AdjustPitch(newDesktop);
				}
				
				// Get new depth id
				msp->mode = 0x00FF & ((VDSwitchInfoPtr)paramptr)->csMode;
				SetDepth(msp->slot, msp->mode, msp->eep6);
				// this should not happen
				if(newDesktop != msp->eep6) {
					short	eep5, eep6;
					
					GetEEPROM56(msp->slot, &eep5, &eep6);
					eep6 = newDesktop;
					if(eep6 <= LastMonitor)
						eep5 = eep6;
					SetEEPROM56(msp->slot, eep5, eep6);
					msp->eep6 = eep6;
				}
			}
			break;
			//еееее Display Manager )))))
		/*еееее Energy Star (((((*/
		case cscSetSync:         /* Enable/Disable Syncs.  (11) */
			/* a change is requested */
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
			/*еееее Energy Star )))))*/
			
		case -1:				// Goodbye condition.  Done when the "GoodBye Kiss" is given
			cClose();			// Clean up things before leaving. */
			break;
		default:				// Illegal csCode	
			errorflag = controlErr;                   /* Return that we couldn't do it. */
			break;
	}
	return(errorflag);
}
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//				cStatus()
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//   Entry:
//      a0 - Parameter Block Pointer
//      a1 - DCE Pointer
//
//   Exit
//      d0 - Error Code
//
// Status calls
//
//   (0)  Error
//   (1)  Error
//   (2)  GetMode
//          csMode <- short
//          csPage <- short
//          csBaseAddr <- pointer
//   (3)  GetEntries  -  valid for indexed and direct
//          csTable <-> pointer
//          csStart -> short
//          csCount -> short
//   (4)  GetPages
//          csMode -> short
//          csPage <- short  (number of pages)
//   (5)  GetBaseAddr
//          csPage -> short
//          csBaseAddr <- pointer
//   (6)  GetGray
//          csMode <- short  (0 for color) (1 for gray)
//   (7)  GetInterrupt
//          csMode >- short  (0 for disabled) (1 for enabled)
//   (8)  GetGamma
//          csTable <- pointer
//   (9)  GetDefaultMode
//          csMode -> char
//
#define statusErr	-18
OSErr cStatus(void)
{
	AuxDCEPtr			dcePtr;		/* Auxiliary Device Control Entry pointer. */
	register MYSTORAGE	*msp;
	CntrlParam			*pbp;		/* Application-passed parameter block pointer. */
	Ptr					paramptr;	/* Local copy of pointer to csParam */
	OSErr 				error = noErr;
	long				base;		/* Slot base address */
	
	GetDcePb(&dcePtr,&pbp);      /* A0 -> pbp, A1 -> dcePtr */
	
	msp = (MYSTORAGE *)(*(dcePtr->dCtlStorage)); /* Set up our pointer to the globals 	*/
	msp = (MYSTORAGE *) StripAddress(msp);
	
	/* Local copy of pointer to csParam */
	paramptr = *((Ptr *)(pbp->csParam));
	
	/* Local copy of base address */
	base =  ((long)(dcePtr->dCtlDevBase) & (long)0xff000000);
	
	 /* Switch on the type of action we are to repond to or do. */
#if 0	
	switch(pbp->csCode) {
		case cscGetMode:
			DebugStr("\pStatus: cscGetMode");
			break;
			
		case cscGetEntries:
			DebugStr("\pStatus: cscGetEntries");
			break;
			
		case cscGetPages:
			DebugStr("\pStatus: cscGetPages");
			break;
			
		case cscGetBaseAddr:
			DebugStr("\pStatus: cscGetBaseAddr");
			break;
			
		case cscGetGray:
			DebugStr("\pStatus: cscGetGray");
			break;
			
		case cscGetInterrupt:
			DebugStr("\pStatus: cscGetInterrupt");
			break;
			
		case cscGetGamma:
			DebugStr("\pStatus: cscGetGamma");
			break;
			
		case cscGetDefaultMode:
			DebugStr("\pStatus: cscGetDefaultMode");
			break;
			
		case cscGetCurMode:
			DebugStr("\pStatus: cscGetCurMode");
			break;
			
		case cscGetSync:
			DebugStr("\pStatus: cscGetSync");
			break;
			
		case cscGetConnection:
			DebugStr("\pStatus: cscGetConnection");
			break;
			
		case cscGetModeTiming:
			DebugStr("\pStatus: cscGetModeTiming");
			break;
		default:
			DebugStr("\pStatus: unknown");
			break;
	}			
#endif
	switch(pbp->csCode)
	{
		case cscGetMode:			// 2: Get the card's video mode
			((VDPgInfoPtr)paramptr)->csMode = msp->mode;
			((VDPgInfoPtr)paramptr)->csPage = 0;
			((VDPgInfoPtr)paramptr)->csBaseAddr = (Ptr)(msp->base + msp->offset);
			break;
			
		case cscGetEntries:			// 3: Get values from card's color lookup table(s)
			GetLut((short *) ((VDSetEntryPtr)paramptr)->csTable,
					((VDSetEntryPtr)paramptr)->csStart,
					((VDSetEntryPtr)paramptr)->csCount,
					dcePtr);
			break;
			
		case cscGetPages:			// 4: Get the total number of video pages on the card
			((VDPgInfoPtr)paramptr)->csPage = 1;
			break;
			
		case cscGetBaseAddr:		// 5: Get base address of specified page in current mode
			((VDPgInfoPtr)paramptr)->csBaseAddr = (Ptr)(msp->base + msp->offset);
			break;
			
		case cscGetGray:			// 6: Get mapping mode (color or grayscale) of color lookup table(s)
			((VDPgInfoPtr)paramptr)->csMode = msp->bwmapping;
			break;
			
		case cscGetInterrupt:		// 7: Get Interrupt enable state ????
			((VDPgInfoPtr)paramptr)->csMode = msp->intflag;
			break;
			
		case cscGetGamma:			// 8: Get pointer to current gamma table */
			((VDGamRecPtr)paramptr)->csGTable = (Ptr) &(msp->gammaTbl);
			break;
			
		case cscGetDefaultMode:		// 9: Get default mode
			((VDDefaultInfoPtr)paramptr)->csMode = msp->eep6;
			break;
		//еееее Display Manager (((((
		case cscGetCurMode:			// 10: Get Current Resolution and Bit Depth
			((VDSwitchInfoPtr)paramptr)->csMode = (short)msp->mode;
			((VDSwitchInfoPtr)paramptr)->csData = (long) GetPRAM6(msp->slot);
			((VDSwitchInfoPtr)paramptr)->csPage = (short)0;
			((VDSwitchInfoPtr)paramptr)->csBaseAddr = (Ptr)(msp->base + msp->offset);
			((VDSwitchInfoPtr)paramptr)->csReserved = (long)0;
			break;
		case cscGetConnection:		// 12: Get Connection info.
			((VDDisplayConnectInfoPtr)paramptr)->csDisplayType = (unsigned short)GetConnection(base);	//kMultiModeCRT2Connect;	//kUnknownConnect
			((VDDisplayConnectInfoPtr)paramptr)->csConnectTagged = (short)0;
			((VDDisplayConnectInfoPtr)paramptr)->csConnectFlags = 1L;	//(long)0x01;	//(1<<kUncertainConnect);
			((VDDisplayConnectInfoPtr)paramptr)->csDisplayComponent = (long)0;
			((VDDisplayConnectInfoPtr)paramptr)->csConnectReserved = (long)0;
			break;
#if 0			
		case cscGetModeTiming:         /* Get Mode Timing info.  (13) */
			{
				SpBlock	spdata;
				OSErr	iErr;
				
				// Get sResource
				spdata.spSlot = msp->slot;
				spdata.spExtDev = 0;
	
				spdata.spID = 1;	//sRsrcBoard;	// Find Board Resource
				iErr = SRsrcInfo(&spdata);
				spdata.spID = sVidParmDir;	////sVidParmDir;	// Find Timing Directory
				iErr = SFindStruct(&spdata);
					
				spdata.spID = ((VDTimingInfoPtr)paramptr)->csTimingMode;
				iErr = SReadLong(&spdata);
	//			((VDTimingInfoPtr)paramptr)->csTimingReserved = ((unsigned long)0;
				((VDTimingInfoPtr)paramptr)->csTimingFormat = (unsigned long)kDeclROMtables;
				((VDTimingInfoPtr)paramptr)->csTimingData = (unsigned long)spdata.spResult;	//timingUnknown;//timingApple19
				switch(spdata.spID) {
					case 0x0084:		// 8x6
						((VDTimingInfoPtr)paramptr)->csTimingFlags = (unsigned long)0x07;
						break;
						
					case 0x0082:		// 10x7 75Hz
					case 0x0085:		// 6x4
						((VDTimingInfoPtr)paramptr)->csTimingFlags = (unsigned long)0x03;
						break;
					
					default:
						((VDTimingInfoPtr)paramptr)->csTimingFlags = (unsigned long)0x01;
						break;
				}
				if(iErr)
					error = statusErr;
			}
			break;
			
		//еееее Display Manager )))))
#endif
		/*еееее Energy Star (((((*/
		case cscGetSync:         /* (11) */
			*((VDFlagPtr)paramptr) = msp->sync_state;
			break;
		/*еееее Energy Star )))))*/
		default:
			error = statusErr;
			break;
	}
	return(error);
}
/*****************************************************************************************************
 * driver utility routines
 *****************************************************************************************************/
/*
 * AdjustPitch()
 *
 * handle the extended desktop sizes
 *
 * all non-extended desktop has row byte of 1152
 * rowbytes for extended desktop are:
 * 1600 x 1200:	3328
 * 2400 x 1800:	2048
 * 3200 x 2400:	1664
 * 4000 x 3000:	1024
 */
void AdjustPitch(short desktopID)
{
	long	pitch;
	
	switch(desktopID) {
		case 0x008a:
				pitch = 3328 / 16;
				break;
		case 0x008b:
				pitch = 2048 / 16;
				break;
		case 0x008c:
				pitch = 1664 / 16;
				break;
		case 0x008d:
				pitch = 1024 / 16;
				break;
	}
	SetPitch(pitch);
}
//еееее Display Manager (((((
//
// GetConnection():
//
short GetConnection(long base)
{
	short rawSense;
	short id;
	
	rawSense = GetRawSenseCode(base);
	switch(rawSense) {
#if 0
		case SENSECODE_11X8C:
		case SENSECODE_6x8M:
		case SENSECODE_5x3:
		case SENSECODE_11x8M:
		case SENSECODE_NTSC:
		case SENSECODE_6X8C:
		case SENSECODE_6X4:
		case SENSECODE_PAL_CODER:
		case SENSECODE_NTSC_CODER:
		case SENSECODE_VGA:
		case SENSECODE_8X6:
		case SENSECODE_PAL:
		case SENSECODE_10X7_75:
					id = kFixedModeCRTConnect;
					break;
#endif					
		case SENSECODE_MSB1:
					id = kMultiModeCRT1Connect;
					break;
					
		case SENSECODE_MSB2:
					id = kMultiModeCRT2Connect;
					break;
					
		case SENSECODE_MSB3:
					id = kMultiModeCRT3Connect;
					break;
					
		case SENSECODE_NONE:
					id = kUnknownConnect;
					break;
					
		default:
					id = kFixedModeCRTConnect;
					break;
	}
	return id;
}
//еееее Display Manager )))))
/*
 * GetLut()
 */
void GetLut(short *thetable, short start, short count, AuxDCEPtr dcePtr)
{
	MYSTORAGE			*msp;		/* pointer to my private storage */
	register short		addr,i;
	register CLUTBUF	*clutBuf;
	register short 		*table;
	short				end;
	Boolean				depth16;
	
	msp = (MYSTORAGE *)*(dcePtr->dCtlStorage);
	msp = (MYSTORAGE *) StripAddress(msp);
	
	clutBuf = msp->clutBuf;
	depth16 = (msp->mode == 0x84);
	table = thetable;
	if (start == -1)
	{
		for (i=0;i<=count;i++)               /* Yank the values in order from our byte table (R,G,B). */
		{
			addr = table[i*4];
			if(depth16) {
				addr = (addr << 3) | (addr >> 2);
			}
			table[i*4+1] = (clutBuf[addr].r << 7) & 0xff80;
			table[i*4+2] = (clutBuf[addr].g << 7) & 0xff80;
			table[i*4+3] = (clutBuf[addr].b << 7) & 0xff80;
		}
	}
	else
	{
		end = start+count;
		for (addr=start;addr<=end;addr++)  /* Yank the values in order from our byte table (R,G,B). */
		{
			if(depth16) {
				addr = (addr << 3) | (addr >> 2);
			}
			table[addr*4+1] = (clutBuf[addr].r << 7) & 0xff80;
			table[addr*4+2] = (clutBuf[addr].g << 7) & 0xff80;
			table[addr*4+3] = (clutBuf[addr].b << 7) & 0xff80;
		}
	}
}
/*
 * GetVramOffset()
 */
long	GetVramOffset()
{
	return VRAM_START;
}
/*
 * GrayScreen()
 */
void GrayScreen(long base, short mode, MYSTORAGE *msp)
{
	register short			i;
	register short			j;
	register long			pattern;
	register long			black;
	register long			*to;
	short					width;
	short					height;
	register long			rowLongs;
	char					mmu_mode;
	short					depth;
	depth = 1 << (mode & 0x07);
	GetWH(msp->eep6, &width, &height);
	rowLongs = GETPITCH() * 16L / 4L;
	
	if(depth >= 8) {
		Rect	r;
		
		EraseScrnMerc(base, VRAM_START, VRAM_END, rowLongs*4);
		r.left = r.top = 0;
		r.right = width;
		r.bottom = height;
		GrayWipeMerc(base, VRAM_START, &r, rowLongs*4, depth);
		return;
	}
	
	/*
	 * black screen
	 */
	/*drBlackMem(base, (short) (1 << (mode&0x7)));*/
	switch(mode & 0x7) {
		case 0:			/* 1bit */
			width >>= 5;			/* we use number of longs */
			pattern = 0xaaaaaaaa;
			black = 0xffffffff;
			break;
		case 1:			/* 2bit */
			width >>= 4;
			pattern = 0xcccccccc;
			black = 0xffffffff;
			break;
		case 2:			/* 4bit */
			width >>= 3;
			pattern = 0xf0f0f0f0;
			black = 0xffffffff;
			break;
		case 3:			/* 8bit */
			width >>= 2;
			pattern = 0xff00ff00;
			black = 0xffffffff;
			break;
		case 4:			/* 16bit */
			width >>= 1;
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
	SwapMMUMode(&mmu_mode);
    
	to = (long *) (base + msp->offset);
	i = height;
	if((mode & 0x7) != 5) {		/* 1bit - 16bit mode */
		while(i--) {
			/* paint gray */
			j = width;
			while(j--) {
				*to++ = pattern;
			}
			/* paint black */
			j = rowLongs - width;
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
			j = rowLongs - width;
			while(j--) {
				*to++ = black;
			}
			pattern = ~pattern;
		}
	}
	SwapMMUMode(&mmu_mode);
}
/*
 * InVBL()
 */
void InVBL()
{
	while((GetVenus(V_STATUS)  & 0x00000010) == 0)
		;
}
/*
 * SetDirect()
 */
OSErr SetDirect(AuxDCEPtr dcePtr)
{
	MYSTORAGE		*msp;		/* pointer to my private storage */
	short			i;
	CLUTBUF			*clutBuf;
	long			base;
	GammaTable		*gammaptr;				/* Gamma Table block pointer */
  
	base = (dcePtr->dCtlDevBase & 0xff000000L) | (long)BT9046;
	
	msp = (MYSTORAGE *)*(dcePtr->dCtlStorage);
	msp = (MYSTORAGE *) StripAddress(msp);
	
	clutBuf = msp->clutBuf;
	clutBuf = (CLUTBUF *) StripAddress((Ptr)clutBuf);  /* mask possible master pointer flag bits */
	
	gammaptr = (GammaTable *)&(msp->gammaTbl);
	gammaptr = (GammaTable *)StripAddress((Ptr)gammaptr);  /* mask possible master pointer flag bits */
	
	/* get pointers to r,g,b gamma table or tables */
	
	if(gammaptr->gDataWidth == 9) {
		short	*gammaptr_r;
		short	*gammaptr_g;
		short	*gammaptr_b;
	
		gammaptr_r = gammaptr->gData.gRTable;
		gammaptr_g = gammaptr->gData.gGTable;
		gammaptr_b = gammaptr->gData.gBTable;
		
		for (i=0;i<256;i++) {
			/* Write the corrected values to our backup table. */
			clutBuf[i].r = gammaptr_r[i*2];
			clutBuf[i].g = gammaptr_g[i*2];
			clutBuf[i].b = gammaptr_b[i*2];
		}
	}
	else {
		char	*gammaptr_r;
		char	*gammaptr_g;
		char	*gammaptr_b;
		GammaData8		*gData8Ptr;
		
		gData8Ptr = (GammaData8 *) &(gammaptr->gData);
		
		gammaptr_r = gData8Ptr->gRTable;
		gammaptr_g = gData8Ptr->gGTable;
		gammaptr_b = gData8Ptr->gBTable;
		
		for (i=0;i<256;i++)
		{
			clutBuf[i].r = gammaptr_r[i] << 1;
			clutBuf[i].g = gammaptr_g[i] << 1;
			clutBuf[i].b = gammaptr_b[i] << 1;
		}
	}
	
	/* Send buffered data to the DACs */
	
	InVBL();
	SetDac((short *) clutBuf, (short) 0, (short) 256);
	
	return(0);	/* Successful completion. */  
}
/*
 * SetGamma()
 */
OSErr SetGamma(GammaTablePtr thetable, MYSTORAGE *msp)
{
	register GammaTablePtr	gammaptr;
	register short			i;
	register short			*dp9;
	register char			*dp8;
	short					count;
	
	gammaptr = &(msp->gammaTbl);
	
	/* Check for a linear table request */
	if ((thetable == 0) || (thetable == -1)) 
	{
		SetLinearGamma(gammaptr);
		return noErr;
	}
	/* Check for the presence of formula data or an incorrect version (non-zero) */
	if ((thetable->gFormulaSize) || (thetable->gVersion != 0)) return(controlErr);
	
	/* Check for a valid ID - either our ID (DrHwRasterOpsCB224) or Apple's ID (DrHwTFB) */ 
	if ((thetable->gType) && (thetable->gType != DrHw)) return(controlErr);
	
	/* Check for more 8-bit entries in the table than we can handle (256 is MAX) */
	if (((thetable->gDataCnt != 256) && (thetable->gDataCnt != 512)) ||
	    ((thetable->gDataWidth != 8) && (thetable->gDataWidth != 9)))
	{
		return(controlErr);
	}
	
	/* Check for a valid number of tables (1 or 3) */
	if ((thetable->gChanCnt != 1) && (thetable->gChanCnt != 3)) return(controlErr);
	
	/* Copy the table header */  
	gammaptr->gVersion     = thetable->gVersion;      /* Currently 0 for all cards */
	gammaptr->gType        = thetable->gType;         /* DrHwTFB = 0,  DrHwRasterOps24XLi = $02A0 */
	gammaptr->gFormulaSize = thetable->gFormulaSize;  /* Formula size = 0, no formula data */
	gammaptr->gChanCnt     = thetable->gChanCnt;      /* Can be 1 or 3 for separate r,g, & b tables */
	gammaptr->gDataCnt     = thetable->gDataCnt;      /* 256 entries per table maximum */
	gammaptr->gDataWidth   = thetable->gDataWidth;    /* 8 bits per entry */
	dp9                    = (short *)&(thetable->gData);
	dp8                    = (char *)&(thetable->gData);
	
	count = gammaptr->gDataCnt;
	if(thetable->gDataWidth == 9)
	{
		if (gammaptr->gChanCnt == 3) 
		{
			for (i=0;i<count;i++)
				gammaptr->gData.gRTable[i] = *dp9++;
			for (i=0;i<count;i++)
				gammaptr->gData.gGTable[i] = *dp9++;
			for (i=0;i<count;i++)
				gammaptr->gData.gBTable[i] = *dp9++;
		}
		else
		{
			for (i=0;i<count;i++) 
				gammaptr->gData.gBTable[i] = gammaptr->gData.gGTable[i] = gammaptr->gData.gRTable[i] = *dp9++;
		}
	}
	else {
		GammaData8	*gData8Ptr;
		
		gData8Ptr = (GammaData8 *) &(gammaptr->gData);
		
		if (gammaptr->gChanCnt == 3) 
		{
			for (i=0;i<count;i++)
				gData8Ptr->gRTable[i] = *dp8++;
			for (i=0;i<count;i++)
				gData8Ptr->gGTable[i] = *dp8++;
			for (i=0;i<count;i++)
				gData8Ptr->gBTable[i] = *dp8++;
		}
		else
		{
			for (i=0;i<count;i++)
			{
				gData8Ptr->gBTable[i] = gData8Ptr->gGTable[i] = gData8Ptr->gRTable[i] = *dp8++;
			}
		}
	}
	
	return(noErr);
}
/*
 * SetLinearGamma()
 */
void SetLinearGamma(GammaTablePtr gammaPtr)
{
	register short	i;
	
    /* Initialize the table header */  
    gammaPtr->gVersion     = 0;    	/* Currently 0 for all cards */
    gammaPtr->gType        = DrHw;	/* DrHwTFB = 0, DrHwRasterOps24XLi = $02A0 */
    gammaPtr->gFormulaSize = 0;  	/* Formula size = 0, no formula data */
    gammaPtr->gChanCnt     = 1;   	/* Can be 1 or 3 for separate r,g, & b tables */
    gammaPtr->gDataCnt     = 512;	/* 512 entries per table maximum */
    gammaPtr->gDataWidth   = 9;		/* 9 bits per entry */
	for (i=0;i<512;i++) {
		gammaPtr->gData.gBTable[i] = gammaPtr->gData.gGTable[i] = gammaPtr->gData.gRTable[i] = i;
	}
}
/*
 * SetLut()
 */
OSErr SetLut(short *thetable, short start,short count, AuxDCEPtr dcePtr)
{
	MYSTORAGE		*msp;		/* pointer to my private storage */
	short			addr,mapmode;
	register short	color,i;
	CLUTBUF			*clutBuf;
	register long 	base;
	short			*table;
	GammaTable		*gammaptr;		/* Gamma Table block pointer */
	short			index = 0;
	Boolean			depth16;
	
	if(thetable == nil)	/* Must have  valid pointer to continue */
		return(controlErr);
	
	base = (dcePtr->dCtlDevBase & 0xff000000L) | (long)BT9046;
	
	/* Dereference locked handle to private storage */
	msp = (MYSTORAGE *)*(dcePtr->dCtlStorage);
	msp = (MYSTORAGE *) StripAddress(msp);
	
	clutBuf = msp->clutBuf;
	clutBuf = (CLUTBUF *) StripAddress((Ptr)clutBuf);  /* mask possible master pointer flag bits */
	
	gammaptr = (GammaTable *)&(msp->gammaTbl);
	gammaptr = (GammaTable *)StripAddress((Ptr)gammaptr);  /* mask possible master pointer flag bits */
	
	mapmode = ((msp->bwmapping) && (msp->mode < 0x84));       /* disable gray mapping for direct mode */
	table = (short *)StripAddress((Ptr)thetable);  /* mask possible master pointer flag bits */
	
	/* get pointers to r,g,b gamma table or tables */
	
	depth16 = (msp->mode == 0x84);
	
	if(gammaptr->gDataWidth == 9) {
		short	*gammaptr_r;
		short	*gammaptr_g;
		short	*gammaptr_b;
	
		gammaptr_r = gammaptr->gData.gRTable;
		gammaptr_g = gammaptr->gData.gGTable;
		gammaptr_b = gammaptr->gData.gBTable;
		
		for (i=0;i<=count;i++) {
			addr       =  (start == -1) ? addr = table[0] & (short)0x00FF : (start+i) & (short)0x00FF;
			if(depth16) {
				addr = (addr << 3) | (addr >> 2);
			}
			if (mapmode) {		/* convert to gray data */
				/* Convert to grayscale using the sum of 30% red, 60% green, 10% blue. */
				color = (((long)table[1] & 0x0000FF80L)*3 +
						 ((long)table[2] & 0x0000FF80L)*6 +
						 ((long)table[3] & 0x0000FF80L))/10;
			
				/* Round up if there's enough remainder. */
				color  = (color & 0x0040) ? 1 + (color >> 7) : color >> 7;	    
				color &= (short)0x01FF;
				clutBuf[addr].r = gammaptr_r[color];
				clutBuf[addr].g = gammaptr_g[color];
				clutBuf[addr].b = gammaptr_b[color];
			}
			else  {		/* Just send the bytes to the DAC's. */
				clutBuf[addr].r = gammaptr_r[(table[1]>>7) & 0x01ff];
				clutBuf[addr].g = gammaptr_g[(table[2]>>7) & 0x01ff];
				clutBuf[addr].b = gammaptr_b[(table[3]>>7) & 0x01ff];
			}
			
			table += 4;
		}
	}
	else {
		char	*gammaptr_r;
		char	*gammaptr_g;
		char	*gammaptr_b;
		GammaData8		*gData8Ptr;
		
		gData8Ptr = (GammaData8 *) &(gammaptr->gData);
		
		gammaptr_r = gData8Ptr->gRTable;
		gammaptr_g = gData8Ptr->gGTable;
		gammaptr_b = gData8Ptr->gBTable;
		
		for (i=0;i<=count;i++) {
			addr       =  (start == -1) ? addr = table[0] & (short)0x00FF : (start+i) & (short)0x00FF;
			if(depth16) {
				addr = (addr << 3) | (addr >> 2);
			}
			if (mapmode) {		/* convert to gray data */
				/* Convert to grayscale using the sum of 30% red, 60% green, 10% blue. */
				color = (((long)table[1] & 0x0000FF00L)*3 +
						 ((long)table[2] & 0x0000FF00L)*6 +
						 ((long)table[3] & 0x0000FF00L))/10;
			
				/* Round up if there's enough remainder. */
				color  = (color & 0x0080) ? 1 + (color >> 8) : color >> 8;	    
				color &= (short)0x00FF;
				clutBuf[addr].r = gammaptr_r[color] << 1;
				clutBuf[addr].g = gammaptr_g[color] << 1;
				clutBuf[addr].b = gammaptr_b[color] << 1;
			}
			else  {		/* Just send the bytes to the DAC's. */
				clutBuf[addr].r = gammaptr_r[(table[1]>>8) & 0x00FF] << 1;
				clutBuf[addr].g = gammaptr_g[(table[2]>>8) & 0x00FF] << 1;
				clutBuf[addr].b = gammaptr_b[(table[3]>>8) & 0x00FF] << 1;
			}
			
			table += 4;
		}
	}
	
	InVBL();
	SetDac((short *) clutBuf, (short) 0, (short) 256);
	
	return(0);	/* Successful completion. */  
}
//
// SetDepth()
//
void SetDepth(short slot, short mode, short resID)
{
#pragma unused(slot);
	long	val;
	long	pitch;
	
	/*
	 * set lut to gray,
	 * change depth
	 * adjust pitch
	 */
	WaitVBL();
	GrayBtPallette();
	WaitVBL();
	
	val = GetBtReg(BT9046_COMMAND_0);
	val &= ~0x07;
	val |= (mode & 0x7);
	SetBtReg(BT9046_COMMAND_0, val);
	if(resID < FirstExtended) {
		if(mode <= 0x84)
			pitch = PITCH16;
		else
			pitch = PITCH32;
		SetPitch(pitch);
	}
}
//еееее Display Manager (((((
/*
 * SwitchModeHW()
 */
void	SwitchModeHW(MYSTORAGE *msp, short newMonitor)
{
	LoadVenusTbl(newMonitor);
	SetVenus(V_CONTROL1, GetVenus(V_CONTROL1) | 0x0091);
	SetVenus(V_CONTROL3, GetVenus(V_CONTROL3) | 0x0072);
	SetVenus(V_CONTROL1, GetVenus(V_CONTROL1) | 0x00B5);
	
	set_frequency(msp->base, newMonitor, MCLK);
	SetStart(msp->offset/16L);
	if(msp->intflag)
		INTERRUPT_ON();
}
//еееее Display Manager )))))
/*
 * WaitVBL()
 */
void WaitVBL()
{
	while(GetVenus(V_STATUS) & 0x00000010)
		;
		
	while((GetVenus(V_STATUS) & 0x00000010) == 0)
		;
}
/*еееее Energy Star (((((*/
/*
 *	set_energy_save_state_rgs14188
 */
void	set_energy_save_state_rgs14188(new_state, msp)
unsigned char	new_state;
MYSTORAGE		*msp;
{
	unsigned long	temp;
	unsigned long	base;
	rgs14188_data	*save_timing;
	
	save_timing = &msp->save_timing;
	base = msp->base;
	
	switch(new_state)
	{
		case POWER_ON:
			switch(msp->sync_state)
			{
				case POWER_OFF:
					/*DebugStr("\Pset_energy_save_state_s3_86c805 POWER_OFF to POWER_ON");*/
					/* Restore original vertical timing */
					SetVenus(V_VERT_ENDSYNC, (long)save_timing->ves);
					SetVenus(V_VERT_TOTAL, (long)save_timing->vtot);
					SetVenus(V_VERT_STARTBLANK, (long)save_timing->vsb);
					SetVenus(V_VERT_INTLINE, (long)save_timing->vil);
					/* Restore original horizontal timing */
					SetVenus(V_HORI_TOTAL, (long)save_timing->htot);
				case POWER_STANDBY:
					/*DebugStr("\Pset_energy_save_state_s3_86c805 POWER_STANDBY to POWER_ON");*/
					/* Restore original horizontal timing */
					SetVenus(V_HORI_ENDSYNC, (long)save_timing->hes);
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
					SetVenus(V_HORI_TOTAL, (long)save_timing->htot);
					/* Set new horizontal timing */
					SetVenus(V_HORI_ENDSYNC, (long)save_timing->htot + 2);
					/* Restore original vertical timing */
					SetVenus(V_VERT_ENDSYNC, (long)save_timing->ves);
					SetVenus(V_VERT_TOTAL, (long)save_timing->vtot);
					SetVenus(V_VERT_STARTBLANK, (long)save_timing->vsb);
					SetVenus(V_VERT_INTLINE, (long)save_timing->vil);
					break;
				case POWER_ON:
					/*DebugStr("\Pset_energy_save_state_s3_86c805 POWER_ON to POWER_STANDBY");*/
					/* Save original horizontal timing */
					save_timing->hes = GetVenus(V_HORI_ENDSYNC);
					save_timing->htot = GetVenus(V_HORI_TOTAL);
					/* Set new horizontal timing */
					SetVenus(V_HORI_ENDSYNC, (long)save_timing->htot + 2);
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
					save_timing->hes = GetVenus(V_HORI_ENDSYNC);
					save_timing->htot = GetVenus(V_HORI_TOTAL);
				case POWER_STANDBY:
					/*DebugStr("\Pset_energy_save_state_s3_86c805 POWER_STANDBY to POWER_OFF");*/
					/* Save original vertical timing */
					save_timing->ves = GetVenus(V_VERT_ENDSYNC);
					save_timing->vsb = GetVenus(V_VERT_STARTBLANK);
					save_timing->vtot = GetVenus(V_VERT_TOTAL);
					save_timing->vil = GetVenus(V_VERT_INTLINE);
					/* Set new vertical timing */
					SetVenus(V_VERT_ENDSYNC, rgs14188_energy_saving_ves);
					SetVenus(V_VERT_TOTAL, rgs14188_energy_saving_vtot);
					SetVenus(V_VERT_STARTBLANK, rgs14188_energy_saving_vsb);
					SetVenus(V_VERT_INTLINE, rgs14188_energy_saving_vil);
					/* Set new horizontal timing */
					temp = (long)save_timing->htot * (long)save_timing->vtot;
					temp = temp/rgs14188_energy_saving_vtot;
					SetVenus(V_HORI_ENDSYNC, temp + 2);
					SetVenus(V_HORI_TOTAL, temp);
				case POWER_OFF:
					break;
			}
			break;
	}
}
/*еееее Energy Star )))))*/
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//				END OF DRIVER BLOCK
//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
void	endDrvr()
{
}
