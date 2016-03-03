#include "Plans/Example/test1449767310348.h"
using namespace alica;
/*PROTECTED REGION ID(eph1449767310348) ENABLED START*/ //Add additional using directives here
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:test

    /* generated comment
     
     Task: DefaultTask  -> EntryPoint-ID: 1449767310350

     */
    shared_ptr<UtilityFunction> UtilityFunction1449767310348::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1449767310348) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

    //State: Stop in Plan: test

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : start 
     *
     * Plans in State: 				
     *   - Plan - (Name): NewStoDefault, (PlanID): 1449767995479 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1449767310350)
     *
     * States:
     *   - Stop (1449767310349)
     *   - GrabTheBall (1454080477675)
     *
     * Vars:
     */
    bool TransitionCondition1450351989007::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1450351987255) ENABLED START*/
        return wm->game.checkSituation(msl::Situation::Start);
        /*PROTECTED REGION END*/

    }

    //State: GrabTheBall in Plan: test

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment :  
     *
     * Plans in State: 				
     *   - Plan - (Name): StdExecutorGrabBallDefault, (PlanID): 1441209089978 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1449767310350)
     *
     * States:
     *   - Stop (1449767310349)
     *   - GrabTheBall (1454080477675)
     *
     * Vars:
     */
    bool TransitionCondition1456847660301::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1456847658915) ENABLED START*/
        return rp->anyChildrenStatus(PlanStatus::Success);
        /*PROTECTED REGION END*/

    }

}
