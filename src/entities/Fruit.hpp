#ifndef FRUIT
#define FRUIT

#include "framework/GameEntity.hpp"
#include <GL/glut.h>

class Fruit: public GameEntity {
    public:
    Fruit(Engine& engine) : GameEntity(engine) {
        const float height = 0.2;
        const float width = 0.2;
        size = Vector2D(width, height);
    }

    void update(){
        
    }

    void draw(CoordinateMapper& mapper) {

        glColor3f(0, 0.3, 0.3);
        glBegin(GL_QUADS);
        Vector2D centerPoint = center(logicPosition);
        Vector2D renderOn = logicPosition.add(centerPoint);
        float x = renderOn.getX();
        float y = renderOn.getY();

        glVertex2f(mapper.XtoVisualFloat(x), mapper.YtoVisualFloat(y));
        glVertex2f(mapper.XtoVisualFloat(x + size.getX()), mapper.YtoVisualFloat(y));
        glVertex2f(mapper.XtoVisualFloat(x + size.getX()), mapper.YtoVisualFloat(y + size.getY()));
        glVertex2f(mapper.XtoVisualFloat(x), mapper.YtoVisualFloat(y + size.getY()));

        glEnd();
    }
};

#endif