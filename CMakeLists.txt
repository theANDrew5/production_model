cmake_minimum_required(VERSION 3.15)
project(Model)

set(CMAKE_CXX_STANDARD 17)

add_executable(Model main.cpp Batch.cpp Batch.h Event.cpp Event.h Machine.cpp Machine.h Recipe.cpp Recipe.h Environment.cpp Environment.h)