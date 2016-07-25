/*
* shovelselect.cpp
*
*  Created on: Mar 7, 2016
*      Author: Lukas Will
*/

#include "shovelselect.h"
#include <sys/time.h>
#include <SystemConfig.h>

using namespace BlackLib;
/* API
ShovelSelect::ShovelSelect(BeaglePWM::PwmPin pwm_name) {
	pwm = BeaglePWM::getInstance();

	pwm_pin = pwm_name;
	pwm->setPeriod(pwm_pin, period);
	pwm->setRunState(pwm_pin, true);
	pwm->setDutyCycle(pwm_pin, 0);

	auto sc = supplementary::SystemConfig::getInstance();
	this->kickPWM = (*sc)["bbb"]->get<int>("BBB.shovelKick", NULL);
	this->passPWM = (*sc)["bbb"]->get<int>("BBB.shovelPass", NULL);
	this->timeout = (*sc)["bbb"]->get<int>("BBB.timeout", NULL);

	enabled = false;
	init = false;
}*/

	// Delete Constructor if using API
	ShovelSelect::ShovelSelect(pwmName pwm_P, bool kill, mutex mtx, condition_variable cv) {
			pwm = new BlackPWM(pwm_P);

			pwm->setPeriodTime(period, nanosecond);
			pwm->setSpaceRatioTime(0, microsecond);
			pwm->setRunState(stop);

			auto sc = supplementary::SystemConfig::getInstance();
			this->kickPWM = (*sc)["bbb"]->get<int>("BBB.shovelKick", NULL);
			this->passPWM = (*sc)["bbb"]->get<int>("BBB.shovelPass", NULL);
			this->timeout = (*sc)["bbb"]->get<int>("BBB.timeout", NULL);

			enabled = false;
			init = false;

			shovelSelectThread(controlShovelSelect);
			// CV, Mutex, Notify und Activ ???
			killThread = kill;
			notifyThread = false;
			this->mtx = mtx;
			this->cv = cv;
	}


ShovelSelect::~ShovelSelect() {
/* API
	pwm->setRunState(pwm_pin, false);*/
	delete pwm;
}

bool ShovelSelect::checkTimeout() {
	timeval	t;
	gettimeofday(&t, NULL);
	if ((TIMEDIFFMS(t, ping) > timeout) && enabled) {
	/* API
		pwm->setDutyCycle(pwm_pin, 0);*/
		pwm->setRunState(stop);	// Delete if using API
		enabled = false;
	}
}

bool ShovelSelect::setShovel(bool passing, timeval time_now) {
	if (statePassing == passing && init) {
		return false;
	}

	init = true;
	ping = time_now;
	statePassing = passing;
	if (passing) {
/* API		
		pwm->setDutyCycle(pwm_pin, passPWM * 1000);	// * 1000 because ns needed and passPWM is in us */
		pwm->setSpaceRatioTime(passPWM, microsecond);	// Delete if using API
	} else {
/* API
		pwm->setDutyCycle(pwm_pin, kickPWM * 1000);	// * 1000 because ns needed and kickPWM is in us */
		pwm->setSpaceRatioTime(kickPWM, microsecond);	// Delete if using API
	}
	if (!enabled) {
		pwm->setRunState(run);	// Delete if using API
		enabled = true;
	}

	return true;
}

void ShovelSelect::controlShovelSelect() {
	timeval	t;
	unique_lock<mutex> shovelSelectMutex(mtx);
	while(!killThread) {
		cv.wait(shovelSelectMutex, [&] { return !killThread || notifyThread; }); // protection against spurious wake-ups
		if (!killThread)
			break;

		try {
			checkTimeout();
		} catch (exception &e) {
			cout << "Shovel: " << e.what() << endl;
		}

		notifyThread = false;
	}
}

