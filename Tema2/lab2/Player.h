#pragma once
#include "Framework\Point3D.h"
#include "Framework\DrawingWindow.h"
#include "Framework\Object3D.h"

class Player{

public:
	vector<Object3D*> parts;
	vector <Point3D*> vertices;
	vector <Face*> faces;

	int n = 1;
	int speed = 0.1;
public:
	Player(){
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

		Object3D* mainpart = new Object3D(vertices, faces, Color(1, 0, 0), false);
		parts.push_back(mainpart);
	}

	~Player(){};

	void addPlayer3D(){
		for (int i = 0; i < parts.size(); i++){
			DrawingWindow::addObject3D(parts[i]);
		}
	}

	void removePlayer3D(){
		for (int i = 0; i < parts.size(); i++){
			DrawingWindow::removeObject3D(parts[i]);
		}
	}

	void move_right(){
		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(speed, 0, 0);
		for (int i = 0; i < parts.size(); i++){
			Transform3D::applyTransform(parts[i]);
		}
	}


	



};