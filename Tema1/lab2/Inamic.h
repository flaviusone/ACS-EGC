#pragma once
#include "Framework\DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"

class Inamic
{
public:
	float directie;
	float centru;
	//valorile pentru colision box
	float bx1, bx2, by1, by2;	
	int tip;
	Rectangle2D *rectangle1;
	Rectangle2D *rectangle2;
public:
	Inamic(int tip, float dir, float startX, float startY);
	Inamic Inamic1(float dir, float startX, float startY);
//	Inamic Inamic2(float dir, float startX, float startY);
//	Inamic Inamic3(float dir, float startX, float startY);
	void addInamic2D();
	void removeInamic2D();
	void translate_to(float startX, float startY);


};