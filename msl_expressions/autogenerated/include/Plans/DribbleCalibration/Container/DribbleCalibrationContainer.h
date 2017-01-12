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
#include <Plans/DribbleCalibration/Behaviours/Calibrations/DribbleForward.h>
#include <Plans/DribbleCalibration/Behaviours/Calibrations/DribbleBackward.h>
#include <Plans/DribbleCalibration/Behaviours/Interfaces/ICalibration.h>

#define DEBUG_DC

using namespace msl;
namespace alica
{
	class DribbleCalibrationContainer
	{
	public:
		DribbleCalibrationContainer();
		virtual ~DribbleCalibrationContainer();

		enum Param
		{
			DribbleForwardParm, DribbleBackwardParm, DribbleLeftParm, DribbleRightParm, RotateLeftParm, RotateRightPram,
			ErrParm
		};

		enum MethodParam
		{
			Move, AdaptParams, WriteConfigParam, ResetParams
		};

		MotionControl paramToMove(Param param, int trans);
		void adaptParam(Param param);
		void writeConfigParameres(Param parm);
		void resetParameters(Param parm);

		// opticalFlow stuff
		double getAverageOpticalFlowXValue(shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>> queue);
		double getAverageOpticalFlowYValue(shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>> queue);

		bool queueFilled;
		bool fillOpticalFlowQueue(int queueSize, shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>> opQueue);

	private:
		msl::MSLWorldModel* wm;

		enum OPValue
		{
			XValue, YValue, QOSValue
		};

		MotionControl callBehaviour(MethodParam mParm, Param parm, int trans = 0);
		MotionControl callMethod(ICalibration *behavior, MethodParam parm, int trans = 0);

		// calibration behaviours
		DribbleForward df;
		DribbleBackward db;

		double getAverageOpticalFlowValue(OPValue value, shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>> queue);
		MotionControl setNaN(MotionControl mc);
	};

}
		/* namespace alica */

#endif /* CNC_MSL_MSL_EXPRESSIONS_AUTOGENERATED_INCLUDE_PLANS_DRIBBLECALIBRATION_CONTAINER_DRIBBLECALIBRATIONCONTAINER_H_ */
