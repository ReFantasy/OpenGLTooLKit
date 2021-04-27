CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
project(OpenGLToolKit)
set(CMAKE_CXX_STANDARD 17)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
link_libraries(${OPENGL_LIBRARY})

IF (WIN32)
    MESSAGE(STATUS "Now is windows")
    include_directories("${CMAKE_SOURCE_DIR}/include")
    LINK_DIRECTORIES( ${CMAKE_SOURCE_DIR}/lib)
    link_libraries(optimized glew32 glfw3 soil2)
    link_libraries(debug glew32d glfw3d soil2d)
ELSEIF (APPLE)
    MESSAGE(STATUS "Now is Apple systens.")
    include_directories("/usr/local/Cellar/glew/2.2.0_1/include")
    include_directories("/usr/local/Cellar/glfw/3.3.3/include")
    include_directories("${CMAKE_SOURCE_DIR}/include")
    link_directories("/usr/local/Cellar/glew/2.2.0_1/lib")
    link_directories("/usr/local/Cellar/glfw/3.3.3/lib")
    link_libraries(${OPENGL_LIBRARY} GLEW glfw)
ELSEIF (UNIX)
    MESSAGE(STATUS "Now is UNIX-like OS's.")
ENDIF ()



AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/src SRC_LIST)
add_executable(gl_tool_kit ${SRC_LIST})

