//Clasa DrawingWindow - permite desenarea obiectelor si tratarea evenimentelor

#pragma once
#include "..\dependente\freeglut.h"
#include <iostream>
#include <string>
#include <vector>
#include "Object2D.h"


#define KEY_DOWN GLUT_KEY_DOWN
#define KEY_LEFT GLUT_KEY_LEFT
#define KEY_UP GLUT_KEY_UP
#define KEY_RIGHT GLUT_KEY_RIGHT
#define KEY_ESC 27
#define KEY_SPACE 32


using namespace std;




class DrawingWindow
{
public:
	//containerul de obiecte
	static vector <Object2D*> objects2D;

public:
	DrawingWindow(int argc, char** argv,int width, int height,int startX, int startY,string name);
	~DrawingWindow(){}
	static void  run();
	static void displayFunction();
	static void reshapeFunction(int width,int height);
	static void keyboardFunction(unsigned char key, int x, int y);
	static void specialFunction(int key, int x, int y);
	static void mouseFunction(int button, int state, int x, int y);
	static void timerFunction(int flag);
	
	static void init();
	static void onIdle();
	static void onKey(unsigned char key);
	static void onMouse(int button, int state,int x, int y);
	
	//functie pentru adaugarea de obiecte la sistemul de coordonate
	static void addObject2D(Object2D *o);

};









