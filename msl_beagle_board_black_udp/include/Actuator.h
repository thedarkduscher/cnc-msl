/*
 * actuator.h
 *
 *  Created on: Apr 7, 2015
 *      Author: Lukas Will
 */

#ifndef CNC_MSL_MSL_BEAGLE_BOARD_BLACK_INCLUDE_ACTUATOR_H_
#define CNC_MSL_MSL_BEAGLE_BOARD_BLACK_INCLUDE_ACTUATOR_H_

#include <ros/ros.h>
#include <condition_variable>

#include "BlackDef.h"
#include "BlackI2C.h"
#include "BlackSPI.h"

#include "BallHandle.h"
#include "CanHandler.h"
#include "IMU.h"
#include "LightBarrier.h"
#include "OpticalFlow.h"
#include "Proxy.h"
#include "ShovelSelect.h"
#include "Switches.h"

class Actuator : Proxy {
public:
	Actuator();
	~Actuator();

	void exitThreads(int sig);

	CanHandler canHandler;

	std::condition_variable cv;
	bool killThreads = false;

private:
	BlackLib::BlackI2C myI2C(BlackLib::I2C_2, ADR_G);
	BlackLib::BlackSPI mySpi(BlackLib::SPI0_0, 8, BlackLib::SpiMode0, 2000000);

	BallHandle *ballHandle;
	IMU *imu;
	LightBarrier *lightbarrier;
	OpticalFlow *opticalflow;
	ShovelSelect *shovel;
	Switches *switches;
};

#endif /* CNC_MSL_MSL_BEAGLE_BOARD_BLACK_INCLUDE_ACTUATOR_H_ */
