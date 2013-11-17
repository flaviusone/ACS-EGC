#pragma once
#include "Framework\Point3D.h"
#include "Framework\DrawingWindow.h"
#include "Framework\Object3D.h"
#include "Inamic.h"
#define PI 3.14159265358979323846
#define stanga 1
#define dreapta -1

class Inamic1 :public Inamic{
public: 
	int nothing;
public:
	Inamic1(float startX, float startY,float startZ){
		//varfurile de jos
		vertices.push_back(new Point3D(0, 0, 0));
		vertices.push_back(new Point3D(n, 0, 0));
		vertices.push_back(new Point3D(n, 0, n));
		vertices.push_back(new Point3D(0, 0, n));
		//varfurile de sus
		vertices.push_back(new Point3D(0, n, 0));
		vertices.push_back(new Point3D(n, n, 0));
		vertices.push_back(new Point3D(n, n, n));
		vertices.push_back(new Point3D(0, n, n));

		//cele 6 fete
		vector <int> contour;
		//fata jos
		contour.clear();
		contour.push_back(0);
		contour.push_back(1);
		contour.push_back(2);
		contour.push_back(3);
		faces.push_back(new Face(contour));
		//fata sus
		contour.clear();
		contour.push_back(4);
		contour.push_back(5);
		contour.push_back(6);
		contour.push_back(7);
		faces.push_back(new Face(contour));
		//fata fata
		contour.clear();
		contour.push_back(0);
		contour.push_back(1);
		contour.push_back(5);
		contour.push_back(4);
		faces.push_back(new Face(contour));
		//fata dreapta
		contour.clear();
		contour.push_back(1);
		contour.push_back(2);
		contour.push_back(6);
		contour.push_back(5);
		faces.push_back(new Face(contour));
		//fata spate
		contour.clear();
		contour.push_back(2);
		contour.push_back(3);
		contour.push_back(7);
		contour.push_back(6);
		faces.push_back(new Face(contour));
		//fata stanga
		contour.clear();
		contour.push_back(3);
		contour.push_back(0);
		contour.push_back(4);
		contour.push_back(7);
		faces.push_back(new Face(contour));

		// Create object
		body = new Object3D(vertices, faces, Color(1, 0.75, 0), false);

		// Set center position
		calc_centru();

		// Seteaza raza collision
		raza = 70;

		// Translate
		tx += startX;
		ty += startY;
		tz += startZ;
		Transform3D::translateMatrix(tx, ty, tz);
		Transform3D::applyTransform(body);
		// Add to visual
		DrawingWindow::addObject3D(body);


	}
	~Inamic1(){};

	
};