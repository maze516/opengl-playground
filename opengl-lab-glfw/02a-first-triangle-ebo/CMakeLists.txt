CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
project(02a-first-triangle-ebo)

include_directories(${OPENGL_LAB_GLFW_INCLUDES})

add_executable(02a-first-triangle-ebo
        ${OPENGL_LAB_WRAPPER}
        window.h
        window.cpp
        main.cpp
        shader.fsh
        shader2.fsh
        shader.vsh)
    target_link_libraries(02a-first-triangle-ebo ${OPENGL_LAB_GLFW_LIBS})

configure_file(shader.fsh ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(shader2.fsh ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(shader.vsh ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
