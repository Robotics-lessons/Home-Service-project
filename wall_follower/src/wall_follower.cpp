// ROS Libraries
#include "ros/ros.h"
#include "geometry_msgs/Twist.h" // Motor Commands
#include "sensor_msgs/LaserScan.h" // Laser Data
#include "tf/transform_listener.h" // tf Tree

// C++ Libraries
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stack>

#define MOVE_PERCENT 1.0
float move_speed_percent = MOVE_PERCENT;

int act_count = 0;

// ROS Publisher:Motor Commands, Subscriber:Laser Data, and Messages:Laser Messages & Motor Messages
ros::Publisher motor_command_publisher;
ros::Subscriber laser_subscriber;
sensor_msgs::LaserScan laser_msg;
geometry_msgs::Twist motor_command;

// Define the robot direction of movement
typedef enum _ROBOT_MOVEMENT {
    STOP = 0,
    FORWARD,
    BACKWARD,
    TURN_LEFT,
    TURN_RIGHT,
    GO_RIGHT,
    GO_LEFT

} ROBOT_MOVEMENT;

// Define the robot direction of movement message
std::string ROBOT_MOVEMENT_MESSAGES[] = {
    "HALT!",
    "FORWARD!",
    "BACKWARD",
    "TURN_LEFT",
    "TURN_RIGHT",
    "GO_RIGHT",
    "GO_LEFT"

};

bool make_full_scan = false;
int pre_move_type = 0;

int makeTurn(float goal_angle, int rate)
{
    int count = 0;
        motor_command.linear.x = 0.0;
        motor_command.angular.z = -0.5; 
        int total_loop = int(goal_angle * rate * 2);
//        ROS_INFO("total loop = %d ", total_loop);
        while (count < total_loop)
        {
           motor_command_publisher.publish(motor_command);
           ROS_INFO("[ROBOT] turn right count = %d ", count);
           usleep(1000000);
           count++;
 //          ROS_INFO("[ROBOT] turn right count = %d ", count);
        }
//    ROS_INFO("[ROBOT] turn right count = %d ", count);
    return count;
}
// The robot_move function will be called by the laser_callback function each time a laser scan data is received
// This function will accept robot movements and actuate the robot's wheels accordingly
// Keep a low speed for better results
bool robot_move(const int move_type, std::string &msg)
{
    if (move_type == STOP) {
 //       ROS_INFO("[ROBOT] HALT! \n");

        motor_command.angular.z = 0.0;
        motor_command.linear.x = 0.0;
    }

    else if (move_type == FORWARD) {
//        ROS_INFO("[ROBOT] Always FORWARD! \n");
        motor_command.angular.z = 0.0;
        motor_command.linear.x = 0.5 * move_speed_percent;
    }

    else if (move_type == BACKWARD) {
 //       ROS_INFO("[ROBOT] I'm going back! \n");
        motor_command.linear.x = -0.75 * move_speed_percent;
        motor_command.angular.z = 0.0;
    }

    else if (move_type == TURN_LEFT) {
//        ROS_INFO("[ROBOT] I'm turning left! \n");
        motor_command.linear.x = 0.0;
        motor_command.angular.z = 1.0; 
    }

    else if (move_type == TURN_RIGHT) {
//        ROS_INFO("[ROBOT] I'm turning right! \n");
        motor_command.linear.x = 0.0;
        motor_command.angular.z = -1.0; 
    }
    else if (move_type == GO_RIGHT) {
//        ROS_INFO("[ROBOT] I'm goin right! \n");
        motor_command.linear.x = 0.25; 
        motor_command.angular.z = -0.25; 
    }
    else if (move_type == GO_LEFT) {
 //       ROS_INFO("[ROBOT] I'm goin left! \n");
        motor_command.linear.x = 0.25;
        motor_command.angular.z = 0.25; 
    }
    else {
        ROS_INFO("[ROBOT_MOVE] Move type wrong! \n");
        return false;
    }
    act_count++;
    if (pre_move_type != move_type) {
       std::string outmsg = ROBOT_MOVEMENT_MESSAGES[move_type];
       if (pre_move_type == TURN_LEFT && move_type == GO_RIGHT && act_count == 1) {
          make_full_scan = true;
       }
       if (pre_move_type == GO_RIGHT && act_count > 40 && make_full_scan) {
          make_full_scan = false;
          outmsg = "TURN RIGHT 360 DEGREES";
          makeTurn(M_PI, 3);
       }
       ROS_INFO("[ROBOT] %s, pre act count = %d ", outmsg.c_str(), act_count);
       if (strlen(msg.c_str()) > 0) {
          ROS_INFO("%s /n", msg.c_str());
       }

       act_count = 0;
    }
    //Publish motor commands to the robot and wait 10ms
    motor_command_publisher.publish(motor_command);
    usleep(10);
    return true;
}

bool following_wall = false;
bool thats_a_door = false;
bool crashed = false;


// The laser_callback function will be called each time a laser scan data is received
void laser_callback(const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
    int move_type = 0;
 //   std::string msg_str;
    std::string outstr = "";
//    msg_str.resize(1024);
    // Read and process laser scan values
    laser_msg = *scan_msg;
    std::vector<float> laser_ranges;
    laser_ranges = laser_msg.ranges;
    size_t range_size = laser_ranges.size();
    float left_side = 0.0, right_side = 0.0;
    float range_min = laser_msg.range_max, range_max = laser_msg.range_min;
    int nan_count = 0;
    for (size_t i = 0; i < range_size; i++) {
        if (laser_ranges[i] < range_min) {
            range_min = laser_ranges[i];
        }

        if (std::isnan(laser_ranges[i])) {
            nan_count++;
        }
        if (i < range_size / 4) {
            if (laser_ranges[i] > range_max) {
                range_max = laser_ranges[i];
            }
        }

        if (i > range_size / 2) {
            left_side += laser_ranges[i];
        }
        else {
            right_side += laser_ranges[i];
        }
    }

    // Check if the robot has crashed into a wall
    if (nan_count > (range_size * 0.9) || laser_ranges[range_size / 2] < 0.25) {
        crashed = true;
    }
    else {
        crashed = false;
    }

    // Assign movements to a robot that still did not crash 
    if (!crashed) {

        if (range_min <= 0.5 && !thats_a_door) {
            following_wall = true;
            crashed = false;
 //           robot_move(STOP);

            if (left_side >= right_side) {
                move_type = TURN_RIGHT;
//                robot_move(TURN_RIGHT);
            }
            else {
                move_type = TURN_LEFT;
//               robot_move(TURN_LEFT);
            }
            robot_move(move_type, outstr);
            
        }
        else {
//               ROS_INFO("[ROBOT] Dam son: %f , following_wall = %d \n", range_max, following_wall);
            std::string msg_str;
            msg_str.resize(1024);
            sprintf(&msg_str[0], "[ROBOT] Dam son: %f , following_wall = %d  ", range_max, following_wall);
            msg_str.resize( strlen( msg_str.data() ) );
            outstr = msg_str;
//          robot_move(STOP);
            if (following_wall) {
                if (range_max >= 2.0) {
                    thats_a_door = true;
                    following_wall = false;
                    //robot_move(TURN_RIGHT);
//                    ROS_INFO("[ROBOT] I am following wall and my max range > 2.0 Range Max: %f \n", range_max);
                    std::string msg_str1;
                    msg_str1.resize(1024);
                    sprintf(&msg_str1[0], "// [ROBOT] I am following wall and my max range > 2.0 Range Max: %f \n", range_max);
                    msg_str1.resize( strlen( msg_str1.data() ) + 1 );
                    outstr += msg_str1;
                }
            }
            if (thats_a_door) {
                if (laser_ranges[0] <= 0.5) {
                    thats_a_door = false;
                }
                else {
//                    robot_move(GO_RIGHT);
                    move_type = GO_RIGHT;
                }
//               ROS_INFO("[ROBOT] I am goin' right!: thats_a_door = %d \n", thats_a_door);
                std::string msg_str2;
                msg_str2.resize(1024);
                sprintf(&msg_str2[0], "// [ROBOT] I am goin' right!: thats_a_door = %d \n", thats_a_door);
                msg_str2.resize( strlen( msg_str2.data() ) + 1 );
                outstr += msg_str2;
            }
            else {
                move_type = FORWARD;
//                robot_move(FORWARD);
            }
            robot_move(move_type, outstr);
        }
    }
    // Robot should go backward since it crashed into a wall
    else {
        move_type = BACKWARD;
        robot_move(move_type, outstr);
    }
    pre_move_type = move_type;
}

int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "node");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;

    n.param<float>("/wall_follower/move_speed_percent", move_speed_percent, MOVE_PERCENT);
    ROS_INFO("move_speed_percent = %f \n", move_speed_percent);

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 100
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 100);

    // Subscribe to the /scan topic and call the laser_callback function
    laser_subscriber = n.subscribe("/scan", 1000, laser_callback);

    // Enter an infinite loop where the laser_callback function will be called when new laser messages arrive
    ros::Duration time_between_ros_wakeups(0.001);
    while (ros::ok()) {
        ros::spinOnce();
        time_between_ros_wakeups.sleep();
    }

    return 0;
}
