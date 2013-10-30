//-------------------------------------------------------------------------------------------------
// Descriere: fisier main
//
// Autor: student
// Data: today
//-------------------------------------------------------------------------------------------------

//librarie matematica 
#include "dependente\glew\glew.h"
#include "dependente\glm\glm.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"
#include "dependente\glm\gtc\matrix_transform.hpp"

//geometrie: drawSolidCube, drawWireTeapot...
#include "lab_geometry.hpp"

//incarcator de shadere
#include "lab_shader_loader.hpp"

//interfata cu glut, ne ofera fereastra, input, context opengl
#include "lab_glut.hpp"

//time
#include <ctime>


class Lab : public lab::glut::WindowListener{

//variabile
private:
	glm::mat4 original_model_matrix;
	glm::mat4 model_matrix, view_matrix, projection_matrix;								//matrici 4x4 pt modelare vizualizare proiectie
	unsigned int location_model_matrix, location_view_matrix, location_projection_matrix;//locatii la nivel de shader ale matricilor (un pointer/offset)
	unsigned int location_object_color;													//locatie uniform culoare obiect
	unsigned int gl_program_shader;														//id-ul de opengl al obiectului de tip program shader


//metode
public:
	
	//constructor .. e apelat cand e instantiata clasa
	Lab(){
		//setari pentru desenare, clear color seteaza culoarea de clear pentru ecran (format R,G,B,A)
		glClearColor(0.5,0.5,0.5,1);
		glClearDepth(1);			//clear depth si depth test (nu le studiem momentan, dar avem nevoie de ele!)
		glEnable(GL_DEPTH_TEST);	//sunt folosite pentru a determina obiectele cele mai apropiate de camera (la curs: algoritmul pictorului, algoritmul zbuffer)
		
		//incarca un shader din fisiere si gaseste locatiile matricilor relativ la programul creat
		gl_program_shader = lab::loadShader("shadere\\shader_vertex.glsl", "shadere\\shader_fragment.glsl");
		location_model_matrix = glGetUniformLocation(gl_program_shader, "model_matrix");
		location_view_matrix = glGetUniformLocation(gl_program_shader, "view_matrix");
		location_projection_matrix = glGetUniformLocation(gl_program_shader, "projection_matrix");
		location_object_color = glGetUniformLocation(gl_program_shader, "object_color");
		
		//matrici de modelare si vizualizare
		original_model_matrix = glm::mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
		view_matrix = myCreateViewMatrix(glm::vec3(0,0,50), glm::vec3(0,0,0), glm::vec3(0,1,0));
	}

	//destructor .. e apelat cand e distrusa clasa
	~Lab(){
		//distruge shader
		glDeleteProgram(gl_program_shader);
	}


	//--------------------------------------------------------------------------------------------
	//functii de definire matrici-----------------------------------------------------------------

	glm::mat4 createViewMatrix(const glm::vec3& eye_position, const glm::vec3& center_position, const glm::vec3& up_direction){
		return glm::lookAt(eye_position, center_position, up_direction);
	}
	glm::mat4 createProjectionMatrix(const float field_of_view_y, const float aspect, const float z_near, const float z_far){
		return glm::perspective(field_of_view_y, aspect,z_near, z_far);
	}

	glm::mat4 myCreateViewMatrix(const glm::vec3& eye_position, const glm::vec3& center_position, const glm::vec3& up_direction){
		glm::mat4 result(0);

		//TODO

		return result;
	}
	glm::mat4 myCreateProjectionMatrix(const float field_of_view_y, const float aspect, const float z_near, const float z_far){
		glm::mat4 result(0);
		
		//TODO

		return result;
	}




	//--------------------------------------------------------------------------------------------
	//functii de cadru ---------------------------------------------------------------------------

	//functie chemata inainte de a incepe cadrul de desenare, o folosim ca sa updatam situatia scenei ( modelam/simulam scena)
	void notifyBeginFrame(){

		
	}
	//functia de afisare (lucram cu banda grafica)
	void notifyDisplayFrame(){
		//bufferele din framebuffer sunt aduse la valorile initiale (setate de clear color si cleardepth)
		//adica se sterge ecranul si se pune culoare (si alte propietati) initiala
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//foloseste shaderul
		glUseProgram(gl_program_shader);
				
		//trimite variabile uniforme la shader
		glUniformMatrix4fv(location_model_matrix,1,false,glm::value_ptr(model_matrix));
		glUniformMatrix4fv(location_view_matrix,1,false,glm::value_ptr(view_matrix));
		glUniformMatrix4fv(location_projection_matrix,1,false,glm::value_ptr(projection_matrix));
		glUniform4f(location_object_color, 1,0,0,0);
		
		//deseneaza obiect
		lab::drawWireCube(40);
	}
	//functie chemata dupa ce am terminat cadrul de desenare (poate fi folosita pt modelare/simulare)
	void notifyEndFrame(){}
	//functei care e chemata cand se schimba dimensiunea ferestrei initiale
	void notifyReshape(int width, int height, int previos_width, int previous_height){
		//reshape
		if(height==0) height=1;
		glViewport(0,0,width,height);
		projection_matrix = myCreateProjectionMatrix(90, (float)width/(float)height,0.1f, 10000.0f);
	}


	//--------------------------------------------------------------------------------------------
	//functii de input output --------------------------------------------------------------------
	
	//tasta apasata
	void notifyKeyPressed(unsigned char key_pressed, int mouse_x, int mouse_y){
		if(key_pressed == 27) lab::glut::close();	//ESC inchide glut si 
		if(key_pressed == 32) {
			//SPACE reincarca shaderul si recalculeaza locatiile (offseti/pointeri)
			glDeleteProgram(gl_program_shader);
			gl_program_shader = lab::loadShader("shadere\\shader_vertex.glsl", "shadere\\shader_fragment.glsl");
			location_model_matrix = glGetUniformLocation(gl_program_shader, "model_matrix");
			location_view_matrix = glGetUniformLocation(gl_program_shader, "view_matrix");
			location_projection_matrix = glGetUniformLocation(gl_program_shader, "projection_matrix");
			location_object_color = glGetUniformLocation(gl_program_shader, "object_color");
		}
	}
	//tasta ridicata
	void notifyKeyReleased(unsigned char key_released, int mouse_x, int mouse_y){	}
	//tasta speciala (up/down/F1/F2..) apasata
	void notifySpecialKeyPressed(int key_pressed, int mouse_x, int mouse_y){
		if(key_pressed == GLUT_KEY_F1) lab::glut::enterFullscreen();
		if(key_pressed == GLUT_KEY_F2) lab::glut::exitFullscreen();
	}
	//tasta speciala ridicata
	void notifySpecialKeyReleased(int key_released, int mouse_x, int mouse_y){}
	//drag cu mouse-ul
	void notifyMouseDrag(int mouse_x, int mouse_y){ }
	//am miscat mouseul (fara sa apas vreun buton)
	void notifyMouseMove(int mouse_x, int mouse_y){ }
	//am apasat pe un boton
	void notifyMouseClick(int button, int state, int mouse_x, int mouse_y){ }
	//scroll cu mouse-ul
	void notifyMouseScroll(int wheel, int direction, int mouse_x, int mouse_y){ std::cout<<"Mouse scroll"<<std::endl;}

};

int main(){
	//initializeaza GLUT (fereastra + input + context OpenGL)
	lab::glut::WindowInfo window(std::string("lab shadere 1"),800,600,100,100,true);
	lab::glut::ContextInfo context(3,3,false);
	lab::glut::FramebufferInfo framebuffer(true,true,true,true);
	lab::glut::init(window,context, framebuffer);

	//initializeaza GLEW (ne incarca functiile openGL, altfel ar trebui sa facem asta manual!)
	glewExperimental = true;
	glewInit();
	std::cout<<"GLEW:initializare"<<std::endl;

	//creem clasa noastra si o punem sa asculte evenimentele de la GLUT
	//DUPA GLEW!!! ca sa avem functiile de OpenGL incarcate inainte sa ii fie apelat constructorul
	Lab mylab;
	lab::glut::setListener(&mylab);

	//run
	lab::glut::run();

	return 0;
}