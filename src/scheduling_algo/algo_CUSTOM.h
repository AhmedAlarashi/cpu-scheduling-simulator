//
// Created by huan on 3/23/17.
//

#ifndef CPU_SCHEDULING_SIMULATOR_ALGO_CUSTOM_H
#define CPU_SCHEDULING_SIMULATOR_ALGO_CUSTOM_H

#include "Scheduling_algorithm.h"
#include "../Thread.h"
#include <queue>
#include <vector>
#include <cstdlib>
#include <iostream>


#ifndef _CPU_SCHEDULING_ALGO_CUSTOM_DATA_STRUCT_
#define _CPU_SCHEDULING_ALGO_CUSTOM_DATA_STRUCT_
namespace CUSTOM_algo {
    struct node {
        size_t last_execute;
        Thread *thread;

        node(Thread *t) {
            last_execute = t->lastexecuteTime;
            thread = t;
        }
    };

    struct Comp {
        bool operator()(const node &a, const node &b) {
            return a.last_execute > b.last_execute;
        }
    };

    typedef priority_queue<CUSTOM_algo::node, vector<CUSTOM_algo::node>, CUSTOM_algo::Comp> pqnode;
}
#endif //_CPU_SCHEDULING_ALGO_CUSTOM_DATA_STRUCT_

using namespace std;

class algo_CUSTOM : public Scheduling_algorithm {
public:
    algo_CUSTOM() {
        qs_.resize(4);
        srand(time(0));
    }

    virtual void add(Thread *thread) {
        qs_[thread->priorityType].push(CUSTOM_algo::node(thread));
    }

    virtual bool has_ready_thread() {
        for (CUSTOM_algo::pqnode &q: qs_) {
            if (q.size())
                return true;
        }
        return false;
    }

    void calc_rand() {
        if (counter != calced_round) {
            rand_num = rand() % 10;
            calced_round = counter;
        }
    }

    size_t which_to_choose() {
        if (rand_num < 1)
            return 3;
        if (rand_num < 3)
            return 2;
        if (rand_num < 6)
            return 1;
        if (rand_num < 10)
            return 0;
        exit(1);
    }

    virtual Thread *peek_next() {
        calc_rand();
        size_t choose_priority = which_to_choose();

        Thread *result;
        if (qs_[choose_priority].size() == 0) {
            for (size_t i = 0; i < 4; i++) {
                if (qs_[i].size()) {
                    result = qs_[i].top().thread;
                    break;
                }
            }
        } else {
            result = qs_[choose_priority].top().thread;
        }

        last_priority = result->priorityType;
        return result;
    }

    virtual Thread *dispatch() {
        running_thread = peek_next();
        qs_[last_priority].pop();
        counter++;
        return running_thread;
    }

    virtual Event execute(size_t system_time) {
        size_t cpu_brust_length = running_thread->next_CPU_brust(system_time);
        size_t time_quantum = time_quantums[running_thread->priorityType];
        if (cpu_brust_length > time_quantum) { // which means the current brust will be preempted
            running_thread->time_spend_on_current_brust(time_quantum);
            return Event(system_time + time_quantum, THREAD_PREEMPTED, *running_thread);
        } else {
            EventType event = (running_thread->is_last_brust()) ? THREAD_COMPLETED : CPU_BRUST_COMPLETED;
            return Event(system_time + cpu_brust_length, event, *running_thread);
        }
    }

    virtual std::string to_string() {
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
    vector<CUSTOM_algo::pqnode> qs_;
    size_t last_priority;

    const size_t time_quantums[4] = {4, 5, 5, 7};

    size_t rand_num;
    size_t counter = 0;
    size_t calced_round = INT32_MAX;
};


#endif //CPU_SCHEDULING_SIMULATOR_ALGO_CUSTOM_H
