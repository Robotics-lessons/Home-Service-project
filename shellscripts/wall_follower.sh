#!/bin/sh
##source /opt/ros/kinetic/setup.bash
#export ROBOT_INITIAL_POSE="-x -4.6 -y 0.3 -z 0.0 -R 0.0  -P 0.0 -Y 0.0"
<<<<<<< HEAD
currentPath=$(pwd)
echo $currentPath
xterm -e " roslaunch homeservice homeservice.launch world_file:=$currentPath/../homeservice/world/homeservice.world " &
=======
xterm -e " roslaunch homeservice homeservice.launch world_file:=$HOME/catkin_ws/src/homeservice/world/homeservice.world " &
>>>>>>> 153ab6a3524a442855bc99171e824e74850dabc9
sleep 5
xterm -e " roslaunch homeservice gmapping.launch " &
#sleep 5
xterm -e " roslaunch homeservice wall_follower.launch " 


