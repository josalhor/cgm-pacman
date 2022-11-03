#ifndef PACMAN
#define PACMAN

#include "framework/GameEntity.hpp"
#include <GL/glut.h>

class PacMan: public GameEntity {
    public:
    PacMan(Engine& engine) : GameEntity(engine) {
        const float height = 0.65;
        const float width = 0.65;
        size = Vector2D(width, height);
    }

    void update(){
        this->logicPosition = Vector2D(this->logicPosition.getX() + 0.01, this->logicPosition.getY());
    }

    void draw(CoordinateMapper& mapper) {

        glColor3f(0, 1, 0);
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

    static string getTypeName(){
        return "PacMan";
    }
    
    string getName() {
        return this->getTypeName();
    }
};
#endif