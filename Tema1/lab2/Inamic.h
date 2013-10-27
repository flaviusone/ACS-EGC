#pragma once
#include "Framework\DrawingWindow.h"
#include "Framework\Rectangle2d.h"
#include "Framework\Polygon2D.h"
#include "Framework\Circle2D.h"
#include "Framework\Object2D.h"


class Inamic
{
public:
	float directie;
	float centrux=0,centruy=0;
	//valorile pentru colision box
	float bxX, bxY;
	int tip;
	//partile din care este alcatuit inamicul
	vector <Object2D*> parts;
public:
	Inamic(){}
	Inamic(float dir, float startX, float startY);
	~Inamic(){}

	void setCollisionBox(){
		float minX = 10000,minY = 10000;
		float maxX = -10000, maxY = -10000;
		for (int i = 0; i < parts.size(); i++){
			for (int j = 0; j < parts[i]->transf_points.size(); j++){
				if (parts[i]->transf_points[j]->x < minX)
					minX = parts[i]->transf_points[j]->x;
				if (parts[i]->transf_points[j]->x > maxX)
					minX = parts[i]->transf_points[j]->x;
				if (parts[i]->transf_points[j]->y < minY)
					minX = parts[i]->transf_points[j]->y;
				if (parts[i]->transf_points[j]->y < maxX)
					minX = parts[i]->transf_points[j]->y;
			}
		}
		bxX = maxX - minX;
		bxY = maxY - minY;
	}

	// Adauga elementele inamicului la drawingwindow
	void addInamic2D(){
		for (int i = 0; i < parts.size(); i++)
			DrawingWindow::addObject2D(parts[i]);
	}

	// Scoate elmentele inamicului din drawingwindow
	void removeInamic2D(){
		for (int i = 0; i < parts.size(); i++)
			DrawingWindow::removeObject2D(parts[i]);
	}

	//TODO
	//eventuala functie de rotire
	void rotire();

	// Translateaza inamicul la coord specificate
	void translate_to(float X, float Y){
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(X  , Y );
		for (int i = 0; i < parts.size(); i++){
			Transform2D::applyTransform(parts[i]);
		}

	}

	// Translateaza inamicul cu constanta primita
	void translate_with(float X, float Y){
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(X, Y);
		for (int i = 0; i < parts.size(); i++){
			Transform2D::applyTransform_o(parts[i]);
		}
	}
	
	// functie generica care calculeaza centrul obiectului folosind media aritmetica
	void calc_centru(){
		int counter=0;
		for (int i = 0; i < parts.size(); i++){
			for (int j = 0; j < parts[i]->transf_points.size(); j++){
				centrux += parts[i]->transf_points[j]->x;
				centruy += parts[i]->transf_points[j]->y;
				counter++;
			}
		}
		centrux /= counter;
		centruy /= counter;
	}
	
	 

};