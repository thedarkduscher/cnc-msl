using namespace std;
#include "Plans/Behaviours/PositionExecutor.h"

/*PROTECTED REGION ID(inccpp1438790362133) ENABLED START*/ //Add additional includes here
#include "engine/model/EntryPoint.h"
#include "engine/RunningPlan.h"
#include "engine/Assignment.h"
#include "engine/model/Plan.h"

#include "MSLWorldModel.h"
#include "pathplanner/PathProxy.h"
#include "pathplanner/evaluator/PathEvaluator.h"

using namespace std;

/*PROTECTED REGION END*/
namespace alica
{
	/*PROTECTED REGION ID(staticVars1438790362133) ENABLED START*/ //initialise static variables here
	/*PROTECTED REGION END*/
	PositionExecutor::PositionExecutor() :
			DomainBehaviour("PositionExecutor"), catchRadius(100), field(nullptr)
	{
		/*PROTECTED REGION ID(con1438790362133) ENABLED START*/ //Add additional options here
		/*PROTECTED REGION END*/
	}
	PositionExecutor::~PositionExecutor()
	{
		/*PROTECTED REGION ID(dcon1438790362133) ENABLED START*/ //Add additional options here
		/*PROTECTED REGION END*/
	}
	void PositionExecutor::run(void* msg)
	{
		/*PROTECTED REGION ID(run1438790362133) ENABLED START*/ //Add additional options here
		shared_ptr<geometry::CNPosition> ownPos = wm->rawSensorData.getOwnPositionVision(); // actually ownPosition corrected
		shared_ptr<geometry::CNPoint2D> egoBallPos = wm->ball.getEgoBallPosition();

		// return if necessary information is missing
		if (ownPos == nullptr || egoBallPos == nullptr)
		{
			return;
		}

		// Create allo ball
		shared_ptr<geometry::CNPoint2D> alloBall = egoBallPos->egoToAllo(*ownPos);

		// Create additional points for path planning
		shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>> additionalPoints = make_shared<
		vector<shared_ptr<geometry::CNPoint2D>>>();
		// add alloBall to path planning
		additionalPoints->push_back(alloBall);

		// get entry point of task name to locate robot with task name
		EntryPoint* ep = getParentEntryPoint(taskName);
		if (ep != nullptr)
		{
			// get the plan in which the behavior is running
			auto parent = this->runningPlan->getParent().lock();
			if (parent == nullptr)
			{
				cout << "parent null" << endl;
				return;
			}
			// get robot ids of robots in found entry point
			shared_ptr<vector<int>> ids = parent->getAssignment()->getRobotsWorking(ep);
			shared_ptr<geometry::CNPoint2D> receiverPos = nullptr;
			// exactly one robot is receiver
			int id = ids->at(0);
			if (id != -1)
			{
				// get receiver position by id
				auto pos = wm->robots.getTeamMatePosition(id);
				receiverPos = make_shared<geometry::CNPoint2D>(pos->x, pos->y);
			}
			MotionControl mc;
			shared_ptr<geometry::CNPoint2D> egoTarget = nullptr;
			// if there is a receiver, align to it
			if (receiverPos != nullptr)
			{
				// calculate target 60cm away from the ball and on a line with the receiver
				egoTarget = (alloBall + ((alloBall - receiverPos)->normalize() * 600))->alloToEgo(*ownPos);
				// ask the path planner how to get there

				msl::MSLWorldModel* wm = msl::MSLWorldModel::get();

				cout << "TimeSinceStart: " << time << endl;
				cout << "distance to ball: " << egoTarget->length() << endl;

				if (wm->game.getSituation() == msl::Situation::Start)
				{ // they already pressed start and we are still positioning, so speed up!
					mc = msl::RobotMovement::moveToPointFast(egoTarget, receiverPos->alloToEgo(*ownPos), catchRadius, additionalPoints);
				}
				else
				{ // still enough time to position...
					mc = msl::RobotMovement::moveToPointCarefully(egoTarget, receiverPos->alloToEgo(*ownPos), catchRadius,
																	additionalPoints);
				}
			}
			else
			{
				// if there is no receiver, align to middle
				egoTarget = (alloBall + ((alloBall - alloTarget)->normalize() * 600))->alloToEgo(*ownPos);
				mc = msl::RobotMovement::moveToPointCarefully(egoTarget, alloTarget->alloToEgo(*ownPos), 0,
																additionalPoints);
			}
			// if we reach the point and are aligned, the behavior is successful
			if (egoTarget->length() < 250 && fabs(egoBallPos->rotate(M_PI)->angleTo()) < (M_PI / 180) * 5)
			{
				this->success = true;
			}
			send(mc);
		}
		/*PROTECTED REGION END*/
	}
	void PositionExecutor::initialiseParameters()
	{
		/*PROTECTED REGION ID(initialiseParameters1438790362133) ENABLED START*/ //Add additional options here
		string receiverTaskName;
		EntryPoint* receiverEp;
		if (getParameter("receiverTask", receiverTaskName))
		{
			receiverEp = this->getParentEntryPoint(receiverTaskName);
		}

		if (receiverEp == nullptr)
		{ // there is no entrypoint with the receiver task given by the behaviour parameters
			auto parent = this->runningPlan->getParent().lock();
			if (parent != nullptr && ((Plan*)parent->getPlan())->getEntryPoints().size() == 2)
			{ // there is only one other entry point than our own entry point, so it must be the receivers entry point.

				// which is my own entry point, so take the other one for the receiver
				auto activeEp = this->runningPlan->getActiveEntryPoint();
				auto eps = ((Plan*)parent->getPlan())->getEntryPoints();

				for (auto ep : eps)
				{
					if (ep.first != activeEp->getId())
					{
						receiverEp = ep.second;
						break;
					}
				}
			}
			else
			{
				cerr << "PositionExecutor: Could not determine the receivers entry point!" << endl;
				throw std::runtime_error("PositionExecutor: Could not determine the receivers entry point!");
			}
		}
		else
		{ // we found the entry point of the receiver, so everything is cool
		}

		// set some static member variables
		field = msl::MSLFootballField::getInstance();
		alloTarget = make_shared<geometry::CNPoint2D>(0, 0);

		readConfigParameters();
		/*PROTECTED REGION END*/
	}
	/*PROTECTED REGION ID(methods1438790362133) ENABLED START*/ //Add additional methods here


	void PositionExecutor::readConfigParameters()
	{
		supplementary::SystemConfig* sc = supplementary::SystemConfig::getInstance();
		catchRadius =  (*sc)["Drive"]->get<double>("Drive.Fast.CatchRadius", NULL);
	}
/*PROTECTED REGION END*/
} /* namespace alica */