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
    Tool* tool = createRandomCubesTool(&v, &c, &n);
    world->addTool(tool);
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
