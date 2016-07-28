#include "Actuator.h"
#include "Proxy.h"


int main(int argc, char** argv) {


	// Initialization
	Actuator actuator;
	Proxy* proxy = Proxy::getInstance();
	proxy->setActuator(&actuator);

	actuator.run();

	return 0;
}
