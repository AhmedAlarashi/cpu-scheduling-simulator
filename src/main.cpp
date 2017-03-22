#include "Simulator.h"

using namespace std;

int main(int argc, char **argv) {
    Simulator sim(parse_flag(argc, argv));
    sim.startSim();


    //printf ("I\033[0;31m love\033[1;36m Stack Overflow\n");

    return 0;
}
