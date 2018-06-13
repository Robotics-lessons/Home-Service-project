
#include "marker_msg.h"



 marker_msg::marker_msg()
 {
    ros::NodeHandle n;

    notify_sub = n.subscribe("notifying", 100, &marker_msg::notifyCallback, this);
    marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

 	  ros::Rate r(1);
 }

 
 marker_msg::~marker_msg()
 {
 
 }

 void marker_msg::notifyCallback(const pick_objects::Notify::ConstPtr& msg)
 {
    try 
    {
       int action = msg->action;
       std::string message = msg->message;
       float x = msg->x;
       float y = msg->y;
       ROS_INFO("action = %i, x = %f, y = %f, message = %s ", action, x, y, message.c_str());
       marker a_marker = creat_marker(action, x, y);
       publish_marker(a_marker);
    } 
    catch(ros::Exception &e1)
    {
      ROS_ERROR("ROS Exception: %s ", e1.what ());
    }
    catch(std::logic_error &e2)
    {
      ROS_ERROR("Logic Error: %s ", e2.what ());
    }
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
//       my_marker.SetColor(0.118, 0.565, 1.0);
       my_marker.SetScalePercent(0.25);
     return my_marker;
  }
