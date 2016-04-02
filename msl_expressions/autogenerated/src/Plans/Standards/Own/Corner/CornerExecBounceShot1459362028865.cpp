#include "Plans/Standards/Own/Corner/CornerExecBounceShot1459362028865.h"
using namespace alica;
/*PROTECTED REGION ID(eph1459362028865) ENABLED START*/ //Add additional using directives here
#include "engine/Assignment.h"
#include "engine/collections/StateCollection.h"
#include "engine/model/Plan.h"
#include "engine/AlicaEngine.h"
#include "engine/teamobserver/TeamObserver.h"
#include "engine/collections/RobotEngineData.h"
#include "engine/collections/SuccessMarks.h"
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:CornerExecBounceShot

    /* generated comment
     
     Task: ExecuteStandard  -> EntryPoint-ID: 1459362049517

     Task: ReceiveStandard  -> EntryPoint-ID: 1459365320409

     Task: Defend  -> EntryPoint-ID: 1459365322922

     */
    shared_ptr<UtilityFunction> UtilityFunction1459362028865::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1459362028865) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

    //State: WaitForReceiver in Plan: CornerExecBounceShot

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : WaitForReceiver2FinishAlign 
     *
     * Plans in State: 				
     *   - Plan - (Name): BounceShotAlignPasserCornerExec, (PlanID): 1459357015987 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1459362049517)
     *   - ReceiveStandard (1439997023446) (Entrypoint: 1459365320409)
     *   - Defend (1225115406909) (Entrypoint: 1459365322922)
     *
     * States:
     *   - WaitForReceiver (1459362049516)
     *   - RealignWall (1459365278157)
     *   - Wait (1459365280181)
     *   - BouncePassOffRobot (1459365281222)
     *   - FinishAlign (1459365282539)
     *   - WaitForShotToFinish (1459365284057)
     *   - WaitForPass (1459365285847)
     *   - DefenderWall (1459365287615)
     *   - NewSuccessState (1459365294648)
     *   - NewSuccessState (1459365296108)
     *   - NewSuccessState (1459365297570)
     *
     * Vars:
     */
    bool TransitionCondition1459365410684::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1459365407849) ENABLED START*/
        return (rp->getAssignment()->getRobotStateMapping()->getRobotsInState(1459365285847).size() > 0);
        /*PROTECTED REGION END*/

    }

    //State: RealignWall in Plan: CornerExecBounceShot

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : RealignWall2WaitforPass 
     *
     * Plans in State: 				
     *   - Plan - (Name): BounceShotRealignWall, (PlanID): 1459356753335 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1459362049517)
     *   - ReceiveStandard (1439997023446) (Entrypoint: 1459365320409)
     *   - Defend (1225115406909) (Entrypoint: 1459365322922)
     *
     * States:
     *   - WaitForReceiver (1459362049516)
     *   - RealignWall (1459365278157)
     *   - Wait (1459365280181)
     *   - BouncePassOffRobot (1459365281222)
     *   - FinishAlign (1459365282539)
     *   - WaitForShotToFinish (1459365284057)
     *   - WaitForPass (1459365285847)
     *   - DefenderWall (1459365287615)
     *   - NewSuccessState (1459365294648)
     *   - NewSuccessState (1459365296108)
     *   - NewSuccessState (1459365297570)
     *
     * Vars:
     */
    bool TransitionCondition1459365407637::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1459365401604) ENABLED START*/
        return rp->anyChildrenStatus(PlanStatus::Success) || isTimeOut(5000000000, rp->getStateStartTime(), rp);
        /*PROTECTED REGION END*/

    }

    //State: Wait in Plan: CornerExecBounceShot

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : Wait2Succ 
     *
     * Plans in State: 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1459362049517)
     *   - ReceiveStandard (1439997023446) (Entrypoint: 1459365320409)
     *   - Defend (1225115406909) (Entrypoint: 1459365322922)
     *
     * States:
     *   - WaitForReceiver (1459362049516)
     *   - RealignWall (1459365278157)
     *   - Wait (1459365280181)
     *   - BouncePassOffRobot (1459365281222)
     *   - FinishAlign (1459365282539)
     *   - WaitForShotToFinish (1459365284057)
     *   - WaitForPass (1459365285847)
     *   - DefenderWall (1459365287615)
     *   - NewSuccessState (1459365294648)
     *   - NewSuccessState (1459365296108)
     *   - NewSuccessState (1459365297570)
     *
     * Vars:
     */
    bool TransitionCondition1459365392367::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1459365391425) ENABLED START*/
        return isTimeOut(500000000, rp->getStateStartTime(), rp);
        /*PROTECTED REGION END*/

    }

    //State: BouncePassOffRobot in Plan: CornerExecBounceShot

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : BouncePassOffRobot2Wait 
     *
     * Plans in State: 				
     *   - Plan - (Name): BouncePassShootCornerKick, (PlanID): 1459357188003 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1459362049517)
     *   - ReceiveStandard (1439997023446) (Entrypoint: 1459365320409)
     *   - Defend (1225115406909) (Entrypoint: 1459365322922)
     *
     * States:
     *   - WaitForReceiver (1459362049516)
     *   - RealignWall (1459365278157)
     *   - Wait (1459365280181)
     *   - BouncePassOffRobot (1459365281222)
     *   - FinishAlign (1459365282539)
     *   - WaitForShotToFinish (1459365284057)
     *   - WaitForPass (1459365285847)
     *   - DefenderWall (1459365287615)
     *   - NewSuccessState (1459365294648)
     *   - NewSuccessState (1459365296108)
     *   - NewSuccessState (1459365297570)
     *
     * Vars:
     */
    bool TransitionCondition1459365412597::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1459365411957) ENABLED START*/
        return rp->anyChildrenStatus(PlanStatus::Success) || isTimeOut(5000000000, rp->getStateStartTime(), rp);
        /*PROTECTED REGION END*/

    }

    //State: FinishAlign in Plan: CornerExecBounceShot

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : FinishAlign2BouncePassOffRobot 
     *
     * Plans in State: 				
     *   - Plan - (Name): StandardActuateDefault, (PlanID): 1435766278023 				
     *   - Plan - (Name): BouncePassFinishAlignCornerKick, (PlanID): 1459357089325 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1459362049517)
     *   - ReceiveStandard (1439997023446) (Entrypoint: 1459365320409)
     *   - Defend (1225115406909) (Entrypoint: 1459365322922)
     *
     * States:
     *   - WaitForReceiver (1459362049516)
     *   - RealignWall (1459365278157)
     *   - Wait (1459365280181)
     *   - BouncePassOffRobot (1459365281222)
     *   - FinishAlign (1459365282539)
     *   - WaitForShotToFinish (1459365284057)
     *   - WaitForPass (1459365285847)
     *   - DefenderWall (1459365287615)
     *   - NewSuccessState (1459365294648)
     *   - NewSuccessState (1459365296108)
     *   - NewSuccessState (1459365297570)
     *
     * Vars:
     */
    bool TransitionCondition1459365411722::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1459365410825) ENABLED START*/
        return rp->anyChildrenStatus(PlanStatus::Success) || isTimeOut(5000000000, rp->getStateStartTime(), rp);
        /*PROTECTED REGION END*/

    }

    //State: WaitForShotToFinish in Plan: CornerExecBounceShot

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : WaitForShotToFinish2Succ 
     *
     * Plans in State: 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1459362049517)
     *   - ReceiveStandard (1439997023446) (Entrypoint: 1459365320409)
     *   - Defend (1225115406909) (Entrypoint: 1459365322922)
     *
     * States:
     *   - WaitForReceiver (1459362049516)
     *   - RealignWall (1459365278157)
     *   - Wait (1459365280181)
     *   - BouncePassOffRobot (1459365281222)
     *   - FinishAlign (1459365282539)
     *   - WaitForShotToFinish (1459365284057)
     *   - WaitForPass (1459365285847)
     *   - DefenderWall (1459365287615)
     *   - NewSuccessState (1459365294648)
     *   - NewSuccessState (1459365296108)
     *   - NewSuccessState (1459365297570)
     *
     * Vars:
     */
    bool TransitionCondition1459365394125::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1459365392554) ENABLED START*/
        if (isTimeOut(3000000000, rp->getStateStartTime(), rp))
        {
            return true;
        }
        auto ball = wm->ball.getEgoBallPosition();
        auto vel = wm->ball.getEgoBallVelocity();
        return (vel != nullptr && ball != nullptr && vel->length() > 800 && (ball->x * vel->x + ball->y * vel->y > 0));
        /*PROTECTED REGION END*/

    }

    //State: WaitForPass in Plan: CornerExecBounceShot

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : WaitForPass2WaitforShotToFinish 
     *
     * Plans in State: 				
     *   - Plan - (Name): StopDefault, (PlanID): 1413992626194 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1459362049517)
     *   - ReceiveStandard (1439997023446) (Entrypoint: 1459365320409)
     *   - Defend (1225115406909) (Entrypoint: 1459365322922)
     *
     * States:
     *   - WaitForReceiver (1459362049516)
     *   - RealignWall (1459365278157)
     *   - Wait (1459365280181)
     *   - BouncePassOffRobot (1459365281222)
     *   - FinishAlign (1459365282539)
     *   - WaitForShotToFinish (1459365284057)
     *   - WaitForPass (1459365285847)
     *   - DefenderWall (1459365287615)
     *   - NewSuccessState (1459365294648)
     *   - NewSuccessState (1459365296108)
     *   - NewSuccessState (1459365297570)
     *
     * Vars:
     */
    bool TransitionCondition1459365413923::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1459365412813) ENABLED START*/
        return (rp->getAssignment()->getRobotStateMapping()->getRobotsInState(1459365280181).size() > 0)
                || isTimeOut(10000000000, rp->getStateStartTime(), rp);
        /*PROTECTED REGION END*/

    }

    //State: DefenderWall in Plan: CornerExecBounceShot

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : DefenderWall2Succ 
     *
     * Plans in State: 				
     *   - Plan - (Name): StandardDefendPosCornerExecBounceShot, (PlanID): 1459356685875 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1459362049517)
     *   - ReceiveStandard (1439997023446) (Entrypoint: 1459365320409)
     *   - Defend (1225115406909) (Entrypoint: 1459365322922)
     *
     * States:
     *   - WaitForReceiver (1459362049516)
     *   - RealignWall (1459365278157)
     *   - Wait (1459365280181)
     *   - BouncePassOffRobot (1459365281222)
     *   - FinishAlign (1459365282539)
     *   - WaitForShotToFinish (1459365284057)
     *   - WaitForPass (1459365285847)
     *   - DefenderWall (1459365287615)
     *   - NewSuccessState (1459365294648)
     *   - NewSuccessState (1459365296108)
     *   - NewSuccessState (1459365297570)
     *
     * Vars:
     */
    bool TransitionCondition1459365401307::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1459365394266) ENABLED START*/
        bool ret = false;
        auto p = rp->getPlan();
        if (p != nullptr)
        {
            auto p2 = (Plan*)p;
            EntryPoint* ep = p2->getEntryPoints().at(1238601692867);
            auto rs = rp->getAlicaEngine()->getTeamObserver()->getAvailableRobots();
            for (RobotEngineData* r : *rs)
            {
                if (r->getSuccessMarks()->succeeded(p, ep))
                {
                    return true;
                }
            }
        }
        //return isEntryPointSuccessful(1238601692867,rp)
        return ret || isTimeOut(9500000000, rp->getStateStartTime(), rp);;
        /*PROTECTED REGION END*/

    }

//State: NewSuccessState in Plan: CornerExecBounceShot

//State: NewSuccessState in Plan: CornerExecBounceShot

//State: NewSuccessState in Plan: CornerExecBounceShot

}
