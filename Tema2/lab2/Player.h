/*
Autor: Flavius Tirnacop
Grupa: 331CA
Fisier: Player.h
Descriere: Clasa Player
*/

#pragma once
#include "Framework\Point3D.h"
#include "Framework\DrawingWindow.h"
#include "Framework\Object3D.h"
#include "Inamic.h"
#define PI 3.14159265358979323846
#define coef_pereti 100

class Player{
public:
	vector<Object3D*> parts;
	vector <Point3D*> vertices;
	vector <Face*> faces;

	float n = 100;						// pentru constructie player
	float speed = 10;					// viteza miscare laterale
	float enemy_speed = 10;				// viteza inaintare
	float tx = 0.0, ty = 0.0, tz = 0.0;	// folosite la translatie
	float centrux, centruy, centruz;	// coordonate centru
	
	float counterL = 0, counterR = 0,counter = 0; // folosite la rotatia pe OZ
	int lives = 3;								  // numar de vieti
	float unghi = PI / 12;						  // unghi maxim de rotatie player
	float raza = 70;							  // raza coliziune
	float distanta_parcursa = 0;				  //folosit la scor
	
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
		tz -= DrawingWindow::height / 2 - 2*n;

		// Setez perspectiva
		set_perspecitve();

		// Il translatez la pozitia de inceput
		Transform3D::translateMatrix(tx, ty, tz);
		for (int i = 0; i < parts.size(); i++)
			Transform3D::applyTransform(parts[i]);
	}

	~Player(){};

	// Seteaza perspectiva
	void set_perspecitve(){
		Transform3D::loadIdentityProjectionMatrix();
		Transform3D::perspectiveProjectionMatrix(DrawingWindow::width / 2, DrawingWindow::height / 2 + 400, 600);
		for (int i = 0; i < parts.size(); i++)
			Transform3D::applyTransform(parts[i]);
	}

	// Adauga obiect la visual
	void addPlayer3D(){
		for (int i = 0; i < parts.size(); i++)
			DrawingWindow::addObject3D(parts[i]);
	}

	// Scoate obiect de la visual
	void removePlayer3D(){
		for (int i = 0; i < parts.size(); i++)
			DrawingWindow::removeObject3D(parts[i]);
	}

	void rotate_stanga(){
		if (counter < unghi)
			counter += 0.01;
		Transform3D::translateMatrix(-n / 2, -n / 2, -n / 2);
		Transform3D::rotateMatrixOz(counter);
		Transform3D::translateMatrix(n / 2, n / 2, n / 2);
	}


	void rotate_dreapta(){
		if (counter > -unghi)
			counter -= 0.01;
		Transform3D::translateMatrix(-n / 2, -n / 2, -n / 2);
		Transform3D::rotateMatrixOz(counter);
		Transform3D::translateMatrix(n / 2, n / 2, n / 2);
	}

	void move_right(){
		tx += speed;

		// Daca am ajuns la margine nu mai avansez
		if ((tx + n / 2) > DrawingWindow::width - coef_pereti)
			tx -= speed;
		
		Transform3D::loadIdentityModelMatrix();
		rotate_dreapta();
		Transform3D::translateMatrix(tx, ty, tz);
		for (int i = 0; i < parts.size(); i++){
			Transform3D::applyTransform(parts[i]);
		}
	}

	void move_left(){
		tx -= speed;
		if ((tx - n/2) < 0  )
			tx += speed;
		Transform3D::loadIdentityModelMatrix();
		rotate_stanga();
		Transform3D::translateMatrix(tx,ty,tz);
		for (int i = 0; i < parts.size(); i++){
			Transform3D::applyTransform(parts[i]);
		}
	}

	void set_straight(){
		Transform3D::loadIdentityModelMatrix();

		if (counter > 0.01)
			rotate_dreapta();
		else if (counter < -0.01)
			rotate_stanga();
		
		Transform3D::translateMatrix(tx, ty, tz);
		for (int i = 0; i < parts.size(); i++){
			Transform3D::applyTransform(parts[i]);
		}
	}

	// Neutilizat
	// Muta jucatorul in susul ecranului
	void move_up(){
		tz -= speed;
		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(tx, ty, tz);
		for (int i = 0; i < parts.size(); i++)
			Transform3D::applyTransform(parts[i]);
	}

	// Neutilizat
	// Muta jucatorul in josul ecranului
	void move_down(){
		tz += speed;
		Transform3D::loadIdentityModelMatrix();
		Transform3D::translateMatrix(tx, ty, tz);
		for (int i = 0; i < parts.size(); i++)
			Transform3D::applyTransform(parts[i]);
	}

	// Calculeaza centrul in functie de punctele initiale de spawn
	void calc_centru(){
		centrux = 0; centruy = 0; centruz = 0;
		int numar_puncte = 0;
		for (int i = 0; i < parts.size(); i++)
			for (int j = 0; j < parts[i]->transf_vertices.size(); j++){
				centrux += parts[i]->vertices[j]->x;
				centruy += parts[i]->vertices[j]->y;
				centruz += parts[i]->vertices[j]->z;
				numar_puncte++;
			}
		centrux /= numar_puncte; centruy /= numar_puncte; centruz /= numar_puncte;

	}
	
	// Calculeaza distanta euclidiana si stableste daca 2 obiecte se lovesc
	int enemy_check_collision(Inamic *inamic){
		calc_centru();
		inamic->calc_centru();
		float	centrux_t = centrux + tx,
				centruy_t = centruy + ty,
				centruz_t = centruz + tz;
		float	inamic_centrux_t = inamic->centrux + inamic->tx,
				inamic_centruy_t = inamic->centruy + inamic->ty,
				inamic_centruz_t = inamic->centruz + inamic->tz;
		float distanta_euclidiana = sqrt(
			pow((centrux_t - inamic_centrux_t),2) +
			pow((centruy_t - inamic_centruy_t),2) +
			pow((centruz_t - inamic_centruz_t),2));
		if (distanta_euclidiana < inamic->raza + raza)
			return 1;
		
		return 0;
	}

	// Updateaza distanta parcursa de jucator
	void update_socre(){
		distanta_parcursa += enemy_speed/300;
	}
};