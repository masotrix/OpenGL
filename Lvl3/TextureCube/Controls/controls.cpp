#include <controls.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;


extern GLFWwindow* window; 
mat4 ViewMatrix; mat4 getView(){ return ViewMatrix; }
mat4 ProjMatrix; mat4 getProj(){ return ProjMatrix; }
vec3 pos(0,0,5); float speed = 5.0f, mouseSpeed = 0.005f;
float hAng = 3.14/2, vAng = 0.f, initialFoV = 45.0f, val;
int width, height;



void computeMatricesFromInputs(){

	static double lastTime = glfwGetTime();

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
    glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width/2, height/2);

	hAng += mouseSpeed * float(width/2 - xpos );
	val = mouseSpeed * float(height/2 - ypos );
    if (abs(vAng+val) < 0.75) vAng+=val;

	vec3 dir(cos(vAng)*sin(hAng), sin(vAng), cos(vAng)*cos(hAng));
	vec3 right(sin(hAng-3.14/2), 0, cos(hAng-3.14/2));
	vec3 up = cross(right, dir);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		pos += dir * deltaTime * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		pos -= dir * deltaTime * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		pos += right * deltaTime * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		pos -= right * deltaTime * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
		pos += up * deltaTime * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
		pos -= up * deltaTime * speed;
	}

	float FoV = initialFoV;
	ProjMatrix = perspective(FoV, 4.f/3.f, 0.1f, 100.f);
	ViewMatrix = lookAt(pos, pos+dir, up);

	lastTime = currentTime;
}
