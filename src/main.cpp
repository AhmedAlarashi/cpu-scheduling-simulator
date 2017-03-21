#include "Simulator.h"

using namespace std;

int main(int argc, char **argv) {
//    srand(time(NULL));
//    set<foo> test;
//    for (int i=0;i<10;i++){
//        test.insert(foo(rand()%1000));
//    }
//
//    set<foo>::iterator it;
//    while ((it = test.begin()) != test.end()){
//        cout << (*it).key <<endl;
//        test.erase(it);
//    }
    Simulator sim(phrase_flag(argc, argv));
    sim.startSim();

    return 0;
}
