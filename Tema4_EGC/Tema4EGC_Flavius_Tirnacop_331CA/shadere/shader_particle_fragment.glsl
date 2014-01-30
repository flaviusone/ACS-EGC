#version 330
layout(location = 0) out vec4 out_color;

uniform sampler2D textura1;

in vec2 texcoord;
in vec3 color;

void main(){

	vec3 tex1 = texture(textura1, texcoord).xyz;
	// alpha discarding
	if(tex1.r >= 0.9 && tex1.g >= 0.9 && tex1.b >= 0.9) discard;
	tex1 = color;
	out_color = vec4(tex1, 1);
}		