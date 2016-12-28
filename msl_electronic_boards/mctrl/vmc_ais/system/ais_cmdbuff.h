//////////////////////////////////////////////////////////////////////////////
/// \defgroup Communication Buffer for AISC167Board
//@{
/// \file ais_combuff.h
///
/// \brief  Communication Buffer and Fetch&Validate Functions for AISC167
///         Communication
///
/// \author Adam Cwientzek
///
/// \version 0.8
///
/// \date 27.12.2005
///
/// \note none
///
//////////////////////////////////////////////////////////////////////////////

#ifndef _AIS_CMDBUFF_H_
#define _AIS_CMDBUFF_H_

#include "ais_typedef.h"

// cmd type definition
#define _CMD_RS232_         0
#define _CMD_CAN_           1

// Buffer size
#define _CMDB_RX_SIZE_      10
#define _CMDB_TX_SIZE_      5
#define _CMDB_MAXDATA_      30


// Selector for Processing Data
#define _CMDB_ALL_          1
#define _CMDB_ONE_          0


// Channels
#define _CMDB_CH_ALL_       0
#define _CMDB_CH_ASC0_      1
#define _CMDB_CH_CAN_       2


// Error bits in SYSINF Byte
#define _CMDB_ERR_OK_       0x00
#define _CMDB_ERR_CRC_      0x01
#define _CMDB_ERR_COUNT_    0x02
#define _CMDB_ERR_UNKNOWN_  0x04

#define _CMDB_RX_           0
#define _CMDB_TX_           1

#define _CMDB_FIRST_        0
#define _CMDB_LAST_         1


typedef struct CmdStruct {
    VMC_UCHAR_8 vmc_cmd_type;
    VMC_UCHAR_8 rxaddr, txaddr;
    VMC_UCHAR_8 count, retcount, sysinf;
    VMC_UCHAR_8 datalen, channel;
    VMC_UCHAR_8 cmdgrp, cmd;
    VMC_UCHAR_8 data[_CMDB_MAXDATA_];
};


// Implemented
VMC_UCHAR_8 cmdb_load_command(VMC_UCHAR_8 Channel, VMC_UCHAR_8 all);

// NOT !!! Implemented      DOCH!
VMC_UCHAR_8 cmdb_send_command(VMC_UCHAR_8 all);

// Implemented
VMC_UCHAR_8 cmdb_get_command(struct CmdStruct *Command);

// Implemented
void cmdb_set_command(struct CmdStruct *Command);

// Implemented
VMC_UCHAR_8 cmdb_isempty(VMC_UCHAR_8 Buffer);

// Implemented
VMC_UCHAR_8 cmdb_count(VMC_UCHAR_8 Buffer);

void cmdb_dataAppendStr(struct CmdStruct *Command, VMC_UCHAR_8 *string);
void cmdb_dataAppendChar(struct CmdStruct *Command, VMC_UCHAR_8 param);
void cmdb_dataAppendInt(struct CmdStruct *Command, VMC_UINT_16 param);
void cmdb_dataAppendLong(struct CmdStruct *Command, TMC_ULONG_32 param);


#endif /* _AIS_CMDBUFF_H_ */

//@}
