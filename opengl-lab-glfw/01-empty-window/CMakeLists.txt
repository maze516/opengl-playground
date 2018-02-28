CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
project(01-empty-window)

include_directories(${OPENGL_LAB_GLFW_INCLUDES})

add_executable(01-empty-window
        ${OPENGL_LAB_WRAPPER}
        window.h
        window.cpp
        main.cpp)
    target_link_libraries(01-empty-window ${OPENGL_LAB_GLFW_LIBS})
#    target_compile_definitions(01-empty-window PUBLIC -DSHOW_DEBUG_INFO)
