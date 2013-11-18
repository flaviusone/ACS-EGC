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
#include "Inamic1.h"
#include "Inamic2.h"
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

#define PI 3.14159265358979323846
#define inf 1000000
#define stanga 1
#define dreapta -1
using namespace std;

Visual2D *v2d1;
Object3D *cube21,*cube22,*chenar;
vector <Point3D*> vertices;
vector <Face*> faces;
vector <Inamic*> inamici;
Player *player;
Board *board;
Text *score,*lifes,*speed,*endgame,*accelerate;
Rectangle2D *speed_out, *speed_in,
			*life1,*life2,*life3;
int game_over = 0;
clock_t t, old_t = 0, old_t2 = 0, old_t3 = 0;
char buffer[20];
float n=1,
	  spawn_time = 1;
bool	left_pressed = false,
		right_pressed = false,
		up_pressed = false,
		down_pressed = false,
		press = false;
float unghi = PI / 12;
int k = 0;
int speed_counter = 1;
int display_accelerate = 0;
float enemy_speed=10;

void inamici_rotate_dreapta(){
	for (int i = 0; i < inamici.size(); i++){
		inamici[i]->rotate_dreapta();
	}
}

void inamici_rotate_stanga(){
	for (int i = 0; i < inamici.size(); i++){
		inamici[i]->rotate_stanga();
	}
}

void inamici_set_straight(){
	for (int i = 0; i < inamici.size(); i++){
		inamici[i]->set_straight();
	}
}

void inamici_move_down(){
	for (int i = 0; i < inamici.size(); i++){
		inamici[i]->move_down();
	}
}

void init_player(){
	player = new Player();
	player->addPlayer3D();

}

void init_board(){

	// Initializez chenar principal de joc
	board = new Board();

	// Initializez text Scor ( distanta parcursa )
	score = new Text("Distance: 0", Point2D(DrawingWindow::width - 200, DrawingWindow::height - 50.0f), Color(1, 1, 1), BITMAP_TIMES_ROMAN_24);
	DrawingWindow::addText(score);

	// Initializez text Shield
	lifes = new Text("Shield: ", Point2D(10, DrawingWindow::height - 50.0f), Color(1, 1, 1), BITMAP_TIMES_ROMAN_24);
	DrawingWindow::addText(lifes);

	// Initializez indicatoare Shield

	life1 = new Rectangle2D(Point2D(90, DrawingWindow::height - 60), 30, 30, Color(1, 0, 0), true);
	DrawingWindow::addObject2D(life1);
	life2 = new Rectangle2D(Point2D(130, DrawingWindow::height - 60), 30, 30, Color(1, 0, 0), true);
	DrawingWindow::addObject2D(life2);
	life3 = new Rectangle2D(Point2D(170, DrawingWindow::height - 60), 30, 30, Color(1, 0, 0), true);
	DrawingWindow::addObject2D(life3);

	// Initializez text speed
	speed = new Text("Speed: ", Point2D(10, DrawingWindow::height - 100.0f), Color(1, 1, 1), BITMAP_TIMES_ROMAN_24);
	DrawingWindow::addText(speed);

	// Initializez bara ce indica speed
	speed_out = new Rectangle2D(Point2D(90, DrawingWindow::height - 100), 150, 30, Color(1, 1, 1), false);
	DrawingWindow::addObject2D(speed_out);
	speed_in = new Rectangle2D(Point2D(95, DrawingWindow::height - 95), 140, 20, Color(1, 0, 0), true);
	DrawingWindow::addObject2D(speed_in);

	accelerate = new Text("AUTO-ACCELERATE", Point2D(DrawingWindow::width/2-100, DrawingWindow::height/2), Color(1, 1, 1), BITMAP_TIMES_ROMAN_24);

}
void remove_enemy(){
	for (int i = 0; i < inamici.size(); i++)
	if (inamici[i]->tz > 300)
	{
		inamici[i]->removeInamic3D();
		Inamic *temp = inamici[i];
		inamici.erase(inamici.begin() + i);
		delete temp;
		i--;
	}
}
void increase_enemy_speed(){
	enemy_speed += 5;
	for (int i = 0; i < inamici.size(); i++){
		inamici[i]->speed += 5;
	}
	player->enemy_speed += 5;
}
void enemy_spawn(){
	t = clock();

	//cresc nivelul la fiecare 10 secunde
	if ((float)t / CLOCKS_PER_SEC / 6 > speed_counter){
		speed_counter++;
		increase_enemy_speed();
		spawn_time -= 0.05;
		if (spawn_time == 0) spawn_time = 0.1;
		display_accelerate = 1;
		old_t2 = clock();
		DrawingWindow::addText(accelerate);
		printf("Accelerate speed \n");
	}

	if ((((float)t) - ((float)old_t)) / CLOCKS_PER_SEC > spawn_time){
		float startx = rand() % DrawingWindow::width - 100;
		float startz = -rand() % 15*DrawingWindow::width;

		//verific sa nu spawnez pe naveta
		while (true){
			if ( (startz > -5000) || (startx < 100)){
					startx = rand() % DrawingWindow::width - 100;
					startz = -rand() % 10 * DrawingWindow::width;
			}
			else break;
		}
		Inamic *temp = new Inamic2(startx, 0.0, startz,enemy_speed);
		inamici.push_back(temp);
		old_t = t;
	}

}

void display_accelerate_speed(){
	t = clock();
	// Daca au trecut 2 secunde de text afisat
	if ((((float)t) - ((float)old_t2)) / CLOCKS_PER_SEC > 1){
		DrawingWindow::removeText(accelerate);
		//dau remove la text
		display_accelerate = 0;
		old_t2 = t;
	}
}
void update_lives(){
	player->lives--;
	switch (player->lives)
	{
	case 2:
		DrawingWindow::removeObject2D(life3);
		break;
	case 1:
		DrawingWindow::removeObject2D(life2);
		break;
	case 0:
		DrawingWindow::removeObject2D(life1);
		sprintf(buffer, "GAME OVER! Score:  %0.0f", player->distanta_parcursa-player->enemy_speed/300);
		endgame = new Text(buffer, Point2D(DrawingWindow::width / 2 - 100, DrawingWindow::height/2 ), Color(1, 1, 1), BITMAP_TIMES_ROMAN_24);
		DrawingWindow::addText(endgame);
		game_over = 1;
		break;
	default:
		break;
	}
}
void enemy_check_collision(){
	for (int i = 0; i < inamici.size(); i++){
		if (player->enemy_check_collision(inamici[i])){
			update_lives();
			

			inamici[i]->removeInamic3D();
			Inamic *temp = inamici[i];
			inamici.erase(inamici.begin() + i);
			delete temp;
			i--;
			printf("Coliziune \n");
			return;
		}
	}
}
void update_score(){
	player->update_socre();

	DrawingWindow::removeObject2D(speed_in);
	speed_in = new Rectangle2D(Point2D(95, DrawingWindow::height - 87), (player->enemy_speed - 10)*1.2, 20, Color(1, 0, 0), true);
	DrawingWindow::addObject2D(speed_in);
}

//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	
	v2d1 = new Visual2D(0,0, DrawingWindow::width, DrawingWindow::height, 0, 0, DrawingWindow::width, DrawingWindow::height);
	v2d1->tipTran(true);
	addVisual2D(v2d1);
	
	init_board();
	init_player();


}


//functia care permite animatia
void DrawingWindow::onIdle()
{
	if (game_over) return;

	if (right_pressed){
		player->move_right();
		board->rotate_dreapta();
		inamici_rotate_dreapta();
	}
	
	if (left_pressed){
		player->move_left();
		board->rotate_stanga();
		inamici_rotate_stanga();
	}

	// Set straight if nothing pressed
	if (!press){
		player->set_straight();
		board->set_straight();
		inamici_set_straight();
	}

	enemy_spawn();				// spawnez nou inamic daca e nevoie
	inamici_move_down();		// translatez toti inamicii in jos
	enemy_check_collision();	// verific daca am lovit un inamic
	update_score();				// updatez distanta parcursa
	remove_enemy();				// verific daca au iesit din cadru
	
	if (display_accelerate){
		display_accelerate_speed();
	}
	
	// afisez de 6 ori pe sec
	if (k == 10){
		sprintf(buffer, "Distance: %0.0f", player->distanta_parcursa);
		DrawingWindow::removeText(score);
		score->text = buffer;
		DrawingWindow::addText(score);
		k = 0;
	}
	k++;
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
		press = false;
		break;
	case GLUT_KEY_RIGHT:
		right_pressed = false;
		press = false;
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
	srand(time(0));
	//creare fereastra
	DrawingWindow dw(argc, argv, 1280, 720, 50, 0, "Tema 2 EGC");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}