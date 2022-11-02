#include "Cell.hpp"

Cell::Cell(CellType type, Vector2D logicPosition) : type(type), logicPosition(logicPosition){

}

void Cell::draw()
{
    if (type == CellType::Wall){
        // todo
    } else if (type == CellType::Corridor){

    }

    for(int i = 0; i < this->entities.size(); i++){
        this->entities[i].draw();
    }
}

void Cell::update()
{
    for(int i = 0; i < this->entities.size(); i++){
        this->entities[i].update();
    }
}

void Cell::detectCollision()
{
    for(int i = 0; i < this->entities.size(); i++){
        for(int j = 0; j < this->entities.size(); j++){
            if (i == j){
                continue;
            }

            this->entities[j].receiveCollision(this->entities[i]);
        }
    }
}