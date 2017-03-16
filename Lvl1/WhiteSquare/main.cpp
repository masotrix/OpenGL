#include <GL/glut.h>


void display(void){

    glClear(GL_COLOR_BUFFER_BIT);
    
	glBegin(GL_QUADS);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glVertex3f(0.5, -0.5, 0.0);
	glEnd();

    glFlush();
}

int main(int argc, char** argv){

	glutInit(&argc, argv);
    glutCreateWindow("Square");

    glutDisplayFunc(display);
    glutMainLoop();    


    return 0;
}
