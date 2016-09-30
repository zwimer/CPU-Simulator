cmake_minimum_required(VERSION 3.0)
project(Project1)

add_library(_MyLib SHARED
	PList.cpp
	Process.cpp
	Event.cpp
	Algo.cpp
	FCFS.cpp SJF.cpp RR.cpp )

add_executable(a.out main.cpp)
target_link_libraries(a.out _MyLib)
