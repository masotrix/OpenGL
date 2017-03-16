#include <figure.h>
using namespace glm;
using namespace std;


// Figure

Figure::Figure(vector<GLfloat>* vertices,
        vector<GLfloat>* colors,
        vector<GLfloat>* texture,
        GLenum drawMode, GLuint dimension,
        GLuint matrixID, mat4* MVP,
        GLuint textureID, GLuint DDS){

    _positions = new Attribute(vertices, 0, dimension);
    _positions->initData();
    if (colors) _colors = new Attribute(colors, 1, dimension);
    else _colors = NULL;
    if (texture){
        _texture = new Attribute(texture, 1, 2);
        _texture->initData();
    }
    else _texture = NULL;
    _mode = drawMode;
    _vert = vertices->size()/dimension;
    _dim = dimension;
    _matrixID = matrixID;
    _MVP = MVP;
    _textureID = textureID;
    _DDS = DDS;
}

void Figure::display(void){

    _positions->chooseAttribute();
    if (_colors) _colors->chooseAttribute();
    if (_texture){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _DDS);
        _texture->chooseAttribute();
    }
    if (_MVP){
        glUniformMatrix4fv(_matrixID,1,GL_FALSE,&(*_MVP)[0][0]);
    }
    glDrawArrays(_mode, 0, _vert);
}

void Figure::fillColors(void){
    
    vector<GLfloat>* data = _colors->getData();
    for (int i=0; i<_vert; i++){
        for (int j=0; j<_dim; j++){
            (*data)[_dim*i+j] = ((GLfloat) rand() / (RAND_MAX));
        }
    }
    _colors->initData();

}

Figure::~Figure(void){

    delete _positions;
    delete _colors;
}


// Attribute

Attribute::Attribute(vector<GLfloat>* data,
        GLuint index, GLuint dimension){

    _index = index;
    _data = data;
    _dim = dimension;
    glGenBuffers(1, &_buffer);
}

void Attribute::initData(void){
    
    size_t s = 4*(*_data).size();
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glBufferData(GL_ARRAY_BUFFER, s, &(*_data)[0], GL_STATIC_DRAW);
}

void Attribute::chooseAttribute(void){

    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glVertexAttribPointer(_index, _dim, GL_FLOAT,
            GL_FALSE, 0, (void*)0);
}

vector<GLfloat>* Attribute::getData(void){
    
    return _data;
}

Attribute::~Attribute(void){

    glDeleteBuffers(1, &_buffer);
}
