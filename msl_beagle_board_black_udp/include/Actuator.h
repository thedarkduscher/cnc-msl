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
#include "ShovelSelect.h"
#include "Switches.h"

#include "msl_actuator_msgs/BallHandleCmd.h"
#include "msl_actuator_msgs/BallHandleMode.h"
#include "msl_actuator_msgs/ShovelSelectCmd.h"
#include "msl_actuator_msgs/MotionLight.h"
#include "msl_actuator_msgs/RawOdometryInfo.h"


class Actuator {
public:
	Actuator();
	~Actuator();
	static void exitThreads(int sig);
	void run();

	static std::condition_variable cv;
	static bool killThreads;

private:
	void handleBallHandleControl(const msl_actuator_msgs::BallHandleCmd msg);
	void handleBallHandleMode(const msl_actuator_msgs::BallHandleMode msg);
	void handleShovelSelectControl(const msl_actuator_msgs::ShovelSelectCmd msg);
	void handleMotionLight(const msl_actuator_msgs::MotionLight msg);
	void handleRawOdometryInfo(const msl_actuator_msgs::RawOdometryInfo msg);
	void handleCanSub(const msl_actuator_msgs::CanMsg &msg);

	BlackLib::BlackI2C *myI2C;
	BlackLib::BlackSPI *mySpi;

	BallHandle *ballHandle;
	IMU *imu;
	LightBarrier *lightbarrier;
	OpticalFlow *opticalflow;
	ShovelSelect *shovel;
	Switches *switches;

	CanHandler canHandler;
};

#endif /* CNC_MSL_MSL_BEAGLE_BOARD_BLACK_INCLUDE_ACTUATOR_H_ */
