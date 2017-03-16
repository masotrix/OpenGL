#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 posWorld;
in vec3 normal_camera;
in vec3 eyeDir_camera;
in vec3 lDir_camera;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform mat4 MV;
uniform vec3 lPos_world;

void main(){

	vec3 lColor = vec3(1,1,1);
	float lPower = 50.0f;
	
	vec3 diffColor = texture( myTextureSampler, UV ).rgb;
	vec3 ambColor = vec3(0.1,0.1,0.1) * diffColor;
	vec3 specColor = vec3(0.3,0.3,0.3);

	float dist = length( lPos_world - posWorld);

	vec3 n = normalize( normal_camera );
	vec3 l = normalize( lDir_camera );
	float cosTheta = clamp( dot( n,l ), 0,1 );
	
	vec3 E = normalize(eyeDir_camera);
	vec3 R = reflect(-l,n);
	float cosAlpha = clamp( dot( E,R ), 0,1 );
	
	color = 
		ambColor +
		diffColor*lColor*lPower * cosTheta / (dist*dist) +
		specColor*lColor*lPower * pow(cosAlpha,5) / (dist*dist);

}
