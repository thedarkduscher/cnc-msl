#ifndef _AIS_BIOPORT3_H_
#define _AIS_BIOPORT3_H_

#include <reg167.h>

#include "ais_typedef.h"


sbit dp_DIO1IN  = DP3^8;       /**< Direction register 3.8 for P3IN*/
sbit dp_DIO2IN  = DP3^9;       /**< Direction register 3.9 for P3IN*/
sbit dp_DIO3IN  = DP3^13;       /**< Direction register 3.13 for P3IN*/

sbit DIO1IN  = P3^8;       /**< register 3.8 for P3IN*/
sbit DIO2IN  = P3^9;       /**< register 3.9 for P3IN*/
sbit DIO3IN  = P3^13;      /**< register 3.13 for P3IN*/


sbit odp_DIO1IN  = ODP3^8;       /**<Open Drain control register 3.8 for P3IN*/
sbit odp_DIO2IN  = ODP3^9;       /**<Open Drain control register 3.9 for P3IN*/
sbit odp_DIO3IN  = ODP3^13;      /**<Open Drain control register 3.13 for P3IN*/

sbit AIO1IN  = P5^4;       /**< register 5.4 for P5IN*/
sbit AIO2IN  = P5^2;       /**< register 5.2 for P5IN*/

// status flag
extern VMC_UCHAR_8 mode_flag;           // 0 channel M3 is reserved for two bumpers
                                        // 1 free use of M3

enum states {BUMPERFREE, BUMPERTILT};

void can_debug(unsigned char mark, char index);
void init_bioport(void);
VMC_UCHAR_8 configurate_ioport(VMC_UINT_16 pins);
VMC_UINT_16 get_configurate_ioport();
VMC_UCHAR_8 set_dioport(VMC_UINT_16 pins);
VMC_UINT_16 get_dioport();
VMC_UINT_16 get_a1_ioport();
VMC_UINT_16 get_a2_ioport();

VMC_UINT_16 get_bumper_port();
#endif /* _AIS_IOPORT3_H_ */

//@}
