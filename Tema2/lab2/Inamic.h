#pragma once
#include "Framework\Point3D.h"
#include "Framework\DrawingWindow.h"
#include "Framework\Object3D.h"
#include "Framework\Transform3D.h"
#define PI 3.14159265358979323846
#define stanga 1
#define dreapta -1

class Inamic{
public:
	vector <Point3D*> vertices;
	vector <Face*> faces;
	Object3D* body;
	float n = 100;
	float speed = 5;
	float tx = 0, ty = 0, tz = 0;
	float centrux, centruy, centruz;
	float counterL = 0, counterR = 0, counter = 0;
	int last_dir = 0;
	float unghi = PI / 12;

public:
	Inamic(){};
	Inamic(float startX, float startY,float startZ);
	~Inamic(){};

	void addInamic3D(){
		DrawingWindow::addObject3D(body);
	}
	void removeInamic3D(){
		DrawingWindow::removeObject3D(body);
	}

	void rotate_stanga(){
		if (counter < unghi)
			counter += 0.01;
		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(-centrux, -centruy, -centruz);
		Transform3D::rotateMatrixOz(counter);
		Transform3D::translateMatrix(centrux, centruy, centruz);
		Transform3D::translateMatrix(tx, ty, tz);
		Transform3D::applyTransform(body);
	}


	void rotate_dreapta(){
		if (counter > -unghi)
			counter -= 0.01;
		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(-centrux, -centruy, -centruz);
		Transform3D::rotateMatrixOz(counter);
		Transform3D::translateMatrix(centrux, centruy, centruz);
		Transform3D::translateMatrix(tx, ty, tz);
		Transform3D::applyTransform(body);
	}

	void set_straight(){
		//Transform3D::loadIdentityModelMatrix();
		if (counter > 0.01)
			rotate_dreapta();
		else if (counter < -0.01)
			rotate_stanga();
		//Transform3D::translateMatrix(tx, ty, tz);
		//Transform3D::applyTransform(body);
	}
	
	void calc_centru(){
		centrux = 0; centruy = 0; centruz = 0;
		int numar_puncte = 0;
		for (int j = 0; j < body->vertices.size(); j++){
			centrux += body->vertices[j]->x;
			centruy += body->vertices[j]->y;
			centruz += body->vertices[j]->z;
			numar_puncte++;
		}
		centrux /= numar_puncte;
		centruy /= numar_puncte;
		centruz /= numar_puncte;
	}

};