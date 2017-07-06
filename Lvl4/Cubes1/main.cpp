#include <camera.h>
#include <world.h>
using namespace glm;
using namespace std;


// Data

World* world; Camera* camera;


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


// Init

void init(){

    world = new World();
    camera = new Camera(world);
    vector<Figure*> cubes(5000);
    for (int i=0; i<cubes.size(); i++){
        cubes[i] = new Figure(&v, &c, NULL, &n, GL_TRIANGLES, 3);
        cubes[i]->fillColors();
        cubes[i]->translate(
                vec3(rand()%200-100,rand()%200-100,rand()%200-100));
        world->addFigure(cubes[i]);
    }
    camera->film();
}




// End

void end(){

    delete camera;
    delete world;
}



// Main

int main(int argc, char **argv){

    init();
    end();
    
    return 0;
}
