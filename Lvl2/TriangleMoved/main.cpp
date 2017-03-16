#include <shaders.h>
#include <figure.h>
#include <controls.h>
#include <GLFW/glfw3.h>
using namespace glm;
using namespace std;


// Data

ShaderInfo shaders[] = {
    { GL_VERTEX_SHADER, "Shaders/shaders.vert" },
    { GL_FRAGMENT_SHADER, "Shaders/shaders.frag" },
    { GL_NONE, NULL }
};
GLuint matrix, program; GLFWwindow* window;
mat4 proje, view, model, MVP;


vector<GLfloat> v = {-1.f,-1.f,0.f, 1.f,-1.f,0.f, 0.f, 1.f,0.f};
GLuint VAO; Figure* tria;


// Init

void init(){

    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    window = glfwCreateWindow(300,300,"Window", NULL,NULL);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowPos(window, 533, 234); glfwPollEvents();
    glfwSetCursorPos(window, 150, 150);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE; glewInit();
    glClearColor(0.f,0.f,0.4f, 0.f);
	glGenVertexArrays(1, &VAO); glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
	program = LoadShaders(shaders); glUseProgram(program);


    matrix = glGetUniformLocation(program, "MVP");
    tria = new Figure(&v, NULL, NULL, GL_TRIANGLES, 3,
            matrix, &MVP, 0, 0); model = mat4(1);
}



// Display

void display(){
    
    do {

        computeMatricesFromInputs();
        proje = getProj(); view = getView();
        MVP = proje * view * model;

        glClear(GL_COLOR_BUFFER_BIT); tria->display();
        glfwSwapBuffers(window); glfwPollEvents(); 

    } while (
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS 
        && glfwWindowShouldClose(window)==0);
}



// End

void end(){

    delete tria;
    glfwTerminate();
	glDeleteProgram(program);
	glDeleteVertexArrays(1,&VAO);
}



// Main

int main(int argc, char **argv){

    init();
    display();
    end();
    
    return 0;
}
