#include "Plans/TestPlans/KickCurveTuning/KickCurveTuning1457698586746.h"
using namespace alica;
/*PROTECTED REGION ID(eph1457698586746) ENABLED START*/ //Add additional using directives here
#include <MSLEnums.h>
#include <MSLWorldModel.h>
#include <Game.h>
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:KickCurveTuning

    /* generated comment
     
     Task: DefaultTask  -> EntryPoint-ID: 1457698586748

     */
    shared_ptr<UtilityFunction> UtilityFunction1457698586746::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1457698586746) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

    //State: Stop in Plan: KickCurveTuning

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : situation=start 
     *
     * Plans in State: 				
     *   - Plan - (Name): StopDefault, (PlanID): 1413992626194 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1457698586748)
     *
     * States:
     *   - Stop (1457698586747)
     *   - LaserBallTracking (1457698608390)
     *
     * Vars:
     */
    bool TransitionCondition1457698634601::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1457698633209) ENABLED START*/
    	return wm->game->checkSituation(msl::Situation::Start);
        /*PROTECTED REGION END*/

    }

    //State: LaserBallTracking in Plan: KickCurveTuning

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : situation=stop 
     *
     * Plans in State: 				
     *   - Plan - (Name): LaserBallTrackingDefault, (PlanID): 1457698689219 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1457698586748)
     *
     * States:
     *   - Stop (1457698586747)
     *   - LaserBallTracking (1457698608390)
     *
     * Vars:
     */
    bool TransitionCondition1457698635818::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1457698634760) ENABLED START*/
    	return wm->game->checkSituation(msl::Situation::Stop);
        /*PROTECTED REGION END*/

    }

}
