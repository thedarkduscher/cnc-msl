using namespace std;
#include "Plans/GenericBehaviours/CheckGoalKick.h"

/*PROTECTED REGION ID(inccpp1449076008755) ENABLED START*/ //Add additional includes here
#include <GeometryCalculator.h>
#include <math.h>
#include "engine/RunningPlan.h"
#include "engine/AlicaEngine.h"
#include <msl_helper_msgs/DebugMsg.h>
#include <msl_helper_msgs/DebugPoint.h>

#include <Rules.h>
/*PROTECTED REGION END*/
namespace alica
{
    /*PROTECTED REGION ID(staticVars1449076008755) ENABLED START*/ //initialise static variables here
    /*PROTECTED REGION END*/
    CheckGoalKick::CheckGoalKick() :
            DomainBehaviour("CheckGoalKick")
    {
        /*PROTECTED REGION ID(con1449076008755) ENABLED START*/ //Add additional options here
        /*PROTECTED REGION END*/
    }
    CheckGoalKick::~CheckGoalKick()
    {
        /*PROTECTED REGION ID(dcon1449076008755) ENABLED START*/ //Add additional options here
        /*PROTECTED REGION END*/
    }
    void CheckGoalKick::run(void* msg)
    {
        /*PROTECTED REGION ID(run1449076008755) ENABLED START*/ //Add additional options here
        // check if it is ok to score a goal
        cout << "==========================================================================" << endl;
        if (false == this->wm->game.isMayScore())
        {
            cout << "may score: false" << endl;
            return;
        }
        // get sensor data from WM and check validity
        ownPos = wm->rawSensorData.getOwnPositionVision();
        egoBallPos = wm->ball.getEgoBallPosition();

//        std::cout << "OwnPos:     " << ownPos << std::endl;
//        std::cout << "EgoBallPos: " << egoBallPos << std::endl;
//        std::cout << "HaveBall: " << (wm->ball.haveBall() ? "true" : "false") << std::endl;


        if (this->usePrediction)
        { // use predicted own position
                auto pred = this->wm->prediction.angleAndPosition(this->predictionTime);

                if (pred != nullptr)
                {
                        auto predPos = pred->first;
                        // move ego ball based on predicted own position
                        this->egoBallPos = this->egoBallPos + (predPos - ownPos);
                        this->egoBallPos = this->egoBallPos->rotate(geometry::deltaAngle(ownPos->theta, predPos->theta));
                        this->ownPos = predPos;
                }
        }

        this->wm->prediction.monitoring();

        if (ownPos == nullptr || egoBallPos == nullptr || !wm->ball.haveBall())
        {
            return;
        }



        shared_ptr<geometry::CNPoint2D> hitPoint = this->computeHitPoint(ownPos->x, ownPos->y, ownPos->theta);

        if (false == hitPoint)
        {
            cout << "hits the goal: false" << endl;
            return;
        }
        else
        {
            cout << "hits the goal: x: " << hitPoint->x << ", y: " << hitPoint->y << endl;
        }

        // Sending debug message for visualization
        msl_helper_msgs::DebugMsg debugMsg;
        debugMsg.topic = "CheckGoalKick";
        debugMsg.senderID = this->getOwnId();
        debugMsg.validFor = 2000000000;

        msl_helper_msgs::DebugPoint point;

        point.radius = 0.12;
        point.point.x = hitPoint->x;
        point.point.y = hitPoint->y;
        point.red = 255;
        point.green = 0;
        point.blue = 255;

        debugMsg.points.push_back(point);
        this->send(debugMsg);
        // ---------------------------------------

        if (!this->checkGoalKeeper(hitPoint))
        { // we hit the goal keeper
            cout << "check goal keeper: false" << endl;
            return;
        }
        else
        {
            cout << "check goal keeper: true" << endl;
        }

        double kickPowerObs = 0;
        if (!this->checkShootPossibility(hitPoint, kickPowerObs))
        { // we cannot shoot over the closest obstacles
            cout << "check shoot possibility: false" << endl;
            return;
        }
        else
        {
            cout << "check shoot possibility: true" << endl;
            cout << "kick power obs: " << kickPowerObs << endl;
        }

        double kickPowerGoal = this->getKickPower(hitPoint);
        cout << "dist ball to hit point: " << cout_distBall2HitPoint << endl;
        cout << "goal power: " << kickPowerGoal << " obs power: " << kickPowerObs << endl;

        // no closest obstacle, FIRE
        if (kickPowerObs == -2)
        {
            cout << "kick power: " << kickPowerGoal << endl;
            kick(kickPowerGoal);
            return;
        }

        if (kickPowerGoal < kickPowerObs)
        {
            cout << "goal power < obs power" << endl;
            return;
        }
        else
        {
            double kickPower = (kickPowerGoal + kickPowerObs) / 2;
            cout << "kick power: " << kickPower << endl;
            kick(kickPower);
        }
        /*PROTECTED REGION END*/
    }
    void CheckGoalKick::initialiseParameters()
    {
        /*PROTECTED REGION ID(initialiseParameters1449076008755) ENABLED START*/ //Add additional options here
        field = msl::MSLFootballField::getInstance();
        auto rules = msl::Rules::getInstance();
        // space required to miss a robot (no offset because robots are pyramids)
        minOppYDist = rules->getBallRadius() + rules->getRobotRadius();

        readConfigParameters();
        /*PROTECTED REGION END*/
    }
    /*PROTECTED REGION ID(methods1449076008755) ENABLED START*/ //Add additional methods here
    void CheckGoalKick::readConfigParameters()
    {
        supplementary::SystemConfig* sc = supplementary::SystemConfig::getInstance();
        minObsDistGoal = (*sc)["GoalKick"]->get<double>("GoalKick.Default.minObsDistGoal", NULL);
        minOwnDistGoal = (*sc)["GoalKick"]->get<double>("GoalKick.Default.minOwnDistGoal", NULL);
        minKickPower = (*sc)["GoalKick"]->get<double>("GoalKick.Default.minKickPower", NULL);
        keeperDistGoal = (*sc)["GoalKick"]->get<double>("GoalKick.Default.keeperDistGoal", NULL);
        minKeeperDistBallTrajectory = (*sc)["GoalKick"]->get<double>("GoalKick.Default.minKeeperDistBallTrajectory", NULL);

        usePrediction = (*sc)["GoalKick"]->get<bool>("GoalKick.Prediction.use", NULL);
        predictionTime = (*sc)["GoalKick"]->get<int>("GoalKick.Prediction.time", NULL);

        // is necessary to calculate the minimum distance to obstacle so that it is possible to shoot a goal
        // close to goal --> distance to robot is higher
        closeGoalDist = (*sc)["GoalKick"]->get<double>("GoalKick.OwnDistObs.closeGoalDist", NULL);
        // far from goal --> distance to robot can be smaller
        farGoalDist = (*sc)["GoalKick"]->get<double>("GoalKick.OwnDistObs.farGoalDist", NULL);

    }

    /**
     * Calculates, whether a robot with the given position is hitting the goal.
     */
    shared_ptr<geometry::CNPoint2D> CheckGoalKick::computeHitPoint(double posX, double posY, double alloAngle)
    {
        double xDist2OppGoalline = this->field->FieldLength / 2 - posX;

        // normalize the position angle
        alloAngle = geometry::normalizeAngle(alloAngle);

        // get the kicker angle from position angle (+/- M_PI)
        if (alloAngle < 0)
        {
            alloAngle += M_PI;
        }
        else
        {
            alloAngle -= M_PI;
        }

        if (alloAngle > M_PI / 2 || alloAngle < -M_PI / 2)
        {
            // you are aiming away from the opponent goal line
            return shared_ptr<geometry::CNPoint2D>();
        }

        double yHitGoalline = posY + xDist2OppGoalline * tan(alloAngle);
        // reduce goalPost->y by (ball radius + safety margin)
        if (abs(yHitGoalline)
                < (this->field->posLeftOppGoalPost()->y - msl::Rules::getInstance()->getBallRadius() - 78))
        {
            // you will hit the goal
            return make_shared < geometry::CNPoint2D > (this->field->FieldLength / 2, yHitGoalline);
        }

        return shared_ptr<geometry::CNPoint2D>();
    }

    /*
     * checks if there is an obstacle between robot and goal.
     *
     * @return true if it is possible to shoot at the enemy goal
     */
    bool CheckGoalKick::checkShootPossibility(shared_ptr<geometry::CNPoint2D> hitPoint, double& kickPower)
    {
        auto obstacles = wm->obstacles.getAlloObstaclePoints();
        if (obstacles == nullptr || obstacles->size() == 0)
        {
            kickPower = -2;
            return true;
        }

        double closestObsDist = 1000000;
        shared_ptr < geometry::CNPoint2D > closestObs;

        for (auto obs : *obstacles)
        {
            if (obs->x < ownPos->x)
            {
                continue; // obs is behind us
            }

            if (abs(obs->alloToEgo(*ownPos)->y) > minOppYDist)
            {
                continue;
            }

            if (obs->distanceTo(ownPos) < closestObsDist)
            {
                closestObs = obs;
                closestObsDist = obs->distanceTo(ownPos);
            }
        }

        if (!closestObs)
        {
            kickPower = -2;
            return true;
        }

        auto alloBallPos = egoBallPos->egoToAllo(*this->ownPos);
        double dist2Obs = alloBallPos->distanceTo(closestObs);
        cout << "Evil Obs: X:" << closestObs->x << ", Y:" << closestObs->y << ", Dist:" << dist2Obs << endl;
        kickPower = this->wm->kicker.getKickPowerForLobShot(dist2Obs, 1100.0);
        if (kickPower == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    double CheckGoalKick::getKickPower(shared_ptr<geometry::CNPoint2D> hitPoint)
    {
        auto alloBallPos = egoBallPos->egoToAllo(*this->ownPos);
        double dist2HitPoint = alloBallPos->distanceTo(hitPoint);
        cout_distBall2HitPoint = dist2HitPoint;

        if (dist2HitPoint < 4500)
        {
            return this->minKickPower;
        }
        else
        {
            return this->wm->kicker.getKickPowerForLobShot(dist2HitPoint, 500.0, 100.0);
        }
    }

    void CheckGoalKick::kick(double kickpower)
    {
        msl_actuator_msgs::KickControl kc;
        kc.enabled = true;
        kc.power = kickpower;
        send(kc);
    }

    /**
     *
     * @return true if no opponent is on/near our hitPoint
     */
    bool CheckGoalKick::checkGoalKeeper(shared_ptr<geometry::CNPoint2D> hitPoint)
    {
        auto opps = wm->robots.opponents.getOpponentsAlloClustered();
        if (opps == nullptr || opps->size() == 0)
        {
            return true;
        }

        for (auto opp : *opps)
        {
            if (opp->distanceTo(hitPoint) < keeperDistGoal)
            {
                std::cout << "Position of evil goalkeeper " << opp->x << ", " << opp->y << std::endl;
//            	double deltaAngleGoalie2HitPoint = opp->angleToPoint(hitPoint);
//            	double stuff = tan(deltaAngleGoalie2HitPoint) * opp->distanceTo(ownPos);
                auto egoGoalKeeper = opp->alloToEgo(*this->ownPos);

                // goalkeeper on same level as attacker, handled by checkShootPossibility
                if (egoGoalKeeper->x == 0)
                    continue;

                double keeperDisBallTrajectory = abs(egoGoalKeeper->y / egoGoalKeeper->x) * egoGoalKeeper->length();

                std::cout << "keeperDisBallTrajectory " << keeperDisBallTrajectory << std::endl;

                if (keeperDisBallTrajectory < minKeeperDistBallTrajectory)
                {
                    return false;
                }
            }
        }
        return true;
    }
/*PROTECTED REGION END*/
} /* namespace alica */
