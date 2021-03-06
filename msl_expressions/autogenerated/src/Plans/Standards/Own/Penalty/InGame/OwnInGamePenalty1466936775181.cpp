#include "Plans/Standards/Own/Penalty/InGame/OwnInGamePenalty1466936775181.h"
using namespace alica;
/*PROTECTED REGION ID(eph1466936775181) ENABLED START*/ //Add additional using directives here
#include <MSLWorldModel.h>
#include <MSLEnums.h>
#include <Ball.h>
#include <Game.h>
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:OwnInGamePenalty

    /* generated comment
     
     Task: ExecuteStandard  -> EntryPoint-ID: 1466936775183

     Task: SupportAttack  -> EntryPoint-ID: 1466936799335

     Task: Defend  -> EntryPoint-ID: 1466972404622

     */
    shared_ptr<UtilityFunction> UtilityFunction1466936775181::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1466936775181) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

    //State: MoveBehindBall in Plan: OwnInGamePenalty

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : any child success 
     *
     * Plans in State: 				
     *   - Plan - (Name): PenaltyPosExecuterDefault, (PlanID): 1466940432683 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1466936775183)
     *   - SupportAttack (1225115536468) (Entrypoint: 1466936799335)
     *   - Defend (1225115406909) (Entrypoint: 1466972404622)
     *
     * States:
     *   - MoveBehindBall (1466936775182)
     *   - Grab Ball (1466936786859)
     *   - Wait4Start (1466936788188)
     *   - AlignAndShoot (1466936790118)
     *   - Pos4Rebounce (1466936792646)
     *   - PenaltySuccess (1466936854348)
     *   - Defend (1466972478368)
     *
     * Vars:
     */
    bool TransitionCondition1466936849620::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1466936848368) ENABLED START*/
        return rp->anyChildrenStatus(PlanStatus::Success);
        /*PROTECTED REGION END*/

    }

    //State: Grab Ball in Plan: OwnInGamePenalty

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : have ball 
     *
     * Plans in State: 				
     *   - Plan - (Name): ShovelSelectLowKick, (PlanID): 1435156714286 				
     *   - Plan - (Name): InterceptCarefullyDefault, (PlanID): 1427703234654 				
     *   - Plan - (Name): DribbleControlNoBall, (PlanID): 1450175539163 				
     *   - Plan - (Name): StandardActuateDefault, (PlanID): 1435766278023 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1466936775183)
     *   - SupportAttack (1225115536468) (Entrypoint: 1466936799335)
     *   - Defend (1225115406909) (Entrypoint: 1466972404622)
     *
     * States:
     *   - MoveBehindBall (1466936775182)
     *   - Grab Ball (1466936786859)
     *   - Wait4Start (1466936788188)
     *   - AlignAndShoot (1466936790118)
     *   - Pos4Rebounce (1466936792646)
     *   - PenaltySuccess (1466936854348)
     *   - Defend (1466972478368)
     *
     * Vars:
     */
    bool TransitionCondition1466936851265::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1466936850672) ENABLED START*/
        return this->wm->ball->haveBall();
        /*PROTECTED REGION END*/

    }

    //State: Wait4Start in Plan: OwnInGamePenalty

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : situation = start 
     *
     * Plans in State: 				
     *   - Plan - (Name): StopDefault, (PlanID): 1413992626194 				
     *   - Plan - (Name): ShovelSelectLowKick, (PlanID): 1435156714286 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1466936775183)
     *   - SupportAttack (1225115536468) (Entrypoint: 1466936799335)
     *   - Defend (1225115406909) (Entrypoint: 1466972404622)
     *
     * States:
     *   - MoveBehindBall (1466936775182)
     *   - Grab Ball (1466936786859)
     *   - Wait4Start (1466936788188)
     *   - AlignAndShoot (1466936790118)
     *   - Pos4Rebounce (1466936792646)
     *   - PenaltySuccess (1466936854348)
     *   - Defend (1466972478368)
     *
     * Vars:
     */
    bool TransitionCondition1466936850439::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1466936849764) ENABLED START*/
        return wm->game->checkSituation(msl::Situation::Start);
        /*PROTECTED REGION END*/

    }

    //State: AlignAndShoot in Plan: OwnInGamePenalty

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : !have ball 
     *
     * Plans in State: 				
     *   - Plan - (Name): ShovelSelectLowKick, (PlanID): 1435156714286 				
     *   - Plan - (Name): PenaltyShootDefault, (PlanID): 1466940268216 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1466936775183)
     *   - SupportAttack (1225115536468) (Entrypoint: 1466936799335)
     *   - Defend (1225115406909) (Entrypoint: 1466972404622)
     *
     * States:
     *   - MoveBehindBall (1466936775182)
     *   - Grab Ball (1466936786859)
     *   - Wait4Start (1466936788188)
     *   - AlignAndShoot (1466936790118)
     *   - Pos4Rebounce (1466936792646)
     *   - PenaltySuccess (1466936854348)
     *   - Defend (1466972478368)
     *
     * Vars:
     */
    bool TransitionCondition1466936852075::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1466936851417) ENABLED START*/
        return !this->wm->ball->haveBall();
        /*PROTECTED REGION END*/

    }

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : any child success 
     *
     * Plans in State: 				
     *   - Plan - (Name): ShovelSelectLowKick, (PlanID): 1435156714286 				
     *   - Plan - (Name): PenaltyShootDefault, (PlanID): 1466940268216 
     *
     * Tasks: 
     *   - ExecuteStandard (1439997010902) (Entrypoint: 1466936775183)
     *   - SupportAttack (1225115536468) (Entrypoint: 1466936799335)
     *   - Defend (1225115406909) (Entrypoint: 1466972404622)
     *
     * States:
     *   - MoveBehindBall (1466936775182)
     *   - Grab Ball (1466936786859)
     *   - Wait4Start (1466936788188)
     *   - AlignAndShoot (1466936790118)
     *   - Pos4Rebounce (1466936792646)
     *   - PenaltySuccess (1466936854348)
     *   - Defend (1466972478368)
     *
     * Vars:
     */
    bool TransitionCondition1466936862234::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1466936861165) ENABLED START*/
        return rp->anyChildrenStatus(PlanStatus::Success);
        /*PROTECTED REGION END*/

    }

//State: Pos4Rebounce in Plan: OwnInGamePenalty

//State: PenaltySuccess in Plan: OwnInGamePenalty

//State: Defend in Plan: OwnInGamePenalty

}
