#include "Plans/Attack/TestPlans/AttackOppGoalPlan1437902649389.h"
using namespace alica;
/*PROTECTED REGION ID(eph1437902649389) ENABLED START*/ //Add additional using directives here
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:AttackOppGoalPlan

    /* generated comment
     
     Task: DefaultTask  -> EntryPoint-ID: 1437902649391

     */
    shared_ptr<UtilityFunction> UtilityFunction1437902649389::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1437902649389) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

    //State: GetBall in Plan: AttackOppGoalPlan

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : haveBall 
     *
     * Plans in State: 				
     *   - Plan - (Name): GetBallDefault, (PlanID): 1414840399972 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1437902649391)
     *
     * States:
     *   - GetBall (1437902649390)
     *   - DribbleToOppPenaltySpot (1437902693350)
     *   - DribbleToOwnPenaltySpot (1437902704803)
     *   - NewSuccessState (1437902754765)
     *   - Shoot (1437902762624)
     *   - GetBall (1437903060557)
     *
     * Vars:
     */
    bool TransitionCondition1437903089358::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1437903088529) ENABLED START*/
        return wm->ball->haveBall();
        /*PROTECTED REGION END*/

    }

    //State: DribbleToOppPenaltySpot in Plan: AttackOppGoalPlan

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : lostBall 
     *
     * Plans in State: 				
     *   - Plan - (Name): DribbleToAttackPointDefault, (PlanID): 1436855860607 				
     *   - Plan - (Name): ShovelSelectLowKick, (PlanID): 1435156714286 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1437902649391)
     *
     * States:
     *   - GetBall (1437902649390)
     *   - DribbleToOppPenaltySpot (1437902693350)
     *   - DribbleToOwnPenaltySpot (1437902704803)
     *   - NewSuccessState (1437902754765)
     *   - Shoot (1437902762624)
     *   - GetBall (1437903060557)
     *
     * Vars:
     */
    bool TransitionCondition1437903093659::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1437903092957) ENABLED START*/
        return !wm->ball->haveBall();
        /*PROTECTED REGION END*/

    }

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : anyChildSuccess 
     *
     * Plans in State: 				
     *   - Plan - (Name): DribbleToAttackPointDefault, (PlanID): 1436855860607 				
     *   - Plan - (Name): ShovelSelectLowKick, (PlanID): 1435156714286 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1437902649391)
     *
     * States:
     *   - GetBall (1437902649390)
     *   - DribbleToOppPenaltySpot (1437902693350)
     *   - DribbleToOwnPenaltySpot (1437902704803)
     *   - NewSuccessState (1437902754765)
     *   - Shoot (1437902762624)
     *   - GetBall (1437903060557)
     *
     * Vars:
     */
    bool TransitionCondition1437903095031::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1437903093831) ENABLED START*/
        return rp->anyChildrenStatus(PlanStatus::Success);
        /*PROTECTED REGION END*/

    }

    //State: DribbleToOwnPenaltySpot in Plan: AttackOppGoalPlan

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : lostBall 
     *
     * Plans in State: 				
     *   - Plan - (Name): DribbleToAttackPointOwnPenaltySpot, (PlanID): 1437391438054 				
     *   - Plan - (Name): ShovelSelectLowKick, (PlanID): 1435156714286 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1437902649391)
     *
     * States:
     *   - GetBall (1437902649390)
     *   - DribbleToOppPenaltySpot (1437902693350)
     *   - DribbleToOwnPenaltySpot (1437902704803)
     *   - NewSuccessState (1437902754765)
     *   - Shoot (1437902762624)
     *   - GetBall (1437903060557)
     *
     * Vars:
     */
    bool TransitionCondition1437903090726::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1437903089522) ENABLED START*/
        return !wm->ball->haveBall();
        /*PROTECTED REGION END*/

    }

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : anyChildSuccess 
     *
     * Plans in State: 				
     *   - Plan - (Name): DribbleToAttackPointOwnPenaltySpot, (PlanID): 1437391438054 				
     *   - Plan - (Name): ShovelSelectLowKick, (PlanID): 1435156714286 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1437902649391)
     *
     * States:
     *   - GetBall (1437902649390)
     *   - DribbleToOppPenaltySpot (1437902693350)
     *   - DribbleToOwnPenaltySpot (1437902704803)
     *   - NewSuccessState (1437902754765)
     *   - Shoot (1437902762624)
     *   - GetBall (1437903060557)
     *
     * Vars:
     */
    bool TransitionCondition1437903100138::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1437903097451) ENABLED START*/
        return rp->anyChildrenStatus(PlanStatus::Success);
        /*PROTECTED REGION END*/

    }

    //State: NewSuccessState in Plan: AttackOppGoalPlan

    //State: Shoot in Plan: AttackOppGoalPlan

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : anyChildSuccess 
     *
     * Plans in State: 				
     *   - Plan - (Name): GoalKickDefault, (PlanID): 1415205578139 				
     *   - Plan - (Name): ShovelSelectLowKick, (PlanID): 1435156714286 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1437902649391)
     *
     * States:
     *   - GetBall (1437902649390)
     *   - DribbleToOppPenaltySpot (1437902693350)
     *   - DribbleToOwnPenaltySpot (1437902704803)
     *   - NewSuccessState (1437902754765)
     *   - Shoot (1437902762624)
     *   - GetBall (1437903060557)
     *
     * Vars:
     */
    bool TransitionCondition1437903097184::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1437903095217) ENABLED START*/
        return rp->anyChildrenStatus(PlanStatus::Success);
        /*PROTECTED REGION END*/

    }

    //State: GetBall in Plan: AttackOppGoalPlan

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : haveBall 
     *
     * Plans in State: 				
     *   - Plan - (Name): GetBallDefault, (PlanID): 1414840399972 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1437902649391)
     *
     * States:
     *   - GetBall (1437902649390)
     *   - DribbleToOppPenaltySpot (1437902693350)
     *   - DribbleToOwnPenaltySpot (1437902704803)
     *   - NewSuccessState (1437902754765)
     *   - Shoot (1437902762624)
     *   - GetBall (1437903060557)
     *
     * Vars:
     */
    bool TransitionCondition1437903092576::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1437903090929) ENABLED START*/
        return wm->ball->haveBall();
        /*PROTECTED REGION END*/

    }

}
