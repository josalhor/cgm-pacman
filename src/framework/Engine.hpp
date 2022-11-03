#ifndef ENGINE
#define ENGINE

#include "utils/Matrix.hpp"
class GameCell;
#include "GameCell.hpp"
class GameEntity;
#include "GameEntity.hpp"
#include "CoordinateMapper.hpp"


class Engine {
    private:
        CoordinateMapper* mapper = nullptr;
        Matrix<GameCell>* matrix = nullptr;
        /*
        TODO: memory cleanup
        */
    public:
        Engine();
        void setup(int columns, int rows);
        void run();
        void display();
        void update();
        void destroy(GameEntity* entity);
};

#endif