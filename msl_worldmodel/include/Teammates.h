/*
 * Teammates.h
 *
 *  Created on: Feb 26, 2016
 *      Author: Stefan Jakob
 */

#ifndef CNC_MSL_MSL_WORLDMODEL_SRC_TEAMMATES_H_
#define CNC_MSL_MSL_WORLDMODEL_SRC_TEAMMATES_H_

#include <memory>
#include <vector>
#include "container/CNPosition.h"
#include "RingBuffer.h"
#include "InformationElement.h"
#include <container/CNPoint2D.h>

using namespace std;

namespace msl
{

    class MSLWorldModel;
    class Teammates
    {
    public:
        Teammates(MSLWorldModel* wm, int ringBufferLength);
        virtual ~Teammates();
        int teamMatesInOwnPenalty();
        int teamMatesInOppPenalty();
        shared_ptr<geometry::CNPosition> getTeamMatePosition(int teamMateId, int index = 0);
        shared_ptr<vector<shared_ptr<pair<int, shared_ptr<geometry::CNPosition>>>>> getPositionsOfTeamMates();
        shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>> getTeammatesAlloClustered(int index = 0);
        void processTeammatesAlloClustered( shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>> teammatesAlloClustered);
        shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>> getTeammatesEgoClustered(int index = 0);
        void processTeammatesEgoClustered(shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>> teammatesEgoClustered);

        map<int, shared_ptr<RingBuffer<InformationElement<geometry::CNPosition>>>> robotPositions;

    private:
        MSLWorldModel* wm;
        int ringBufferLength;
        unsigned long maxInformationAge = 1000000000;
        RingBuffer<InformationElement<vector<shared_ptr<geometry::CNPoint2D>>>> teammatesEgoClustered;
        RingBuffer<InformationElement<vector<shared_ptr<geometry::CNPoint2D>>>> teammatesAlloClustered;

    };

} /* namespace msl */

#endif /* CNC_MSL_MSL_WORLDMODEL_SRC_TEAMMATES_H_ */
