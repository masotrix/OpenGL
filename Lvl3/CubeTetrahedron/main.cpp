#include <shaders.h>
#include <figure.h>
#include <controls.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <bits/stdc++.h>
using namespace glm;
using namespace std;


// Data

ShaderInfo shaders[] = {
    { GL_VERTEX_SHADER, "Shaders/shaders.vert" },
    { GL_FRAGMENT_SHADER, "Shaders/shaders.frag" },
    { GL_NONE, NULL }
};
GLuint program, matrix, VAO; GLFWwindow* window;
mat4 proje, view, model1, model2, MVP1, MVP2;


const GLfloat w = 2*sqrt(3)/3, z = w/2; Figure* cube,* tetra;
GLfloat x = -w*tan(radians(90.)-2*asin(z)), y = sqrt(2)*w+x;
vector<GLfloat> c1(108), v1 = {
    -1,-1,-1, -1,-1,1., -1,1.,1., 1,1.,-1, -1,-1,-1, -1,1.,-1,  
    1.,-1,1., -1,-1,-1, 1.,-1,-1, 1,1.,-1, 1.,-1,-1, -1,-1,-1, 
    -1,-1,-1, -1,1.,1., -1,1.,-1, 1,-1,1., -1,-1,1., -1,-1,-1,
    -1,1.,1., -1,-1,1., 1.,-1,1., 1,1.,1., 1.,-1,-1, 1.,1.,-1,
    1.,-1,-1, 1.,1.,1., 1.,-1,1., 1,1.,1., 1.,1.,-1, -1,1.,-1,
    1.,1.,1., -1,1.,-1, -1,1.,1., 1,1.,1., -1,1.,1., 1.,-1,1.
};
vector<GLfloat> c2(36), v2 = {
    1.,+x,-z, -1,+x,-z, 0.,+y,0., -1,+x,-z, .0,+x,+w, 0,+y,0.,
    0.,+x,+w, 1.,+x,-z, 0.,+y,0., 1,+x,-z, .0,+x,+w, -1,+x,-z 
};



// Init

void init(){
    
    glfwInit(); srand(time(NULL));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(300,300,"Window", NULL,NULL);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowPos(window, 533, 234); glfwPollEvents();
    glfwSetCursorPos(window, 150, 150);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE; glewInit();
    glClearColor(0.f,0.f,0.4f, 0.f); glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); glEnable(GL_CULL_FACE);
    glGenVertexArrays(1, &VAO); glBindVertexArray(VAO);
    glEnableVertexAttribArray(0); glEnableVertexAttribArray(1);
    program = LoadShaders(shaders); glUseProgram(program);


    matrix = glGetUniformLocation(program, "MVP");
    model1 = translate(mat4(1), vec3(-1.3,0,0));
    model2 = translate(mat4(1), vec3(+1.3,0,0))*
        scale(mat4(1), vec3(1.4));
    cube = new Figure(&v1, &c1, NULL, GL_TRIANGLES, 3,
            matrix, &MVP1, 0, 0);
    tetra = new Figure(&v2, &c2, NULL, GL_TRIANGLES, 3,
            matrix, &MVP2, 0, 0);
}



// Display

void display(){
    
    do {

        computeMatricesFromInputs();
        proje = getProj(); view = getView();
        MVP1 = proje * view * model1; 
        MVP2 = proje * view * model2;
    
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        
        cube->fillColors(); cube->display();
        tetra->fillColors(); tetra->display();
        glfwSwapBuffers(window); glfwPollEvents();

    } while (
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS 
        && glfwWindowShouldClose(window)==0);
}



// End

void end(){

    glfwTerminate();
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &VAO);
}



// Main

int main(int argc, char **argv){

    init();
    display();
    end();
    
    return 0;
}
