/*
 * a_marker class
 */

#include "marker.h"

// constructor
marker::marker(const char* name, int id, uint32_t type, int duration, const char* frame_id)
{	
    a_marker = visualization_msgs::Marker();
    a_marker.ns = name;
    a_marker.id = id;
    a_marker.type = type;
    a_marker.header.frame_id = frame_id;
    a_marker.header.stamp = ros::Time::now();
    a_marker.lifetime = duration == 0 ? ros::Duration() : ros::Duration(duration);
 
    SetPosition();
    SetOrientation();
    SetColor();
    SetScale();
    SetAction();
}

// destructor
marker::~marker()
{}


void marker::SetPosition(float x, float y, float z)
{
	a_marker.pose.position.x = x;
	a_marker.pose.position.y = y;
	a_marker.pose.position.z = z;
}

void marker::SetOrientation(float x, float y, float z, float w)
{
	a_marker.pose.orientation.x = x;
	a_marker.pose.orientation.y = y;
	a_marker.pose.orientation.z = z;
	a_marker.pose.orientation.w = w;
}

void marker::SetColor(float r, float g, float b, float a)
{
	a_marker.color.r = r;
	a_marker.color.g = g;
	a_marker.color.b = b;
	a_marker.color.a = a;
}

void marker::SetScale(float x, float y, float z)
{
	a_marker.scale.x = x;
	a_marker.scale.y = y;
	a_marker.scale.z = z;
}

void marker::SetScalePercent(float percent)
{
	a_marker.scale.x = a_marker.scale.x * percent;
	a_marker.scale.y = a_marker.scale.y * percent;
	a_marker.scale.z = a_marker.scale.z * percent;
}

void marker::SetMeshResource(std::string resource)
{ 
	a_marker.type = visualization_msgs::Marker::MESH_RESOURCE;
	a_marker.mesh_resource = "package://" + resource; 
}

void marker::SetText(std::string text)
{ 
	a_marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
	a_marker.text = text; 
}