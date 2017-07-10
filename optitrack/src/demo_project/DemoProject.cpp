#include "DemoProject.h"

#include <iostream>
#include <fstream>

#include <signal.h>
static volatile bool g_runloop = true;
void stop(int) { g_runloop = false; }

// Return true if any elements in the Eigen::MatrixXd are NaN
template<typename Derived>
static inline bool isnan(const Eigen::MatrixBase<Derived>& x) {
	return (x.array() != x.array()).any();
}

using namespace std;

/**
 * DemoProject::readRedisValues()
 * ------------------------------
 * Retrieve all read keys from Redis.
 */
void DemoProject::readRedisValues() {
	// read from Redis current sensor values
	// redis_client_.getEigenMatrixDerivedString(JOINT_ANGLES_KEY, robot->_q);
	// redis_client_.getEigenMatrixDerivedString(JOINT_VELOCITIES_KEY, robot->_dq);

	// Get current simulation timestamp from Redis
	redis_client_.getCommandIs(TIMESTAMP_KEY, redis_buf_);
	t_curr_ = stod(redis_buf_);

}

/**
 * DemoProject::writeRedisValues()
 * -------------------------------
 * Send all write keys to Redis.
 */
void DemoProject::writeRedisValues() {
	// Send end effector position and desired position
	redis_client_.setEigenMatrixDerivedString(EE_POSITION_KEY, x_);
	redis_client_.setEigenMatrixDerivedString(EE_POSITION_DESIRED_KEY, x_des_);

	// Send torques
	redis_client_.setEigenMatrixDerivedString(JOINT_TORQUES_COMMANDED_KEY, command_torques_);
}


/**
 * public DemoProject::initialize()
 * --------------------------------
 * Initialize timer and Redis client
 */
void DemoProject::initialize() {
	// Create a loop timer
	timer_.setLoopFrequency(kControlFreq);   // 1 KHz
	// timer.setThreadHighPriority();  // make timing more accurate. requires running executable as sudo.
	timer_.setCtrlCHandler(stop);    // exit while loop on ctrl-c
	timer_.initializeTimer(kInitializationPause); // 1 ms pause before starting loop

	// Start redis client
	// Make sure redis-server is running at localhost with default port 6379
	redis_client_.serverIs(kRedisServerInfo);

	// Set up optitrack
	optitrack_ = make_unique<OptiTrackClient>();
	// optitrack_->openConnection("10.34.171.10");
	optitrack_->openConnection("10.34.161.81");
	
	// if(!optitrack_->openCsv("../resources/optitrackdata.csv") ) {
	// 	cout << "Failed to open the file" << endl;
	// }

	// Demo usage for OptiTrackClient
	ofstream outputFile;
	outputFile.open("../../data/newoptitrackdata.csv");
	Eigen::VectorXd sensor_force = Eigen::VectorXd::Zero(6);
	Eigen::VectorXd sensor_force2 = Eigen::VectorXd::Zero(6);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	optitrack_->getFrame();
	outputFile << "Timestamp:";
	// for (auto& pos : optitrack_->pos_rigid_bodies_) {
	outputFile << ", "<< "sensor 1 " << ", " << ", " << ", " << ", " << ", ";
	outputFile << ", "<< "sensor 2 " << ", " << ", " << ", " << ", " << ", ";
	for(int i = 0; i < optitrack_->pos_rigid_bodies_.size(); i++) {
		outputFile << ", "<< "body " << i + 1 << ", " << ", " << ", " << ", " << ", " << ", ";

	}
	outputFile << endl;

	while (g_runloop) {
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		if (!optitrack_->getFrame()) {
			// cout << "Its not really working" << endl;
			continue;
		}
		redis_client_.getEigenMatrixDerived("sai2::optoforceSensor::6Dsensor::force", sensor_force);
		redis_client_.getEigenMatrixDerived("sai2::optoforceSensor2::6Dsensor::force", sensor_force2);

		// cout << "Timestamp: " << optitrack_->frameTime() << endl;
		// cout << "Rigid body positions:" << endl;
		outputFile << optitrack_->frameTime() << ", ";

		// double fx, fy;

		Eigen::Matrix3d rotation;

		rotation << 1.0/sqrt(2.0), 1.0/sqrt(2.0), 0,
					-1.0/sqrt(2.0), 1.0/sqrt(2.0), 0,
					0,				0,				1;

		sensor_force.head(3) = rotation * sensor_force.head(3);
		sensor_force.tail(3) = rotation * sensor_force.tail(3);


		// std::cout << sensor_force(0) << ","<< sensor_force(1) << ","<< sensor_force(2) << ","<< sensor_force(3) << ","<< sensor_force(4) << ","<< sensor_force(5) << "," << std::endl;
		// std::cout << sensor_force2(0) << ","<< sensor_force2(1) << ","<< sensor_force2(2) << ","<< sensor_force2(3) << ","<< sensor_force2(4) << ","<< sensor_force2(5) << ",\n" << std::endl;
		
		
		outputFile << sensor_force(0) << ","<< sensor_force(1) << ","<< sensor_force(2) << ","<< sensor_force(3) << ","<< sensor_force(4) << ","<< sensor_force(5) << ",";
		outputFile << sensor_force2(0) << ","<< sensor_force2(1) << ","<< sensor_force2(2) << ","<< sensor_force2(3) << ","<< sensor_force2(4) << ","<< sensor_force2(5) << ",";
		
		for (int i = 0; i < optitrack_->pos_rigid_bodies_.size(); i++) {
			auto& pos = optitrack_->pos_rigid_bodies_[i];
			auto& ori = optitrack_->ori_rigid_bodies_[i];
			// cout << '\t' << pos.transpose() << endl;
			// cout << '\t' << pos(0) << "," << pos(1) << ","<< pos(2) << "," << ori.w() << "," << ori.x() << "," << ori.y() << "," <<ori.z() << endl;

			// outputFile << '\t' << pos.transpose() << endl;
			outputFile << pos(0) << "," << pos(1) << ","<< pos(2) << "," << ori.w() << "," << ori.x() << "," << ori.y() << "," <<ori.z() << ",";
		}
		outputFile << endl;
		// cout << "Force Sensor Output:" << endl;
		// cout << sensor_force.transpose() << endl;
		// cout << sensor_force2.transpose() << endl;
		// cout << "Marker positions:" << endl;
		// outputFile << "Marker positions:" << endl;
		// for (auto& pos : optitrack_->pos_single_markers_) {
		// 	cout << '\t' << pos.transpose() << endl;
		// 	outputFile << '\t' << pos.transpose() << endl;
		// }
		// cout << endl;
		// outputFile << endl;
	}
	optitrack_->closeConnection();
	outputFile.close();


}


int main(int argc, char** argv) {


	// Start controller app
	cout << "Initializing app" <<  endl;
	DemoProject app("robot_name");
	app.initialize();
	cout << "App finished." << endl;
	// app.runLoop();

	return 0;
}


