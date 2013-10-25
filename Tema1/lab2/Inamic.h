#pragma once
#include "Framework\DrawingWindow.h"
#include "Framework\Object2D.h"


class Inamic
{
public:
	float directie;
	float centrux,centruy;
	//valorile pentru colision box
	float bxX, bxY;
	int tip;
	//partile din care este alcatuit inamicul
	vector <Object2D*> parts;
public:
	Inamic(int tip, float dir, float startX, float startY);
	~Inamic(){}

	// Adauga elementele inamicului la drawingwindow
	void addInamic2D(){
		for (int i = 0; i < parts.size(); i++)
		{
			DrawingWindow::addObject2D(parts[i]);
		}
	}

	// Scoate elmentele inamicului din drawingwindow
	void removeInamic2D(){
		for (int i = 0; i < parts.size(); i++)
		{
			DrawingWindow::removeObject2D(parts[i]);
		}
	}

	//TODO
	//eventuala functie de rotire
	void rotire();

	// Translateaza inamicul la coord specificate
	void translate_to(float X, float Y){
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(X - centrux, Y - centruy);
		for (int i = 0; i < parts.size(); i++){
			Transform2D::applyTransform_o(parts[i]);
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
		for (int i = 0; i < parts.size(); i++){
			for (int j = 0; j < parts[i]->transf_points.size(); j++){
				centrux += parts[i]->transf_points[j]->x;
				centruy += parts[i]->transf_points[j]->y;
			}
			centrux = centrux / parts[i]->transf_points.size();
			centruy = centruy / parts[i]->transf_points.size();
		}
		centrux = centrux / parts.size();
		centruy = centruy / parts.size();
	}
	
	 

};