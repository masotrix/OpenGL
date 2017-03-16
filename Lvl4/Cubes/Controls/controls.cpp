#include <controls.h>
using namespace glm;
using namespace std;


extern GLuint program;
extern GLFWwindow* window;
extern mat4 MVP;

Controls::Controls(const GLchar *mvp, GLuint& mvpId,
        const GLchar *model, GLuint& modelId, const GLchar *view,
        const GLchar *lights, vector<vec3>* lightsData) : 

    _hAng(3.14/2), _vAng(0.0f), _initialFoV(45.0f), 
    _speed(5.0f), _mouseSpeed(0.005f) {

    _pos      = vec3(0,0,5);
	_persp    = perspective(_initialFoV, 4.f/3.f, 0.1f, 100.f);
    _mvpId    = glGetUniformLocation(program, mvp); 
    _modelId  = glGetUniformLocation(program, model);
    _viewId   = glGetUniformLocation(program, view);
    mvpId = _mvpId; modelId = _modelId;
/*
    if (lights != "") {
        _lightsId = glGetUniformLocation(program, lights);
        _lights   = lightsData;
    } else _lights = NULL;
*/
}



void Controls::sendData(void) {

    this->computeMatrices();
    glUniformMatrix4fv(_viewId, 1, GL_FALSE, &_view[0][0]);
    //glUniform3fv(_lightsId, _lights->size(), &(*_lights)[0][0]);
}


void Controls::computeMatrices(void) {

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

	_view = lookAt(_pos, _pos+dir, up);
	lastTime = currentTime;
}
