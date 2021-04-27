 cmake_minimum_required(VERSION 3.0)
project(OpenGLToolKit)
set(CMAKE_CXX_STANDARD 17)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
link_libraries(${OPENGL_LIBRARY})


include_directories("${CMAKE_SOURCE_DIR}/include")
LINK_DIRECTORIES( ${CMAKE_SOURCE_DIR}/lib)
link_libraries(optimized glew32 glfw3 soil2)
link_libraries(debug glew32d glfw3d soil2d)

AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/src SRC_LIST)
add_executable(gl_tool_kit ${SRC_LIST})

