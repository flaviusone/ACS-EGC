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

Visual2D *visual;
Rectangle2D *chenar_alb;
Circle2D *cerc_naveta;
Polygon2D *poly_naveta;
Text *score,*modifying_score,*nolives;
//functia care permite adaugarea de obiecte

//Constructie naveta
void init_naveta_spatiala(){
	int centru_x = DrawingWindow::width / 2;
	int centru_y = DrawingWindow::height / 2;

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
	//creeam context vizual
	visual = new Visual2D(0, 0, DrawingWindow::width, DrawingWindow::height, 0, 0, DrawingWindow::width, DrawingWindow::height);
	DrawingWindow::addVisual2D(visual);

	//creeam chenar alb
	chenar_alb = new Rectangle2D(Point2D(5, 5), DrawingWindow::width - 20, DrawingWindow::height - 20, Color(1, 1, 1), false);
	DrawingWindow::addObject2D(chenar_alb);

	//adaugam text SCORE
	score = new Text("SCORE", Point2D(DrawingWindow::width / 2 - 40, DrawingWindow::height - 50), Color(0, 1, 0), BITMAP_TIMES_ROMAN_24);
	DrawingWindow::addText(score);

	//adaugam modifying score
	modifying_score = new Text("000000", Point2D(DrawingWindow::width / 2 - 40, DrawingWindow::height - 80), Color(0, 1, 0), BITMAP_TIMES_ROMAN_24);
	DrawingWindow::addText(modifying_score);

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
	DrawingWindow dw(argc, argv, 1280, 720, 40, 0, "Laborator EGC");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}