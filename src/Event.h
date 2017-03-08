//
// Created by huan on 3/7/17.
//

#ifndef CPU_SCHEDULING_SIMULATOR_EVENT_H
#define CPU_SCHEDULING_SIMULATOR_EVENT_H


enum EventType {
    THREAD_ARRIVED,
    THREAD_DISPATCH_COMPLETED,
    PROCESS_DISPATCH_COMPLETED,
    CPU_BRUST_COMPLETED,
    IO_BRUST_COMPLETED,
    THREAD_COMPLETED,
    THREAD_PREEMPTED,
    DISPATCHER_INVOKED,
    NONE
};

class Event {
public:
    // default constructor
    Event();

    EventType event;
private:
};


#endif //CPU_SCHEDULING_SIMULATOR_EVENT_H
