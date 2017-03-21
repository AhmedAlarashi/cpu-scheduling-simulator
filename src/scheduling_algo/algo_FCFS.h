//
// Created by huan on 3/20/17.
//

#ifndef CPU_SCHEDULING_SIMULATOR_FCFS_H
#define CPU_SCHEDULING_SIMULATOR_FCFS_H

#include "Scheduling_algorithm.h"
#include <queue>

using namespace std;

class algo_FCFS : public Scheduling_algorithm {
public:

    void add(Thread *thread) {
        q_.push(thread);
    }

    const Thread *dispatch() {
        Thread *top = q_.front();
        q_.pop();
        return top;
    }

private:
    queue<Thread *> q_;
};


#endif //CPU_SCHEDULING_SIMULATOR_FCFS_H
