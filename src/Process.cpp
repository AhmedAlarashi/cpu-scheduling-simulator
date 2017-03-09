//
// Created by huan on 3/7/17.
//

#include "Process.h"

using namespace std;

/**
 * Initialize a process
 */
Process::Process() {
    processID = 0;
    numThread = 0;
    priorityType = 0;
}

/**
 * Initialize a process with give parameters, and resize the thread vector to correct size
 * @param ID        ID of the process
 * @param type      Priority type of the process
 * @param numThread Number of thread the process has
 */
Process::Process(size_t ID, size_t type, size_t numThread) {
    this->processID = ID;
    this->priorityType = type;
    this->numThread = numThread;

    this->threads.resize(numThread);
}

/**
 * Set the
 * @param idx           ID of the thread
 * @param arrive_time
 * @param numBrust
 */
void Process::setThread(size_t idx, size_t arrive_time, size_t numBrust) {

}