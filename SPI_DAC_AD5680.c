/* SPI_DAC_AD5680.c
 *
 *  Created on: 21 Eyl 2020
 *  Author: Yavuz AYRAK (yayrak@kalearge.com.tr)
 *  Device: TMS320F28035XX
 *
 */

/*-->Control and Accessories Divison of KALE ARGE<-------
*
*This file created by yayrak in 2020 for PM_Sensorless
*/
#ifndef SPI_DAC_AD5680
#define SPI_DAC_AD5680
#include "PeripheralHeaderIncludes.h"
#include <math.h>
//#include "DRV8301_SPI.h""

#define DAC_REF_VOLT 4.997    //DAC in aldigi referans voltaj degeri
 void SPI_Baslat( volatile struct SPI_REGS *s )
{
	s->SPICCR.bit.SPISWRESET = 0;       // Put SPI in reset state
	s->SPICCR.bit.SPICHAR = 7;      // 8-bit character
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

 /*-----------SPI DATA YAZMA-------------------*/

 Uint16 SPI_YAZ( volatile struct SPI_REGS *s, Uint16 data )
{
//    int totalData=0;
	volatile Uint16 stat_reg1;
	volatile Uint16 dummy;

	//  while (s->SPISTS.bit.INT_FLAG == 1){ dummy = s->SPIRXBUF;}

	s->SPITXBUF = ( data );
	while ( s->SPISTS.bit.INT_FLAG == 0 )
		;
	//   while (s->SPISTS.bit.BUFFULL_FLAG == 1){}

	while ( s->SPISTS.bit.INT_FLAG == 1 )
	{
		dummy = s->SPIRXBUF;
	}

	return stat_reg1;
}
/*---------------------------------------------------*/

/*----------SPI DATA OKUMA---------------------*/


/*---------------------------------------------*/

/*------------ Writing data to the AD5680 18 bit DAC----------*/

 void AD5680_DAC_Data_Send( Uint32 verilenSicaklik, float offsetDeger )
	{
	volatile float verilenVolt;
	volatile Uint32 dacDataToAD5680;
	volatile Uint16 i1 , i2 , i3 , i4;

		verilenVolt = -4 * powf( 10, -9 ) * powf( verilenSicaklik, 3 );
		verilenVolt = verilenVolt + 6 * powf( 10, -6 ) * powf( verilenSicaklik, 2 );
		verilenVolt = verilenVolt + 0.0392 * verilenSicaklik;
		verilenVolt = ( verilenVolt + 0.0536 ) + offsetDeger;     // verilecek mV
		verilenVolt = verilenVolt / 1000;     //verilecek Volt
		/*AD56080 18bit DAC entegresindeki register a yazilacak olan deger K tipi thermocouple formulu ile hesaplaniyor */

		verilenVolt = ( verilenVolt / DAC_REF_VOLT ) * 262144;
		dacDataToAD5680 = verilenVolt;
		dacDataToAD5680 = dacDataToAD5680 * 4;
		/*AD5680 18bit DAC entegresideki register a yazilacak degeri voltajdan sayiya cevirmek icin gerekli olan formul*/

		i2 = 16;
		//   GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;
		GpioDataRegs.GPACLEAR.bit.GPIO22 = 1;     // SYNC pin of DAC sets to clear (DAC a yazma sarti i?in gerekli)
		if( GpioDataRegs.GPADAT.bit.GPIO22 == 0 )
		{
			for ( i1 = 0; i1 < 3; ++i1 )
			{
				i3 = ( dacDataToAD5680 >> i2 );
				i3 &= 0x000000FF;
				i4 = i3 << 8;
				SPI_YAZ( &SpiaRegs, i4 );
				i2 = i2 - 8;
			}
			GpioDataRegs.GPASET.bit.GPIO22 = 1;     // SYNC pin of DAC sets to logic 1 after complete the data transfer
			//  GpioDataRegs.GPASET.bit.GPIO19 = 1;
		}
		/*AD5680 18bit DAC entegresine SPI ile haberlesme icin 3 kere kaydirilarak yazdirilacak */
	}

/*------------------------------------------------------------*/
#endif /*SPI_DAC_AD5680*/
