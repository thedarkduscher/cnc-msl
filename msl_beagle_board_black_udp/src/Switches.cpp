#include "Switches.h"

#include <SystemConfig.h>

#include "process_manager/ProcessCommand.h"
#include "msl_actuator_msgs/VisionRelocTrigger.h"
#include "std_msgs/Empty.h"

Switches::Switches() {
	/* sw_vis, sw_bun, sw_pwr, led_pwr, led_bun, led_vis */
	const char *pin_names[] = { "P9_11", "P9_13", "P9_15", "P9_23", "P9_41", "P9_42" };
	gpio = BeagleGPIO::getInstance();
	pins = gpio->claim((char**) pin_names, 6);

	int outputIdxs[] = { led_power, led_bundle, led_vision };
	pins->enableOutput(outputIdxs, 3);

	killThread = false;
	notifyThread = false;

	proxy = Proxy::getInstance();
	sThread = new std::thread(&Switches::controlSwitches, this);
}

Switches::~Switches() {
	killThread = true;
	cv.notify_all();

	delete sThread;
	delete gpio;
}

void Switches::controlSwitches() {
	supplementary::SystemConfig* sc;
	sc = supplementary::SystemConfig::getInstance();
	int		ownID = (*sc)["bbb"]->get<int>("BBB.robotID",NULL);
	msl_actuator_msgs::VisionRelocTrigger msg_v;
	process_manager::ProcessCommand msg_pm;

	std::unique_lock<std::mutex> switchesMutex(mtx);
	while(!killThread) {
		cv.wait(switchesMutex, [&] { return !killThread || notifyThread; }); // protection against spurious wake-ups
		if (!killThread)
			break;

		static bool		state[3] = {false, false, false};
		bool newstate[3];
		int	sw[3] = {1, 1, 1};

		try {
			// TODO überprüfen, ob Auslesen mit der API funktioniert
			sw[sw_vision] = pins->getBit(sw_vision);
			sw[sw_bundle] = pins->getBit(sw_bundle);
			sw[sw_power] = pins->getBit(sw_power);
		} catch (std::exception &e) {
			std::cout << "Buttons: " << e.what() << std::endl;
		}

		for (int i = 0; i <= 2; i++) {
			if(sw[i] == 1)
				newstate[i] = false;
			else if (sw[i] == 0)
				newstate[i] = true;
			else
				std::cout << "Button " << i << " failure" << std::endl;
		}

		if (newstate[sw_bundle] != state[sw_bundle]) {
			state[sw_bundle] = newstate[sw_bundle];

			if (state[sw_bundle]) {
				static uint8_t bundle_state = 0;

				msg_pm.receiverId = ownID;
				msg_pm.robotIds = {ownID};
				msg_pm.processKeys = {2,3,4,5,7};
				msg_pm.paramSets = {1,0,0,0,3};

				if (bundle_state == 0) {		// Prozesse starten
					bundle_state = 1;
					msg_pm.cmd = 0;
					pins->setBit(led_bundle);	// LED an
				} else if (bundle_state == 1) {	// Prozesse stoppen
					bundle_state = 0;
					msg_pm.cmd = 1;
					pins->clearBit(led_bundle);	// LED aus
				}
				proxy->onRosProcessCommand554624761(msg_pm);
				//brtPub->publish(msg_pm);
			}
		}

		if (newstate[sw_vision] != state[sw_vision]) {
			state[sw_vision] = newstate[sw_vision];

			if (state[sw_vision]) {
				msg_v.receiverID = ownID;
				msg_v.usePose = false;
				proxy->onRosVisionRelocTrigger2772566283(msg_v);
				pins->setBit(led_vision);	// Vision-LED an
			} else {
				pins->clearBit(led_vision);	// Vision-LED aus
			}
		}

		if (newstate[sw_power] != state[sw_power]) {
			state[sw_power] = newstate[sw_power];

			if (state[sw_power]) {
				std_msgs::Empty msg;
				pins->setBit(led_power);	// Power-LED an
			} else {
				pins->clearBit(led_power);	// Power-LED aus
			}
		}

		notifyThread = false;
	}
}

void Switches::notify() {
	notifyThread = true;
	cv.notify_all();
}
