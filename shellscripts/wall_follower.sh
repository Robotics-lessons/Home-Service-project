#!/bin/sh
##source /opt/ros/kinetic/setup.bash

xterm -e " roslaunch homeservice homeservice.launch world_file:=$HOME/catkin_ws/src/homeservice/world/homeservice.world " &
sleep 5
xterm -e " roslaunch homeservice gmapping.launch " &
#sleep 5
xterm -e " rosrun wall_follower wall_follower " &


