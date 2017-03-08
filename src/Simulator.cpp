//
// Created by huan on 3/8/17.
//

#include "Simulator.h"
#include "Priority_type.h"
#include <fstream>

using namespace std;

Simulator::Simulator(Operation opt) {
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
        process.threads.push_back(loadThread(in, processID, i));
    }

    return process;
}

Thread Simulator::loadThread(std::istream &in, size_t processID, size_t threadID) {
    Thread thread;
    size_t arriveTime, numBrust;
    in >> arriveTime >> numBrust;

    thread.arriveTime = arriveTime;
    thread.numBrust = numBrust;
    thread.processID = processID;
    thread.threadID = threadID;

    for (size_t i = 0; i < numBrust; ++i) {
        thread.brusts.push_back(loadBrust(in, (numBrust - i) == 1));
    }

    return thread;
}

Brust Simulator::loadBrust(std::istream &in, bool lastOne) {
    Brust brust;
    size_t cpu = 0, io = 0;
    in >> cpu;
    if (!lastOne) in >> io;
    // else cout << "last one!" << "\t cpu = " << cpu << endl;

    brust.cpu = cpu;
    brust.io = io;

    return brust;
}

void Simulator::startSim() {
    populateNewQueue();

    //TODO later, change this block and add more functions to have a fully featured simulator
    while (!newQueue.empty()) {
        Thread* top = newQueue.front();
        verboseMsg(top->arriveTime, top->processID, top->threadID, Event(THREAD_ARRIVED));
        newQueue.pop();
    }
}

/**
 * After reading all the rules and processes from the file, this function is called to add the processes TO BE SPECIFIC, add the thread to the new queue and prepare to start the simulation.
 */
void Simulator::populateNewQueue() {
    for (Process &p : processes) {
        for (Thread &t : p.threads) {
            newQueue.push(&t);
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