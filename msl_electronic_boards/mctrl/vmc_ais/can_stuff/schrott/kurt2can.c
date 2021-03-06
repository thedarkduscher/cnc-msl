/** \file
 * Interface for transmitting data from and to KURT2's microcontroller via CAN bus.
 * $Id: $       
 */

/*
 * The contents of this file are subject to the Mozilla Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code is KURT2 Open Source Firmware and Win32 Software,
 * released March 15, 2001.
 *
 * The Initial Developer of the Original Code is GMD National Research
 * Center for Information Technology.  Portions created by GMD are
 * Copyright (C) 2000 - 2001 GMD National Research Center for
 * Information Technology.  All Rights Reserved.
 *
 * As of July 11, 2001, GMD has been integrated into the Fraunhofer-
 * Gesellschaft. As the new legal entity, Fraunhofer-Gesellschaft has thus
 * taken over all legal relationships involving GMD. Portions created by 
 * Fraunhofer-Gesellschaft are Copyright (C) 2002 Fraunhofer-Gesellschaft.
 * All Rights Reserved.
 * 
 * Contributor(s):
 */

#include <reg167.h>
#include "kurt2mc.h"

/**
 * Global buffer for the to be send CAN messages' data bytes.
 */
unsigned char cansend_data[8];

/**
 * Global buffer for the received CAN messages' data bytes.
 */
unsigned char canrec_data[8];

/**
 * Type definition for a volatile byte.
 */
typedef volatile unsigned char can_byte;

/**
 * Type definition for a volatile word.
 */
typedef volatile unsigned int can_word;

/**
 * Type definition for CAN register.
 */
typedef union {
  can_word word;        /**< Whole 16-bit register. */
  can_byte byte[2];     /**< Two parts of 8-bit each. */
} canreg;

/**
 * Type definition for CAN message object.
 */
typedef struct {
  canreg    C1MCR;      /**< Message Control Register. */
  canreg    C1UAR;      /**< Upper Arbitration Register. */
  canreg    C1LAR;      /**< Lower Arbitration Register. */
  can_byte  C1MCFG;     /**< Message Configuration Register. */
  can_byte  C1DA0;      /**< Data Area. */
  can_byte  C1DA1;      /**< Data Area. */
  can_byte  C1DA2;      /**< Data Area. */
  can_byte  C1DA3;      /**< Data Area. */
  can_byte  C1DA4;      /**< Data Area. */
  can_byte  C1DA5;      /**< Data Area. */
  can_byte  C1DA6;      /**< Data Area. */
  can_byte  C1DA7;      /**< Data Area. */
  can_byte  C1RESVD;    /**< Reserved. */
} messageobject;

#define C1CSR    (*(canreg *)0x00EF00)        /**< Control/Status Register. */
#define C1IR     (*(canreg *)0x00EF02)        /**< Interrupt Register. */
#define C1BTR    (*(canreg *)0x00EF04)        /**< Bit Timing Register. */
#define C1GMS    (*(canreg *)0x00EF06)        /**< Global Mask Short. */
#define C1UGML   (*(canreg *)0x00EF08)        /**< Global Mask Long. */
#define C1LGML   (*(canreg *)0x00EF0A)        /**< Global Mask Long. */
#define C1UMLM   (*(canreg *)0x00EF0C)        /**< Mask of Last Message. */
#define C1LMLM   (*(canreg *)0x00EF0E)        /**< Mask of Last Message. */
#define C1MOBJ1  (*(messageobject *)0x00EF10) /**< Message Object 1. */
#define C1MOBJ2  (*(messageobject *)0x00EF20) /**< Message Object 2. */
#define C1MOBJ3  (*(messageobject *)0x00EF30) /**< Message Object 3. */
#define C1MOBJ4  (*(messageobject *)0x00EF40) /**< Message Object 4. */
#define C1MOBJ5  (*(messageobject *)0x00EF50) /**< Message Object 5. */
#define C1MOBJ6  (*(messageobject *)0x00EF60) /**< Message Object 6. */
#define C1MOBJ7  (*(messageobject *)0x00EF70) /**< Message Object 7. */
#define C1MOBJ8  (*(messageobject *)0x00EF80) /**< Message Object 8. */
#define C1MOBJ9  (*(messageobject *)0x00EF90) /**< Message Object 9. */
#define C1MOBJ10 (*(messageobject *)0x00EFA0) /**< Message Object 10. */
#define C1MOBJ11 (*(messageobject *)0x00EFB0) /**< Message Object 11. */
#define C1MOBJ12 (*(messageobject *)0x00EFC0) /**< Message Object 12. */
#define C1MOBJ13 (*(messageobject *)0x00EFD0) /**< Message Object 13. */
#define C1MOBJ14 (*(messageobject *)0x00EFE0) /**< Message Object 14. */
#define C1MOBJ15 (*(messageobject *)0x00EFF0) /**< Message Object 15. */

/**
 * Assign word to CAN register.
 * \param reg CAN register.
 * \param value 16-bit variable.
 */
void setWord(canreg *reg, can_word value) {
  reg->word = value;
}

/**
 * Assign low byte to CAN register.
 * \param reg CAN register.
 * \param value 8-bit variable.
 */
void setLowByte(canreg *reg, can_byte value) {
  (*reg).byte[0] = value;
}

/**
 * Assign (high) byte to CAN register.
 * \param reg CAN register.
 * \param value 8-bit variable.
 */
void setByte(can_byte *reg, can_byte value) {
  *reg = value;
}

/**
 * Read word from CAN register.
 * \param reg CAN register.
 * \param value 16-bit variable.
 */
void getWord(canreg reg, can_word *value) {
  *value = reg.word;
}

/**
 * Initialize on-chip CAN controller.
 * See also chapter 18 of the C167 user's manual.
 * \param baud_rate 50, 125, 250, 500, or 1000 MBaud.
 * \param mc_no 0 or 1, depending whether the interface is used by the first or the second microcontroller.
 * \return success or exception.
 * \retval 0 function was successful.
 * \retval -1 invalid baud_rate.
 */
int can_init(int baud_rate, int mc_no) {
  can_word uar;

/**
 * Set baudrate.
 */
  setLowByte(&C1CSR, 0x41);       /* INIT:=1, CCE:=1 */
  switch (baud_rate) {
    case 50:
      setWord(&C1BTR, 0x7ac9);    /* BRP:=9, SJW:=3, TSEG1:=a, TSEG2:=7 */
      break;
    case 125:
      setWord(&C1BTR, 0x7ac3);    /* BRP:=3, SJW:=3, TSEG1:=a, TSEG2:=7 */
      break;
    case 250:
      setWord(&C1BTR, 0x7ac1);    /* BRP:=1, SJW:=3, TSEG1:=a, TSEG2:=7 */
      break;
    case 500:
      setWord(&C1BTR, 0x7ac0);    /* BRP:=0, SJW:=3, TSEG1:=a, TSEG2:=7 */
      break;
    case 1000:
      setWord(&C1BTR, 0x25c0);    /* BRP:=0, SJW:=3, TSEG1:=5, TSEG2:=2 */
      break;
    default:
      return -1;
  }
  setLowByte(&C1CSR, 0x01);       /* INIT:=1, CCE:=0 */

/**
 * Initialize CAN related registers.
 */
  setWord(&C1GMS,  0xE0FF);
  setWord(&C1UGML, 0xFFFF);
  setWord(&C1LGML, 0xF8FF);
  setWord(&C1UMLM, 0xFFFF);
  setWord(&C1LMLM, 0xF8FF);

  setWord(&C1MOBJ1.C1MCR,  0xFF7F);
  setWord(&C1MOBJ2.C1MCR,  0xFF7F);
  setWord(&C1MOBJ3.C1MCR,  0xFF7F);
  setWord(&C1MOBJ4.C1MCR,  0xFF7F);
  setWord(&C1MOBJ5.C1MCR,  0xFF7F);
  setWord(&C1MOBJ6.C1MCR,  0xFF7F);
  setWord(&C1MOBJ7.C1MCR,  0xFF7F);
  setWord(&C1MOBJ8.C1MCR,  0xFF7F);
  setWord(&C1MOBJ9.C1MCR,  0xFF7F);
  setWord(&C1MOBJ10.C1MCR, 0xFF7F);
  setWord(&C1MOBJ11.C1MCR, 0xFF7F);
  setWord(&C1MOBJ12.C1MCR, 0xFF7F);
  setWord(&C1MOBJ13.C1MCR, 0xFF7F);
  setWord(&C1MOBJ14.C1MCR, 0xFF7F);
  setWord(&C1MOBJ15.C1MCR, 0xFF7F);

/**
 * Set up message objects for receive.
 */
  setWord(&C1MOBJ1.C1MCR, 0x55A9);  /* INTPND:=0, RXIE:=1, TXIE:=1, MSGVAL:=1 */
                                    /* NEWDAT:=0, MSGLST:=0, TXRQ:=0, RMTPND:=0 */
  setByte(&C1MOBJ1.C1MCFG, 0x80);   /* XTD:=0, DIR:=0, DLC:=8 */
  uar = CAN_CONTROL + 16 * mc_no;
  setWord(&C1MOBJ1.C1UAR, (uar << 13) + (uar >> 3));
  setWord(&C1MOBJ1.C1LAR, 0x0000);  /* Lower Message ID: 000000000000000000 */

/*
 * Set up message objects for send.
 */  
  setWord(&C1MOBJ2.C1MCR, 0x59A9);  /* INTPND:=0, RXIE:=1, TXIE:=1, MSGVAL:=1 */
                                    /* NEWDAT:=0, CPUUPD:=1, TXRQ:=0, RMTPND:=0 */
  setByte(&C1MOBJ2.C1MCFG, 0x0488);   /* XTD:=0, DIR:=1, DLC:=8 */
  uar = _CAN_MOTOR_CONFOUT_ + 16 * mc_no;
  setWord(&C1MOBJ2.C1UAR, (uar << 13) + (uar >> 3));
  setWord(&C1MOBJ2.C1LAR, 0x0000);  /* Lower Message ID: 000000000000000000 */

////////////////////////////////////////////////////////////////////////////////////

  setWord(&C1MOBJ4.C1MCR, 0x59A9);  /* INTPND:=0, RXIE:=1, TXIE:=1, MSGVAL:=1 */
                                    /* NEWDAT:=0, CPUUPD:=1, TXRQ:=0, RMTPND:=0 */
  setByte(&C1MOBJ4.C1MCFG, 0x0488);   /* XTD:=0, DIR:=1, DLC:=8 */
  uar = CAN_INFO + 16 * mc_no;
  setWord(&C1MOBJ4.C1UAR, (uar << 13) + (uar >> 3));
  setWord(&C1MOBJ4.C1LAR, 0x0000);  /* Lower Message ID: 000000000000000000 */

////////////////////////////////////////////////////////////////////////////////////

  setWord(&C1MOBJ5.C1MCR, 0x59A9);  /* INTPND:=0, RXIE:=1, TXIE:=1, MSGVAL:=1 */
                                    /* NEWDAT:=0, CPUUPD:=1, TXRQ:=0, RMTPND:=0 */
  setByte(&C1MOBJ5.C1MCFG, 0xef88);   /* XTD:=0, DIR:=1, DLC:=8 */
  uar = _CAN_MOTOR_STATUSOUT_; // + 16 * mc_no;
  setWord(&C1MOBJ5.C1UAR, 0xa03f);
  setWord(&C1MOBJ5.C1LAR, 0x0000);  /* Lower Message ID: 000000000000000000 */
 
 ////////////////////////////////////////////////////////////////////////////////////

  setWord(&C1MOBJ6.C1MCR, 0x59A9);  /* INTPND:=0, RXIE:=1, TXIE:=1, MSGVAL:=1 */
                                 	/* NEWDAT:=0, CPUUPD:=1, TXRQ:=0, RMTPND:=0 */
  setByte(&C1MOBJ6.C1MCFG, 0x0688);   /* XTD:=0, DIR:=1, DLC:=8 */
  uar = CAN_ADC04_07 + 16 * mc_no;
  setWord(&C1MOBJ6.C1UAR, (uar << 13) + (uar >> 3));
  setWord(&C1MOBJ6.C1LAR, 0x0000);  /* Lower Message ID: 000000000000000000 */

////////////////////////////////////////////////////////////////////////////////////


  setWord(&C1MOBJ7.C1MCR, 0x59A9);  /* INTPND:=0, RXIE:=1, TXIE:=1, MSGVAL:=1 */
                                    /* NEWDAT:=0, CPUUPD:=1, TXRQ:=0, RMTPND:=0 */
  setByte(&C1MOBJ7.C1MCFG, 0x0788);   /* XTD:=0, DIR:=1, DLC:=8 */
  uar = _CAN_CONTROLLER_PAROUT_ + 16 * mc_no;
  setWord(&C1MOBJ7.C1UAR, (uar << 13) + (uar >> 3));
  setWord(&C1MOBJ7.C1LAR, 0x0000);  /* Lower Message ID: 000000000000000000 */

  ////////////////////////////////////////////////////////////////////////////////////

  setWord(&C1MOBJ8.C1MCR, 0x59A9);  /* INTPND:=0, RXIE:=1, TXIE:=1, MSGVAL:=1 */
                                    /* NEWDAT:=0, CPUUPD:=1, TXRQ:=0, RMTPND:=0 */
  setByte(&C1MOBJ8.C1MCFG, 0x88);   /* XTD:=0, DIR:=1, DLC:=8 */
  uar = CAN_ADC12_15 + 16 * mc_no;
  setWord(&C1MOBJ8.C1UAR, (uar << 13) + (uar >> 3));
  setWord(&C1MOBJ8.C1LAR, 0x0000);  /* Lower Message ID: 000000000000000000 */

  ////////////////////////////////////////////////////////////////////////////////////

  setWord(&C1MOBJ9.C1MCR, 0x59A9);  /* INTPND:=0, RXIE:=1, TXIE:=1, MSGVAL:=1 */
                                    /* NEWDAT:=0, CPUUPD:=1, TXRQ:=0, RMTPND:=0 */
  setByte(&C1MOBJ9.C1MCFG, 0x88);   /* XTD:=0, DIR:=1, DLC:=8 */
  uar = CAN_ENCODER + 16 * mc_no;
  setWord(&C1MOBJ9.C1UAR, (uar << 13) + (uar >> 3));
  setWord(&C1MOBJ9.C1LAR, 0x0000);  /* Lower Message ID: 000000000000000000 */

 ////////////////////////////////////////////////////////////////////////////////////

  setWord(&C1MOBJ10.C1MCR, 0x59A9); /* INTPND:=0, RXIE:=1, TXIE:=1, MSGVAL:=1 */
                                    /* NEWDAT:=0, CPUUPD:=1, TXRQ:=0, RMTPND:=0 */
  setByte(&C1MOBJ10.C1MCFG, 0x28);  /* XTD:=0, DIR:=1, DLC:=2 */
  uar = CAN_BUMPERC + 16 * mc_no;
  setWord(&C1MOBJ10.C1UAR, (uar << 13) + (uar >> 3));
  setWord(&C1MOBJ10.C1LAR, 0x0000); /* Lower Message ID: 000000000000000000 */

 ////////////////////////////////////////////////////////////////////////////////////

  setWord(&C1MOBJ11.C1MCR, 0x59A9); /* INTPND:=0, RXIE:=1, TXIE:=1, MSGVAL:=1 */
                                    /* NEWDAT:=0, CPUUPD:=1, TXRQ:=0, RMTPND:=0 */
  setByte(&C1MOBJ11.C1MCFG, 0x88);  /* XTD:=0, DIR:=1, DLC:=8 */
  uar = CAN_POSITION + 16 * mc_no;
  setWord(&C1MOBJ11.C1UAR, (uar << 13) + (uar >> 3));
  setWord(&C1MOBJ11.C1LAR, 0x0000);  /* Lower Message ID: 000000000000000000 */

 ////////////////////////////////////////////////////////////////////////////////////

  setWord(&C1MOBJ12.C1MCR, 0x59A9); /* INTPND:=0, RXIE:=1, TXIE:=1, MSGVAL:=1 */
                                    /* NEWDAT:=0, CPUUPD:=1, TXRQ:=0, RMTPND:=0 */
  setByte(&C1MOBJ12.C1MCFG, 0x88);  /* XTD:=0, DIR:=1, DLC:=8 */
  uar = CAN_ENC_ODO + 16 * mc_no;
  setWord(&C1MOBJ12.C1UAR, (uar << 13) + (uar >> 3));
  setWord(&C1MOBJ12.C1LAR, 0x0000); /* Lower Message ID: 000000000000000000 */

 ////////////////////////////////////////////////////////////////////////////////////

  setWord(&C1MOBJ13.C1MCR, 0x59A9); /* INTPND:=0, RXIE:=1, TXIE:=1, MSGVAL:=1 */
                                    /* NEWDAT:=0, CPUUPD:=1, TXRQ:=0, RMTPND:=0 */
  setByte(&C1MOBJ13.C1MCFG, 0x88);  /* XTD:=0, DIR:=1, DLC:=8 */
  uar = CAN_TILT_COMP + 16 * mc_no;
  setWord(&C1MOBJ13.C1UAR, (uar << 13) + (uar >> 3));
  setWord(&C1MOBJ13.C1LAR, 0x0000); /* Lower Message ID: 000000000000000000 */

 ////////////////////////////////////////////////////////////////////////////////////

  setWord(&C1MOBJ14.C1MCR, 0x59A9); /* INTPND:=0, RXIE:=1, TXIE:=1, MSGVAL:=1 */
                                    /* NEWDAT:=0, CPUUPD:=1, TXRQ:=0, RMTPND:=0 */
  setByte(&C1MOBJ14.C1MCFG, 0x88);  /* XTD:=0, DIR:=1, DLC:=8 */
  uar = CAN_GYRO + 16 * mc_no;
  setWord(&C1MOBJ14.C1UAR, (uar << 13) + (uar >> 3));
  setWord(&C1MOBJ14.C1LAR, 0x0000); /* Lower Message ID: 000000000000000000 */

  setLowByte(&C1CSR, 0x00);         /* INIT:=0, CCE:=0 */

  return 0;
}

/**
 * Receive CAN message.
 * Move the data bytes of a received CAN message to the global variable canrec_data.
 * \param mobj number of message object buffer to be read.
 * \return success or exception.
 * \retval 0 function was successful.
 * \retval 1 no new CAN message could be read.
 * \retval -1 invalid mobj.
 */
int can_receive(char mobj) {
  can_word mcr;
  char rc = 1;                            /* return code 1: no new CAN message */

  switch (mobj) {
    case MSG_CONTROL:
      getWord(C1MOBJ1.C1MCR, &mcr);
      if (mcr & 0x0200) {                 /* NEWDAT set by CAN controller? */
        rc = 0;
        canrec_data[0] = C1MOBJ1.C1DA0;
        canrec_data[1] = C1MOBJ1.C1DA1;
        canrec_data[2] = C1MOBJ1.C1DA2;
        canrec_data[3] = C1MOBJ1.C1DA3;
        canrec_data[4] = C1MOBJ1.C1DA4;
        canrec_data[5] = C1MOBJ1.C1DA5;
        canrec_data[6] = C1MOBJ1.C1DA6;
        canrec_data[7] = C1MOBJ1.C1DA7;
      }
      setWord(&C1MOBJ1.C1MCR, 0xFDFF);    /* NEWDAT:=0 */
      break;
    default:
      rc = -1;
  }

  return rc;
}

/**
 * Send CAN message.
 * Move the data bytes of the global variable cansend_data to the appropriate message buffer and submit transmission.
 * \param mobj number of message object buffer to be used for send.
 * \return success or exception.
 * \retval 0 function was successful.
 * \retval -1 invalid mobj.
 */
int can_send(char mobj) {

  switch (mobj) {
    case 2:
      setWord(&C1MOBJ2.C1MCR, 0xF9FF);    /* NEWDAT:=0, CPUUPD:=1 */
      setByte(&C1MOBJ2.C1DA0, cansend_data[0]);
      setByte(&C1MOBJ2.C1DA1, cansend_data[1]);
      setByte(&C1MOBJ2.C1DA2, cansend_data[2]);
      setByte(&C1MOBJ2.C1DA3, cansend_data[3]);
      setByte(&C1MOBJ2.C1DA4, cansend_data[4]);
      setByte(&C1MOBJ2.C1DA5, cansend_data[5]);
      setByte(&C1MOBJ2.C1DA6, cansend_data[6]);
      setByte(&C1MOBJ2.C1DA7, 0xcd );  //cansend_data[7]);
      setWord(&C1MOBJ2.C1MCR, 0xE6FF);    /* NEWDAT:=1, CPUUPD:=0, TXRQ:=1 */
      break;
    case MSG_INFO:
      setWord(&C1MOBJ4.C1MCR, 0xF9FF);    /* NEWDAT:=0, CPUUPD:=1 */
      setByte(&C1MOBJ4.C1DA0, cansend_data[0]);
      setByte(&C1MOBJ4.C1DA1, cansend_data[1]);
      setByte(&C1MOBJ4.C1DA2, cansend_data[2]);
      setByte(&C1MOBJ4.C1DA3, cansend_data[3]);
      setByte(&C1MOBJ4.C1DA4, cansend_data[4]);
      setByte(&C1MOBJ4.C1DA5, cansend_data[5]);
      setByte(&C1MOBJ4.C1DA6, cansend_data[6]);
      setByte(&C1MOBJ4.C1DA7, cansend_data[7]);
      setWord(&C1MOBJ4.C1MCR, 0xE6FF);    /* NEWDAT:=1, CPUUPD:=0, TXRQ:=1 */
      break;
    case _MSG_MOTOR_STATUSOUT_:
      setWord(&C1MOBJ5.C1MCR, 0xF9FF);    /* NEWDAT:=0, CPUUPD:=1 */
      setByte(&C1MOBJ5.C1DA0, cansend_data[0]);
      setByte(&C1MOBJ5.C1DA1, cansend_data[1]);
      setByte(&C1MOBJ5.C1DA2, cansend_data[2]);
      setByte(&C1MOBJ5.C1DA3, cansend_data[3]);
      setByte(&C1MOBJ5.C1DA4, cansend_data[4]);
      setByte(&C1MOBJ5.C1DA5, cansend_data[5]);
      setByte(&C1MOBJ5.C1DA6, cansend_data[6]);
      setByte(&C1MOBJ5.C1DA7, cansend_data[7]);
      setWord(&C1MOBJ5.C1MCR, 0xE6FF);    /* NEWDAT:=1, CPUUPD:=0, TXRQ:=1 */
      break;
    case MSG_ADC04_07:
      setWord(&C1MOBJ6.C1MCR, 0xF9FF);    /* NEWDAT:=0, CPUUPD:=1 */
      setByte(&C1MOBJ6.C1DA0, cansend_data[0]);
      setByte(&C1MOBJ6.C1DA1, cansend_data[1]);
      setByte(&C1MOBJ6.C1DA2, cansend_data[2]);
      setByte(&C1MOBJ6.C1DA3, cansend_data[3]);
      setByte(&C1MOBJ6.C1DA4, cansend_data[4]);
      setByte(&C1MOBJ6.C1DA5, cansend_data[5]);
      setByte(&C1MOBJ6.C1DA6, cansend_data[6]);
      setByte(&C1MOBJ6.C1DA7, cansend_data[7]);
      setWord(&C1MOBJ6.C1MCR, 0xE6FF);    /* NEWDAT:=1, CPUUPD:=0, TXRQ:=1 */
     break;
    case _MSG_CONTROLLER_PAROUT_:
      setWord(&C1MOBJ7.C1MCR, 0xF9FF);    /* NEWDAT:=0, CPUUPD:=1 */

	   setWord(&C1MOBJ7.C1UAR, 0xffff);
 

      setByte(&C1MOBJ7.C1DA0, cansend_data[0]);
      setByte(&C1MOBJ7.C1DA1, cansend_data[1]);
      setByte(&C1MOBJ7.C1DA2, cansend_data[2]);
      setByte(&C1MOBJ7.C1DA3, cansend_data[3]);
      setByte(&C1MOBJ7.C1DA4, cansend_data[4]);
      setByte(&C1MOBJ7.C1DA5, cansend_data[5]);
      setByte(&C1MOBJ7.C1DA6, cansend_data[6]);
      setByte(&C1MOBJ7.C1DA7, cansend_data[7]);
      setWord(&C1MOBJ7.C1MCR, 0xE6FF);    /* NEWDAT:=1, CPUUPD:=0, TXRQ:=1 */
      break;
    case MSG_ADC12_15:
      setWord(&C1MOBJ8.C1MCR, 0xF9FF);    /* NEWDAT:=0, CPUUPD:=1 */
      setByte(&C1MOBJ8.C1DA0, cansend_data[0]);
      setByte(&C1MOBJ8.C1DA1, cansend_data[1]);
      setByte(&C1MOBJ8.C1DA2, cansend_data[2]);
      setByte(&C1MOBJ8.C1DA3, cansend_data[3]);
      setByte(&C1MOBJ8.C1DA4, cansend_data[4]);
      setByte(&C1MOBJ8.C1DA5, cansend_data[5]);
      setByte(&C1MOBJ8.C1DA6, cansend_data[6]);
      setByte(&C1MOBJ8.C1DA7, cansend_data[7]);
      setWord(&C1MOBJ8.C1MCR, 0xE6FF);    /* NEWDAT:=1, CPUUPD:=0, TXRQ:=1 */
      break;
    case MSG_ENCODER:
      setWord(&C1MOBJ9.C1MCR, 0xF9FF);    /* NEWDAT:=0, CPUUPD:=1 */
      setByte(&C1MOBJ9.C1DA0, cansend_data[0]);
      setByte(&C1MOBJ9.C1DA1, cansend_data[1]);
      setByte(&C1MOBJ9.C1DA2, cansend_data[2]);
      setByte(&C1MOBJ9.C1DA3, cansend_data[3]);
      setByte(&C1MOBJ9.C1DA4, cansend_data[4]);
      setByte(&C1MOBJ9.C1DA5, cansend_data[5]);
      setByte(&C1MOBJ9.C1DA6, cansend_data[6]);
      setByte(&C1MOBJ9.C1DA7, cansend_data[7]);
      setWord(&C1MOBJ9.C1MCR, 0xE6FF);    /* NEWDAT:=1, CPUUPD:=0, TXRQ:=1 */
      break;
    case MSG_BUMPERC:
      setWord(&C1MOBJ10.C1MCR, 0xF9FF);   /* NEWDAT:=0, CPUUPD:=1 */
      setByte(&C1MOBJ10.C1DA0, cansend_data[0]);
      setByte(&C1MOBJ10.C1DA1, cansend_data[1]);
       setWord(&C1MOBJ10.C1MCR, 0xE6FF);  /* NEWDAT:=1, CPUUPD:=0, TXRQ:=1 */
      break;
    case MSG_POSITION:
      setWord(&C1MOBJ11.C1MCR, 0xF9FF);   /* NEWDAT:=0, CPUUPD:=1 */
      setByte(&C1MOBJ11.C1DA0, cansend_data[0]);
      setByte(&C1MOBJ11.C1DA1, cansend_data[1]);
      setByte(&C1MOBJ11.C1DA2, cansend_data[2]);
      setByte(&C1MOBJ11.C1DA3, cansend_data[3]);
      setByte(&C1MOBJ11.C1DA4, cansend_data[4]);
      setByte(&C1MOBJ11.C1DA5, cansend_data[5]);
      setByte(&C1MOBJ11.C1DA6, cansend_data[6]);
      setByte(&C1MOBJ11.C1DA7, cansend_data[7]);
      setWord(&C1MOBJ11.C1MCR, 0xE6FF);   /* NEWDAT:=1, CPUUPD:=0, TXRQ:=1 */
      break;
    case MSG_ENC_ODO:
      setWord(&C1MOBJ12.C1MCR, 0xF9FF);   /* NEWDAT:=0, CPUUPD:=1 */
      setByte(&C1MOBJ12.C1DA0, cansend_data[0]);
      setByte(&C1MOBJ12.C1DA1, cansend_data[1]);
      setByte(&C1MOBJ12.C1DA2, cansend_data[2]);
      setByte(&C1MOBJ12.C1DA3, cansend_data[3]);
      setByte(&C1MOBJ12.C1DA4, cansend_data[4]);
      setByte(&C1MOBJ12.C1DA5, cansend_data[5]);
      setByte(&C1MOBJ12.C1DA6, cansend_data[6]);
      setByte(&C1MOBJ12.C1DA7, cansend_data[7]);
      setWord(&C1MOBJ12.C1MCR, 0xE6FF);   /* NEWDAT:=1, CPUUPD:=0, TXRQ:=1 */
      break;
    case MSG_TILT_COMP:
      setWord(&C1MOBJ13.C1MCR, 0xF9FF);   /* NEWDAT:=0, CPUUPD:=1 */
      setByte(&C1MOBJ13.C1DA0, cansend_data[0]);
      setByte(&C1MOBJ13.C1DA1, cansend_data[1]);
      setByte(&C1MOBJ13.C1DA2, cansend_data[2]);
      setByte(&C1MOBJ13.C1DA3, cansend_data[3]);
      setByte(&C1MOBJ13.C1DA4, cansend_data[4]);
      setByte(&C1MOBJ13.C1DA5, cansend_data[5]);
      setByte(&C1MOBJ13.C1DA6, cansend_data[6]);
      setByte(&C1MOBJ13.C1DA7, cansend_data[7]);
      setWord(&C1MOBJ13.C1MCR, 0xE6FF);   /* NEWDAT:=1, CPUUPD:=0, TXRQ:=1 */
      break;
    case MSG_GYRO:
      setWord(&C1MOBJ14.C1MCR, 0xF9FF);   /* NEWDAT:=0, CPUUPD:=1 */
      setByte(&C1MOBJ14.C1DA0, cansend_data[0]);
      setByte(&C1MOBJ14.C1DA1, cansend_data[1]);
      setByte(&C1MOBJ14.C1DA2, cansend_data[2]);
      setByte(&C1MOBJ14.C1DA3, cansend_data[3]);
      setByte(&C1MOBJ14.C1DA4, cansend_data[4]);
      setByte(&C1MOBJ14.C1DA5, cansend_data[5]);
      setByte(&C1MOBJ14.C1DA6, cansend_data[6]);
      setByte(&C1MOBJ14.C1DA7, cansend_data[7]);
      setWord(&C1MOBJ14.C1MCR, 0xE6FF);   /* NEWDAT:=1, CPUUPD:=0, TXRQ:=1 */
      break;
    default:
      return -1;
  }

  return 0;
}
