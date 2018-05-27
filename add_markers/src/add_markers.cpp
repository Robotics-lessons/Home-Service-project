#include <ros/ros.h>
// #include <visualization_msgs/Marker.h>
#include <marker.h>
#include <marker_msg.h>
#include <string.h>
#include <pick_objects/Notify.h>
 


 int main( int argc, char** argv )
 {
   ros::init(argc, argv, "add_marker");
   ros::NodeHandle n;

   marker_msg m_msg = marker_msg("visualization_marker");

//   pick_objects::Notify notify;
 
   if (ros::ok())
   {
     ros::Subscriber notify_sub = n.subscribe("notifying", 100, &marker_msg::notifyCallback, &m_msg);
//      marker_pub.publish(my_marker.GetMarker());
//      ROS_INFO("Great, the marker add at the first position successfully!");
//      ros::Duration(4.0).sleep();
//      // my_marker.SetAction(visualization_msgs::Marker::DELETE);
//      // marker_pub.publish(my_marker.GetMarker());
//      ROS_INFO("Great, the marker hind successfully!");
//      ros::Duration(5.0).sleep();

//      my_marker = marker("my_marker", 0, shape);
//      my_marker.SetPosition(-3.6, 6.0);
//      my_marker.SetColor(0.118, 0.565, 1.0);
//      my_marker.SetScalePercent(0.25);
// //     my_marker.SetMeshResource("homeservice/meshes/RubixCube.dae");
// //     my_marker.SetText("Great, the marker add at the second position successfully!");

//      marker_pub.publish(my_marker.GetMarker());
//      ROS_INFO("Great, the marker add at the second position successfully!");
//      ros::Duration(5.0).sleep();
//     r.sleep();
   }
   ros::spin();
   return 0;
 }