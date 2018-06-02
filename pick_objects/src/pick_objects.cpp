#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <pick_objects/Notify.h>
#include <visualization_msgs/Marker.h>
#include <string>
#include <stdlib.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

void notyfyPublish(float x, float y, int action, pick_objects::Notify &notify, std::string msg, ros::Publisher &pub)
{
   notify.header.stamp = ros::Time::now();
   notify.x = x;
   notify.y = y;
   notify.action = action;
   notify.message = msg;
   pub.publish(notify);
}

void goalPublish(float x, float y, float w, move_base_msgs::MoveBaseGoal &goal, MoveBaseClient &ac)
{
  goal.target_pose.header.stamp = ros::Time::now();
  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;
  goal.target_pose.pose.orientation.w = w;
  ROS_INFO("Sending the 1st goal; x=%g, y=%g, w=%g \n", x, y, w);
  ac.sendGoal(goal);  
}

template <typename T>
std::string NumberToString(T pNumber)
{
   std::ostringstream oOStrStream;
   oOStrStream << pNumber;
 return oOStrStream.str();
}

int main(int argc, char** argv){
  float start_goal_x = 0.0;
  float start_goal_y = 5.0;
  float end_goal_x = -4.2;
  float end_goal_y = 6.0;
  std::string str = "none";
  bool loop = true;
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

  
  move_base_msgs::MoveBaseGoal goal;
  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";

  int i = 1;

  while(loop) {

     std::string key = "/pick_object/run_" + NumberToString(i);
     ROS_INFO("yaml key = %s", key.c_str());
     if (!ros::param::has(key)) {
        break;
     }
     n.param<float>(key + "/start_point/x", start_goal_x, 4.0);
     n.param<float>(key + "/start_point/y", start_goal_y, 5.0);
     n.param<float>(key + "/end_point/x", end_goal_x, 4.0);
     n.param<float>(key + "/end_point/y", end_goal_y, 5.0);   
       
     notyfyPublish(start_goal_x, start_goal_y, visualization_msgs::Marker::ADD, notify,"Show a red square object on the map", notifying_pub);

     goalPublish(start_goal_x, start_goal_y, 1.0, goal, ac);
     // Wait an infinite time for the results
     ac.waitForResult();

     // Check if the robot reached its goal
     if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
     {
       ROS_INFO("Great, the robot moved the first goal successfully! \n");
       notyfyPublish(start_goal_x, start_goal_y, visualization_msgs::Marker::DELETE, notify,"The robot moved the pick up position successfully!", notifying_pub);

       ROS_INFO("Waiting for 5 sec \n");
       ros::Duration(5.0).sleep();

       goalPublish(end_goal_x, end_goal_y, 1.0, goal, ac);
       ac.waitForResult();
       if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
         ROS_INFO("Great, the robot moved to the second goal successfully! \n");
         notyfyPublish(end_goal_x, end_goal_y, visualization_msgs::Marker::ADD, notify,"The robot moved to the drop off position successfully!", notifying_pub);

       } else {
         ROS_INFO("The base failed to move forward 1 meter for some reason");
       }
     }
     else {
       ROS_INFO("The base failed to move forward 1 meter for some reason");
     }
     ROS_INFO("Waiting for 6 sec, do next run \n");
     ros::Duration(6.0).sleep();

     i++;
  }
  return 0;
}
