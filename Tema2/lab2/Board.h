/*
Autor: Flavius Tirnacop
Grupa: 331CA
Fisier: Board.h
Descriere: Clasa Board pentru chenar
*/
#pragma once
#include "Framework\Point3D.h"
#include "Framework\DrawingWindow.h"
#include "Framework\Object3D.h"
#define PI 3.14159265358979323846
class Board{

public:
	vector<Object3D*> parts;
	vector <Point3D*> vertices;
	vector <Face*> faces;
	Object3D *chenar;
	float w, h;							// lungime latime Drawingwindow
	float unghi = PI / 12;				// unghi maxim de rotatie
	float centrux, centruy, centruz;	// centrul obiectului
	float counter = 0;					// auxiliar rotatii
public:
	Board(){

		w = DrawingWindow::width;
		h = DrawingWindow::height;

		// Adauga puncte chenar sosea
		vertices.push_back(new Point3D(0, 0, 200));
		vertices.push_back(new Point3D( w, 0, 200));
		vertices.push_back(new Point3D(5 * w, 0, -30 * w));
		vertices.push_back(new Point3D(-4 * w, 0, -30 * w));


		vector <int> contour;
		//fata jos
		contour.clear();
		contour.push_back(0);
		contour.push_back(1);
		contour.push_back(2);
		contour.push_back(3);
		faces.push_back(new Face(contour));

		chenar = new Object3D(vertices, faces, Color(1, 1, 1), false);

		DrawingWindow::addObject3D(chenar);

		calc_centru();
		set_perspective();
	}
	~Board(){};
	// Seteaza perspectiva
	void set_perspective(){
		Transform3D::loadIdentityProjectionMatrix();
		Transform3D::perspectiveProjectionMatrix(DrawingWindow::width / 2, DrawingWindow::height / 2 + 400, 600);
		Transform3D::applyTransform(chenar);
	}

	void rotate_stanga(){
		if (counter < unghi)
			counter += 0.01;
		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(-centrux, -centruy, -centruz);
		Transform3D::rotateMatrixOz(counter);
		Transform3D::translateMatrix(centrux, centruy, centruz);
		Transform3D::applyTransform(chenar);
		
	}


	void rotate_dreapta(){
		if (counter > -unghi)
			counter -= 0.01;
		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(-centrux, -centruy, -centruz);
		Transform3D::rotateMatrixOz(counter);
		Transform3D::translateMatrix(centrux, centruy, centruz);
		Transform3D::applyTransform(chenar);
		
	}

	void set_straight(){
		Transform3D::loadIdentityModelMatrix();
		if (counter > 0.01)
			rotate_dreapta();
		else if (counter < -0.01)
			rotate_stanga();
		Transform3D::applyTransform(chenar);
	}	

	void calc_centru(){
		centrux = 0; centruy = 0; centruz = 0;
		int numar_puncte = 0;
		for (int j = 0; j < chenar->vertices.size(); j++){
			centrux += chenar->vertices[j]->x;
			centruy += chenar->vertices[j]->y;
			centruz += chenar->vertices[j]->z;
			numar_puncte++;
		}
		centrux /= numar_puncte;
		centruy /= numar_puncte;
		centruz /= numar_puncte;	
	}





};