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
const GLchar* VertexShaderSource = "#version 330 core\n"
                                   "layout (location = 0) in vec3 position;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n"
                                   "}\0";
const GLchar* FragmentShaderSource = "#version 330 core\n"
                                     "out vec4 color;\n"
                                     "void main()\n"
                                     "{\n"
                                     "  color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                     "}\n\0";

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
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); 
    glShaderSource(vertexShader, 1, &VertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar shaderInfo[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, shaderInfo);
        cout << "Compile VertexShader Failed: " << shaderInfo << endl;
        return -1;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &FragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, shaderInfo);
        cout << "Compile Fragment Shader Failed: " << shaderInfo << endl; 
        return -1;
    }
    
    //Link Program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, shaderInfo);
        cout << "Link Shader Program Failed: " << shaderInfo << endl;
        return -1;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //setup vertex data and attribute pointers
    //vertex data
    GLfloat vertices[] = {
        0.75f, 0.75f, 0.0f,  //right up
        0.75f, 0.25f, 0.0f, //right down
        0.25f, 0.25f, 0.0f, //left down
        0.25f, 0.75f, 0.0f,  //left up
    };

    GLuint indices[] = {
       0, 1, 2,
       2, 3, 0
    };

    GLfloat vertices2[] = {
        -0.25f, -0.25f, 0.0f,  //right up
        -0.25f, -0.75f, 0.0f, //right down
        -0.75f, -0.75f, 0.0f, //left down
        -0.75f, -0.25f, 0.0f,  //left up
    };

    GLuint indices2[] = {
       0, 1, 2,
       2, 3, 0
    };

    GLuint VBO[2], VAO[2], EBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(2, EBO);

    //Bind VAO first, then bind and set VBO data and attribute
    //set 1
    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    //set 2
    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        //Render
        //Clear Color Buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT );

        //Draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[0]);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(VAO[1]);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    };
    
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteBuffers(2, EBO);
    glfwTerminate();
    return 0;
}
