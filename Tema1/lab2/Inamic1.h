#pragma once
#include "Inamic.h"

class Inamic1:public Inamic
{
public:
	Rectangle2D *rectangle1, *rectangle2;

public:
	Inamic1(float dir, float startX, float startY){

		rectangle1 = new Rectangle2D(Point2D(0, 0), 20, 20, Color(0, 1, 0), false);
		rectangle2 = new Rectangle2D(Point2D(10, 10), 20, 20, Color(0, 1, 0), false);
		
		//latime si lungime collision box	
		bxX = 30; 	bxY = 30;

		//Initializare hitbox
		hitbox = new Rectangle2D(Point2D(0, 0), bxX, bxY, Color(0, 1, 0), false);

		//Adauga la vector de obiecte
		parts.push_back(rectangle1);
		parts.push_back(rectangle2);

		//Seteaza centrul
		calc_centru();

		//Muta la pozitia de start
		translate_to(startX, startY);

		//Seteaza directie tip valoare scor
		directie = dir;
		tip = 1;
		value = 10;
	}
	~Inamic1() {}

};