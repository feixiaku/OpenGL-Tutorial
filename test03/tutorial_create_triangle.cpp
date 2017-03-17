/*************************************************************************
	> File Name: tutorial_create_window.cpp
	> Author: wangl
	> Mail: feixiaku@gmail.com
	> Created Time: Fri Mar 10 15:53:34 2017
 ************************************************************************/

#include<iostream>

//opengl dependence include file
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include"../common/shader.hpp"

using namespace glm;
using namespace std;

const GLuint WIDTH = 800, HEIGHT = 600;

void key_callback(GLFWwindow* window, int key, int scanmode, int action, int mode)
{
    cout << "key: " << key << endl;
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(int argc, char* argv[])
{
    if(!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow* window;
    window = glfwCreateWindow(WIDTH, HEIGHT, "Tutorial 01", nullptr, nullptr);
    if(window == nullptr)
    {
        cout << "Failed to Create GLFW Window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    int height, width;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glewExperimental = true;
    if(glewInit() != GLEW_OK)
    {
        cout << "Failed to initialize GLEW!" << endl;
        return -1;
    }

    //set input mode
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    //register keyboard callback function
    glfwSetKeyCallback(window, key_callback);

    //Build and Compile our Shader Program
    Shader shader = Shader("../../common/vertex.vs", "../../common/fragment.fs");

    //setup vertex data and attribute pointers
    //vertex data
    GLfloat vertices[] = {
        //position          //color 
        0.5f,  0.5f,  0.0f,  1.0f, 0.0f, 0.0f, //right up
        0.5f,  -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, //right down
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, //left down
        -0.5f, 0.5f,  0.0f,  0.5f, 0.5f, 0.5f, //left up
    };

    GLuint indices[] = {
       0, 1, 2,
       2, 3, 0
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Bind VAO first, then bind and set VBO data and attribute
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //postion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) 0);
    glEnableVertexAttribArray(0);
    //color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        //Render
        //Clear Color Buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT );

        GLint x_trans_location = glGetUniformLocation(shader.shaderProgram, "x_trans");
        glUniform1f(x_trans_location, -0.0f);
        //Draw our first triangle
        shader.UseShaderProgram();
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    };
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}
