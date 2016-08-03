/*
 * lightbarrier.cpp
 *
 *  Created on: Mar 7, 2016
 *      Author: Lukas Will
 */


#include "LightBarrier.h"
#include "Proxy.h"
#include <SystemConfig.h>

using namespace BlackLib;

LightBarrier::LightBarrier(adcName adc_P, bool *killT, std::condition_variable *cv) {
	adc = new BlackADC(adc_P);

	auto sc = supplementary::SystemConfig::getInstance();
	this->threshold = (*sc)["bbb"]->get<int>("BBB.lightbarrierThreshold", NULL);

	killThread = killT;
	notifyThread = false;
	this->cv = cv;
	lbThread = new std::thread(&LightBarrier::controlLightBarrier, this);
}

LightBarrier::~LightBarrier() {
	delete lbThread;
	delete adc;
}

bool LightBarrier::checkLightBarrier() {
	if (adc->getNumericValue() > threshold) {
		return true;
	} else {
		return false;
	}
}

void LightBarrier::controlLightBarrier() {
	Proxy *proxy = Proxy::getInstance();
	std_msgs::Bool msg;
	unique_lock<mutex> lightBarrierMutex(mtx);
	while(!killThread) {
		cv->wait(lightBarrierMutex, [&] { return !killThread || notifyThread; }); // protection against spurious wake-ups
		if (!killThread)
			break;

		try {
			msg.data = checkLightBarrier();
			proxy->onRosBool2802967882(msg);
		} catch (exception &e) {
			cout << "ADC: " << e.what() << endl;
		}

		notifyThread = false;
	}
}

bool LightBarrier::setTreshold(int th) {
	if ((th > 0) && (th < 1024)) {
		threshold = th;
		return true;
	} else {
		return false;
	}
}
