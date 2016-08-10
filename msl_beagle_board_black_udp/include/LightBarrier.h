/*
 * lightbarrier.h
 *
 *  Created on: Mar 7, 2016
 *      Author: Lukas Will
 */

#ifndef INCLUDE_LIGHTBARRIER_H_
#define INCLUDE_LIGHTBARRIER_H_

#include "BlackDef.h"
#include "BlackADC.h"

#include "Proxy.h"
#include <thread>
#include <mutex>
#include <condition_variable>


class LightBarrier {
public:
	LightBarrier(BlackLib::adcName adc_P);
	~LightBarrier();

	bool checkLightBarrier();
	void controlLightBarrier();
	void notify();
	bool setTreshold(int th);

private:
	std::thread* lbThread;
	std::condition_variable cv;
	std::mutex mtx;
	bool killThread;
	bool notifyThread;

	Proxy* proxy;

	BlackLib::BlackADC* adc;
	int		threshold;
};



#endif /* INCLUDE_LIGHTBARRIER_H_ */
