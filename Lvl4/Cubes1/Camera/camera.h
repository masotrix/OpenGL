#ifndef CAMERA_H
#define CAMERA_H
#include <cstdlib>
#include <ctime>
#include <shaders.h>
#include <controls.h>
#include <world.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

ShaderInfo _shaders[] = {
    { GL_VERTEX_SHADER, "Camera/Shaders/shaders.vert" },
    { GL_FRAGMENT_SHADER, "Camera/Shaders/shaders.frag" },
    { GL_NONE, NULL }
};

class Camera {


    private:

        GLuint _program, _model, _mvp, _VAO, _texture, _dds;
        glm::mat4 _MVP;
        Controls* _controls;
        World* _world;
        GLFWwindow* _window; 
        std::vector<glm::vec3> _l;

    public:

        Camera(World* world) {

			glfwInit(); srand(time(NULL));
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
			_window = glfwCreateWindow(1024,768,"Window", NULL,NULL);
			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetWindowPos(_window, 0, 0); glfwPollEvents();
			glfwSetCursorPos(_window, 150, 150);
			glfwMakeContextCurrent(_window);
			glewExperimental = GL_TRUE; glewInit();

			glClearColor(0.f,0.f,0.f, 0.f); glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS); glEnable(GL_CULL_FACE);
			glGenVertexArrays(1, &_VAO); glBindVertexArray(_VAO);
			glEnableVertexAttribArray(0); glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2); 
            
            _l = std::vector<glm::vec3>(10);
            _program = LoadShaders(_shaders); 
            glUseProgram(_program);
            _world = world; 
            _controls = new Controls("MVP",_mvp,"M",_model,"V",
				"lPos_world",&_l,_program);

			for (int i=0; i<_l.size(); i++){
				_l[i] = glm::vec3(rand()%200-100,
						rand()%200-100,
						rand()%200-100);
    		}
        }

		void film(void){

            do { 

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				_controls->sendData(_window);
                
                std::vector<Figure*> figures = _world->getFigures();
                for_each (figures.begin(), figures.end(), [&](Figure* fig){
				    fig->display(_controls->getViewPersp(),
                            _MVP,_mvp,_model,_texture,_dds);
                });
                std::vector<Tool*> tools = _world->getTools();
                for_each (tools.begin(), tools.end(), [&](Tool* tool){
				    tool->display(_controls->getViewPersp(),
                            _MVP,_mvp,_model,_texture,_dds);
                });

				glfwSwapBuffers(_window); glfwPollEvents();

			} while (
				glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS 
				&& glfwWindowShouldClose(_window)==0);
        }

		~Camera(void){
            delete _controls; 
        	glDeleteProgram(_program);
			glDeleteVertexArrays(1,&_VAO);
			glfwTerminate();
        }
};





#endif /*CAMERA_H*/
