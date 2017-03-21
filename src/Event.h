//
// Created by huan on 3/7/17.
//

#ifndef CPU_SCHEDULING_SIMULATOR_EVENT_H
#define CPU_SCHEDULING_SIMULATOR_EVENT_H

#include <iostream>
#include <string>
#include <vector>
#include "Thread.h"

#ifndef _EVENT_EVENTTYPE_
#define _EVENT_EVENTTYPE_
enum EventType {
    THREAD_ARRIVED = 0,
    THREAD_DISPATCH_COMPLETED,
    PROCESS_DISPATCH_COMPLETED,
    CPU_BRUST_COMPLETED,
    IO_BRUST_COMPLETED,
    THREAD_COMPLETED,
    THREAD_PREEMPTED,
    DISPATCHER_INVOKED
};
#endif //_EVENT_EVENTTYPE_

class Event {
public:
    Event(size_t time, EventType type, Thread &thread) {
        eventTime = time;
        threadID = thread.threadID;
        processID = thread.processID;
        priorityType = thread.priorityType;
        eventType = type;
    }

    size_t eventTime;
    size_t threadID;
    size_t processID;
    size_t priorityType;
    EventType eventType;

    friend std::ostream &operator<<(std::ostream &os, const Event &event) {
        return os << event.eventStr[event.eventType];
    }

    bool operator<(const Event &right) const {
        return (this->eventTime < right.eventTime);
    }

    bool operator>(const Event &right) const {
        return (this->eventTime > right.eventTime);
    }

    Event &operator=(const Event &right) {
        this->eventTime = right.eventTime;
        this->threadID = right.threadID;
        this->processID = right.processID;
        this->priorityType = right.priorityType;
        this->eventType = right.eventType;
        return *this;
    }

private:
    const std::vector<std::string> eventStr =
            {"THREAD_ARRIVED", "THREAD_DISPATCH_COMPLETED",
             "PROCESS_DISPATCH_COMPLETED", "CPU_BRUST_COMPLETED",
             "IO_BRUST_COMPLETED", "THREAD_COMPLETED",
             "THREAD_PREEMPTED", "DISPATCHER_INVOKED"};
};

#endif //CPU_SCHEDULING_SIMULATOR_EVENT_H
