#ifndef PassIntoPathCONSTRAINT_H_
#define PassIntoPath_H_
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

    class Constraint1457531039142 : public BasicConstraint
    {
        void getConstraint(shared_ptr<ConstraintDescriptor> c, shared_ptr<RunningPlan>);
    };

} /* namespace alica */

#endif /* PassIntoPathCONSTRAINT_H_ */