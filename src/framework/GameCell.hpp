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
#include "CoordinateMapper.hpp"
#include "CellType.hpp"
#include <vector>
using namespace std;

class GameCell {
    private:
        CellType type;
         // Absolute position in the matrix ex: [0, 0] can only be ints in this case
        Vector2D logicPosition;
        // Vertices to paint
        // vector<Vector2D> region;
    public:
        vector<GameEntity*> entities;
    GameCell();
    GameCell(CellType type, Vector2D logicPosition);
    CellType getCellType() {
        return type;
    }
    void receiveKeyboard(unsigned char c);
    void drawScenario(CoordinateMapper& mapper);
    void draw(CoordinateMapper& mapper);
    void update();
    void detectCollision();
};

#endif