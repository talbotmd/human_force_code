cd optoforcesensors/sensor2/build/
x-terminal-emulator -e "bash -c 'echo \"Plug in second force sensor before running this\" && sudo ./optoforce_driver'"
cd ../../..

cd optoforcesensors/sensor1/build/
x-terminal-emulator -e "bash -c 'echo \"Run this one first\" && sudo ./optoforce_driver'"
cd ../../..

read -p "Once both sensors are running, press any key to continue..." yn

./optitrack/bin/demo_project