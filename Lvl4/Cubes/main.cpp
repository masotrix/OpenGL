#include <shaders.h>
#include <figure.h>
#include <controls.h>
#include <GLFW/glfw3.h>
using namespace glm;
using namespace std;
#define LIGHTS 10

// Data

ShaderInfo shaders[] = {
    { GL_VERTEX_SHADER, "Shaders/shaders.vert" },
    { GL_FRAGMENT_SHADER, "Shaders/shaders.frag" },
    { GL_NONE, NULL }
};
GLuint program, model, mvp, VAO, lights; GLFWwindow* window;
mat4 MVP; vector<Figure*> cubes(5000); Controls* controls;

vector<vec3> c(36), v = {
    vec3(-1,-1,-1), vec3(-1,-1,1.), vec3(-1,1.,1.),
    vec3(1.,1.,-1), vec3(-1,-1,-1), vec3(-1,1.,-1),  
    vec3(1.,-1,1.), vec3(-1,-1,-1), vec3(1.,-1,-1), 
    vec3(1.,1.,-1), vec3(1.,-1,-1), vec3(-1,-1,-1), 
    vec3(-1,-1,-1), vec3(-1,1.,1.), vec3(-1,1.,-1),
    vec3( 1,-1,1.), vec3(-1,-1,1.), vec3(-1,-1,-1),
    vec3(-1,1.,1.), vec3(-1,-1,1.), vec3(1.,-1,1.),
    vec3(1.,1.,1.), vec3(1.,-1,-1), vec3(1.,1.,-1),
    vec3(1.,-1,-1), vec3(1.,1.,1.), vec3(1.,-1,1.),
    vec3(1.,1.,1.), vec3(1.,1.,-1), vec3(-1,1.,-1),
    vec3(1.,1.,1.), vec3(-1,1.,-1), vec3(-1,1.,1.),
    vec3(1.,1.,1.), vec3(-1,1.,1.), vec3(1.,-1,1.)
}, n = {
    vec3(-1,-1,-1), vec3(-1,-1,1.), vec3(-1,1.,1.),
    vec3(1.,1.,-1), vec3(-1,-1,-1), vec3(-1,1.,-1),  
    vec3(1.,-1,1.), vec3(-1,-1,-1), vec3(1.,-1,-1), 
    vec3(1.,1.,-1), vec3(1.,-1,-1), vec3(-1,-1,-1), 
    vec3(-1,-1,-1), vec3(-1,1.,1.), vec3(-1,1.,-1),
    vec3( 1,-1,1.), vec3(-1,-1,1.), vec3(-1,-1,-1),
    vec3(-1,1.,1.), vec3(-1,-1,1.), vec3(1.,-1,1.),
    vec3(1.,1.,1.), vec3(1.,-1,-1), vec3(1.,1.,-1),
    vec3(1.,-1,-1), vec3(1.,1.,1.), vec3(1.,-1,1.),
    vec3(1.,1.,1.), vec3(1.,1.,-1), vec3(-1,1.,-1),
    vec3(1.,1.,1.), vec3(-1,1.,-1), vec3(-1,1.,1.),
    vec3(1.,1.,1.), vec3(-1,1.,1.), vec3(1.,-1,1.)
};

typedef struct lightsPos {
    vec3 _lights[LIGHTS];
} lightsPos;


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
    glClearColor(0.f,0.f,0.f,0.f); glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); glEnable(GL_CULL_FACE);
	glGenVertexArrays(1, &VAO); glBindVertexArray(VAO);
    glEnableVertexAttribArray(0); glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    



    program = LoadShaders(shaders); glUseProgram(program);
    controls = new Controls("MVP", mvp, "M", model, "V", "lights", &n);
    
    for (int i=0; i<cubes.size(); i++){
        cubes[i] = new Figure(&v, &c, NULL, &n, GL_TRIANGLES, 3,
            mvp, &MVP, model, 0, 0); cubes[i]->fillColors();
        cubes[i]->translate(
                vec3(rand()%200-100,
                    rand()%200-100,
                    rand()%200-100));
    }

    lightsPos ls;
    for (int i=0; i<LIGHTS; i++){
        ls._lights[i] = vec3(rand()%200-100,
                rand()%200-100,
                rand()%200-100);
    }

    glGenBuffers(1, &lights);
    glBindBuffer(GL_UNIFORM_BUFFER, lights);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(ls), &ls, GL_DYNAMIC_COPY);
    GLuint block_index= glGetUniformBlockIndex(program, "lights");
    GLuint binding_point_index = 2;
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_point_index, lights);
    glUniformBlockBinding(program, block_index, binding_point_index);
}



// Display

void display(){
    
    do { 
    
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        controls->sendData();
        for (int i=0; i<cubes.size(); i++)
            cubes[i]->display(controls->getViewPersp());
        glfwSwapBuffers(window); glfwPollEvents();

    } while (
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS 
        && glfwWindowShouldClose(window)==0);
}



// End

void end(){

    for (int i=0; i<cubes.size(); i++) delete cubes[i];
    delete controls;
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
