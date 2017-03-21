//
// Created by huan on 3/8/17.
//

#include "Simulator.h"
#include "Priority_type.h"

using namespace std;

Simulator::Simulator(const Operation opt) {
    this->algorithm = opt.ALGO;
    this->inputfile = opt.INFILE;
    this->per_thread = opt.PER_THREAD;
    this->verbose = opt.VERBOSE;
}

void Simulator::loadFromFile() {
    ifstream fin(inputfile);
    if (!fin) {
        cerr << "Error opening file: " << inputfile << endl;
        exit(EXIT_FAILURE);
    }

    fin >> numProcess >> threadOverhead >> processOverhead;
    for (size_t i = 0; i < numProcess; ++i) {
        processes.push_back(loadProcess(fin));
    }

    fin.close();
}

Process Simulator::loadProcess(istream &in) {
    Process process;
    size_t processID, type, numThread;
    in >> processID >> type >> numThread;

    process.processID = processID;
    process.numThread = numThread;
    process.priorityType = type;

    for (size_t i = 0; i < numThread; ++i) {
        process.threads.push_back(loadThread(in, process, i));
    }
    cout << process.threads.size()<<endl;

    return process;
}

Thread Simulator::loadThread(istream &in, Process &process, size_t threadID) {
    Thread thread;
    size_t arriveTime, numBrust;
    in >> arriveTime >> numBrust;

    thread.arriveTime = arriveTime;
    thread.numBrust = numBrust;
    thread.threadID = threadID;
    thread.processID = process.processID;
    thread.priorityType = process.priorityType;

    for (size_t i = 0; i < numBrust; ++i) {
        thread.brusts.push_back(loadBrust(in, (numBrust - i) == 1));
    }

    return thread;
}

Brust Simulator::loadBrust(istream &in, bool lastOne) {
    Brust brust;
    size_t cpu = 0, io = 0;
    in >> cpu;
    if (!lastOne) in >> io;

    brust.cpu = cpu;
    brust.io = io;

    return brust;
}

void Simulator::startSim() {
    cout << "loading file" << endl;
    loadFromFile();
    cout << "populating New Queue" << endl;
    populateNewQueue();

    //TODO later, change this block and add more functions to have a fully featured simulator
    while (!newQueue.empty()) {
        verboseMsg(newQueue.top());
        newQueue.pop();
    }
}

/**
 * After reading all the rules and processes from the file, this function is called to add the processes TO BE SPECIFIC, add the thread to the new queue and prepare to start the simulation.
 */
void Simulator::populateNewQueue() {
    for (Process &p : processes) {
        for (Thread &t : p.threads) {
            newQueue.push(Event(t.arriveTime, THREAD_ARRIVED, t));
        }
    }
}

void Simulator::verboseMsg(size_t time, size_t processID, size_t threadID, Event event) {
    cout << "At time " << time << ":" << endl
         << "\t" << event << endl
         << "\tThread " << threadID << " in process " << processID << " "
         << PriorityStr[processes[processID].priorityType] << endl
         << "\tThread arrived." << endl << endl;
}

void Simulator::verboseMsg(const Event &event) {
    cout << "At time " << event.eventTime << ":" << endl
         << "\t" << event << endl
         << "\tThread " << event.threadID << " in process " << event.processID << " "
         << PriorityStr[event.priorityType] << endl
         << "\tThread arrived." << endl << endl;
}