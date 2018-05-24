#!/bin/sh
##source /opt/ros/kinetic/setup.bash
export ROBOT_INITIAL_POSE="-x 3.0 -y -1.2 -z 0.0 -R 0.0  -P 0.0 -Y 0.0"
xterm -e " roslaunch homeservice homeservice.launch world_file:=$HOME/catkin_ws/src/homeservice/world/homeservice.world " &
sleep 5
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$HOME/catkin_ws/src/homeservice/maps/homeservice.yaml  3d_sensor:=kinect " &



