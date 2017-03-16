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
GLuint program, texture, mvp, VAO; mat4 MVP; 
vector<vec3> v, n, l = {vec3(6), vec3(-4)}; vector<vec2> uv;
GLFWwindow* window; Figure* sphere; Controls* controls;


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
    glClearColor(0.f,0.f,0.f, 0.f); glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); glEnable(GL_CULL_FACE);
	glGenVertexArrays(1, &VAO); glBindVertexArray(VAO);
    glEnableVertexAttribArray(0); glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    program = LoadShaders(shaders); glUseProgram(program);
    controls = new Controls("MVP", mvp, "M", "V",
            "lPos_world", &l);

    loadOBJ("sphere.obj", v, uv, n);
    sphere = new Figure(&v, NULL, NULL, &n, GL_TRIANGLES, 3,
            mvp, &MVP, 0, 0);
}



// Display

void display(){
    
    do { 

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        controls->sendData();
        sphere->display(controls->getViewPersp());
        glfwSwapBuffers(window); glfwPollEvents();

    } while (
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS 
        && glfwWindowShouldClose(window)==0);
}



// End

void end(){

    delete sphere; delete controls;
	glDeleteVertexArrays(1,&VAO);
    glDeleteProgram(program);
    glfwTerminate();
}



// Main

int main(int argc, char **argv){

    init();
    display();
    end();
    
    return 0;
}
