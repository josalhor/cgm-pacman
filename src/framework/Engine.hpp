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

enum EngineState {
    PreGame,
    InGame,
    PostGame
};

class Engine {
    private:
        EngineSetup* settings = nullptr;
        CoordinateMapper* mapper = nullptr;
        Matrix<GameCell>* matrix = nullptr;
        PathFinder* pathFinder = nullptr;
        long last_t = 0.0;
        /*--- Global variables that determine the viewpoint location ---*/
        int anglealpha = 78;
        int anglebeta = 51;
        float smooth_alpha = anglealpha;
        float smooth_beta = anglebeta;
        EngineState state = EngineState::PreGame;
        /*
        TODO: memory cleanup
        */
       void PositionObserver(int radi);
       void displayScenario();
       void displayInGame();
       void displayPreGame();
       void displayPostGame();
    public:
        Engine();
        CellType getCellType(Cell cell);
        void setup(EngineSetup* setup);
        void run();
        void display();
        void update(long t);
        void destroy(GameEntity* entity);
        void destroyAll();
        void idle();
        void keyboard(unsigned char c);
        void specialFunc(int c);
        void keyboard(Direction d);
        void setEngineState(EngineState state);
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