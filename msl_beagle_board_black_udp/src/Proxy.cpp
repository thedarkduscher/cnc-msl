#include "Proxy.h"
#include "Actuator.h"

using boost::asio::ip::udp;

Proxy::Proxy() {
	supplementary::SystemConfig* sc = supplementary::SystemConfig::getInstance();

	supplementary::Configuration *proxyconf = (*sc)["msl_bbb_proxy"];
	std::string baddress = proxyconf->get<std::string>("UdpProxy","MulticastAddress",NULL);
	unsigned short port = (unsigned short)proxyconf->get<int>("UdpProxy","Port",NULL);
	multiCastAddress = boost::asio::ip::address::from_string(baddress);
	destEndPoint = udp::endpoint(multiCastAddress,port);
	std::cout<<"Opening to "<<multiCastAddress <<std::endl;
	insocket = new udp::socket(io_service,udp::endpoint(multiCastAddress,port));
	insocket->set_option(boost::asio::ip::multicast::enable_loopback(false));
	insocket->set_option(boost::asio::ip::multicast::join_group(multiCastAddress));
//	listenForPacket();

	iothread = new boost::thread(&Proxy::run_udp, this);
	std::cout << "Udp connection active..." << std::endl;
}

Proxy::~Proxy() {
	io_service.stop();
	iothread->join();
	delete actuator;
	delete iothread;
	delete insocket;
}

Proxy* Proxy::getInstance() {
	static Proxy instance;
	return &instance;
}

void Proxy::setActuator(Actuator* actuator) {
	this->actuator = actuator;
}

void Proxy::onRosBallHandleCmd1334345447(msl_actuator_msgs::BallHandleCmd& message) {
uint8_t* buffer = NULL;
	try{
		uint32_t serial_size = ros::serialization::serializationLength(message);
		buffer = new uint8_t[serial_size+sizeof(uint32_t)];
		ros::serialization::OStream stream(buffer+sizeof(uint32_t), serial_size);
		*((uint32_t*)buffer) = 1334345447u;
		ros::serialization::serialize(stream, message);
		// write message to UDP
		insocket->send_to(boost::asio::buffer((void*)buffer,serial_size+sizeof(uint32_t)),destEndPoint);
	} catch(std::exception& e) {
		ROS_ERROR_STREAM_THROTTLE(2,"Exception while sending UDP message:"<<e.what()<< " Discarding message!");
	}
	if(buffer!=NULL) delete[] buffer;
}
void Proxy::onRosBallHandleMode297244167(msl_actuator_msgs::BallHandleMode& message) {
uint8_t* buffer = NULL;
	try{
		uint32_t serial_size = ros::serialization::serializationLength(message);
		buffer = new uint8_t[serial_size+sizeof(uint32_t)];
		ros::serialization::OStream stream(buffer+sizeof(uint32_t), serial_size);
		*((uint32_t*)buffer) = 297244167u;
		ros::serialization::serialize(stream, message);
		// write message to UDP
		insocket->send_to(boost::asio::buffer((void*)buffer,serial_size+sizeof(uint32_t)),destEndPoint);
	} catch(std::exception& e) {
		ROS_ERROR_STREAM_THROTTLE(2,"Exception while sending UDP message:"<<e.what()<< " Discarding message!");
	}
	if(buffer!=NULL) delete[] buffer;
}
void Proxy::onRosShovelSelectCmd1418208429(msl_actuator_msgs::ShovelSelectCmd& message) {
uint8_t* buffer = NULL;
	try{
		uint32_t serial_size = ros::serialization::serializationLength(message);
		buffer = new uint8_t[serial_size+sizeof(uint32_t)];
		ros::serialization::OStream stream(buffer+sizeof(uint32_t), serial_size);
		*((uint32_t*)buffer) = 1418208429u;
		ros::serialization::serialize(stream, message);
		// write message to UDP
		insocket->send_to(boost::asio::buffer((void*)buffer,serial_size+sizeof(uint32_t)),destEndPoint);
	} catch(std::exception& e) {
		ROS_ERROR_STREAM_THROTTLE(2,"Exception while sending UDP message:"<<e.what()<< " Discarding message!");
	}
	if(buffer!=NULL) delete[] buffer;
}
void Proxy::onRosMotionLight2056271736(msl_actuator_msgs::MotionLight& message) {
uint8_t* buffer = NULL;
	try{
		uint32_t serial_size = ros::serialization::serializationLength(message);
		buffer = new uint8_t[serial_size+sizeof(uint32_t)];
		ros::serialization::OStream stream(buffer+sizeof(uint32_t), serial_size);
		*((uint32_t*)buffer) = 2056271736u;
		ros::serialization::serialize(stream, message);
		// write message to UDP
		insocket->send_to(boost::asio::buffer((void*)buffer,serial_size+sizeof(uint32_t)),destEndPoint);
	} catch(std::exception& e) {
		ROS_ERROR_STREAM_THROTTLE(2,"Exception while sending UDP message:"<<e.what()<< " Discarding message!");
	}
	if(buffer!=NULL) delete[] buffer;
}
void Proxy::onRosProcessCommand554624761(process_manager::ProcessCommand& message) {
uint8_t* buffer = NULL;
	try{
		uint32_t serial_size = ros::serialization::serializationLength(message);
		buffer = new uint8_t[serial_size+sizeof(uint32_t)];
		ros::serialization::OStream stream(buffer+sizeof(uint32_t), serial_size);
		*((uint32_t*)buffer) = 3108117629u;
		ros::serialization::serialize(stream, message);
		// write message to UDP
		insocket->send_to(boost::asio::buffer((void*)buffer,serial_size+sizeof(uint32_t)),destEndPoint);
	} catch(std::exception& e) {
		ROS_ERROR_STREAM_THROTTLE(2,"Exception while sending UDP message:"<<e.what()<< " Discarding message!");
	}
	if(buffer!=NULL) delete[] buffer;
}
void Proxy::onRosVisionRelocTrigger2772566283(msl_actuator_msgs::VisionRelocTrigger& message) {
uint8_t* buffer = NULL;
	try{
		uint32_t serial_size = ros::serialization::serializationLength(message);
		buffer = new uint8_t[serial_size+sizeof(uint32_t)];
		ros::serialization::OStream stream(buffer+sizeof(uint32_t), serial_size);
		*((uint32_t*)buffer) = 2772566283u;
		ros::serialization::serialize(stream, message);
		// write message to UDP
		insocket->send_to(boost::asio::buffer((void*)buffer,serial_size+sizeof(uint32_t)),destEndPoint);
	} catch(std::exception& e) {
		ROS_ERROR_STREAM_THROTTLE(2,"Exception while sending UDP message:"<<e.what()<< " Discarding message!");
	}
	if(buffer!=NULL) delete[] buffer;
}
void Proxy::onRosMotionBurst1028144660(msl_actuator_msgs::MotionBurst& message) {
uint8_t* buffer = NULL;
	try{
		uint32_t serial_size = ros::serialization::serializationLength(message);
		buffer = new uint8_t[serial_size+sizeof(uint32_t)];
		ros::serialization::OStream stream(buffer+sizeof(uint32_t), serial_size);
		*((uint32_t*)buffer) = 1028144660u;
		ros::serialization::serialize(stream, message);
		// write message to UDP
		insocket->send_to(boost::asio::buffer((void*)buffer,serial_size+sizeof(uint32_t)),destEndPoint);
	} catch(std::exception& e) {
		ROS_ERROR_STREAM_THROTTLE(2,"Exception while sending UDP message:"<<e.what()<< " Discarding message!");
	}
	if(buffer!=NULL) delete[] buffer;
}
void Proxy::onRosBool2802967882(std_msgs::Bool& message) {
uint8_t* buffer = NULL;
	try{
		uint32_t serial_size = ros::serialization::serializationLength(message);
		buffer = new uint8_t[serial_size+sizeof(uint32_t)];
		ros::serialization::OStream stream(buffer+sizeof(uint32_t), serial_size);
		*((uint32_t*)buffer) = 2802967882u;
		ros::serialization::serialize(stream, message);
		// write message to UDP
		insocket->send_to(boost::asio::buffer((void*)buffer,serial_size+sizeof(uint32_t)),destEndPoint);
	} catch(std::exception& e) {
		ROS_ERROR_STREAM_THROTTLE(2,"Exception while sending UDP message:"<<e.what()<< " Discarding message!");
	}
	if(buffer!=NULL) delete[] buffer;
}
void Proxy::onRosRawOdometryInfo3134514216(msl_actuator_msgs::RawOdometryInfo& message) {
uint8_t* buffer = NULL;
	try{
		uint32_t serial_size = ros::serialization::serializationLength(message);
		buffer = new uint8_t[serial_size+sizeof(uint32_t)];
		ros::serialization::OStream stream(buffer+sizeof(uint32_t), serial_size);
		*((uint32_t*)buffer) = 3134514216u;
		ros::serialization::serialize(stream, message);
		// write message to UDP
		insocket->send_to(boost::asio::buffer((void*)buffer,serial_size+sizeof(uint32_t)),destEndPoint);
	} catch(std::exception& e) {
		ROS_ERROR_STREAM_THROTTLE(2,"Exception while sending UDP message:"<<e.what()<< " Discarding message!");
	}
	if(buffer!=NULL) delete[] buffer;
}
void Proxy::onRosCanMsg1267609526(msl_actuator_msgs::CanMsg& message) {
uint8_t* buffer = NULL;
	try{
		uint32_t serial_size = ros::serialization::serializationLength(message);
		buffer = new uint8_t[serial_size+sizeof(uint32_t)];
		ros::serialization::OStream stream(buffer+sizeof(uint32_t), serial_size);
		*((uint32_t*)buffer) = 1267609526u;
		ros::serialization::serialize(stream, message);
		// write message to UDP
		insocket->send_to(boost::asio::buffer((void*)buffer,serial_size+sizeof(uint32_t)),destEndPoint);
	} catch(std::exception& e) {
		ROS_ERROR_STREAM_THROTTLE(2,"Exception while sending UDP message:"<<e.what()<< " Discarding message!");
	}
	if(buffer!=NULL) delete[] buffer;
}
void Proxy::onRosCanMsg217678336(msl_actuator_msgs::CanMsg& message) {
uint8_t* buffer = NULL;
	try{
		uint32_t serial_size = ros::serialization::serializationLength(message);
		buffer = new uint8_t[serial_size+sizeof(uint32_t)];
		ros::serialization::OStream stream(buffer+sizeof(uint32_t), serial_size);
		*((uint32_t*)buffer) = 217678336u;
		ros::serialization::serialize(stream, message);
		// write message to UDP
		insocket->send_to(boost::asio::buffer((void*)buffer,serial_size+sizeof(uint32_t)),destEndPoint);
	} catch(std::exception& e) {
		ROS_ERROR_STREAM_THROTTLE(2,"Exception while sending UDP message:"<<e.what()<< " Discarding message!");
	}
	if(buffer!=NULL) delete[] buffer;
}
void Proxy::onRosCanMsg418700403(msl_actuator_msgs::CanMsg& message) {
uint8_t* buffer = NULL;
	try{
		uint32_t serial_size = ros::serialization::serializationLength(message);
		buffer = new uint8_t[serial_size+sizeof(uint32_t)];
		ros::serialization::OStream stream(buffer+sizeof(uint32_t), serial_size);
		*((uint32_t*)buffer) = 418700403u;
		ros::serialization::serialize(stream, message);
		// write message to UDP
		insocket->send_to(boost::asio::buffer((void*)buffer,serial_size+sizeof(uint32_t)),destEndPoint);
	} catch(std::exception& e) {
		ROS_ERROR_STREAM_THROTTLE(2,"Exception while sending UDP message:"<<e.what()<< " Discarding message!");
	}
	if(buffer!=NULL) delete[] buffer;
}
void Proxy::onRosCanMsg3391245383(msl_actuator_msgs::CanMsg& message) {
uint8_t* buffer = NULL;
	try{
		uint32_t serial_size = ros::serialization::serializationLength(message);
		buffer = new uint8_t[serial_size+sizeof(uint32_t)];
		ros::serialization::OStream stream(buffer+sizeof(uint32_t), serial_size);
		*((uint32_t*)buffer) = 3391245383u;
		ros::serialization::serialize(stream, message);
		// write message to UDP
		insocket->send_to(boost::asio::buffer((void*)buffer,serial_size+sizeof(uint32_t)),destEndPoint);
	} catch(std::exception& e) {
		ROS_ERROR_STREAM_THROTTLE(2,"Exception while sending UDP message:"<<e.what()<< " Discarding message!");
	}
	if(buffer!=NULL) delete[] buffer;
}
void Proxy::onRosIMUData3455796956(msl_actuator_msgs::IMUData& message) {
uint8_t* buffer = NULL;
	try{
		uint32_t serial_size = ros::serialization::serializationLength(message);
		buffer = new uint8_t[serial_size+sizeof(uint32_t)];
		ros::serialization::OStream stream(buffer+sizeof(uint32_t), serial_size);
		*((uint32_t*)buffer) = 3455796956u;
		ros::serialization::serialize(stream, message);
		// write message to UDP
		insocket->send_to(boost::asio::buffer((void*)buffer,serial_size+sizeof(uint32_t)),destEndPoint);
	} catch(std::exception& e) {
		ROS_ERROR_STREAM_THROTTLE(2,"Exception while sending UDP message:"<<e.what()<< " Discarding message!");
	}
	if(buffer!=NULL) delete[] buffer;
}
void Proxy::listenForPacket() {
	insocket->async_receive_from(boost::asio::buffer(inBuffer), otherEndPoint,
        boost::bind(&Proxy::handleUdpPacket, this, boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
}
void Proxy::handleUdpPacket(const boost::system::error_code& error,   std::size_t bytes_transferred) {
	//std::cout << "From "<<otherEndPoint.address() << std::endl;
	if (bytes_transferred > 64000) {
		return;
	}
	if (!error) { // && otherEndPoint.address() != localIP) {
		__uint32_t id = *((__uint32_t*)(inBuffer.data()));
		//std::cout << "Got packet"<<std::endl;
		try {
			ros::serialization::IStream stream(((uint8_t*)inBuffer.data())+sizeof(__uint32_t),bytes_transferred-sizeof(__uint32_t));
			switch(id) {
				case 1334345447ul: {
				msl_actuator_msgs::BallHandleCmd m1334345447;
				ros::serialization::Serializer<msl_actuator_msgs::BallHandleCmd>::read(stream, m1334345447);

				actuator->handleBallHandleControl(m1334345447);
				break; }
				case 297244167ul: {
				msl_actuator_msgs::BallHandleMode m297244167;
				ros::serialization::Serializer<msl_actuator_msgs::BallHandleMode>::read(stream, m297244167);

				actuator->handleBallHandleMode(m297244167);
				break; }
				case 1418208429ul: {
				msl_actuator_msgs::ShovelSelectCmd m1418208429;
				ros::serialization::Serializer<msl_actuator_msgs::ShovelSelectCmd>::read(stream, m1418208429);

				actuator->handleShovelSelectControl(m1418208429);
				break; }
				case 2056271736ul: {
				msl_actuator_msgs::MotionLight m2056271736;
				ros::serialization::Serializer<msl_actuator_msgs::MotionLight>::read(stream, m2056271736);

				actuator->handleMotionLight(m2056271736);
				break; }
				case 554624761ul: {
//				process_manager::ProcessCommand m554624761;
//				ros::serialization::Serializer<process_manager::ProcessCommand>::read(stream, m554624761);
//				pub554624761.publish<process_manager::ProcessCommand>(m554624761);
				break; }
				case 2772566283ul: {
//				msl_actuator_msgs::VisionRelocTrigger m2772566283;
//				ros::serialization::Serializer<msl_actuator_msgs::VisionRelocTrigger>::read(stream, m2772566283);
//				pub2772566283.publish<msl_actuator_msgs::VisionRelocTrigger>(m2772566283);
				break; }
				case 1028144660ul: {
//				msl_actuator_msgs::MotionBurst m1028144660;
//				ros::serialization::Serializer<msl_actuator_msgs::MotionBurst>::read(stream, m1028144660);
//				pub1028144660.publish<msl_actuator_msgs::MotionBurst>(m1028144660);
				break; }
				case 2802967882ul: {
//				std_msgs::Bool m2802967882;
//				ros::serialization::Serializer<std_msgs::Bool>::read(stream, m2802967882);
//				pub2802967882.publish<std_msgs::Bool>(m2802967882);
				break; }
				case 3134514216ul: {
				msl_actuator_msgs::RawOdometryInfo m3134514216;
				ros::serialization::Serializer<msl_actuator_msgs::RawOdometryInfo>::read(stream, m3134514216);
				actuator->handleRawOdometryInfo(m3134514216);
				break; }
				case 1267609526ul: {
				// CanSub
				msl_actuator_msgs::CanMsg m1267609526;
				ros::serialization::Serializer<msl_actuator_msgs::CanMsg>::read(stream, m1267609526);
				actuator->handleCanSub(m1267609526);

				break; }
				case 217678336ul: {
//				msl_actuator_msgs::CanMsg m217678336;
//				ros::serialization::Serializer<msl_actuator_msgs::CanMsg>::read(stream, m217678336);
//				pub217678336.publish<msl_actuator_msgs::CanMsg>(m217678336);
				break; }
				case 418700403ul: {
//				msl_actuator_msgs::CanMsg m418700403;
//				ros::serialization::Serializer<msl_actuator_msgs::CanMsg>::read(stream, m418700403);
//				pub418700403.publish<msl_actuator_msgs::CanMsg>(m418700403);
				break; }
				case 3391245383ul: {
//				msl_actuator_msgs::CanMsg m3391245383;
//				ros::serialization::Serializer<msl_actuator_msgs::CanMsg>::read(stream, m3391245383);
//				pub3391245383.publish<msl_actuator_msgs::CanMsg>(m3391245383);
				break; }
				case 3455796956ul: {
//				msl_actuator_msgs::IMUData m3455796956;
//				ros::serialization::Serializer<msl_actuator_msgs::IMUData>::read(stream, m3455796956);
//				pub3455796956.publish<msl_actuator_msgs::IMUData>(m3455796956);
				break; }

				default:
					std::cerr << "Cannot find Matching topic:" << id << std::endl;
			}
		}
		catch(std::exception& e) {
			ROS_ERROR_STREAM_THROTTLE(2,"Exception while receiving DDS message:"<<e.what()<< " Discarding message!");
		}

	}
	listenForPacket();
	return;
}
void Proxy::run_udp() {
	io_service.run();
}
