#include "Plans/Attack/AttackPlay1434045709191.h"
using namespace alica;
/*PROTECTED REGION ID(eph1434045709191) ENABLED START*/ //Add additional using directives here
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:AttackPlay

    /* generated comment
     
     Task: Attack  -> EntryPoint-ID: 1434045709194

     Task: AttackSupport  -> EntryPoint-ID: 1434045719840

     Task: Defend  -> EntryPoint-ID: 1434045723977

     Task: Keeper  -> EntryPoint-ID: 1434045771503

     */
    shared_ptr<UtilityFunction> UtilityFunction1434045709191::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1434045709191) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

//State: Attack in Plan: AttackPlay

//State: AttackSupport in Plan: AttackPlay

//State: Defend in Plan: AttackPlay

//State: KeepGoal in Plan: AttackPlay

}
