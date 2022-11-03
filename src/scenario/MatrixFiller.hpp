#ifndef MATRIXFILLER
#define MATRIXFILLER
#include "utils/Matrix.hpp"
#include "framework/GameCell.hpp"
#include "entities/Phantom.hpp"

void fillMatrix(Engine& engine, Matrix<GameCell>& matrix){
    int phantoms = 4;

    for (int i = 0; i < matrix.width; i++)
    {
        for (int j = 0; j < matrix.height; j++)
        {
            Cell c = Cell(i, j);
            GameCell gc = matrix[c];
            bool empty = gc.entities.size() == 0 && gc.getCellType() == CellType::Wall;
            if (phantoms > 0 && empty){
                Phantom p = Phantom(engine);
                gc.entities.push_back(p);
                phantoms--;
            }
        }
    }

}
#endif