/*===================================================================================                                            
 *  File Name : f2803x_sci_bmsk.h 
 *  Company   : KALE-ARGE
 *  Desc      : Header file containing handy bitmasks for setting up register values.
 *              This file defines the bitmasks for F2803X sci communucation
 *                                             
 *  Created on: 25 Tem 2019
 *  Author    : yayrak																	  
 ===================================================================================*/

#ifndef __F2803X_SCI_BMSK_H__
#define __F2803X_SCI_BMSK_H__

/*----------------------------------------------------
 * SCICCR communication control register
 ------------------------------------------------------*/

#define SCI_CHAR_X1         0x0000  // Character lenght bits
#define SCI_CHAR_X2         0x0001
#define SCI_CHAR_X3         0x0002
#define SCI_CHAR_X4         0x0003
#define SCI_CHAR_X5         0x0004
#define SCI_CHAR_X6         0x0005
#define SCI_CHAR_X7         0x0006
#define SCI_CHAR_X8         0x0007

#define SCI_ADDRESS_MODE    0x0008
#define SCI_IDLE_MODE       0x0000

#define SCI_LOOP_TEST_EN    0x0010
#define SCI_LOOP_TEST_DIS   0x0000

#define SCI_PARITY_EN       0x0020
#define SCI_PARITY_DIS      0x0000

#define SCI_PARITY_ODD      0x0000
#define SCI_PARITY_EVEN     0x0040

#define SCI_STOPBIT_ONE     0x0000
#define SCI_STOPBIT_TWO     0x0080

/*----------------------------------------------------
 * SCICTL1 control register 1
 ----------------------------------------------------*/

#define SCI_RXENA_EN        0x0001  // Send received characters to SCIRXEMU and SCIRXBUF
#define SCI_RXENA_DIS       0x0000  // Prevent received characters from into the SCIRXEMU and SCIRXBUF receiver buffers

#define SCI_TXENA_EN        0x0002
#define SCI_TXENA_DIS       0x0000

#define SCI_SLEEP_EN        0x0004
#define SCI_SLEEP_DIS       0x0000

#define SCI_TXWAKE_NO_SLCT  0x0000 // Tramsmit feature is not selected
#define SCI_TXWAKE_SELECT   0x0008 // TXWAKE is not cleared by SW RESET bit

#define SCI_SW_RESET_FLAG   0x0000 // Initializes the SCI state machines and operating flags
#define SCI_SW_RESER_REEN   0x0020 // Re enable the SCI by writing this

#define SCI_RXERR_INT_EN    0x0040
#define SCI_RXERR_INT_DIS   0x0000

/*----------------------------------------------------
 *SCI Baudrate set
 ----------------------------------------------------*/

#define SCI_BAUDRATE_FREQ   115200 // the desired baudrate frequency is writen

/*----------------------------------------------------
 * SCICTL2 control register 2
 ----------------------------------------------------*/

#define SCI_TX_INT_EN       0x0001
#define SCI_TX_INT_DIS      0x0000

#define SCI_RX_BK_INT_EN    0x0002
#define SCI_RX_BK_INT_DIS   0x0000

//#define baud 0x1C200

/*----------------------------------------------------
 * SCI FIFO Transmit register
 ----------------------------------------------------*/

#define SCI_TXFFIL_DEFAULT  0x0000

#define SCI_TX_FFINT_EN     0x0020
#define SCI_TX_FFINT_DIS    0x0000

#define SCI_TX_FFINT_CLR    0x0040
#define SCI_TX_FFINT_ZERO   0x0000

#define SCI_TX_FFRES_EN     0x2000
#define SCI_TX_FFRES_DIS    0x0000

#define SCI_FIFO_EN         0x4000
#define SCI_FIFO_DIS        0x0000

#define SCI_RST_EN          0x8000
#define SCI_RST_DIS         0x0000

/*----------------------------------------------------
 * SCI FIFO recieve register
 ----------------------------------------------------*/

#define SCI_RXFFIL_DEFAULT  0x0004 // Deðiþebilir

#define SCI_RX_FFINT_EN     0x0020
#define SCI_RX_FFINT_DIS    0x0000

#define SCI_RX_FFINT_CLR    0x0040
#define SCI_RX_FFINT_ZERO   0x0000

#define SCI_RX_FFRES_EN     0x2000
#define SCI_RX_FFRES_DIS    0x0000

#define SCI_RX_FFOVR_CLR    0x4000
#define SCI_RX_FFOVR_ZERO   0x0000

/*----------------------------------------------------
 * SCI FIFO control register
 ----------------------------------------------------*/

#define SCI_FFCT_DELAY_DEF  0x0000

#define SCI_FFCT_CDC_EN     0x2000
#define SCI_FFCT_CDC_DIS    0x0000

#define SCI_FFCT_ABD_CLR    0x4000
#define SCI_FFCT_ABD_ZERO   0x0000

/*----------------------------------------------------
 * SCIPRI Priority control register
 ----------------------------------------------------*/

#define SCI_PRI_FREE_RUN    0x0008
#define SCI_PRI_COMPLETE    0x0010
#define SCI_PRI_IMMADIATE   0x0000

#endif /* END OF THE F2803X_SCI_BMSK_H_ */
