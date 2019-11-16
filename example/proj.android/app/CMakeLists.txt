cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

SET(DRAWLOOP_DIR ../../..)

include_directories(${DRAWLOOP_DIR}/include)
include_directories(${DRAWLOOP_DIR}/libs/nanovg/src)
include_directories(${DRAWLOOP_DIR}/libs/nanosvg/src)
include_directories(${DRAWLOOP_DIR}/libs/lua/src)

file(GLOB APP_SRC "../../sources/*.*")
file(GLOB APP_HEADERS "../../sources/*.h")
file(GLOB NATIVE_SRC "src/main/cpp/*.cpp")

add_library (
    applib
    SHARED
    ${APP_SRC}
    ${APP_HEADERS}
    ${NATIVE_SRC}
)

find_library (
    log-lib
    log
    zlib
)

target_link_libraries (
    applib
    android
    z
    log
    EGL
    GLESv2
    OpenSLES
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../build/android/${ANDROID_ABI}/libdrawloop.a
)