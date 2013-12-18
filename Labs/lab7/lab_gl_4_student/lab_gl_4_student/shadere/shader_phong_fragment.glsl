#version 330
layout(location = 0) out vec4 out_color;

uniform vec3 light_position;
uniform vec3 eye_position;
uniform int material_shininess;
uniform float material_kd;
uniform float material_ks;

in vec3 world_pos;
in vec3 world_normal;

void main(){
	
	//TODO
	float light=0;

		vec3 L = normalize ( light_position - world_pos);
	vec3 V = normalize ( eye_position - world_pos);
	vec3 H = normalize(L+V);

	
	float AMBIENT = 0.3;
	float DIFUZA  = max(dot(world_normal,L),0);

	float primestelumina;
	if(dot(world_normal,L)>0)
		primestelumina = 1;
	else 
		primestelumina = 0;

	float SPECULARA = primestelumina * pow(max(dot(world_normal,H),0),material_shininess);

	

	

	//vec3 culoarelumina = vec3(1,1,1);

	light = material_kd * (AMBIENT+DIFUZA) + material_ks*SPECULARA;

	out_color = vec4(light,light, light,1);
}