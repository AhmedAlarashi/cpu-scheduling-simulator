#include "Simulator.h"

using namespace std;

int main(int argc, char **argv) {
    Simulator sim(phrase_flag(argc, argv));
    sim.loadFromFile();
    sim.startSim();

    return 0;
}
