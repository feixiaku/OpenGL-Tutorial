#cmake_minimum_required(VERSION 2.6)
#project (openglTest)

find_package(OpenGL REQUIRED)
message(STATUS "OPNEGL_INCLUDE_DIR =  ${OPENGL_INCLUDE_DIR}")
message(STATUS "OPNEGL_LIB_DIR =  ${OPENGL_LIBRARIES}")

set(CMAKE_VERBOSE_MAKEFILE on)

set(SRC_LISTS 
    tutorial_create_triangle.cpp
    ../../common/shader.cpp
    #triangle.cpp
    )

include_directories(
    /usr/local/include/GLFW/
    /usr/local/Cellar/glew/2.0.0/include/
    /usr/local/Cellar/glm/0.9.8.3/include/
    ../../common/
    /usr/local/include/SOIL/
    .
    )

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    GLFW
    glew
    SOIL
    )


#LINK_LIBRARIES (
#    "/usr/local/lib/SOIL/libSOIL.dylib"
#    "/usr/local/Cellar/glfw/3.2.1/lib/lib/libglfw.dylib"
#    "/usr/local/Cellar/glew/2.0.0/lib/libGLEW.dylib"
#    )

link_directories(
    /usr/local/lib/SOIL/
    /usr/local/Cellar/glfw/3.2.1/lib/
    /usr/local/Cellar/glew/2.0.0/lib/
    )

add_executable(tutorial_create_triangle 
    ${SRC_LISTS}
    )

target_link_libraries(tutorial_create_triangle
    ${ALL_LIBS} 
    )

