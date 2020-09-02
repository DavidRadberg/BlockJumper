cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the project name
project(BlockJumper)

SET(GCC_COVERAGE_COMPILE_FLAGS "")
SET(GCC_COVERAGE_LINK_FLAGS    "-lglfw -ldl -lspdlog")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

include_directories("src/renderer" "src/character" "src/3rd-party" "src/objects" "src/util")

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")
SET(GLAD_SOURCE "src/glad/glad.c")

add_executable(BlockJumper ${GLAD_SOURCE} ${SOURCES} ${HEADERS})

target_link_libraries(BlockJumper glfw ${CMAKE_DL_LIBS})
