#ifndef FRUIT
#define FRUIT

#include "framework/GameEntity.hpp"
#include "framework/graphics/Color.hpp"
#include "PacMan.hpp"
#include <GL/glut.h>

class Fruit: public GameEntity {
    Prisma prisma;
    public:
    Fruit(Engine& engine) : prisma(engine.getCoordinateMapper(), GREEN), GameEntity(engine, prisma) {
        const float height = 0.33;
        const float width = 0.33;
        size = Vector2D(width, height);
    }

    void update(long t){
        
    }

    void draw() {

        glColor3f(0, 0.6, 0.6);
        glBegin(GL_QUADS);
        Vector2D centerPoint = getCenter();
        Vector2D renderOn = logicPosition.add(centerPoint);
        float x = renderOn.getX();
        float y = renderOn.getY();

        glVertex3f(mapper.XtoVisualFloat(x), mapper.YtoVisualFloat(y), 0);
        glVertex3f(mapper.XtoVisualFloat(x + size.getX()), mapper.YtoVisualFloat(y), 0);
        glVertex3f(mapper.XtoVisualFloat(x + size.getX()), mapper.YtoVisualFloat(y + size.getY()), 0);
        glVertex3f(mapper.XtoVisualFloat(x), mapper.YtoVisualFloat(y + size.getY()), 0);

        glEnd();
    }

    static string getTypeName(){
        return "Fruit";
    }

    string getName() {
        return this->getTypeName();
    }

    void receiveCollision(GameEntity& entity) {
        if (entity.getName() == PacMan::getTypeName()){
            destroy();
        }
    }
};

#endif