#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include "Inamic1.h"
#include "Inamic2.h"
#include "Inamic3.h"
#include "Laser.h"
#include <iostream>
#include <windows.h>
#include "Inamic.h"
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h> 
#include "Naveta.h"

#define PI 3.14159265358979323846

using namespace std;
clock_t t, old_t = 0, old_t2 = 0;
Visual2D *visual;
Rectangle2D *chenar_alb;
Circle2D * cerc_test;
Text *score, *modifying_score, *nolives;
vector<Inamic*> inamici;
vector<Object2D*> obiecte2d;
vector<Laser*> lasere;
Naveta *naveta;
int lives = 3,
score_val = 0,
chenar_x, chenar_y,
speed_counter = 1;
	
bool left_pressed = false, 
	 right_pressed = false, 
	 up_pressed = false;
float enemy_speed = 0.2, 
	  spawn_time = 1;
char buffer[20];

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
	visual->tipTran(true);
	DrawingWindow::addVisual2D(visual);

	//creeam chenar alb
	chenar_alb = new Rectangle2D(Point2D(5, 5), chenar_x, chenar_y, Color(1, 1, 1), false);
	DrawingWindow::addObject2D_to_Visual2D(chenar_alb,visual);

	//adaugam text SCORE
	score = new Text("SCORE", Point2D(DrawingWindow::width / 2 - 40.0f, DrawingWindow::height - 50.0f), Color(0, 1, 0), BITMAP_TIMES_ROMAN_24);
	DrawingWindow::addText(score);

	//adaugam modifying score
	modifying_score = new Text("000000", Point2D(DrawingWindow::width / 2 - 40.0f, DrawingWindow::height - 80.0f), Color(0, 1, 0), BITMAP_TIMES_ROMAN_24);
	DrawingWindow::addText(modifying_score);

	nolives = new Text("000000", Point2D(DrawingWindow::width - 140.0f, DrawingWindow::height - 80.0f), Color(0, 1, 0), BITMAP_TIMES_ROMAN_24);

}

void DrawingWindow::init()
{
	//init chenar, scor, visual2d
	init_principale();

	//creeam naveta spatiala si o adaugam la centru
	init_naveta_spatiala();
}

void enemy_attack(){
	for (int i = 0; i < inamici.size(); i++){
		naveta->calcCentru();
		inamici[i]->calc_centru();

		float inamic_bxX = inamici[i]->bxX;
		float inamic_byY = inamici[i]->bxY;
		float dx, dy;
		float inamic_centrux = inamici[i]->centrux;
		float inamic_centruy = inamici[i]->centruy;
		dx = -naveta->centru_x + inamic_centrux;
		dy = -naveta->centru_y + inamic_centruy;

		/*if (inamici[i]->tip != 1){
			inamici[i]->rotire();
		}*/

		if (inamici[i]->tip == 2){

			if (inamic_centrux - 15 < 6){
				inamici[i]->directie -= PI/2;
			}
			else if (inamic_centrux + 15 > chenar_x + 4){
				inamici[i]->directie -= PI/2;
			}
			else if (inamic_centruy - 15 < 6){
				inamici[i]->directie -= PI/2;
			}
			else if (inamic_centruy + 15 > chenar_y + 3){
				inamici[i]->directie -= PI/2;
			}


			inamici[i]->translate_with(enemy_speed*cos(inamici[i]->directie), enemy_speed*sin(inamici[i]->directie));
		}

		if (inamici[i]->tip == 1)
		inamici[i]->translate_with(-enemy_speed*dx / (fabs(dx) + fabs(dy)), -enemy_speed*dy / (fabs(dx) + fabs(dy)));

		
	}
}

void enemy_spawn(){
	
	t = clock();

	//cresc nivelul la fiecare 10 secunde
	if ((float)t / CLOCKS_PER_SEC / 10 > speed_counter){
		speed_counter++;
		enemy_speed += 0.1;
		spawn_time -= 0.1;
	}

	//spawnez inamic la fiecare 1 sec
	if ((((float)t) - ((float)old_t)) / CLOCKS_PER_SEC > spawn_time){
		float startx = rand() % 1150;
		float starty = rand() % 650;

		//verific sa nu spawnez pe naveta

		while (true){
			if (startx < naveta->centru_x + 100 &&
				startx > naveta->centru_x - 100 &&
				startx < naveta->centru_y + 100 &&
				startx > naveta->centru_y - 100 &&
				startx < 20 && starty < 20
				){
					startx = rand() % 1200;
					starty = rand() % 700;
			}
			else break;
		}
		float  spawn = rand() % 30;
		if (spawn  < 10){
			Inamic *temp = new Inamic2(naveta->directie, startx, starty);
			temp->addInamic2D();
			inamici.push_back(temp);
		}else if (spawn > 10 && spawn < 20){
			Inamic *temp3 = new Inamic3(naveta->directie, startx, starty);
			temp3->addInamic2D();
			inamici.push_back(temp3);
		}
		else{
			Inamic *temp2 = new Inamic1(naveta->directie, startx, starty);
			temp2->addInamic2D();
			inamici.push_back(temp2);
		}
		
		old_t = t;
	}
}

void respawn_world(){

	// Sterge toti inamicii
	for (int i = 0; i < inamici.size(); i++){
		inamici[i]->removeInamic2D();
		Inamic *temp = inamici[i];
		inamici.erase(inamici.begin() + i);
		delete temp; //destruct
		i--;
	}

	naveta->removeNaveta2D();
	naveta->deactivateBurghiu();
	delete naveta;
	init_naveta_spatiala();

	// reda vietile
	lives = 3;
	// scor = 0
	score_val = 0;
		
	enemy_speed = 0.2;
	spawn_time = 1;
}

void laser_spawn(){
	t = clock();
	
	if ((((float)t) - ((float)old_t2)) / CLOCKS_PER_SEC > 0.5){
		naveta->calcCentru();
		Laser *temp = new Laser(naveta->directie,naveta->centru_x+ cos(naveta->directie),naveta->centru_y+ sin(naveta->directie));
		lasere.push_back(temp);
		Laser *temp2 = new Laser(naveta->directie + PI/6, naveta->centru_x + cos(naveta->directie + PI/6), naveta->centru_y + sin(naveta->directie + PI/6));
		lasere.push_back(temp2);
		Laser *temp3 = new Laser(naveta->directie - PI / 6, naveta->centru_x + cos(naveta->directie + PI / 6), naveta->centru_y + sin(naveta->directie - PI / 6));
		lasere.push_back(temp3);
		old_t2 = t;
	}


}
//verifica coliziuni cu inamicii

void laser_collision(){
	for (int i = 0; i < inamici.size(); i++){
		for (int j = 0; j < lasere.size(); j++){
			for (int k = 0; k < lasere[j]->body->transf_points.size(); k++){
				float punct_x = lasere[j]->body->transf_points[k]->x;
				float punct_y = lasere[j]->body->transf_points[k]->y;

				if (punct_x < inamici[i]->hitbox->transf_points[1]->x &&
					punct_x >inamici[i]->hitbox->transf_points[0]->x &&
					punct_y < inamici[i]->hitbox->transf_points[3]->y &&
					punct_y >inamici[i]->hitbox->transf_points[0]->y){

						score_val += inamici[i]->value;

						//remove inamic si laser
						inamici[i]->removeInamic2D();
						lasere[j]->removeLaser2D();
						Inamic *temp = inamici[i];
						Laser *templaser = lasere[j];
						inamici.erase(inamici.begin() + i);
						lasere.erase(lasere.begin() + j);
						delete temp;
						delete templaser;
						return;
						i--;
						j--;

				}//endif
			}//endfor
		}//endfor
	}//endfor
}//end function

void move_lasers(){
	for (int i = 0; i < lasere.size(); i++){
		//lasere[i]->calc_centru();

		float punct_x = lasere[i]->body->transf_points[0]->x;
		float punct_y = lasere[i]->body->transf_points[0]->y;

		if (punct_x < 0 || 
			punct_x > chenar_x + 10 ||
			punct_y < 0  ||
			punct_y > chenar_y + 10){
			lasere[i]->removeLaser2D();
			Laser *templaser = lasere[i];
			lasere.erase(lasere.begin() + i);
			delete templaser;
			i--;
		}else

		lasere[i]->translate_with(cos(lasere[i]->directie), sin(lasere[i]->directie));
	}
}
//functia care permite animatia
void DrawingWindow::onIdle()
{	
	

	//Spawnez inamic la fiecare 1 secunda
	enemy_spawn();

	// Muta inamicii catre nava mea
	enemy_attack();
	
	// Verifica coliziuni cu nava si burghiu
	naveta->check_collision(&inamici,&lives,&score_val);
	
	// spawn laser
	laser_spawn();

	laser_collision();

	move_lasers();

	if (lives == 0)
		respawn_world();

	// Miscare stanga
	if (left_pressed)	naveta->rotate(0);

	//accelerare
	if (up_pressed)
	{
		if (naveta->viteza_aux > naveta->viteza)
			naveta->viteza_aux -= 0.05;
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



	//adaugam modifying score
	//sprintf(buffer, " %.2f ", enemy_speed);
	sprintf(buffer, " %06d ", score_val);
	DrawingWindow::removeText(modifying_score);
	modifying_score->text = buffer;
	DrawingWindow::addText(modifying_score);
	
	//adaugam si vieti
	sprintf(buffer, "Lives x%d ", lives);
	DrawingWindow::removeText(nolives);
	nolives->text = buffer;
	DrawingWindow::addText(nolives);
}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width, int height)
{

	visual->poarta(0, 0, width, height);

}
void DrawingWindow::keyboardbuttonUP(unsigned char key, int x, int y){
	//switch (key){
	//case 110:
	//	naveta->viteza = 3;
	//	naveta->viteza_aux = naveta->viteza;
	//	break;
	//}
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
	//case 110: //cand apas N dau boost la viteza
	//	naveta->viteza = 5;
	//	break;
	case 32:
		if (naveta->burghiu_on){
			naveta->deactivateBurghiu();
			naveta->viteza = 2;
			naveta->burghiu_on = false;
		}
		else {
			naveta->activateBurghiu();
			naveta->viteza = 1;
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
	srand(time(0));
	//creare fereastra
	DrawingWindow dw(argc, argv, 1280, 720, 40, 0, "Tema1");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}