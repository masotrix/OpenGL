#ifndef TOOL_H
#define TOOL_H
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <bits/stdc++.h>


class Tool {

    private:
        
        std::vector<Figure*>* _figures;
        std::vector<std::function<void(Figure*)>>* _functions;
        std::map<Figure*,std::function<void(Figure*)>*>* _parts;


    public:

        Tool(std::vector<Figure*>* figures,
            std::vector<std::function<void(Figure*)>>* functions,
            std::map<Figure*,std::function<void(Figure*)>*>* parts);

        void apply(void);
        void display(glm::mat4 ViewPerspective);
        ~Tool(void);
};

Tool* createRandomCubesTool(std::vector<GLfloat>* v,
        std::vector<GLfloat>* c, GLuint matrix, glm::mat4* MVP);

#endif
