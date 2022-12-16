#ifndef ENGINE
#define ENGINE

#include "utils/Matrix.hpp"
class GameCell;
#include "GameCell.hpp"
class GameEntity;
#include "GameEntity.hpp"
#include "CellType.hpp"
#include "CoordinateMapper.hpp"
class PathFinder;
#include "PathFinder.hpp"
#include "utils/parser.hpp"

class Engine {
    private:
        EngineSetup* settings = nullptr;
        CoordinateMapper* mapper = nullptr;
        Matrix<GameCell>* matrix = nullptr;
        PathFinder* pathFinder = nullptr;
        long last_t = 0.0;
        /*
        TODO: memory cleanup
        */
    public:
        Engine();
        CellType getCellType(Cell cell);
        void setup(EngineSetup* setup);
        void run();
        void display();
        void update(long t);
        void destroy(GameEntity* entity);
        void idle();
        void keyboard(unsigned char c);
        void specialFunc(int c);
        void keyboard(Direction d);
        CoordinateMapper& getCoordinateMapper() {
            if (mapper == nullptr) {
                printf("Empty mapper\n");
                exit(-1);
            }
            return *mapper;
        }
        vector<Cell> pathTo(Cell base, string name);
};

#endif