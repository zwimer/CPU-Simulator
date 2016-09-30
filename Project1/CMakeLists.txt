cmake_minimum_required(VERSION 3.0)
project(Project1)

add_library(_MyLib SHARED Algo.cpp Event.cpp Process.cpp FCFS.cpp PList.cpp)

add_executable(a.out main.cpp)
target_link_libraries(a.out _MyLib)
