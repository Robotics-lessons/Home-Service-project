#include <ros/ros.h>
// #include <visualization_msgs/Marker.h>
#include <marker.h>
#include <marker_msg.h>
#include <string.h>

 int main( int argc, char** argv )
 {
   ros::init(argc, argv, "add_marker");
   marker_msg marker_message;
   
   if (ros::ok())
   {
     ROS_INFO(" ROS is ready to run ");
   }

   ros::spin();
   return 0;
 }