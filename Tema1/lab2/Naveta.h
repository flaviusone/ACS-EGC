#pragma once
#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"

class Naveta{

public:
	Circle2D *cerc_naveta;
	Polygon2D *poly_naveta, *burghiu;

	float	centru_burghiu_x,
			centru_burghiu_y,
			directie = 0,
			viteza = 2,		//Viteaza la care se ajunge
			viteza_aux = 0; //Viteza actuala
	bool	burghiu_on = false, 
			laser_on = false;
	int chenar_x, // Dimensiunile chenarului cadrului
		chenar_y;
	float centru_x=0, centru_y=0;
public:

	//Main constructor
	Naveta(float centrux , float centruy,int chenarx,int chenary){
		
		centru_x = centrux;
		centru_y = centruy;

		cerc_naveta = new Circle2D(Point2D(centru_x, centru_y), 30, Color(255, 0, 0), false);				


		//updatez detalii chenar
		chenar_x = chenarx;
		chenar_y = chenary;

		//adaug naveta
		poly_naveta = new Polygon2D(Color(255, 0, 0), false);
		poly_naveta->addPoint(Point2D(centru_x - 20, centru_y));
		poly_naveta->addPoint(Point2D(centru_x, centru_y + 25));
		poly_naveta->addPoint(Point2D(centru_x + 20, centru_y + 5));
		poly_naveta->addPoint(Point2D(centru_x, centru_y + 15));
		poly_naveta->addPoint(Point2D(centru_x - 10, centru_y));
		poly_naveta->addPoint(Point2D(centru_x, centru_y - 15));
		poly_naveta->addPoint(Point2D(centru_x + 20, centru_y - 5));
		poly_naveta->addPoint(Point2D(centru_x, centru_y - 25));

		//temp values
		float y = 25, x = 80;

		//adaug burghiul
		burghiu = new Polygon2D(Color(255, 0, 0), true);
		burghiu->addPoint(Point2D(centru_x + 30, centru_y + y));
		burghiu->addPoint(Point2D(centru_x + 30 + x / 4, centru_y + 3 * y / 4));
		burghiu->addPoint(Point2D(centru_x + 30 + x / 2, centru_y + y / 2));
		burghiu->addPoint(Point2D(centru_x + 30 + 3 * x / 4 , centru_y + y / 4));
		burghiu->addPoint(Point2D(centru_x + 110, centru_y));
		burghiu->addPoint(Point2D(centru_x + 30 + 3 * x / 4 , centru_y - y / 4));
		burghiu->addPoint(Point2D(centru_x + 30 + x / 2, centru_y - y / 2));
		burghiu->addPoint(Point2D(centru_x + 30 + x / 4, centru_y - 3 * y / 4));
		burghiu->addPoint(Point2D(centru_x + 30, centru_y - 25));

		calcCentru();


	}
	
	//translateaza naveta cu deplasament x y
	void translate(float x, float y){
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(x, y);
		Transform2D::applyTransform_o(cerc_naveta);
		Transform2D::applyTransform_o(poly_naveta);
		Transform2D::applyTransform_o(burghiu);
	}


	//roteste nava
	void rotate(int param){
		centru_x = 0, centru_y = 0;

		float unghi = 0.02;
		if (param != 0) unghi = -unghi;

		//updatam directia actuala a navei
		directie += unghi;

		//calcul centru poligon
		for (int i = 0; i < poly_naveta->points.size(); i++)
		{
			centru_x = centru_x + poly_naveta->transf_points[i]->x;
			centru_y = centru_y + poly_naveta->transf_points[i]->y;
		}
		centru_x = centru_x / 8;
		centru_y = centru_y / 8;

		//rotirea navei
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(-centru_x, -centru_y);
		Transform2D::rotateMatrix(unghi);
		Transform2D::translateMatrix(centru_x, centru_y);
		Transform2D::applyTransform_o(poly_naveta);
		Transform2D::applyTransform_o(burghiu);

	}

	//muta naveta inainte
	void move_straight(float viteza_aux){
		removeNaveta2D();

		translate(viteza_aux*cos(directie), viteza_aux*sin(directie));
		verifica_ecran();
		addNaveta2D();
	}

	//verifica daca am iesit din ecran
	void verifica_ecran(){
		while (true){
			if ((cerc_naveta->transf_points[0]->x - 60) < 6){
				//mut inapoi unde era inainte de mutare
				translate(-viteza_aux*cos(directie), 0);
				//mut fix pe margine
				translate(-(cerc_naveta->transf_points[0]->x - 60 - 6), 0);
			}
			else
			if ((cerc_naveta->transf_points[0]->x) > chenar_x + 4){
				//mut inapoi unde era inainte de mutare
				translate(-viteza_aux*cos(directie), 0);
				//mut fix pe margine
				translate(chenar_x - cerc_naveta->transf_points[0]->x + 4, 0);
			}
			else
			if ((cerc_naveta->transf_points[0]->y - 30) < 6){
				//mut inapoi unde era inainte de mutare
				translate(0, -viteza_aux*sin(directie));
				//mut fix pe margine
				translate(0, -(cerc_naveta->transf_points[0]->y - 30 - 6));
			}
			else
			if ((cerc_naveta->transf_points[0]->y + 30) > chenar_y + 3){
				//mut inapoi unde era inainte de mutare
				translate(0, -viteza_aux*sin(directie));
				//mut fix pe margine
				translate(0, chenar_y - cerc_naveta->transf_points[0]->y - 30 + 3);
			}
			else break;
		}
	}

	//adauga nava la drawingwindow
	void addNaveta2D(){
		DrawingWindow::addObject2D(poly_naveta);
		DrawingWindow::addObject2D(cerc_naveta);
	}

	//adauga nava la drawingwindow
	void removeNaveta2D(){
		DrawingWindow::removeObject2D(poly_naveta);
		DrawingWindow::removeObject2D(cerc_naveta);
	}
	// Activeaza burghiu
	void activateBurghiu(){
		DrawingWindow::addObject2D(burghiu);

	}

	//Dezactiveaza burghiu
	void deactivateBurghiu(){
		DrawingWindow::removeObject2D(burghiu);
	}
	
	//Calculeaza centrul navei si centrul burghiului
	void calcCentru(){
		centru_x = 0;
		centru_y = 0;
		for (int i = 0; i < poly_naveta->transf_points.size(); i++){
			centru_x += poly_naveta->transf_points[i]->x;
			centru_y += poly_naveta->transf_points[i]->y;
		}
		centru_x = centru_x / 8;
		centru_y = centru_y / 8;

		
		//calculeaza centrul burghiului
		centru_burghiu_x = 0, centru_burghiu_y = 0;
		for (int i = 0; i < burghiu->transf_points.size(); i++){
			centru_burghiu_x += burghiu->transf_points[i]->x;
			centru_burghiu_y += burghiu->transf_points[i]->y;
		}
		centru_burghiu_x /= burghiu->transf_points.size();
		centru_burghiu_y /= burghiu->transf_points.size();
	}

	// Verifica coliziune inamic cu burghiu
	void check_collision(vector <Inamic*> *inamici,int *life,int *scor ,clock_t *old_t){

		for (int i = 0; i < (*inamici).size(); i++){
			(*inamici)[i]->calc_centru();
			for (int j = 0; j < cerc_naveta->transf_points.size(); j += 2)
			{
				float punct_x = cerc_naveta->transf_points[j]->x;
				float punct_y = cerc_naveta->transf_points[j]->y;

				if (punct_x < (*inamici)[i]->hitbox->transf_points[1]->x &&
					punct_x >(*inamici)[i]->hitbox->transf_points[0]->x &&
					punct_y < (*inamici)[i]->hitbox->transf_points[3]->y &&
					punct_y >(*inamici)[i]->hitbox->transf_points[0]->y){
						(*inamici)[i]->removeInamic2D();
						Inamic *temp = (*inamici)[i];
						(*inamici).erase((*inamici).begin() + i);
						delete temp;
						i--;
						(*life)--;
						return;
				}

			}
			// Verifica coliziune cu Burghiul
			if (burghiu_on){
				(*inamici)[i]->calc_centru();
				for (int j = 0; j < burghiu->transf_points.size(); j++)
				{
					float punct_x = burghiu->transf_points[j]->x;
					float punct_y = burghiu->transf_points[j]->y;

					if (punct_x < (*inamici)[i]->hitbox->transf_points[1]->x &&
						punct_x >(*inamici)[i]->hitbox->transf_points[0]->x &&
						punct_y < (*inamici)[i]->hitbox->transf_points[3]->y &&
						punct_y >(*inamici)[i]->hitbox->transf_points[0]->y){

							if ((*inamici)[i]->tip == 4){
								(*old_t) = clock();
								laser_on = true;
							}

							//update scor
							(*scor) += (*inamici)[i]->value;

							//scot inamic din window
							(*inamici)[i]->removeInamic2D();

							//salvez pt delete
							Inamic *temp = (*inamici)[i];
							(*inamici).erase((*inamici).begin() + i);
							delete temp;

							//dec i 
							i--;
							break;
					}
				}
			}
		}

		return;
	}

};

