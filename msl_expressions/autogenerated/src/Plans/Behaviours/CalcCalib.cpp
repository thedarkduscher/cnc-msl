using namespace std;
#include "Plans/Behaviours/CalcCalib.h"

/*PROTECTED REGION ID(inccpp1446033324019) ENABLED START*/ //Add additional includes here
ros::Publisher calibCoeff_pub;
#include <RawSensorData.h>
/*PROTECTED REGION END*/
namespace alica
{
    /*PROTECTED REGION ID(staticVars1446033324019) ENABLED START*/ //initialise static variables here
    /*PROTECTED REGION END*/
    CalcCalib::CalcCalib() :
            DomainBehaviour("CalcCalib")
    {
        /*PROTECTED REGION ID(con1446033324019) ENABLED START*/ //Add additional options here
        /*PROTECTED REGION END*/
    }
    CalcCalib::~CalcCalib()
    {
        /*PROTECTED REGION ID(dcon1446033324019) ENABLED START*/ //Add additional options here
        /*PROTECTED REGION END*/
    }
    void CalcCalib::run(void* msg)
    {
        /*PROTECTED REGION ID(run1446033324019) ENABLED START*/ //Add additional options here

        calibPosMotionX = this->wm->rawSensorData->getOwnPositionMotion()->x;
        calibPosMotionY = this->wm->rawSensorData->getOwnPositionMotion()->y;

        correctedWayX = (calibPosMotionX - calibOldPosMotionX)
                * cos(this->wm->rawSensorData->getOwnPositionVision()->theta
                        - this->wm->rawSensorData->getOwnPositionMotion()->theta)
                - (calibPosMotionY - calibOldPosMotionY)
                        * sin(this->wm->rawSensorData->getOwnPositionVision()->theta
                                - this->wm->rawSensorData->getOwnPositionMotion()->theta);
        correctedWayY = (calibPosMotionX - calibOldPosMotionX)
                * sin(this->wm->rawSensorData->getOwnPositionVision()->theta
                        - this->wm->rawSensorData->getOwnPositionMotion()->theta)
                + (calibPosMotionY - calibOldPosMotionY)
                        * cos(this->wm->rawSensorData->getOwnPositionVision()->theta
                                - this->wm->rawSensorData->getOwnPositionMotion()->theta);

        correctedPosX = correctedPosX + correctedWayX;
        correctedPosY = correctedPosY + correctedWayY;

        lengthSegment = lengthSegment + sqrt((correctedWayX) * (correctedWayX) + (correctedWayY) * (correctedWayY));
        length = length + sqrt((correctedWayX) * (correctedWayX) + (correctedWayY) * (correctedWayY));

        calibOldPosMotionX = calibPosMotionX;
        calibOldPosMotionY = calibPosMotionY;

        /*PROTECTED REGION END*/
    }
    void CalcCalib::initialiseParameters()
    {
        /*PROTECTED REGION ID(initialiseParameters1446033324019) ENABLED START*/ //Add additional options here
        diffX = correctedPosX - this->wm->rawSensorData->getOwnPositionVision()->x;
        diffY = correctedPosY - this->wm->rawSensorData->getOwnPositionVision()->y;

        string value;
        string filename = string(sc->getConfigPath()) + string(sc->getHostname()) + string("/CalibData.txt");
        ifstream calibData(filename);
        if (calibData.is_open())
        {
            for (int lineno = 0; getline(calibData, value) && lineno < 2; lineno++)
            {
                if (lineno == 0)
                {
                    calibCoefficientX = std::stod(value);
                }

                if (lineno == 1)
                {
                    calibCoefficientY = std::stod(value);
                }
            }
            calibData.close();
        }

        if (calibCoefficientX == 0)
        {
            calibCoefficientX = 1;
        }
        if (calibCoefficientY == 0)
        {
            calibCoefficientY = 1;
        }

        ros::NodeHandle calibCEP;
        calibCoeff_pub = calibCEP.advertise < CalibrationCoefficient > ("CalibrationCoefficient", 1);

        if (length >= 1)
        {
        	if (abs(correctedPosX - oldCorrectedPosX) > 1000)
        	{
        		if (correctedPosX - oldCorrectedPosX > 0)
        		{
        			calibCoefficientX *= calibSign(this->wm->rawSensorData->getOwnPositionVision()->x, correctedWayX)
                        * (sqrt(diffX * diffX) / lengthSegment) + 1;
        		}
        		if (correctedPosX - oldCorrectedPosX < 0)
        		{
        			calibCoefficientX *= calibSign(correctedWayX, this->wm->rawSensorData->getOwnPositionVision()->x)
                        * (sqrt(diffX * diffX) / lengthSegment) + 1;
        		}
        	}
        	if (abs(correctedPosY - oldCorrectedPosY) > 1000)
        	{
        		if (correctedPosY - oldCorrectedPosY > 0)
        		{
        			calibCoefficientY *= calibSign(this->wm->rawSensorData->getOwnPositionVision()->y, correctedWayY)
                        * (sqrt(diffY * diffY) / lengthSegment) + 1;
        		}
        		if (correctedPosY - oldCorrectedPosY < 0)
        		{
        			calibCoefficientY *= calibSign(correctedWayY, this->wm->rawSensorData->getOwnPositionVision()->y)
                        * (sqrt(diffY * diffY) / lengthSegment) + 1;
        		}
        	}

            if (calibCoefficientX < 0.5)
            {
                calibCoefficientX = 0.5;
            }
            if (calibCoefficientY < 0.3)
            {
                calibCoefficientY = 0.3;
            }

            if (calibCoefficientX > 2)
            {
                calibCoefficientX = 2;
            }

            if (calibCoefficientY > 2)
            {
                calibCoefficientY = 2;
            }


            string filename = string(sc->getConfigPath()) + string(sc->getHostname()) + string("/CalibData.txt");
            ofstream saveToCalibData;
            saveToCalibData.open(filename);
            saveToCalibData << calibCoefficientX << "\n";
            saveToCalibData << calibCoefficientY;
            saveToCalibData.close();

            calibCoeff.calibCoefficientX = calibCoefficientX;
            calibCoeff.calibCoefficientY = calibCoefficientY;
            calibCoeff_pub.publish(calibCoeff);

        }

        std::cout << "Differenzen: " << std::endl;
        std::cout << "X: " << diffX << std::endl;
        std::cout << "Y: " << diffY << std::endl;
        std::cout << "Länge: " << length << std::endl;
        std::cout << "FaktorX: " << calibCoefficientX << std::endl;
        std::cout << "FaktorY: " << calibCoefficientY << std::endl;
        std::cout << "posMotionX: " << this->wm->rawSensorData->getOwnPositionMotion()->x << std::endl;
        std::cout << "posMotionY: " << this->wm->rawSensorData->getOwnPositionMotion()->y << std::endl;
        std::cout << "correctedWayX : " << correctedPosX << std::endl;
        std::cout << "correctedWayY : " << correctedPosY << std::endl;
        std::cout << "posVisionX: " << this->wm->rawSensorData->getOwnPositionVision()->x << std::endl;
        std::cout << "posVisionY: " << this->wm->rawSensorData->getOwnPositionVision()->y << std::endl;
        std::cout << "lengthSegment: " << lengthSegment << std::endl;
        std::cout << "calibCounter: " << calibCounter << std::endl;

        std::cout << "" << std::endl;

        lengthSegment = 0;
        oldCorrectedPosX = correctedPosX;
        oldCorrectedPosY = correctedPosY;
        correctedPosX = this->wm->rawSensorData->getOwnPositionVision()->x;
        correctedPosY = this->wm->rawSensorData->getOwnPositionVision()->y;

        calibCounter++;
        /*PROTECTED REGION END*/
    }
/*PROTECTED REGION ID(methods1446033324019) ENABLED START*/ //Add additional methods here
/*PROTECTED REGION END*/
} /* namespace alica */
