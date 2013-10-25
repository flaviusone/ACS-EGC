#pragma once
#include "Inamic.h"

class Inamic1:public Inamic
{
public:
	int aux;
	Rectangle2D *rectangle1, *rectangle2;

public:
	Inamic1(float dir, float startX, float startY){
		rectangle1 = new Rectangle2D(Point2D(0, 0), 20, 20, Color(0, 1, 0), false);
		rectangle2 = new Rectangle2D(Point2D(10, 10), 20, 20, Color(0, 1, 0), false);
		parts.push_back(rectangle1);
		parts.push_back(rectangle2);
		calc_centru();
		translate_to(startX, startY);
		directie = dir;
		tip = 1;
	}
	~Inamic1() {}

};