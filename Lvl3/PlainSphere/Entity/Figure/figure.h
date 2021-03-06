#ifndef FIGURE_H
#define FIGURE_H
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <bits/stdc++.h>


template <class T>
class Attribute {

    private:
            
        GLuint _index, _buffer, _dim;
        std::vector<T>* _data;

    public:

        Attribute(std::vector<T>* data, GLuint index,
                GLuint dimension);

        void initData(void);
        void chooseAttribute(void);
        std::vector<T>* getData(void);
        ~Attribute(void);
};


class Figure {

    private:
        
        Attribute<glm::vec3>* _positions,* _colors,* _normals;
        Attribute<glm::vec2>* _texture;
        GLuint _vert, _dim, _matrixID, _textureID, _DDS;
        GLenum _mode;
        glm::mat4* _MVP, _model;
        

    public:

        Figure(std::vector<glm::vec3>* vertices,
                std::vector<glm::vec3>* colors,
                std::vector<glm::vec2>* texture,
                std::vector<glm::vec3>* normals,
                GLenum drawMode, GLuint dimension,
                GLuint matrixID, glm::mat4* MVP,
                GLuint textureID, GLuint DDS);

        void display(glm::mat4& ViewPerspective);
        void translate(glm::vec3 movement);
        glm::mat4 getModel(void);
        void fillColors(void);
        ~Figure(void);
};


#endif
