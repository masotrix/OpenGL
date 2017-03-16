#include <shaders.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;


// Data

GLFWwindow* window;
GLuint program;
ShaderInfo shaders[] = {
    { GL_VERTEX_SHADER, "shaders.vert" },
    { GL_FRAGMENT_SHADER, "shaders.frag" },
    { GL_NONE, NULL }
};


enum VAO_IDs {VAO, NumVAOs};
GLuint VAOs[NumVAOs];
const GLuint NumSquares = 1, NumTriangles = 4,
    SquareVert = 4, TriangleVert = 3,
    TotalVert = NumSquares*SquareVert +
        NumTriangles*TriangleVert;
GLfloat vert[TotalVert][2] = {
    {-.5,-.5}, {.5,-.5}, {.5,.5}, {-.5,.5},
    {-.75,.25}, {-.25,.25}, {-.25,.75},
    {.75,.25}, {.25,.25}, {.25,.75},
    {.75,-.25}, {.25,-.25}, {.25,-.75}, 
    {-.75,-.25}, {-.25,-.25}, {-.25,-.75}
};
enum Buffer_IDs {VAOBuff, NumBuff};
GLuint Buffers[NumBuff];



// Init

void init(void){

    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    window = glfwCreateWindow(300,300,"Window", NULL,NULL);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE; glewInit();
    program = LoadShaders(shaders); glUseProgram(program);
    
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[VAO]);      
    glGenBuffers(NumBuff, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[VAOBuff]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vert),vert,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);
}



// Display

void display(void){

    do {

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_LINE_LOOP, 0, SquareVert);
        for (int i=SquareVert; i<TotalVert; i+=TriangleVert)
            glDrawArrays(GL_LINE_LOOP, i, TriangleVert);
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
    
    glDeleteBuffers(NumBuff,Buffers);
	glDeleteVertexArrays(NumVAOs,VAOs);
}



// Main

int main(int argc, char** argv){
    
    init();
    display();
    end();    
}
