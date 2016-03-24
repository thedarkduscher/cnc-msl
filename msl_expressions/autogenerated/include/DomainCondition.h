#ifndef DomainBehaviour_H_
#define DomainBehaviour_H_

#include "engine/BasicCondition.h"

namespace msl{
	class MSLWorldModel;
}

namespace supplementary {
	class SystemConfig;
}

namespace alica
{
	class DomainCondition : public BasicCondition
	{
	public:
		DomainCondition();
		virtual ~DomainCondition();

		msl::MSLWorldModel* wm;
		supplementary::SystemConfig* sc;

		/* The time that can pass since the last start command
		 * until we need to skip proper positioning and execute
		 * the standard right away. [ns]
		 */
		uint64_t timeUntilEmergencyExecute;
	};
} /* namespace alica */

#endif /* DomainBehaviour_H_ */

