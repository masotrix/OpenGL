#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
uniform mat4 MVP;
out vec3 fColor;

void main(){

    gl_Position = MVP * vec4(vPosition, 1.0);
    fColor = vColor;    
}
