#!/bin/sh
export ROBOT_INITIAL_POSE="-x -4.6 -y 0.3 -z 0.0 -R 0.0  -P 0.0 -Y 0.0"
xterm -e " roslaunch homeservice homeservice.launch world_file:=$HOME/catkin_ws/src/homeservice/world/homeservice.world " &
sleep 5
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$HOME/catkin_ws/src/homeservice/maps/homeservice.yaml  3d_sensor:=kinect " &
sleep 5
xterm -e " rosrun pick_objects pick_objects "



