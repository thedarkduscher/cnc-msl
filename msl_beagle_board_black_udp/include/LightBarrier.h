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

#include <thread>
#include <mutex>
#include <condition_variable>


class LightBarrier {
public:
	LightBarrier(BlackLib::adcName adc_P, bool *killT, std::condition_variable *cv);
	~LightBarrier();

	bool checkLightBarrier();
	void controlLightBarrier();
	bool setTreshold(int th);

	bool notifyThread;

private:
	std::condition_variable *cv;
	std::mutex mtx;
	bool *killThread;

	BlackLib::BlackADC	*adc;
	int		threshold;
};



#endif /* INCLUDE_LIGHTBARRIER_H_ */
