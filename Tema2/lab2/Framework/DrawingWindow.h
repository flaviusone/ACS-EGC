#pragma once
#include "..\dependente\freeglut.h"
#include <iostream>
#include <string>
#include <vector>
#include "Object2D.h"
#include "Object3D.h"
#include "Visual2D.h"
#include "Text.h"

#define KEY_DOWN GLUT_KEY_DOWN
#define KEY_LEFT GLUT_KEY_LEFT
#define KEY_UP GLUT_KEY_UP
#define KEY_RIGHT GLUT_KEY_RIGHT
#define KEY_ESC 27
#define KEY_SPACE 32



// GLUT BUG - se ia in considerare si dimensiunea marginii ferestrei pe Y
#define GLUT_Y_AXIS_BUG


using namespace std;

class DrawingWindow
{
public:
	//containerul de obiecte 2D
	static vector <Object2D*> objects2D;

	//containerul de obiecte 3D
	static vector <Object3D*> objects3D;

	//containerul de contexte vizuale
	static vector <Visual2D*> visuals2D;

	//dimensiunea ferestrei de afisare
	static int width, height;
	
	//vectorul de stringuri care vor fi afisate pe ecran
	static vector <Text*> texts;

		#ifdef GLUT_Y_AXIS_BUG
	// GLUT BUG - pentru a se tine cont de dimensiunea marginilor ferestrei pe Y
	static int glutBorderOffset;
	static int actualBorderOffset;
	#endif

public:
	DrawingWindow(int argc, char** argv,int width, int height,int startX, int startY,string name);
	~DrawingWindow(){}
	static void  run();
	static void displayFunction();
	static void drawObjects();
	static void drawObjects(Visual2D *v);
	static void reshapeFunction(int width,int height);
	static void redisplay();
	static void idleFunction();
	static void timerFunction(int flag);
	static void keyboardFunction(unsigned char key, int x, int y);
	static void specialFunction(int key, int x, int y);
	static void mouseFunction(int button, int state, int x, int y);

	//functii folosite in main.cpp
	static void init();
	static void onIdle();
	static void onKey(unsigned char key);
	static void onMouse(int button, int state,int x, int y);
	static void onReshape(int width,int height);

	
	//functii pentru adaugarea de obiecte la sistemul de coordonate
	static void addObject2D(Object2D *o);
	static void addObject3D(Object3D *o);
	//functie pentru adaugare de text
	static void addText(Text *text);

	
	//functi pentru Visual2D
	static void clip(float XFm, float XFM, float YFm, float YFM, int XPm, int XPM, int YPm, int YPM);
	static void fereastra(float XFm, float XFM, float YFm, float YFM);
	static void poarta(int XPm, int XPM, int YPm, int YPM);
	//adaugare context vizual
	static void addVisual2D(Visual2D *v);
	//adaugare obiect2D la context vizual v
	static void addObject2D_to_Visual2D(Object2D *o, Visual2D *v);
	//adaugare obiect3D la context vizual v
	static void addObject3D_to_Visual2D(Object3D *o, Visual2D *v);
	//functie pentru adaugare de text la context v
	static void addText_to_Visual2D(Text *text,Visual2D *v);


	static void removeObject2D(Object2D *o);
	static void removeObject3D(Object3D *o);
	static void removeVisual2D(Visual2D *v);
	static void removeObject2D_from_Visual2D(Object2D *o, Visual2D *v);
	static void removeObject3D_from_Visual2D(Object3D *o, Visual2D *v);
	static void removeText(Text *text);
	static void removeText_from_Visual2D(Text *text,Visual2D *v);
	
	
	
	
	

};









