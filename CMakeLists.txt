cmake_minimum_required(VERSION 3.10)

# set the project name
project(test_glfw)

SET(GCC_COVERAGE_COMPILE_FLAGS "")
SET(GCC_COVERAGE_LINK_FLAGS    "-lglfw -ldl")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB_RECURSE SOURCES "src/*.cpp")
SET(GLAD_SOURCE "src/glad/src/glad.c")
 
add_executable(test_glfw ${GLAD_SOURCE} ${SOURCES})

target_link_libraries(test_glfw glfw ${CMAKE_DL_LIBS})
