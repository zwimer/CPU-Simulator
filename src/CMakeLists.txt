cmake_minimum_required(VERSION 3.0)
project(CPU-Simulator)

add_executable(CPU-Simulator.out
	main.cpp
	Time.cpp
	PList.cpp
	Process.cpp
	Event.cpp
	Algo.cpp
	FCFS.cpp SJF.cpp RR.cpp )
