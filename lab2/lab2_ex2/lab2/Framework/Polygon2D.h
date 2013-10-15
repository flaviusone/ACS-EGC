#pragma once
#include "Object2D.h"

using namespace std;

class Polygon2D:public Object2D
{

public:
	Polygon2D()
	{
		color.r = color.b = color.g = 0;
		fill = false;
		type = 4;
	}


	Polygon2D(Color _color, bool _fill)
	{
		color.r = _color.r;
		color.g = _color.g;
		color.b = _color.b;

		fill = _fill;
		type = 4;
	}

	~Polygon2D() {}

	void addPoint(Point2D p)
	{
		points.push_back(new Point2D(p.x,p.y));
		transf_points.push_back(new Point2D(p.x,p.y));
	}

};