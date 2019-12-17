cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(PROJECTNAME drawloop)
project(${PROJECTNAME})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "C++11 support has been enabled by default.")

file(GLOB LIB_NVG "libs/nanovg/src/*.*")
file(GLOB LIB_NVGSVG "libs/nanosvg/src/*.h")

if( ANDROID )
	file(GLOB LIB_NVG_EXT "")
elseif( UNIX )
	file(GLOB LIB_NVG_EXT "libs/metalvg/src/*.*")

endif()

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/libs/metalvg/src
	${CMAKE_CURRENT_SOURCE_DIR}/libs/nanovg/src
	${CMAKE_CURRENT_SOURCE_DIR}/libs/nanosvg/src
)

file(
	GLOB_RECURSE SRCS RELATIVE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	sources/*.*
)
list(REMOVE_DUPLICATES SRCS)

foreach(source IN LISTS SRCS)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()  
message(STATUS "Tree reorganized")

set(PROJECT_FILES ${SRCS} ${LIB_NVG} ${LIB_NVGSVG} ${LIB_LUA})
add_library(${PROJECTNAME} ${SRCS} ${FILES_SRC} ${FILES_HEADERS} ${LIB_NVG} ${LIB_NVG_EXT} ${LIB_NVGSVG} ${LIB_LUA})

target_include_directories(${PROJECTNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sources)
TARGET_LINK_LIBRARIES(${PROJECTNAME})