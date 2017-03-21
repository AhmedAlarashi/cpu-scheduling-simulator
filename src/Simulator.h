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

    Process loadProcess(istream &in);

    Thread loadThread(istream &in, Process &process, size_t threadID);

    Brust loadBrust(istream &in, bool lastOne);

    void populateNewQueue();

    void verboseMsg(const Event & event);

    // Parameters
    bool verbose;
    bool per_thread;
    Algorithm algorithm;
    string inputfile;

    // data
    size_t numProcess;
    size_t threadOverhead;
    size_t processOverhead;

    vector<Process> processes;

    priority_queue<Event, vector<Event>, std::greater<Event>> newQueue;
    Scheduling_algorithm *scheduling;
};


#endif //CPU_SCHEDULING_SIMULATOR_SIMULATOR_H
