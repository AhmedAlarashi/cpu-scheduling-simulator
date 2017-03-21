//
// Created by huan on 3/7/17.
//

#ifndef CPU_SCHEDULING_SIMULATOR_BRUST_H
#define CPU_SCHEDULING_SIMULATOR_BRUST_H

#include <cstddef>

class Brust {
public:
    Brust(){
        cpu = 0;
        io = 0;
    }

    size_t cpu;
    size_t io;
};

#endif //CPU_SCHEDULING_SIMULATOR_BRUST_H
