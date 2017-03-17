/*************************************************************************
	> File Name: shader.cpp
	> Author: wangl
	> Mail: feixiaku@gmail.com
	> Created Time: Wed Mar 15 10:38:17 2017
	> Last Update Time: Wed Mar 15 10:38:17 2017
 ************************************************************************/

#include "shader.hpp"

using namespace std;

Shader::Shader(GLchar* vShaderName, GLchar* fShaderName)
{
    string vCode, fCode;
    ifstream vShaderFile, fShaderFile;

    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);

    stringstream vStream, fStream;
    try{
        vShaderFile.open(vShaderName);
        fShaderFile.open(fShaderName);
        
        vStream << vShaderFile.rdbuf();
        fStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vCode = vStream.str();
        fCode = fStream.str();
    }catch(std::ifstream::failure e){
        cout << "ERROR::SHADER::FILE_NOT_SUCCESSFUL_READ" << endl;
    }
    const GLchar* vShaderCode = vCode.c_str();
    const GLchar* fShaderCode = fCode.c_str();

    system("pwd");

    if(!vCode.empty())
    {
        cout << "vShader: " << vCode << endl;
    }else {
        cout << "vShader is empty !" << endl;
    }

    if(!fCode.empty())
    {
        cout << "fShader: " << fCode << endl;
    }else {
        cout << "fShader is empty !" << endl;
    }

    GLuint vShader, fShader;
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderCode, NULL);
    glCompileShader(vShader);

    GLint success;
    GLchar shaderInfo[512];
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vShader, 512, NULL, shaderInfo);
        cout << "Compile vertex shader failed: " << shaderInfo << endl;
        return;
    }

    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShaderCode, NULL);
    glCompileShader(fShader);
    
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fShader, 512, NULL, shaderInfo);
        cout << "Compile fragment shader failed: " << shaderInfo << endl;
        return;
    }

    //link program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, shaderInfo);
        cout << "Link program failed: " << shaderInfo << endl;
        return;
    }

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

void Shader::UseShaderProgram()
{
    glUseProgram(shaderProgram);
}
