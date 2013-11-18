#pragma once
#include "Framework\Point3D.h"
#include "Framework\DrawingWindow.h"
#include "Framework\Object3D.h"
#include "Framework\Transform3D.h"
#define PI 3.14159265358979323846
#define stanga 1
#define dreapta -1
#define rotate_speed 0.01
class Inamic{
public:
	vector <Point3D*> vertices;
	vector <Face*> faces;
	Object3D* body;
	float n = 100;
	float speed = 10;
	float tx = 0, ty = 0, tz = 0;
	float centrux, centruy, centruz;
	float counterL = 0, counterR = 0, counter = 0;
	float unghi = PI / 12;
	float raza = 0;
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
			counter += rotate_speed;
		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(0, -centruy, -centruz);
		Transform3D::rotateMatrixOz(counter);
		Transform3D::translateMatrix(0, centruy, centruz);
		Transform3D::translateMatrix(tx, ty, tz);
		Transform3D::applyTransform(body);
	}


	void rotate_dreapta(){
		if (counter > -unghi)
			counter -= rotate_speed;
		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(0, -centruy, -centruz);
		Transform3D::rotateMatrixOz(counter);
		Transform3D::translateMatrix(0, centruy, centruz);
		Transform3D::translateMatrix(tx, ty, tz);
		Transform3D::applyTransform(body);
	}

	void set_straight(){
		//Transform3D::loadIdentityModelMatrix();
		if (counter > rotate_speed)
			rotate_dreapta();
		else if (counter < -rotate_speed)
			rotate_stanga();
		//Transform3D::translateMatrix(tx, ty, tz);
		//Transform3D::applyTransform(body);
	}

	void move_down(){
		tz += speed;
		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(-centrux, -centruy, -centruz);
		Transform3D::rotateMatrixOz(counter);
		Transform3D::translateMatrix(centrux, centruy, centruz);
		Transform3D::translateMatrix(tx, ty, tz);
		Transform3D::applyTransform(body);
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