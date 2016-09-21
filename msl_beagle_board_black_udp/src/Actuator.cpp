/*
 * actuator.cpp
 *
 *  Created on: Mar 10, 2015
 *      Author: Lukas Will
 */


#include "Actuator.h"



Actuator::Actuator() {
	ballHandle = new BallHandle();
	myI2C = new BlackLib::BlackI2C(BlackLib::I2C_2, ADR_G);
	imu = new IMU(myI2C);
	lightbarrier = new LightBarrier(BlackLib::AIN0);
	mySpi = new BlackLib::BlackSPI(BlackLib::SPI0_0, 8, BlackLib::SpiMode0, 2000000);
	opticalflow = new OpticalFlow(mySpi);
	shovel = new ShovelSelect(BlackLib::P9_14);	// Delete if using API
		//ShovelSelect	shovel(BeaglePWM::P9_14);
	switches = new Switches();

	myI2C->open(BlackLib::ReadWrite);
	mySpi->open(BlackLib::ReadWrite);
	imu->init();

	canHandler.Start();
}

Actuator::~Actuator() {
	canHandler.Stop();

	delete myI2C;
	delete mySpi;
	delete ballHandle;
	delete imu;
	delete lightbarrier;
	delete opticalflow;
	delete shovel;
	delete switches;
}

void Actuator::run() {
	ros::Time::init();
	ros::Rate loop_rate(100);

	int counter = 0;
	while(1) {
		counter++;

		if (counter % 1 == 0) {
			// 100Hz
//			ballHandle->notify();
		}

		if (counter % 2 == 0) {
			// 50Hz
			lightbarrier->notify();
		}

		if (counter % 3 == 0) {
			// 33Hz
			opticalflow->notify();
			imu->notify();

			// Data from Optical Flow Sensor and IMU into BallHandle !
			// opticalflow->sendMotionBurstMsg();
		//	imu->sendData();
		}

		if (counter % 4 == 0) {
			// 25Hz
			shovel->notify();
			switches->notify();
		}

		loop_rate.sleep();
	}
}

void Actuator::handleBallHandleControl(const msl_actuator_msgs::BallHandleCmd msg) {
	const msl_actuator_msgs::BallHandleMode mode;

	ballHandle->ping();
	if (ballHandle->getMode() == mode.REMOTE_CONTROL) {
		ballHandle->setBallHandling(msg.leftMotor, msg.rightMotor);
	}
}

void Actuator::handleBallHandleMode(const msl_actuator_msgs::BallHandleMode msg) {
	ballHandle->ping();
	ballHandle->setMode(msg.mode);
}

void Actuator::handleShovelSelectControl(const msl_actuator_msgs::ShovelSelectCmd msg) {
	try {
		shovel->setShovel(msg.passing);
	} catch (exception &e) {
		cout << "ShovelSelect: " << e.what() << endl;
	}
}

void Actuator::handleMotionLight(const msl_actuator_msgs::MotionLight msg) {
	// LED vom Maussensor ansteuern
	try {
		opticalflow->controlLED(msg.enable);
	} catch (exception &e) {
		cout << "MotionLight: " << e.what() << endl;
	}
}

void Actuator::handleRawOdometryInfo(const msl_actuator_msgs::RawOdometryInfo msg) {
	ballHandle->setOdometryData(msg.motion.angle, msg.motion.translation);
}

void Actuator::handleCanSub(const msl_actuator_msgs::CanMsg &msg) {
	// Nachrichten ueber can verschicken
	try {
		canHandler.sendCanMsg(msg);
	} catch (exception &e) {
		cout << "Can't send CAN-Msg: " << e.what() << endl;
	}
}
