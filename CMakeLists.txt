cmake_minimum_required(VERSION 3.9)
project(csomszall)

set(CMAKE_CXX_STANDARD 98)

add_executable(csomszall main.cpp Luggage.cpp Luggage.h Controller.cpp Controller.h Junction.cpp Junction.h Conveyor.cpp Conveyor.h System.cpp System.h)