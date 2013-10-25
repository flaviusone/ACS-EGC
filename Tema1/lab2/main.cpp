#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include "Inamic1.h"
#include <iostream>
#include <windows.h>
#include "Inamic.h"
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h> 
#include "Naveta.h"

#define PI 3.14159265358979323846

using namespace std;
clock_t t,old_t=0;
int chenar_x, chenar_y;
Visual2D *visual;
Rectangle2D *chenar_alb;
Text *score, *modifying_score, *nolives;
bool left_pressed = false, right_pressed = false, up_pressed = false;
vector<Inamic*> inamici;
vector<Object2D*> obiecte2d;
Naveta *naveta;
//Constructie naveta
void init_naveta_spatiala(){
	float centru_x = DrawingWindow::width / 2;
	float centru_y = DrawingWindow::height / 2;
	naveta = new Naveta(centru_x, centru_y,chenar_x,chenar_y);
	naveta->addNaveta2D();
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

void DrawingWindow::init()
{
	//init chenar, scor, visual2d
	init_principale();

	//creeam naveta spatiala si o adaugam la centru
	init_naveta_spatiala();
}

float unghiinamic;
//functia care permite animatia
void DrawingWindow::onIdle()
{	
	naveta->calcCentru();
	//spawnez inamic la fiecare 1 sec
	t = clock();
	if ((((float)t) - ((float)old_t)) / CLOCKS_PER_SEC > 1){
		Inamic *temp = new Inamic1(naveta->directie, rand() % 1200 , rand() % 700);
		temp->addInamic2D();
		inamici.push_back(temp);
		old_t = t;
	}

	for (int i = 0; i < inamici.size(); i++){
		float dx, dy;
		//printf("Inamic x %f \n", inamici.at(i)->centrux);
		inamici[i]->calc_centru();
		dx = - naveta->centru_x + inamici[i]->centrux;
		//printf("Coord naveta X = %f Y = %f \n", naveta->cerc_naveta->transf_points[0]->x, naveta->cerc_naveta->transf_points[0]->y);
		//printf("Coord inamic X = %f Y= %f \n\n", inamici[i]->centrux, inamici[i]->centruy);
		dy = - naveta->centru_y + inamici[i]->centruy;
		//printf("Coord Y punct %d  = %f \n", i, y);
		
		inamici[i]->translate_with(-dx / (fabs(dx) + fabs(dy)), -dy / (fabs(dx) + fabs(dy)));
		// unghiinamic = atan2(y, x);
		//inamici.at(i)->translate_with(viteza*cos( unghiinamic), viteza*sin(unghiinamic));
		//inamici.at(i)->directie = unghiinamic;
	}
	//	//verifica in bounds
	//	if (inamici.at(i)->centrux < 5 || inamici.at(i)->centrux < chenar_x || inamici.at(i)->centruy < 5 || inamici.at(i)->centruy < chenar_y){
	//		inamici.at(i)->removeInamic2D();
	//		inamici.erase(inamici.begin() + i);
	//		i--;
	//	}
	//}

	if (left_pressed)	naveta->rotate(0);

	//accelerare
	if (up_pressed)
	{
		if (naveta->viteza_aux < naveta->viteza)
			naveta->viteza_aux += 0.05;
		naveta->move_straight(naveta->viteza_aux);
	}

	//decelerare
	if (!up_pressed){
		if (naveta->viteza_aux>0){
			naveta->move_straight(naveta->viteza_aux);
			naveta->viteza_aux -= 0.05;
		}
		else	naveta->viteza_aux = 0;
	}
	if (right_pressed)	naveta->rotate(1);


	//For debug purposes
	char buffer[50];
	sprintf(buffer, "Coord X = %f Y = %f", naveta->centru_x, naveta->centru_y);
	//adaugam modifying score
	DrawingWindow::removeText(modifying_score);
	modifying_score = new Text(buffer, Point2D(DrawingWindow::width / 2 + 100.0f, DrawingWindow::height - 80.0f), Color(0, 1, 0), BITMAP_TIMES_ROMAN_24);
	DrawingWindow::addText(modifying_score);
	//For debug purposes
}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width, int height)
{

	visual->poarta(0, 0, width, height);

}
void DrawingWindow::keyboardbuttonUP(unsigned char key, int x, int y){
	switch (key){
	case 110:
		naveta->viteza = 3;
		naveta->viteza_aux = naveta->viteza;
		break;
	}
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
		if (!up_pressed)
			naveta->viteza_aux = 0;		//plec de pe loc cu viteza 0

		up_pressed = true;
		break;
	case 110: //cand apas N dau boost la viteza
		naveta->viteza = 5;
		break;
	case 32:
		if (naveta->burghiu_on){
			naveta->deactivateBurghiu();
			naveta->burghiu_on = false;
		}
		else {
			naveta->activateBurghiu();
			naveta->burghiu_on = true;
		}
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