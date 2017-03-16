#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>

void display(void){
	
    glClear( GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0); // Green Quads

	glBegin(GL_QUADS);
		glVertex3f(2.0, 4.0, 0.0);
		glVertex3f(8.0, 4.0, 0.0);
		glVertex3f(8.0, 6.0, 0.0);
		glVertex3f(2.0, 6.0, 0.0);
	glEnd();
	
    glFlush();
}

int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow("Not normalized green Quad");

	glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);   

	glutDisplayFunc(display);
	glutMainLoop();

    return 0;
}
