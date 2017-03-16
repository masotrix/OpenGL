#include <shaders.h>
#include <figure.h>
#include <controls.h>
#include <objloader.h>
#include <GLFW/glfw3.h>
using namespace glm;
using namespace std;


// Data

ShaderInfo shaders[] = {
    { GL_VERTEX_SHADER, "Shaders/shaders.vert" },
    { GL_FRAGMENT_SHADER, "Shaders/shaders.frag" },
    { GL_NONE, NULL }
};
GLuint program, matrix, VAO; 
mat4 ViewPerspective, MVP; Figure* sphere;
vector<vec3> v, n; GLFWwindow* window;
vector<vec2> uv;


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
    glClearColor(0.f,0.f,0.f, 0.f); glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); glEnable(GL_CULL_FACE);
	glGenVertexArrays(1, &VAO); glBindVertexArray(VAO);
    glEnableVertexAttribArray(0); glEnableVertexAttribArray(1);
    program = LoadShaders(shaders); glUseProgram(program);

    matrix = glGetUniformLocation(program, "MVP");
    loadOBJ("sphere.obj", v, uv, n);
    sphere = new Figure(&v, NULL, NULL, &n, GL_TRIANGLES, 3,
            matrix, &MVP, 0, 0); sphere->fillColors();
}



// Display

void display(){
    
    do { 

        computeMatricesFromInputs(); 
        ViewPerspective = getProj()*getView();
 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        sphere->display(ViewPerspective);
        glfwSwapBuffers(window); glfwPollEvents();

    } while (
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS 
        && glfwWindowShouldClose(window)==0);
}



// End

void end(){

    delete sphere;
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
