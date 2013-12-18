//-------------------------------------------------------------------------------------------------
// Descriere: fisier main
//
// Autor: student
// Data: today
//-------------------------------------------------------------------------------------------------

//incarcator de meshe
#include "lab_mesh_loader.hpp"
 
//geometrie: drawSolidCube, drawWireTeapot...
#include "lab_geometry.hpp"

//incarcator de shadere
#include "lab_shader_loader.hpp"

//interfata cu glut, ne ofera fereastra, input, context opengl
#include "lab_glut.hpp"

//camera
#include "lab_camera.hpp"

//time
#include <ctime>


class Laborator : public lab::glut::WindowListener{

//variabile
private:
	glm::mat4 model_matrix, projection_matrix;											//matrici 4x4 pt modelare vizualizare proiectie
	lab::Camera cam;
	unsigned int gl_program_shader;														//id-ul de opengl al obiectului de tip program shader
	unsigned int screen_width, screen_height;
	unsigned int mesh_vbo, mesh_ibo, mesh_vao, mesh_num_indices;						//containere opengl pentru vertecsi, indecsi si stare

//metode
public:
	
	//constructor .. e apelat cand e instantiata clasa
	Laborator(){
		//setari pentru desenare, clear color seteaza culoarea de clear pentru ecran (format R,G,B,A)
		glClearColor(0.5,0.5,0.5,1);
		glClearDepth(1);			//clear depth si depth test (nu le studiem momentan, dar avem nevoie de ele!)
		glEnable(GL_DEPTH_TEST);	//sunt folosite pentru a determina obiectele cele mai apropiate de camera (la curs: algoritmul pictorului, algoritmul zbuffer)
		
		//incarca un shader din fisiere si gaseste locatiile matricilor relativ la programul creat
		gl_program_shader = lab::loadShader("shadere\\shader_vertex.glsl", "shadere\\shader_fragment.glsl");
		
		//incarca un mesh
		lab::loadObj("resurse\\bunny.obj",mesh_vao, mesh_vbo, mesh_ibo, mesh_num_indices);	

		//matrici de modelare si vizualizare
		model_matrix = glm::mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
		cam.set(glm::vec3(0,0,40), glm::vec3(0,0,0), glm::vec3(0,1,0));

		//desenare wireframe
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(10);
		glPointSize(10);
	}

	//destructor .. e apelat cand e distrusa clasa
	~Laborator(){
		//distruge shader
		glDeleteProgram(gl_program_shader);

		//distruge mesh incarcat
		glDeleteBuffers(1,&mesh_vbo);
		glDeleteBuffers(1,&mesh_ibo);
		glDeleteVertexArrays(1,&mesh_vao);
	}

	
	//--------------------------------------------------------------------------------------------
	//functii de cadru ---------------------------------------------------------------------------

	//functie chemata inainte de a incepe cadrul de desenare, o folosim ca sa updatam situatia scenei ( modelam/simulam scena)
	void notifyBeginFrame(){
		//rotatie
		static float angle=0;
		angle = 0.1f;
		model_matrix = glm::rotate(model_matrix,angle,glm::vec3(0,1,0));
	}
	//functia de afisare (lucram cu banda grafica)
	void notifyDisplayFrame(){
		
		//pe tot ecranul
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//cadru normal
		{
			glViewport(0,0, screen_width/2, screen_height);
			
			//foloseste shaderul
			glUseProgram(gl_program_shader);
				
			//trimite variabile uniforme la shader
			glUniformMatrix4fv(glGetUniformLocation(gl_program_shader,"model_matrix"),1,false,glm::value_ptr(model_matrix));
			glUniformMatrix4fv(glGetUniformLocation(gl_program_shader,"view_matrix"),1,false,glm::value_ptr(cam.getViewMatrix()));
			glUniformMatrix4fv(glGetUniformLocation(gl_program_shader,"projection_matrix"),1,false,glm::value_ptr(projection_matrix));
		
			//bind obiect
			glBindVertexArray(mesh_vao);
			glDrawElements(GL_TRIANGLES, mesh_num_indices, GL_UNSIGNED_INT, 0);
		}
		
		//cadru vazut din alt punct de vedere
		{
			glViewport(screen_width/2,0, screen_width/2, screen_height);
			
			//foloseste shaderul
			glUseProgram(gl_program_shader);
				
			//trimite variabile uniforme la shader
			glUniformMatrix4fv(glGetUniformLocation(gl_program_shader,"model_matrix"),1,false,glm::value_ptr(model_matrix));
			glm::mat4 view_matrix = glm::lookAt(glm::vec3(50,50,50), glm::vec3(0,0,0), glm::vec3(0,1,0));
			glUniformMatrix4fv(glGetUniformLocation(gl_program_shader,"view_matrix"),1,false,glm::value_ptr(view_matrix));
			glUniformMatrix4fv(glGetUniformLocation(gl_program_shader,"projection_matrix"),1,false,glm::value_ptr(projection_matrix));
		
			//bind obiect
			glBindVertexArray(mesh_vao);
			glDrawElements(GL_TRIANGLES, mesh_num_indices, GL_UNSIGNED_INT, 0);

			//deseneaza axe camera
			glUniformMatrix4fv(glGetUniformLocation(gl_program_shader,"model_matrix"),1,false,glm::value_ptr(glm::mat4()));	//identity
			cam.drawGeometry();
		}
		
	}
	//functie chemata dupa ce am terminat cadrul de desenare (poate fi folosita pt modelare/simulare)
	void notifyEndFrame(){}
	//functei care e chemata cand se schimba dimensiunea ferestrei initiale
	void notifyReshape(int width, int height, int previos_width, int previous_height){
		//reshape
		if(height==0) height=1;
		screen_width = width;
		screen_height = height;
		float aspect = width*0.5f / height;
		projection_matrix = glm::perspective(75.0f, aspect,0.1f, 10000.0f);
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
		}
		if(key_pressed == 'i'){
			static bool wire =true;
			wire=!wire;
			glPolygonMode(GL_FRONT_AND_BACK, (wire?GL_LINE:GL_FILL));
		}
		if(key_pressed == 'w') { cam.translateForward(1.0f); }
		if(key_pressed == 'a') { cam.translateRight(-1.0f); }
		if(key_pressed == 's') { cam.translateForward(-1.0f); }
		if(key_pressed == 'd') { cam.translateRight(1.0f); }
		if(key_pressed == 'r') { cam.translateUpword(1.0f); }
		if(key_pressed == 'f') { cam.translateUpword(-1.0f); }
		if(key_pressed == 'q') { cam.rotateFPSoY(1.0f); }
		if(key_pressed == 'e') { cam.rotateFPSoY(-1.0f); }
		if(key_pressed == 'z') { cam.rotateFPSoZ(-1.0f); }
		if(key_pressed == 'c') { cam.rotateFPSoZ(1.0f); }
		if(key_pressed == 't') { cam.rotateFPSoX(1.0f); }
		if(key_pressed == 'g') { cam.rotateFPSoX(-1.0f); }
		if(key_pressed == 'o') { cam.set(glm::vec3(0,0,40), glm::vec3(0,0,0), glm::vec3(0,1,0)); }
		if(key_pressed == '1') { cam.rotateTPSoX(1.0f,40.0f); }
		if(key_pressed == '2') { cam.rotateTPSoX(-1.0f,40.0f); }
		if(key_pressed == '3') { cam.rotateTPSoY(1.0f,40.0f); }
		if(key_pressed == '4') { cam.rotateTPSoY(-1.0f,40.0f); }
		if(key_pressed == '5') { cam.rotateTPSoZ(1.0f,40.0f); }
		if(key_pressed == '6') { cam.rotateTPSoZ(-1.0f,40.0f); }
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
	lab::glut::WindowInfo window(std::string("lab shadere 3 - camera"),800,600,100,100,true);
	lab::glut::ContextInfo context(3,3,false);
	lab::glut::FramebufferInfo framebuffer(true,true,true,true);
	lab::glut::init(window,context, framebuffer);

	//initializeaza GLEW (ne incarca functiile openGL, altfel ar trebui sa facem asta manual!)
	glewExperimental = true;
	glewInit();
	std::cout<<"GLEW:initializare"<<std::endl;

	//creem clasa noastra si o punem sa asculte evenimentele de la GLUT
	//DUPA GLEW!!! ca sa avem functiile de OpenGL incarcate inainte sa ii fie apelat constructorul (care creeaza obiecte OpenGL)
	Laborator mylab;
	lab::glut::setListener(&mylab);

	//taste
	std::cout<<"Taste:"<<std::endl<<"\tESC ... iesire"<<std::endl<<"\tSPACE ... reincarca shadere"<<std::endl<<"\ti ... toggle wireframe"<<std::endl<<"\to ... reseteaza camera"<<std::endl;
	std::cout<<"\tw ... translatie camera in fata"<<std::endl<<"\ts ... translatie camera inapoi"<<std::endl;
	std::cout<<"\ta ... translatie camera in stanga"<<std::endl<<"\td ... translatie camera in dreapta"<<std::endl;
	std::cout<<"\tr ... translatie camera in sus"<<std::endl<<"\tf ... translatie camera jos"<<std::endl;
	std::cout<<"\tq ... rotatie camera FPS pe Oy, minus"<<std::endl<<"\te ... rotatie camera FPS pe Oy, plus"<<std::endl;
	std::cout<<"\tz ... rotatie camera FPS pe Oz, minus"<<std::endl<<"\tc ... rotatie camera FPS pe Oz, plus"<<std::endl;

	//run
	lab::glut::run();

	return 0;
}