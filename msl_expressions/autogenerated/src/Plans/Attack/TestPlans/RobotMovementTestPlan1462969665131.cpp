#include "Plans/Attack/TestPlans/RobotMovementTestPlan1462969665131.h"
using namespace alica;
/*PROTECTED REGION ID(eph1462969665131) ENABLED START*/ //Add additional using directives here
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:RobotMovementTestPlan

    /* generated comment
     
     Task: DefaultTask  -> EntryPoint-ID: 1462969665133

     */
    shared_ptr<UtilityFunction> UtilityFunction1462969665131::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1462969665131) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

    //State: Stop in Plan: RobotMovementTestPlan

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : start 
     *
     * Plans in State: 				
     *   - Plan - (Name): StopDefault, (PlanID): 1413992626194 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1462969665133)
     *
     * States:
     *   - Stop (1462969665132)
     *   - dribbleTest (1462969884284)
     *
     * Vars:
     */
    bool TransitionCondition1462969760665::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1462969759156) ENABLED START*/
        return wm->game->checkSituation(msl::Situation::Start);
        /*PROTECTED REGION END*/

    }

    //State: dribbleTest in Plan: RobotMovementTestPlan

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : stop 
     *
     * Plans in State: 				
     *   - Plan - (Name): RobotMovementDribbleTestDefault, (PlanID): 1462969753310 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1462969665133)
     *
     * States:
     *   - Stop (1462969665132)
     *   - dribbleTest (1462969884284)
     *
     * Vars:
     */
    bool TransitionCondition1462969788458::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1462969786619) ENABLED START*/
        return wm->game->checkSituation(msl::Situation::Stop);
        /*PROTECTED REGION END*/

    }

}
