//
// Created by huan on 3/22/17.
//

#ifndef CPU_SCHEDULING_SIMULATOR_ALGO_RR_H
#define CPU_SCHEDULING_SIMULATOR_ALGO_RR_H

#include "Scheduling_algorithm.h"
#include "../Thread.h"
#include <iostream>
#include <queue>

using namespace std;

class algo_RR : public Scheduling_algorithm {
public:
    virtual void add(Thread *thread) {
        q_.push(thread);
    }

    virtual bool has_ready_thread() {
        return (bool) q_.size();
    }

    virtual Thread *peek_next() {
        return q_.front();
    }

    virtual Thread *dispatch() {
        running_thread = q_.front();
        q_.pop();
        return running_thread;
    }

    /**
     *
     * @param system_time
     * @return the next event (A preemption or CPU brust finish)
     */
    virtual Event execute(size_t system_time) {
        size_t cpu_brust_length = running_thread->next_CPU_brust(system_time);
        if (cpu_brust_length > time_quantum) { // which means the current brust will be preempted
            running_thread->time_spend_on_current_brust(time_quantum);
            return Event(system_time + time_quantum, THREAD_PREEMPTED, *running_thread);
        } else {
            EventType event = (running_thread->is_last_brust()) ? THREAD_COMPLETED : CPU_BRUST_COMPLETED;
            return Event(system_time + cpu_brust_length, event, *running_thread);
        }
    }

    virtual std::string to_string() {
        string result("Selected from ");
        result += std::to_string(q_.size());
        result += " threads; will run for at most 3 ticks";
        return result;
    }

private:
    queue<Thread *> q_;

    // Hard-coded value
    const size_t time_quantum = 3;
};

#endif //CPU_SCHEDULING_SIMULATOR_ALGO_RR_H
