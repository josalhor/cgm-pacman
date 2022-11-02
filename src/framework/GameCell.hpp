#ifndef CELL
#define CELL
/*
 * 3 Types of cell { WALL, CORRIDOR }
 * position
 * 
 * GameEntity[Fruit, PacMan]
 * draw()
 */

#include "utils/Vector2D.hpp"
class GameEntity;
#include "GameEntity.hpp"
#include "CellType.hpp"
#include <vector>
using namespace std;

class GameCell {
    private:
        CellType type;
         // Absolute position in the matrix ex: [0, 0] can only be ints in this case
        Vector2D logicPosition;
        // Vertices to paint
        vector<Vector2D> region;
        vector<GameEntity> entities;

    public:
    GameCell();
    GameCell(CellType type, Vector2D logicPosition);
    void draw();
    void update();
    void detectCollision();
};

#endif