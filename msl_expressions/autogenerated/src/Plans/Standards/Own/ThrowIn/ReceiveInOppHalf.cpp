using namespace std;
#include "Plans/Standards/Own/ThrowIn/ReceiveInOppHalf.h"

/*PROTECTED REGION ID(inccpp1462370340143) ENABLED START*/ //Add additional includes here
#include "robotmovement/RobotMovement.h"
#include "SystemConfig.h"
#include "engine/model/EntryPoint.h"
#include "engine/constraintmodul/ConstraintQuery.h"
#include "engine/RunningPlan.h"
#include "engine/Assignment.h"
#include "engine/model/Plan.h"
#include "SolverType.h"
/*PROTECTED REGION END*/
namespace alica
{
    /*PROTECTED REGION ID(staticVars1462370340143) ENABLED START*/ //initialise static variables here
    /*PROTECTED REGION END*/
    ReceiveInOppHalf::ReceiveInOppHalf() :
            DomainBehaviour("ReceiveInOppHalf")
    {
        /*PROTECTED REGION ID(con1462370340143) ENABLED START*/ //Add additional options here
        this->query = make_shared < alica::ConstraintQuery > (this->wm->getEngine());
        /*PROTECTED REGION END*/
    }
    ReceiveInOppHalf::~ReceiveInOppHalf()
    {
        /*PROTECTED REGION ID(dcon1462370340143) ENABLED START*/ //Add additional options here
        /*PROTECTED REGION END*/
    }
    void ReceiveInOppHalf::run(void* msg)
    {
        /*PROTECTED REGION ID(run1462370340143) ENABLED START*/ //Add additional options here
        auto ownPos = wm->rawSensorData->getOwnPositionVision();
        auto alloBallPose = wm->ball->getAlloBallPosition();
        if (!ownPos || !alloBallPose)
            return;

        double yCordOfReceiver = 0.0;
        if (alloBallPose->y < 0.0) // right side line
        {
            // place the receiver 1m outside the sideline
            yCordOfReceiver = -wm->field->getFieldWidth() / 2.0 - 1000.0;
        }
        else // left side line
        {
            // place the receiver 1m outside the sideline
            yCordOfReceiver = wm->field->getFieldWidth() / 2.0 + 1000.0;
        }

        double lowestX = wm->field->getFieldLength() / 2;
        auto opps = wm->robots->opponents.getOpponentsAlloClustered();
        for (auto opp : *opps)
        {
            double distToLine = geometry::distancePointToLineSegment(opp->x, opp->y, 2000, yCordOfReceiver,
                                                                     wm->field->getFieldLength() / 2 - 2000,
                                                                     yCordOfReceiver);
            if (distToLine > 3000)
            {
                continue;
            }

            if (lowestX > opp->x)
            {
                lowestX = opp->x;
            }
        }

        auto alloTarget = make_shared < geometry::CNPoint2D > (wm->field->getFieldLength() / 4, yCordOfReceiver);

        if (lowestX < wm->field->getFieldLength() / 2 - 2000)
        { // opponent close to pass line
            alloTarget->x = min(alloTarget->x, max(lowestX - 2000, 2000.0));
        }

        // Create additional points for path planning
        shared_ptr < vector<shared_ptr<geometry::CNPoint2D>>> additionalPoints = make_shared<
                vector<shared_ptr<geometry::CNPoint2D>>>();

        // add alloBall to path planning
        additionalPoints->push_back(alloBallPose);
        msl_actuator_msgs::MotionControl mc = msl::RobotMovement::moveToPointCarefully(alloTarget->alloToEgo(*ownPos),
                                                                                       alloBallPose->alloToEgo(*ownPos),
                                                                                       100.0, additionalPoints);

        send(mc);
        /*PROTECTED REGION END*/
    }
    void ReceiveInOppHalf::initialiseParameters()
    {
        /*PROTECTED REGION ID(initialiseParameters1462370340143) ENABLED START*/ //Add additional options here
        query->clearDomainVariables();
        query->addVariable(wm->getOwnId(), "x");
        query->addVariable(wm->getOwnId(), "y");
        result.clear();
        /*PROTECTED REGION END*/
    }
/*PROTECTED REGION ID(methods1462370340143) ENABLED START*/ //Add additional methods here
/*PROTECTED REGION END*/
} /* namespace alica */
