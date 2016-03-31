#include "Plans/Goalie/Test/GoalieDefault1447254438614.h"
using namespace alica;
/*PROTECTED REGION ID(eph1447254438614) ENABLED START*/ //Add additional using directives here
#include "robotmovement/RobotMovement.h"
#include <cmath>
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:GoalieDefault

    /* generated comment
     
     Task: Keeper  -> EntryPoint-ID: 1447254438616

     */
    shared_ptr<UtilityFunction> UtilityFunction1447254438614::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1447254438614) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

    //State: DriveToGoal in Plan: GoalieDefault

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : situation == WatchBall 
     *
     * Plans in State: 				
     *   - Plan - (Name): DriveToGoalDefault, (PlanID): 1447863442558 
     *
     * Tasks: 
     *   - Keeper (1221754402444) (Entrypoint: 1447254438616)
     *
     * States:
     *   - DriveToGoal (1447254438615)
     *   - WatchBall (1447255061404)
     *   - DriveToBall (1447256447585)
     *   - Pass (1447256481745)
     *
     * Vars:
     */
    bool TransitionCondition1447255447830::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1447255446546) ENABLED START*/
        if (rp->anyChildrenStatus(PlanStatus::Success))
        {
            cout << "--- DriveToGoal finished ---" << endl;
            return true;
        }
        else
            return false;
        return rp->anyChildrenStatus(PlanStatus::Success);
        /*PROTECTED REGION END*/

    }

    //State: WatchBall in Plan: GoalieDefault

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : situation == BallInsideGoalArea && BallNotMoving 
     *
     * Plans in State: 				
     *   - Plan - (Name): GoalieExtensionDefault, (PlanID): 1459249287791 				
     *   - Plan - (Name): WatchBallDefault, (PlanID): 1447863472667 
     *
     * Tasks: 
     *   - Keeper (1221754402444) (Entrypoint: 1447254438616)
     *
     * States:
     *   - DriveToGoal (1447254438615)
     *   - WatchBall (1447255061404)
     *   - DriveToBall (1447256447585)
     *   - Pass (1447256481745)
     *
     * Vars:
     */
    bool TransitionCondition1447259463769::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1447259462162) ENABLED START*/
        int condition, condition1, condition2, condition3 = 0;
        shared_ptr < geometry::CNPosition > me = wm->rawSensorData.getOwnPositionVision();
        shared_ptr < geometry::CNVelocity2D > egoBallVel = wm->ball.getEgoBallVelocity();
        shared_ptr < geometry::CNPoint2D > alloGoalMid;
        shared_ptr < geometry::CNPoint2D > alloBallPos = wm->ball.getAlloBallPosition();

        if (me != nullptr && alloBallPos != nullptr && egoBallVel != nullptr)
        {
            static const int SIMULATING = 1; // simulating 1, real life -1
            std::shared_ptr < geometry::CNPoint2D > uLGoalArea;

            if (SIMULATING > 0)
            {
                uLGoalArea = MSLFootballField::posLROppGoalArea();
                alloGoalMid = MSLFootballField::posOppGoalMid();
            }
            else if (SIMULATING < 0)
            {
                uLGoalArea = MSLFootballField::posULOwnGoalArea();
                alloGoalMid = MSLFootballField::posOwnGoalMid();
            }
            double uLX = abs(uLGoalArea->x);
            double uLY = abs(uLGoalArea->y);
            double ballX = abs(wm->ball.getAlloBallPosition()->x);
            double ballY = abs(wm->ball.getAlloBallPosition()->y);
            double ballVelX = abs(egoBallVel->x);
            double ballVelY = abs(egoBallVel->y);

            condition1 = ballVelX <= 50 && ballVelY <= 50;
            condition2 = ballY < uLY;
            condition3 = ballX > uLX && ballX < abs(alloGoalMid->x);

            /*cout << "cond1: " << condition1 << endl;
             cout << "cond2: " << condition2 << endl;
             cout << "cond3: " << condition3 << endl;
             cout << endl;*/

            condition = condition1 && condition2 && condition3;
        }

        //if (condition > 0)
        if (false)
        {
            /*cout << egoBallVel->x << ", " << egoBallVel->y << endl;
             cout << "ballPos " << alloBallPos->toString() << endl;*/
            cout << "--- DriveToBallstarted, ball is inside goalArea ---" << endl;
            return true;
        }
        else
        {
            return false;
        }
//return output;
        /*PROTECTED REGION END*/

    }

    //State: DriveToBall in Plan: GoalieDefault

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : situation == ReachedBall && BallInsideGoalArea && BallNotMoving 
     *
     * Plans in State: 				
     *   - Plan - (Name): DriveToBallDefault, (PlanID): 1447863503279 
     *
     * Tasks: 
     *   - Keeper (1221754402444) (Entrypoint: 1447254438616)
     *
     * States:
     *   - DriveToGoal (1447254438615)
     *   - WatchBall (1447255061404)
     *   - DriveToBall (1447256447585)
     *   - Pass (1447256481745)
     *
     * Vars:
     */
    bool TransitionCondition1447256488686::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1447256487026) ENABLED START*/
        /*double distance = me->distanceTo(alloTarget);
         cout << "\nRemaining distance to ball: " << distance << endl;

         auto obstacles = wm->obstacles.getAlloObstaclePoints();
         if (obstacles != nullptr)
         {
         cout << obstacles->size() << endl;
         }

         // todo: drive parallel to ball until me->y == ball->y (alignPoint = parallel to right/left field border
         // then alloAlignpoint=alloBall
         if (distance <= goalieHalfSize)
         {
         this->success = true;
         cout << "### DriveToBall ###\n" << endl;
         return;
         }*/
        return false;
        /*PROTECTED REGION END*/

    }

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : situation == BallMoving || BallOutSideGoalArea 
     *
     * Plans in State: 				
     *   - Plan - (Name): DriveToBallDefault, (PlanID): 1447863503279 
     *
     * Tasks: 
     *   - Keeper (1221754402444) (Entrypoint: 1447254438616)
     *
     * States:
     *   - DriveToGoal (1447254438615)
     *   - WatchBall (1447255061404)
     *   - DriveToBall (1447256447585)
     *   - Pass (1447256481745)
     *
     * Vars:
     */
    bool TransitionCondition1457943658078::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1457943655376) ENABLED START*/
        int condition, condition1, condition2, condition3 = 0;
        shared_ptr < geometry::CNPosition > me = wm->rawSensorData.getOwnPositionVision();
        shared_ptr < geometry::CNVelocity2D > egoBallVel = wm->ball.getEgoBallVelocity();
        shared_ptr < geometry::CNPoint2D > alloGoalMid;
        shared_ptr < geometry::CNPoint2D > alloBallPos = wm->ball.getAlloBallPosition();

        if (me != nullptr && alloBallPos != nullptr && egoBallVel != nullptr)
        {
            static const int SIMULATING = 1; // simulating 1, real life -1
            std::shared_ptr < geometry::CNPoint2D > uLGoalArea;

            if (SIMULATING > 0)
            {
                uLGoalArea = MSLFootballField::posLROppGoalArea();
                alloGoalMid = MSLFootballField::posOppGoalMid();
            }
            else if (SIMULATING < 0)
            {
                uLGoalArea = MSLFootballField::posULOwnGoalArea();
                alloGoalMid = MSLFootballField::posOwnGoalMid();
            }

            double uLX = abs(uLGoalArea->x);
            double uLY = abs(uLGoalArea->y);
            double ballX = abs(wm->ball.getAlloBallPosition()->x);
            double ballY = abs(wm->ball.getAlloBallPosition()->y);
            double ballVelX = abs(egoBallVel->x);
            double ballVelY = abs(egoBallVel->y);

            condition1 = ballVelX > 1000 || ballVelY > 1000;
            condition2 = ballX <= uLX || ballX >= abs(alloGoalMid->x);
            condition3 = ballY >= uLY;

            condition = condition1 || condition2 || condition3;
        }
        if (condition > 0)
        {
            /*cout << "dBallStopped " << endl;
             cout << "cond1: " << condition1 << endl;
             cout << "cond2: " << condition2 << endl;
             cout << "cond3: " << condition3 << endl;
             cout << egoBallVel->x << ", " << egoBallVel->y << endl;
             cout << "ballPos " << alloBallPos->toString() << endl;*/
            cout << "--- DriveToBallstopped, ball is outside goalArea or moving ---" << endl;
            return true;
        }
        else
            return false;
        /*PROTECTED REGION END*/

    }

    //State: Pass in Plan: GoalieDefault

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : situation == BallMoving || BallOutsideGoalArea 
     *
     * Plans in State: 				
     *   - Plan - (Name): KickToDirectionDefault, (PlanID): 1447863487000 
     *
     * Tasks: 
     *   - Keeper (1221754402444) (Entrypoint: 1447254438616)
     *
     * States:
     *   - DriveToGoal (1447254438615)
     *   - WatchBall (1447255061404)
     *   - DriveToBall (1447256447585)
     *   - Pass (1447256481745)
     *
     * Vars:
     */
    bool TransitionCondition1447256495415::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1447256488872) ENABLED START*/
        return false;
        /*PROTECTED REGION END*/

    }

}
