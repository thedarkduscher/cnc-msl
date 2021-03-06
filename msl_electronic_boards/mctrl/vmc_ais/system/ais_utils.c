//////////////////////////////////////////////////////////////////////////////
/// \defgroup utils Different Functions to ease use of AISC167Board
//@{
/// \file ais_utils.c
///
/// \brief 	Different Functions to ease use of AISC167Board
///
/// \author Jan Paulus and Adam Cwientzek
///
/// \version 0.8
///
/// \date 31.06.2005
///
//////////////////////////////////////////////////////////////////////////////


#include <intrins.h>
#include "system/ais_utils.h"
#include "aisc167b/ais_gpt.h"
#include "aisc167b/ais_pwm.h"


//////////////////////////////////////////////////////////////////////////////
/// \brief Initialize AISC167Board
///
//////////////////////////////////////////////////////////////////////////////
void init_aisc167b() {
   DIR_LED_GREEN = 1; // I/O for green LED is Output
   DIR_LED_RED   = 1; // I/O for red LED is Output

   DIR_SW_1 	 = 0; // I/O for Switch 1 is Input
   DIR_SW_2		 = 0; // I/O for Switch 2 is Input
}
//////////////////////////////////////////////////////////////////////////////






//////////////////////////////////////////////////////////////////////////////
/// \brief Switch on/off green LED
///
//////////////////////////////////////////////////////////////////////////////
void led_set_green(VMC_UCHAR_8 status) {
   LED_GREEN = status;
}
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
/// \brief Switch on/off red LED
///
//////////////////////////////////////////////////////////////////////////////
void led_set_red(VMC_UCHAR_8 status) {
   LED_RED = status;
}
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
/// \brief Swap Status of green LED
///
//////////////////////////////////////////////////////////////////////////////
void led_swap_green() {
   LED_GREEN = !LED_GREEN;
}
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
/// \brief Swap Status of red LED
///
//////////////////////////////////////////////////////////////////////////////
void led_swap_red() {
   LED_RED = !LED_RED;
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
/// \brief this funcion controlls the two LEDs
//////////////////////////////////////////////////////////////////////////////
void led_control() {
 led_swap_red();
}
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
/// \brief Return State of Jumper Switch 1
//////////////////////////////////////////////////////////////////////////////
VMC_CHAR_8 get_state_sw1() {
 return !SW_1;
}
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
/// \brief Return State of Jumper Switch 1
//////////////////////////////////////////////////////////////////////////////
VMC_CHAR_8 get_state_sw2() {
 return !SW_2;
}
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
/// \brief Expands every cycle to a disired cycle time
/// \param desired_cycletime the cycle time that is needed in [ms]
/// \note by desired_cycletime=0 the cycle time is asynchron and as long as
///       the code takes
/// \note also if the desired_cycletime is smaller than the natural cycle time
//////////////////////////////////////////////////////////////////////////////
void sync_cycletime(VMC_UINT_16 desired_cycletime){
	if(desired_cycletime == 0)
		return;
	while( (((long)desired_cycletime*1000)-50) > get_cycle_time_part() ) ;
}


//@}


