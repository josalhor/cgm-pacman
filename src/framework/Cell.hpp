/*
 * 3 Types of cell { WALL, CORRIDOR }
 * position
 * 
 * GameEntity[Fruit, PacMan]
 * draw()
 */

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
        vec<Vector2D> region;
        

    public: Cell() {

    }

    void draw(){}
    void detectCollision(){}
}