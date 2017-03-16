#version 330 core

in vec2 fUV;
out vec3 color;
uniform sampler2D DDS;

void main(){ color = texture(DDS, vec2(fUV.x, 1-fUV.y)).rgb; }
