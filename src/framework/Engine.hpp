#ifndef ENGINE
#define ENGINE

#include "utils/Matrix.hpp"
class GameEntity;
#include "GameEntity.hpp"


class Engine {
    private:
        Matrix matrix;
    public:
        Engine();
        void setup();
        void run();
        void display();
        void destroy(GameEntity entity);
};

#endif