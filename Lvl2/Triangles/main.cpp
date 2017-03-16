#include <shaders.h>


enum VAO_IDs{ Triangles, NumVAOs };
enum Buffer_IDs{ ArrayBuffer, NumBuffers};
enum Attrib_IDs{ vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6,
      Dimensions = 2;


GLfloat vertices[NumVertices][Dimensions] = {
    { -0.9, -0.9 }, { 0.85, -0.9 }, { -0.90, 0.85 }, // Tri1
    { 0.9, -0.85 }, { 0.90, 0.90 }, { -0.85, 0.90 }  // Tri2
};


void init(void){
    
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);    

    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);


    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
            vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);
    glEnableVertexAttribArray(vPosition);



    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER, "shaders.vert" },
        { GL_FRAGMENT_SHADER, "shaders.frag" },
        { GL_NONE, NULL }
    };

    GLuint program = LoadShaders(shaders);
    glUseProgram(program);
}



void display(void){

    glClear(GL_COLOR_BUFFER_BIT);
    
    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    
    glFlush();
}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("Triangles");


    glewExperimental = GL_TRUE;
    glewInit();


    init();
    glutDisplayFunc(display);
    glutMainLoop();    



    return 0;
}
