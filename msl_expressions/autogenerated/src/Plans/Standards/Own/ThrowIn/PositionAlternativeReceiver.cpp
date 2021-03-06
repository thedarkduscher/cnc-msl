using namespace std;
#include "Plans/Standards/Own/ThrowIn/PositionAlternativeReceiver.h"

/*PROTECTED REGION ID(inccpp1462978634990) ENABLED START*/ //Add additional includes here
#include "msl_robot/robotmovement/RobotMovement.h"
#include "SystemConfig.h"
#include "engine/model/EntryPoint.h"
#include "engine/RunningPlan.h"
#include "engine/Assignment.h"
#include "engine/model/Plan.h"
#include <RawSensorData.h>
#include <MSLWorldModel.h>
#include <Ball.h>
/*PROTECTED REGION END*/
namespace alica
{
    /*PROTECTED REGION ID(staticVars1462978634990) ENABLED START*/ //initialise static variables here
    /*PROTECTED REGION END*/
    PositionAlternativeReceiver::PositionAlternativeReceiver() :
            DomainBehaviour("PositionAlternativeReceiver")
    {
        /*PROTECTED REGION ID(con1462978634990) ENABLED START*/ //Add additional options here
        query = make_shared<msl::MovementQuery>();
        /*PROTECTED REGION END*/
    }
    PositionAlternativeReceiver::~PositionAlternativeReceiver()
    {
        /*PROTECTED REGION ID(dcon1462978634990) ENABLED START*/ //Add additional options here
        /*PROTECTED REGION END*/
    }
    void PositionAlternativeReceiver::run(void* msg)
    {
        /*PROTECTED REGION ID(run1462978634990) ENABLED START*/ //Add additional options here
        msl::RobotMovement rm;
        shared_ptr < geometry::CNPosition > ownPos = wm->rawSensorData->getOwnPositionVision();
        shared_ptr < geometry::CNPoint2D > egoBallPos = wm->ball->getEgoBallPosition();
        if (ownPos == nullptr || egoBallPos == nullptr)
        {
            return;
        }
        shared_ptr < geometry::CNPoint2D > alloBall = egoBallPos->egoToAllo(*ownPos);
        // Create additional points for path planning
        shared_ptr < vector<shared_ptr<geometry::CNPoint2D>>> additionalPoints = make_shared<
                vector<shared_ptr<geometry::CNPoint2D>>>();
        // add alloBall to path planning
        additionalPoints->push_back(alloBall);

        msl_actuator_msgs::MotionControl mc;
        shared_ptr < geometry::CNPoint2D > alloTarget = make_shared<geometry::CNPoint2D>();
        shared_ptr < geometry::CNPoint2D > egoTarget = nullptr;

        if (alloBall->y < 0)
        {
            alloTarget->y = alloBall->y + 2300.0;
        }
        else
        {
            alloTarget->y = alloBall->y - 2300.0;
        }

        alloTarget->x = alloBall->x;

        egoTarget = alloTarget->alloToEgo(*ownPos);

//        mc = msl::RobotMovement::moveToPointCarefully(egoTarget, egoBallPos, 0, additionalPoints);
        query->egoDestinationPoint = egoTarget;
        query->egoAlignPoint = egoBallPos;
        query->additionalPoints = additionalPoints;
        mc = rm.moveToPoint(query);

        if (!std::isnan(mc.motion.translation))
        {
            send(mc);
        }
        else
        {
            cout << "Motion command is NaN!" << endl;
        }

        /*PROTECTED REGION END*/
    }
    void PositionAlternativeReceiver::initialiseParameters()
    {
        /*PROTECTED REGION ID(initialiseParameters1462978634990) ENABLED START*/ //Add additional options here
        /*PROTECTED REGION END*/
    }
/*PROTECTED REGION ID(methods1462978634990) ENABLED START*/ //Add additional methods here
/*PROTECTED REGION END*/
} /* namespace alica */
