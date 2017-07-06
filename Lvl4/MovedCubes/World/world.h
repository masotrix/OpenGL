#ifndef WORLD_H
#define WORLD_H
#include <tool.h>
#include <figure.h>


class World {

    private:

        std::vector<Figure*> _figures;
        std::vector<Tool*> _tools;

    public:

        const std::vector<Figure*>& getFigures() const { return _figures; }
        const std::vector<Tool*>& getTools(void) const { return _tools; }
        void addFigure(Figure* figure) { _figures.push_back(figure); }
        void addTool(Tool* tool) { _tools.push_back(tool); }
        ~World(void) { 
            for (int i=0; i<_figures.size(); i++) 
                delete _figures[i];
            for (int i=0; i<_tools.size(); i++) 
                delete _tools[i];
        }
};


#endif
