#include <shaders.h>
#include <figure.h>
#include <texture.h>
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
GLuint program, matrix, VAO, DDS, texture; GLFWwindow* window;
mat4 projec, view, model, MVP; Figure* cube;


vector<GLfloat>  v = {
    -1,-1,-1, -1,-1,1., -1,1.,1., 1,1.,-1, -1,-1,-1, -1,1.,-1,  
    1.,-1,1., -1,-1,-1, 1.,-1,-1, 1,1.,-1, 1.,-1,-1, -1,-1,-1, 
    -1,-1,-1, -1,1.,1., -1,1.,-1, 1,-1,1., -1,-1,1., -1,-1,-1,
    -1,1.,1., -1,-1,1., 1.,-1,1., 1,1.,1., 1.,-1,-1, 1.,1.,-1,
    1.,-1,-1, 1.,1.,1., 1.,-1,1., 1,1.,1., 1.,1.,-1, -1,1.,-1,
    1.,1.,1., -1,1.,-1, -1,1.,1., 1,1.,1., -1,1.,1., 1.,-1.,1.
},
         uv = {
	0.000059,1-0.000004, 0.000103,1-0.336048, 0.335973,1-0.335903,
    1.000023,1-0.000013, 0.667979,1-0.335851, 0.999958,1-0.336064, 
	0.667979,1-0.335851, 0.336024,1-0.671877, 0.667969,1-0.671889,
    1.000023,1-0.000013, 0.668104,1-0.000013, 0.667979,1-0.335851, 
	0.000059,1-0.000004, 0.335973,1-0.335903, 0.336098,1-0.000071,
    0.667979,1-0.335851, 0.335973,1-0.335903, 0.336024,1-0.671877, 
	1.000004,1-0.671847, 0.999958,1-0.336064, 0.667979,1-0.335851,
    0.668104,1-0.000013, 0.335973,1-0.335903, 0.667979,1-0.335851, 
	0.335973,1-0.335903, 0.668104,1-0.000013, 0.336098,1-0.000071,
    0.000103,1-0.336048, 0.000004,1-0.671870, 0.336024,1-0.671877, 
	0.000103,1-0.336048, 0.336024,1-0.671877, 0.335973,1-0.335903,
    0.667969,1-0.671889, 1.000004,1-0.671847, 0.667979,1-0.335851
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
    DDS = loadDDS("Texture/uvtemplate.DDS");

    
    texture = glGetUniformLocation(program, "DDS");
    matrix = glGetUniformLocation(program, "MVP");
    cube = new Figure(&v, NULL, &uv, GL_TRIANGLES, 3,
            matrix, &MVP, texture, DDS); model = mat4(1.0);
}



// Display

void display(){
    
    do { 
    
        computeMatricesFromInputs();
        projec = getProj(); view = getView(); ;
        MVP = projec * view * model;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cube->display(); glfwSwapBuffers(window); glfwPollEvents();

    } while (
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS 
        && glfwWindowShouldClose(window)==0);
}



// End

void end(){

    delete cube;
	glDeleteProgram(program);
    glDeleteTextures(1, &DDS);
	glDeleteVertexArrays(1, &VAO);
    glfwTerminate();
}



// Main

int main(int argc, char **argv){

    init();
    display();
    end();
    
    return 0;
}
