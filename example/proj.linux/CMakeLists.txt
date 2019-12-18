cmake_minimum_required(VERSION 3.15)
project(proj_linux)

set(CMAKE_CXX_STANDARD 11)

find_package(glfw3 3.3 REQUIRED)

include_directories(
        "/usr/local/include"
        "../sources"
        "../../libs/nanovg/src"
        "../../libs/nanosvg/src"
        "../../sources"
)
link_directories(
        "/usr/local/lib"
        "../../build/linux"
)

file(GLOB SOURCES
        "../sources/*.*"
)

add_executable(proj_linux ${SOURCES} main.cpp utils.cpp )
target_include_directories(proj_linux PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../sources)
target_link_libraries(proj_linux -lglfw3 -lX11 -ldl -lGLU -lglut -lGLEW -lGL -pthread -ldrawloop )