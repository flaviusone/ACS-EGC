#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Transform3D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include <iostream>
#include <windows.h>


#define PI 3.14159265358979323846

using namespace std;

Visual2D *v2d;
Object3D *cube1;
float n=1;

//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	
	v2d = new Visual2D(-5,-5,5,5,0,0,DrawingWindow::width,DrawingWindow::height);  
	v2d->tipTran(true);
	addVisual2D(v2d);
	
	

	//se deseneaza un cub
	
	vector <Point3D*> vertices;
	vector <Face*> faces;
	
	//varfurile de jos
	vertices.push_back(new Point3D(0,0,0));
	vertices.push_back(new Point3D(n,0,0));
	vertices.push_back(new Point3D(n,0,n));
	vertices.push_back(new Point3D(0,0,n));
	//varfurile de sus
	vertices.push_back(new Point3D(0,n,0));
	vertices.push_back(new Point3D(n,n,0));
	vertices.push_back(new Point3D(n,n,n));
	vertices.push_back(new Point3D(0,n,n));
	
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
	
	cube1 = new Object3D(vertices,faces,Color(1,0,0),false);
	addObject3D(cube1);
	

}


//functia care permite animatia
void DrawingWindow::onIdle()
{

	
}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	
	v2d->poarta(0,0,width,height); 

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
	DrawingWindow dw(argc, argv, 600, 600, 200, 50, "Laborator EGC");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}