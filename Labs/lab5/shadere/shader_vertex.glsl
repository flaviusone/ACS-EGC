#version 330

//3 variante: layout location pentru varianta 1 (Cea mai buna), layout location sau doar in/attribute pentru varianta 2, doar in pentru varianta 3.
//attribute e sintaxa veche (OpenGL 2) e recomandat sa folositi in

//layout(location = 0) in vec3 in_position;		
//layout(location = 1) in vec3 in_color;		

//attribute vec3 in_position;					
//attribute vec3 in_color;								

in vec3 in_position;
in vec3 in_color;


uniform mat4 model_matrix, view_matrix, projection_matrix;

out vec3 vertex_to_fragment_color;

void main(){

	vertex_to_fragment_color = in_color;

	gl_Position = projection_matrix*view_matrix*model_matrix*vec4(in_position,1); 
}
