#ifndef MATRIXFILLER
#define MATRIXFILLER
#include "utils/Matrix.hpp"
#include "framework/GameCell.hpp"
#include "entities/Phantom.hpp"
#include "entities/PacMan.hpp"
#include "entities/Fruit.hpp"

void spawnEnemies(int entityIndex, Engine& engine, Matrix<GameCell>& matrix, int n)
{
    for (int i = 0; i < matrix.width; i++)
    {
        for (int j = 0; j < matrix.height; j++)
        {
            Cell c = Cell(i, j);
            GameCell& gc = matrix[c];
            bool empty = gc.entities.size() == 0 && gc.getCellType() == CellType::FixedCorridor;
            if (n > 0 && empty){
                Phantom* p = new Phantom(entityIndex + n - 1, engine);
                p->setPosition(Vector2D(i, j));
                gc.entities.push_back(p);
                n--;
            }
        }
    }
}

PacMan* spawnPlayer(int entityIndex, Engine& engine, Matrix<GameCell>& matrix)
{
    for (int i = 1; i < matrix.width-1; i++)
    {
        for (int j = 1; j < matrix.height-1; j++)
        {
            Cell c = Cell(i, j);
            GameCell& gc = matrix[c];
            bool empty = gc.entities.size() == 0 && gc.getCellType() != CellType::Wall;
            if (empty){
                PacMan* p = new PacMan(entityIndex, engine);
                p->setPosition(Vector2D(i, j));
                gc.entities.push_back(p);
                return p;
            }
        }
    }
    return nullptr;
}

int spawnPoints(int entityIndex, Engine& engine, Matrix<GameCell>& matrix)
{
    int points = 0;
    for (int i = 1; i < matrix.width-1; i++)
    {
        for (int j = 1; j < matrix.height-1; j++)
        {
            Cell c = Cell(i, j);
            GameCell& gc = matrix[c];
            bool valid = gc.entities.size() == 0 && gc.getCellType() == CellType::Corridor;
            if (valid){
                Fruit* p = new Fruit(points + entityIndex, engine);
                p->setPosition(Vector2D(i, j));
                gc.entities.push_back(p);
                points++;
            }
        }
    }
    return points;
}

void fillMatrix(Engine& engine, Matrix<GameCell>& matrix, int phantoms){
    PacMan* p = spawnPlayer(0, engine, matrix);
    spawnEnemies(1, engine, matrix, phantoms);
    int fruits;
    fruits = spawnPoints(1 + phantoms, engine, matrix);
    p->setFruitsToEat(fruits);
}
#endif