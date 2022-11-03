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

        const float height = 0.25;
        const float width = 0.65;

        const float centerY = 0.5 - height / 2.0;
        const float centerX = 0.5 - width / 2.0;

        glVertex2f(mapper.XtoVisualFloat(x + centerX), mapper.YtoVisualFloat(y + centerY));
        glVertex2f(mapper.XtoVisualFloat(x + width + centerX), mapper.YtoVisualFloat(y + centerY));
        glVertex2f(mapper.XtoVisualFloat(x + width + centerX), mapper.YtoVisualFloat(y + height + centerY));
        glVertex2f(mapper.XtoVisualFloat(x + centerX), mapper.YtoVisualFloat(y + height + centerY));

        glEnd();
    }
};

#endif