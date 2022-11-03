#ifndef PHANTOM
#define PHANTOM

#include "framework/GameEntity.hpp"
#include <GL/glut.h>

class Phantom: public GameEntity {
    using GameEntity::GameEntity;

    void update(){
        this->logicPosition = Vector2D(this->logicPosition.getX() + 0.01, this->logicPosition.getY());
    }

    void draw(CoordinateMapper& mapper) {

        glColor3f(1, 0, 0);
        glBegin(GL_QUADS);
        float x = logicPosition.getX();
        float y = logicPosition.getY();

        glVertex2f(mapper.XtoVisualFloat(x), mapper.YtoVisualFloat(y));
        glVertex2f(mapper.XtoVisualFloat(x + 1), mapper.YtoVisualFloat(y));
        glVertex2f(mapper.XtoVisualFloat(x + 1), mapper.YtoVisualFloat(y + 1));
        glVertex2f(mapper.XtoVisualFloat(x), mapper.YtoVisualFloat(y + 1));

        glEnd();
    }
};

#endif