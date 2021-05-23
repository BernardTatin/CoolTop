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

include_directories(nklib/include ctoplib/include)
include_directories(~/git/Nuklear)
IF(${CMAKE_SYSTEM_NAME} MATCHES "NetBSD")
    link_directories(/usr/X11R7/lib /usr/pkg/lib)
    include_directories(/usr/X11R7/include /usr/pkg/include)
endif(${CMAKE_SYSTEM_NAME} MATCHES "NetBSD")

add_library(nklib STATIC nklib/src/environment.c
        nklib/src/local-nuklear.c
        nklib/src/nuke-tools.c
        nklib/include/common.h
        nklib/include/environment.h
        nklib/include/local-nuklear.h
        nklib/include/nuke-tools.h
        nklib/src/windows_list.c
        nklib/include/windows_list.h
        nklib/src/window_element.c
        nklib/include/window_element.h)

add_library(ctoplib STATIC
        ctoplib/src/static-data.c ctoplib/include/static-data.h
        )

add_executable(test-ctop
        test-ctop/test-ctop.c)

add_executable(CoolTop
        CoolTop/main.c
        nklib/include/common.h
        nklib/include/environment.h
        nklib/include/local-nuklear.h
        nklib/include/nuke-tools.h
        CoolTop/cooltop-tools.c
        CoolTop/cooltop-tools.h
        CoolTop/cooltop-common.h
        CoolTop/static-system-data.c
        CoolTop/static-system-data.h
        CoolTop/dynamic-system-data.c
        CoolTop/dynamic-system-data.h)

add_executable(Nuklear-sample
        nklib/include/common.h
        nklib/include/environment.h
        nklib/include/local-nuklear.h
        Nuklear-samplecode/calculator.c
        Nuklear-samplecode/main.c
        Nuklear-samplecode/node_editor.c
        Nuklear-samplecode/overview.c
        Nuklear-samplecode/style.c
        nklib/include/nuke-tools.h
        Nuklear-samplecode/about-box.c
        Nuklear-samplecode/about-box.h
        Nuklear-samplecode/nuke_sample.h
        Nuklear-samplecode/nuke_sample.c)

target_link_libraries(test-ctop  ctoplib)
target_link_libraries(CoolTop  ${COMMON_LIBS})
target_link_libraries(Nuklear-sample ${COMMON_LIBS})
