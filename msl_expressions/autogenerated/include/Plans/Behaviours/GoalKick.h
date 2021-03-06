#ifndef GoalKick_H_
#define GoalKick_H_

#include "DomainBehaviour.h"
/*PROTECTED REGION ID(inc1415205565589) ENABLED START*/ //Add additional includes here
#include "msl_robot/robotmovement/MovementQuery.h"
/*PROTECTED REGION END*/
namespace alica
{
    class GoalKick : public DomainBehaviour
    {
    public:
        GoalKick();
        virtual ~GoalKick();
        virtual void run(void* msg);
        /*PROTECTED REGION ID(pub1415205565589) ENABLED START*/ //Add additional public methods here
        /*PROTECTED REGION END*/
    protected:
        virtual void initialiseParameters();
        /*PROTECTED REGION ID(pro1415205565589) ENABLED START*/ //Add additional protected methods here
        /*PROTECTED REGION END*/
    private:
        /*PROTECTED REGION ID(prv1415205565589) ENABLED START*/ //Add additional private methods here
        shared_ptr<geometry::CNPoint2D> alloLeftAimPoint;
        shared_ptr<geometry::CNPoint2D> alloRightAimPoint;
        shared_ptr<geometry::CNPoint2D> alloMidAimPoint;
        shared_ptr<geometry::CNPoint2D> alloAimPoint;
        double angleTolerance;
        double minKickPower;
        double alignMaxVel;
        double alignToPointRapidMaxRotation;
        double lastRotErrorWithBallRapid;
        msl_actuator_msgs::MotionControl rapidAlignToPointWithBall(shared_ptr<geometry::CNPoint2D> egoAlignPoint,
                                                                   shared_ptr<geometry::CNPoint2D> egoBallPos,
                                                                   double angleTolerance, double ballAngleTolerance);
        /*PROTECTED REGION END*/};
} /* namespace alica */

#endif /* GoalKick_H_ */
