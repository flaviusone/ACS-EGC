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
	glm::mat4 original_model_matrix;
	glm::mat4 model_matrix, view_matrix, projection_matrix;								//matrici 4x4 pt modelare vizualizare proiectie
	unsigned int location_model_matrix, location_view_matrix, location_projection_matrix;//locatii la nivel de shader ale matricilor (un pointer/offset)
	unsigned int gl_program_shader;														//id-ul de opengl al obiectului de tip program shader

	unsigned int mesh_vbo, mesh_ibo, mesh_vao, mesh_num_indices;						//containere opengl pentru vertecsi, indecsi si stare
	// vbo = vertex_buffer_object, in el stau vertecsii
	// ibo = index buffer object, deseori numit si element buffer object, in el stau indecsii
	// vao = vertex array object, container de stare (care e vbo-ul curent, care e ibo-ul curent, cum se trimit atributele, etc)
	// num_indices = cati indecsi are obiectul, necesar pt comanda de draw

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
		location_model_matrix = glGetUniformLocation(gl_program_shader, "model_matrix");
		location_view_matrix = glGetUniformLocation(gl_program_shader, "view_matrix");
		location_projection_matrix = glGetUniformLocation(gl_program_shader, "projection_matrix");
		
		//incarca un mesh
		lab::loadObj("resurse\\dragon.obj",mesh_vao, mesh_vbo, mesh_ibo, mesh_num_indices);	
		//createMeshManual();																

		//matrici de modelare si vizualizare
		original_model_matrix = glm::mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
		view_matrix = glm::lookAt(glm::vec3(0,0,50), glm::vec3(0,0,0), glm::vec3(0,1,0));

		//desenare wireframe
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
	//functii de constructie geometrie------------------------------------------------------------
	void createMeshManual(){
		struct MYVERTEXFORMAT{
			glm::vec3 pozitie;
			glm::vec3 culoare;

			//unsigned int mesh_vbo, mesh_ibo, mesh_vao, mesh_num_indices;						//containere opengl pentru vertecsi, indecsi si stare

			MYVERTEXFORMAT(){
				pozitie = glm::vec3(0, 0, 0);
				culoare = glm::vec3(1, 1, 1);
			}
			MYVERTEXFORMAT(float px,float py,float pz,float cx,float cy,float cz){
				pozitie = glm::vec3(px,py,pz);
				culoare = glm::vec3(cx,cy,cz);
			}
		};

		std::vector <MYVERTEXFORMAT> vertices;
		std::vector < glm::uvec3> index;

		vertices.push_back(MYVERTEXFORMAT(-10, -10, 10, 0, 0, 1));
		vertices.push_back(MYVERTEXFORMAT(10, -10, 10, 1, 0, 1));
		vertices.push_back(MYVERTEXFORMAT(10, -10, -10, 1, 0, 0));
		vertices.push_back(MYVERTEXFORMAT(-10, -10, -10, 0, 0, 0));
		vertices.push_back(MYVERTEXFORMAT(-10, 10, 10, 0, 1, 1));
		vertices.push_back(MYVERTEXFORMAT(10, 10, 10, 1, 1, 1));
		vertices.push_back(MYVERTEXFORMAT(10, 10, -10, 1, 1, 0));
		vertices.push_back(MYVERTEXFORMAT(-10, 10, -10, 0, 1, 0));

		index.push_back(glm::uvec3(0, 1,2));
		index.push_back(glm::uvec3(2,3,0));
		index.push_back(glm::uvec3(4,5,6));
		index.push_back(glm::uvec3(6,7,4));
		index.push_back(glm::uvec3(0,1,5));
		index.push_back(glm::uvec3(5,4,0));
		index.push_back(glm::uvec3(3,2,6));
		index.push_back(glm::uvec3(6,7,3));
		index.push_back(glm::uvec3(1,2,6));
		index.push_back(glm::uvec3(6,5,1));
		index.push_back(glm::uvec3(3,0,4));
		index.push_back(glm::uvec3(4,7,3));
		//TODO

		//VAO
		glGenVertexArrays(1, &mesh_vao);
		glBindVertexArray(mesh_vao);


		//VBO
		glGenBuffers(1, &mesh_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(MYVERTEXFORMAT)* vertices.size(),&vertices[0],GL_STATIC_DRAW);

		//IBO
		glGenBuffers(1, &mesh_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*index.size() * 3, &index[0], GL_STATIC_DRAW);

		/*
		glEnableVertexAttribArray(0); 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MYVERTEXFORMAT), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MYVERTEXFORMAT), (void*)sizeof(glm::uvec3));
		*/
	
		/*
		unsigned int pipe = glGetAttribLocation(gl_program_shader, "in_position");
		glEnableVertexAttribArray(pipe);
		glVertexAttribPointer(pipe, 3, GL_FLOAT, GL_FALSE, sizeof(MYVERTEXFORMAT), (void*)0);

		unsigned int pipe2 = glGetAttribLocation(gl_program_shader, "in_color");
		glEnableVertexAttribArray(pipe2);
		glVertexAttribPointer(pipe2, 3, GL_FLOAT, GL_FALSE, sizeof(MYVERTEXFORMAT), (void*)sizeof(glm::uvec3)); */
		unsigned int pipe=0;
		unsigned int pipe2=1;
		glBindAttribLocation(gl_program_shader, pipe, "in_position");
			
		glBindAttribLocation(gl_program_shader, pipe2, "in_color");

		glEnableVertexAttribArray(pipe);
		glVertexAttribPointer(pipe, 3, GL_FLOAT, GL_FALSE, sizeof(MYVERTEXFORMAT), (void*)0);
		glEnableVertexAttribArray(pipe2);
		glVertexAttribPointer(pipe2, 3, GL_FLOAT, GL_FALSE, sizeof(MYVERTEXFORMAT), (void*)sizeof(glm::vec3));

		glLinkProgram(gl_program_shader);

		mesh_num_indices = index.size()*3;
	}





	//--------------------------------------------------------------------------------------------
	//functii de cadru ---------------------------------------------------------------------------

	//functie chemata inainte de a incepe cadrul de desenare, o folosim ca sa updatam situatia scenei ( modelam/simulam scena)
	void notifyBeginFrame(){

		//translatie
		static glm::vec3 translation = glm::vec3(0,0,0);
		translation = glm::vec3(10*sin( std::clock()/1000.f),0,0);		
		//model_matrix = glm::translate(original_model_matrix, translation);

		//rotatie
		static float angle=0;
		angle = 0.1f;
		model_matrix = glm::rotate(model_matrix,angle,glm::vec3(0,1,0));
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
		
		//bind obiect
		glBindVertexArray(mesh_vao);
		glDrawElements(GL_TRIANGLES, mesh_num_indices, GL_UNSIGNED_INT, 0);
		
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
			glDeleteProgram(gl_program_shader);
			gl_program_shader = lab::loadShader("shadere\\shader_vertex.glsl", "shadere\\shader_fragment.glsl");
			location_model_matrix = glGetUniformLocation(gl_program_shader, "model_matrix");
			location_view_matrix = glGetUniformLocation(gl_program_shader, "view_matrix");
			location_projection_matrix = glGetUniformLocation(gl_program_shader, "projection_matrix");
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

	//run
	lab::glut::run();

	return 0;
}