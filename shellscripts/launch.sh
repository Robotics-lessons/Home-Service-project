#!/bin/sh
source /opt/ros/kinetic/setup.bash
xterm -e " gazebo " &
sleep 5
xterm -e " source /opt/ros/kinetic/setup.bash; roscore" &
sleep 5
echo "Start rviz...."
xterm -e " rosrun rviz rviz"
echo "Done"
