#version 330

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;

uniform mat4 model_matrix, view_matrix, projection_matrix;

void main(){

	gl_Position = projection_matrix*view_matrix*model_matrix*vec4(in_position,1); 
}
