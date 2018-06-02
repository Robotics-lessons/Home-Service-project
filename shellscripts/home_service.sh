#!/bin/sh
#export ROBOT_INITIAL_POSE="-x -4.6 -y 0.3 -z 0.0 -R 0.0  -P 0.0 -Y 0.0"
currentPath=$(pwd)
echo $currentPath
xterm -e " roslaunch homeservice homeservice.launch world_file:=$currentPath/../homeservice/world/homeservice.world " &
sleep 5
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$currentPath/../homeservice/maps/homeservice.yaml  3d_sensor:=kinect " &
sleep 5
xterm -e " rosrun add_markers add_markers " &
sleep 5
xterm -e " roslaunch homeservice pick_objects.launch "



