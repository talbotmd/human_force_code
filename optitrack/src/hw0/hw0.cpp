#include "redis/RedisClient.h"
#include "timer/LoopTimer.h"

#include <iostream>
#include <string>

using namespace std;

// Location of URDF files specifying world and robot information
const string world_file = "resources/hw0/world.urdf";
const string robot_file = "resources/hw0/RRPbot.urdf";
const string robot_name = "RRPbot";

// Redis is just a key value store, publish/subscribe is also possible
// The visualizer and simulator will have keys like "cs225a::robot::{ROBOTNAME}::sensors::q"
// You can hardcode the robot name in like below or read them in from cli
// redis keys:
// - write:
const std::string JOINT_ANGLES_KEY  = "cs225a::robot::RRPbot::sensors::q";
const std::string JOINT_VELOCITIES_KEY = "cs225a::robot::RRPbot::sensors::dq";

int main() {
	cout << "Loading URDF world model file: " << world_file << endl;

	// Make sure redis-server is running at localhost with default port 6379
	// start redis client
	HiredisServerInfo info;
	info.hostname_ = "127.0.0.1";
	info.port_ = 6379;
	info.timeout_ = { 1, 500000 }; // 1.5 seconds
	auto redis_client = RedisClient();
	redis_client.serverIs(info);

	ifstream file("../../Downloads/VIK_elb_forward.csv");

	/* 
	Here we use our redis set method to serialize an 'Eigen' vector into a specific Redis Key
	Changing set to get populates the 'Eigen' vector given
	This key is then read by the physics integrator or visualizer to update the system
	*/
	// redis_client.setEigenMatrixDerivedString(JOINT_ANGLES_KEY,robot->_q);
	// redis_client.setEigenMatrixDerivedString(JOINT_VELOCITIES_KEY, robot->_dq);

	// operational space
	std::string op_pos_task_link_name = "link2"; // Link of the "Task" or "End Effector"

	// Position of Task Frame in relation to Link Frame (When using custom E.E. attachment, etc..)
	Eigen::Vector3d op_pos_task_pos_in_link = Eigen::Vector3d(0.0, 0.0, 0.0); 
	
	Eigen::MatrixXd op_pos_task_jacobian(3,dof); // Empty Jacobian Matrix sized to right size
	Eigen::VectorXd g(dof); // Empty Gravity Vector


	cout << g << endl;

	/* 
	Retrieve multiple values of jacobian or M with a for loop of setting robot->_q's, 
	setting redis keys for display update if needed and don't forget robot->updateModel()! 
	We'll have a logger for you later to dump redis values at whatever rate you choose
	*/

	// This function retrives absolute position of Task Frame in Base Frame
	//Eigen::Vector3d initial_position;
	//robot->position(initial_position,op_pos_task_link_name,op_pos_task_pos_in_link);

	// Wait for user input before quit
	int wait;
	cin >> wait;

    return 0;
}

