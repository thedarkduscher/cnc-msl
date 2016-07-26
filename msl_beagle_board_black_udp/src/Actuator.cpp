/*
 * actuator.cpp
 *
 *  Created on: Mar 10, 2015
 *      Author: Lukas Will
 */


#include "actuator.h"

#include <SystemConfig.h>
#include <Configuration.h>
#include <exception>

#include <usbcanconnection.h>
#include "../include/CanHandler.h"

using namespace std;
using namespace BlackLib;

void handleBallHandleControl(const msl_actuator_msgs::BallHandleCmd msg) {
	const msl_actuator_msgs::BallHandleMode mode;

	ballHandle.ping();
	if (ballHandle.getMode() == mode.REMOTE_CONTROL) {
		ballHandle.setBallHandling(msg.leftMotor, msg.rightMotor);
	}
}

void handleBallHandleMode(const msl_actuator_msgs::BallHandleMode msg) {
	ballHandle.ping();
	ballHandle.setMode(msg.mode);
}

void handleShovelSelectControl(const msl_actuator_msgs::ShovelSelectCmd msg) {
	try {
		shovel.setShovel(msg.passing, time_now);
	} catch (exception &e) {
		cout << "ShovelSelect: " << e.what() << endl;
	}
}

void handleMotionLight(const msl_actuator_msgs::MotionLight msg) {
	// LED vom Maussensor ansteuern
	try {
		adns3080.controlLED(msg.enable);
	} catch (exception &e) {
		cout << "MotionLight: " << e.what() << endl;
	}
}

void handleRawOdometryInfo(const msl_actuator_msgs::RawOdometryInfo msg) {
	ballHandle.setOdometryData(msg.motion.angle, msg.motion.translation);
}

void handleCanSub(const msl_actuator_msgs::CanMsg &msg) {
	// Nachricht an ueber can verschicken
	canHandler.sendCanMsg(msg);
}

void exit_program(int sig) {
	ex = true;
	th_activ = false;
	for (int i=0; i<7; i++)
		threw[i].cv.notify_all();
}




int main(int argc, char** argv) {
	ros::Time::init();
	ros::Rate loop_rate(30);		// in Hz



	thread th_controlBallHandle(controlBallHandle);
	thread th_controlShovel(contolShovelSelect);
	thread th_lightbarrier(getLightbarrier);
	thread th_switches(getSwitches);
	thread th_imu(getIMU);

	// I2C
	bool i2c = myI2C.open(ReadWrite);
	bool spi = mySpi.open(ReadWrite);
	bool imu = lsm9ds0.init();



	usleep(50000);

	// CAN hack
	canHandler.Start();



	(void) signal(SIGINT, exit_program);
	while(!ex) {
		gettimeofday(&time_now, NULL);

		// Thread Notify
		for (int i=0; i<6; i++) { // TODO remove magic number
			if (threw[i].notify) {
				cerr << "Thread " << i << " requires to much time, iteration is skipped" << endl;
			} else {
				threw[i].notify = true;
			}
			threw[i].cv.notify_all();
		}

		loop_rate.sleep();
	}
    io_service.stop();
    iothread.join();
    canHandler.Stop();

	return 0;
}
