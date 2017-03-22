//
// Created by huan on 3/7/17.
//

#ifndef CPU_SCHEDULING_SIMULATOR_THREAD_H
#define CPU_SCHEDULING_SIMULATOR_THREAD_H

#include <vector>
#include <cstddef>
#include "Brust.h"

class Thread {
public:
    Thread() {}

    size_t next_CPU_brust() {
        return brusts[current_brust].cpu;
    }

    size_t next_IO_brust() {
        size_t brust = brusts[current_brust].io;
        current_brust++;
        return brust;
    }

    bool is_last_brust() {
        return ((current_brust + 1) == numBrust);
    }

    size_t arriveTime = 0;
    size_t finishTime = 0;
    size_t threadID = 0;
    size_t processID = 0;
    size_t priorityType = 0;
    size_t current_brust = 0;
    size_t numBrust = 0;
    std::vector<Brust> brusts;
    bool CPU_brust_finished = false;
};

#endif //CPU_SCHEDULING_SIMULATOR_THREAD_H
