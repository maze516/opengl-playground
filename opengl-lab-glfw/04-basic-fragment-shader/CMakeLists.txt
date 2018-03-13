CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
project(04-basic-fragment-shader)

include_directories(${OPENGL_LAB_GLFW_INCLUDES})

add_executable(04-basic-fragment-shader
        ${OPENGL_LAB_WRAPPER}
        window.h
        window.cpp
        main.cpp
        shader.fsh
        shader.vsh)
    target_link_libraries(04-basic-fragment-shader ${OPENGL_LAB_GLFW_LIBS})

configure_file(shader.fsh ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(shader.vsh ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
