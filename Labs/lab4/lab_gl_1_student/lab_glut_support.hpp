//-------------------------------------------------------------------------------------------------
// Descriere: header in care sunt definite structuri folosite de lab_glut sau utilizate pentru a 
// comunica cu lab_glut
// Nota:
//		WindowInfo      - stocheaza informatii despre fereastra (inaltime, lungime, etc)
//		FramebufferInfo - stocheaza inforatii despre framebuffer
//		ContextInfo     - stocheaza informatii despre contextul opengl CERUT.
//		WindowListener  - clasa din care trebuie sa derivam pentru a lucra cu glut
//
// Nota2:
//		tot ce apartine de glut se afla intr-un namespace propriu
//
// Autor: Lucian Petrescu
// Data: 28 Sep 2013
//-------------------------------------------------------------------------------------------------

#pragma once
#include "dependente\freeglut\freeglut.h"
#include <string>

namespace lab{ namespace glut{

	//-------------------------------------------------------------------------------------------------
	// Informatii despre fereastra
	struct WindowInfo{
		WindowInfo(){
			name="nume default fereastra";
			width=800; height=600; start_position_x=start_position_y=100;
			is_reshapable=true;
		}
		WindowInfo(std::string name, int width, int height, int start_position_x, int start_position_y, bool is_reshapable){
			this->name=name;								
			this->width=width;							
			this->height = height;	
			this->start_position_x = start_position_x;
			this->start_position_y= start_position_y;	
			this->is_reshapable = is_reshapable;
		}
		void operator =(const WindowInfo& info){
			name=info.name;								
			width=info.width;						
			height=info.height;
			start_position_x = info.start_position_x;	
			start_position_y = info.start_position_y;	
			is_reshapable=info.is_reshapable;
		}
		std::string name;													//numele ferestrei
		int width, height;													//inaltime, lungime
		int start_position_x, start_position_y;								//coordonate de start pt fereastra
		bool is_reshapable;													//e fereastra redimensionabila?
	};


	//-------------------------------------------------------------------------------------------------
	// informatii despre framebuffer
	struct FramebufferInfo{
		FramebufferInfo(){
			flags=GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH;	
			msaa = false;
		}
		FramebufferInfo(bool color, bool depth, bool stencil, bool msaa){
			flags =GLUT_DOUBLE;					//tot timpul folosim double buffering!
			if(color) flags |= GLUT_RGBA | GLUT_ALPHA;
			if(depth) flags |= GLUT_DEPTH;
			if(stencil) flags |= GLUT_STENCIL;
			if(msaa) flags |= GLUT_MULTISAMPLE;
			this->msaa = msaa;
		}
		void operator=(const FramebufferInfo& info){
			flags= info.flags;
			msaa = info.msaa;
		}
		unsigned int flags;													// GL_RGBA | GL_DEPTH | GL_RGB | GL_STENCIL | ..
		bool msaa;															// MSAA 4x da/nu?
	};


	//-------------------------------------------------------------------------------------------------
	//informatii despre contextul OpenGL
	struct ContextInfo{
		ContextInfo(){
			major_version = 3;						//cel mai nou context e 4.4
			minor_version = 3;						//dar nu toate driverele sustin inca functionalitatea
			core = true;							//forteaza doar functiile core pentru contextul cerut.
		}
		ContextInfo(int major_version, int minor_version, bool core){
			this->major_version = major_version;		
			this->minor_version = minor_version;	
			this->core=core; 
		}
		void operator=(const ContextInfo &info){
			major_version = info.major_version;
			minor_version = info.minor_version; 
			core=info.core; 
		}
		int major_version, minor_version;
		bool core;
	};


	//---------------------------------------------------------------------------------------------------
	//clasa din care trebuie derivat pentru a putea lucra cu glut
	//functioneza ca un listener pe lab::glut
	class WindowListener{
	public:
		WindowListener(){}
		virtual ~WindowListener(){}

		//------------------- functii ce tin cadrul curent
		//functie chemata inainte de inceperea cadrului curent (adica inainte de a incepe procesul de afisare)
		virtual void notifyBeginFrame(){}
		//functie de afisare, chemata inainte afisarea efectiva (swapBuffers)
		virtual void notifyDisplayFrame(){}
		//functie chemata dupa sfarsirea procesului de afisare pe CPU
		virtual void notifyEndFrame(){}

		//------------------- reshape - se apealeaza atunci cand ecranul este 
		virtual void notifyReshape(int width, int height, int previos_width, int previous_height){}

		//------------------- functii de input
		//functie chemata cand e apasata o tasta
		virtual void notifyKeyPressed(unsigned char key_pressed, int mouse_x, int mouse_y){}
		//functie chemata cand se termina apasarea unei taste
		virtual void notifyKeyReleased(unsigned char key_released, int mouse_x, int mouse_y){}
		//functie chemata cand o tasta speciala e apasata (up down, left right, F1-12, etc)
		virtual void notifySpecialKeyPressed(int key_pressed, int mouse_x, int mouse_y){}
		//functie chemata cand ose termina apsarea unei taste speciale (up down, left right, F1-12, etc)
		virtual void notifySpecialKeyReleased(int key_released, int mouse_x, int mouse_y){}
		//functie chemata cand se face mouse drag
		virtual void notifyMouseDrag(int mouse_x, int mouse_y){}
		//functie chemata cand mouse-ul se misca
		virtual void notifyMouseMove(int mouse_x, int mouse_y){}
		//functie chemata cand un button de mouse e apasat
		virtual void notifyMouseClick(int button, int state, int mouse_x, int mouse_y){}
		//functie chemata cand se face scroll cu mouse-ul.
		virtual void notifyMouseScroll(int wheel, int direction, int mouse_x, int mouse_y){}
	};
}}