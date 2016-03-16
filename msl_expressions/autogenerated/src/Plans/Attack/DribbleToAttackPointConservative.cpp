using namespace std;
#include "Plans/Attack/DribbleToAttackPointConservative.h"

/*PROTECTED REGION ID(inccpp1458132872550) ENABLED START*/ //Add additional includes here
/*PROTECTED REGION END*/
namespace alica
{
    /*PROTECTED REGION ID(staticVars1458132872550) ENABLED START*/ //initialise static variables here
    /*PROTECTED REGION END*/
    DribbleToAttackPointConservative::DribbleToAttackPointConservative() :
            DomainBehaviour("DribbleToAttackPointConservative")
    {
        /*PROTECTED REGION ID(con1458132872550) ENABLED START*/ //Add additional options here
    	field = msl::MSLFootballField::getInstance();
		currentTarget = make_shared<geometry::CNPoint2D>();
		attackPosY = make_shared<vector<double>>();
		attackPosY->push_back(field->FieldWidth/3.0-700);
		attackPosY->push_back(0);
		attackPosY->push_back(-field->FieldWidth/3.0+700);
        /*PROTECTED REGION END*/
    }
    DribbleToAttackPointConservative::~DribbleToAttackPointConservative()
    {
        /*PROTECTED REGION ID(dcon1458132872550) ENABLED START*/ //Add additional options here
        /*PROTECTED REGION END*/
    }
    void DribbleToAttackPointConservative::run(void* msg)
    {
        /*PROTECTED REGION ID(run1458132872550) ENABLED START*/ //Add additional options here
		auto ownPos = wm->rawSensorData.getOwnPositionVision();
		auto ballPos = wm->ball.getEgoBallPosition();
		auto dstscan = wm->rawSensorData.getDistanceScan();

		if (ownPos == nullptr) return;
		if (currentTarget==nullptr) trueInitialize();
		if (currentTarget==nullptr) return;
		auto egoTarget = currentTarget->alloToEgo(*ownPos);
		if (egoTarget->length() < 1200) {
			this->success = true;
		}

		msl_actuator_msgs::MotionControl bm;
		shared_ptr<geometry::CNPoint2D> pathPlanningPoint;
		//bm = DribbleHelper.DribbleToPoint(egoTarget,this.dribbleVel,WM,out pathPlanningPoint);
		auto tmpMC = msl::RobotMovement::dribbleToPointConservative(egoTarget, pathPlanningPoint);


		/*Point2D oppInFront = ObstacleHelper.ClosestOpponentInCorridor(WM,ballPos.Angle(),300);
		double distInFront = (oppInFront==null?Double.MaxValue:oppInFront.Distance()-300);

		double minInFrontDist = 1800;
		if (od!=null && od.Motion!=null) {
			minInFrontDist = Math.Max(minInFrontDist,Math.Min(2800,od.Motion.Translation+800));
		}
		if (ballPos != null && pathPlanningPoint!=null && Math.Abs(HHelper.DeltaAngle(pathPlanningPoint.Angle(),ballPos.Angle())) > Math.PI *4.75/6.0) {
			HHelper.SetTargetPoint(WorldHelper.Ego2Allo(pathPlanningPoint,ownPos));
			this.FailureStatus = true;
		} else if (ballPos!=null && dstscan!=null && distInFront < minInFrontDist && distInFront > 800){
			if(oppInFront!=null) HHelper.SetTargetPoint(WorldHelper.Ego2Allo(oppInFront.Rotate(Math.PI),ownPos));
			this.FailureStatus = true;
		}*/
		shared_ptr<geometry::CNPoint2D> turnTo = msl::RobotMovement::dribbleNeedToTurn(ownPos,ballPos,pathPlanningPoint);
//		if (turnTo!=nullptr) {
//			HHelper.SetTargetPoint(turnTo);
//			this->failure = true;
//		}

		//if i drive in to the enemy goal area
		//bm = DriveHelper.NearGoalArea(WM,bm);

		if(tmpMC != nullptr) {
				bm = *tmpMC;
				send(bm);
		}

        /*PROTECTED REGION END*/
    }
    void DribbleToAttackPointConservative::initialiseParameters()
    {
        /*PROTECTED REGION ID(initialiseParameters1458132872550) ENABLED START*/ //Add additional options here
		currentTarget = nullptr;
		msl::RobotMovement::reset();
		trueInitialize();
        /*PROTECTED REGION END*/
    }
/*PROTECTED REGION ID(methods1458132872550) ENABLED START*/ //Add additional methods here
    void DribbleToAttackPointConservative::trueInitialize() {
		auto ownPos = wm->rawSensorData.getOwnPositionVision();
		if (ownPos==nullptr) return;
//		Random rand = new Random();
//		int index = (int)Math.Round(rand.NextDouble()*2.0);

		srand(supplementary::DateTime::getUtcNowC());
		int index = (rand() % 3) +1;

		if (ownPos->x < field->FieldLength/6.0) {
			currentTarget = make_shared<geometry::CNPoint2D>(field->FieldLength/6.0-1500,0);
		//} else if (ownPos.X < field.FieldLength/2.0) {
		//	currentTarget = new Point2D(field.FieldLength/2.0,0);
		} else {
			currentTarget = make_shared<geometry::CNPoint2D>(field->FieldLength/4.0-1500,0);
		}
		currentTarget->y = attackPosY->at(index);
		if (currentTarget->alloToEgo(*ownPos)->length() < 1500) {
			currentTarget->y = attackPosY->at((index+1)%attackPosY->size());
		}
    }
/*PROTECTED REGION END*/
} /* namespace alica */