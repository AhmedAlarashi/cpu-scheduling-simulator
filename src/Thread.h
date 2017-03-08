//
// Created by huan on 3/7/17.
//

#ifndef CPU_SCHEDULING_SIMULATOR_THREAD_H
#define CPU_SCHEDULING_SIMULATOR_THREAD_H

#include <vector>
#include "Brust.h"

class Thread {
public:
    Thread();

    std::vector<Brust> brusts;
};


#endif //CPU_SCHEDULING_SIMULATOR_THREAD_H
