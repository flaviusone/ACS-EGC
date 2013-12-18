#version 330
layout(location = 0) out vec4 out_color;

uniform vec4 object_color;


void main(){

	out_color = object_color;
}