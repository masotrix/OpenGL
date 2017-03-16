#ifndef CONTROLS_H
#define CONTROLS_H
#include <string>
#include <vector>
#include <GL/gl.h>
#include <glm/glm.hpp>

class Controls {
    
    private:

        GLuint _mvpId, _modelId, _viewId, _persId, _lightsId;
        glm::mat4 _mvp, _model, _view, _pers;
        float _hAng, _vAng, _initialFoV, _speed, _mouseSpeed;
        std::vector<glm::vec3> _pos, *_lights;

        static void computeMatrices(void);

    public:

        Controls(std::string mvp, glm::mat4* MVP, GLuint mvpId,
                 std::string model, std::string view,
                 std::string lights,
                 std::vector<glm::vec3>* lightsData);

        virtual ~Controls(void){ delete _lights; }
        void sendData(void);
};


#endif
