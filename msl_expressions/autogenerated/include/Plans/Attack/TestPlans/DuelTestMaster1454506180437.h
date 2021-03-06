#ifndef DuelTestMaster_H_
#define DuelTestMaster_H_

#include "DomainCondition.h"
#include "engine/BasicUtilityFunction.h"
#include "engine/UtilityFunction.h"
#include "engine/DefaultUtilityFunction.h"
/*PROTECTED REGION ID(incl1454506180437) ENABLED START*/
//Add inlcudes here
/*PROTECTED REGION END*/
using namespace alica;

namespace alicaAutogenerated
{
    /*PROTECTED REGION ID(meth1454506180437) ENABLED START*/
    //Add other things here
    /*PROTECTED REGION END*/
    class UtilityFunction1454506180437 : public BasicUtilityFunction
    {
        shared_ptr<UtilityFunction> getUtilityFunction(Plan* plan);
    };

    class TransitionCondition1454506224420 : public DomainCondition
    {
        bool evaluate(shared_ptr<RunningPlan> rp);
    };

    class TransitionCondition1458125293553 : public DomainCondition
    {
        bool evaluate(shared_ptr<RunningPlan> rp);
    };

    class TransitionCondition1458135843050 : public DomainCondition
    {
        bool evaluate(shared_ptr<RunningPlan> rp);
    };

    class TransitionCondition1458125320118 : public DomainCondition
    {
        bool evaluate(shared_ptr<RunningPlan> rp);
    };

} /* namespace alica */

#endif
