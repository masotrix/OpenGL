#ifndef CONTROLS_H
#define CONTROLS_H
#include <string>
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Controls {
    
    private:

        GLuint _mvpId, _modelId, _viewId, _persId, _lightsId;
        glm::mat4 _view, _persp, _viewPersp;
        float _hAng, _vAng, _initialFoV, _speed, _mouseSpeed;
        glm::vec3 _pos; std::vector<glm::vec3> *_lights;

        void computeMatrices(void);

    public:

        Controls(const GLchar *mvp, GLuint& mvpId,
                 const GLchar *model, GLuint& modelId,
                 const GLchar *view, const GLchar *lights,
                 std::vector<glm::vec3>* lightsData);

        virtual ~Controls(void){/* delete _lights;*/ }
        glm::mat4 getViewPersp(void){ return _persp*_view; }
        void sendData(void);
};


#endif
