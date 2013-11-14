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
#include "Board.h"


#define PI 3.14159265358979323846
#define inf 1000000
#define stanga 1
#define dreapta -1
using namespace std;

Visual2D *v2d1;
Object3D *cube21,*cube22,*chenar;
vector <Point3D*> vertices;
vector <Face*> faces;
Player *player;
Board *board;
float n=1;
bool	left_pressed = false,
		right_pressed = false,
		up_pressed = false,
		down_pressed = false,
		press = false;
float unghi = PI / 12;

void init_player(){
	player = new Player();
	player->addPlayer3D();

}

void init_board(){
	board = new Board();
}


//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	
	v2d1 = new Visual2D(0,0, DrawingWindow::width, DrawingWindow::height, 0, 0, DrawingWindow::width, DrawingWindow::height);
	v2d1->tipTran(true);
	addVisual2D(v2d1);

	init_board();
	init_player();
		
	//se deseneaza playerul
	
}


//functia care permite animatia
void DrawingWindow::onIdle()
{

	if (right_pressed){
		player->move_right();
		board->rotate_dreapta();
	}
	
	if (left_pressed){
		player->move_left();
		board->rotate_stanga();
	}

	if (!press){
		player->set_straight();
		board->set_straight();
	}

	/*if (up_pressed)
		player->move_up();
	if (down_pressed)
		player->move_down();*/

	
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
		board->set_straight();
		press = false;
		//player->set_straight(-1);
		break;
	case GLUT_KEY_RIGHT:
		right_pressed = false;
		press = false;
		board->set_straight();
		//player->set_straight(1);
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
		press = true;
		break;
	case GLUT_KEY_RIGHT:
		right_pressed = true;
		press = true;
		break;
	case GLUT_KEY_UP:
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