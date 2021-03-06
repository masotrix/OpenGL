#include <tool.h>
#include <GLFW/glfw3.h>
using namespace std;
using namespace glm;


Tool::Tool(vector<Figure*>* figures, 
        vector<function<void(Figure*)>>* functions,
        map<Figure*,function<void(Figure*)>*>* parts){

    _figures = figures;
    _functions = functions;
    _parts = parts;
}

void Tool::apply(void){

    for (map<Figure*,function<void(Figure*)>*>::iterator ite =
            _parts->begin(); ite != _parts->end(); ite++)

        (*ite->second)(ite->first);
}

void Tool::display(const mat4& ViewPerspective, mat4& MVP,
        GLuint mvp, GLuint model, GLuint texture, GLuint dds){

    apply();
    for (int i=0; i<_figures->size(); i++)
        (*_figures)[i]->display(ViewPerspective, MVP, 
                mvp, model, texture, dds);
}

Tool::~Tool(void){

    for (int i=0; i<_figures->size(); i++)
        delete (*_figures)[i];

    delete _figures;
    delete _functions;
    delete _parts;
}
