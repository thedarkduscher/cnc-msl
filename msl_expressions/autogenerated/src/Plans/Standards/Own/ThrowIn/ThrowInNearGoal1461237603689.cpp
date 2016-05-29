#include "Plans/Standards/Own/ThrowIn/ThrowInNearGoal1461237603689.h"
using namespace alica;
/*PROTECTED REGION ID(eph1461237603689) ENABLED START*/ //Add additional using directives here
#include "engine/model/Plan.h"
#include "engine/Assignment.h"
#include "engine/collections/StateCollection.h"
#include "BallXIntervall.h"
#include <MSLWorldModel.h>
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:ThrowInNearGoal

    //Check of RuntimeCondition - (Name): NewRuntimeCondition, (ConditionString): , (Comment) :  

    /* 
     * Available Vars:
     */
    bool RunTimeCondition1461574228077::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1461574228077) ENABLED START*/
        return true;
        /*PROTECTED REGION END*/
    }

    /* generated comment
     
     Task: ExecuteStandard  -> EntryPoint-ID: 1461237603691

     Task: ReceiveStandard  -> EntryPoint-ID: 1461237744256

     Task: Block  -> EntryPoint-ID: 1461237746825

     Task: InGamePassReceiver  -> EntryPoint-ID: 1461237748826

     */
    shared_ptr<UtilityFunction> UtilityFunction1461237603689::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1461237603689) ENABLED START*/
        vector<long> entryPoints;

        entryPoints.push_back(1461237603691); // ExecuteStandard
        entryPoints.push_back(1461237744256); // ReceiveStandard
        entryPoints.push_back(1461237746825); // Block
        entryPoints.push_back(1461237748826); // InGamePassReceiver

        double angle = 55 * M_PI / 180; // nice angle to shoot on the goal
        double x = ((msl::MSLWorldModel::get()->field->getFieldWidth() / 2.0) / atan(angle)) - 2300;
        BallXIntervall* us = new BallXIntervall(2.0, "ThrowInNearGoal", 2, entryPoints, 2500.0,
                                                msl::MSLWorldModel::get()->field->getFieldLength() / 2 - x, 1000.0);
        list<USummand*> utilSummands;
        utilSummands.push_back(us);
        shared_ptr < UtilityFunction > function = make_shared < UtilityFunction
                > ("ThrowInNearGoalTest", utilSummands, 0.1, 0.2, plan);
        return function;

        /*PROTECTED REGION END*/
    }

    //State: Align in Plan: ThrowInNearGoal

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : Aligned 
     *
     * Plans in State: 				
     *   - Plan - (Name): StandardAlignToPointExecutor, (PlanID): 1435155363994 				
     *   - Plan - (Name): StandardActuateDefault, (PlanID): 1435766278023 				
     *   - Plan - (Name): ShovelSelectLowKick, (PlanID): 1435156714286 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1461237603691)
     *   - ReceiveStandard (1439997023446) (Entrypoint: 1461237744256)
     *   - Block (1461237765109) (Entrypoint: 1461237746825)
     *   - InGamePassReceiver (1307185798142) (Entrypoint: 1461237748826)
     *
     * States:
     *   - Align (1461237603690)
     *   - Success (1461237614163)
     *   - GrabBall (1461237638988)
     *   - Pass (1461237666032)
     *   - Align (1461237695900)
     *   - Receive (1461237704581)
     *   - Block (1461237711590)
     *   - PosAlternativePassReceiver (1461237728343)
     *   - Wait (1461584409837)
     *
     * Vars:
     */
    bool TransitionCondition1461237657374::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1461237656318) ENABLED START*/
        return (rp->anyChildrenStatus(PlanStatus::Success) && wm->game->checkSituation(msl::Situation::Start))
                || (wm->game->checkSituation(msl::Situation::Start)
                        && wm->getTime() - wm->game->getTimeSinceStart() > 8000000000);
        /*PROTECTED REGION END*/

    }

    //State: Success in Plan: ThrowInNearGoal

    //State: GrabBall in Plan: ThrowInNearGoal

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : haveBall 
     *
     * Plans in State: 				
     *   - Plan - (Name): ShovelSelectLowKick, (PlanID): 1435156714286 				
     *   - Plan - (Name): StandardActuateDefault, (PlanID): 1435766278023 				
     *   - Plan - (Name): StandardAlignAndGrabThrowIn, (PlanID): 1461583806472 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1461237603691)
     *   - ReceiveStandard (1439997023446) (Entrypoint: 1461237744256)
     *   - Block (1461237765109) (Entrypoint: 1461237746825)
     *   - InGamePassReceiver (1307185798142) (Entrypoint: 1461237748826)
     *
     * States:
     *   - Align (1461237603690)
     *   - Success (1461237614163)
     *   - GrabBall (1461237638988)
     *   - Pass (1461237666032)
     *   - Align (1461237695900)
     *   - Receive (1461237704581)
     *   - Block (1461237711590)
     *   - PosAlternativePassReceiver (1461237728343)
     *   - Wait (1461584409837)
     *
     * Vars:
     */
    bool TransitionCondition1461237677283::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1461237676305) ENABLED START*/
        return rp->anyChildrenStatus(PlanStatus::Success);
        /*PROTECTED REGION END*/

    }

    //State: Pass in Plan: ThrowInNearGoal

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : not haveBall 
     *
     * Plans in State: 				
     *   - Plan - (Name): StandardPassDefault, (PlanID): 1435760175843 				
     *   - Plan - (Name): StandardActuateDefault, (PlanID): 1435766278023 				
     *   - Plan - (Name): ShovelSelectLowKick, (PlanID): 1435156714286 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1461237603691)
     *   - ReceiveStandard (1439997023446) (Entrypoint: 1461237744256)
     *   - Block (1461237765109) (Entrypoint: 1461237746825)
     *   - InGamePassReceiver (1307185798142) (Entrypoint: 1461237748826)
     *
     * States:
     *   - Align (1461237603690)
     *   - Success (1461237614163)
     *   - GrabBall (1461237638988)
     *   - Pass (1461237666032)
     *   - Align (1461237695900)
     *   - Receive (1461237704581)
     *   - Block (1461237711590)
     *   - PosAlternativePassReceiver (1461237728343)
     *   - Wait (1461584409837)
     *
     * Vars:
     */
    bool TransitionCondition1461584286706::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1461584284347) ENABLED START*/
        return !wm->ball->haveBall();
        /*PROTECTED REGION END*/

    }

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : executed 
     *
     * Plans in State: 				
     *   - Plan - (Name): StandardPassDefault, (PlanID): 1435760175843 				
     *   - Plan - (Name): StandardActuateDefault, (PlanID): 1435766278023 				
     *   - Plan - (Name): ShovelSelectLowKick, (PlanID): 1435156714286 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1461237603691)
     *   - ReceiveStandard (1439997023446) (Entrypoint: 1461237744256)
     *   - Block (1461237765109) (Entrypoint: 1461237746825)
     *   - InGamePassReceiver (1307185798142) (Entrypoint: 1461237748826)
     *
     * States:
     *   - Align (1461237603690)
     *   - Success (1461237614163)
     *   - GrabBall (1461237638988)
     *   - Pass (1461237666032)
     *   - Align (1461237695900)
     *   - Receive (1461237704581)
     *   - Block (1461237711590)
     *   - PosAlternativePassReceiver (1461237728343)
     *   - Wait (1461584409837)
     *
     * Vars:
     */
    bool TransitionCondition1461584441559::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1461584440317) ENABLED START*/
        return rp->anyChildrenStatus(PlanStatus::Success);
        /*PROTECTED REGION END*/

    }

    //State: Align in Plan: ThrowInNearGoal

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : aligned && executor in wait 
     *
     * Plans in State: 				
     *   - Plan - (Name): PositionReceiverThrownInDefault, (PlanID): 1461584235418 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1461237603691)
     *   - ReceiveStandard (1439997023446) (Entrypoint: 1461237744256)
     *   - Block (1461237765109) (Entrypoint: 1461237746825)
     *   - InGamePassReceiver (1307185798142) (Entrypoint: 1461237748826)
     *
     * States:
     *   - Align (1461237603690)
     *   - Success (1461237614163)
     *   - GrabBall (1461237638988)
     *   - Pass (1461237666032)
     *   - Align (1461237695900)
     *   - Receive (1461237704581)
     *   - Block (1461237711590)
     *   - PosAlternativePassReceiver (1461237728343)
     *   - Wait (1461584409837)
     *
     * Vars:
     */
    bool TransitionCondition1461572770571::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1461572769511) ENABLED START*/
        return rp->anyChildrenStatus(PlanStatus::Success)
                && rp->getAssignment()->getRobotStateMapping()->getRobotsInState(1461584409837).size() > 0;
        /*PROTECTED REGION END*/

    }

    //State: Receive in Plan: ThrowInNearGoal

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : pass received 
     *
     * Plans in State: 				
     *   - Plan - (Name): ShovelSelectHighKick, (PlanID): 1435156811453 				
     *   - Plan - (Name): InterceptCarefullyDefault, (PlanID): 1427703234654 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1461237603691)
     *   - ReceiveStandard (1439997023446) (Entrypoint: 1461237744256)
     *   - Block (1461237765109) (Entrypoint: 1461237746825)
     *   - InGamePassReceiver (1307185798142) (Entrypoint: 1461237748826)
     *
     * States:
     *   - Align (1461237603690)
     *   - Success (1461237614163)
     *   - GrabBall (1461237638988)
     *   - Pass (1461237666032)
     *   - Align (1461237695900)
     *   - Receive (1461237704581)
     *   - Block (1461237711590)
     *   - PosAlternativePassReceiver (1461237728343)
     *   - Wait (1461584409837)
     *
     * Vars:
     */
    bool TransitionCondition1461237854702::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1461237853423) ENABLED START*/
        return this->isTimeOut(750000000, rp->getStateStartTime(), rp);
        /*PROTECTED REGION END*/

    }

//State: Block in Plan: ThrowInNearGoal

//State: PosAlternativePassReceiver in Plan: ThrowInNearGoal

//State: Wait in Plan: ThrowInNearGoal

}
