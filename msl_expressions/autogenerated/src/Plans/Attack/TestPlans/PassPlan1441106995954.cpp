#include "Plans/Attack/TestPlans/PassPlan1441106995954.h"
using namespace alica;
/*PROTECTED REGION ID(eph1441106995954) ENABLED START*/ //Add additional using directives here
#include <MSLWorldModel.h>
#include <Game.h>
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:PassPlan

    /* generated comment
     
     Task: DefaultTask  -> EntryPoint-ID: 1441107009535

     Task: AttackSupport  -> EntryPoint-ID: 1441107038524

     Task: InGamePassReceiver  -> EntryPoint-ID: 1441107040804

     */
    shared_ptr<UtilityFunction> UtilityFunction1441106995954::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1441106995954) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

    //State: SearchForPassPoint in Plan: PassPlan

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : situation freekick 
     *
     * Plans in State: 				
     *   - Plan - (Name): SearchForPassPointTest, (PlanID): 1441107270872 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1441107009535)
     *   - AttackSupport (1225115536468) (Entrypoint: 1441107038524)
     *   - InGamePassReceiver (1307185798142) (Entrypoint: 1441107040804)
     *
     * States:
     *   - SearchForPassPoint (1441107009534)
     *   - WaitForPass (1441107086220)
     *   - WaitForPass (1441107089085)
     *   - Pass (1441107193775)
     *
     * Vars:
     */
    bool TransitionCondition1441107213887::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1441107212515) ENABLED START*/
    	return wm->game->checkSituation(msl::Situation::OwnFreekick);
        /*PROTECTED REGION END*/

    }

    //State: WaitForPass in Plan: PassPlan

    //State: WaitForPass in Plan: PassPlan

    //State: Pass in Plan: PassPlan

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : situation goalkick 
     *
     * Plans in State: 				
     *   - Plan - (Name): AlignAndPassRapidTest, (PlanID): 1441108023281 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1441107009535)
     *   - AttackSupport (1225115536468) (Entrypoint: 1441107038524)
     *   - InGamePassReceiver (1307185798142) (Entrypoint: 1441107040804)
     *
     * States:
     *   - SearchForPassPoint (1441107009534)
     *   - WaitForPass (1441107086220)
     *   - WaitForPass (1441107089085)
     *   - Pass (1441107193775)
     *
     * Vars:
     */
    bool TransitionCondition1441107217606::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1441107214550) ENABLED START*/
    	return wm->game->checkSituation(msl::Situation::OwnGoalkick);
        /*PROTECTED REGION END*/

    }

}
