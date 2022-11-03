#ifndef MATRIX
#define MATRIX

#include "Cell.hpp"
#include "framework/Direction.hpp"


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

    Matrix(int width, int height)
    {
        this->width = width;
        this->height = height;
        this->matrix = new T *[height];
        for (int i = 0; i < height; i++)
        {
            matrix[i] = new T[width];
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