#pragma once
#include "Inamic.h"

class Inamic2 :public Inamic
{
public:
	int aux;
	Polygon2D *poly1, *poly2, *poly3, *poly4;
	Circle2D *cerc;


public:
	Inamic2(float dir, float startX, float startY){
		
		//latime si lungime collision box	
		bxX = 30;
		bxY = 30;

		poly1 = new Polygon2D(Color(1, 0, 1), false);
		poly1->addPoint(Point2D(0, 0));
		poly1->addPoint(Point2D(10, 0));
		poly1->addPoint(Point2D(10, 10));
		parts.push_back(poly1);

		poly2 = new Polygon2D(Color(1, 0, 1), false);
		poly2->addPoint(Point2D(0, 20));
		poly2->addPoint(Point2D(10, 20));
		poly2->addPoint(Point2D(0, 30));
		parts.push_back(poly2);

		poly3 = new Polygon2D(Color(1, 0, 1), false);
		poly3->addPoint(Point2D(20, 20));
		poly3->addPoint(Point2D(20, 30));
		poly3->addPoint(Point2D(30, 30));
		parts.push_back(poly3);

		poly4 = new Polygon2D(Color(1, 0, 1), false);
		poly4->addPoint(Point2D(20, 10));
		poly4->addPoint(Point2D(30, 10));
		poly4->addPoint(Point2D(30, 0));
		parts.push_back(poly4);
		
		cerc = new Circle2D(Point2D(15, 15), 5, Color(1, 0, 1), false);
		parts.push_back(cerc);

		hitbox = new Rectangle2D(Point2D(0, 0), bxX, bxY, Color(0, 1, 0), false);
		calc_centru();
		translate_to(startX, startY);
		directie = dir;
		tip = 1;
		value = 10;

	}
	~Inamic2() {}

};