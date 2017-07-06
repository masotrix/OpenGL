#include <iostream>
#include <shaders.h>
using namespace std;


static const GLchar* ReadShader(const char *filename){

    FILE* infile = fopen(filename, "rb");
    fseek(infile, 0, SEEK_END);
    int len = ftell( infile );
    fseek(infile, 0, SEEK_SET);

    GLchar* source = new GLchar[len+1];
    fread(source, 1, len, infile);
    fclose(infile);
    source[len] = 0;

    return const_cast<const GLchar*>(source);
}

static bool assertCompile(GLuint shader){

	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled) {

		GLsizei len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		GLchar* log = new GLchar[len+1];
		glGetShaderInfoLog(shader, len, &len, log);
		cerr << "Shader compilation failed: " << log << endl;
		delete [] log;

		return false;
	}

	return true;
}

static bool assertLink(ShaderInfo *shaders, GLuint program){
    
	GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if (!linked) {

        GLsizei len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
        GLchar* log = new GLchar[len+1];
        glGetProgramInfoLog(program, len, &len, log);
        std::cerr << "Shader linking failed: " << log << std::endl;
        delete [] log;

        for (ShaderInfo* i=shaders; i->type!=GL_NONE; ++i) {
            glDeleteShader(i->shader);
            i->shader = 0;
        }
        
        return false;
    }

	return true;
}



GLuint LoadShaders(ShaderInfo *shaders){

    if (shaders == NULL) { return 0; }

    GLuint program = glCreateProgram();
    ShaderInfo* entry = shaders;
    
    while (entry->type != GL_NONE) {

        GLuint shader = glCreateShader( entry->type );
        entry->shader = shader;
        const GLchar* source = ReadShader( entry->filename ); 
        glShaderSource(shader, 1, &source, NULL);
        delete [] source;

        cout << "Compiling " << entry->filename << endl;
        glCompileShader(shader);
		if (!assertCompile(shader)) return 0;
        glAttachShader(program, shader);
        
        ++entry;
    }

    cout << "Linking\n";
    glLinkProgram(program);
	if (!assertLink(shaders, program)) return 0;

    return program;
}



