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
#include "Player.h"


#define PI 3.14159265358979323846
#define inf 1000000
using namespace std;

Visual2D *v2d1;
Object3D *cube21,*cube22,*chenar;
vector <Point3D*> vertices;
vector <Face*> faces;
Player *player;
float n=1;
bool	left_pressed = false,
		right_pressed = false,
		up_pressed = false,
		down_pressed = false;
	

void init_player(){
	player = new Player();
	player->addPlayer3D();

}

void init_board(){
	n = 3;
	vertices.push_back(new Point3D(-n, 0, -n));
	vertices.push_back(new Point3D(n, 0, -n));
	vertices.push_back(new Point3D(2*n, 0, 5*n));
	vertices.push_back(new Point3D(-2*n, 0, 5*n));

	vector <int> contour;
	//fata jos
	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	faces.push_back(new Face(contour));

	chenar = new Object3D(vertices, faces, Color(1, 0, 0), false);
	DrawingWindow::addObject3D(chenar);
	Transform3D::loadIdentityProjectionMatrix();
	Transform3D::perspectiveProjectionMatrix(0.5, 10, 20);
	Transform3D::applyTransform(chenar);
}


//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	
	v2d1 = new Visual2D(-9,-12,9,12,0,0,DrawingWindow::width,DrawingWindow::height); 
	v2d1->tipTran(true);
	addVisual2D(v2d1);
	
	init_board();

	//se deseneaza playerul
	init_player();
	
	
		
	/*Transform3D::loadIdentityProjectionMatrix();
	Transform3D::perspectiveProjectionMatrix(0.5, 4, 4);
	Transform3D::applyTransform(player->parts[0]);

	Transform3D::loadIdentityModelMatrix();
	Transform3D::translateMatrix(2, 0, 0);
	Transform3D::applyTransform(player->parts[0]);*/
	//Transform3D::translateMatrix(0,0,ty);
	//Transform3D::rotateMatrixOy(-0.5);
	//Transform3D::rotateMatrixOz(-0.1);
}


//functia care permite animatia
void DrawingWindow::onIdle()
{

	if (right_pressed)
		player->move_right();
	if (left_pressed)
		player->move_left();
	if (up_pressed)
		player->move_up();
	if (down_pressed)
		player->move_down();


	
}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	
	v2d1->poarta(0,0,width,height); 
	

}

void DrawingWindow::buttonUP(int key, int x, int y){
	switch (key){
	case GLUT_KEY_UP:
		up_pressed = false;
		break;
	case GLUT_KEY_LEFT:
		left_pressed = false;
		break;
	case GLUT_KEY_RIGHT:
		right_pressed = false;
		break;
	case GLUT_KEY_DOWN:
		down_pressed = false;
		break;
	}
}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		left_pressed = true;
		break;
	case GLUT_KEY_RIGHT:
		right_pressed = true;
		break;
	case GLUT_KEY_UP:
		//if (!up_pressed)
		//	naveta->viteza_aux = 0;		//plec de pe loc cu viteza 0
		up_pressed = true;
		break;
	case GLUT_KEY_DOWN:
		down_pressed = true;
		break;
	case 27: exit(0);
	}
}
//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button,int state,int x, int y)
{
	
}


int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 1280, 720, 50, 0, "Tema 2 EGC");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}