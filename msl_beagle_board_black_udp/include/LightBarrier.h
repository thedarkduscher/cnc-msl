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


class LightBarrier {
public:
	LightBarrier(BlackLib::adcName adc_P, bool *kill, condition_variable *cv);
	~LightBarrier();

	bool checkLightBarrier();
	void controlLightBarrier();
	bool setTreshold(int th);

	bool notifyThread;

private:
	thread lightBarrierThread;
	std::condition_variable *cv;
	std::mutex mtx;
	bool *killThread;

	BlackLib::BlackADC	*adc;
	int		threshold;
};



#endif /* INCLUDE_LIGHTBARRIER_H_ */
