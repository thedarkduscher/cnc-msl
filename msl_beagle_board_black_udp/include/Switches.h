/*
 * Switches.cpp
 *
 *  Created on: Jul 26, 2016
 *      Author: cn
 */

#ifndef CNC_MSL_MSL_BEAGLE_BOARD_BLACK_UDP_INCLUDE_SWITCHES_CPP_
#define CNC_MSL_MSL_BEAGLE_BOARD_BLACK_UDP_INCLUDE_SWITCHES_CPP_

#include "Proxy.h"
#include <thread>
#include <mutex>
#include <condition_variable>

#include <BeagleGPIO.h>
#include <BeaglePins.h>
#include <BeaglePWM.h>


class Switches
{
public:
	Switches();
	~Switches();
	void controlSwitches();
	void notify();

private:
	std::thread* sThread;
	std::condition_variable cv;
	std::mutex mtx;
	bool killThread;
	bool notifyThread;

	Proxy* proxy;

	BeagleGPIO *gpio;
	BeaglePins *pins;

	enum Pin {
		sw_vision,
		sw_bundle,
		sw_power,
		led_power,
		led_bundle,
		led_vision
	};
};


#endif /* CNC_MSL_MSL_BEAGLE_BOARD_BLACK_UDP_INCLUDE_SWITCHES_CPP_ */
