//
// Created by huan on 3/8/17.
//

#include "Simulator.h"
#include "Priority_type.h"
#include "scheduling_algo/algo_FCFS.h"
#include "scheduling_algo/algo_RR.h"
#include <iomanip>

using namespace std;

Simulator::Simulator(const Operation opt) {
    this->algorithm = opt.ALGO;
    this->inputfile = opt.INFILE;
    this->per_thread = opt.PER_THREAD;
    this->verbose = opt.VERBOSE;

    // initialize system time and last_processId (set to INT_MAX just act as a rubbish data)
    system_time = 0;
    last_processID = INT32_MAX;
}

//TODO: add all algorithms
void Simulator::choose_scheduling_algorithm() {
    if (algorithm == Algorithm::FCFS)
        scheduler = new algo_FCFS;
    if (algorithm == Algorithm::RR)
        scheduler = new algo_RR;
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

    size_t io_brust_time;
    Thread *thread = &processes[event.processID].threads[event.threadID];
    switch (event.eventType) {
        case THREAD_ARRIVED:
            scheduler->add(thread);
            break;

        case THREAD_DISPATCH_COMPLETED:
        case PROCESS_DISPATCH_COMPLETED:
            eventTracker.push(scheduler->execute(system_time));
            break;

        case CPU_BRUST_COMPLETED:
            total_service_time += (system_time - thread->lastexecuteTime);
            has_running_or_scheduled_thread = false;
            io_brust_time = thread->next_IO_brust();
            system_time += io_brust_time;
            total_io_time += io_brust_time;
            eventTracker.push(Event(system_time, IO_BRUST_COMPLETED, *thread));
            break;

        case IO_BRUST_COMPLETED:
            scheduler->add(thread);
            break;

        case THREAD_COMPLETED:
            total_service_time += (system_time - thread->lastexecuteTime);
            has_running_or_scheduled_thread = false;
            thread->finishTime = system_time;
            break;

        case THREAD_PREEMPTED:
            total_service_time += (system_time - thread->lastexecuteTime);
            has_running_or_scheduled_thread = false;
            scheduler->add(thread);
            break;

        case DISPATCHER_INVOKED:
            // Test if it is a process switch or a thread switch
            EventType eventType;
            has_running_or_scheduled_thread = true;
            if (last_processID == event.processID) {
                system_time += threadOverhead;
                total_dispatch_time += threadOverhead;
                eventType = THREAD_DISPATCH_COMPLETED;
            } else {
                last_processID = event.processID;
                system_time += processOverhead;
                total_dispatch_time += processOverhead;
                eventType = PROCESS_DISPATCH_COMPLETED;
            }
            thread = scheduler->dispatch();
            eventTracker.push(Event(system_time, eventType, *thread));
            break;
    }
}

/**
 * Starting from current system, do:
 * 1. take the next event from event tracker
 * 2. handle that event and finish the round
 */
void Simulator::advance() {
    Event event = get_next_event();
    event_handler(event);
    if (!has_running_or_scheduled_thread && scheduler->has_ready_thread()) {
        Thread *thread = scheduler->peek_next();
        eventTracker.push(Event(event.eventTime, DISPATCHER_INVOKED, *thread));
        has_running_or_scheduled_thread = true;
    }

    total_elapsed_time = event.eventTime;
    total_idle_time = total_elapsed_time - total_service_time - total_dispatch_time;
}

void Simulator::startSim() {
    choose_scheduling_algorithm();
    loadFromFile();
    populateNewQueue();

    while (!eventTracker.empty()) advance();

    usage_analysis();

    if (per_thread) perthreadMsg();

    cout << "SIMULATION COMPLETED!" << endl << endl;

    normalMsg();
}

void Simulator::verboseMsg(const Event &event) {
    verbose_buffer << "At time " << event.eventTime << ":" << endl
                   << "    " << event << endl
                   << "    Thread " << event.threadID << " in process " << event.processID << " ["
                   << PriorityStr[event.priorityType] << "]" << endl << "    ";
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
            verbose_buffer << "Transitioned from RUNNING to READY";
            break;
        case DISPATCHER_INVOKED:
            verbose_buffer << scheduler->to_string();
            break;
    }
    verbose_buffer << endl << endl;

    cout << verbose_buffer.str();
    verbose_buffer.str(string());
}

void Simulator::normalMsg() {
    vector<size_t> counts(4, 0);
    vector<size_t> response_times(4, 0);
    vector<size_t> turnaround_times(4, 0);

    for (Process &p:processes) {
        for (Thread &t:p.threads) {
            counts[t.priorityType]++;
            response_times[t.priorityType] += t.responseTime;
            turnaround_times[t.priorityType] += t.turnaroundTime;
        }
    }

    normal_buffer << fixed << setprecision(2);
    for (int i = 0; i < 4; i++) {
        size_t count = counts[i];
        double avg_resp, avg_turn;
        if (count) {
            avg_resp = double(response_times[i]) / count;
            avg_turn = double(turnaround_times[i]) / count;
        } else avg_resp = avg_turn = 0.;

        normal_buffer << PriorityStr[i] << " THREADS:" << endl
                      << setw(25) << left << "    Total count:"
                      << setw(7) << right << counts[i] << endl
                      << setw(25) << left << "    Avg response time:"
                      << setw(7) << right << avg_resp << endl
                      << setw(25) << left << "    Avg turnaround time:"
                      << setw(7) << right << avg_turn << endl << endl;
    }

    normal_buffer << setw(25) << left << "Total elapsed time:"
                  << setw(7) << right << total_elapsed_time << endl
                  << setw(25) << left << "Total service time:"
                  << setw(7) << right << total_service_time << endl
                  << setw(25) << left << "Total I/O time:"
                  << setw(7) << right << total_io_time << endl
                  << setw(25) << left << "Total dispatch time:"
                  << setw(7) << right << total_dispatch_time << endl
                  << setw(25) << left << "Total idle time:"
                  << setw(7) << right << total_idle_time << endl << endl;
    normal_buffer << setw(25) << left << "CPU utilization:"
                  << setw(6) << right << CPU_utility * 100 << "%" << endl
                  << setw(25) << left << "CPU efficiency:"
                  << setw(6) << right << CPU_efficiency * 100 << "%" << endl << endl;

    cout << normal_buffer.str();
    normal_buffer.str(string());
}

void Simulator::perthreadMsg() {
    for (Process &p:processes) {
        per_thread_buffer << "Process " << p.processID << " [" << PriorityStr[p.priorityType] << "]:" << endl;
        for (Thread &t:p.threads) {
            per_thread_buffer << "    Thread " << t.threadID
                              << ":\tARR: " << setw(5) << left << t.arriveTime
                              << "CPU: " << setw(5) << left << t.totalCPUTime
                              << "I/O: " << setw(5) << left << t.totalIOTime
                              << "TRT: " << setw(5) << left << t.turnaroundTime
                              << "END: " << setw(5) << left << t.finishTime << endl << endl;
        }
        per_thread_buffer << endl;
    }
    cout << per_thread_buffer.str();
    per_thread_buffer.str(string());
}

void Simulator::usage_analysis() {
    for (Process &p:processes) {
        for (Thread &t:p.threads) {
            t.responseTime = t.startTime - t.arriveTime;
            t.turnaroundTime = t.finishTime - t.arriveTime;
        }
    }
    CPU_utility = 1.0 - double(total_idle_time) / total_elapsed_time;
    CPU_efficiency = double(total_service_time) / total_elapsed_time;
}