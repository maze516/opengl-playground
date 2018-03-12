CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
project(03-basic-vertex-shader)

include_directories(${OPENGL_LAB_GLFW_INCLUDES})

add_executable(03-basic-vertex-shader
        ${OPENGL_LAB_WRAPPER}
        window.h
        window.cpp
        main.cpp
        shader.fsh
        shader.vsh)
    target_link_libraries(03-basic-vertex-shader ${OPENGL_LAB_GLFW_LIBS})

configure_file(shader.fsh ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(shader.vsh ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
