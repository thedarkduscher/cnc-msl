#include "Plans/Standards/Opponent/FreeKick/constraints/OppFreeKick1445411471122Constraints.h"
using namespace std;
using namespace alica;
/*PROTECTED REGION ID(ch1445411471122) ENABLED START*/
//Add additional using directives here
#include <memory>
#include "AutoDiff.h"
#include "MSLConstraintBuilder.h"
#include "MSLFootballField.h"
#include "engine/constraintmodul/SolverTerm.h"
#include "engine/constraintmodul/ConstraintDescriptor.h"
/*PROTECTED REGION END*/

namespace alicaAutogenerated
{
	//Plan:OppFreeKick

	/*
	 * Tasks:
	 * - EP:1445411471124 : DefaultTask (1225112227903)
	 *
	 * States:
	 * - PosDef (1445411471123)
	 * - Success (1447875657650)
	 *
	 * Vars:
	 */

	/*
	 * RuntimeCondition - (Name): NewRuntimeCondition
	 * (ConditionString):
	 * Static Variables: []
	 * Domain Variables:

	 * forall agents in PosDef let v = [x, y]

	 */
	void Constraint1445442215438::getConstraint(shared_ptr<ConstraintDescriptor> c, shared_ptr<RunningPlan> rp)
	{
		/*PROTECTED REGION ID(cc1445442215438) ENABLED START*/
		auto constraint = autodiff::LTConstraint::TRUE;
		auto domainVariables = c->getDomainVars();
		vector<shared_ptr<TVec>> poses;

		for (int i = 0; i < c->getDomainRanges()->at(0).size(); i++)
		{
			c->getDomainRanges()->at(0).at(i).at(0).at(0) = -msl::MSLFootballField::FieldLength / 2;
			c->getDomainRanges()->at(0).at(i).at(0).at(1) = msl::MSLFootballField::FieldLength / 2;
			c->getDomainRanges()->at(0).at(i).at(1).at(0) = -msl::MSLFootballField::FieldWidth / 2;
			c->getDomainRanges()->at(0).at(i).at(1).at(1) = msl::MSLFootballField::FieldWidth / 2;
		}

		for (int i = 0; i < domainVariables->at(0)->size(); i++)
		{
			poses.push_back(
					make_shared<TVec>(
							initializer_list<shared_ptr<Term>> {dynamic_pointer_cast<autodiff::Variable>(
									domainVariables->at(0)->at(i)->at(0)),
																dynamic_pointer_cast<autodiff::Variable>(
																		domainVariables->at(0)->at(i)->at(1))}));

			constraint = constraint & msl::MSLConstraintBuilder::insideArea(msl::Areas::OwnHalf, poses.at(i));
//			constraint = constraint & msl::MSLConstraintBuilder::applyRules(8,poses);
			constraint = constraint & msl::MSLConstraintBuilder::spread(0,poses);
//			cout << constraint->toString() << endl;
		}

		c->setDomainVars(domainVariables);
		c->setConstraint(dynamic_pointer_cast<alica::SolverTerm>(constraint));
		auto util = make_shared<autodiff::Constant>(1);
		c->setUtility(dynamic_pointer_cast<alica::SolverTerm>(util));

		/*PROTECTED REGION END*/
	}

// State: PosDef

// State: PosDef

// State: Success

// State: Success

}
