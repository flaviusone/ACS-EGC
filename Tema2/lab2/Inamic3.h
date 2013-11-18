/*
Autor: Flavius Tirnacop
Grupa: 331CA
Fisier: Inamic3.h
Descriere: Clasa Inamic3 Hexagon
*/
#pragma once
#include "Framework\Point3D.h"
#include "Framework\DrawingWindow.h"
#include "Framework\Object3D.h"
#include "Inamic.h"
#define PI 3.14159265358979323846

class Inamic3 :public Inamic{

public:
	Inamic3(float startX, float startY, float startZ, float enemy_speed){
		// set speed
		speed = enemy_speed;

		//varfurile de jos
		vertices.push_back(new Point3D(n/2, 0, 0));
		vertices.push_back(new Point3D(0, 0, n/2));
		vertices.push_back(new Point3D(n/2, 0, n));
		vertices.push_back(new Point3D(n, 0, n));
		vertices.push_back(new Point3D(3*n/2, 0, n/2));
		vertices.push_back(new Point3D(n, 0, 0));

		//varfurile de sus
		vertices.push_back(new Point3D(n / 2, n, 0));
		vertices.push_back(new Point3D(0, n, n / 2));
		vertices.push_back(new Point3D(n / 2, n, n));
		vertices.push_back(new Point3D(n, n, n));
		vertices.push_back(new Point3D(3 * n / 2, n, n / 2));
		vertices.push_back(new Point3D(n, n, 0));

		//cele 8 fete
		vector <int> contour;

		//fata jos
		contour.clear();
		contour.push_back(0);
		contour.push_back(1);
		contour.push_back(2);
		contour.push_back(3);
		contour.push_back(4);
		contour.push_back(5);
		faces.push_back(new Face(contour));

		//fata sus
		contour.clear();
		contour.push_back(6);
		contour.push_back(7);
		contour.push_back(8);
		contour.push_back(9);
		contour.push_back(10);
		contour.push_back(11);
		faces.push_back(new Face(contour));

		//fata lateral
		contour.clear();
		contour.push_back(0);
		contour.push_back(1);
		contour.push_back(7);
		contour.push_back(6);
		faces.push_back(new Face(contour));

		//fata lateral
		contour.clear();
		contour.push_back(1);
		contour.push_back(2);
		contour.push_back(8);
		contour.push_back(7);
		faces.push_back(new Face(contour));

		//fata lateral
		contour.clear();
		contour.push_back(2);
		contour.push_back(3);
		contour.push_back(9);
		contour.push_back(8);
		faces.push_back(new Face(contour));

		//fata lateral
		contour.clear();
		contour.push_back(3);
		contour.push_back(4);
		contour.push_back(10);
		contour.push_back(9);
		faces.push_back(new Face(contour));

		//fata lateral
		contour.clear();
		contour.push_back(4);
		contour.push_back(5);
		contour.push_back(11);
		contour.push_back(10);
		faces.push_back(new Face(contour));

		//fata lateral
		contour.clear();
		contour.push_back(5);
		contour.push_back(0);
		contour.push_back(6);
		contour.push_back(11);
		faces.push_back(new Face(contour));

		// Create object
		body = new Object3D(vertices, faces, Color(0, 1, 0), false);

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
	~Inamic3(){};


};