/*
 * 3 Types of cell { WALL, CORRIDOR }
 * position
 * 
 * GameEntity[Fruit, PacMan]
 * draw()
 */

#include "utils/Vector2D.hpp"
#include <vector>
using namespace std;

 enum CellType
{
    Wall,
    Corridor
};
class Cell {
    private:
        CellType type;
         // Absolute position in the matrix ex: [0, 0] can only be ints in this case
        Vector2D logicPosition;
        // Vertices to paint
        vector<Vector2D> region;
        

    public: Cell(CellType type, Vector2D logicPosition) : type(type), logicPosition(logicPosition) {

    }

    void draw(){}
    void detectCollision(){}
};