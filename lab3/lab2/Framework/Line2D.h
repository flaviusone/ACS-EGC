#pragma once
#include "Object2D.h"

class Line2D:public Object2D
{
public:
	Line2D(Point2D p1, Point2D p2)
	{
		color.r = color.b = color.g = 0;
		type = 1;

		//adaug punctele la lista de puncte
		points.push_back(new Point2D(p1.x,p1.y));
		points.push_back(new Point2D(p2.x,p2.y));

		transf_points.push_back(new Point2D(p1.x,p1.y));
		transf_points.push_back(new Point2D(p2.x,p2.y));
	}

	Line2D(Point2D p1, Point2D p2, Color _color)
	{
		type = 1;
		color.r = _color.r;
		color.g = _color.g;
		color.b = _color.b;

		points.push_back(new Point2D(p1.x,p1.y));
		points.push_back(new Point2D(p2.x,p2.y));

		transf_points.push_back(new Point2D(p1.x,p1.y));
		transf_points.push_back(new Point2D(p2.x,p2.y));
	}

	~Line2D(){}

};