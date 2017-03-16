#include <figure.h>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace std;


// Figure

Figure::Figure(vector<vec3>* vertices,
        vector<vec3>* colors,
        vector<vec2>* texture,
        vector<vec3>* normals,
        GLenum drawMode, GLuint dimension,
        GLuint matrixID, mat4* MVP, 
        GLuint modelID, GLuint textureID, GLuint DDS){

    _positions = new Attribute<vec3>(vertices, 0, dimension);
    _positions->initData();
    _vert = vertices->size();
    _dim = dimension;
    _matrixID = matrixID;
    _MVP = MVP;
    _modelID = modelID;
    _model = mat4(1.0);
    _mode = drawMode;
    _textureID = textureID;
    _DDS = DDS;
    

    if (!colors) colors = new vector<vec3>(_vert);
    _colors = new Attribute<vec3>(colors,1,dimension); 

    if (texture){
        _texture = new Attribute<vec2>(texture, 1, 2);
        _texture->initData();
    } else _texture = NULL;

    if (normals){
        _normals = new Attribute<vec3>(normals, 2, dimension);
        _normals->initData();
    } else _normals = NULL;
}

void Figure::display(const mat4& ViewPerspective){
    
    *_MVP = ViewPerspective * _model;
    glUniformMatrix4fv(_matrixID,1,GL_FALSE,&(*_MVP)[0][0]);
    glUniformMatrix4fv(_modelID,1,GL_FALSE,&_model[0][0]);
    _positions->chooseAttribute();
    if (_colors) _colors->chooseAttribute();
    if (_texture){
        glUniform1i(_textureID, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _DDS);
        _texture->chooseAttribute();
    }
    if (_normals) _normals->chooseAttribute();
    glDrawArrays(_mode, 0, _vert);
}

void Figure::translate(vec3 movement){
    
    _model = glm::translate(_model, movement);
}

mat4 Figure::getModel(void){

    return _model;
}

void Figure::fillColors(void){
    
    vector<vec3>* colors = _colors->getData();
    for (int i=0; i<_vert; i++)
        for (int j=0; j<_dim; j++)
        (*colors)[i][j] = ((GLfloat) rand() / (RAND_MAX));

    _colors->initData();

}


Figure::~Figure(void){

    delete _positions;
    delete _colors;
    delete _texture;
    delete _normals;
}


// Attribute
template <class T>
Attribute<T>::Attribute(vector<T>* data,
        GLuint index, GLuint dimension){

    _index = index;
    _data = data;
    _dim = dimension;
    glGenBuffers(1, &_buffer);
}


template <class T>
void Attribute<T>::initData(void){
    
    size_t s = (*_data).size()*sizeof(vec3);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glBufferData(GL_ARRAY_BUFFER, s, &(*_data)[0], GL_STATIC_DRAW);
}

template <class T>
void Attribute<T>::chooseAttribute(void){

    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glVertexAttribPointer(_index, _dim, GL_FLOAT,
            GL_FALSE, 0, (void*)0);
}

template <class T>
Attribute<T>::~Attribute(void){

    glDeleteBuffers(1, &_buffer);
}
