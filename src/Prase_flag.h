//
// Created by huan on 3/7/17.
//

#ifndef CPU_SCHEDULING_SIMULATOR_PRASE_FLAG_H
#define CPU_SCHEDULING_SIMULATOR_PRASE_FLAG_H

#include <FreeImage.h>

enum Algorithm {
    FCFS,
    RR,
    PRIORITY,
    CUSTOM
};

struct Operation {
    bool PER_THREAD;
    bool VERBOSE;
    Algorithm ALGO;
    char *INFILE;

    Operation() {
        PER_THREAD = false;
        VERBOSE = false;
        ALGO = FCFS;
        INFILE = NULL;
    }
};

Operation phrase_flag(int argc, char **argv);

#endif //CPU_SCHEDULING_SIMULATOR_PRASE_FLAG_H
