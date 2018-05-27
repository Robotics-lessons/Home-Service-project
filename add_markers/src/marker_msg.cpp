
#include "marker_msg.h"


 marker_msg::marker_msg(const char* name)
 {
 	marker_pub = n.advertise<visualization_msgs::Marker>(name, 1);
 	ros::Rate r(1);
 }

 
 marker_msg::~marker_msg()
 {
 
 }

 void marker_msg::notifyCallback(const pick_objects::Notify::ConstPtr& msg)
 {
    int action = msg->action;
    std::string action_name = msg->action_name;
    float x = msg->x;
    float y = msg->y;
    ROS_INFO(" action name = %s, x = %f, y = %f ", action_name.c_str(), x, y);
    marker a_marker = creat_marker(action, x, y);
    publish_marker(a_marker);
 }

 void marker_msg::publish_marker(marker a_marker)
 {
 	// Publish the marker
     while (marker_pub.getNumSubscribers() < 1)
     {
       if (!ros::ok())
       {
         return;
       }
       ROS_WARN_ONCE("Please create a subscriber to the marker");
       sleep(1);
     }
     marker_pub.publish(a_marker.GetMarker());
 }

  marker marker_msg::creat_marker(int action, float x, float y, uint32_t shape)
  { 	 
  	 marker my_marker = marker("my_marker", 0, shape);
  	 my_marker.SetPosition(x, y);
  	 my_marker.SetAction(action);
     my_marker.SetColor(0.118, 0.565, 1.0);
     my_marker.SetScalePercent(0.25);
  }
