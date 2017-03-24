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

    size_t next_CPU_brust(size_t time) {
        if (!thread_started) {
            thread_started = true;
            startTime = time;
        }
        lastexecuteTime = time;
        size_t brust = brusts[current_brust].cpu;
        totalCPUTime += brust;
        return brust;
    }

    // if the next cpu brust cannot be run to the end of the brust
    // this method is called. To add back the time been preempted
    void time_spend_on_current_brust(size_t time) {
        brusts[current_brust].cpu -= time;
        totalCPUTime -= brusts[current_brust].cpu;
    }

    size_t next_IO_brust() {
        size_t brust = brusts[current_brust].io;
        totalIOTime += brust;
        current_brust++;
        return brust;
    }

    bool is_last_brust() {
        return ((current_brust + 1) == numBrust);
    }

    size_t arriveTime = 0;
    size_t startTime = 0;
    size_t finishTime = 0;
    size_t lastexecuteTime = 0;
    size_t responseTime = 0;
    size_t turnaroundTime = 0;
    size_t totalCPUTime = 0;
    size_t totalIOTime = 0;

    size_t threadID = 0;
    size_t processID = 0;
    size_t priorityType = 0;
    size_t current_brust = 0;
    size_t numBrust = 0;
    std::vector<Brust> brusts;

    bool thread_started = false;
};

#endif //CPU_SCHEDULING_SIMULATOR_THREAD_H
