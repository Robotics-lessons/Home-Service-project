/*
 * http://github.com/yangnie
 */

#ifndef __MARKER_MSG_H_
#define __MARKER_MSG_H_


#include <marker.h>
#include <string.h>
#include <pick_objects/Notify.h>
#include <ros/ros.h>

 /**
 * A marker message class.
 */
class marker_msg
{
public:
	/**
	 * Constructor
	 */
    marker_msg();
	/**
	 * Destructor
	 */
	virtual ~marker_msg();

	/**
	 * Notify callback function
	 */
	virtual void notifyCallback(const pick_objects::Notify::ConstPtr& msg);

	/**
	 * Publish a marker
	 */
	virtual marker creat_marker(int action, float x = 0.0, float y = 0.0, uint32_t shape = visualization_msgs::Marker::CUBE);

	/**
	 * Publish a marker
	 */
	virtual void publish_marker(marker a_marker);

private:
//        visualization_msgs::Marker a_marker;
        ros::Publisher marker_pub;
        ros::Subscriber notify_sub;
   
};


#endif