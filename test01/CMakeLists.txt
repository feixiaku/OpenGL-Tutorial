cmake_minimum_required(VERSION 2.6)
project (openglTest)

find_package(OpenGL REQUIRED)
message(STATUS "OPNEGL_INCLUDE_DIR =  ${OPENGL_INCLUDE_DIR}")
message(STATUS "OPNEGL_LIB_DIR =  ${OPENGL_LIBRARIES}")

set(CMAKE_VERBOSE_MAKEFILE on)

set(SRC_LISTS 
    tutorial_create_window.cpp
    )
add_executable(tutorial_create_window           
    ${SRC_LISTS}
    )

include_directories(
    /usr/local/include/GLFW/
    /usr/local/Cellar/glew/2.0.0/include/
    /usr/local/Cellar/glm/0.9.8.3/include/
    .
    )

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    GLFW
    glew
    )

#link_libraries(
#    )

link_directories(
    /usr/local/Cellar/glfw/3.2.1/lib/
    /usr/local/Cellar/glew/2.0.0/lib/
    )

target_link_libraries(tutorial_create_window
    ${ALL_LIBS}
    )
