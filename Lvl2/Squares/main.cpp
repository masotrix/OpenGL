#include <shaders.h>
#include <figure.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <bits/stdc++.h>
using namespace glm;
using namespace std;


// Data

ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER, "Shaders/shaders.vert" },
        { GL_FRAGMENT_SHADER, "Shaders/shaders.frag" },
        { GL_NONE, NULL }
};
GLFWwindow* window; GLuint program;


vector<vector<GLfloat>> v = {
    {-.50,-.50, +.50,-.50, +.50,+.50, -.50,+.50},
    {-.75,+.25, -.25,+.25, -.25,+.75, -.75,+.75},
    {+.75,+.25, +.25,+.25, +.25,+.75, +.75,+.75},
    {+.75,-.25, +.25,-.25, +.25,-.75, +.75,-.75}, 
    {-.75,-.25, -.25,-.25, -.25,-.75, -.75,-.75}
};
GLuint VAO; vector<Figure*> square(5);



// Init

void init(void){

    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    window = glfwCreateWindow(300,300,"Window", NULL,NULL);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE; glewInit();
    program = LoadShaders(shaders); glUseProgram(program);


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);    
    for (int i=0; i<5; i++)
        square[i] = new Figure(&v[i], NULL, NULL, GL_LINE_LOOP, 2,
                0, NULL, 0, 0);
    glEnableVertexAttribArray(0);   
}



// End

void end(){

    glfwTerminate();
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &VAO);
}



// Dispay

void display(void){

    do {

        glClear(GL_COLOR_BUFFER_BIT);
        for (int i=0; i<v.size(); i++)
            square[i]->display();
        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (
        glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS 
        && glfwWindowShouldClose(window) == 0 );    
}



// Main

int main(int argc, char** argv){

    init();
    display();
    end();
}
