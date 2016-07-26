/*
 * actuator.h
 *
 *  Created on: Apr 7, 2015
 *      Author: Lukas Will
 */

#ifndef CNC_MSL_MSL_BEAGLE_BOARD_BLACK_INCLUDE_ACTUATOR_H_
#define CNC_MSL_MSL_BEAGLE_BOARD_BLACK_INCLUDE_ACTUATOR_H_

#include "includes.h"

#include "BallHandle.h"
#include "CanHandler.h"
#include "IMU.h"
#include "LightBarrier.h"
#include "OpticalFlow.h"
#include "Proxy.h"
#include "ShovelSelect.h"
#include "Switches.h"

using namespace BlackLib;

class Actuator {
public:
	Actuator();
	~Actuator();

private:
	BlackI2C myI2C(I2C_2, ADR_G);
	BlackSPI mySpi(SPI0_0, 8, SpiMode0, 2000000);


	LightBarrier	lightbarrier(AIN0);
	ShovelSelect	shovel(P9_14);	// Delete if using API
	//ShovelSelect	shovel(BeaglePWM::P9_14);

	timeval			time_now;
	timeval			last_ping;

	mutex		mtx;
	uint8_t		th_count;
	bool		th_activ = true;

	BallHandle ballHandle;
	IMU lsm9ds0(&myI2C);
	OpticalFlow adns3080(&mySpi);

	// Can hack
	CanHandler canHandler;
	Proxy proxy;

};









struct CV {
	std::mutex					mtx;
	std::condition_variable		cv;
	bool						notify = false;
};



CV				threw[7];

bool			ex = false;


#endif /* CNC_MSL_MSL_BEAGLE_BOARD_BLACK_INCLUDE_ACTUATOR_H_ */
