 #include <ros/ros.h>
// #include <visualization_msgs/Marker.h>
#include <marker.h>
 
 int main( int argc, char** argv )
 {
   ros::init(argc, argv, "add_marker");
   ros::NodeHandle n;
   ros::Rate r(1);
   ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
 
   // Set our initial shape type to be a cube
   uint32_t shape = visualization_msgs::Marker::CUBE;
 
   if (ros::ok())
   {
     marker my_marker = marker("my_marker", 0, shape, 5);
     my_marker.SetPosition(3.5, 5.0);
     my_marker.SetScalePercent(0.25);
 
     // Publish the marker
     while (marker_pub.getNumSubscribers() < 1)
     {
       if (!ros::ok())
       {
         return 0;
       }
       ROS_WARN_ONCE("Please create a subscriber to the marker");
       sleep(1);
     }
     marker_pub.publish(my_marker.GetMarker());
     ROS_INFO("Great, the marker add at the first position successfully!");
     ros::Duration(4.0).sleep();
     // my_marker.SetAction(visualization_msgs::Marker::DELETE);
     // marker_pub.publish(my_marker.GetMarker());
     ROS_INFO("Great, the marker hind successfully!");
     ros::Duration(5.0).sleep();

     my_marker = marker("my_marker", 0, shape);
     my_marker.SetPosition(-3.6, 6.0);
     my_marker.SetColor(0.118, 0.565, 1.0);
     my_marker.SetScalePercent(0.25);
//     my_marker.SetMeshResource("homeservice/meshes/RubixCube.dae");
//     my_marker.SetText("Great, the marker add at the second position successfully!");

     marker_pub.publish(my_marker.GetMarker());
     ROS_INFO("Great, the marker add at the second position successfully!");
     ros::Duration(5.0).sleep();
//     r.sleep();
   }
 }