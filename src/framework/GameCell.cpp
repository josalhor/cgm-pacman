#include "GameCell.hpp"
#include "framework/graphics/Prisma.hpp"
#include "framework/graphics/Color.hpp"
#include <GL/glut.h>

GameCell::GameCell() : type(CellType::Debug), logicPosition(Vector2D()){

}

GameCell::GameCell(CoordinateMapper* mapper, CellType type, Vector2D logicPosition) : mapper(mapper), type(type), logicPosition(logicPosition){

}

void GameCell::drawScenario()
{
    Color color;
    if (type == CellType::Wall || type == CellType::FixedWall){
        color = BLUE;
    } else if (type == CellType::Corridor || type == CellType::FixedCorridor){
        color = WHITE;

    }
    int height = 0;
    if (type == Wall){
        height = 50;
    }

    Prisma(*mapper, color).draw(
        logicPosition,
        Vector2D(1, 1),
        height,
        0
    );
    // glBegin(GL_QUADS);
    // glVertex3i(mapper.XtoVisual(x), mapper.YtoVisual(y), height);
    // glVertex3i(mapper.XtoVisual(x + 1), mapper.YtoVisual(y), height);
    // glVertex3i(mapper.XtoVisual(x + 1), mapper.YtoVisual(y + 1), height);
    // glVertex3i(mapper.XtoVisual(x), mapper.YtoVisual(y + 1), height);

    // glEnd();
}
void GameCell::draw()
{
    for(int i = 0; i < this->entities.size(); i++){
        this->entities[i]->draw();
    }
}

void GameCell::update(long t)
{
    for(int i = 0; i < this->entities.size(); i++){
        this->entities[i]->update(t);
    }
}

void GameCell::receiveKeyboard(Direction d)
{
    for(int i = 0; i < this->entities.size(); i++){
        this->entities[i]->receiveKeyboard(d);
    }
}

void GameCell::detectCollision()
{
    for(int i = 0; i < this->entities.size(); i++){
        for(int j = 0; j < this->entities.size(); j++){
            if (i == j){
                continue;
            }

            this->entities[j]->receiveCollision(*(this->entities[i]));
        }
    }
}

bool GameCell::containsEntity(string name){
    for(int i = 0; i < this->entities.size(); i++){
        if(this->entities[i]->getName() == name) {
            return true;
        }
    }
    return false;
}