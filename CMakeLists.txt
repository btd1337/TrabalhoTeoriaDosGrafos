cmake_minimum_required(VERSION 3.5)
project(TrabalhoGrafos)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Main.cpp Adjacente.cpp Adjacente.h Grafo.cpp Grafo.h Vertice.cpp Vertice.h)
add_executable(TrabalhoGrafos ${SOURCE_FILES})