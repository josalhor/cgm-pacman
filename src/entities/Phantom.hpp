#ifndef PHANTOM
#define PHANTOM

#include "framework/GameEntity.hpp"
#include <GL/glut.h>

class Phantom: public GameEntity {
    public:
    Phantom(Engine& engine) : GameEntity(engine) {
        const float height = 0.25;
        const float width = 0.65;
        size = Vector2D(width, height);
        speed = Vector2D(0.01, 0.0);
    }

    bool canMoveInto(CellType cellType){
        return cellType == CellType::Corridor || cellType == CellType::FixedCorridor;
    }

    void update(long t){
        Vector2D _speed = speed.multiply(t);
        Vector2D nextPos = this->logicPosition.add(_speed);
        setPosition(nextPos);
    }

    void draw(CoordinateMapper& mapper) {

        glColor3f(1, 0, 0);
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
        return "Phantom";
    }

    string getName() {
        return this->getTypeName();
    }
};

#endif