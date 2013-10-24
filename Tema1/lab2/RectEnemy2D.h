#pragma once
#include "Framework\Object2D.h"

class RectEnemy2D :public Object2D
{
public:
	RectEnemy2D(Point2D p, float width, float height)
	{
		fill = false;
		color.r = color.b = color.r = 0;
		type = 2;
		
		//adauga cele 8 puncte ale inamicului
		points.push_back(new Point2D(p.x, p.y));
		transf_points.push_back(new Point2D(p.x, p.y));

		Point2D *p2 = new Point2D(); p2->x = p.x + width;  p2->y = p.y;
		points.push_back(p2);
		transf_points.push_back(new Point2D(p2->x, p2->y));
		Point2D *p3 = new Point2D(); p3->x = p2->x; p3->y = p2->y + height;
		points.push_back(p3);
		transf_points.push_back(new Point2D(p3->x, p3->y));
		Point2D *p4 = new Point2D(); p4->x = p.x; p4->y = p.y + height;
		points.push_back(p4);
		transf_points.push_back(new Point2D(p4->x, p4->y));
		Point2D *p5 = new Point2D(); p5->x = p.x + 10;  p5->y = p.y + 10;
		points.push_back(p5);
		transf_points.push_back(new Point2D(p5->x, p5->y));
		Point2D *p6 = new Point2D(); p6->x = p5->x + width; p6->y = p5->y ;
		points.push_back(p6);
		transf_points.push_back(new Point2D(p6->x, p6->y));
		Point2D *p7 = new Point2D(); p7->x = p6->x; p7->y = p6->y + height;
		points.push_back(p7);
		transf_points.push_back(new Point2D(p7->x, p7->y));
		Point2D *p8 = new Point2D(); p8->x = p5->x ; p8->y = p5->y + height;
		points.push_back(p8);
		transf_points.push_back(new Point2D(p8->x, p8->y));
	}

	RectEnemy2D(Point2D p, float width, float height, Color _color, bool _fill)
	{
		fill = _fill;
		color.r = _color.r;
		color.g = _color.g;
		color.b = _color.b;
		type = 4;

		//adauga cele 8 puncte ale inamicului
		points.push_back(new Point2D(p.x, p.y));
		transf_points.push_back(new Point2D(p.x, p.y));

		Point2D *p2 = new Point2D(); p2->x = p.x + width;  p2->y = p.y;
		points.push_back(p2);
		transf_points.push_back(new Point2D(p2->x, p2->y));
		Point2D *p3 = new Point2D(); p3->x = p2->x; p3->y = p2->y + height;
		points.push_back(p3);
		transf_points.push_back(new Point2D(p3->x, p3->y));
		Point2D *p4 = new Point2D(); p4->x = p.x; p4->y = p.y + height;
		points.push_back(p4);
		transf_points.push_back(new Point2D(p4->x, p4->y));
		Point2D *p5 = new Point2D(); p5->x = p.x + 10;  p5->y = p.y + 10;
		points.push_back(p5);
		transf_points.push_back(new Point2D(p5->x, p5->y));
		Point2D *p6 = new Point2D(); p6->x = p5->x + width; p6->y = p5->y;
		points.push_back(p6);
		transf_points.push_back(new Point2D(p6->x, p6->y));
		Point2D *p7 = new Point2D(); p7->x = p6->x; p7->y = p6->y + height;
		points.push_back(p7);
		transf_points.push_back(new Point2D(p7->x, p7->y));
		Point2D *p8 = new Point2D(); p8->x = p5->x; p8->y = p5->y + height;
		points.push_back(p8);
		transf_points.push_back(new Point2D(p8->x, p8->y));
	}

	~RectEnemy2D() {}

};