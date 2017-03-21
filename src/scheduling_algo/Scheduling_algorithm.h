//
// Created by huan on 3/20/17.
//

#ifndef CPU_SCHEDULING_SIMULATOR_SCHEDULING_ALGORITHM_H
#define CPU_SCHEDULING_SIMULATOR_SCHEDULING_ALGORITHM_H

#include "../Process.h"

class Scheduling_algorithm {
public:
    virtual void add(Thread *thread) = 0;

    virtual const Thread *dispatch() = 0;
};

#endif //CPU_SCHEDULING_SIMULATOR_SCHEDULING_ALGORITHM_H
