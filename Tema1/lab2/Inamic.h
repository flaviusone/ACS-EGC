#pragma once
#include "Framework\DrawingWindow.h"
#include "Framework\Rectangle2d.h"
#include "Framework\Polygon2D.h"
#include "Framework\Circle2D.h"
#include "Framework\Object2D.h"


class Inamic
{
public:
	float	directie,					// Directie de deplasare
			centrux = 0, centruy = 0,	//Centru inamic
			bxX = 0, bxY = 0;			//Limitele pentru collision box

	int tip,	//Tipul inamicului
		value;	//Valoarea acestuia pentru scor

	vector <Object2D*> parts; //partile din care este alcatuit inamicul

	Rectangle2D *hitbox;	//Hitbox-ul inamicului
public:
	Inamic(){}
	Inamic(float dir, float startX, float startY);
	~Inamic(){}

	// Adauga elementele inamicului la drawingwindow
	void addInamic2D(){
		for (int i = 0; i < parts.size(); i++)
			DrawingWindow::addObject2D(parts[i]);
	} 

	// Scoate elmentele inamicului din drawingwindow
	void removeInamic2D(){
		for (int i = 0; i < parts.size(); i++)
			DrawingWindow::removeObject2D(parts[i]);
		DrawingWindow::removeObject2D(hitbox);
	}

	// Translateaza inamicul la coord specificate
	void translate_to(float X, float Y){
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(X  , Y );
		for (int i = 0; i < parts.size(); i++){
			Transform2D::applyTransform(parts[i]);
		}
		Transform2D::applyTransform(hitbox);

	}

	// Translateaza inamicul cu constanta primita
	void translate_with(float X, float Y){
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(X, Y);
		for (int i = 0; i < parts.size(); i++){
			Transform2D::applyTransform_o(parts[i]);
		}
		Transform2D::applyTransform_o(hitbox);
	}
	
	// functie generica care calculeaza centrul obiectului folosind media aritmetica
	void calc_centru(){

		//centrul inamicului este si centrul hitboxului
		centrux = (hitbox->transf_points[0]->x +
			hitbox->transf_points[1]->x +
			hitbox->transf_points[2]->x +
			hitbox->transf_points[3]->x)/4;
		
		centruy = (hitbox->transf_points[0]->y +
			hitbox->transf_points[1]->y +
			hitbox->transf_points[2]->y +
			hitbox->transf_points[3]->y) / 4;
	}
};