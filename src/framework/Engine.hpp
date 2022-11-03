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
        long last_t = 0.0;
        /*
        TODO: memory cleanup
        */
    public:
        Engine();
        CellType getCellType(Cell cell);
        void setup(int columns, int rows);
        void run();
        void display();
        void update(long t);
        void destroy(GameEntity* entity);
        void idle();
        void keyboard(unsigned char c);
        void specialFunc(int c);
        void keyboard(Direction d);
};

#endif