#include "Plans/TestPlans/GoalieMotionTuning/DriveToPost1464189637940.h"
using namespace alica;
/*PROTECTED REGION ID(eph1464189637940) ENABLED START*/ //Add additional using directives here
#include <MSLWorldModel.h>
#include <Game.h>
#include "RawSensorData.h"
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:DriveToPost

    /* generated comment

     Task: Keeper  -> EntryPoint-ID: 1464189637942

     */
    shared_ptr<UtilityFunction> UtilityFunction1464189637940::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1464189637940) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

    //State: Stop in Plan: DriveToPost

    /*
     *
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : situation == start
     *
     * Plans in State:
     *   - Plan - (Name): StopDefault, (PlanID): 1413992626194
     *
     * Tasks:
     *   - Keeper (1221754402444) (Entrypoint: 1464189637942)
     *
     * States:
     *   - Stop (1464189637941)
     *   - DriveToGoal (1464189715889)
     *   - DriveToPost (1464189729245)
     *
     * Vars:
     */
    bool TransitionCondition1464189727040::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1464189725286) ENABLED START*/
        return wm->game->checkSituation(msl::Situation::Start);
        /*PROTECTED REGION END*/

    }

    //State: DriveToGoal in Plan: DriveToPost

    /*
     *
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : situation == anychild success
     *
     * Plans in State:
     *   - Plan - (Name): DriveToGoalDefault, (PlanID): 1447863442558
     *
     * Tasks:
     *   - Keeper (1221754402444) (Entrypoint: 1464189637942)
     *
     * States:
     *   - Stop (1464189637941)
     *   - DriveToGoal (1464189715889)
     *   - DriveToPost (1464189729245)
     *
     * Vars:
     */
    bool TransitionCondition1464189738685::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1464189737293) ENABLED START*/
        if (rp->anyChildrenStatus(PlanStatus::Success))
        {
            cout << "[DriveToPost] --- DriveToGoal finished ---" << endl;
            return true;
        }
        else
            return false;
        /*PROTECTED REGION END*/

    }

    //State: DriveToPost in Plan: DriveToPost

    /*
     *
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : situation == stop
     *
     * Plans in State:
     *   - Plan - (Name): DriveToPostDefault, (PlanID): 1464189840525
     *
     * Tasks:
     *   - Keeper (1221754402444) (Entrypoint: 1464189637942)
     *
     * States:
     *   - Stop (1464189637941)
     *   - DriveToGoal (1464189715889)
     *   - DriveToPost (1464189729245)
     *
     * Vars:
     */
    bool TransitionCondition1464979938671::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1464979937235) ENABLED START*/
        bool stop = wm->game->checkSituation(msl::Situation::Stop);
        if (stop == true)
        {
            cout << "[DriveToPost] --- situation == stop! ---" << endl;
        }
        return stop;
        /*PROTECTED REGION END*/

    }

}
