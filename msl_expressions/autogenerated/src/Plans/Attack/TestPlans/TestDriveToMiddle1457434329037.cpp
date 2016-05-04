#include "Plans/Attack/TestPlans/TestDriveToMiddle1457434329037.h"
using namespace alica;
/*PROTECTED REGION ID(eph1457434329037) ENABLED START*/ //Add additional using directives here
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:TestDriveToMiddle

    /* generated comment
     
     Task: DefaultTask  -> EntryPoint-ID: 1457434329039

     */
    shared_ptr<UtilityFunction> UtilityFunction1457434329037::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1457434329037) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

    //State: Stop in Plan: TestDriveToMiddle

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : Start 
     *
     * Plans in State: 				
     *   - Plan - (Name): StopDefault, (PlanID): 1413992626194 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1457434329039)
     *
     * States:
     *   - Stop (1457434329038)
     *   - DriveToMiddle (1457434444773)
     *
     * Vars:
     */
    bool TransitionCondition1457434475372::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1457434473874) ENABLED START*/
        return wm->game->checkSituation(msl::Situation::Start);
        /*PROTECTED REGION END*/

    }

    //State: DriveToMiddle in Plan: TestDriveToMiddle

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : Stop 
     *
     * Plans in State: 				
     *   - Plan - (Name): DriveToMiddle, (PlanID): 1431527260342 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1457434329039)
     *
     * States:
     *   - Stop (1457434329038)
     *   - DriveToMiddle (1457434444773)
     *
     * Vars:
     */
    bool TransitionCondition1457434476549::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1457434475595) ENABLED START*/
        return wm->game->checkSituation(msl::Situation::Stop);;
        /*PROTECTED REGION END*/

    }

}
