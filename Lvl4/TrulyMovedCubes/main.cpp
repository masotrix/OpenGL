#include <shaders.h>
#include <figure.h>
#include <controls.h>
#include <tool.h>
#include <GLFW/glfw3.h>
using namespace glm;
using namespace std;


// Data

ShaderInfo shaders[] = {
    { GL_VERTEX_SHADER, "Shaders/shaders.vert" },
    { GL_FRAGMENT_SHADER, "Shaders/shaders.frag" },
    { GL_NONE, NULL }
};
GLuint program, model, mvp, VAO; GLFWwindow* window;
mat4 MVP; Tool* tool; Controls* controls;


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
}, l(10), n = {
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


// Init

void init(){

    glfwInit(); srand(time(NULL));
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    window = glfwCreateWindow(1024,768,"Window", NULL,NULL);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowPos(window, 0, 0); glfwPollEvents();
    glfwSetCursorPos(window, 150, 150);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE; glewInit();
    glClearColor(0.f,0.f,0.f, 0.f); glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); glEnable(GL_CULL_FACE);
	glGenVertexArrays(1, &VAO); glBindVertexArray(VAO);
    glEnableVertexAttribArray(0); glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

    program = LoadShaders(shaders); glUseProgram(program);
	controls = new Controls("MVP", mvp, "M", model, "V",
		"lPos_world", &l);
    tool = createRandomCubesTool(&v, &c, &n, mvp, &MVP, model);
	
    for (int i=0; i<l.size(); i++){
        l[i] = vec3(rand()%200-100,
                rand()%200-100,
                rand()%200-100);
    }

}



// Display

void display(){
    
    do { 

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		controls->sendData();
        tool->display(controls->getViewPersp());
        glfwSwapBuffers(window); glfwPollEvents();

    } while (
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS 
        && glfwWindowShouldClose(window)==0);
}



// End

void end(){

    delete tool;
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
