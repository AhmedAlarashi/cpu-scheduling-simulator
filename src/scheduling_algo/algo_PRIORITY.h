//
// Created by huan on 3/22/17.
//

#ifndef CPU_SCHEDULING_SIMULATOR_ALGO_PRIORITY_H
#define CPU_SCHEDULING_SIMULATOR_ALGO_PRIORITY_H

#include "Scheduling_algorithm.h"
#include "../Thread.h"
#include "../Priority_type.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class algo_PRIORITY : public Scheduling_algorithm {
public:
    algo_PRIORITY() { qs_.resize(4); }

    virtual void add(Thread *thread) {
        qs_[thread->priorityType].push(thread);
    }

    virtual bool has_ready_thread() {
        for (queue<Thread *> &q: qs_) {
            if (q.size())
                return true;
        }
        return false;
    }

    virtual Thread *peek_next() {
        Thread *result;
        for (queue<Thread *> &q: qs_) {
            if (q.size()) {
                result = q.front();
                last_priority = result->priorityType;
                break;
            }
        }
        return result;
    }

    virtual Thread *dispatch() {
        running_thread = peek_next();
        qs_[last_priority].pop();
        return running_thread;
    }

    virtual Event execute(size_t system_time) {
        size_t time = system_time + running_thread->next_CPU_brust(system_time);
        EventType event = (running_thread->is_last_brust()) ? THREAD_COMPLETED : CPU_BRUST_COMPLETED;
        return Event(time, event, *running_thread);
    }

    virtual std::string to_string() {
        //Selected from queue 0 [S:0 I:1 N:0 B:0]

        string result("Select from queue ");
        result.reserve(45);
        result += std::to_string(last_priority);
        result += " [S:";
        result += std::to_string(qs_[0].size());
        result += " I:";
        result += std::to_string(qs_[1].size());
        result += " N:";
        result += std::to_string(qs_[2].size());
        result += " B:";
        result += std::to_string(qs_[3].size());
        result += "]";
        return result;
    }

private:
    vector<queue<Thread *>> qs_;
    size_t last_priority;
};

#endif //CPU_SCHEDULING_SIMULATOR_ALGO_PRIORITY_H
