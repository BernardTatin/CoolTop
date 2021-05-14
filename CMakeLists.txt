cmake_minimum_required(VERSION 3.17)
project(CoolTop C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE FALSE)

IF(${CMAKE_SYSTEM_NAME} MATCHES "NetBSD")
    find_package(glfw3 CONFIG REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
    find_package(GLEW REQUIRED)
    list(APPEND COMMON_LIBS "glfw" "GL" "GLU" "GLEW" "nklib" "m" "GL")
endif(${CMAKE_SYSTEM_NAME} MATCHES "NetBSD")
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    list(APPEND COMMON_LIBS "glfw" "GL" "GLU" "GLEW" "nklib" "m" "GL")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

include_directories(lib/include ~/git/Nuklear)
IF(${CMAKE_SYSTEM_NAME} MATCHES "NetBSD")
    link_directories(/usr/X11R7/lib /usr/pkg/lib)
    include_directories(/usr/X11R7/include /usr/pkg/include)
endif(${CMAKE_SYSTEM_NAME} MATCHES "NetBSD")

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
        lib/include/nuke-tools.h Nuklear-samplecode/about-box.c Nuklear-samplecode/about-box.h Nuklear-samplecode/nuke_sample.h Nuklear-samplecode/nuke_sample.c)

add_library(nklib STATIC lib/src/environment.c
        lib/src/local-nuklear.c
        lib/src/nuke-tools.c
        lib/include/common.h
        lib/include/environment.h
        lib/include/local-nuklear.h
        lib/include/nuke-tools.h
        lib/src/windows_list.c lib/include/windows_list.h lib/src/window_element.c lib/include/window_element.h)

target_link_libraries(CoolTop  ${COMMON_LIBS})
target_link_libraries(Nuklear-sample ${COMMON_LIBS})
