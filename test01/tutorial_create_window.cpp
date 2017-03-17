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

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glfwSetKeyCallback(window, key_callback);
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT );

        glfwSwapBuffers(window);
    };
    
    glfwTerminate();
    return 0;
}
