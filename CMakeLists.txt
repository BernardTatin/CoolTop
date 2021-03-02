cmake_minimum_required(VERSION 3.17)
project(CoolTop C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(CoolTop
        CoolTop/main.c
        include/common.h
        include/environment.h
        include/nuklear_glfw_gl3.h
        src/environment.c
        src/nuklear_glfw_gl3.c)

add_executable(Nuklear-sample
        include/common.h
        include/environment.h
        include/nuklear_glfw_gl3.h
        Nuklear-samplecode/calculator.c
        Nuklear-samplecode/main.c
        Nuklear-samplecode/node_editor.c
        Nuklear-samplecode/overview.c
        Nuklear-samplecode/style.c
        src/environment.c
        src/nuklear_glfw_gl3.c)
