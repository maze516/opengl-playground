CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
project(02-first-triangle)

include_directories(${OPENGL_LAB_GLFW_INCLUDES})

add_executable(02-first-triangle
        ${OPENGL_LAB_WRAPPER}
        window.h
        window.cpp
        main.cpp
        shader.fsh
        shader.vsh)
    target_link_libraries(02-first-triangle ${OPENGL_LAB_GLFW_LIBS})
