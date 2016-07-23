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

using namespace msl;
namespace alica
{
	#define FORWARD 100
	#define BACKWARD 200
	#define LEFT 300
	#define RIGHT 400

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

		msl_actuator_msgs::MotionControl getBall();
		msl_actuator_msgs::MotionControl move(int movement, int translation);


		double readConfigParameter(const char *path);
//		void writeConfigParameters(shared_ptr<vector<subsection>> sections);
		void writeConfigParameters(vector<subsection> sections);
	private:
		msl::MSLWorldModel* wm;

		shared_ptr<msl::MovementQuery> query;
	};

} /* namespace alica */

#endif /* CNC_MSL_MSL_EXPRESSIONS_AUTOGENERATED_INCLUDE_PLANS_DRIBBLECALIBRATION_CONTAINER_DRIBBLECALIBRATIONCONTAINER_H_ */
