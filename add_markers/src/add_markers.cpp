#include <ros/ros.h>
// #include <visualization_msgs/Marker.h>
#include <marker.h>
#include <marker_msg.h>
#include <string.h>

 int main( int argc, char** argv )
 {
   ros::init(argc, argv, "add_marker");
   // Create a marker_msg class which includes publisher and subscriber callback function
   marker_msg marker_message;
   
   if (ros::ok())
   {
      ROS_INFO(" ROS is ready to run ");
   }
   // Wait for next subscribe notify message
   ros::spin();
   return 0;
 }