#ifndef PHANTOM
#define PHANTOM

#include "framework/GameEntity.hpp"
#include <GL/glut.h>

class Phantom: public GameEntity {
    using GameEntity::GameEntity;

    void update(){
        
    }

    void draw(CoordinateMapper& mapper) {

        glColor3f(1, 0, 0);
        glBegin(GL_QUADS);
        float x = logicPosition.getX();
        float y = logicPosition.getY();

        glVertex2i(mapper.XtoVisual(x), mapper.YtoVisual(y));
        glVertex2i(mapper.XtoVisual(x + 1), mapper.YtoVisual(y));
        glVertex2i(mapper.XtoVisual(x + 1), mapper.YtoVisual(y + 1));
        glVertex2i(mapper.XtoVisual(x), mapper.YtoVisual(y + 1));

        glEnd();
    }
};

#endif