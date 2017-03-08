//
// Created by huan on 3/7/17.
//

#ifndef CPU_SCHEDULING_SIMULATOR_PROCESS_H
#define CPU_SCHEDULING_SIMULATOR_PROCESS_H

#include <vector>
#include <cstddef>
#include "Thread.h"
#include "Priority_type.h"

class Process {
public:
    Process();
    Process(size_t ID, Priority type, size_t numThread);

    void setThread(size_t idx, size_t arrive_time, size_t numBrust);

    // data
    size_t processID;
    size_t numThread;

    Priority type;
    std::vector<Thread> threads;
};


#endif //CPU_SCHEDULING_SIMULATOR_PROCESS_H