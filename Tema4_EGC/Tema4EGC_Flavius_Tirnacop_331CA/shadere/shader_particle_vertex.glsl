#version 330

layout(location = 0) in vec3 in_position;		
	
layout(location = 2) in vec2 in_texcoord;

uniform mat4 view_matrix, projection_matrix,model_matrix;
uniform vec3 culoare, viteza;
uniform float time;

out vec2 texcoord;
out vec3 color;

void main(){

	texcoord = in_texcoord;
	color = culoare;
	vec3 pos = in_position + time * viteza + vec3(-30, -10, 10);
	// formula billboards
	gl_Position = projection_matrix*model_matrix*(vec4(view_matrix[3].xyz, 0)+vec4(pos,1)); 
}
