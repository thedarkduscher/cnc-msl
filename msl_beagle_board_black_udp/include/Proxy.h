/*
 * Proxy.h
 *
 *  Created on: Jul 26, 2016
 *      Author: cn
 */

#ifndef CNC_MSL_MSL_BEAGLE_BOARD_BLACK_UDP_INCLUDE_PROXY_H_
#define CNC_MSL_MSL_BEAGLE_BOARD_BLACK_UDP_INCLUDE_PROXY_H_

#include <string>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include <SystemConfig.h>
#include <Configuration.h>
#include <exception>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "ros/ros.h"
#include <ros/transport_hints.h>

#include "msl_actuator_msgs/BallHandleCmd.h"
#include "msl_actuator_msgs/BallHandleMode.h"
#include "msl_actuator_msgs/ShovelSelectCmd.h"
#include "msl_actuator_msgs/MotionLight.h"
#include "process_manager/ProcessCommand.h"
#include "msl_actuator_msgs/VisionRelocTrigger.h"
#include "msl_actuator_msgs/MotionBurst.h"
#include "std_msgs/Bool.h"
#include "msl_actuator_msgs/RawOdometryInfo.h"
#include "msl_actuator_msgs/CanMsg.h"
#include "msl_actuator_msgs/CanMsg.h"
#include "msl_actuator_msgs/CanMsg.h"
#include "msl_actuator_msgs/CanMsg.h"
#include "msl_actuator_msgs/IMUData.h"

class Proxy
{
public:
	void onRosBallHandleCmd1334345447(msl_actuator_msgs::BallHandleCmd& message);
	void onRosBallHandleMode297244167(msl_actuator_msgs::BallHandleMode& message);
	void onRosShovelSelectCmd1418208429(msl_actuator_msgs::ShovelSelectCmd& message);
	void onRosMotionLight2056271736(msl_actuator_msgs::MotionLight& message);
	void onRosProcessCommand554624761(process_manager::ProcessCommand& message);
	void onRosVisionRelocTrigger2772566283(msl_actuator_msgs::VisionRelocTrigger& message);
	void onRosMotionBurst1028144660(msl_actuator_msgs::MotionBurst& message);
	void onRosBool2802967882(std_msgs::Bool& message);
	void onRosRawOdometryInfo3134514216(msl_actuator_msgs::RawOdometryInfo& message);
	void onRosCanMsg1267609526(msl_actuator_msgs::CanMsg& message);
	void onRosCanMsg217678336(msl_actuator_msgs::CanMsg& message);
	void onRosCanMsg418700403(msl_actuator_msgs::CanMsg& message);
	void onRosCanMsg3391245383(msl_actuator_msgs::CanMsg& message);
	void onRosIMUData3455796956(msl_actuator_msgs::IMUData& message);

	void listenForPacket();
	void handleUdpPacket(const boost::system::error_code& error,   std::size_t bytes_transferred);
	void run_udp();

	boost::thread *iothread;
	boost::asio::io_service io_service;


private:
	std::string ownRosName;
	udp::socket* insocket;
	udp::endpoint otherEndPoint;
	udp::endpoint destEndPoint;
	boost::array<char,64000> inBuffer;
	boost::asio::ip::address multiCastAddress;
};


#endif /* CNC_MSL_MSL_BEAGLE_BOARD_BLACK_UDP_INCLUDE_PROXY_H_ */
