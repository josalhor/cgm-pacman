#ifndef CELL
#define CELL

#include "framework/Direction.hpp"

class Cell
{
public:
    int x;
    int y;
    Cell(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    bool operator==(const Cell &other) const
    {
        return (x == other.x && y == other.y);
    }

    Cell move(Direction d)
    {
        switch (d)
        {
        case Direction::Up:
            return Cell(x, y + 1);
        case Direction::Down:
            return Cell(x, y - 1);
        case Direction::Left:
            return Cell(x - 1, y);
        case Direction::Right:
            return Cell(x + 1, y);
        default:
            return *this;
        }
    }

    bool validInBounds(int width, int height)
    {
        return 0 <= x && x < width && 0 <= y && y < height;
    }
};

#endif