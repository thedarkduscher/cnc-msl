using namespace std;
#include "Plans/Attack/AdvancdeSimplePass.h"

/*PROTECTED REGION ID(inccpp1450176193656) ENABLED START*/ //Add additional includes here
#include "robotmovement/RobotMovement.h"
/*PROTECTED REGION END*/
namespace alica
{
    /*PROTECTED REGION ID(staticVars1450176193656) ENABLED START*/ //initialise static variables here
    /*PROTECTED REGION END*/
    AdvancdeSimplePass::AdvancdeSimplePass() :
            DomainBehaviour("AdvancdeSimplePass")
    {
        /*PROTECTED REGION ID(con1450176193656) ENABLED START*/ //Add additional options here
        maxVel = 2000;
        minDistToMate = 2000;
        gotMessage = false;
        sc = supplementary::SystemConfig::getInstance();
        teamMateTaskName = "";
        itcounter = 0;
        receiver = nullptr;
        shared_ptr < geometry::CNPosition > oldMatePos = nullptr;
        /*PROTECTED REGION END*/
    }
    AdvancdeSimplePass::~AdvancdeSimplePass()
    {
        /*PROTECTED REGION ID(dcon1450176193656) ENABLED START*/ //Add additional options here
        /*PROTECTED REGION END*/
    }
    void AdvancdeSimplePass::run(void* msg)
    {
        /*PROTECTED REGION ID(run1450176193656) ENABLED START*/ //Add additional options here
        if (itcounter < 3)
        {
            itcounter++;
            return; //give the ball a few milliseconds to leave the kicker
        }
        msl_actuator_msgs::MotionControl mc;
        shared_ptr < geometry::CNPoint2D > ballPos = wm->ball->getEgoBallPosition();
        shared_ptr < geometry::CNPosition > ownPos = wm->rawSensorData->getOwnPositionVision(); //Corrected;
        if (ballPos == nullptr)
        {
            return;
        }
        if (ownPos == nullptr)
        {

            mc = msl::RobotMovement::driveRandomly(1000);
            send(mc);
            return;
        }

        shared_ptr < geometry::CNPoint2D > egoMatePos = nullptr;
        shared_ptr < geometry::CNPosition > matePos = nullptr;

        if (receiver != nullptr)
        {
            shared_ptr<vector<int>> robots = robotsInEntryPoint(receiver); //make_shared<vector<int>>(); // = robotsInEntryPoint(receiver); // please fix this compile error, greatings Stopfer

            if (robots->size() > 0)
            {
                matePos = wm->robots->teammates.getTeamMatePosition(robots->at(0)); //SHWM.GetRobotDataByID(rob).PlayerPosition;
            }
            if (matePos != nullptr)
            {
                egoMatePos = matePos->getPoint()->alloToEgo(*ownPos);
                oldMatePos = matePos;
            }
            else
            {
                if (oldMatePos != nullptr)
                {
                    egoMatePos = oldMatePos->getPoint()->alloToEgo(*ownPos);
                }
            }
        }

        if (egoMatePos != nullptr)
        {
            mc = msl::RobotMovement::moveToFreeSpace(egoMatePos->egoToAllo(*ownPos), maxVel);
            send(mc);
        }
        /*PROTECTED REGION END*/
    }
    void AdvancdeSimplePass::initialiseParameters()
    {
        /*PROTECTED REGION ID(initialiseParameters1450176193656) ENABLED START*/ //Add additional options here
        maxVel = (*this->sc)["Behaviour"]->get<double>("Behaviour", "MaxSpeed", NULL);
        oldMatePos = nullptr;
        //planName = parameters["Plan"];
        receiver = getParentEntryPoint(teamMateTaskName);
        itcounter = 0;
        bool success = true;
        try
        {
            success &= getParameter("AttackTask", teamMateTaskName);
        }

        catch (exception& e)
        {
            cerr << "Could not cast the parameter properly" << endl;
        }
        if (!success)
        {
            cerr << "ASP: Parameter does not exist" << endl;
        }
        /*PROTECTED REGION END*/
    }
/*PROTECTED REGION ID(methods1450176193656) ENABLED START*/ //Add additional methods here
/*PROTECTED REGION END*/
} /* namespace alica */
