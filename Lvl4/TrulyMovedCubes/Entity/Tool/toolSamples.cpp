#include <figure.h>
#include <tool.h>
#include <GLFW/glfw3.h>
using namespace std;
using namespace glm;


Tool* createRandomCubesTool(vector<vec3>* v, vector<vec3>* c,
        vector<vec3>* n, GLuint mvp, mat4* MVP, GLuint model){


    vector<Figure*>* cubes = new vector<Figure*>(5000);
    for (int i=0; i<cubes->size(); i++){
        (*cubes)[i] = new Figure(v, c, NULL, n, GL_TRIANGLES, 3,
            mvp, MVP, model, 0, 0); 
        (*cubes)[i]->fillColors();
        (*cubes)[i]->translate(
            vec3(rand()%200-100,rand()%200-100, rand()%200-100));
    }

    vector<function<void(Figure*)>>* functions = 
        new vector<function<void(Figure*)>>(3);

    (*functions)[0] = [](Figure* fig){ 
        fig->translate(vec3(sin(glfwGetTime())/20,0,0)); };
    (*functions)[1] = [](Figure* fig){ 
        fig->translate(vec3(0,sin(glfwGetTime())/20,0)); };
    (*functions)[2] = [](Figure* fig){ 
        fig->translate(vec3(0,0,sin(glfwGetTime())/20)); };


    map<Figure*,function<void(Figure*)>*>* parts =
        new map<Figure*,function<void(Figure*)>*>();
    for (int i=0; i<cubes->size(); i++)
        (*parts)[(*cubes)[i]] = 
            &(*functions)[rand()%functions->size()];
    

    Tool* randomCubes = new Tool(cubes, functions, parts);

}

