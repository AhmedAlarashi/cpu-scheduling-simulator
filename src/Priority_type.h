//
// Created by huan on 3/7/17.
//

#ifndef CPU_SCHEDULING_SIMULATOR_PRIORITY_H
#define CPU_SCHEDULING_SIMULATOR_PRIORITY_H

enum Priority {
    SYSTEM = 0,
    INTERACTIVE,
    NORMAL,
    BATCH,
};

const char *PriorityStr[] = {"[SYSTEM]", "[INTERACTIVE]", "[NORMAL]", "[BATCH]"};

#endif //CPU_SCHEDULING_SIMULATOR_PRIORITY_H
