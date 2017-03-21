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

#include <cstdlib>

const size_t SYSTEM = 0;
const size_t INTERACTIVE = 1;
const size_t NORMAL = 2;
const size_t BATCH = 3;

extern const char *PriorityStr[];

#endif //CPU_SCHEDULING_SIMULATOR_PRIORITY_H
