#include <shaders.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;


// Data

GLFWwindow* window;
GLuint program;
ShaderInfo shaders[] = {
    { GL_VERTEX_SHADER, "shaders/shader.vert" },
    { GL_FRAGMENT_SHADER, "shaders/shader.frag" },
    { GL_NONE, NULL }
};


enum VAO_IDs { Triangle, NumVAOs }; GLuint VAOs[NumVAOs];
GLfloat vert[] = {-1.f,-1.f,0.f, 1.f,-1.f,0.f, 0.f,1.f,0.f};
enum Buffer_IDs { VAOBuff, NumBuff}; GLuint Buffers[NumBuff];



// Init

void init(void){
    
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    window = glfwCreateWindow(300,300,"Window", NULL,NULL);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE; glewInit();
    glClearColor(0.f,0.f,0.4f, 0.f);
    GLuint program = LoadShaders(shaders);
    glUseProgram(program);
    
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangle]);    
    glGenBuffers(NumBuff, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[VAOBuff]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vert),vert,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
}



// Display

void display(void){
    
    do { 
    
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES,0,3); 
        glfwSwapBuffers(window);
        glfwPollEvents();
        

    } while (
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS 
        && glfwWindowShouldClose(window)==0);
}



// End

void end(){

    glfwTerminate();
	glDeleteProgram(program);
    
    glDeleteBuffers(NumBuff, Buffers);
	glDeleteVertexArrays(NumVAOs, VAOs);
}



// Main

int main(int argc, char** argv){

    init();
    display();
    end();

    return 0;
}
