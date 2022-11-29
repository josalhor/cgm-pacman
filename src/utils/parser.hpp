#ifndef ARG_PARSER
#define ARG_PARSER
#include <iostream>
#include <getopt.h>

#include "./utils.hpp"

using namespace std;

class EngineSetup {
    public:
        bool verbose;
        unsigned int phantoms;
        unsigned int rows;
        unsigned int cols;

        EngineSetup() {
            this->verbose = false;
            this->phantoms = 4;
            this->rows = 0;
            this->cols = 0;
        }
};

class ArgParser {
    private:
        int argc;
        char **argv;
        EngineSetup setup;

        void invalid();
        void preValidate();
        void usage();
        void validate();
    public:
        ArgParser(int argc, char **argv);
        EngineSetup parse();
};

#endif
