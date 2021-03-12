cmake_minimum_required(VERSION 3.17)
project(CoolTop C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

#list(APPEND COMMON_LIBS "glfw" "GL" "m" "GLU" "GLEW" "nklib" "m" "GL")
list(APPEND COMMON_LIBS "glfw" "GL" "GLU" "GLEW" "nklib" "m" "GL")

include_directories(lib/include ~/git/Nuklear)

add_executable(CoolTop
        CoolTop/main.c
        lib/include/common.h
        lib/include/environment.h
        lib/include/local-nuklear.h
        lib/include/nuke-tools.h
        CoolTop/cooltop-tools.c
        CoolTop/cooltop-tools.h
        CoolTop/cooltop-common.h
        CoolTop/static-system-data.c
        CoolTop/static-system-data.h
        CoolTop/dynamic-system-data.c
        CoolTop/dynamic-system-data.h)

add_executable(Nuklear-sample
        lib/include/common.h
        lib/include/environment.h
        lib/include/local-nuklear.h
        Nuklear-samplecode/calculator.c
        Nuklear-samplecode/main.c
        Nuklear-samplecode/node_editor.c
        Nuklear-samplecode/overview.c
        Nuklear-samplecode/style.c
        lib/include/nuke-tools.h)

add_library(nklib STATIC lib/src/environment.c
        lib/src/local-nuklear.c
        lib/src/nuke-tools.c
        lib/include/common.h
        lib/include/environment.h
        lib/include/local-nuklear.h
        lib/include/nuke-tools.h
        )

target_link_libraries(CoolTop  ${COMMON_LIBS})
target_link_libraries(Nuklear-sample ${COMMON_LIBS})
