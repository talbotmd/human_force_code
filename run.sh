cd optoforcesensors/sensor1/build/
# x-terminal-emulator -e "bash -c 'echo \"Run this one first\" && sudo ./optoforce_driver'"
# cd ../../..
x-terminal-emulator -e "bash -c 'echo \"Run this second, with the round force sensor\";
while true; do
	sudo ./optoforce_driver
done
'"
cd ../../..

cd optoforcesensors/sensor2/build/
x-terminal-emulator -e "bash -c 'echo \"Run this first, with the square sensor\";
while true; do
	sudo ./optoforce_driver
done
'"
cd ../../..

read -p "Once both sensors are running, press any key to continue..." yn

cd optitrack/bin
./demo_project
cd ../..