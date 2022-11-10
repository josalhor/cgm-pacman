#ifndef ARG_PARSER
#define ARG_PARSER
#include <iostream>
#include <getopt.h>

#include "./utils.hpp"
#include "../enums/graphics_mode.hpp"

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

        GraphicsMode mode = GraphicsMode::SIMPLE;

        void invalid();
        void preValidate();
        void usage();
        void validate();
    public:
        ArgParser(int argc, char **argv);
        void parse();
};

#endif
