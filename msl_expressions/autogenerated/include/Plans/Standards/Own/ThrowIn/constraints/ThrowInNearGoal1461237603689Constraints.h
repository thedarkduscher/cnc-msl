#ifndef ThrowInNearGoalCONSTRAINT_H_
#define ThrowInNearGoal_H_
#include "engine/BasicConstraint.h"
#include <memory>

using namespace std;
using namespace alica;

namespace alica
{
    class ConstraintDescriptor;
    class RunningPlan;
}

namespace alicaAutogenerated
{

    class Constraint1461574228077 : public BasicConstraint
    {
        void getConstraint(shared_ptr<ConstraintDescriptor> c, shared_ptr<RunningPlan>);
    };

} /* namespace alica */

#endif /* ThrowInNearGoalCONSTRAINT_H_ */
