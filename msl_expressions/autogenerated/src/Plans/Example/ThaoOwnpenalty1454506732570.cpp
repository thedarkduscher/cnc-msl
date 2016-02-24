#include "Plans/Example/ThaoOwnpenalty1454506732570.h"
using namespace alica;
/*PROTECTED REGION ID(eph1454506732570) ENABLED START*/ //Add additional using directives here
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:ThaoOwnpenalty

    /* generated comment
     
     Task: DefaultTask  -> EntryPoint-ID: 1454506732572

     */
    shared_ptr<UtilityFunction> UtilityFunction1454506732570::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1454506732570) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

    //State: DriveToMiddle in Plan: ThaoOwnpenalty

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment :  
     *
     * Plans in State: 				
     *   - Plan - (Name): StopDefault, (PlanID): 1413992626194 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1454506732572)
     *
     * States:
     *   - DriveToMiddle (1454506732571)
     *   - WaitForStart (1454507325367)
     *   - GrabBall (1454507326785)
     *   - AlignAndShoot (1454507336161)
     *
     * Vars:
     */
    bool TransitionCondition1454507416455::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1454507415324) ENABLED START*/
        return wm->game.checkSituation(msl::Situation::Start);

        /*PROTECTED REGION END*/

    }

    //State: WaitForStart in Plan: ThaoOwnpenalty

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment :  
     *
     * Plans in State: 				
     *   - Plan - (Name): DriveToMiddle, (PlanID): 1431527260342 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1454506732572)
     *
     * States:
     *   - DriveToMiddle (1454506732571)
     *   - WaitForStart (1454507325367)
     *   - GrabBall (1454507326785)
     *   - AlignAndShoot (1454507336161)
     *
     * Vars:
     */
    bool TransitionCondition1454507418308::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1454507416623) ENABLED START*/

        return rp->anyChildrenStatus(PlanStatus::Success);
        /*PROTECTED REGION END*/

    }

    //State: GrabBall in Plan: ThaoOwnpenalty

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment :  
     *
     * Plans in State: 				
     *   - Plan - (Name): InterceptCarefullyDefault, (PlanID): 1427703234654 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1454506732572)
     *
     * States:
     *   - DriveToMiddle (1454506732571)
     *   - WaitForStart (1454507325367)
     *   - GrabBall (1454507326785)
     *   - AlignAndShoot (1454507336161)
     *
     * Vars:
     */
    bool TransitionCondition1454507419613::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1454507418557) ENABLED START*/
        return wm->ball.haveBall();
        /*PROTECTED REGION END*/

    }

    //State: AlignAndShoot in Plan: ThaoOwnpenalty

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment :  
     *
     * Plans in State: 				
     *   - Plan - (Name): PenaltyAlignAndShootDefault, (PlanID): 1431531542052 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1454506732572)
     *
     * States:
     *   - DriveToMiddle (1454506732571)
     *   - WaitForStart (1454507325367)
     *   - GrabBall (1454507326785)
     *   - AlignAndShoot (1454507336161)
     *
     * Vars:
     */
    bool TransitionCondition1454507421144::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1454507420022) ENABLED START*/
        return !wm->ball.haveBall();
        /*PROTECTED REGION END*/

    }

}
