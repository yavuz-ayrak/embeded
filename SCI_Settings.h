/*===================================================================================                                            
 *  File Name : SCI_Settings.h 
 *  Company   : KALE-ARGE
 *  Desc      : Created for settings of sci
 *                                             
 *  Created on: 19 Tem 2019
 *  Author    : yayrak																	  
 ===================================================================================*/

#ifndef __SCI_SETTINGS_H__
#define __SCI_SETTINGS_H__

#include "f2803x_sci_bmsk.h"
#include "f2803xdrvlib.h"

//================================================================================//

/*-----------------------------------------------
 * SCICCR communication control register
 *-----------------------------------------------*/

#define SCI_CCR_INIT        ( SCI_CHAR_X8 + \
                              SCI_IDLE_MODE + \
                              SCI_LOOP_TEST_DIS + \
                              SCI_PARITY_DIS + \
                              SCI_PARITY_ODD + \
                              SCI_STOPBIT_ONE )

/*-----------------------------------------------
 * SCICTL1 control register 1
 *-----------------------------------------------*/

#define SCI_CTL1_INIT       (  SCI_RXENA_EN + \
                               SCI_TXENA_EN + \
                               SCI_SLEEP_DIS + \
                               SCI_TXWAKE_NO_SLCT + \
                               SCI_SW_RESER_REEN + \
                               SCI_RXERR_INT_DIS )

/*-----------------------------------------------
 * SCICTL2 control register 2
 *-----------------------------------------------*/

#define SCI_CTL2_INIT       ( SCI_TX_INT_EN + \
                              SCI_RX_BK_INT_EN )

/*-----------------------------------------------
 * SCI FIFO Transmit register
 *-----------------------------------------------*/

#define SCI_FIFO_TX_INIT    ( SCI_TXFFIL_DEFAULT + \
                              SCI_TX_FFINT_DIS + \
                              SCI_TX_FFINT_ZERO + \
                              SCI_TX_FFRES_EN + \
                              SCI_FIFO_EN + \
                              SCI_RST_EN )

/*-----------------------------------------------
 * SCI FIFO Receiver register
 *-----------------------------------------------*/

#define SCI_FIFO_RX_INIT    ( SCI_RXFFIL_DEFAULT + \
                              SCI_RX_FFINT_EN + \
                              SCI_RX_FFINT_ZERO + \
                              SCI_RX_FFRES_EN + \
                              SCI_RX_FFOVR_ZERO )

/*-----------------------------------------------
 * SCI FIFO control register
 *-----------------------------------------------*/

#define SCI_FIFO_CT_INIT    ( SCI_FFCT_DELAY_DEF + \
                              SCI_FFCT_CDC_DIS + \
                              SCI_FFCT_ABD_ZERO )
/*-----------------------------------------------
 * SCIPRI Priority control register
 *-----------------------------------------------*/

#define SCI_PRI_INIT        ( SCI_PRI_IMMADIATE )

//================================================================================//

Uint16 temp1;
#define SCI_INIT_MACRO(m,v)                                                      \
                                                                                 \
         /*--- The whole initialization settings sends to register setting ---*/ \
                                                                                 \
    (*SCI[m]).SCICCR.all  = SCI_CCR_INIT;                                        \
    (*SCI[m]).SCICTL1.all = SCI_CTL1_INIT;                                       \
    (*SCI[m]).SCICTL2.all = SCI_CTL2_INIT;                                       \
    (*SCI[m]).SCIFFTX.all = SCI_FIFO_TX_INIT;                                    \
    (*SCI[m]).SCIFFRX.all = SCI_FIFO_RX_INIT;                                    \
    (*SCI[m]).SCIFFCT.all = SCI_FIFO_CT_INIT;                                    \
    (*SCI[m]).SCIPRI.all  = SCI_PRI_INIT;                                        \
                                                                                 \
         /*--- m value indicates the intended baud rate  ---*/                   \
                                                                                 \
    temp1 = ((LSPCLK_FREQ/(v*8))-1);                                             \
    (*SCI[m]).SCILBAUD  = temp1 & 0x00FF;                                        \
    (*SCI[m]).SCIHBAUD  = (temp1 & ( 0xFF00 )) << 8;                             \
                                                                                 \
/*  For example; v maybe 115200, 9600, 4800 and so on */                         \

#endif /* END OF THE SCI_SETTINGS_H_ */

