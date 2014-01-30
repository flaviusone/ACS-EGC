/*
* Author: Flavius Tirnacop
* Grupa: 331CA
* Clasa generica object pentru obiecte
*/

//interfata cu glut, ne ofera fereastra, input, context opengl
#include "lab_glut.hpp"
#define PI 3.1415926535
class Object{

//variabile
public:
	glm::mat4 model_matrix;
	float directie = 0;
	unsigned int mesh_vbo, mesh_ibo, mesh_vao, mesh_num_indices;	//containere opengl pentru vertecsi, indecsi si stare
//metode
public:
	Object(char* a){
		model_matrix = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		load_obj(a);
	};
	~Object(){
		//distruge mesh incarcat
		glDeleteBuffers(1, &mesh_vbo);
		glDeleteBuffers(1, &mesh_ibo);
		glDeleteVertexArrays(1, &mesh_vao);
	};
	void translate(float x, float y, float z){
		model_matrix = glm::translate(model_matrix, glm::vec3(x, y, z));
	}
	void translate2(glm::vec3 x){
		model_matrix = glm::translate(model_matrix,x);
	}
	void rotate(float angle, float x, float y, float z){
		model_matrix = glm::rotate(model_matrix, angle, glm::vec3(x, y, z));
	}
	void scale(float x, float y, float z){
		model_matrix = glm::scale(model_matrix, glm::vec3(x, y, z));
	}
	void load_obj(char* a){
		lab::loadObj(a, mesh_vao, mesh_vbo, mesh_ibo, mesh_num_indices);
	}

};