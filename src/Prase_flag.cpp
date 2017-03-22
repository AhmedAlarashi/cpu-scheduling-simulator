//
// Created by huan on 3/7/17.
//

#include "Prase_flag.h"
#include <iostream>
#include <cstring>
#include <getopt.h>

using namespace std;

const char *short_option = "tvha:";
const struct option long_options[] = {
        {"per_thread", no_argument,       0, 't'},
        {"verbose",    no_argument,       0, 'v'},
        {"help",       no_argument,       0, 'h'},
        {"algorithm",  required_argument, 0, 'a'},
        {0, 0,                            0, 0}};

void print_usage() {
    cout << "Usage: sim [options] filename" << endl << endl;
    cout << "Options:" << endl;
    cout << "  -h, --help:" << endl << "\tPrint this help message and exit" << endl;
    cout << "  -t, --per_thread:" << endl << "\tIf set, outputs per-thread metrics " << "at the end of the simulation."
         << endl;
    cout << "  -v, --verbose:" << endl << "\tIf set, outputs all state transitions and scheduler choices." << endl;
    cout << "  -a, --algorithm <algorithm>:" << endl << "\tThe scheduler algorithm to use. Valid values are:" << endl;
    cout << "  \talgo_FCFS: first-come, first-serve (default)" << endl
         << "  \tRR: round-robin scheduler" << endl
         << "  \tPRIORITY: priority scheduler" << endl
         << "  \tNOT YET IMPLEMENTED" << endl;
}

//TODO add custom algo
Algorithm validate_algo(char *str) {
    if (!strcmp("algo_FCFS", str)) {
       // cout << "algo_FCFS" << endl;
        return FCFS;
    }
    if (!strcmp("RR", str)) {
      //  cout << "RR" << endl;
        return RR;
    }
    if (!strcmp("PRIORITY", str)) {
       // cout << "PRIORITY" << endl;
        return PRIORITY;
    }
    if (!strcmp("abcd", str)) {
      //  cout << "asdsad" << endl;
        return FCFS;
    }
    cerr << "ERROR: Unknown algorithm: " << str << endl;
    exit(EXIT_FAILURE);
}

Operation phrase_flag(int argc, char **argv) {
    Operation result;
    int choice = 0, option_index = 0;
    while ((choice = getopt_long(argc, argv, short_option, long_options, &option_index)) != -1) {
        switch (choice) {
            case 'h':
                print_usage();
                exit(EXIT_SUCCESS);
            case 't':
                result.PER_THREAD = true;
                break;
            case 'v':
                result.VERBOSE = true;
                break;
            case 'a':
                result.ALGO = validate_algo(optarg);
                break;
            case '?':
                /* getopt_long already printed an error message. */
                print_usage();
                exit(1);
            default:
                abort();
        }
    }

    if ((argc - optind) != 1) {
        cerr << "Incorrect command format" << endl;
        print_usage();
        exit(EXIT_FAILURE);
    }
    result.INFILE = argv[argc - 1];

    //cout << "File name: " << result.INFILE << endl;

    return result;
}

