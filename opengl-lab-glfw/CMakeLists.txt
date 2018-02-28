CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
project(opengl-lab-glfw)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat -Wno-padded")

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLM REQUIRED glm)

find_library(COCOA_FRAMEWORK Cocoa)
find_library(IOKIT_FRAMEWORK IOKit)
find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
find_library(CORE_VIDEO_FRAMEWORK CoreVideo)

set(OPENGL_LAB_GLFW_INCLUDES
        ${GLFW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ../opengl-wrapper
        ../opengl-wrapper/glad/include)

set(OPENGL_LAB_GLFW_LIBS
        ${GLFW_LIBRARIES}
        ${GLM_LIBRARIES}
        ${COCOA_FRAMEWORK}
        ${OPENGL_gl_LIBRARY}
        ${IOKIT_FRAMEWORK}
        ${CORE_FOUNDATION_FRAMEWORK}
        ${CORE_VIDEO_FRAMEWORK})

set(OPENGL_LAB_WRAPPER
    ../opengl-wrapper/logger.h
    ../opengl-wrapper/openglwindow.h
    ../opengl-wrapper/openglwindow.cpp
    ../opengl-wrapper/simpletimer.h
    ../opengl-wrapper/glad/src/glad.c)


add_subdirectory(01-empty-window)
