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

Visual2D *v2d1, *v2d2, *v2d3, *v2d4;
Rectangle2D *rect;
Circle2D *cercverde, *cercrosu, *cercgalben;
Text *text;
//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	
	v2d1 = new Visual2D(0, 0, DrawingWindow::width, DrawingWindow::height, 0, 0, DrawingWindow::width / 2, DrawingWindow::height / 2);
	addVisual2D(v2d1);

	v2d2 = new Visual2D(0, 0, DrawingWindow::width, DrawingWindow::height, DrawingWindow::width / 2, 0, DrawingWindow::width, DrawingWindow::height /2);
	addVisual2D(v2d2);

	v2d3 = new Visual2D(0, 0, DrawingWindow::width, DrawingWindow::height, 0, DrawingWindow::height /2 , DrawingWindow::width /2, DrawingWindow::height);
	addVisual2D(v2d3);

	v2d4 = new Visual2D(0, 0, DrawingWindow::width, DrawingWindow::height, DrawingWindow::width / 2, DrawingWindow::height / 2, DrawingWindow::width, DrawingWindow::height);
	addVisual2D(v2d4);
	
	rect = new Rectangle2D(Point2D(100,100),300,300);
	addObject2D(rect);
	
	text = new Text("dreptunghi",Point2D(200,250),Color(0,1,0),BITMAP_TIMES_ROMAN_24);
	addText(text);

	cercverde = new Circle2D(Point2D(250, 250), 100, Color(255, 0, 0), false);
	addObject2D_to_Visual2D(cercverde, v2d3);
	cercrosu = new Circle2D(Point2D(250, 250), 100, Color(0, 255, 0), false);
	addObject2D_to_Visual2D(cercrosu, v2d2);
	cercgalben = new Circle2D(Point2D(250, 250), 100, Color(100, 100, 0), false);
	addObject2D_to_Visual2D(cercgalben, v2d4);

	v2d1->cadruFereastra(Color(0, 0, 0));
	v2d2->cadruFereastra(Color(0, 255, 0));
	v2d3->cadruFereastra(Color(255, 0, 0));
	v2d4->cadruFereastra(Color(100, 100, 0));
}


//functia care permite animatia
void DrawingWindow::onIdle()
{

}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	
	v2d1->poarta(0,0,width/2,height/2); 
	v2d2->poarta(width / 2, 0, width, height /2);
	v2d3->poarta(0, height / 2, width / 2, height);
	v2d4->poarta(width / 2, height/2, width, height);
}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{
	switch(key)
	{
		case 27 : exit(0);
	}
}

//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button,int state,int x, int y)
{
	
}


int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 500, 500, 200, 100, "Laborator EGC");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}