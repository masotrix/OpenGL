#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vPos_model;
layout(location = 1) in vec2 vUV;
layout(location = 2) in vec3 vNormal_model;

out vec2 UV;
out vec3 posWorld;
out vec3 normal_camera;
out vec3 eyeDir_camera;
out vec3 lDir_camera;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 lPos_world;

void main(){

	gl_Position =  MVP * vec4(vPos_model,1);
	
	posWorld = (M * vec4(vPos_model,1)).xyz;
	
	vec3 vPos_camera = ( V * M * vec4(vPos_model,1)).xyz;
	eyeDir_camera = vec3(0,0,0) - vPos_camera;

	vec3 lPos_camera = ( V * M * vec4(lPos_world,1)).xyz;
	lDir_camera = lPos_camera + eyeDir_camera;
	
	normal_camera = ( V * M * vec4(vNormal_model,0)).xyz; 
	
	UV = vUV;
}

