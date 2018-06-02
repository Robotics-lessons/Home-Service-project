#!/bin/sh
##source /opt/ros/kinetic/setup.bash
currentPath=$(pwd)
echo $currentPath
xterm -e " roslaunch homeservice homeservice.launch world_file:=$currentPath/../homeservice/world/homeservice.world " &
sleep 5
xterm -e " roslaunch homeservice gmapping.launch " &
#sleep 5
xterm -e " roslaunch turtlebot_teleop keyboard_teleop.launch " &


