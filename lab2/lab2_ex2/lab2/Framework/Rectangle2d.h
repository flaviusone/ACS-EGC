#pragma once
#include "Object2D.h"

class Rectangle2D:public Object2D
{
public:
	Rectangle2D(Point2D p, float width, float height)
	{
		fill = false;
		color.r = color.b = color.r = 0;
		type = 2;

		//adauga cele patru puncte ale dreptunghiului
		points.push_back(new Point2D(p.x,p.y));
		transf_points.push_back(new Point2D(p.x,p.y));
		Point2D *p2 = new Point2D(); p2->x = p.x + width;  p2->y = p.y;
		points.push_back(p2);
		transf_points.push_back(new Point2D(p2->x,p2->y));
		Point2D *p3 = new Point2D(); p3->x = p2->x; p3->y = p2->y + height;
		points.push_back(p3);
		transf_points.push_back(new Point2D(p3->x,p3->y));
		Point2D *p4 = new Point2D(); p4->x = p.x; p4->y = p.y + height;
		points.push_back(p4);
		transf_points.push_back(new Point2D(p4->x,p4->y));
	}


	Rectangle2D(Point2D p, float width, float height, Color _color, bool _fill)
	{
		fill = _fill;
		color.r = _color.r;
		color.g = _color.g;
		color.b = _color.b;
		type = 2;

		//adauga cele patru puncte ale dreptunghiului
		points.push_back(new Point2D(p.x,p.y));
		transf_points.push_back(new Point2D(p.x,p.y));
		Point2D *p2 = new Point2D(); p2->x = p.x + width;  p2->y = p.y;
		points.push_back(p2);
		transf_points.push_back(new Point2D(p2->x,p2->y));
		Point2D *p3 = new Point2D(); p3->x = p2->x; p3->y = p2->y + height;
		points.push_back(p3);
		transf_points.push_back(new Point2D(p3->x,p3->y));
		Point2D *p4 = new Point2D(); p4->x = p.x; p4->y = p.y + height;
		points.push_back(p4);
		transf_points.push_back(new Point2D(p4->x,p4->y));
	}

	~Rectangle2D() {}

};