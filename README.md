# Human Force Data

First plug in one force sensor, and run the executable in optoforcesensors/sensor1/build.

Plug in the next sensor and run the executable in optoforcesensors/sensor2/build.

It is probable that the files will need to be run multiple times, 
it takes time to register that there is a force sensor attached.

Run the executable in optitrack/bin.
You will likely need to input your IP address.

The force sensor executables may need to be run several times, until they find the connected force sensors.  If running on Linux, you will likely need to run them with sudo.

The data will be written to a csv file in the data folder.
