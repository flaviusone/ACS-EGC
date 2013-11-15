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

};