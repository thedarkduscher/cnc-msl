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
     *   - Movecenter (1450351941460)
     *   - GrabTheBall (1454080477675)
     *   - MoveToGoal (1456247693363)
     *
     * Vars:
     */
    bool TransitionCondition1450351989007::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1450351987255) ENABLED START*/
        return wm->game.checkSituation(msl::Situation::Start);
        /*PROTECTED REGION END*/

    }

    //State: Movecenter in Plan: test

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : start circle 
     *
     * Plans in State: 				
     *   - Plan - (Name): DriveToMiddle, (PlanID): 1431527260342 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1449767310350)
     *
     * States:
     *   - Stop (1449767310349)
     *   - Movecenter (1450351941460)
     *   - GrabTheBall (1454080477675)
     *   - MoveToGoal (1456247693363)
     *
     * Vars:
     */
    bool TransitionCondition1450351990459::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1450351989143) ENABLED START*/

        return rp->anyChildrenStatus(PlanStatus::Success);

        /*PROTECTED REGION END*/

    }

    //State: GrabTheBall in Plan: test

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment :  
     *
     * Plans in State: 				
     *   - Plan - (Name): GetBallDefault, (PlanID): 1414840399972 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1449767310350)
     *
     * States:
     *   - Stop (1449767310349)
     *   - Movecenter (1450351941460)
     *   - GrabTheBall (1454080477675)
     *   - MoveToGoal (1456247693363)
     *
     * Vars:
     */
    bool TransitionCondition1456247861415::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1456247858975) ENABLED START*/
        return rp->anyChildrenStatus(PlanStatus::Success);

        /*PROTECTED REGION END*/

    }

    //State: MoveToGoal in Plan: test

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment :  
     *
     * Plans in State: 				
     *   - Plan - (Name): DriveTo(-3500,0), (PlanID): 1443003717671 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1449767310350)
     *
     * States:
     *   - Stop (1449767310349)
     *   - Movecenter (1450351941460)
     *   - GrabTheBall (1454080477675)
     *   - MoveToGoal (1456247693363)
     *
     * Vars:
     */
    bool TransitionCondition1456247858719::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1456247857100) ENABLED START*/
        return rp->anyChildrenStatus(PlanStatus::Success);

        /*PROTECTED REGION END*/

    }

}
