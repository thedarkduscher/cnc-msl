#include "Plans/Attack/RunFree1434115664325.h"
using namespace alica;
/*PROTECTED REGION ID(eph1434115664325) ENABLED START*/ //Add additional using directives here
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:RunFree

    /* generated comment
     
     Task: OffensiveMidfield  -> EntryPoint-ID: 1434115664327

     */
    shared_ptr<UtilityFunction> UtilityFunction1434115664325::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1434115664325) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

    //State: Release in Plan: RunFree

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : is target for pass 
     *
     * Plans in State: 
     *
     * Tasks: 
     *   - OffensiveMidfield (1434112683820) (Entrypoint: 1434115664327)
     *
     * States:
     *   - Release (1434115664326)
     *   - CatchPass (1434115849689)
     *   - InterceptPass (1434115852118)
     *
     * Vars:
     */
    bool TransitionCondition1434115869504::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1434115867679) ENABLED START*/
        return false;
        /*PROTECTED REGION END*/

    }

    //State: CatchPass in Plan: RunFree

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : empty pass msg  
     *
     * Plans in State: 
     *
     * Tasks: 
     *   - OffensiveMidfield (1434112683820) (Entrypoint: 1434115664327)
     *
     * States:
     *   - Release (1434115664326)
     *   - CatchPass (1434115849689)
     *   - InterceptPass (1434115852118)
     *
     * Vars:
     */
    bool TransitionCondition1434115870439::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1434115869697) ENABLED START*/
        return false;
        /*PROTECTED REGION END*/

    }

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : ball conf high enough 
     *
     * Plans in State: 
     *
     * Tasks: 
     *   - OffensiveMidfield (1434112683820) (Entrypoint: 1434115664327)
     *
     * States:
     *   - Release (1434115664326)
     *   - CatchPass (1434115849689)
     *   - InterceptPass (1434115852118)
     *
     * Vars:
     */
    bool TransitionCondition1434115871872::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1434115870604) ENABLED START*/
        return false;
        /*PROTECTED REGION END*/

    }

    //State: InterceptPass in Plan: RunFree

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : pass msg empty 
     *
     * Plans in State: 
     *
     * Tasks: 
     *   - OffensiveMidfield (1434112683820) (Entrypoint: 1434115664327)
     *
     * States:
     *   - Release (1434115664326)
     *   - CatchPass (1434115849689)
     *   - InterceptPass (1434115852118)
     *
     * Vars:
     */
    bool TransitionCondition1434115873056::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1434115872185) ENABLED START*/
        return false;
        /*PROTECTED REGION END*/

    }

}
