cmake_minimum_required(VERSION 3.0)
project(MeshSegmentation)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(MeshSegmentation ${SOURCES})
