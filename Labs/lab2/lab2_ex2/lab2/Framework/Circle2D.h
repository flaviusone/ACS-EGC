#pragma once
#include "Object2D.h"
#include <math.h>

class Circle2D:public Object2D
{
	
public:
	Circle2D(Point2D center, float radius)
	{
		color.r = color.b = color.g = 0;
		fill = false;
		type = 3;
		

		//construim lista de puncte tinand cont de centru si raza

		float u;
		float du = 10;
		float u_rad;
		for (u = 0; u <= 360; u+=du)
		{
			Point2D *p = new Point2D();
			u_rad = u * 3.14159 / 180;
			p->x = center.x + radius * cos(u_rad);
			p->y = center.y + radius * sin(u_rad);
			points.push_back(p);
			transf_points.push_back(new Point2D(p->x,p->y));
		}
	}

	Circle2D(Point2D center, float radius, Color _color, bool _fill)
	{
		fill = _fill;
		color.r = _color.r;
		color.g = _color.g;
		color.b = _color.b;
		type = 3;

		//construim lista de puncte tinand cont de centru si raza

		float u;
		float du = 10;
		float u_rad;
		for (u = 0; u < 360; u+=du)
		{
			Point2D *p = new Point2D();
			u_rad = u * 3.14159 / 180;
			p->x = center.x + radius * cos(u_rad);
			p->y = center.y + radius * sin(u_rad);

			
			points.push_back(p);
			transf_points.push_back(new Point2D(p->x,p->y));
		}
	}

	~Circle2D(){}
};