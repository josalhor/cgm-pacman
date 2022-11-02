#ifndef ENGINE
#define ENGINE

#include "utils/Matrix.hpp"

class Engine {
    private:
        Matrix matrix;
    public:
        void display();
        void setup();
        void run();
};

#endif