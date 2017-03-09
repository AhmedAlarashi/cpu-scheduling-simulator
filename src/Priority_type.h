//
// Created by huan on 3/7/17.
//

#ifndef CPU_SCHEDULING_SIMULATOR_PRIORITY_H
#define CPU_SCHEDULING_SIMULATOR_PRIORITY_H

//enum Priority {
//    SYSTEM = 0,
//    INTERACTIVE,
//    NORMAL,
//    BATCH,
//};

#define SYSTEM 0
#define INTERACTIVE 1
#define NORMAL 2
#define BATCH 3

//const char *PriorityStr[]; = {"[SYSTEM]", "[INTERACTIVE]", "[NORMAL]", "[BATCH]"};
extern const char *PriorityStr[];

#endif //CPU_SCHEDULING_SIMULATOR_PRIORITY_H
