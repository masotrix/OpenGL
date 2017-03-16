#ifndef FIGURE_H
#define FIGURE_H
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <bits/stdc++.h>


class Attribute {

    private:
            
        GLuint _index, _buffer, _dim;
        std::vector<GLfloat>* _data;

    public:

        Attribute(std::vector<GLfloat>* data, GLuint index,
                GLuint dimension);

        void initData(void);
        void chooseAttribute(void);
        std::vector<GLfloat>* getData(void);
        ~Attribute(void);

};


class Figure {

    private:
        
        Attribute* _positions,* _colors,* _texture;
        GLuint _vert, _dim, _matrixID, _textureID, _DDS;
        GLenum _mode;
        glm::mat4* _MVP;
        

    public:

        Figure(std::vector<GLfloat>* vertices,
                std::vector<GLfloat>* colors,
                std::vector<GLfloat>* texture,
                GLenum drawMode, GLuint dimension,
                GLuint matrixID, glm::mat4* MVP,
                GLuint textureID, GLuint DDS);

        void display(void);
        void fillColors(void);
        ~Figure(void);
};


#endif
