# cs225a
Repository for class resources: CS225a experimental robotics

## Automatic Installation Instructions (for Ubuntu and Mac only)
1. If you have a Mac, install Brew (https://brew.sh/). If you have Ubuntu, install git (sudo apt install git)

2. Clone this repository

   ```git clone https://github.com/tmigimatsu/cs225a-dist.git cs225a.git```

3. Build the cs225a applications

   ```sh make.sh```

## Manual Installation Instructions (for any Linux distro or Mac)
1. Install Brew for Mac (https://brew.sh/) or have Ubuntu installed or any other distro with the following packages. Also install git (sudo apt-get install git). Windows will have to dualboot ubuntu or install a VM.

2. Install Cmake

   Linux: ```sudo apt-get install cmake```
   
   Mac: ```brew install cmake```
   
3. Install Eigen

   Linux:```sudo apt-get install libeigen3-dev```
    
   Mac:```brew install eigen```
    
4. Install TinyXML
 
   Linux:```sudo apt-get install libtinyxml2-dev```
    
   Mac:```brew install tinyxml2```

5. Install JsonCPP

   Linux:```sudo apt-get install libjsoncpp-dev```
    
   Mac:```brew install jsoncpp```
   
6. Install HiRedis Client

   Linux:```sudo apt-get install libhiredis-dev```
    
   Mac:```brew install hiredis```
   
7. Install Redis-Server

   Linux:```sudo apt-get install redis-server```
    
   Mac:```brew install redis```
   
8. Install Yaml-CPP

   Linux:```sudo apt-get install libyaml-cpp-dev```
    
   Mac:```brew install yaml```

9. Clone This Repo
    ```
    sh make.sh
    ```
10. Clone the NatNetLinux repo in external

## Post-Installation

1. Inside bin, you will find visualizer, simulator, and hw0
   ```
   ./hw0 &
   ./visualizer &
   ```
   Note this opens up the applications in the background, use "jobs" to see currently running jobs and "fg" or "bg" to foreground next job or background next job
   
1.5 You can also run the script inside the bin folder "run_hw0.sh" to run hw0. Ctrl-c on the shell to quit.
   
2. Read the source code of hw0 inside src/hw0/hw0.cpp and the URDF file src/RRPbot.urdf and src/world.urdf to understand what is happening inside the robot code and how the simple robot is described both kinematically and graphically.
