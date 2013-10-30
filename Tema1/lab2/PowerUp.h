#pragma once
#include "Inamic.h"

class PowerUp :public Inamic
{
public:
	int aux;
	Circle2D *cerc;

public:
	PowerUp(float dir, float startX, float startY){
		
		//latime si lungime collision box	
		bxX = 30;
		bxY = 30;

		cerc = new Circle2D(Point2D(0, 0), 15, Color(1, 0.11, 0), true);
		parts.push_back(cerc);

		hitbox = new Rectangle2D(Point2D(0, 0), bxX, bxY, Color(0, 1, 0), false);

		calc_centru();
		translate_to(startX, startY);
		directie = dir;
		tip = 4;
		value = 10;

	}
	~PowerUp() {}

};