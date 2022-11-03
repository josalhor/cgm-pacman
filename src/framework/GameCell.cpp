#include "GameCell.hpp"
#include <GL/glut.h>

GameCell::GameCell() : type(CellType::Debug), logicPosition(Vector2D()){

}

GameCell::GameCell(CellType type, Vector2D logicPosition) : type(type), logicPosition(logicPosition){

}

void GameCell::drawScenario(CoordinateMapper& mapper)
{
    if (type == CellType::Wall || type == CellType::FixedWall){
        glColor3f(0, 0, 1);
    } else if (type == CellType::Corridor || type == CellType::FixedCorridor){
        glColor3f(1, 1, 1);

    }
    glBegin(GL_QUADS);
    int x = (int) logicPosition.getX();
    int y = (int) logicPosition.getY();

    glVertex2i(mapper.XtoVisual(x), mapper.YtoVisual(y));
    glVertex2i(mapper.XtoVisual(x + 1), mapper.YtoVisual(y));
    glVertex2i(mapper.XtoVisual(x + 1), mapper.YtoVisual(y + 1));
    glVertex2i(mapper.XtoVisual(x), mapper.YtoVisual(y + 1));

    glEnd();
}
void GameCell::draw(CoordinateMapper& mapper)
{
    for(int i = 0; i < this->entities.size(); i++){
        this->entities[i]->draw(mapper);
    }
}

void GameCell::update()
{
    for(int i = 0; i < this->entities.size(); i++){
        this->entities[i]->update();
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