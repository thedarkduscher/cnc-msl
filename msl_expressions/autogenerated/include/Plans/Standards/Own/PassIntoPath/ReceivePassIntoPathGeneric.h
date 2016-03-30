#ifndef ReceivePassIntoPathGeneric_H_
#define ReceivePassIntoPathGeneric_H_

#include "DomainBehaviour.h"
/*PROTECTED REGION ID(inc1457531583460) ENABLED START*/ //Add additional includes here
#include "engine/constraintmodul/ConstraintQuery.h"
/*PROTECTED REGION END*/
namespace alica
{
    class ReceivePassIntoPathGeneric : public DomainBehaviour
    {
    public:
        ReceivePassIntoPathGeneric();
        virtual ~ReceivePassIntoPathGeneric();
        virtual void run(void* msg);
        /*PROTECTED REGION ID(pub1457531583460) ENABLED START*/ //Add additional public methods here
        /*PROTECTED REGION END*/
    protected:
        virtual void initialiseParameters();
        /*PROTECTED REGION ID(pro1457531583460) ENABLED START*/ //Add additional protected methods here
        /*PROTECTED REGION END*/
    private:
        /*PROTECTED REGION ID(prv1457531583460) ENABLED START*/ //Add additional private methods here
        shared_ptr<ConstraintQuery> query;
        vector<double> result;
        double sign;
        double maxVel;
        /*PROTECTED REGION END*/};
} /* namespace alica */

#endif /* ReceivePassIntoPathGeneric_H_ */
