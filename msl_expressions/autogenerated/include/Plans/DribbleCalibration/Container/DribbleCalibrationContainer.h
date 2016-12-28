/*
 * DribbleCalibrationContainer.h
 *
 *  Created on: Jul 22, 2016
 *      Author: Carpe Noctem
 */

#ifndef CNC_MSL_MSL_EXPRESSIONS_AUTOGENERATED_INCLUDE_PLANS_DRIBBLECALIBRATION_CONTAINER_DRIBBLECALIBRATIONCONTAINER_H_
#define CNC_MSL_MSL_EXPRESSIONS_AUTOGENERATED_INCLUDE_PLANS_DRIBBLECALIBRATION_CONTAINER_DRIBBLECALIBRATIONCONTAINER_H_

#include "msl_actuator_msgs/MotionControl.h"
#include "msl_robot/robotmovement/MovementQuery.h"

//#define DEBUG_DC

using namespace msl;
namespace alica
{

    struct subsection
    {
        string name;
        double robotSpeed;
        double actuatorSpeed;
    };

    class DribbleCalibrationContainer
    {
    public:
        DribbleCalibrationContainer();
        virtual ~DribbleCalibrationContainer();

        enum Parm
        {
            DribbleForwardParm, DribbleBackwardParm, DribbleLeftParm, DribbleRightParm, RotateLeftParm, RotateRightPram, ErrParm
        };

        enum MethodParm
        {
            Move, AdaptParams, WriteConfigParam
        };

        MotionControl parmToMove(Parm parm, int trans);
        void parmToParmAdapt(Parm parm);

        //  movement stuff
        enum Movement
        {
            Forward, Backward, Left, Right, ForwardRight, ForwardLeft, BackwardRight, BackwardLeft
        };
        const char* movementToString[8] = {"Forward", "Backward", "Left", "Right", "Forward right", "Forward left",
                                            "Backward right", "Backward left"};
//      vector<char> movementToString[8] = {"Forward", "Backward", "Left", "Right", "Forward right", "Forward left", "Backward right", "Backward left"};
        msl_actuator_msgs::MotionControl getBall();
        msl_actuator_msgs::MotionControl move(Movement movement, int translation);
        bool checkObstacles(Movement movement, double distance);
        shared_ptr<geometry::CNPoint2D> calcNewAlignPoint(Movement curMove);
        double robotRadius;
        // used in checkObstacles and calcNewAlignPoint to decide where to drive if there is an obstacle in our way
//      shared_ptr<geometry::CNPoint2D> potentialAlignPoint;

// output variables
        bool changeDirFlag;

        // opticalFlow stuff
        double getAverageOpticalFlowXValue(shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>> queue);
    double getAverageOpticalFlowYValue(shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>> queue);

    bool queueFilled;
    bool fillOpticalFlowQueue(int queueSize, shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>> opQueue);

    double readConfigParameter(const char *path);
    void writeConfigParameters(vector<subsection> sections, const char* path);
private:
    msl::MSLWorldModel* wm;

    shared_ptr<msl::MovementQuery> query;

    double defaultDistance;
    double distToObs;

    enum OPValue
    {
        XValue, YValue, QOSValue
    };

    MotionControl callBehavour(MethodParm mParm, Parm parm, int trans = 0);

    // movement and obstacle avoiding stuff
                bool changeDirections;
                bool rotateAroundTheBall;
                double angleTolerance;
                shared_ptr<geometry::CNPoint2D> alloAlignPoint;

                double getAverageOpticalFlowValue(OPValue value, shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>> queue);
                shared_ptr<geometry::CNPoint2D> getEgoDestinationPoint(Movement movement, double distance);

                bool checkFieldLines(shared_ptr<geometry::CNPoint2D> egoDest);
                MotionControl setZero(MotionControl mc);
                MotionControl setNaN(MotionControl mc);
                Movement getNewDirection(int curDir, vector<Movement> movement, int next);
                void readOwnConfigParameter();
            };

        }
        /* namespace alica */

#endif /* CNC_MSL_MSL_EXPRESSIONS_AUTOGENERATED_INCLUDE_PLANS_DRIBBLECALIBRATION_CONTAINER_DRIBBLECALIBRATIONCONTAINER_H_ */
