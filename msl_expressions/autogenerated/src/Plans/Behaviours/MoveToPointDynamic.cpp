using namespace std;
#include "Plans/Behaviours/MoveToPointDynamic.h"

/*PROTECTED REGION ID(inccpp1456997073100) ENABLED START*/ //Add additional includes here
#include "msl_robot/robotmovement/RobotMovement.h"
#include "SolverType.h"
#include <RawSensorData.h>
#include <Ball.h>
#include <MSLWorldModel.h>
/*PROTECTED REGION END*/
namespace alica
{
    /*PROTECTED REGION ID(staticVars1456997073100) ENABLED START*/ //initialise static variables here
    /*PROTECTED REGION END*/
    MoveToPointDynamic::MoveToPointDynamic() :
            DomainBehaviour("MoveToPointDynamic")
    {
        /*PROTECTED REGION ID(con1456997073100) ENABLED START*/ //Add additional options here
        query = make_shared < Query > (wm->getEngine());
        maxVel = 0;
        avoidBall = false;
        result = vector<double>();
        lastResult = 0;
        movQuery = make_shared<msl::MovementQuery>();
        readConfigParameters();
        /*PROTECTED REGION END*/
    }
    MoveToPointDynamic::~MoveToPointDynamic()
    {
        /*PROTECTED REGION ID(dcon1456997073100) ENABLED START*/ //Add additional options here
        /*PROTECTED REGION END*/
    }
    void MoveToPointDynamic::run(void* msg)
    {
        /*PROTECTED REGION ID(run1456997073100) ENABLED START*/ //Add additional options here
        msl::RobotMovement rm;
        msl_actuator_msgs::MotionControl mc;
        shared_ptr < geometry::CNPosition > ownPos = wm->rawSensorData->getOwnPositionVision();
        shared_ptr < geometry::CNPoint2D > ballPos = wm->ball->getEgoBallPosition();
        if (ownPos == nullptr)
        {
            return;
        }
        if (result.size() == 0 || lastResult + 300000000 < wm->getTime())
        {
            bool ret = query->getSolution(SolverType::GRADIENTSOLVER, runningPlan, result);
            lastResult = wm->getTime();
        }

        if (result.size() > 0)
        {
            shared_ptr < geometry::CNPoint2D > driveTo = make_shared < geometry::CNPoint2D
                    > (result[0], result[1])->alloToEgo(*ownPos);
            if (avoidBall)
            {
                // replace method with new moveToPoint method
//              mc = msl::RobotMovement::placeRobotCareBall(driveTo, ballPos, maxVel);
                movQuery->egoDestinationPoint = driveTo;
                movQuery->egoAlignPoint = ballPos;
                mc = rm.moveToPoint(movQuery);
                if (driveTo->length() < 100)
                {
                    mc.motion.translation = 0;
                }
            }
            else
            {
                // replaced with new moveToPoint method
//                mc = msl::RobotMovement::placeRobotAggressive(driveTo, ballPos, maxVel);
                movQuery->egoDestinationPoint = driveTo;
                movQuery->egoAlignPoint = ballPos;
                movQuery->fast = true;
                mc = rm.moveToPoint(movQuery);
            }
            if (driveTo->length() < 150)
            {
                this->setSuccess(true);
            }
            else
            {
                this->setSuccess(false);
            }

        }
        else
        {
            cout << "no solution found!!!" << endl;
            return;
        }
        send(mc);
        /*PROTECTED REGION END*/
    }
    void MoveToPointDynamic::initialiseParameters()
    {
        /*PROTECTED REGION ID(initialiseParameters1456997073100) ENABLED START*/ //Add additional options here
        query->clearStaticVariables();
        query->addStaticVariable(getVariablesByName("X"));
        query->addStaticVariable(getVariablesByName("Y"));
        result.clear();
        bool success = true;
        string tmp = "";
        try
        {
            success &= getParameter("AvoidBall", tmp);
            if (success)
            {
                std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
                istringstream(tmp) >> std::boolalpha >> avoidBall;
            }
        }
        catch (exception& e)
        {
            cerr << "Could not cast the parameter properly" << endl;
        }
        if (!success)
        {
            cerr << "M2PD: Parameter 'AvoidBall' does not exist" << endl;
        }
        /*PROTECTED REGION END*/
    }
    /*PROTECTED REGION ID(methods1456997073100) ENABLED START*/ //Add additional methods here
    void MoveToPointDynamic::readConfigParameters()
    {
        supplementary::SystemConfig* sys = supplementary::SystemConfig::getInstance();
        maxVel = (*sys)["Behaviour"]->get<double>("Behaviour.MaxSpeed", NULL);
    }
/*PROTECTED REGION END*/
} /* namespace alica */
