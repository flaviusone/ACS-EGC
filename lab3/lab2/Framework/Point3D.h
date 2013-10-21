#pragma once
#include "Color.h"

class Point3D
{
public:
	float x,y,z;
	//Color color;

public:
	Point3D()
	{
		x = 0;
		y = 0;
		z = 0;
		//color.r = color.g = color.b = 0;
	}

	Point3D(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
		//color.r = color.g = color.b = 0;
	}

	/* Point3D(float _x, float _y, float _z, Color _color)
	{
		x = _x;
		y = _y;
		z = _z;
		color.r = _color.r;
		color.g = _color.g;
		color.b = _color.b;
	}
	*/

	~Point3D()
	{}

};