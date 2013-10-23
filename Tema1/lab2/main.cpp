#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include <iostream>
#include <windows.h>


#define PI 3.14159265358979323846

using namespace std;

int chenar_x, chenar_y;
Visual2D *visual;
Rectangle2D *chenar_alb;
Circle2D *cerc_naveta;
Polygon2D *poly_naveta;
Text *score,*modifying_score,*nolives;
float directie = 0;
float viteza = 20;	

//Constructie naveta
void init_naveta_spatiala(){
	float centru_x = DrawingWindow::width / 2;
	float centru_y = DrawingWindow::height / 2;

	//adaug cercul
	cerc_naveta = new Circle2D(Point2D(centru_x, centru_y), 30, Color(255, 0, 0), false);
	
	//adaug naveta
	poly_naveta = new Polygon2D(Color(255, 0, 0), false);
	poly_naveta->addPoint(Point2D(centru_x - 20, centru_y));
	poly_naveta->addPoint(Point2D(centru_x, centru_y + 25));
	poly_naveta->addPoint(Point2D(centru_x + 20, centru_y + 5));
	poly_naveta->addPoint(Point2D(centru_x , centru_y + 15));
	poly_naveta->addPoint(Point2D(centru_x - 10, centru_y));
	poly_naveta->addPoint(Point2D(centru_x , centru_y - 15));
	poly_naveta->addPoint(Point2D(centru_x + 20, centru_y - 5));
	poly_naveta->addPoint(Point2D(centru_x, centru_y - 25));

	DrawingWindow::addObject2D(poly_naveta);
	DrawingWindow::addObject2D(cerc_naveta);

	return;
}

//Initializari principale
void init_principale(){
	chenar_x = DrawingWindow::width - 20;
	chenar_y = DrawingWindow::height - 20;

	//creeam context vizual
	visual = new Visual2D(0, 0, DrawingWindow::width, DrawingWindow::height, 0, 0, DrawingWindow::width, DrawingWindow::height);
	DrawingWindow::addVisual2D(visual);

	//creeam chenar alb
	chenar_alb = new Rectangle2D(Point2D(5, 5), chenar_x, chenar_y, Color(1, 1, 1), false);
	DrawingWindow::addObject2D(chenar_alb);

	//adaugam text SCORE
	score = new Text("SCORE", Point2D(DrawingWindow::width / 2 - 40.0f, DrawingWindow::height - 50.0f), Color(0, 1, 0), BITMAP_TIMES_ROMAN_24);
	DrawingWindow::addText(score);

	//adaugam modifying score
	modifying_score = new Text("000000", Point2D(DrawingWindow::width / 2 - 40.0f, DrawingWindow::height - 80.0f), Color(0, 1, 0), BITMAP_TIMES_ROMAN_24);
	DrawingWindow::addText(modifying_score);

}

void translate_object_o(float x, float y,Object2D *ob){
	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(x, y);
	Transform2D::applyTransform_o(ob);
}

void translate_naveta(float x, float y){
	translate_object_o(x, y, poly_naveta);
	translate_object_o(x, y, cerc_naveta);
}

void verifica_ecran(){
	while (true){
		if ((cerc_naveta->transf_points[0]->x - 60) < 6){
			//mut inapoi unde era inainte de mutare
			translate_naveta(-viteza*cos(directie), 0); 
			//mut fix pe margine
			translate_naveta(- (cerc_naveta->transf_points[0]->x - 60 - 6), 0); 
		}else
		if ((cerc_naveta->transf_points[0]->x) > chenar_x+4){
			//mut inapoi unde era inainte de mutare
			translate_naveta(-viteza*cos(directie), 0);
			//mut fix pe margine
			translate_naveta(chenar_x - cerc_naveta->transf_points[0]->x+4, 0);
		}else
		if ((cerc_naveta->transf_points[0]->y - 30) < 6){
			//mut inapoi unde era inainte de mutare
			translate_naveta(0, -viteza*sin(directie));
			//mut fix pe margine
			translate_naveta(0, -(cerc_naveta->transf_points[0]->y -30 - 6));
		}else
		if ((cerc_naveta->transf_points[0]->y + 30) > chenar_y+3){
			//mut inapoi unde era inainte de mutare
			translate_naveta(0, -viteza*sin(directie));
			//mut fix pe margine
			translate_naveta(0, chenar_y - cerc_naveta->transf_points[0]->y - 30 + 3);
		}else break;
	}
}


void move_straight(){
	DrawingWindow::removeObject2D(poly_naveta);
	DrawingWindow::removeObject2D(cerc_naveta);

	translate_naveta(viteza*cos(directie), viteza*sin(directie));
	
	verifica_ecran();

	DrawingWindow::addObject2D(poly_naveta);
	DrawingWindow::addObject2D(cerc_naveta);
}

void rotate(int param){
	float centru_x = 0, centru_y = 0;

	//if param 0 -> rotate_right
	//else -> rotate_left
	float unghi = PI / 12;
	//float unghi = 0.1;
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
}

void DrawingWindow::init()	
{
	//init chenar, scor, visual2d
	init_principale();

	//creeam naveta spatiala si o adaugam la centru
	init_naveta_spatiala();	
}


//functia care permite animatia
void DrawingWindow::onIdle()
{
	//verifica_ecran();
	//For debug purposes
	char buffer[50];
	sprintf(buffer, "Tema1 v1.0 alpha");
	//adaugam modifying score
	DrawingWindow::removeText(modifying_score);
	modifying_score = new Text(buffer, Point2D(DrawingWindow::width / 2 + 100.0f, DrawingWindow::height - 80.0f), Color(0, 1, 0), BITMAP_TIMES_ROMAN_24);
	DrawingWindow::addText(modifying_score);
	//For debug purposes
}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width, int height)
{

	visual->poarta(0,0,width,height); 

}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		rotate(0);
		break;
	case GLUT_KEY_RIGHT:
		rotate(1);
		break;
	case GLUT_KEY_UP:
		move_straight();
		break;
	case 32:
		//drill(param);
		printf("Am apasat space\n");
		break;
	case 27: exit(0);
	}
}

//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button, int state, int x, int y)
{

}


int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 1280, 720, 40, 0, "Tema1");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}