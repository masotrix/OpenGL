#version 330 core
#define LIGHTS 10

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vPos_model;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal_model;

out vec3 vPos_world, fColor, vNormal_camera;
out vec3 eDir_camera, lDir_camera[LIGHTS];

// Values that stay constant for the whole mesh.
uniform mat4 MVP, V, M;
uniform lights { vec3 pos[LIGHTS]; };



// Computes Light directions

void computeLightDirections(){

    for (int i=0; i<pos.length(); i++){
        vec3 lPos_camera = (V*M*vec4(pos[i],1)).xyz;
        lDir_camera[i] = normalize(lPos_camera + eDir_camera);
    }
}


void main(){

	gl_Position      =  MVP * vec4(vPos_model,1);
	vPos_world       = (M * vec4(vPos_model,1)).xyz;
	fColor           = vColor;
	vec3 vPos_camera = (V*M*vec4(vPos_model,1)).xyz;
	eDir_camera      = vec3(0,0,0) - vPos_camera;
	vNormal_camera   = (V*M*vec4(vNormal_model,0)).xyz;

    computeLightDirections();
}
