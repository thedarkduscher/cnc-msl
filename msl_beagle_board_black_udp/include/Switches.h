/*
 * Switches.cpp
 *
 *  Created on: Jul 26, 2016
 *      Author: cn
 */

#ifndef CNC_MSL_MSL_BEAGLE_BOARD_BLACK_UDP_INCLUDE_SWITCHES_CPP_
#define CNC_MSL_MSL_BEAGLE_BOARD_BLACK_UDP_INCLUDE_SWITCHES_CPP_

#include <thread>
#include <mutex>
#include <condition_variable>


class Switches
{
public:
	Switches(bool *killT, std::condition_variable *cv);
	~Switches();
	void controlSwitches();

	bool notifyThread;

private:
	std::condition_variable *cv;
	std::mutex mtx;
	bool *killThread;

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
