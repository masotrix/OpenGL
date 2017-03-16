#version 330 core
#define LIGHTS 10

// Interpolated values from the vertex shaders
in vec3 vPos_world, fColor, vNormal_camera;
in vec3 eDir_camera, lDir_camera[LIGHTS];

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform mat4 MV, V, M;
uniform lights { vec3 pos[LIGHTS]; };



// Computes Light directions

vec3[LIGHTS] computeLightDirections(){

	vec3 lDir_camera[LIGHTS];
    for (int i=0; i<pos.length(); i++){
        vec3 lPos_camera = (V*M*vec4(pos[i],1)).xyz;
        lDir_camera[i] = normalize(lPos_camera + eDir_camera);
    }

	return lDir_camera;
}


// Iluminate

void iluminate(vec3 lCP, vec3 dColor, vec3 sColor, vec3 n, vec3 E
				/*, vec3 lDir_camera[LIGHTS]*/){

    for (int i=0; i<lDir_camera.length(); i++){         
        vec3 l = lDir_camera[i], R = reflect(-l,n);

        float slDist = pow(length(pos[i]-vPos_world),2), 
            cosT = clamp(dot(n,l),0,1), cosA = clamp(dot(E,R),0,1);

        color += lCP*(dColor*cosT+sColor*pow(cosA,5))/slDist;
    }
}


// Computes fragment color

void main(void){

    float lPower=500.f,slDist, cosT,cosA;
    vec3 lColor=vec3(1), aColor=vec3(0), sColor=vec3(0.3),
         dColor=fColor, lCP=lColor*lPower,
         n=normalize(vNormal_camera),E= normalize(eDir_camera),l,R;
	
    color = aColor;

	//vec3 lDir_camera[] = computeLightDirections();
    iluminate(lCP, dColor, sColor, n, E/*, lDir_camera*/);
}
