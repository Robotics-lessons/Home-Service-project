# Home Service project

##  Abstract:

Home Service project was implemented with a Robot, Map and virtual object in ROS Gazebo simulation environment. The turtlebot robot, a built map, slam-mapping algorithm, AMCL navigation algorithm and ROS marker were used in it. it simulated a full home service robot capable of navigating to pick up and deliver virtual objects. The result for the simulated robot will be discussed in this article.

## Introduction:

These 7 steps need to complete in this project,:

1. Preparing Catkin Workspace

2. Building a map

3. Testing SLAM

4. Using Wall Follower code to generate a digit map

5. Testing navigation and reaching multiple goals

6. Modeling virtual objects

7. Integrating all 6 steps code into home service package

    

   The final result shows a robot navigating in Rviz  and Gazebo windows with a map.

    <img src="images/Rviz-Gazebo-nav 2018-05-24 13-14-46.png" width="80%" height="70%" title="Rviz and Gazebo windows">




## Background / Tasks

#### Hardware Environment:

PC: HP Omen desktop

CPU: 8 x Intel(R) Core(TM) i7-7700K @4.20GHz

Memory:  64G

Hard disk:  512G SSD

GPU: GTX 1080i

#### Software Environment:

OS: Ubuntu 16.04

ROS: kinetic

Gazebo:  7.0.0

Rviz: 1.12.16

gcc:  5.4.0 

#### Tasks:

1. **Preparing Catkin Workspace**

Creating a catkin_ws workspace.

Installing these packages: [gmapping](http://wiki.ros.org/gmapping), [turtlebot_teleop](http://wiki.ros.org/turtlebot_teleop), [turtlebot_rviz_launchers](http://wiki.ros.org/turtlebot_rviz_launchers), [turtlebot_gazebo](http://wiki.ros.org/turtlebot_gazebo).

Creating a file folders structure as:

<img src="images/project-file-struct.png" width="50%" height="50%" title="file folder structure">



2. **Building a map**

Using **Building Editor** in Gazebo to create a map as:
<img src="images/gazebo-map.png" width="80%" height="70%" title="map">

Save this map as a world format file (homeservice.world) under homeservice/map folder.

3. **Testing SLAM**

Creating a test_slam.sh file to test SLAM manually.

Launch the test_slam.sh file and running the **keyboard_teleop** node, and start controlling the robot.
<img src="images/test_slam.png" width="80%" height="70%" title="map">

4. **Using Wall Follower code to generate a digit map**

This task was automating the process and let the robot follow the walls and autonomously map the environment while avoiding obstacles. To do so, the keyboard teleop node was replaced with a programming wall_follower node.
A wall follower algorithm is a common algorithm that solves mazes. This algorithm is also known as the left-hand rule algorithm or the right-hand rule algorithm depending on which is the project's priority. This wall follower can only solve mazes with connected walls, where the robot is guaranteed to reach the exit of the maze after traversing close to walls.
Here’s the wall follower algorithm(the left-hand one) at a high level:

````
If left is free:
    Turn Left
Else if left is occupied and straight is free:
    Go Straight
Else if left and straight are occupied:
    Turn Right 
Else if left/right/straight are occupied or you crashed:
    Turn 180 degrees

````

This algorithm has a lot of disadvantages because of the restricted space it can operate in. In other words, this algorithm will fail in open or infinitely large environments. Usually, the best algorithms for autonomous mapping are the ones that go in pursuit of undiscovered areas or unknown grid cells.

<img src="images/wall_follower.png" width="100%" height="90%" title="map">

Using ````rosrun map_server map_saver -f homeservice ```` command, the two output map files were saved under homeservice/maps folder.

<img src="images/map-output.png" width="50%" height="50%" title="map">

