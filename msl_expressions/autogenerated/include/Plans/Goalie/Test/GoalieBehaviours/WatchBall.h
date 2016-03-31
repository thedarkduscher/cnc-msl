#ifndef WatchBall_H_
#define WatchBall_H_

#include "DomainBehaviour.h"
/*PROTECTED REGION ID(inc1447863466691) ENABLED START*/ //Add additional includes here
#include "container/CNPoint2D.h"
#include "container/CNPosition.h"
#include <string>

using namespace msl;
/*PROTECTED REGION END*/
namespace alica
{
    class WatchBall : public DomainBehaviour
    {
    public:
        WatchBall();
        virtual ~WatchBall();
        virtual void run(void* msg);
        /*PROTECTED REGION ID(pub1447863466691) ENABLED START*/ //Add additional public methods here
        /*PROTECTED REGION END*/
    protected:
        virtual void initialiseParameters();
        /*PROTECTED REGION ID(pro1447863466691) ENABLED START*/ //Add additional protected methods here
        static const int SNAP_DIST = 100;
        shared_ptr<geometry::CNPoint2D> alloFieldCntr = MSLFootballField::posCenterMarker();
        shared_ptr<geometry::CNPoint2D> alloAlignPt = alloFieldCntr;
        int simulating;
        int maxVariance;
        int goalieSize;
        int nrOfPositions;
        /*PROTECTED REGION END*/
    private:
        /*PROTECTED REGION ID(prv1447863466691) ENABLED START*/ //Add additional private methods here
        msl_actuator_msgs::MotionControl mc;
        shared_ptr<geometry::CNPosition> me;
        double fitTargetY(double targetY);
        void watchBall();
        int modRingBuffer(int k, int bufferSize);
        shared_ptr<geometry::CNPoint2D> calcGoalImpactY(std::vector<shared_ptr<geometry::CNPoint2D>>& ballPositions);
        shared_ptr<geometry::CNPoint2D> alloGoalLeft;
        shared_ptr<geometry::CNPoint2D> alloGoalRight;
        shared_ptr<geometry::CNPoint2D> alloGoalMid;
        shared_ptr<geometry::CNPoint2D> prevTarget;
        /*PROTECTED REGION END*/};
} /* namespace alica */

#endif /* WatchBall_H_ */
