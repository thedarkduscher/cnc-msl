/*
 * ballhandle.h
 *
 *  Created on: Mar 11, 2015
 *      Author: Lukas Will
 */

#ifndef CNC_MSL_MSL_BEAGLE_BOARD_BLACK_INCLUDE_BALLHANDLE_H_
#define CNC_MSL_MSL_BEAGLE_BOARD_BLACK_INCLUDE_BALLHANDLE_H_

#define TIMEDIFFMS(n,o) (((n).tv_sec-(o).tv_sec)*1000+((n).tv_usec-(o).tv_usec)/1000)


#include <thread>
#include <mutex>
#include <condition_variable>

#include "Motor.h"
#include "Spline.h"


class BallHandle
{
public:
	BallHandle(bool *killT, std::condition_variable *cv);
	~BallHandle();

	void readConfigParameters();
	void setOdometryData(double newAngle, double newTranslation);
	void setRotation(double newRotation);
	void dribbleControl();
	void setBallHandling(int32_t left, int32_t right);
	void ping();
	void checkTimeout();
	uint8_t getMode();
	void setMode(uint8_t newMode);
	void controlBallHandle();


	bool notifyThread;

private:
	std::condition_variable *cv;
	std::mutex mtx;
	bool *killThread;

	Motor *rightMotor;
	Motor *leftMotor;

	uint8_t mode = 1;

	double angle = 0.0;
	double translation = 0.0;
	double rotation = 0.0;

	const int minSpeed = 1800;
	const int maxSpeed = 10000;
	double speedX = 0;
	double speedY = 0;

	int timeout = 1000;
	double handlerSpeedSummand = 0;
	double handlerSpeedFactor = 0.0;
	double speedNoBall = 0.0;
	double slowTranslation = 0.0;
	double slowTranslationWheelSpeed = 0.0;
	double curveRotationFactor = 0.0;
	double orthoDriveFactor = 0;
	splines::spline forwardSpeedSpline;

	timeval last_ping;
};

#endif /* CNC_MSL_MSL_BEAGLE_BOARD_BLACK_INCLUDE_BALLHANDLE_H_ */
