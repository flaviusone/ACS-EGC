#include "DrawingWindow.h"


vector <Object2D*> DrawingWindow::objects2D;
vector <Visual2D*> DrawingWindow::visuals2D;
vector <Text*> DrawingWindow::texts;

int DrawingWindow::width(600);
int DrawingWindow::height(600);

DrawingWindow::DrawingWindow(int argc, char** argv,int _width, int _height, int startX, int startY, string name)
{
	width = _width;
	height = _height;

	//init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(width,height);
	glutInitWindowPosition(startX,startY); 
	glutCreateWindow(name.c_str());
	
	//Sunt definite functiile care vor fi apelate direct de sistemul Windows:
	glutDisplayFunc(displayFunction); //functia apelata pentru afisarea continutului ferestrei aplicatiei
	glutReshapeFunc(reshapeFunction); //functia apelata pentru refacerea continutului ferestrei dupa o redimensionare sau dupa ce fereastra a fost (partial) acoperita
	glutIdleFunc(idleFunction); //functia apelata atunci cand sistemul nu are de tratat alte evenimente
	glutKeyboardFunc(keyboardFunction); //functia apelata la apasarea unei taste
	glutSpecialFunc(specialFunction); //functia apelata la apasarea unei taste speciale
	glutMouseFunc(mouseFunction); //functia apelata la click de mouse

	glClearColor(0.2,0.2,0.2,1);  //afiseaza fondul ferestrei aplicatiei in alb

	//activeaza testul de adancime pentru eliminarea partilor nevizibile in imagini
	glEnable(GL_DEPTH_TEST); 

}

void DrawingWindow::drawObjects()
{
	
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

	//desenare text
	for (i = 0; i < texts.size(); i++)
	{
		glColor3f( texts[i]->color.r, texts[i]->color.g, texts[i]->color.b );
		glRasterPos2f(texts[i]->pos.x, texts[i]->pos.y);
		for (j = 0; j < texts[i]->text.size(); j++) {
		glutBitmapCharacter(texts[i]->font, texts[i]->text[j]);
		}
	}
}


void DrawingWindow::drawObjects(Visual2D *v)
{
	
	//deseneaza obiecte 2D
	int i,j;
	for (i = 0; i < (int)v->visual2D_objects2D.size(); i++)
	{
		//daca e linie
		if (v->visual2D_objects2D[i]->type == 1)
		{
			glColor3f(v->visual2D_objects2D[i]->color.r,v->visual2D_objects2D[i]->color.g,v->visual2D_objects2D[i]->color.b);
			glBegin(GL_LINES);
			glVertex3f(v->visual2D_objects2D[i]->transf_points[0]->x,v->visual2D_objects2D[i]->transf_points[0]->y,0);
			glVertex3f(v->visual2D_objects2D[i]->transf_points[1]->x,v->visual2D_objects2D[i]->transf_points[1]->y,0);
			glEnd();
		}
		else 
		{
			if (v->visual2D_objects2D[i]->points.size() >= 3) //daca are mai mult de 3 puncte
			{
				glColor3f(v->visual2D_objects2D[i]->color.r,v->visual2D_objects2D[i]->color.g,v->visual2D_objects2D[i]->color.b);
				if (!v->visual2D_objects2D[i]->fill)
				{
					glBegin(GL_LINE_LOOP); //se poate folosi si GL_LINES, dar trebuie date doua puncte o data
					for (j = 0; j < (int)v->visual2D_objects2D[i]->points.size();j++)
					{
						
						glVertex3f(v->visual2D_objects2D[i]->transf_points[j]->x,v->visual2D_objects2D[i]->transf_points[j]->y,0);
						
					
					}
					glEnd();
				}
				else
				{
					glBegin(GL_TRIANGLE_FAN); //se poate folosi si GL_TRIANGLES, dar trebuie sa se dea cate trei puncte o data
					for (j = 0; j < (int)v->visual2D_objects2D[i]->points.size();j++)
					{
						glVertex3f(v->visual2D_objects2D[i]->transf_points[j]->x,v->visual2D_objects2D[i]->transf_points[j]->y,0);
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

	//desenare text
	for (i = 0; i < v->visual2D_texts.size(); i++)
	{
		glColor3f( v->visual2D_texts[i]->color.r, v->visual2D_texts[i]->color.g, v->visual2D_texts[i]->color.b );
		glRasterPos2f(v->visual2D_texts[i]->pos.x, v->visual2D_texts[i]->pos.y);
		for (j = 0; j < v->visual2D_texts[i]->text.size(); j++) {
		glutBitmapCharacter(v->visual2D_texts[i]->font, v->visual2D_texts[i]->text[j]);
		}
	}
	
}


void DrawingWindow::displayFunction()
{

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	if (visuals2D.size() == 0)
		drawObjects();
	else
		for (int i = 0; i < visuals2D.size(); i++)
		{
			
			visuals2D[i]->decupare(true);
			//deseneaza obiectele din contextul vizual curent
			drawObjects(visuals2D[i]);

			//deseneaza obiectele din containerul principal
			drawObjects();
		}

	
	//swap buffers
	glutSwapBuffers();
}

void DrawingWindow::redisplay()
{
	//redisplay
	glutPostRedisplay();
}

void DrawingWindow::idleFunction()
{
	onIdle();
	
	//redisplay
	glutPostRedisplay();
}


void DrawingWindow::clip(float XFm, float XFM, float YFm, float YFM, int XPm, int XPM, int YPm, int YPM)
{
	
	//glViewport stabileste transformarea in poarta de vizualizare
	//glViewport(x,y,width,height) - x si y sunt coordonatele punctului celui mai din stanga jos
	

	glViewport(XPm,height-YPM,XPM-XPm,YPM-YPm);
	//cout<<"YPm="<<YPm<<" height="<<height<<" YPM="<<YPM<<endl;	
	//se stabileste transformarea de proiectie
	glMatrixMode(GL_PROJECTION);
	//se porneste de la matricea identitate
	glLoadIdentity();
	//glOrtho este o proiectie ortografica - ea stabileste volumul de vizualizare
	//in cazul nostru, stabileste fereastra de vizualizare
	glOrtho(XFm-0.01,XFM+0.01,YFm-0.01,YFM+0.01,1,300);
	//ne intoarcem la matricea de modelare vizualizare
	glMatrixMode(GL_MODELVIEW);
			
	
	
}


void DrawingWindow::fereastra(float XFm, float XFM, float YFm, float YFM)
{
	//se stabileste transformarea de proiectie
	glMatrixMode(GL_PROJECTION);
	//se porneste de la matricea identitate
	glLoadIdentity();
	//glOrtho este o proiectie ortografica - ea stabileste volumul de vizualizare
	//in cazul nostru, stabileste fereastra de vizualizare
	glOrtho(XFm-0.01,XFM+0.01,YFm-0.01,YFM+0.01,1,300);
	//ne intoarcem la matricea de modelare vizualizare
	glMatrixMode(GL_MODELVIEW);
}



void DrawingWindow::poarta(int XPm, int XPM, int YPm, int YPM)
{
	
	//glViewport stabileste transformarea in poarta de vizualizare
	glViewport(XPm,height-YPM,XPM-XPm,YPM-YPm);
	//cout<<"x="<<XPm<<" y="<<height-YPM<<" width="<<XPM-XPm<<" height="<<YPM-YPm<<endl;	
}


void DrawingWindow::reshapeFunction(int _width, int _height)
{
	onReshape(_width,_height);
	
	width = _width;
	height = _height;

	//glViewport stabileste transformarea in poarta de vizualizare
	glViewport(0,0,width,height);
		
	//se stabileste transformarea de proiectie
	glMatrixMode(GL_PROJECTION);
	//se porneste de la matricea identitate
	glLoadIdentity();
	//glOrtho este o proiectie ortografica - ea stabileste volumul de vizualizare
	//in cazul nostru, stabileste fereastra de vizualizare
	glOrtho(0,200,0,200,1,300);
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



void DrawingWindow::addObject2D_to_Visual2D(Object2D *o,Visual2D *v2d)
{
	v2d->visual2D_objects2D.push_back(o);
}


void DrawingWindow::addVisual2D(Visual2D *v)
{
	visuals2D.push_back(v);
}

void DrawingWindow::addText(Text *text)
{
	texts.push_back(text);
}

void DrawingWindow::addText_to_Visual2D(Text *text,Visual2D *v)
{
	v->visual2D_texts.push_back(text);
}


void DrawingWindow::removeObject2D(Object2D *o)
{
	//gaseste obiectul care trebuie sters
	int poz;
	bool gasit = false;
	for (poz = 0; poz< objects2D.size(); poz++)
	{
		if (o == objects2D[poz])
		{
			gasit = true;
			break;
		}
	}
	if (gasit)
		objects2D.erase(objects2D.begin() + poz);
}

void DrawingWindow::removeVisual2D(Visual2D *v)
{
	//gaseste contextul vizual care trebuie sters
	int poz;
	bool gasit = false;
	for (poz = 0; poz< visuals2D.size(); poz++)
	{
		if (v == visuals2D[poz])
		{
			gasit = true;
			break;
		}
	}
	if (gasit)
		visuals2D.erase(visuals2D.begin() + poz);
}

void DrawingWindow::removeObject2D_from_Visual2D(Object2D *o, Visual2D *v)
{
	//gaseste obiectul care trebuie sters
	int poz;
	bool gasit = false;
	for (poz = 0; poz< v->visual2D_objects2D.size(); poz++)
	{
		if (o == v->visual2D_objects2D[poz])
		{
			gasit = true;
			break;
		}
	}
	if (gasit)
		v->visual2D_objects2D.erase(v->visual2D_objects2D.begin() + poz);
}

void DrawingWindow::removeText(Text *text)
{
	//gaseste textul care trebuie sters
	int poz;
	bool gasit = false;
	for (poz = 0; poz< texts.size(); poz++)
	{
		if (text == texts[poz])
		{
			gasit = true;
			break;
		}
	}
	if (gasit)
		texts.erase(texts.begin() + poz);
}
	

void DrawingWindow::removeText_from_Visual2D(Text *text, Visual2D *v)
{
	//gaseste obiectul care trebuie sters
	int poz;
	bool gasit = false;
	for (poz = 0; poz< v->visual2D_texts.size(); poz++)
	{
		if (text == v->visual2D_texts[poz])
		{
			gasit = true;
			break;
		}
	}
	if (gasit)
		v->visual2D_texts.erase(v->visual2D_texts.begin() + poz);
}
	