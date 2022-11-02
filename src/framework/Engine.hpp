#ifndef ENGINE
#define ENGINE

#include "utils/Matrix.hpp"
class GameCell;
#include "GameCell.hpp"
class GameEntity;
#include "GameEntity.hpp"


class Engine {
    private:
        Matrix<GameCell>* matrix = nullptr;
    public:
        Engine();
        void setup(int columns, int rows);
        void run();
        void display();
        void destroy(GameEntity entity);
};

#endif