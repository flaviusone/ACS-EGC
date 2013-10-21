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
Circle2D *cercverde;
Text *score,*modifying_score,*nolives;
Object2D *obiect;
//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	//creeam context vizual
	visual = new Visual2D(0, 0, DrawingWindow::width, DrawingWindow::height, 0, 0, DrawingWindow::width, DrawingWindow::height);
	addVisual2D(visual);

	//creeam chenar alb
	chenar_alb = new Rectangle2D(Point2D(5, 5), DrawingWindow::width - 20 , DrawingWindow::height - 20,Color(1,1,1),false);
	addObject2D(chenar_alb);

	//adaugam text SCORE
	score = new Text("SCORE", Point2D(DrawingWindow::width / 2 - 40, DrawingWindow::height - 50 ), Color(0, 1, 0), BITMAP_TIMES_ROMAN_24);
	addText(score);

	//adaugam modifying score
	modifying_score = new Text("000000", Point2D(DrawingWindow::width / 2 - 40, DrawingWindow::height - 80), Color(0, 1, 0), BITMAP_TIMES_ROMAN_24);
	addText(modifying_score);
	
	
	//cercverde = new Circle2D(Point2D(683, 384), 100, Color(255, 0, 0), false);
	//addObject2D_to_Visual2D(cercverde, visual);
	
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