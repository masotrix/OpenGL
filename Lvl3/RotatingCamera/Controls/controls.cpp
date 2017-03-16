#include <controls.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;


extern GLFWwindow* window; 
mat4 ViewMatrix; mat4 getView(){ return ViewMatrix; }
mat4 ProjMatrix; mat4 getProj(){ return ProjMatrix; }
vec3 pos(0,0,5), dir; float speed = 5.0, r = 5.0, hPos=0, val=0;
int width, height;


void computeMatricesFromInputs(){

	static double lastTime = glfwGetTime();

	double curTime = glfwGetTime();
	float deltaTime = float(curTime - lastTime);

    glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width/2, height/2);


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		r -= (float)deltaTime * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		r += (float)deltaTime * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
		hPos -= (float)deltaTime * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
		hPos += (float)deltaTime * speed;
	}
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        val += (float)deltaTime * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		val -= (float)deltaTime * speed;
	}
        
    pos = vec3(0)-vec3(r*cos(curTime+val), hPos, r*sin(curTime+val));
	dir = vec3(0)-pos;

	ProjMatrix = perspective(45.f, 4.f/3.f, 0.1f, 100.f);
	ViewMatrix = lookAt(pos, pos+dir, vec3(0,1,0));

	lastTime = curTime;
}
