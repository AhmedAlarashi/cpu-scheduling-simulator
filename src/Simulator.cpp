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

    // initialize system time and last_processId (set to INT_MAX just act as a rubbish data)
    system_time = 0;
    last_CPU_finish_time = 0;
    last_processID = INT32_MAX;
}

void Simulator::choose_scheduling_algorithm() {
    if (algorithm == Algorithm::FCFS)
        scheduling = new algo_FCFS;
    else {
        cout << "No matching algorithm provided" << endl;
        exit(EXIT_FAILURE);
    }
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

    for (size_t i = 0; i < numThread; ++i)
        process.threads.push_back(loadThread(in, process, i));

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

/**
 * After reading all the rules and processes from the file, this function is called to add the processes TO BE SPECIFIC, add the thread to the new queue and prepare to start the simulation.
 */
void Simulator::populateNewQueue() {
    for (Process &p : processes) {
        for (Thread &t : p.threads) {
            eventTracker.push(Event(t.arriveTime, THREAD_ARRIVED, t));
        }
    }
}

Event Simulator::get_next_event() {
    Event result = eventTracker.top();
    eventTracker.pop();
    return result;
}

void Simulator::event_handler(const Event &event) {
    if (verbose) verboseMsg(event);
    system_time = event.eventTime;

    Thread *thread = &processes[event.processID].threads[event.threadID];
    switch (event.eventType) {
        case THREAD_ARRIVED:
            scheduling->add(thread);
            break;

        case THREAD_DISPATCH_COMPLETED:
        case PROCESS_DISPATCH_COMPLETED:
            eventTracker.push(scheduling->execute(system_time));
            break;

        case CPU_BRUST_COMPLETED:
            has_running_or_scheduled_thread = false;
//            if (thread->is_last_brust())
//                eventTracker.push(Event(system_time, THREAD_COMPLETED, *thread));
//            else {
            system_time += thread->next_IO_brust();
            eventTracker.push(Event(system_time, IO_BRUST_COMPLETED, *thread));
            // }
            break;

        case IO_BRUST_COMPLETED:
            scheduling->add(thread);
            break;

        case THREAD_COMPLETED:
            has_running_or_scheduled_thread = false;
            thread->finishTime = system_time;
            break;

        case THREAD_PREEMPTED:
            break;

        case DISPATCHER_INVOKED:
            // Test if it is a process switch or a thread switch
            EventType eventType;
            has_running_or_scheduled_thread = true;
            if (last_processID == event.processID) {
                system_time += threadOverhead;
                eventType = THREAD_DISPATCH_COMPLETED;
            } else {
                last_processID = event.processID;
                system_time += processOverhead;
                eventType = PROCESS_DISPATCH_COMPLETED;
            }
            thread = scheduling->dispatch();
            eventTracker.push(Event(system_time, eventType, *thread));
            break;
    }
}

/**
 * Starting from current system, do:
 * 1. take the next event from event tracker
 * 2.
 */
void Simulator::advance() {
    Event event = get_next_event();
    event_handler(event);
    if (!has_running_or_scheduled_thread && scheduling->has_ready_thread()) {
        Thread *thread = scheduling->peek_next();
        eventTracker.push(Event(event.eventTime, DISPATCHER_INVOKED, *thread));
        has_running_or_scheduled_thread = true;
    }
}

void Simulator::startSim() {
    // cout << "choosing scheduling algorithm" << endl << endl;
    choose_scheduling_algorithm();
    // cout << "loading file" << endl << endl;
    loadFromFile();
    // cout << "populating New Queue" << endl << endl;
    populateNewQueue();

    while (!eventTracker.empty())
        advance();

    cout << verbose_buffer.str();
}

void Simulator::verboseMsg(const Event &event) {
    verbose_buffer << "At time " << event.eventTime << ":" << endl
                   << "\t" << event << endl
                   << "\tThread " << event.threadID << " in process " << event.processID << " "
                   << PriorityStr[event.priorityType] << endl << "\t";
    switch (event.eventType) {
        case THREAD_ARRIVED:
            verbose_buffer << "Transitioned from NEW to READY";
            break;
        case THREAD_DISPATCH_COMPLETED:
        case PROCESS_DISPATCH_COMPLETED:
            verbose_buffer << "Transitioned from READY to RUNNING";
            break;
        case CPU_BRUST_COMPLETED:
            verbose_buffer << "Transitioned from RUNNING to BLOCKED";
            break;
        case IO_BRUST_COMPLETED:
            verbose_buffer << "Transitioned from BLOCKED to READY";
            break;
        case THREAD_COMPLETED:
            verbose_buffer << "Transitioned from RUNNING to EXIT";
            break;
        case THREAD_PREEMPTED:
            verbose_buffer << "DSFSDKFJKSDLKL;DSKL;SDLKFD;SKF;SDLKCY";
            break;
        case DISPATCHER_INVOKED:
            verbose_buffer << scheduling->to_string();
            break;
    }
    verbose_buffer << endl << endl;
}