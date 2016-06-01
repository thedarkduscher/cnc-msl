#include "Plans/Defence/Test/TestBackroomDefence1455127495970.h"
using namespace alica;
/*PROTECTED REGION ID(eph1455127495970) ENABLED START*/ //Add additional using directives here
#include <MSLWorldModel.h>
#include <Game.h>
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:TestBackroomDefence

    /* generated comment
     
     Task: DefaultTask  -> EntryPoint-ID: 1455127495972

     */
    shared_ptr<UtilityFunction> UtilityFunction1455127495970::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1455127495970) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

    //State: Stop in Plan: TestBackroomDefence

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : Situation == start 
     *
     * Plans in State: 				
     *   - Plan - (Name): StopDefault, (PlanID): 1413992626194 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1455127495972)
     *
     * States:
     *   - Stop (1455127495971)
     *   - BackroomDefence (1455127584801)
     *
     * Vars:
     */
    bool TransitionCondition1455127641457::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1455127639286) ENABLED START*/
        return wm->game->checkSituation(msl::Situation::Start);
        /*PROTECTED REGION END*/

    }

    //State: BackroomDefence in Plan: TestBackroomDefence

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : situation == stop 
     *
     * Plans in State: 				
     *   - Plan - (Name): BackroomDefenceDefault, (PlanID): 1454507819086 
     *
     * Tasks: 
     *   - DefaultTask (1225112227903) (Entrypoint: 1455127495972)
     *
     * States:
     *   - Stop (1455127495971)
     *   - BackroomDefence (1455127584801)
     *
     * Vars:
     */
    bool TransitionCondition1455127612198::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1455127609026) ENABLED START*/
        return wm->game->checkSituation(msl::Situation::Stop);
        /*PROTECTED REGION END*/

    }

}
