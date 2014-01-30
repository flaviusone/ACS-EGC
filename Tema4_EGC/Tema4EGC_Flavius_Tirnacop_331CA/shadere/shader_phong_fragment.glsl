#version 330
layout(location = 0) out vec4 out_color;

uniform vec3 light_position;
uniform vec3 eye_position;
uniform int material_shininess;
uniform float material_kd;
uniform float material_ks;

in vec3 world_pos;
in vec3 world_normal;

uniform sampler2D textura1;
uniform sampler2D textura2;
uniform int has_alpha;

in vec2 texcoord;


void main(){

	vec3 tex1 = texture(textura1, texcoord).xyz;
	vec3 tex2 = texture(textura2, texcoord).xyz;
	
	float light=0;

	vec3 l = normalize(light_position-world_pos);
	vec3 v = normalize(eye_position-world_pos);
	vec3 h = normalize(l+v);

	float ambientala = 0.1f;
	float difuza = material_kd*max(dot(world_normal,l),0);
	float spectrala = material_ks * pow(max(dot(world_normal , h ), 0),material_shininess)*(difuza<0 ?0:1);

	light = ambientala + difuza + spectrala;

	//out_color = vec4(light,light, light,1);
	out_color = vec4(tex1*1.4*light, 1);
}