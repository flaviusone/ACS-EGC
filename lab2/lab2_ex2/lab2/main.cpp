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
Object3D *cube1,*piramida,*cube2,*cube3;
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

	cube2 = new Object3D(vertices, faces, Color(0, 1, 0), false);
	addObject3D(cube2);

	Transform3D::loadIdentityModelMatrix();
	Transform3D::translateMatrix(3 * n, 3 * n, 10);
	Transform3D::applyTransform(cube2);

	cube3 = new Object3D(vertices, faces, Color(1, 1, 0), false);
	addObject3D(cube3);

	Transform3D::loadIdentityModelMatrix();
	Transform3D::translateMatrix(3 * n, - 3 * n, 0);
	Transform3D::applyTransform(cube3);

}

void RotesteCubulOY(Object3D *cub, float i){
	float centru_x, centru_y, centru_z;

	centru_x = (cub->vertices[1]->x - cub->vertices[0]->x) / 2 + cub->vertices[0]->x;
	centru_y = (cub->vertices[4]->y - cub->vertices[0]->y) / 2 + cub->vertices[0]->y;
	centru_z = (cub->vertices[3]->z - cub->vertices[0]->z) / 2 + cub->vertices[0]->z;

	//centru_x = (cub->transf_vertices[1]->x - cub->transf_vertices[0]->x) / 2 + cub->transf_vertices[0]->x;
	//centru_y = (cub->transf_vertices[4]->y - cub->transf_vertices[0]->y) / 2 + cub->transf_vertices[0]->y;
	//centru_z = (cub->transf_vertices[3]->z - cub->transf_vertices[0]->z) / 2 + cub->transf_vertices[0]->z;


	Transform3D::loadIdentityModelMatrix();
	Transform3D::translateMatrix(-centru_x, -centru_y, -centru_z);
	Transform3D::rotateMatrixOy(i);
	Transform3D::translateMatrix(centru_x, centru_y, centru_z);
	Transform3D::applyTransform(cub);



}

void Scaleazacub(Object3D *cub, float i){
	float centru_x = 0, centru_y = 0, centru_z = 0;

	centru_x = (cub->vertices[1]->x - cub->vertices[0]->x) / 2 + cub->vertices[0]->x;
	centru_y = (cub->vertices[4]->y - cub->vertices[0]->y) / 2 + cub->vertices[0]->y;
	centru_z = (cub->vertices[3]->z - cub->vertices[0]->z) / 2 + cub->vertices[0]->z;


	Transform3D::loadIdentityModelMatrix();
	Transform3D::translateMatrix(-centru_x, -centru_y, -centru_z);
	Transform3D::scaleMatrix(i,i,i);
	Transform3D::translateMatrix(centru_x, centru_y, centru_z);
	Transform3D::applyTransform(cub);



}

float counter = 0;
float value = 0.005;
float value2 = 0.1;
float centru_x, centru_y, centru_z;
//functia care permite animatia
void DrawingWindow::onIdle()
{
	RotesteCubulOY(cube1, counter);
	counter += 0.01;
	if (counter >= PI * 2) counter -= PI * 2;
	
	Transform3D::loadIdentityModelMatrix();
	Transform3D::translateMatrix(3 * n, cube2->transf_vertices[0]->y + value , 0);
	Transform3D::applyTransform(cube2);

	if (cube2->transf_vertices[0]->y > 5 || cube2->transf_vertices[0]->y < -5) value = -value;

	Scaleazacub(cube3, cube2->transf_vertices[0]->y);

	
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