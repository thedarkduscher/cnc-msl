#include "Plans/GameStrategy/OwnStandards/GenericOwnStandardPositioning1428507630593.h"
using namespace alica;
/*PROTECTED REGION ID(eph1428507630593) ENABLED START*/ //Add additional using directives here
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:GenericOwnStandardPositioning

    /* generated comment
     
     Task: Receiver  -> EntryPoint-ID: 1428507664503

     Task: Executer  -> EntryPoint-ID: 1428507727863

     Task: StandardDefend  -> EntryPoint-ID: 1428507808894

     */
    shared_ptr<UtilityFunction> UtilityFunction1428507630593::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1428507630593) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

//State: ReceiverPositioning in Plan: GenericOwnStandardPositioning

//State: ExecuterPositioning in Plan: GenericOwnStandardPositioning

//State: StandardDefendPositioning in Plan: GenericOwnStandardPositioning

}
