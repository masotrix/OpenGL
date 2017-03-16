#include <shaders.h>
#include <controls.h>
#include <objloader.h>
#include <texture.h>
#include <figure.h>
#include <GLFW/glfw3.h>
using namespace glm;
using namespace std;

ShaderInfo shaders[] = {
    { GL_VERTEX_SHADER, "Shaders/shaders.vert" },
    { GL_FRAGMENT_SHADER, "Shaders/shaders.frag" },
    { GL_NONE, NULL }
};
GLFWwindow* window; mat4 projP, viewV, modelM, viewPersp, MVP;
vector<vec3> v, n; vector<vec2> uv; Figure* monkey;
GLuint VAO, program, DDS, texture, matrix, view, model, light; 



// Init

void init(){

	glfwInit();
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	window = glfwCreateWindow(300, 300, "Window", NULL, NULL);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowPos(window, 533, 234); glfwPollEvents();
    glfwSetCursorPos(window, 150, 150);
	glfwMakeContextCurrent(window); glewExperimental = true;
    glewInit(); glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE); glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1); glEnableVertexAttribArray(2);
    program = LoadShaders(shaders); glUseProgram(program);

	matrix = glGetUniformLocation(program, "MVP");
	view = glGetUniformLocation(program, "V");
	model = glGetUniformLocation(program, "M");
    DDS = loadDDS("uvmap.DDS");
    texture  = glGetUniformLocation(program, "myTextureSampler");
	loadOBJ("suzanne.obj", v, uv, n);
    monkey = new Figure(&v, NULL, &uv, &n, GL_TRIANGLES, 3,
            matrix, &MVP, texture, DDS);

	light = glGetUniformLocation(program, "lPos_world");
}



// Display

void display() {
		
	do {

        computeMatricesFromInputs();
        projP = getProj(); viewV = getView();
        viewPersp = projP*viewV;
        modelM = mat4(1.0);
        MVP = viewPersp * modelM;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniformMatrix4fv(matrix, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(model, 1, GL_FALSE, &modelM[0][0]);
        glUniformMatrix4fv(view, 1, GL_FALSE, &viewV[0][0]);
        vec3 lightPos = vec3(4,4,4);
        glUniform3f(light, lightPos.x, lightPos.y, lightPos.z);
        monkey->display(viewPersp);
        glfwSwapBuffers(window); glfwPollEvents();

    } while( glfwGetKey(window, GLFW_KEY_ESCAPE )
            != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );
}



// End

void end() {

    delete monkey; glDeleteProgram(program); glfwTerminate();
	glDeleteTextures(1, &DDS); glDeleteVertexArrays(1, &VAO);
}



// Main

int main(void) {

    init();
    display();
    end();

	return 0;
}

