#ifndef ENGINE
#define ENGINE

#include "utils/Matrix.hpp"
class GameEntity;
#include "GameEntity.hpp"


class Engine {
    private:
        Matrix matrix;
    public:
        void display();
        void setup();
        void run();
        void destroy(GameEntity entity);
};

#endif