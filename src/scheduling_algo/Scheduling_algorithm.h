//
// Created by huan on 3/20/17.
//

#ifndef CPU_SCHEDULING_SIMULATOR_SCHEDULING_ALGORITHM_H
#define CPU_SCHEDULING_SIMULATOR_SCHEDULING_ALGORITHM_H

#include <string>
#include "../Process.h"
#include "../Event.h"

class Scheduling_algorithm {
public:
    virtual void add(Thread *thread) = 0;

    virtual bool has_ready_thread() = 0;

    virtual Thread *peek_next() = 0;

    virtual Thread *dispatch() = 0;

    virtual Event execute(size_t) = 0;

    virtual std::string to_string() = 0;

protected:
    Thread *running_thread = 0;
};

#endif //CPU_SCHEDULING_SIMULATOR_SCHEDULING_ALGORITHM_H
