/*
 * http://github.com/yangnie
 */

#ifndef __MARKER_H_
#define __MARKER_H_


#include <visualization_msgs/Marker.h>
#include <string>

/**
 * A marker wrap class.
 */
class marker
{
public:
	/**
	 * Constructor
	 */
    marker(const char* name, int id, uint32_t type, int duration = 0, const char* frame_id = "map");
	/**
	 * Destructor
	 */
	virtual ~marker();

	/**
	 * Set marker position x, y, z
	 * Default values are zero
	 */
	virtual void SetPosition(float x = 0.0, float y = 0.0, float z = 0.0);

	/**
	 * Set marker orientation x, y, z, w
	 * Default values are zero, w is one
	 */
	virtual void SetOrientation(float x = 0.0, float y = 0.0, float z = 0.0, float w = 1.0);

	/**
	 * Set marker color r, g, b, a
	 * Default color value is glod
	 */
	virtual void SetColor(float r = 1.0, float g = 0.843, float b = 0.0, float a = 1.0);

	/**
	 * Set marker scale x, y, z
	 * Default values are one
	 */
	virtual void SetScale(float x = 1.0, float y = 1.0, float z = 1.0);

	/**
	 * Set marker scale percentage
	 * Default values are one
	 */
	virtual void SetScalePercent(float percent = 1.0);

	/**
	 * SetAction: actions are ADD, DELETE, DELETEALL
	 */
	virtual void SetAction(int action = visualization_msgs::Marker::ADD) 
          { a_marker.action = action; }

    /**
	 * SetMeshResource: pass mesh resource path and file name
	 */
	virtual void SetMeshResource(std::string resource); 

    /**
	 * SetText: pass test string
	 */
	virtual void SetText(std::string text); 


	/**
	 * GetMarker: Return a marker object
	 */
	virtual visualization_msgs::Marker GetMarker() 
          { return a_marker; }

	/**
 	 * IsType: Check marker type
	 */
	bool IsType(uint32_t type ) const 
          { return (a_marker.type == type); }

private:
        visualization_msgs::Marker a_marker;
   
};


#endif
