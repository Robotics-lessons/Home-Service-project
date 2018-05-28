#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <pick_objects/Notify.h>
#include <visualization_msgs/Marker.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  int start_goal_x = 4.0;
  int start_goal_y = 5.0;
  int end_goal_x = -4.2;
  int end_goal_y = 6.0;

  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  ros::NodeHandle n;
  ros::Publisher notifying_pub = n.advertise<pick_objects::Notify>("notifying", 10);
  

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  pick_objects::Notify notify;
  notify.header.frame_id = "notify";
  notify.header.stamp = ros::Time::now();
  notify.x = start_goal_x;
  notify.y = start_goal_y;
  notify.action = visualization_msgs::Marker::ADD;
  notify.message = "Show a red square object on the map";
  notifying_pub.publish(notify);

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = start_goal_x;
  goal.target_pose.pose.position.y = start_goal_y;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending the 1st goal; x=%g, y=%g, w=%g", goal.target_pose.pose.position.x, goal.target_pose.pose.position.y, goal.target_pose.pose.orientation.w);
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Great, the robot moved the first goal successfully!");
    notify.action = visualization_msgs::Marker::DELETE;
    notify.message = "The robot moved the pick up position successfully!";
    notify.header.stamp = ros::Time::now();
    notifying_pub.publish(notify);
    ROS_INFO("Waiting for 5 sec");
    ros::Duration(5.0).sleep();
    goal.target_pose.pose.position.x = end_goal_x;
    goal.target_pose.pose.position.y = end_goal_y;
    goal.target_pose.pose.orientation.w = 1.0;
    goal.target_pose.header.stamp = ros::Time::now();
    ROS_INFO("Sending the 2nd goal; x=%g, y=%g, w=%g", goal.target_pose.pose.position.x, goal.target_pose.pose.position.y, goal.target_pose.pose.orientation.w);
    ac.sendGoal(goal);
    ac.waitForResult();
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
      ROS_INFO("Great, the robot moved to the second goal successfully!");
      notify.header.stamp = ros::Time::now();
      notify.x = end_goal_x;
      notify.y = end_goal_y;
      notify.action = visualization_msgs::Marker::ADD;
      notify.message = "The robot moved to the drop off position successfully!";
      notifying_pub.publish(notify);
    } else {
      ROS_INFO("The base failed to move forward 1 meter for some reason");
    }
  }
  else {
    ROS_INFO("The base failed to move forward 1 meter for some reason");
  }
 
  return 0;
}
