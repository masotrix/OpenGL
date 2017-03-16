#ifndef SHADERS_H
#define SHADERS_H
#include <GL/glew.h>
#include <GL/gl.h>


struct ShaderInfo {
    GLenum       type;
    const char*  filename;
    GLuint       shader;
};

GLuint LoadShaders(ShaderInfo*);

#endif
