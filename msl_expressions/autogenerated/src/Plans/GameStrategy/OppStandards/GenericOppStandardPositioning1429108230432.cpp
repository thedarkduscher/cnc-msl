#include "Plans/GameStrategy/OppStandards/GenericOppStandardPositioning1429108230432.h"
using namespace alica;
/*PROTECTED REGION ID(eph1429108230432) ENABLED START*/ //Add additional using directives here
/*PROTECTED REGION END*/
namespace alicaAutogenerated
{
    //Plan:GenericOppStandardPositioning

    /* generated comment
     
     Task: Watcher  -> EntryPoint-ID: 1429108491532

     Task: Blocker  -> EntryPoint-ID: 1429109224669

     Task: StandardDefend  -> EntryPoint-ID: 1429110470504

     */
    shared_ptr<UtilityFunction> UtilityFunction1429108230432::getUtilityFunction(Plan* plan)
    {
        /*PROTECTED REGION ID(1429108230432) ENABLED START*/

        shared_ptr < UtilityFunction > defaultFunction = make_shared < DefaultUtilityFunction > (plan);
        return defaultFunction;

        /*PROTECTED REGION END*/
    }

//State: WatcherPositioning in Plan: GenericOppStandardPositioning

//State: BlockerPositioning in Plan: GenericOppStandardPositioning

//State: StandardDefend in Plan: GenericOppStandardPositioning

}
