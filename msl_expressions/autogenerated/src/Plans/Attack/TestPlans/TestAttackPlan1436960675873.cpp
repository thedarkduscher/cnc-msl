#include "Plans/Attack/TestPlans/TestAttackPlan1436960675873.h"
using namespace alica;
/*PROTECTED REGION ID(eph1436960675873) ENABLED START*/ //Add additional using directives here
#include <MSLWorldModel.h>
#include <Game.h>
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:TestAttackPlan

    /* generated comment
     
     Task: DefaultTask  -> EntryPoint-ID: 1436960675875

     */
    shared_ptr<UtilityFunction> UtilityFunction1436960675873::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1436960675873) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

    //State: Stop in Plan: TestAttackPlan

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : Situation == start 
     *
     * Plans in State: 				
     *   - Plan - (Name): StopDefault, (PlanID): 1413992626194 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1436960675875)
     *
     * States:
     *   - Stop (1436960675874)
     *   - Start (1436960747966)
     *
     * Vars:
     */
    bool TransitionCondition1436960798234::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1436960796936) ENABLED START*/
        return wm->game->checkSituation(msl::Situation::Start);
        /*PROTECTED REGION END*/

    }

    //State: Start in Plan: TestAttackPlan

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : situation == stop || anyChildSucc 
     *
     * Plans in State: 				
     *   - Plan - (Name): AttackOppGoalPlan, (PlanID): 1437902649389 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1436960675875)
     *
     * States:
     *   - Stop (1436960675874)
     *   - Start (1436960747966)
     *
     * Vars:
     */
    bool TransitionCondition1436960799378::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1436960798576) ENABLED START*/
        return wm->game->checkSituation(msl::Situation::Stop) || rp->anyChildrenStatus(PlanStatus::Success);
        /*PROTECTED REGION END*/

    }

}
