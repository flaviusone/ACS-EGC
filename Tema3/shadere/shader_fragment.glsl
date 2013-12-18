#version 330
layout(location = 0) out vec4 out_color;

in vec3 vertex_to_fragment_color;

void main(){

	out_color = vec4(vertex_to_fragment_color,1);
}