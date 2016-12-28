#include "Plans/Standards/Own/FreeKick/constraints/OwnFreeKickInOppHalf1464531946023Constraints.h"
using namespace std;
using namespace alica;
/*PROTECTED REGION ID(ch1464531946023) ENABLED START*/
//Add additional using directives here
#include <memory>
#include "AutoDiff.h"
#include "MSLConstraintBuilder.h"
#include "MSLFootballField.h"
#include "engine/constraintmodul/SolverTerm.h"
#include "engine/constraintmodul/ProblemDescriptor.h"
#include <MSLWorldModel.h>
#include <Robots.h>
#include <Ball.h>
#include <Game.h>
/*PROTECTED REGION END*/

namespace alicaAutogenerated
{
    //Plan:OwnFreeKickInOppHalf

    /*
     * Tasks:
     * - EP:1464531946025 : ExecuteStandard (1439997010902)
     * - EP:1464532126334 : ReceiveStandard (1439997023446)
     * - EP:1464532128302 : StandInsideOppPenalty (1464532449309)
     * - EP:1464532130252 : StandCloseToOppPenalty (1464864263733)
     *
     * States:
     * - PositionExecutor (1464535161175)
     * - PositionReceiver (1464535169536)
     * - GrabBall (1464535201681)
     * - Pass (1464535219397)
     * - Receive (1464535253598)
     * - Shoot (1464535263395)
     * - PositionInsideOppPenalty (1464535682818)
     * - PositionCloseToOppPenalty (1464535706293)
     * - Success (1464785222776)
     * - Wait/MoveOutOfWay (1464785237103)
     *
     * Vars:
     */

    /*
     * RuntimeCondition - (Name): NewRuntimeCondition
     * (ConditionString):
     * Static Variables: []
     * Domain Variables:

     * forall agents in PositionInsideOppPenalty let v = [x, y]

     * forall agents in PositionCloseToOppPenalty let v = [x, y]

     */
    void Constraint1467206311808::getConstraint(shared_ptr<ProblemDescriptor> c, shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(cc1467206311808) ENABLED START*/
        msl::MSLWorldModel* wm = msl::MSLWorldModel::get();
        auto constraint = autodiff::LTConstraint::TRUE;
        auto util = autodiff::TermBuilder::constant(0);
        auto domainVariables = c->getDomainVars();

        shared_ptr < geometry::CNPoint2D > ballPose = wm->ball->getAlloBallPosition();

        vector < shared_ptr < TVec >> poses;

        vector < shared_ptr < TVec >> standInside;
        vector < shared_ptr < TVec >> standOutside;

        vector < shared_ptr < geometry::CNPosition >> robotPositions;

        for (int i = 0; i < domainVariables->at(0)->size(); i++)
        {
            //
            c->getDomainRanges()->at(0).at(i).at(0).at(0) = wm->field->getFieldLength() / 2
                    - wm->field->getPenaltyAreaLength() + 500;
            c->getDomainRanges()->at(0).at(i).at(0).at(1) = wm->field->getFieldLength() / 2
                    - wm->field->getGoalAreaLength() - 500;
            if (ballPose->y > 0)
            {
                //
                c->getDomainRanges()->at(0).at(i).at(1).at(0) = 1500;
                c->getDomainRanges()->at(0).at(i).at(1).at(1) = wm->field->getPenaltyAreaWidth() / 2;
            }
            else
            {
                c->getDomainRanges()->at(0).at(i).at(1).at(0) = -wm->field->getPenaltyAreaWidth() / 2;
                c->getDomainRanges()->at(0).at(i).at(1).at(1) = -1500;
                //          c->getDomainRanges()->at(0).at(i).at(1).at(0) = wm->field->getPenaltyAreaWidth() / 2;
                //          c->getDomainRanges()->at(0).at(i).at(1).at(1) = -wm->field->getPenaltyAreaWidth() / 2;
            }

            robotPositions.push_back(wm->robots->teammates.getTeamMatePosition(c->getAgentsInScope()->at(0)->at(i)));
            auto vec = make_shared < TVec
                    > (initializer_list<shared_ptr<Term>> {dynamic_pointer_cast < autodiff::Variable
                                                                   > (domainVariables->at(0)->at(i)->at(0)),
                                                           dynamic_pointer_cast < autodiff::Variable
                                                                   > (domainVariables->at(0)->at(i)->at(1))});
            poses.push_back(vec);
            standInside.push_back(vec);
        }

        for (int i = 0; i < domainVariables->at(1)->size(); i++)
        {
            c->getDomainRanges()->at(1).at(i).at(0).at(0) = wm->field->getFieldLength() / 8;
            c->getDomainRanges()->at(1).at(i).at(0).at(1) = wm->field->getFieldLength() / 2
                    - wm->field->getPenaltyAreaLength();
            if (ballPose->y > 0)
            {
                c->getDomainRanges()->at(1).at(i).at(1).at(0) = -wm->field->getFieldWidth() / 2;
                c->getDomainRanges()->at(1).at(i).at(1).at(1) = -wm->field->getGoalAreaWidth() / 2;
            }
            else
            {
                c->getDomainRanges()->at(1).at(i).at(1).at(0) = wm->field->getGoalAreaWidth() / 2;
                c->getDomainRanges()->at(1).at(i).at(1).at(1) = wm->field->getFieldWidth() / 2;
            }

            robotPositions.push_back(wm->robots->teammates.getTeamMatePosition(c->getAgentsInScope()->at(1)->at(i)));
            auto vec = make_shared < TVec
                    > (initializer_list<shared_ptr<Term>> {dynamic_pointer_cast < autodiff::Variable
                                                                   > (domainVariables->at(1)->at(i)->at(0)),
                                                           dynamic_pointer_cast < autodiff::Variable
                                                                   > (domainVariables->at(1)->at(i)->at(1))});
            poses.push_back(vec);
            standOutside.push_back(vec);
        }

        if (ballPose == nullptr)
        {
            cout << "OFKOH: ball null" << endl;
            ballPose = make_shared < geometry::CNPoint2D > (0, 0);
        }
        shared_ptr < TVec > tvecBallPose = make_shared < TVec > (initializer_list<double> {ballPose->x, ballPose->y});

        constraint = constraint & msl::MSLConstraintBuilder::applyRules(-1, poses);

        //Just for the case when we use this after "start" has been pressed
        if (wm->game->getSituation() == msl::Situation::Start)
        {
            constraint = constraint
                    & msl::MSLConstraintBuilder::ownPenaltyAreaDistanceExceptionRule(tvecBallPose, poses);
        }

        auto opps = wm->robots->opponents.getOpponentsAlloClustered();

        vector < shared_ptr < TVec >> blockPositions;
        vector < shared_ptr < TVec >> lessGoodBlockPositions;
        vector < shared_ptr < TVec >> blockOpponents;
        shared_ptr < geometry::CNPoint2D > nearestOpp = nullptr;
        //default nearest opp

        if (ballPose != nullptr)
            nearestOpp = make_shared < geometry::CNPoint2D > (ballPose->x - 250, ballPose->y);
        double dist = 999999999;

        if (opps != nullptr)
        {
            for (auto opp : *opps)
            {
                //is nearest to the ball?
                if (ballPose != nullptr)
                {
                    wm->field->mapOutOfOwnPenalty(opp, ballPose - opp);
                    double oDist = opp->distanceTo(ballPose);
                    if (oDist < dist)
                    {
                        nearestOpp = opp;
                        oDist = dist;
                    }
                }
                else
                {
                    opp = wm->field->mapOutOfOwnPenalty(opp);
                }

                //add blocking position
                shared_ptr < geometry::CNPoint2D > blockingPos;
                if (ballPose != nullptr)
                {
                    blockingPos = opp + (ballPose - opp)->normalize() * 700;
                }
                else
                {
                    blockingPos = make_shared < geometry::CNPoint2D > (opp->x - 700, opp->y);
                }

                //only add if opp is not close to the ball
                if (ballPose->distanceTo(blockingPos) > 1800 && ballPose->distanceTo(blockingPos) < 4000)
                {
                    blockPositions.push_back(
                            make_shared < TVec > (initializer_list<double> {blockingPos->x, blockingPos->y}));
                    blockOpponents.push_back(make_shared < TVec > (initializer_list<double> {opp->x, opp->y}));
                }
                else if (ballPose->distanceTo(blockingPos) > 1800)
                {
                    lessGoodBlockPositions.push_back(make_shared < TVec > (initializer_list<double> {blockingPos->x,
                                                                                                     blockingPos->y}));
                }

            }
        }

        if (standOutside.size() > 0)
        {
            auto oppGoalPos = wm->field->posOppGoalMid();
            auto direction = (ballPose - oppGoalPos)->normalize();
            auto wallPoint = direction
                    * min(oppGoalPos->distanceTo(wm->field->posULOppPenaltyArea()),
                          ballPose->distanceTo(oppGoalPos) / 2);
            wallPoint = wallPoint + oppGoalPos;

            auto directionTVec = make_shared < TVec > (initializer_list<double> {direction->x, direction->y});
            auto wallPointTVec = make_shared < TVec > (initializer_list<double> {wallPoint->x, wallPoint->y});
            for (int j = 0; j < standOutside.size(); j++)
            {
                vector < shared_ptr < Term >> diffTerm;
                diffTerm.push_back(standOutside.at(j)->getX() - autodiff::TermBuilder::constant(wallPoint->x));
                diffTerm.push_back(standOutside.at(j)->getY() - autodiff::TermBuilder::constant(wallPoint->y));
                auto g2def = make_shared < TVec > (diffTerm);
                auto relPoint = ConstraintBuilder::inCoordsOf(g2def, directionTVec);
                constraint = constraint
                        & ((shared_ptr<autodiff::Term> )make_shared < autodiff::Abs > (relPoint->getX())
                                < autodiff::TermBuilder::constant(200));
                util = util
                        + 100
                                * (1
                                        - (ConstraintBuilder::distanceSqr(standOutside.at(j), wallPointTVec)
                                                / (wm->field->getMaxDistanceSqr())));
            }
            //c.Constraint &= ConstraintBuilder.Distance(defender[0],new AD.TVec(wallPoint.X,wallPoint.Y)) < 100;
        }

        if (standInside.size() > 0)
        {
//          shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>> trianglePoints = make_shared<vector<shared_ptr<geometry::CNPoint2D>>>();
//          trianglePoints->push_back(wm->field->posLeftOppGoalPost());
//          trianglePoints->push_back(wm->field->posRightOppGoalPost());
//          trianglePoints->push_back(ballPose);

            shared_ptr < TVec > tvecLeftPost = make_shared < TVec
                    > (initializer_list<double> {wm->field->posLeftOppGoalPost()->x, wm->field->posLeftOppGoalPost()->y
                                                         - 500});
            shared_ptr < TVec > tvecRightPost = make_shared < TVec
                    > (initializer_list<double> {wm->field->posRightOppGoalPost()->x,
                                                 wm->field->posRightOppGoalPost()->y + 500});

            constraint = constraint
                    & msl::MSLConstraintBuilder::outsideTriangle(tvecLeftPost, tvecRightPost, tvecBallPose, 0,
                                                                 standInside);

            int opponents2BlockCount = blockPositions.size();
            //constraint = constraint & msl::MSLConstraintBuilder::see(tvecBallPose, true, 10000, blocker);
            for (int k = 0; k < standInside.size(); k++)
            {
                //close to block positions
                auto blockUtil = autodiff::TermBuilder::constant(0);
                //for (int j = 0; j < min(opponents2BlockCount, (int)blocker.size()); j++)
                for (int j = 0; j < opponents2BlockCount; j++)
                {
                    blockUtil = make_shared < autodiff::Max
                            > (blockUtil, 10
                                    * (1
                                            - ((ConstraintBuilder::distanceSqr(standInside.at(k), blockPositions.at(j)))
                                                    / (wm->field->getMaxDistanceSqr() * standInside.size()))));
                }

                //if we have too view blockers... take the next best opps
                if (opponents2BlockCount < standInside.size())
                {
                    for (int j = 0; j < lessGoodBlockPositions.size(); j++)
                    {
                        blockUtil = make_shared < autodiff::Max
                                > (blockUtil, 3
                                        * (1
                                                - ((ConstraintBuilder::distanceSqr(
                                                        standInside.at(k),
                                                        lessGoodBlockPositions.at(j - opponents2BlockCount)))
                                                        / (wm->field->getMaxDistanceSqr() * standInside.size()))));
                    }
                }
                util = util + blockUtil;
                //Do not block more than 4 m away from the ball
                //constraint = constraint
                // & ConstraintBuilder::distanceSqr(blocker.at(k), tvecBallPose)
                // < autodiff::TermBuilder::constant(4000 * 4000);
                //

                //avoid opponents!
                for (int j = 0; j < opponents2BlockCount; j++)
                {
                    auto dist2Opp = ConstraintBuilder::distanceSqr(standInside.at(k), blockOpponents.at(j));
                    constraint = constraint & (dist2Opp > autodiff::TermBuilder::constant(650 * 650));
                }
                //avoid other blockers and prefer block positions with a distance of 2m (to not block the same opponents)
                for (int j = k + 1; j < standInside.size(); j++)
                {
                    auto distBlockBlock = ConstraintBuilder::distanceSqr(standInside.at(k), standInside.at(j));
                    constraint = constraint & distBlockBlock > autodiff::TermBuilder::constant(800 * 800);
                    util = util + 5 * make_shared < autodiff::Min
                            > (autodiff::TermBuilder::constant(2000 * 2000), distBlockBlock)
                                    / autodiff::TermBuilder::constant(2000 * 2000 * standInside.size());
                }
            }
        }

        //lazy utility
        vector < shared_ptr < TVec >> realRobotPosesTVec;
        for (int i = 0; i < robotPositions.size(); i++)
        {
            auto pos = robotPositions.at(i);
            if (pos != nullptr)
                realRobotPosesTVec.push_back(make_shared < TVec > (initializer_list<double> {pos->x, pos->y}));
            else
                realRobotPosesTVec.push_back(make_shared < TVec > (initializer_list<double> {0.0, 0.0}));
        }
        util = util + msl::MSLConstraintBuilder::lazyUtil(realRobotPosesTVec, poses);
        c->setConstraint(dynamic_pointer_cast < alica::SolverTerm > (constraint));
        c->setUtility(dynamic_pointer_cast < alica::SolverTerm > (util));
        /*PROTECTED REGION END*/
    }

// State: PositionExecutor

// State: PositionExecutor

// State: PositionReceiver

// State: PositionReceiver

// State: GrabBall

// State: GrabBall

// State: Pass

// State: Pass

// State: Receive

// State: Receive

// State: Shoot

// State: Shoot

// State: PositionInsideOppPenalty

// State: PositionInsideOppPenalty

// State: PositionCloseToOppPenalty

// State: PositionCloseToOppPenalty

// State: Success

// State: Success

// State: Wait/MoveOutOfWay

// State: Wait/MoveOutOfWay

}
