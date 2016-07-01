#include "RTIMULib.h"

#include <stdlib.h>
#include "msl_msgs/Point3dInfo.h"

class RTIMUBBB
{
public:
	RTIMUBBB();
	~RTIMUBBB();

	void getNewData();

	msl_msgs::Point3dInfo getAcceleration();
	msl_msgs::Point3dInfo getMagnetfield();
	msl_msgs::Point3dInfo getRotation();

	uint64_t getDataTime();
	uint64_t getTimeDifference();

private:
	RTIMU *imu;
	RTIMU_DATA oldData;

	int sampleCount = 0;
	int sampleRate = 0;
	uint64_t rateTimer;
	uint64_t timeDifference;
	uint64_t now;


};
