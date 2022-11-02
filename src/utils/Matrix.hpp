#ifndef MATRIX
#define MATRIX

enum Direction
{
    Up = 0,
    Down = 1,
    Left = 2,
    Right = 3
};


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

template <typename T>
class Matrix
{
public:
    T **matrix;
    int width;
    int height;

    Matrix(int width, int height, T def)
    {
        this->width = width;
        this->height = height;
        this->matrix = new T *[height];
        for (int i = 0; i < height; i++)
        {
            matrix[i] = new T[width];
            for (int j = 0; j < width; j++)
            {
                matrix[i][j] = def;
            }
        }
    }

    ~Matrix()
    {
        for (int i = 0; i < height; i++)
        {
            delete matrix[i];
        }
        delete matrix;
    }

    bool validInBounds(Cell cell)
    {
        return cell.validInBounds(width, height);
    }

    bool isPerimeter(Cell cell)
    {
        return cell.x == 0 || cell.x == width - 1 || cell.y == 0 || cell.y == height - 1;
    }

    T &operator[](Cell cell)
    {
        return matrix[cell.y][cell.x];
    }
};

#endif