#ifndef DEMO_PROJECT_H
#define DEMO_PROJECT_H

// cs225a includes
#include "redis/RedisClient.h"
#include "timer/LoopTimer.h"
#include "optitrack/OptiTrackClient.h"

// external includes
#include <Eigen/Core>
#include <hiredis/hiredis.h>
// #include <model/ModelInterface.h>

// std includes
#include <string>
#include <thread>

class DemoProject {

public:

	DemoProject(const std::string &robot_name)
	
	{

	}

	/***** Public functions *****/

	void initialize();
	// void runLoop();

protected:

	/***** Constants *****/

	const int kControlFreq = 1000;         // 1 kHz control loop
	const int kInitializationPause = 1e6;  // 1ms pause before starting control loop

	const HiredisServerInfo kRedisServerInfo = {
		"127.0.0.1",  // hostname
		6379,         // port
		{ 1, 500000 } // timeout = 1.5 seconds
	};

	// Redis
	RedisClient redis_client_;
	std::string redis_buf_;

	// Timer
	LoopTimer timer_;
	double t_curr_;
	uint64_t controller_counter_ = 0;

	// OptiTrack
	std::unique_ptr<OptiTrackClient> optitrack_;
};

#endif //DEMO_PROJECT_H
