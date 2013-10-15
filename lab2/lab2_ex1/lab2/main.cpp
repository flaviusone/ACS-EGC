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

Visual2D *v2d1;
Rectangle2D *rect;
Text *text;
//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	
	v2d1 = new Visual2D(0,0,DrawingWindow::width,DrawingWindow::height,0,0,DrawingWindow::width,DrawingWindow::height);  
	addVisual2D(v2d1);
	
	rect = new Rectangle2D(Point2D(100,100),300,300);
	addObject2D(rect);
	
	text = new Text("dreptunghi",Point2D(200,250),Color(0,1,0),BITMAP_TIMES_ROMAN_24);
	addText(text);

	
}


//functia care permite animatia
void DrawingWindow::onIdle()
{

}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	
	v2d1->poarta(0,0,width,height); 
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