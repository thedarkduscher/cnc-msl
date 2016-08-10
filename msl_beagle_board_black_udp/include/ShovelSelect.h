/*
 * shovelselect.h
 *
 *  Created on: Mar 7, 2016
 *      Author: Lukas Will
 */

#ifndef INCLUDE_SHOVELSELECT_H_
#define INCLUDE_SHOVELSELECT_H_
#define TIMEDIFFMS(n,o) (((n).tv_sec-(o).tv_sec)*1000+((n).tv_usec-(o).tv_usec)/1000)

#include <thread>
#include <mutex>
#include <condition_variable>

#include <BeaglePWM.h>

#include "BlackDef.h"
#include "BlackPWM.h"

class ShovelSelect
{
public:
	ShovelSelect(BlackLib::pwmName pwm_P);	// Delete if using API
// API Stuff	ShovelSelect(BeaglePWM::PwmPin pwm_name);
	~ShovelSelect();

	bool checkTimeout();
	bool setShovel(bool passing);
	void controlShovelSelect();
	void notify();

private:
	std::thread* ssThread;
	std::condition_variable cv;
	std::mutex mtx;
	bool killThread;
	bool notifyThread;

/* API
	BeaglePWM *pwm;
	BeaglePWM::PwmPin pwm_pin; */
	BlackLib::BlackPWM* pwm;	// Delete if using API

	bool enabled;
	bool init;
	bool statePassing;
	const int period = 20000000;
	int kickPWM = 1600;
	int passPWM = 1300;
	int timeout;
	timeval ping;
};

#endif /* INCLUDE_SHOVELSELECT_H_ */
