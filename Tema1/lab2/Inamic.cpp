#include "Inamic.h"


Inamic::Inamic(int tip, float dir, float startX, float startY){
	switch (tip)
	{
	case 0:
		Inamic1(directie, startX, startY);
		break;
	case 1:
		Inamic1(directie, startX, startY);
		break;
	case 2:
		//Inamic3(directie, startX, startY);
		break;
	default:
		Inamic1(directie, startX, startY);
		break;
	}
}

Inamic Inamic::Inamic1(float dir, float startX, float startY){
	this->tip = 0;
	this->directie = dir;

	rectangle1 = new Rectangle2D(Point2D(0, 0), 20, 20, Color(0, 1, 0), false);
	rectangle2 = new Rectangle2D(Point2D(10, 10), 20, 20,Color(0,1,0),false);

	translate_to(startX, startY);

	return *this;
}

void Inamic::translate_to(float startX, float startY){
	printf("translating\n");
	float centru_x, centru_y;
	if (this->tip == 0){
		centru_x = 15;
		centru_y = 15;
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(startX - centru_x, startY - centru_y);
		Transform2D::applyTransform(rectangle1);
		Transform2D::applyTransform(rectangle2);
	}
}

void Inamic::addInamic2D(){
	if (this->tip == 0){
		DrawingWindow::addObject2D(rectangle1);
		DrawingWindow::addObject2D(rectangle2);
	}
	
	return;
}

void Inamic::removeInamic2D(){
	if (this->tip == 0){
		DrawingWindow::removeObject2D(rectangle1);
		DrawingWindow::removeObject2D(rectangle2);
	}
	return;
}
