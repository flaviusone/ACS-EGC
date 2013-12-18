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


class Laborator : public lab::glut::WindowListener{

//variabile
private:
	glm::mat4 model_matrix_bamboo, model_matrix_earth, model_matrix_cube;				//matrici modelare pentru cele 3 obiecte
	glm::mat4 view_matrix, projection_matrix;											//matrici 4x4 pt modelare vizualizare proiectie
	unsigned int gl_program_shader;														//id-ul de opengl al obiectului de tip program shader
	unsigned int screen_width, screen_height;

	//meshe
	unsigned int earth_vbo, earth_ibo, earth_vao, earth_num_indices;					
	unsigned int bamboo_vbo, bamboo_ibo, bamboo_vao, bamboo_num_indices;				//containere opengl pentru vertecsi, indecsi si stare
	unsigned int cube_vbo, cube_ibo, cube_vao, cube_num_indices;		

	//texturi
	unsigned int earth_texture, bamboo_texture_color, bamboo_texture_alpha, cube_texture;

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
		
		//earth
		lab::loadObj("resurse\\earth.obj",earth_vao, earth_vbo, earth_ibo, earth_num_indices);	
		earth_texture = lab::loadTextureBMP("resurse\\earth.bmp");
		model_matrix_earth = glm::mat4(1,0,0,0,  0,1,0,0, 0,0,1,0, 0,0,0,1);

		//bamboo
		lab::loadObj("resurse\\bamboo.obj",bamboo_vao, bamboo_vbo, bamboo_ibo, bamboo_num_indices);	
		bamboo_texture_color = lab::loadTextureBMP("resurse\\bamboo.bmp");
		bamboo_texture_alpha = lab::loadTextureBMP("resurse\\bambooalpha.bmp");
		model_matrix_bamboo = glm::translate(glm::mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1),glm::vec3(-20,-10,0));

		//cube
		lab::loadObj("resurse\\cube.obj", cube_vao, cube_vbo, cube_ibo, cube_num_indices);
		cube_texture = createManualTexture(64,64);
		model_matrix_cube = glm::translate(glm::mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1),glm::vec3(20,0,0));
		
		//matrici de modelare si vizualizare
		view_matrix = glm::lookAt(glm::vec3(0,0,40), glm::vec3(0,0,0), glm::vec3(0,1,0));

		//desenare wireframe
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	//destructor .. e apelat cand e distrusa clasa
	~Laborator(){
		//distruge shader
		glDeleteProgram(gl_program_shader);

		//distruge obiecte
		glDeleteBuffers(1,&earth_vbo);	glDeleteBuffers(1,&earth_ibo);	glDeleteVertexArrays(1,&earth_vao);		glDeleteTextures(1, &earth_texture);
		glDeleteBuffers(1,&bamboo_vbo);	glDeleteBuffers(1,&bamboo_ibo);	glDeleteVertexArrays(1,&bamboo_vao);	glDeleteTextures(1, &bamboo_texture_alpha);		glDeleteTextures(1, &bamboo_texture_color);
		glDeleteBuffers(1,&cube_vbo);	glDeleteBuffers(1,&cube_ibo);	glDeleteVertexArrays(1,&cube_vao);		
	}

	//--------------------------------------------------------------------------------------------
	//functie manuala ----------------------------------------------------------------------------
	unsigned int createManualTexture(unsigned int width, unsigned int height){
		//TODO
		unsigned char* data = new unsigned char[width * height * 3];
		int color = 255;
		for (int i = 0; i < width; i++) {
			if (i % 8 == 0){
				if (color == 255){
					color = 0;
				}
				else color = 255;
			}

			for (int j = 0; j < height; j++) {
				if (j % 8 == 0){
					if (color == 255){
						color = 0;
					}
					else color = 255;
				}
				data[(i*height + j) * 3] = color;
				data[(i*height + j) * 3 + 1] = color;
				data[(i*height + j) * 3 + 2] = color;
			}
		}

		unsigned int gl_texture_object;
		glGenTextures(1, &gl_texture_object);

		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, gl_texture_object);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);

		//

		float maxAnisotropy; 
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
		
		//

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);

		return gl_texture_object;
	}

	
	//--------------------------------------------------------------------------------------------
	//functii de cadru ---------------------------------------------------------------------------

	//functie chemata inainte de a incepe cadrul de desenare, o folosim ca sa updatam situatia scenei ( modelam/simulam scena)
	void notifyBeginFrame(){
		//rotatie
		static float angle=0;
		angle = 0.1f;
		model_matrix_earth = glm::rotate(model_matrix_earth,angle,glm::vec3(0,1,0));
	}
	//functia de afisare (lucram cu banda grafica)
	void notifyDisplayFrame(){
		
		//pe tot ecranul
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//foloseste shaderul
		glUseProgram(gl_program_shader);
				
		//trimite variabile uniforme la shader
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader,"view_matrix"),1,false,glm::value_ptr(view_matrix));
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader,"projection_matrix"),1,false,glm::value_ptr(projection_matrix));

		//earth----------------------------
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader,"model_matrix"),1,false,glm::value_ptr(model_matrix_earth));

		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, earth_texture);
		unsigned int locatie = glGetUniformLocation(gl_program_shader, "textura1");
		glUniform1i(locatie, earth_texture);
		locatie = glGetUniformLocation(gl_program_shader, "has_alpha");
		glUniform1i(locatie, 0);

		glBindVertexArray(earth_vao);
		glDrawElements(GL_TRIANGLES, earth_num_indices, GL_UNSIGNED_INT, 0);
	
		////bamboo----------------------------
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader,"model_matrix"),1,false,glm::value_ptr(model_matrix_bamboo));
		
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, bamboo_texture_color);
		glActiveTexture(GL_TEXTURE0 + 2);
		glBindTexture(GL_TEXTURE_2D, bamboo_texture_alpha);

		locatie = glGetUniformLocation(gl_program_shader, "textura1");
		glUniform1i(locatie, 1);
		locatie = glGetUniformLocation(gl_program_shader, "textura2");
		glUniform1i(locatie, 2);


		locatie = glGetUniformLocation(gl_program_shader, "has_alpha");
		glUniform1i(locatie, 1);

		glBindVertexArray(bamboo_vao);
		glDrawElements(GL_TRIANGLES, bamboo_num_indices, GL_UNSIGNED_INT, 0);

		////cube----------------------------
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader,"model_matrix"),1,false,glm::value_ptr(model_matrix_cube));
		//TODO

		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, cube_texture);
		locatie = glGetUniformLocation(gl_program_shader, "textura1");
		glUniform1i(locatie, 1);
		locatie = glGetUniformLocation(gl_program_shader, "has_alpha");
		glUniform1i(locatie, 0);

		glBindVertexArray(cube_vao);
		glDrawElements(GL_TRIANGLES, cube_num_indices, GL_UNSIGNED_INT, 0);
	}
	//functie chemata dupa ce am terminat cadrul de desenare (poate fi folosita pt modelare/simulare)
	void notifyEndFrame(){}
	//functei care e chemata cand se schimba dimensiunea ferestrei initiale
	void notifyReshape(int width, int height, int previos_width, int previous_height){
		//reshape
		if(height==0) height=1;
		float aspect = (float)width / (float)height;
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
	void notifyMouseScroll(int wheel, int direction, int mouse_x, int mouse_y){ }

};

int main(){
	//initializeaza GLUT (fereastra + input + context OpenGL)
	lab::glut::WindowInfo window(std::string("lab shadere 5 - texturi"),800,600,100,100,true);
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