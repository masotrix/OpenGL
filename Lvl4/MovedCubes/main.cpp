#include <camera.h>
#include <world.h>
using namespace glm;
using namespace std;


World *world; Camera *camera;

// Init

void init(){

    world = new World();
    camera = new Camera(world);
    Tool* tool = createRandomCubesTool();
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
