//
// Created by huan on 3/8/17.
//

#ifndef CPU_SCHEDULING_SIMULATOR_SIMULATOR_H
#define CPU_SCHEDULING_SIMULATOR_SIMULATOR_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include "Prase_flag.h"
#include "Process.h"
#include "Event.h"

struct SimNode {
    size_t ProcessID;
    size_t ThreadID;
    size_t EventType;
};

class Simulator {
public:
    // paramed constructor
    Simulator(Operation opt);

    void loadFromFile();

    void startSim();

private:
    // functions
    Process loadProcess(std::istream &in);

    Thread loadThread(std::istream &in, size_t processID, size_t threadID);

    Brust loadBrust(std::istream &in, bool lastOne);

    void populateNewQueue();
    void verboseMsg(size_t time, size_t processID, size_t threadID, Event event);

    // Parameters
    bool verbose;
    bool per_thread;
    Algorithm algorithm;
    char *inputfile;

    // data
    size_t numProcess;
    size_t threadOverhead;
    size_t processOverhead;

    std::vector<Process> processes;

    // The queue (implemented as a map)
    //std::map<size_t, SimNode> rawQueue;
    std::queue<Thread *> newQueue;
};


#endif //CPU_SCHEDULING_SIMULATOR_SIMULATOR_H
