/*
Autor: Flavius Tirnacop
Grupa: 331CA
Fisier: Inamic3.h
Descriere: Clasa principala pentru inamic tip 3
*/
#pragma once
#include "Inamic.h"

class Inamic3 :public Inamic
{
public:
	int aux;
	Rectangle2D *rect1;
	Polygon2D *poly1;
	Circle2D *cerc;


public:
	Inamic3(float dir, float startX, float startY){

		//latime si lungime collision box	
		bxX = 30;
		bxY = 30;

		//Init patrat
		rect1 = new Rectangle2D(Point2D(0, 0), 30, 30, Color(0.5, 0.5, 0), false);
		parts.push_back(rect1);

		//Init poligon
		poly1 = new Polygon2D(Color(1, 0, 1), false);
		poly1->addPoint(Point2D(0, 15));
		poly1->addPoint(Point2D(15, 30));
		poly1->addPoint(Point2D(30, 15));
		poly1->addPoint(Point2D(15, 0));
		parts.push_back(poly1);

		
		hitbox = new Rectangle2D(Point2D(0, 0), bxX, bxY, Color(0, 1, 0), false);
		calc_centru();
		translate_to(startX, startY);
		directie = dir;
		tip = 3;
		value = 50;

	}
	~Inamic3() {}

};