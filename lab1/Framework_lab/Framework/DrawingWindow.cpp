#include "DrawingWindow.h"
#include <ctime>


vector <Object2D*> DrawingWindow::objects2D;

DrawingWindow::DrawingWindow(int argc, char** argv,int width, int height, int startX, int startY, string name)
{
	//init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(width,height);
	glutInitWindowPosition(startX,startY);
	glutCreateWindow(name.c_str());
	
	//Sunt definite functiile care vor fi apelate direct de sistemul Windows:
	glutDisplayFunc(displayFunction); //functia apelata pentru afisarea continutului ferestrei aplicatiei
	glutReshapeFunc(reshapeFunction); //functia apelata pentru refacerea continutului ferestrei dupa o redimensionare sau dupa ce fereastra a fost (partial) acoperita
	//glutIdleFunc(idleFunction); //functia apelata atunci cand sistemul nu are de tratat alte evenimente
	glutTimerFunc(0, timerFunction, 0);
	glutKeyboardFunc(keyboardFunction); //functia apelata la apasarea unei taste
	glutSpecialFunc(specialFunction); //functia apelata la apasarea unei taste speciale
	glutMouseFunc(mouseFunction); //functia apelata la click de mouse

	glClearColor(1,1,1,1);  //afiseaza fondul ferestrei aplicatiei in alb

	//activeaza testul de adancime pentru eliminarea partilor nevizibile in imagini
	glEnable(GL_DEPTH_TEST); 

}

void DrawingWindow::displayFunction()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//deseneaza obiecte 2D
	int i,j;
	for (i = 0; i < (int)objects2D.size(); i++)
	{
		//daca e linie
		if (objects2D[i]->type == 1)
		{
			glColor3f(objects2D[i]->color.r,objects2D[i]->color.g,objects2D[i]->color.b);
			glBegin(GL_LINES);
			glVertex3f(objects2D[i]->transf_points[0]->x,objects2D[i]->transf_points[0]->y,0);
			glVertex3f(objects2D[i]->transf_points[1]->x,objects2D[i]->transf_points[1]->y,0);
			glEnd();
		}
		else 
		{
			if (objects2D[i]->points.size() >= 3) //daca are mai mult de 3 puncte
			{
				glColor3f(objects2D[i]->color.r,objects2D[i]->color.g,objects2D[i]->color.b);
				if (!objects2D[i]->fill)
				{
					glBegin(GL_LINE_LOOP); //se poate folosi si GL_LINES, dar trebuie date doua puncte o data
					for (j = 0; j < (int)objects2D[i]->points.size();j++)
					{
						
						glVertex3f(objects2D[i]->transf_points[j]->x,objects2D[i]->transf_points[j]->y,0);
						
					
					}
					glEnd();
				}
				else
				{
					glBegin(GL_TRIANGLE_FAN); //se poate folosi si GL_TRIANGLES, dar trebuie sa se dea cate trei puncte o data
					for (j = 0; j < (int)objects2D[i]->points.size();j++)
					{
						glVertex3f(objects2D[i]->transf_points[j]->x,objects2D[i]->transf_points[j]->y,0);
					}	
					glEnd();
				}
			}
			else
			{
				cout<<"Obiectul curent are prea putine varfuri"<<endl;
			}
			
		}
	}

	//swap buffers
	glutSwapBuffers();
}


void DrawingWindow::timerFunction(int flag) 
{
    clock_t drawStartTime = clock();
	onIdle();
	glutPostRedisplay();
    clock_t drawEndTime = clock();
	
	const int MAX_FPS  = 60;
    unsigned int delayToNextFrame = (CLOCKS_PER_SEC / MAX_FPS) - (drawEndTime - drawStartTime);
    delayToNextFrame = (unsigned int)(delayToNextFrame + 0.5f);
    delayToNextFrame < 0 ? delayToNextFrame = 0 : NULL;

    glutTimerFunc(delayToNextFrame, timerFunction, 0);
}




void DrawingWindow::reshapeFunction(int width, int height)
{
	

	//glViewport stabileste transformarea in poarta de vizualizare
	glViewport(0,0,width,height);
		
	//se stabileste transformarea de proiectie
	glMatrixMode(GL_PROJECTION);
	//se porneste de la matricea identitate
	glLoadIdentity();
	//glOrtho este o proiectie ortografica - ea stabileste volumul de vizualizare
	//in cazul nostru, stabileste fereastra de vizualizare
	glOrtho(-20,20,-20,20,1,300);
	
	//ne intoarcem la matricea de modelare vizualizare
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//observatorul este pozitionat pe axa pozitiva a lui z si priveste spre planul XOY
	gluLookAt(0.0, 0.0, 20.0,0.0, 0.0, 0.0,	0.0, 1.0, 0.0);  
}


void DrawingWindow::keyboardFunction(unsigned char key, int x, int y)
{
	onKey(key);
}


void DrawingWindow::specialFunction(int key, int x, int y)
{
	onKey(key);
}


void DrawingWindow::mouseFunction(int button,int state, int x, int y)
{
	onMouse(button, state, x, y);
}

void DrawingWindow::run()
{
	glutMainLoop();
}


void DrawingWindow::addObject2D(Object2D *o)
{
	objects2D.push_back(o);
}
	