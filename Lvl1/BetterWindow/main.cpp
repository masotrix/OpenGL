#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


//Drawing funciton
void display(GLFWwindow* window){
    
    glClear( GL_COLOR_BUFFER_BIT );
    glfwSwapBuffers(window);
    glfwPollEvents();
}

//Main program
int main(int argc, char **argv){


    glfwInit();
    GLFWwindow* window = glfwCreateWindow(
            300, 300, "Window", NULL, NULL);
    glfwMakeContextCurrent(window);


    glewExperimental = GL_TRUE;
    glewInit();


    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    do {

        display(window);

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

    glfwTerminate();
    
    return 0;
}
