#pragma once
#include "Framework\Point3D.h"
#include "Framework\DrawingWindow.h"
#include "Framework\Object3D.h"
#define PI 3.14159265358979323846
#define stanga 1
#define dreapta -1
class Player{

public:
	vector<Object3D*> parts;
	vector <Point3D*> vertices;
	vector <Face*> faces;

	float n = 100;
	float speed = 5;
	float tx = 0, ty = 0, tz = 0;
	float centrux, centruy, centruz;
	float counterL = 0, counterR = 0,counter = 0;
	int last_dir = 0;
	float unghi = PI / 12;
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

				
		

		tx += DrawingWindow::width / 2 - n/2 ;
		tz -= DrawingWindow::height / 2 - n/2;
		set_perspecitve();
		Transform3D::translateMatrix(tx, ty, tz);
		for (int i = 0; i < parts.size(); i++){
			Transform3D::applyTransform(parts[i]);
		}

	}

	~Player(){};

	void set_perspecitve(){
		Transform3D::loadIdentityProjectionMatrix();
		Transform3D::perspectiveProjectionMatrix(DrawingWindow::width / 2, DrawingWindow::height / 2 + 400, 600);
		//Transform3D::perspectiveProjectionMatrix(tx,-tz,600);
		for (int i = 0; i < parts.size(); i++){
			Transform3D::applyTransform(parts[i]);
		}
	}

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

	void rotate_stanga(){
		if (counter < unghi)
			counter += 0.01;
		Transform3D::translateMatrix(-n / 2, -n / 2, -n / 2);
		Transform3D::rotateMatrixOz(counter);
		Transform3D::translateMatrix(n / 2, n / 2, n / 2);
		last_dir = stanga;
	}


	void rotate_dreapta(){
		if (counter > -unghi)
			counter -= 0.01;
		Transform3D::translateMatrix(-n / 2, -n / 2, -n / 2);
		Transform3D::rotateMatrixOz(counter);
		Transform3D::translateMatrix(n / 2, n / 2, n / 2);
		last_dir = dreapta;
	}

	void move_right(){
		tx += speed;
		Transform3D::loadIdentityModelMatrix();
		rotate_dreapta();
		Transform3D::translateMatrix(tx, ty, tz);
		for (int i = 0; i < parts.size(); i++){
			Transform3D::applyTransform(parts[i]);
		}
	}

	void move_left(){
		tx -= speed;
		Transform3D::loadIdentityModelMatrix();
		rotate_stanga();
		Transform3D::translateMatrix(tx,ty,tz);
		for (int i = 0; i < parts.size(); i++){
			Transform3D::applyTransform(parts[i]);
		}
	}

	void set_straight(){
		Transform3D::loadIdentityModelMatrix();

		if (counter > 0)
			rotate_dreapta();
		else if (counter < 0)
			rotate_stanga();
		
		/*Transform3D::translateMatrix(-n / 2, -n / 2, -n / 2);
		Transform3D::rotateMatrixOz(counter * last_dir);
		Transform3D::translateMatrix(n / 2, n / 2, n / 2);*/
		Transform3D::translateMatrix(tx, ty, tz);
		for (int i = 0; i < parts.size(); i++){
			Transform3D::applyTransform(parts[i]);
		}
	}

	void move_up(){
		tz -= speed;
		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(tx, ty, tz);
		for (int i = 0; i < parts.size(); i++){
			Transform3D::applyTransform(parts[i]);
		}
	}

	void move_down(){
		tz += speed;
		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(tx, ty, tz);
		for (int i = 0; i < parts.size(); i++){
			Transform3D::applyTransform(parts[i]);
		}
	}

	void calc_centru(){
		centrux = 0; centruy = 0; centruz = 0;
		int numar_puncte = 0;
		for (int i = 0; i < parts.size(); i++){
			for (int j = 0; j < parts[i]->transf_vertices.size(); j++){
				centrux += parts[i]->transf_vertices[j]->x;
				centruy += parts[i]->transf_vertices[j]->y;
				centruz += parts[i]->transf_vertices[j]->z;
				numar_puncte++;
			}
		}
		centrux /= numar_puncte;
		centruy /= numar_puncte;
		centruz /= numar_puncte;

	}
	



};