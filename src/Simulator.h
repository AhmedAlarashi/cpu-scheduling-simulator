//
// Created by huan on 3/8/17.
//

/**
 * Class description
 * This is the overall framework of the entire simulator. It handles 5 stage transaction machine,
 * and controls all the input/ output. In general this controls everything except the detailed implementation of
 * the dispatching algorithm. All the dispatching algorithms are in the separate file for clarity. This "machine"
 * Only need to invoke different scheduling algorithm to get the detailed scheduling done.
 */

#ifndef CPU_SCHEDULING_SIMULATOR_SIMULATOR_H
#define CPU_SCHEDULING_SIMULATOR_SIMULATOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include "Prase_flag.h"
#include "Process.h"
#include "Event.h"
#include "scheduling_algo/Scheduling_algorithm.h"
#include "scheduling_algo/algo_FCFS.h"

using namespace std;

struct SimNode {
    size_t ProcessID;
    size_t ThreadID;
    size_t EventType;
};

class Simulator {
public:
    Simulator(const Operation opt);

    void startSim();

private:
    // functions
    void choose_scheduling_algorithm();

    void loadFromFile();

    void populateNewQueue();

    void advance();

    void event_handler(const Event &event);

    Event get_next_event();

    Process loadProcess(istream &in);

    Thread loadThread(istream &in, Process &process, size_t threadID);

    Brust loadBrust(istream &in, bool lastOne);

    void normalMsg();

    void perthreadMsg();

    void verboseMsg(const Event &event);

    void usage_analysis();

    // Parameters
    bool verbose;
    bool per_thread;
    Algorithm algorithm;
    string inputfile;

    // data
    bool has_running_or_scheduled_thread = false;

    size_t system_time;
    size_t last_processID;
    size_t numProcess;
    size_t threadOverhead;
    size_t processOverhead;

    vector<Process> processes;

    priority_queue<Event, vector<Event>, std::greater<Event>> eventTracker;

    Scheduling_algorithm *scheduler;

    //statistics
    size_t total_service_time = 0,
            total_io_time = 0,
            total_dispatch_time = 0,
            total_idle_time = 0,
            total_elapsed_time = 0;
    double CPU_utility, CPU_efficiency;

    // string streams
    ostringstream verbose_buffer;
    ostringstream normal_buffer;
    ostringstream per_thread_buffer;
};

#endif //CPU_SCHEDULING_SIMULATOR_SIMULATOR_H
