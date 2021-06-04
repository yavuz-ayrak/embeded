/*
 * SPI_FREQGEN_AD9833.c
 *
 *  Created on: 5 May 2021
 *      Author: yayrak
 *      This document is used for AD9833 frequency generator which has 28bit resolution
 */

/*--Control and Accessories Divison of KALE ARGE-------
*
*This file created by yayrak in 2021 for DAC_FREQ_GEN_REV00
*/

#ifndef SPI_FREQGEN_AD9833
#define SPI_FREQGEN_AD9833
#include "PeripheralHeaderIncludes.h"
#include <math.h>


void SPI_Freq_Init(volatile struct SPI_REGS *s)
	{
		s->SPICCR.bit.SPISWRESET = 0;       // Put SPI in reset state
		s->SPICCR.bit.SPICHAR = 15;      // 8-bit character
		s->SPICCR.bit.SPILBK = 0;           // loopback off
		s->SPICCR.bit.CLKPOLARITY = 1;      // Fallind edge with delay

		s->SPICTL.bit.SPIINTENA = 0;        // disable SPI interrupt
		s->SPICTL.bit.TALK = 1;             // enable transmission
		s->SPICTL.bit.MASTER_SLAVE = 1;     // master
		s->SPICTL.bit.CLK_PHASE = 1;        // Fallind edge with delay
		s->SPICTL.bit.OVERRUNINTENA = 0;     // disable reciever overrun interrupt

		s->SPIBRR = 0;                      // SPICLK = LSPCLK / 4 (max SPICLK)

		s->SPICCR.bit.SPISWRESET = 1;         // Enable SPI
	}

Uint16 SPI_Freq_Gen_Write( volatile struct SPI_REGS *s, Uint16 data )
	{
	//	GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;
	    volatile Uint16 stat_reg1;

		s->SPITXBUF = (data);
		while(s->SPISTS.bit.INT_FLAG == 0){}

		while(s->SPISTS.bit.INT_FLAG==1) stat_reg1 = s->SPIRXBUF;

//		GpioDataRegs.GPASET.bit.GPIO15 = 1;
		return (stat_reg1);
	}

void AD9833_Freq_Send( Uint32 frequency, Uint16 waveType )
	{
		//waveType=0  sinwave
		//waveTppe=1  triangle
		//waveTppe=2  square
		Uint32 bitLow;
		Uint32 bitHigh;
		Uint16 freqData;
		Uint16 waveType2 = 0;

		if( waveType == 0 )waveType = 0;
		else if( waveType == 1 )waveType = 2;
		else {waveType = 0x0028;waveType2 = 0x2100;}
		//DB13 is set to 1 and DB8 is set to 1.(Control Register)
		SPI_Freq_Gen_Write( &SpibRegs, ( 0x2100 + waveType ) );
	//	SPI_Freq_Gen_Write( &SpibRegs, ( 0x2128 ) );

		////Send frequency data
		bitLow = ( 0x00003FFF & frequency ) | 0x00004000;     //mask for first 14 bits LSBs
		freqData = bitLow;
		SPI_Freq_Gen_Write( &SpibRegs, freqData );     //send LSB bits of frequency data to AD9833
		bitHigh = frequency >> 14;
		bitHigh = ( 0x00003FFF & bitHigh ) | 0x00004000;     //mask for second 14 bits MSBs
		freqData = bitHigh;
		SPI_Freq_Gen_Write( &SpibRegs, freqData );     //send MSB bits of frequency data to AD9833

		//Phase0 is set to 0 and others are set 0 (Phase Rgister)
		SPI_Freq_Gen_Write( &SpibRegs, 0xC000 + waveType2 + waveType );
	//	SPI_Freq_Gen_Write(&SpibRegs, 0xE128);

		//DB8 is set to 0 (Exit Reset)
		SPI_Freq_Gen_Write( &SpibRegs, 0x2000 + waveType );
	//	SPI_Freq_Gen_Write(&SpibRegs, 0x2028);

	}
#endif /*__SPI_FREQGEN_AD9833_H_*/



