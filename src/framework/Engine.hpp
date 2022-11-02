#ifndef ENGINE
#define ENGINE

#include "utils/Matrix.hpp"
#include "GameCell.hpp"
class GameEntity;
#include "GameEntity.hpp"


class Engine {
    private:
        Matrix<Cell>* matrix = nullptr;
    public:
        Engine();
        void setup();
        void run();
        void display();
        void destroy(GameEntity entity);
};

#endif