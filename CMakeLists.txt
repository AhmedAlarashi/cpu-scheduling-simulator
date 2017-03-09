cmake_minimum_required(VERSION 3.6)
project(cpu_scheduling_simulator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Brust.cpp src/Brust.h src/Thread.cpp src/Thread.h src/Process.cpp src/Process.h src/Event.cpp src/Event.h src/Schedule_state.h src/Priority_type.h src/Prase_flag.cpp src/Prase_flag.h src/Simulator.cpp src/Simulator.h src/Priority_type.cpp)
add_executable(cpu_scheduling_simulator ${SOURCE_FILES})