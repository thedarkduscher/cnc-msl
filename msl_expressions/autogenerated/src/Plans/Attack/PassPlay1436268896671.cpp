#include "Plans/Attack/PassPlay1436268896671.h"
using namespace alica;
/*PROTECTED REGION ID(eph1436268896671) ENABLED START*/ //Add additional using directives here
#include "engine/model/AbstractPlan.h"
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
	//Plan:PassPlay

	/* generated comment

	 Task: DefaultTask  -> EntryPoint-ID: 1436268896674

	 */
	shared_ptr<UtilityFunction> UtilityFunction1436268896671::getUtilityFunction(Plan* plan)
	{
		/*PROTECTED REGION ID(1436268896671) ENABLED START*/

		shared_ptr<UtilityFunction> defaultFunction = make_shared<DefaultUtilityFunction>(plan);
		return defaultFunction;

		/*PROTECTED REGION END*/
	}

	//State: Dribble in Plan: PassPlay

	/*
	 *
	 * Transition:
	 *   - Name: MISSING_NAME, ConditionString: , Comment : Success
	 *
	 * Plans in State:
	 *   - Plan - (Name): SearchForPassPointDefault, (PlanID): 1436269036396
	 *   - Plan - (Name): ShovelSelectHighKick, (PlanID): 1435156811453
	 *   - Plan - (Name): Dribble, (PlanID): 1434049476066
	 *
	 * Tasks:
	 *   - DefaultTask (1225112227903) (Entrypoint: 1436268896674)
	 *
	 * States:
	 *   - Dribble (1436268896672)
	 *   - Pass (1436268931449)
	 *
	 * Vars:
	 */
	bool TransitionCondition1436268944209::evaluate(shared_ptr<RunningPlan> rp)
	{
		/*PROTECTED REGION ID(1436268942088) ENABLED START*/
		bool canShoot = true;
		if (wm->game.isMayScore())
		{
			msl::MSLFootballField* field = msl::MSLFootballField::getInstance();
			shared_ptr<geometry::CNPosition> ownPos = wm->rawSensorData.getOwnPositionVision();
			if (ownPos == nullptr)
			{
				return false;
			}
			//RC-10: no goal shot from own half:
			if (ownPos->x < 0)
			{
				canShoot = false;
			}
			else
			{
				double distance = numeric_limits<double>::max();
				auto obs = wm->robots.getObstaclePoints();
				auto ballPos = wm->ball.getEgoBallPosition();
				if (obs == nullptr || ballPos == nullptr)
				{
					return false;
				}
				double dist = 1300;
				double temp = numeric_limits<double>::max();
				if (geometry::GeometryCalculator::outsideTriangle(ballPos->egoToAllo(*ownPos),
																	field->posRightOppGoalPost()->normalize() * dist,
																	field->posLeftOppGoalPost()->normalize() * dist,
																	450, obs))
				{
					for (int i = 0; i < obs->size(); i++)
					{
						temp = obs->at(i)->egoToAllo(*ownPos)->distanceTo(ballPos->egoToAllo(*ownPos));
						if (temp < distance)
						{
							distance = temp;
						}
					}
				}

				shared_ptr<geometry::CNPoint2D> goalMid = make_shared<geometry::CNPoint2D>(field->FieldLength / 2, 0);

				double goalAng = goalMid->angleToPoint(ownPos->getPoint());
				if (abs(goalAng) < 118.0 * M_PI / 180)
				{
					canShoot = false;
				}
				else
				{
					double goalDist = ownPos->distanceTo(goalMid);
					canShoot = goalDist < wm->kicker.getPreciseShotMaxDistance()
							&& goalDist > wm->kicker.getPreciseShotMinDistance()
							&& wm->kicker.getFreeGoalVector() != nullptr
							&& distance > 1300;
				}
			}
			if (canShoot)
			{
				return false;
			}
		}

		for(shared_ptr<RunningPlan> rpChild : *rp->getChildren())
		{
			if (rpChild->isBehaviour() && rpChild->getPlan()->getId() == 1436269036396 && rpChild->getStatus() == PlanStatus::Success)
			{
				return true;
			}
		}
		return false;
		/*PROTECTED REGION END*/

	}

	//State: Pass in Plan: PassPlay

	/*
	 *
	 * Transition:
	 *   - Name: MISSING_NAME, ConditionString: , Comment : pass fails
	 *
	 * Plans in State:
	 *   - Plan - (Name): AlignAndPassRapidDefault, (PlanID): 1436269080263
	 *   - Plan - (Name): ShovelSelectLowKick, (PlanID): 1435156714286
	 *
	 * Tasks:
	 *   - DefaultTask (1225112227903) (Entrypoint: 1436268896674)
	 *
	 * States:
	 *   - Dribble (1436268896672)
	 *   - Pass (1436268931449)
	 *
	 * Vars:
	 */
	bool TransitionCondition1436268945305::evaluate(shared_ptr<RunningPlan> rp)
	{
		/*PROTECTED REGION ID(1436268944412) ENABLED START*/
		return rp->anyChildrenStatus(PlanStatus::Failed);
		/*PROTECTED REGION END*/

	}

}
