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

    bool has_ready_thread() {
        return (bool) q_.size();
    }

    Thread *peek_next() {
        return q_.front();
    }

    Thread *dispatch() {
        running_thread = q_.front();
        q_.pop();
        return running_thread;
    }

    Event execute(size_t system_time) {
        size_t time = system_time + running_thread->next_CPU_brust(system_time);
        EventType event = (running_thread->is_last_brust()) ? THREAD_COMPLETED : CPU_BRUST_COMPLETED;
        return Event(time, event, *running_thread);
    }

    string to_string() {
        string result("Selected from ");
        result += std::to_string(q_.size());
        result += " threads; will run to completion of burst";
        return result;
    }

private:
    queue<Thread *> q_;
};

#endif //CPU_SCHEDULING_SIMULATOR_FCFS_H
