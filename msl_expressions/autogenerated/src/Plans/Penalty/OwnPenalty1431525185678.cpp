#include "Plans/Penalty/OwnPenalty1431525185678.h"
using namespace alica;
/*PROTECTED REGION ID(eph1431525185678) ENABLED START*/ //Add additional using directives here
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:OwnPenalty

    /* generated comment
     
     Task: StandardExecuter  -> EntryPoint-ID: 1431525245110

     Task: DefaultTask  -> EntryPoint-ID: 1431526909013

     */
    shared_ptr<UtilityFunction> UtilityFunction1431525185678::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1431525185678) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

    //State: DriveToMiddle in Plan: OwnPenalty

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : start signal received 
     *
     * Plans in State: 				
     *   - Plan - (Name): DriveToMiddle, (PlanID): 1431527260342 
     *
     * Tasks: 
     *   - StandardExecuter (1238601692867) (Entrypoint: 1431525245110)
     *   - DefaultTask (1225112227903) (Entrypoint: 1431526909013)
     *
     * States:
     *   - DriveToMiddle (1431525245109)
     *   - GrabBall (1431526626723)
     *   - AlignAndShoot (1431526769660)
     *   - Stop (1431526917231)
     *   - Stop (1431531108950)
     *
     * Vars:
     */
    bool TransitionCondition1431526664270::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1431526662401) ENABLED START*/
        return rp->anyChildrenStatus(PlanStatus::Success);
        /*PROTECTED REGION END*/

    }

    //State: GrabBall in Plan: OwnPenalty

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment :  
     *
     * Plans in State: 				
     *   - Plan - (Name): InterceptCarefullyDefault, (PlanID): 1427703234654 
     *
     * Tasks: 
     *   - StandardExecuter (1238601692867) (Entrypoint: 1431525245110)
     *   - DefaultTask (1225112227903) (Entrypoint: 1431526909013)
     *
     * States:
     *   - DriveToMiddle (1431525245109)
     *   - GrabBall (1431526626723)
     *   - AlignAndShoot (1431526769660)
     *   - Stop (1431526917231)
     *   - Stop (1431531108950)
     *
     * Vars:
     */
    bool TransitionCondition1431526792158::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1431526790723) ENABLED START*/
        cout << "have ball " << wm->ball.haveBall() << endl;
        return wm->ball.haveBall();
        /*PROTECTED REGION END*/

    }

    //State: AlignAndShoot in Plan: OwnPenalty

    /*
     *		
     * Transition:
     *   - Name: MISSING_NAME, ConditionString: , Comment : shot 
     *
     * Plans in State: 				
     *   - Plan - (Name): PenaltyAlignAndShootDefault, (PlanID): 1431531542052 
     *
     * Tasks: 
     *   - StandardExecuter (1238601692867) (Entrypoint: 1431525245110)
     *   - DefaultTask (1225112227903) (Entrypoint: 1431526909013)
     *
     * States:
     *   - DriveToMiddle (1431525245109)
     *   - GrabBall (1431526626723)
     *   - AlignAndShoot (1431526769660)
     *   - Stop (1431526917231)
     *   - Stop (1431531108950)
     *
     * Vars:
     */
    bool TransitionCondition1431531118276::evaluate(shared_ptr<RunningPlan> rp)
    {
        /*PROTECTED REGION ID(1431531116597) ENABLED START*/
        return rp->anyChildrenStatus(PlanStatus::Success);
        /*PROTECTED REGION END*/

    }

//State: Stop in Plan: OwnPenalty

//State: Stop in Plan: OwnPenalty

}
