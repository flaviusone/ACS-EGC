#version 330

layout(location = 0) in vec3 in_position;		
layout(location = 1) in vec3 in_normal;		
layout(location = 2) in vec2 in_texcoord;
layout(location = 3) in vec3 in_position_final;		
layout(location = 4) in vec3 in_normal_final;		
layout(location = 5) in vec2 in_texcoord_final;

uniform mat4 model_matrix, view_matrix, projection_matrix;
uniform float time;

out vec3 world_pos;
out vec3 world_normal;

out vec2 texcoord;

void main(){

	vec3 change_p = (in_position_final - in_position) / 4;
	vec3 change_n = (in_normal_final - in_normal) / 4;
	vec2 change_t = (in_texcoord_final - in_texcoord) / 4;

	vec2 tex = in_texcoord + time* change_t;
	texcoord = tex;

	vec3 pos = in_position  + time* change_p;
	world_pos = ( model_matrix * vec4(pos,1) ).xyz;
	

	vec3 normal = in_normal + time* change_n;
	world_normal = normalize( mat3(model_matrix) * normal );


	gl_Position = projection_matrix*view_matrix*model_matrix*vec4(pos,1); 
}
