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

//time
#include <ctime>


class Laborator : public lab::glut::WindowListener{

//variabile
private:
	glm::mat4 model_matrix, view_matrix, projection_matrix;								//matrici 4x4 pt modelare vizualizare proiectie
	unsigned int gl_program_shader_gouraud;												//id obiect shader gouraud
	unsigned int gl_program_shader_phong;												//id obiect shader phong
	unsigned int gl_program_shader_curent;												//id obiect shader curent

	unsigned int mesh_vbo, mesh_ibo, mesh_vao, mesh_num_indices;						//containere opengl pentru vertecsi, indecsi si stare

	unsigned int mesh_vbo_sphere, mesh_ibo_sphere, mesh_vao_sphere, mesh_num_indices_sphere;	//containere opengl pentru vertecsi, indecsi si stare pentru sfera ce va fi pusa la pozitia luminii

	unsigned int mesh_vbo_ground, mesh_ibo_ground, mesh_vao_ground, mesh_num_indices_ground;	//containere opengl pentru vertecsi, indecsi si stare pentru sol

	glm::vec3 light_position;
	glm::vec3 eye_position;
	unsigned int material_shininess;
	float material_kd;
	float material_ks;

//metode
public:
	
	//constructor .. e apelat cand e instantiata clasa
	Laborator(){
		//setari pentru desenare, clear color seteaza culoarea de clear pentru ecran (format R,G,B,A)
		glClearColor(0.5,0.5,0.5,1);
		glClearDepth(1);			//clear depth si depth test (nu le studiem momentan, dar avem nevoie de ele!)
		glEnable(GL_DEPTH_TEST);	//sunt folosite pentru a determina obiectele cele mai apropiate de camera (la curs: algoritmul pictorului, algoritmul zbuffer)
		
		//incarca un shader din fisiere si gaseste locatiile matricilor relativ la programul creat
		gl_program_shader_gouraud = lab::loadShader("shadere\\shader_gouraud_vertex.glsl", "shadere\\shader_gouraud_fragment.glsl");
		gl_program_shader_phong = lab::loadShader("shadere\\shader_phong_vertex.glsl", "shadere\\shader_phong_fragment.glsl");
		gl_program_shader_curent = gl_program_shader_gouraud;
		
		//incarca un mesh
		lab::loadObj("resurse\\venus.obj",mesh_vao, mesh_vbo, mesh_ibo, mesh_num_indices);	

		//incarca o sfera
		lab::loadObj("resurse\\sphere.obj",mesh_vao_sphere, mesh_vbo_sphere, mesh_ibo_sphere, mesh_num_indices_sphere);	

		//incarca un plan
		lab::loadObj("resurse\\plane.obj",mesh_vao_ground, mesh_vbo_ground, mesh_ibo_ground, mesh_num_indices_ground);

		//lumina & material
		eye_position = glm::vec3(0,10,50);
		light_position = glm::vec3(10,7,25);
		material_shininess = 100;
		material_kd = 0.5;
		material_ks = 0.5;


		//matrici de modelare si vizualizare
		model_matrix = glm::mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
		view_matrix = glm::lookAt(eye_position, glm::vec3(0,0,0), glm::vec3(0,1,0));

		//desenare wireframe
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	//destructor .. e apelat cand e distrusa clasa
	~Laborator(){
		//distruge shadere
		glDeleteProgram(gl_program_shader_gouraud);
		glDeleteProgram(gl_program_shader_phong);

		//distruge mesh incarcat
		glDeleteBuffers(1,&mesh_vbo);
		glDeleteBuffers(1,&mesh_ibo);
		glDeleteVertexArrays(1,&mesh_vbo);

		//distruge sfera
		glDeleteBuffers(1,&mesh_vbo_sphere);
		glDeleteBuffers(1,&mesh_ibo_sphere);
		glDeleteVertexArrays(1,&mesh_vbo_sphere);

		//distruge solul
		glDeleteBuffers(1,&mesh_vbo_ground);
		glDeleteBuffers(1,&mesh_ibo_ground);
		glDeleteVertexArrays(1,&mesh_vbo_ground);
	}


	//--------------------------------------------------------------------------------------------
	//functii de cadru ---------------------------------------------------------------------------

	//functie chemata inainte de a incepe cadrul de desenare, o folosim ca sa updatam situatia scenei ( modelam/simulam scena)
	void notifyBeginFrame(){
		//rotatie lumina Oy
		float angle =0.005f;
		glm::vec3 lp = light_position;
		light_position.x = lp.x*cos(angle)-lp.z*sin(angle);
		light_position.z = lp.x*sin(angle)+lp.z*cos(angle);
		
	}
	//functia de afisare (lucram cu banda grafica)
	void notifyDisplayFrame(){
		//bufferele din framebuffer sunt aduse la valorile initiale (setate de clear color si cleardepth)
		//adica se sterge ecranul si se pune culoare (si alte propietati) initiala
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//foloseste shaderul
		glUseProgram(gl_program_shader_curent);
				
		//trimite variabile uniforme la shader
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader_curent, "model_matrix"),1,false,glm::value_ptr(model_matrix));
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader_curent, "view_matrix"),1,false,glm::value_ptr(view_matrix));
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader_curent, "projection_matrix"),1,false,glm::value_ptr(projection_matrix));
		glUniform3f(glGetUniformLocation(gl_program_shader_curent, "light_position"),light_position.x, light_position.y, light_position.z);
		glUniform3f(glGetUniformLocation(gl_program_shader_curent, "eye_position"),eye_position.x, eye_position.y, eye_position.z);
		glUniform1i(glGetUniformLocation(gl_program_shader_curent, "material_shininess"),material_shininess);
		glUniform1f(glGetUniformLocation(gl_program_shader_curent, "material_kd"),material_kd);
		glUniform1f(glGetUniformLocation(gl_program_shader_curent, "material_ks"),material_ks);
				
		//bind obiect
		glBindVertexArray(mesh_vao);
		glDrawElements(GL_TRIANGLES, mesh_num_indices, GL_UNSIGNED_INT, 0);

		//pune o sfera la pozitia luminii
		glm::mat4 matrice_translatie = glm::translate(model_matrix, glm::vec3(light_position.x,light_position.y,light_position.z));
		glm::mat4 matrice_scalare = glm::scale(model_matrix, glm::vec3(0.1,0.1,0.1));
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader_curent, "model_matrix"),1,false,glm::value_ptr(matrice_translatie * matrice_scalare));
		
		glBindVertexArray(mesh_vao_sphere);
		glDrawElements(GL_TRIANGLES, mesh_num_indices_sphere, GL_UNSIGNED_INT, 0);

		//pune si un sol
		matrice_translatie = glm::translate(model_matrix, glm::vec3(0,-10,-20));
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader_curent, "model_matrix"),1,false,glm::value_ptr(matrice_translatie));
		
		glBindVertexArray(mesh_vao_ground);
		glDrawElements(GL_TRIANGLES, mesh_num_indices_ground, GL_UNSIGNED_INT, 0);


	}
	//functie chemata dupa ce am terminat cadrul de desenare (poate fi folosita pt modelare/simulare)
	void notifyEndFrame(){}
	//functei care e chemata cand se schimba dimensiunea ferestrei initiale
	void notifyReshape(int width, int height, int previos_width, int previous_height){
		//reshape
		if(height==0) height=1;
		glViewport(0,0,width,height);
		projection_matrix = glm::perspective(90.0f, (float)width/(float)height,0.1f, 10000.0f);
	}


	//--------------------------------------------------------------------------------------------
	//functii de input output --------------------------------------------------------------------
	
	//tasta apasata
	void notifyKeyPressed(unsigned char key_pressed, int mouse_x, int mouse_y){
		if(key_pressed == 27) lab::glut::close();	//ESC inchide glut si 
		if(key_pressed == 32) {
			//SPACE reincarca shaderul si recalculeaza locatiile (offseti/pointeri)
			glDeleteProgram(gl_program_shader_gouraud);
			glDeleteProgram(gl_program_shader_phong);
			gl_program_shader_gouraud = lab::loadShader("shadere\\shader_gouraud_vertex.glsl", "shadere\\shader_gouraud_fragment.glsl");
			gl_program_shader_phong = lab::loadShader("shadere\\shader_phong_vertex.glsl", "shadere\\shader_phong_fragment.glsl");
			gl_program_shader_curent = gl_program_shader_gouraud;
		}
		if(key_pressed == 'w'){
			static bool wire =true;
			wire=!wire;
			glPolygonMode(GL_FRONT_AND_BACK, (wire?GL_LINE:GL_FILL));
		}
		if(key_pressed == '1'){
			gl_program_shader_curent = gl_program_shader_gouraud;
		}
		if(key_pressed == '2'){
			gl_program_shader_curent = gl_program_shader_phong;
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
	//DUPA GLEW!!! ca sa avem functiile de OpenGL incarcate inainte sa ii fie apelat constructorul (care creeaza obiecte OpenGL)
	Laborator mylab;
	lab::glut::setListener(&mylab);

	//taste
	std::cout<<"Taste:"<<std::endl<<"\tESC ... iesire"<<std::endl<<"\tSPACE ... reincarca shadere"<<std::endl<<"\tw ... toggle wireframe"<<std::endl;
	std::cout<<"\t1 ... foloseste shader Gouraud"<<std::endl<<"\t2 ... foloseste shader Phong"<<std::endl;

	//run
	lab::glut::run();

	return 0;
}