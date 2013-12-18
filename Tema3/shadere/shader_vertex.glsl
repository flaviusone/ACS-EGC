#version 330

layout(location = 0) in vec3 in_position;		
layout(location = 1) in vec3 in_color;		

uniform mat4 model_matrix, view_matrix, projection_matrix;

out vec3 vertex_to_fragment_color;

void main(){

	vertex_to_fragment_color = in_color;

	gl_Position = projection_matrix*view_matrix*model_matrix*vec4(in_position,1); 
}
