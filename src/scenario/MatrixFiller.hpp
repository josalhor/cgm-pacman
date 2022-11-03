#ifndef MATRIXFILLER
#define MATRIXFILLER
#include "utils/Matrix.hpp"
#include "framework/GameCell.hpp"
#include "entities/Phantom.hpp"
#include "entities/PacMan.hpp"
#include "entities/Fruit.hpp"

void fillMatrix(Engine& engine, Matrix<GameCell>& matrix){
    int phantoms = 4;

    for (int i = 0; i < matrix.width; i++)
    {
        for (int j = 0; j < matrix.height; j++)
        {
            Cell c = Cell(i, j);
            GameCell& gc = matrix[c];
            bool empty = gc.entities.size() == 0 && gc.getCellType() == CellType::FixedCorridor;
            if (phantoms > 0 && empty){
                Phantom* p = new Phantom(engine);
                p->setPosition(Vector2D(i, j));
                gc.entities.push_back(p);
                phantoms--;
            }
        }
    }

    int pacman = 1;
    for (int i = 0; i < matrix.width; i++)
    {
        for (int j = 0; j < matrix.height; j++)
        {
            Cell c = Cell(i, j);
            GameCell& gc = matrix[c];
            bool empty = gc.entities.size() == 0 && gc.getCellType() != CellType::Wall;
            if (pacman > 0 && empty){
                PacMan* p = new PacMan(engine);
                p->setPosition(Vector2D(i, j));
                gc.entities.push_back(p);
                pacman--;
            }
        }
    }

    for (int i = 0; i < matrix.width; i++)
    {
        for (int j = 0; j < matrix.height; j++)
        {
            Cell c = Cell(i, j);
            GameCell& gc = matrix[c];
            bool empty = gc.entities.size() == 0 && gc.getCellType() == CellType::Corridor;
            if (empty){
                Fruit* p = new Fruit(engine);
                p->setPosition(Vector2D(i, j));
                gc.entities.push_back(p);
            }
        }
    }

}
#endif