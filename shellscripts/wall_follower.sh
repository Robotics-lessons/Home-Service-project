#!/bin/sh
##source /opt/ros/kinetic/setup.bash
#export ROBOT_INITIAL_POSE="-x -4.6 -y 0.3 -z 0.0 -R 0.0  -P 0.0 -Y 0.0"
xterm -e " roslaunch homeservice homeservice.launch world_file:=$HOME/catkin_ws/src/homeservice/world/homeservice.world " &
sleep 5
xterm -e " roslaunch homeservice gmapping.launch " &
#sleep 5
xterm -e " rosrun wall_follower wall_follower " &


