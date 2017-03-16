#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cstdio>
#include <cstdlib>


//  LoadShaders() takes an array of ShaderFile structures,
// each of which contains the type of the shader, and a pointer a
// C-style character string (i.e., a NULL-terminated array of
// characters) containing the entire shader source.
//
//  The array of structures is terminated by a final Shader with
// the "type" field set to GL_NONE.
// 
//  LoadShaders() returns the shader program value (as returned by
// glCreateProgram()) on success, or zero on failure. 
//

struct ShaderInfo {
    GLenum       type;
    const char*  filename;
    GLuint       shader;
};

GLuint LoadShaders(ShaderInfo*);


