/*
 * DribbleForward.cpp
 *
 *  Created on: Dec 14, 2016
 *      Author: cn
 */

#include "Plans/DribbleCalibration/Behaviours/Calibrations/DribbleForward.h"

DribbleForward::DribbleForward()
{
    // TODO Auto-generated constructor stub

}

DribbleForward::~DribbleForward()
{
    // TODO Auto-generated destructor stub
}

MotionControl DribbleForward::move(int trans)
{
    MotionControl mc;
    return mCon.move(mCon.Forward, trans);

}

void DribbleForward::writeConfigParameters()
{

}

void DribbleForward::adaptParams()
{

}
