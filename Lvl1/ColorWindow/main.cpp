#include <GL/glut.h>


//Drawing funciton
void display(void){

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 1.0, 0.0, 1.0);
    glFlush();
}

//Main program
int main(int argc, char **argv){

    glutInit(&argc, argv);
    glutCreateWindow("Green window");
    
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
