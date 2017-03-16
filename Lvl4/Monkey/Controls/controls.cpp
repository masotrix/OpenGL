#include <controls.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace std;


extern GLuint program;
extern GLFWwindow* window;

float Controls::Controls(string mvp, GLuint& mvpId, mat4* MVP,
        string model, string view,
        string lights, vector<vec3>* lightsData) : 
    _hAng(3.14/2), _vAng(0.0f), _initialFoV(45.0f), 
    _speed(5.0f), _mouseSpeed(0.005f) {

    _pos      = vec3(0,0,5);
	_pers     = perspective(_initialFoV, 4.f/3.f, 0.1f, 100.f);
    _mvpId    = getUniformLocation(program, mvp); mvpId = _mvpId;
    _modelId  = getUniformLoctaion(program, model);
    _viewId   = getUniformLocation(program, view);
    _model    = mat4(1.0);

    if (lights != "") {
        _lightsId = getUniformLocation(program, lights);
        _lights   = lightsData;
    } else _lights = NULL;
}

void Controls::sendData(void) {

    this->computeMatrices();
    glUniformMatrix4fv(_mvpId, 1, GL_FALSE, &(*_mvp));
    glUniformMatrix4fv(_modelId, 1, GL_FALSE, &_model);
    glUniformMatrix4fv(_viewId, 1, GL_FALSE, &_view);
    glUniform3fv(_lightsId, _lights.length(), &(*_lights)[0][0]);
}

mat4 Controls::getViewPersp(void) { return _pers*_view; }
void Controls::~Controls(void) { delete _lights; }
static void Controls::computeMatrices(void) {

	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float val, deltaTime = float(currentTime - lastTime);

	double xpos, ypos; int width, height;
	glfwGetCursorPos(window, &xpos, &ypos);
    glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width/2, height/2);

	_hAng += _mouseSpeed * float(width/2 - xpos );
	val = _mouseSpeed * float(height/2 - ypos );
    if (abs(_vAng+val) < 0.75) _vAng+=val;


	vec3 dir(cos(_vAng)*sin(_hAng), sin(_vAng), cos(_vAng)*cos(_hAng));
	vec3 right(sin(_hAng-3.14/2), 0, cos(_hAng-3.14/2));
	vec3 up = cross(right, dir);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		_pos += dir * deltaTime * _speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		_pos -= dir * deltaTime * _speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		_pos += right * deltaTime * _speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		_pos -= right * deltaTime * _speed;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
		_pos += up * deltaTime * _speed;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
		_pos -= up * deltaTime * _speed;
	}

	_view = lookAt(pos, pos+dir, up);
	lastTime = currentTime;
}
