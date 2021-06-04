/*
 * AD5680_fonc.c
 *
 *  Created on: 13 Kas 2020
 *      Author: yayrak
 */

/*--Control and Accessories Divison of KALE ARGE-------
*


// Initialize the SPI peripheral*/
#include "PeripheralHeaderIncludes.h"
#include "DRV8301_SPI.h"
#include <math.h>

void fDRV8301_SPI_Init(volatile struct SPI_REGS *s)
{
	s->SPICCR.bit.SPISWRESET = 0; 		// Put SPI in reset state
	s->SPICCR.bit.SPICHAR = 7;		// 8-bit character
	s->SPICCR.bit.SPILBK = 0;     		// loopback off
	s->SPICCR.bit.CLKPOLARITY = 1;  	// Fallind edge with delay

	s->SPICTL.bit.SPIINTENA = 0;		// disable SPI interrupt
	s->SPICTL.bit.TALK = 1;				// enable transmission
	s->SPICTL.bit.MASTER_SLAVE = 1;		// master
	s->SPICTL.bit.CLK_PHASE = 1;    	// Fallind edge with delay
	s->SPICTL.bit.OVERRUNINTENA = 0;	// disable reciever overrun interrupt

	s->SPIBRR = 0;						// SPICLK = LSPCLK / 4 (max SPICLK)

	s->SPICCR.bit.SPISWRESET=1;  		// Enable SPI
}

/*****************************************************************************/
// Read from a DRV8301 Register
/*****************************************************************************/
Uint16 fDRV8301_SPI_Read(volatile struct SPI_REGS *s, Uint16 address)
{
	union DRV8301_SPI_WRITE_WORD_REG w;
	volatile Uint16 dummy;

	w.bit.R_W = 1;							//we are initiating a read
	w.bit.ADDRESS = address;				//load the address
	w.bit.DATA = 0;							//dummy data;

	s->SPITXBUF = w.all;					//send out the data

	while(s->SPISTS.bit.INT_FLAG == 0);		//wait for the packet to complete

	dummy = s->SPIRXBUF;					//dummy read to clear the INT_FLAG bit

	w.bit.R_W = 1;							//we are initiating a read
	w.bit.ADDRESS = address;				//load the address
	w.bit.DATA = 0;							//dummy data;

	s->SPITXBUF = w.all;					//send out the data

	while(s->SPISTS.bit.INT_FLAG == 0);		//wait for the packet to complete

	dummy = s->SPIRXBUF;					//dummy read to clear the INT_FLAG bit

	return(dummy);

}

/*****************************************************************************/
// Write to a DRV8301 Register
// SPI writes always clock out the data in Status Register 1.
// Since it's available we'll return the status from this function
/*****************************************************************************/
Uint16 fDRV8301_SPI_Write(volatile struct SPI_REGS *s, Uint16 address, Uint16 data)
{
	union DRV8301_SPI_WRITE_WORD_REG w;
	volatile Uint16 stat_reg1;

	w.bit.R_W = 0;							//we are initiating a write
	w.bit.ADDRESS = address;				//load the address
	w.bit.DATA = data;						//data to be written;

	s->SPITXBUF = w.all;					//send out the data

	while(s->SPISTS.bit.INT_FLAG == 0);		//wait for the packet to complete

	stat_reg1 = s->SPIRXBUF;				//read returned value of Status Register 1 and clear the INT_FLAG bit

	return(stat_reg1);

}

/*----------------------------------------------*/
Uint16 fDAC_YAZ(volatile struct SPI_REGS *s,Uint16 data)
{
//    int totalData=0;
    volatile Uint16 stat_reg1;
    volatile Uint16 dummy;

  //  while (s->SPISTS.bit.INT_FLAG == 1){ dummy = s->SPIRXBUF;}

    s->SPITXBUF = (data);
    while(s->SPISTS.bit.INT_FLAG == 0);
 //   while (s->SPISTS.bit.BUFFULL_FLAG == 1){}

    while (s->SPISTS.bit.INT_FLAG == 1){ dummy = s->SPIRXBUF;}


    return stat_reg1;
}

void AD5680_TEMP_SEND( float fSicaklik, float fOffset )
	{
		float fVerilenVolt,fBolumDeger;
		Uint32 fDacData;
		Uint16 fa,fb,fc,fd;
		fc=16; fd=0; fa=0; fb=0;

		fVerilenVolt = -4 * powf( 10, -9 ) * powf( fSicaklik, 3 );
		fVerilenVolt = fVerilenVolt
		        + 6 * powf( 10, -6 ) * powf( fSicaklik, 2 );
		fVerilenVolt = fVerilenVolt + 0.0392 * fSicaklik;
		fVerilenVolt = ( fVerilenVolt + 0.0536 ) - fOffset;     // verilecek mV
		fVerilenVolt = fVerilenVolt / 1000;     // verilecek V

		fBolumDeger = ( fVerilenVolt / 4.997 ) * 262144;     //DAC_REF_VOLT=4.997
		fDacData = fBolumDeger;
		fDacData = fDacData * 4;

		for ( fa = 0; fa < 3; fa++ )
		{
			fb = ( fDacData >> fc ); //(toplamGonderilecekData>>c);
			fb &= 0x000000FF;
			fd = fb << 8;
			fDAC_YAZ( &SpiaRegs, fd );
			fc = fc - 8;
		}
	}

