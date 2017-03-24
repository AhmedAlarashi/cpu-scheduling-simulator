cmake_minimum_required(VERSION 3.4)
project(cpu_scheduling_simulator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Brust.h src/Thread.h src/Process.h src/Event.h src/Priority_type.h src/Parse_flag.cpp src/Parse_flag.h src/Simulator.cpp src/Simulator.h src/Priority_type.cpp src/scheduling_algo/Scheduling_algorithm.h src/scheduling_algo/algo_FCFS.h src/scheduling_algo/algo_RR.h src/scheduling_algo/algo_PRIORITY.h src/scheduling_algo/algo_CUSTOM.h)
add_executable(cpu_scheduling_simulator ${SOURCE_FILES})
