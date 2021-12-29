cmake_minimum_required(VERSION 3.0)

project(projeto-cg)

find_package(OpenGL REQUIRED)
set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/install)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp" "src/*.hpp")

add_executable(programa ${SOURCES})

target_link_libraries(programa
	glfw
  OpenGL::GL
	GLEW::glew
)
