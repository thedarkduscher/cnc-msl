#include "Plans/Defence/constraints/MidfieldBlock1458033620834Constraints.h"
using namespace std;
using namespace alica;
/*PROTECTED REGION ID(ch1458033620834) ENABLED START*/
//Add additional using directives here
#include "MSLFootballField.h"
#include "MSLWorldModel.h"
#include "engine/constraintmodul/ProblemDescriptor.h"
#include "engine/RunningPlan.h"
#include "AutoDiff.h"
#include "MSLConstraintBuilder.h"
#include "engine/model/AbstractPlan.h"
#include "engine/model/Plan.h"
#include "engine/model/EntryPoint.h"
#include "engine/model/Task.h"
#include "engine/Assignment.h"
#include <container/CNPosition.h>
#include <WhiteBoard.h>
#include <Ball.h>
#include <Robots.h>
#include <RawSensorData.h>
/*PROTECTED REGION END*/

namespace alicaAutogenerated
{
    //Plan:MidfieldBlock

    /*		
     * Tasks: 
     * - EP:1458033636229 : DefaultTask (1225112227903)
     *
     * States:
     * - MidfieldBlock (1458033636228)
     * - BlockingFinished (1458033701713)
     *
     * Vars:				
     * - X (1458034250626) 				
     * - Y (1458034254267) 
     */

    /*
     * RuntimeCondition - (Name): NewRuntimeCondition
     * (ConditionString): 
     * Static Variables: [X, Y]
     * Domain Variables:

     */
    void Constraint1458033723845::getConstraint(shared_ptr<ProblemDescriptor> c, shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(cc1458033723845) ENABLED START*/
        msl::MSLWorldModel* wm = msl::MSLWorldModel::get();
        auto util = autodiff::TermBuilder::constant(0);
        auto constraint = autodiff::LTConstraint::TRUE;
        c->getStaticRanges()->at(0).at(0) = -wm->field->getFieldLength() / 2.0;
        c->getStaticRanges()->at(0).at(1) = wm->field->getFieldLength() / 2.0;
        c->getStaticRanges()->at(1).at(0) = -wm->field->getFieldWidth() / 2.0;
        c->getStaticRanges()->at(1).at(1) = wm->field->getFieldWidth() / 2.0;

        vector < shared_ptr < autodiff::Term >> targetPosVec;
        targetPosVec.push_back(dynamic_pointer_cast < autodiff::Term > (c->getStaticVars()->at(0)));
        targetPosVec.push_back(dynamic_pointer_cast < autodiff::Term > (c->getStaticVars()->at(1)));
        shared_ptr < autodiff::TVec > p1 = make_shared < autodiff::TVec > (targetPosVec);

        // Get the Attacker Pos
        EntryPoint* attackerEp = nullptr;
        shared_ptr < RunningPlan > cur = rp->getParent().lock();
        while (cur != nullptr)
        {
            if (cur->getPlan()->getName().compare("AttackPlay"))
            {
                for (auto e : ((Plan*)cur->getPlan())->getEntryPoints())
                {
                    if (e.second->getTask()->getName().compare("Attack"))
                    {
                        attackerEp = e.second;
                        break;
                    }
                }
                break;
            }
            cur = cur->getParent().lock();
        }

        if (attackerEp == nullptr)
        {
            cout << "Midfieldblockconstraint: No Attacker EntryPoint found!" << endl;
            c->setConstraint(ConstraintBuilder::FALSE);
            return;
        }

        cur = rp->getParent().lock();
        shared_ptr<vector<int>> attacker = make_shared<vector<int>>();
        while (cur != nullptr)
        {
            if (((Plan*)cur->getPlan())->getEntryPoints().find(attackerEp->getId())
                    != ((Plan*)cur->getPlan())->getEntryPoints().end())
            {
                attacker = cur->getAssignment()->getRobotsWorking(attackerEp);
                break;
            }
            cur = cur->getParent().lock();
        }

        shared_ptr < geometry::CNPosition > attackerPos = nullptr;
        if (attacker != nullptr && attacker->size() >= 1)
        {
            attackerPos = wm->robots->teammates.getTeamMatePosition(attacker->at(0));
        }

        if (attackerPos == nullptr)
        {
            cout << "Midfieldblockconstraint: No Attacker Position found!" << endl;
            constraint = constraint & ConstraintBuilder::FALSE;
            return;
        }

        shared_ptr < autodiff::TVec > tAttackerPos = make_shared < autodiff::TVec > (initializer_list<double> {
                attackerPos->x, attackerPos->y});

        //robot must not enter opp penalty, but may enter own one
        constraint = constraint & msl::MSLConstraintBuilder::outsideArea(msl::Areas::OppPenaltyArea, p1)
                & msl::MSLConstraintBuilder::outsideArea(msl::Areas::OppPenaltyArea, p1);

        shared_ptr < geometry::CNPosition > ownPos = wm->rawSensorData->getOwnPositionVision();
        shared_ptr < geometry::CNPoint2D > ball = wm->ball->getEgoBallPosition();
        shared_ptr < geometry::CNPoint2D > alloBall = nullptr;

        shared_ptr < autodiff::Term > op1 = autodiff::Term::FALSE;

        if (ownPos == nullptr || ball == nullptr)
        {
            c->setConstraint(autodiff::Term::FALSE);
            return;
        }

        alloBall = ball->egoToAllo(*ownPos);
        shared_ptr < autodiff::TVec > talloBall = make_shared < autodiff::TVec
                > (initializer_list<double> {alloBall->x, alloBall->y});
        // min max distance
        constraint = constraint
                & ConstraintBuilder::distanceSqr(p1, talloBall) > autodiff::TermBuilder::constant(400.0 * 400.0);
        constraint = constraint
                & ConstraintBuilder::distanceSqr(p1, tAttackerPos) < autodiff::TermBuilder::constant(5500.0 * 5500.0);

        shared_ptr < geometry::CNPoint2D > attacker2ball = alloBall - attackerPos;
        double freeWayLength = 1500.0;
        shared_ptr < geometry::CNPoint2D > freeWayPoint = attackerPos->getPoint()
                + attacker2ball->normalize() * freeWayLength;
        double ratio = tan(45 * M_PI / 180);
        shared_ptr < geometry::CNPoint2D > attacker2ballOrth = make_shared < geometry::CNPoint2D
                > (-attacker2ball->y, attacker2ball->x)->normalize() * ratio * freeWayLength;

        shared_ptr < geometry::CNPoint2D > left = freeWayPoint + attacker2ballOrth;
        shared_ptr < autodiff::TVec > tLeft = make_shared < autodiff::TVec
                > (initializer_list<double> {left->x, left->y});
        shared_ptr < geometry::CNPoint2D > right = freeWayPoint - attacker2ballOrth;
        shared_ptr < autodiff::TVec > tRight = make_shared < autodiff::TVec
                > (initializer_list<double> {right->x, right->y});

        util = util + (1 - ConstraintBuilder::distance(p1, talloBall) / wm->field->getMaxDistance());

        shared_ptr < geometry::CNPoint2D > own2Attacker = attackerPos->getPoint() - ownPos->getPoint()
                + attackerPos->getPoint();
        shared_ptr < autodiff::TVec > town2Attacker = make_shared < autodiff::TVec > (initializer_list<double> {
                own2Attacker->x, own2Attacker->y});

        shared_ptr < geometry::CNPoint2D > attacker2Own = ownPos->getPoint() - attackerPos->getPoint();
        double distToCake = (attacker2Own->x * attacker2ball->y - attacker2Own->y * attacker2ball->x)
                / attacker2Own->length();

        if (distToCake > 300)
        {
            //right of
            vector < shared_ptr < TVec >> v;
            v.push_back(p1);
            constraint = constraint
                    & msl::MSLConstraintBuilder::outsideCakePiece(tAttackerPos, talloBall, town2Attacker, 150, v);
        }
        else if (distToCake < -300)
        {
            //left of
            vector < shared_ptr < TVec >> v;
            v.push_back(p1);
            constraint = constraint
                    & msl::MSLConstraintBuilder::outsideCakePiece(tAttackerPos, town2Attacker, talloBall, 150, v);
        } //else no piece of cake for us :(

        auto opps = wm->robots->opponents.getOpponentsAlloClustered(); //GetTrackedOpponents();
        if (opps->size() > 0)
        {
            for (int i = 0; i < opps->size(); i++)
            {
                shared_ptr < geometry::CNPoint2D > bpos = opps->at(i) + (alloBall - opps->at(i))->normalize() * 600;
                shared_ptr < autodiff::TVec > tbpos = make_shared < autodiff::TVec
                        > (initializer_list<double> {bpos->x, bpos->y});
                //Equality constraint is more efficient than 'distance < x' constraint, use if a very small area is ment
                vector < shared_ptr < TVec >> v;
                v.push_back(tbpos);
                op1 = op1
                        | (ConstraintBuilder::equals(p1, tbpos, 10)
                                & (msl::MSLConstraintBuilder::outsideTriangle(tAttackerPos, tRight, tLeft, 500.0, v)
                                        | ConstraintBuilder::distanceSqr(tbpos, p1)
                                                < autodiff::TermBuilder::constant(300.0 * 300.0)));

            }
        }

        constraint = constraint & op1;

        //avoid teammates
        auto mates = wm->robots->teammates.getTeammatesAlloClustered();
        vector < shared_ptr < autodiff::TVec >> mateVec;
        if (mates != nullptr)
        {
            for (int i = 0; i < mates->size(); i++)
            {
                mateVec.push_back(
                        make_shared < autodiff::TVec > (initializer_list<double> {mates->at(i)->x, mates->at(i)->y}));
                constraint = constraint
                        & ConstraintBuilder::distanceSqr(p1, mateVec[i]) > autodiff::TermBuilder::constant(750 * 750); //get away from mates
            }
        }
        //Pass should be at most 2m away from the ball (relevant if we do not have the ball)
        shared_ptr < geometry::CNPoint2D > ballPos = wm->ball->getAlloBallPosition();
        if (ballPos != nullptr
                && (wm->whiteBoard->getPassMsg() == nullptr
                        || wm->whiteBoard->getPassMsg()->receiverID != wm->getOwnId()))
        {
            shared_ptr < TVec > tvecBallPose = make_shared < TVec > (initializer_list<double> {ballPos->x, ballPos->y});
            constraint = constraint
                    & (ConstraintBuilder::distanceSqr(p1, tvecBallPose) > autodiff::TermBuilder::constant(1500 * 1500));
        }

        if (ownPos != nullptr)
        {
            //add 'lazyness' utility for stability:
            util = util
                    + 0.75
                            * (1
                                    - (ConstraintBuilder::distanceSqr(
                                            p1, make_shared < autodiff::TVec > (initializer_list<double> {ownPos->x,
                                                                                                          ownPos->y}))
                                            / (wm->field->getMaxDistance() * wm->field->getMaxDistance())));
        }

        c->setConstraint(dynamic_pointer_cast < alica::SolverTerm > (constraint));
        c->setUtility(dynamic_pointer_cast < alica::SolverTerm > (util));

        /*PROTECTED REGION END*/
    }

// State: MidfieldBlock

// State: MidfieldBlock

// State: BlockingFinished

// State: BlockingFinished

}
