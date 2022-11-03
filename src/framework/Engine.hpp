#ifndef ENGINE
#define ENGINE

#include "utils/Matrix.hpp"
class GameCell;
#include "GameCell.hpp"
class GameEntity;
#include "GameEntity.hpp"
#include "CellType.hpp"
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
        CellType getCellType(Cell cell);
        void setup(int columns, int rows);
        void run();
        void display();
        void update();
        void destroy(GameEntity* entity);
        void idle();
        void keyboard(unsigned char c);
        void specialFunc(int c);
        void keyboard(Direction d);
};

#endif