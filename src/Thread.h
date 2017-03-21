//
// Created by huan on 3/7/17.
//

#ifndef CPU_SCHEDULING_SIMULATOR_THREAD_H
#define CPU_SCHEDULING_SIMULATOR_THREAD_H

#include <vector>
#include <cstddef>
#include "Brust.h"

// TODO: brust may be better with queue
class Thread {
public:
    Thread() {}

    size_t arriveTime;
    size_t threadID;
    size_t processID;
    size_t priorityType;
    size_t numBrust;
    std::vector<Brust> brusts;
};


#endif //CPU_SCHEDULING_SIMULATOR_THREAD_H
