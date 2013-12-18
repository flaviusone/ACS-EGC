#version 330

layout(location = 0) in vec3 in_position;		
layout(location = 1) in vec3 in_normal;		

uniform mat4 model_matrix, view_matrix, projection_matrix;
uniform vec3 light_position;
uniform vec3 eye_position;
uniform int material_shininess;
uniform float material_kd;
uniform float material_ks;

out float light;

void main(){

	vec3 world_pos = (model_matrix * vec4(in_position,1)).xyz; 
	vec3 world_normal = normalize( mat3(model_matrix) * in_normal);

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

	
	

	gl_Position = projection_matrix*view_matrix*model_matrix*vec4(in_position,1); 
}
