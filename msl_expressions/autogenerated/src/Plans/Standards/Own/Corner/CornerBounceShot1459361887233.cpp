#include "Plans/Standards/Own/Corner/CornerBounceShot1459361887233.h"
using namespace alica;
/*PROTECTED REGION ID(eph1459361887233) ENABLED START*/ //Add additional using directives here
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:CornerBounceShot

    /* generated comment
     
     Task: DefaultTask  -> EntryPoint-ID: 1459361887235

     */
    shared_ptr<UtilityFunction> UtilityFunction1459361887233::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1459361887233) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

    //State: CornerPos in Plan: CornerBounceShot

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : CornerPos2DoCorner 
     *
     * Plans in State: 				
     *   - Plan - (Name): CornerPosBounceShot, (PlanID): 1459361999064 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1459361887235)
     *
     * States:
     *   - CornerPos (1459361887234)
     *   - DoCorner (1459361895479)
     *   - NewSuccessState (1459361899313)
     *   - NewFailureState (1459361900873)
     *
     * Vars:
     */
    bool TransitionCondition1459361912141::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1459361911154) ENABLED START*/
        return wm->game.checkSituation(msl::Situation::Start);
        /*PROTECTED REGION END*/

    }

    //State: DoCorner in Plan: CornerBounceShot

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : DoCorner2Succ 
     *
     * Plans in State: 				
     *   - Plan - (Name): CornerExecBounceShot, (PlanID): 1459362028865 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1459361887235)
     *
     * States:
     *   - CornerPos (1459361887234)
     *   - DoCorner (1459361895479)
     *   - NewSuccessState (1459361899313)
     *   - NewFailureState (1459361900873)
     *
     * Vars:
     */
    bool TransitionCondition1459361914252::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1459361912344) ENABLED START*/
        return rp->anyChildrenStatus(PlanStatus::Success);
        /*PROTECTED REGION END*/

    }

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : DoCorner2Fail 
     *
     * Plans in State: 				
     *   - Plan - (Name): CornerExecBounceShot, (PlanID): 1459362028865 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1459361887235)
     *
     * States:
     *   - CornerPos (1459361887234)
     *   - DoCorner (1459361895479)
     *   - NewSuccessState (1459361899313)
     *   - NewFailureState (1459361900873)
     *
     * Vars:
     */
    bool TransitionCondition1459361916700::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1459361914595) ENABLED START*/
        return isTimeOut(10000000000, rp->getStateStartTime(), rp);
        /*PROTECTED REGION END*/

    }

//State: NewSuccessState in Plan: CornerBounceShot

//State: NewFailureState in Plan: CornerBounceShot

}