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

//texturi
#include "lab_texture_loader.hpp"

//time
#include <ctime>

#include "Object.hpp"
#include "Particle.hpp"

#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

class Laborator : public lab::glut::WindowListener{

//variabile
private:
	glm::mat4 model_matrix, view_matrix, projection_matrix;								//matrici 4x4 pt modelare vizualizare proiectie
	unsigned int gl_program_shader_phong;												//id obiect shader phong
	unsigned int gl_particle_shader;
	unsigned int gl_program_shader_curent;												//id obiect shader curent

	glm::vec3 light_position;
	glm::vec3 eye_position;
	unsigned int material_shininess;
	float material_kd;
	float material_ks;
	float timp,timp2;

	unsigned int face_texture,note_texture;
	int state = 3;
	clock_t t, old_t = 0;
	std::vector<Particle*> particles;
	Object *girl_annoyed, *girl_sleep, *girl_surprise, *girl_sleep2;

//metode
public:
	
	//constructor .. e apelat cand e instantiata clasa
	Laborator(){
		//setari pentru desenare, clear color seteaza culoarea de clear pentru ecran (format R,G,B,A)
		glClearColor(0.5,0.5,0.5,1);
		glClearDepth(1);			//clear depth si depth test (nu le studiem momentan, dar avem nevoie de ele!)
		glEnable(GL_DEPTH_TEST);	//sunt folosite pentru a determina obiectele cele mai apropiate de camera (la curs: algoritmul pictorului, algoritmul zbuffer)
		
		//incarca un shader din fisiere si gaseste locatiile matricilor relativ la programul creat
		gl_program_shader_phong = lab::loadShader("shadere\\shader_phong_vertex.glsl", "shadere\\shader_phong_fragment.glsl");
		gl_program_shader_curent = gl_program_shader_phong;
		gl_particle_shader = lab::loadShader("shadere\\shader_particle_vertex.glsl", "shadere\\shader_particle_fragment.glsl");
		
		
	
		//lumina & material
		eye_position = glm::vec3(0,11,23);
		light_position = glm::vec3(0,11,23);
		material_shininess = 100;
		material_kd = 0.5;
		material_ks = 0.5;

		//matrici de modelare si vizualizare
		model_matrix = glm::mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
		view_matrix = glm::lookAt(eye_position, glm::vec3(0,8,0), glm::vec3(0,1,0));

		//desenare wireframe
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		/*----------------------------------MY PART START---------------------------------------*/

		//incarca texturi
		face_texture = lab::loadTextureBMP("resurse\\girl_texture.bmp");
		note_texture = lab::loadTextureBMP("resurse\\music.bmp");

		// Incarca si muta cap
		girl_annoyed	= new Object("resurse\\girl_annoyed.obj");	
		girl_annoyed->scale(6,6,6);
		girl_annoyed->translate(0, -5, 2);
		girl_annoyed->rotate(15, 0, 1, 0);
		
		
		// Incarca si muta cap
		girl_sleep		= new Object("resurse\\girl_sleep.obj");
		girl_sleep->scale(6, 6, 6);
		girl_sleep->translate(0, -5, 2);
		girl_sleep->rotate(15, 0, 1, 0);

		// Incarca si muta cap
		girl_sleep2 = new Object("resurse\\girl_sleep.obj");
		girl_sleep2->scale(6, 6, 6);
		girl_sleep2->translate(0, -5, 2);
		girl_sleep2->rotate(15, 0, 1, 0);

		// Incarca si muta cap
		girl_surprise	= new Object("resurse\\girl_surprise.obj");
		girl_surprise->scale(6, 6, 6);
		girl_surprise->translate(0, -5, 2);
		girl_surprise->rotate(15, 0, 1, 0);


		// Legare atribute
		glBindVertexArray(girl_sleep->mesh_vao);
		glBindBuffer(GL_ARRAY_BUFFER, girl_surprise->mesh_vbo);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)(sizeof(float)* 3));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)(2 * sizeof(float)* 3));
		// Legare atribute
		glBindVertexArray(girl_surprise->mesh_vao);
		glBindBuffer(GL_ARRAY_BUFFER, girl_annoyed->mesh_vbo);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)(sizeof(float)* 3));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)(2 * sizeof(float)* 3));
		// Legare atribute
		glBindVertexArray(girl_annoyed->mesh_vao);
		glBindBuffer(GL_ARRAY_BUFFER, girl_sleep2->mesh_vbo);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)(sizeof(float)* 3));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)(2 * sizeof(float)* 3));
		// Legare atribute
		glBindVertexArray(girl_sleep2->mesh_vao);
		glBindBuffer(GL_ARRAY_BUFFER, girl_sleep->mesh_vbo);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)(sizeof(float)* 3));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(lab::VertexFormat), (void*)(2 * sizeof(float)* 3));

		
		for (int i = 0; i < 1000; i++){
			Particle *particle = new Particle();
			particles.push_back(particle);
		}
		/*----------------------------------MY PART END---------------------------------------*/
	}

	//destructor .. e apelat cand e distrusa clasa
	~Laborator(){
		//distruge shadere
		glDeleteProgram(gl_program_shader_phong);
	}


	//--------------------------------------------------------------------------------------------
	//functii de cadru ---------------------------------------------------------------------------

	//functie chemata inainte de a incepe cadrul de desen are, o folosim ca sa updatam situatia scenei ( modelam/simulam scena)
	void notifyBeginFrame(){
		t = clock();
		timp = (((float)t) - ((float)old_t)) / CLOCKS_PER_SEC;
		if (timp > 4){
			state++;
			if (state == 4) state = 0;
			old_t = t;
			timp = 0;
		}
	}
	//functia de afisare (lucram cu banda grafica)
	void notifyDisplayFrame(){

		//bufferele din framebuffer sunt aduse la valorile initiale (setate de clear color si cleardepth)
		//adica se sterge ecranul si se pune culoare (si alte propietati) initiala
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//foloseste shaderul
		glUseProgram(gl_program_shader_curent);
				
		//trimite variabile uniforme la shader
		
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader_curent, "view_matrix"),1,false,glm::value_ptr(view_matrix));
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader_curent, "projection_matrix"),1,false,glm::value_ptr(projection_matrix));
		glUniform3f(glGetUniformLocation(gl_program_shader_curent, "light_position"),light_position.x, light_position.y, light_position.z);
		glUniform3f(glGetUniformLocation(gl_program_shader_curent, "eye_position"),eye_position.x, eye_position.y, eye_position.z);
		glUniform1i(glGetUniformLocation(gl_program_shader_curent, "material_shininess"),material_shininess);
		glUniform1f(glGetUniformLocation(gl_program_shader_curent, "material_kd"),material_kd);
		glUniform1f(glGetUniformLocation(gl_program_shader_curent, "material_ks"),material_ks);
		glUniform1f(glGetUniformLocation(gl_program_shader_curent, "time"), (float)timp);

		switch (state)
		{
		case 0:
			//desenez girl_sleeping
			glUniformMatrix4fv(glGetUniformLocation(gl_program_shader_curent, "model_matrix"), 1, false, glm::value_ptr(girl_sleep->model_matrix));

			glBindVertexArray(girl_sleep->mesh_vao);
			glDrawElements(GL_TRIANGLES, girl_sleep->mesh_num_indices, GL_UNSIGNED_INT, 0);	
			
			//adaug textura
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, face_texture);
			glUniform1i(glGetUniformLocation(gl_program_shader_curent, "textura1"), 0);

			//trimti variabile uniforme la particle_shader
			glUseProgram(gl_particle_shader);
			
			glUniformMatrix4fv(glGetUniformLocation(gl_particle_shader, "view_matrix"), 1, false, glm::value_ptr(view_matrix));
			glUniformMatrix4fv(glGetUniformLocation(gl_particle_shader, "projection_matrix"), 1, false, glm::value_ptr(projection_matrix));
			glUniform1f(glGetUniformLocation(gl_particle_shader, "time"), (float)timp);
			
			// Particule
			for (int i = 0; i < particles.size(); i++){
				glUniformMatrix4fv(glGetUniformLocation(gl_particle_shader, "model_matrix"), 1, false, glm::value_ptr(particles[i]->model_matrix));
				glUniform3f(glGetUniformLocation(gl_particle_shader, "culoare"), particles[i]->culoare.x, particles[i]->culoare.y, particles[i]->culoare.z);
				glUniform3f(glGetUniformLocation(gl_particle_shader, "viteza"), particles[i]->viteza.x, particles[i]->viteza.y, particles[i]->viteza.z);
				glBindVertexArray(particles[i]->vao);
				glDrawElements(GL_TRIANGLES, particles[i]->num_indices, GL_UNSIGNED_INT, 0);

				// Add texture
				glActiveTexture(GL_TEXTURE0 + 1);
				glBindTexture(GL_TEXTURE_2D, note_texture);
				glUniform1i(glGetUniformLocation(gl_particle_shader, "textura1"), 1);
			}
			break;
		case 1:
			//desenez girl_surprise
			glUniformMatrix4fv(glGetUniformLocation(gl_program_shader_curent, "model_matrix"), 1, false, glm::value_ptr(girl_surprise->model_matrix));

			glBindVertexArray(girl_surprise->mesh_vao);
			glDrawElements(GL_TRIANGLES, girl_surprise->mesh_num_indices, GL_UNSIGNED_INT, 0);

			//adaug textura
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, face_texture);
			glUniform1i(glGetUniformLocation(gl_program_shader_curent, "textura1"), 0);

			//trimti variabile uniforme la particle_shader
			glUseProgram(gl_particle_shader);
			timp2 = timp + 4;

			glUniformMatrix4fv(glGetUniformLocation(gl_particle_shader, "view_matrix"), 1, false, glm::value_ptr(view_matrix));
			glUniformMatrix4fv(glGetUniformLocation(gl_particle_shader, "projection_matrix"), 1, false, glm::value_ptr(projection_matrix));
			glUniform1f(glGetUniformLocation(gl_particle_shader, "time"), (float)timp2);

			// Particule
			for (int i = 0; i < particles.size(); i++){
				glUniformMatrix4fv(glGetUniformLocation(gl_particle_shader, "model_matrix"), 1, false, glm::value_ptr(particles[i]->model_matrix));
				glUniform3f(glGetUniformLocation(gl_particle_shader, "culoare"), particles[i]->culoare.x, particles[i]->culoare.y, particles[i]->culoare.z);
				glUniform3f(glGetUniformLocation(gl_particle_shader, "viteza"), particles[i]->viteza.x, particles[i]->viteza.y, particles[i]->viteza.z);
				glBindVertexArray(particles[i]->vao);
				glDrawElements(GL_TRIANGLES, particles[i]->num_indices, GL_UNSIGNED_INT, 0);

				// Add texture
				glActiveTexture(GL_TEXTURE0 + 1);
				glBindTexture(GL_TEXTURE_2D, note_texture);
				glUniform1i(glGetUniformLocation(gl_particle_shader, "textura1"), 1);
			}
			break;
		case 2:
			//desenez girl_annoyed
			glUniformMatrix4fv(glGetUniformLocation(gl_program_shader_curent, "model_matrix"), 1, false, glm::value_ptr(girl_annoyed->model_matrix));

			glBindVertexArray(girl_annoyed->mesh_vao);
			glDrawElements(GL_TRIANGLES, girl_annoyed->mesh_num_indices, GL_UNSIGNED_INT, 0);
			
			//adaug textura
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, face_texture);
			glUniform1i(glGetUniformLocation(gl_program_shader_curent, "textura1"), 0);

			break;
		case 3:
			//desenez girl_sleeping
			glUniformMatrix4fv(glGetUniformLocation(gl_program_shader_curent, "model_matrix"), 1, false, glm::value_ptr(girl_sleep2->model_matrix));

			glBindVertexArray(girl_sleep2->mesh_vao);
			glDrawElements(GL_TRIANGLES, girl_sleep2->mesh_num_indices, GL_UNSIGNED_INT, 0);

			//adaug textura
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, face_texture);
			glUniform1i(glGetUniformLocation(gl_program_shader_curent, "textura1"), 0);


			break;
		default:
			break;
		}

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
			glDeleteProgram(gl_program_shader_phong);
			gl_program_shader_phong = lab::loadShader("shadere\\shader_phong_vertex.glsl", "shadere\\shader_phong_fragment.glsl");
			gl_program_shader_curent = gl_program_shader_phong;
		}
		if(key_pressed == 'w'){
			static bool wire =true;
			wire=!wire;
			glPolygonMode(GL_FRONT_AND_BACK, (wire?GL_LINE:GL_FILL));
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
	srand(time(0));

	//initializeaza GLUT (fereastra + input + context OpenGL)
	lab::glut::WindowInfo window(std::string("Tema 4"),800,600,100,100,true);
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

	//run
	lab::glut::run();

	return 0;
}