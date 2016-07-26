/*
 * actuator.cpp
 *
 *  Created on: Mar 10, 2015
 *      Author: Lukas Will
 */


#include "Actuator.h"

#include <usbcanconnection.h>


Actuator::Actuator() {
	ballHandle = new BallHandle(&killThreads, &cv);
	imu = new IMU(&myI2C, &killThreads, &cv);
	lightbarrier = new LightBarrier(BlackLib::AIN0, &killThreads, &cv);
	opticalflow = new OpticalFlow(&mySpi, &killThreads, &cv);
	shovel = new ShovelSelect(BlackLib::P9_14, &killThreads, &cv);	// Delete if using API
		//ShovelSelect	shovel(BeaglePWM::P9_14);
	switches = new Switches(&killThreads, &cv);

	myI2C.open(BlackLib::ReadWrite);
	mySpi.open(BlackLib::ReadWrite);
	imu->init();

	canHandler.Start();
}

Actuator::~Actuator() {
	delete ballHandle;
	delete imu;
	delete lightbarrier;
	delete opticalflow;
	delete shovel;
	delete switches;
}

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

void Actuator::exitThreads(int sig) {
	killThreads = true;
	cv.notify_all();
}

int main(int argc, char** argv) {
	ros::Time::init();
	ros::Rate loop_rate(100);

	// Initialization
	Actuator actuator;


	int counter = 0;
	(void) signal(SIGINT, actuator.exitThreads);
	while(1) {
		counter++;

		if (counter % 1 == 0) {
			// 100Hz
			actuator.ballHandle->notifyThread = true;
		}

		if (counter % 2 == 0) {
			// 50Hz
			actuator.lightbarrier->notifyThread = true;
		}

		if (counter % 3 == 0) {
			// 33Hz
			actuator.opticalflow->notifyThread = true;
			actuator.imu->notifyThread = true;
		}

		if (counter % 4 == 0) {
			// 25Hz
			actuator.shovel->notifyThread = true;
			actuator.switches->notifyThread = true;
		}

		actuator.cv.notify_all(); // Notify all Threads

		loop_rate.sleep();
	}

    actuator.proxy.io_service.stop();
    actuator.proxy.iothread.join();
    actuator.canHandler.Stop();

	return 0;
}
