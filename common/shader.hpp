#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

class Shader{
    public:
        GLuint shaderProgram;
        Shader(GLchar* vertexShaderName, GLchar* fragmentShaderName);  
        void UseShaderProgram();
};

#endif
