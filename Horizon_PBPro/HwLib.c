/*
	File:		HwLib.c
	Contains:	venus routines
	Written by:	Eric Kuo
	Copyright:	й 1994 by RasterOps, Inc., all rights reserved.
	Change History (most recent first):
	
		 <2>	 3/31/94	ek		renamed from Venus.c
		 <1>	 3/30/94	ek		first checked in
*/
#include "Rom.h"
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//				EEPROM code
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*
 * SetupEEPROM()
 */
void SetupEEPROM()
{
	SetVenus(V_GIOCONFIG, 0x80b3L);
}
/*
 * GetEEPROM56()
 */
void GetEEPROM56(short slot, short *ptr5, short *ptr6)
{
	long	*eep;
	short	w;
	
	eep = (long *) ((unsigned long) DEVBASE(slot) | EEPROM);
	w = eeReadWord(eep, (short) 3);
	*ptr5 = (w >> 8) & 0x00ff;
	*ptr6 = w & 0x00ff;
}
	
/*
 * SetEEPROM56()
 */
void SetEEPROM56(short slot, short pram5, short pram6)
{
	register long	*eep;
	short	w;
	
	eep = (long *) ((unsigned long) DEVBASE(slot) | EEPROM);
	w = (pram5 << 8) | (pram6 & 0x00ff);
	eeWriteWord(eep, (short) 3, w);
}
/*
 * eeEnable()
 */
void eeEnable(long *eep)
{
	EESendStartOpAddr(eep, (short) OP_EWEN, (short) ADDR_EWEN);
	EEEpilog(eep);
}
/*
 * eeDisable()
 */
void eeDisable(long *eep)
{
	EESendStartOpAddr(eep, (short) OP_EWDS, (short) ADDR_EWDS);
	EEEpilog(eep);
}
/*
 * eeReadWord()
 */
short eeReadWord(long *eep, short addr)
{
	short	w;
	
	EESendStartOpAddr(eep, (short) OP_READ, addr);
	EEDiscardBit(eep);
	w = EEReadBitStream(eep);
	EEEpilog(eep);
	return w;
}
/*
 * eeWriteWord()
 */
void eeWriteWord(long *eep, short addr, short data)
{	
	eeEnable(eep);
	EESendStartOpAddr(eep, (short) OP_WRITE, addr);
	EESendData(eep, data);
	EEPollReady(eep);
	EEEpilog(eep);
	eeDisable(eep);
	WaitNms(20);
}	
/*
 * EEPollReady()
 *
 * wait till data written is ready
 * quit after 10 ms no matter what
 */
short EEPollReady(long *eep)
{
	long	bits;
	short	i;
	EEPoke(eep, 0, 0, 0);
	EEPoke(eep, 1, 0, 0);
	Wait1ms();
	
	i = 100;
	while(i--) {
		bits = EEPeek(eep);
		if(bits & 0x01) {
			return 1;
		}
		Wait1ms();
	}
	return 0;
}
/*
 * EEReadBitStream()
 */
short EEReadBitStream(long *eep)
{
	register short	w;
	register short	count;
	register long	bit;
	
	w = 0;
	count = 16;
	
	while(count--) {
		EEPoke(eep, 0, 1, 0);
		bit = EEPeek(eep);
		EEPoke(eep, 1, 1, 0);
		w = (w << 1) | (bit & 0x01);
	}
	return w;
}
/*
 * EESendBitStream()
 */
void EESendBitStream(long *eep, short bits,short  n)
{
	bits <<= (16 - n);
	while(n--) {
		if(bits >= 0) {
			EEPoke(eep, 0, 1, 0);
			EEPoke(eep, 1, 1, 0);
		}
		else {
			EEPoke(eep, 0, 1, 1);
			EEPoke(eep, 1, 1, 1);
		}
		bits <<= 1;
	}
}
/*
 * EESendStartOpAddr()
 */
void EESendStartOpAddr(long *eep, short opcode, short addr)
{
	EEProlog(eep);	 	
	EESendOpcode(eep, opcode);
	EESendAddr(eep, addr);
}
/*
 * eePoke()
 */
void eePoke32XL(long *eep, short bits)
{
	char	mmu_mode;
	
	mmu_mode = true32b;
	SwapMMUMode(&mmu_mode);
	*(eep) = *(eep) & 0x0000000f | ((long) bits << 4L);
	SwapMMUMode(&mmu_mode);
}
/*
 * eePeek()
 */
short eePeek32XL(long *eep)
{
	char			mmu_mode;
	register long	w;
	
	mmu_mode = true32b;
	SwapMMUMode(&mmu_mode);
	w = (*(eep) & 0x00000040) >> 6;
	SwapMMUMode(&mmu_mode);
	return ((short) w);
}
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//				Systhesizer code
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
#define	icd2062clock	1
#define	icd2062data		2
void	set_frequency(long base, short pram5)
{
	switch(pram5 & 0x000f)
	{
		case 0:	/* 1280 X 1024 */
			send_to_icd2062(base, 0, 0x001BB813L);	/* A=0, I=0D, P=7F, M=0, Q=18 */
			break;
		case 1:	/* 1152 X 870 */
			send_to_icd2062(base, 0, 0x001BFC18L);	/* A=0, I=0D, P=7F, M=0, Q=18 */
			break;
		case 2:	/* 1024 X 768 75hz */
			send_to_icd2062(base, 0, 0x000FF41EL);	/* A=0, I=07, P=7D, M=0, Q=1E */
			break;
		case 3:	/* 1024 X 768 60 hz */
			send_to_icd2062(base, 0, 0x000BF426L);	/* A=0, I=05, P=7D, M=0, Q=26 */
			break;
		case 4:	/* 832 X 624 */
			send_to_icd2062(base, 0, 0x00099C23L);	/* A=0, I=04, P=7C, M=1, Q=28 */
			break;
		case 5:	/* 640 X 480 */
			send_to_icd2062(base, 0, 0x0009F0A8L);	/* A=0, I=04, P=67, M=0, Q=23 */
			break;
		case 6:	/* 640 X 870 30hz */
			send_to_icd2062(base, 0, 0x00099C23L);	/* A=0, I=04, P=7C, M=1, Q=28 */
			break;
	}
	
	WaitNms(10);
	/* send_to_icd2062(base, 3, 0x000feca1L);	/* A=3, I=01, P=5F, M=0, Q=2F */
	/* send_to_icd2062(base, 3, 0x000dd0a1L);	/* A=3, I=01, P=5F, M=0, Q=2F */  /* 34 */
	/* send_to_icd2062(base, 3, 0x000feca2L);	/* A=3, I=01, P=5F, M=0, Q=2F */ /* 35 */
	/* send_to_icd2062(base, 3, 0x0005d42eL);	/* A=3, I=01, P=5F, M=0, Q=2F */  /* 50 */
	/* send_to_icd2062(base, 3, 0x00058026L);	/* A=3, I=01, P=5F, M=0, Q=2F */  /* 49.5 */
	/* send_to_icd2062(base, 3, 0x00057c26L);	/* A=3, I=01, P=5F, M=0, Q=2F */  /* 49 */
	/* send_to_icd2062(base, 3, 0x000fc89cL);	/* A=3, I=01, P=5F, M=0, Q=2F */  /* 39Mhz */
	/* send_to_icd2062(base, 3, 0x00037d2fL);	/* A=3, I=01, P=5F, M=0, Q=2F */  /* 10Mhz */
	send_to_icd2062(base, 3, 0xcafedea0L);	/* ROM loader will change this to valid value */
	WaitNms(10);
}
short	send_to_icd2062(long base, short address, long data)
{
	register long	*gio_lo_ptr;
	register long 	i;
	register long 	bits;
	unsigned char	mmu_mode;
	unsigned char	freq_select;
	
	mmu_mode = true32b;
	
	gio_lo_ptr = (long *)(base + RGS14188) + gio_reg_Lo;
	bits = ((long)address << 21) | (data & 0x001FFFFFL);
	
	SwapMMUMode(&mmu_mode);
	/* Save previous frequency selection */
	freq_select = *gio_lo_ptr & 3;
	/* unlock sequence */
	*gio_lo_ptr |= icd2062data | icd2062clock;
	for(i=0; i<5; i++)
	{
		*gio_lo_ptr &= ~icd2062clock;
		*gio_lo_ptr |= icd2062clock;
	}
	*gio_lo_ptr &= ~icd2062data;
	*gio_lo_ptr &= ~icd2062clock;
	*gio_lo_ptr |= icd2062clock;
	
	/* start bit */
	*gio_lo_ptr &= ~icd2062clock;
	*gio_lo_ptr |= icd2062clock;
	
	/* send bits */
	for(i=0; i<24; i++)
	{
		if(bits & 1)
			*gio_lo_ptr &= ~icd2062data;
		else
			*gio_lo_ptr |= icd2062data;
			
		*gio_lo_ptr &= ~icd2062clock;
		if(bits & 1)
			*gio_lo_ptr |= icd2062data;
		else
			*gio_lo_ptr &= ~icd2062data;
			
		*gio_lo_ptr |= icd2062clock;
		
		bits >>= 1;
	}
	/* stop bit */
	*gio_lo_ptr |= icd2062data;
	*gio_lo_ptr &= ~icd2062clock;
	*gio_lo_ptr |= icd2062clock;
	
	/* Restore previous frequency selection */
	*gio_lo_ptr = (*gio_lo_ptr & ~3) | freq_select;
	SwapMMUMode(&mmu_mode);
	return 0;
}
void	icd2062_vco(long base, short address,  short q,  short m,  short p, short i)
{
	long 	w;
	w =	(((long)i & 0x0000000FL) << 17) |
		(((long)p & 0x0000007FL) << 10) |
		(((long)m & 0x00000007L) << 7) |
		(((long)q & 0x0000007FL) << 0);
	send_to_icd2062(base, address, w);
}
void	icd2062_control(long base, short control)
{
	long 	w;
	w =	((long)control & 0x0000003FL) << 15;
	send_to_icd2062(base, 6, w);
}
void	icd2062_div(long base, short div)
{
	long 	w;
	w =	((long)div & 0x00000007L) << 18;
	send_to_icd2062(base, 5, w);
}
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
//				mointor sense code
//ееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
/*
 * GetSavedSense()
 *	get the monitor sense stored in eep
 */
short GetSavedSense(short slot)
{
	long	*eep;
	short	sense;
	
	eep = (long *) ((unsigned long) DEVBASE(slot) | EEPROM);
	sense = eeReadWord(eep, (short) 4);
	return sense ;
}
//
// GetSenseReg(): drive the bit and read back register
//
short GetSenseReg(long base, short bitMask)
{
	volatile long	*gio_hi_reg;	/* pointer to data register */
	long	*gio_hi_config;	/* pointer to configuration register */
	long	config_bits;
	long	reg_bits;
	char	mmu_mode;
	long	val;
	
	gio_hi_config = (long *)(base + RGS14188) + gio_config_Hi;
	gio_hi_reg = (long *)(base + RGS14188) + gio_reg_Hi;
	config_bits = bitMask;
	reg_bits = 0x7 & ~config_bits;
	
	mmu_mode = 1;
	SwapMMUMode(&mmu_mode);
	*gio_hi_config = config_bits;
	*gio_hi_reg = reg_bits;
	val = *gio_hi_reg;
	val &= 0x00000007L;
	*gio_hi_config = 0;
	SwapMMUMode(&mmu_mode);
	
	return (short) val;
}
/*
 * SaveSense()
 */
void SaveSense(short slot, short sense)
{
	register long	*eep;
	
	eep = (long *) ((unsigned long) DEVBASE(slot) | EEPROM);
	eeWriteWord(eep, (short) 4, sense);
}
