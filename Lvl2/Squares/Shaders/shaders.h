#ifndef SHADERS_H
#define SHADERS_H
#include <GL/glew.h>
#include <GL/gl.h>


typedef struct {
    GLenum       type;
    const char*  filename;
    GLuint       shader;
} ShaderInfo;

GLuint LoadShaders(ShaderInfo*);


#endif
