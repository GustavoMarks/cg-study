cmake_minimum_required(VERSION 3.0)

project(projeto-cg)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp" "src/*.hpp")

add_executable(programa ${SOURCES})
