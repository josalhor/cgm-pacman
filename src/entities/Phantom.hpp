#ifndef PHANTOM
#define PHANTOM

#include "framework/GameEntity.hpp"
#include "framework/graphics/Color.hpp"
#include "PacMan.hpp"
#include <GL/glut.h>

#define PHANTOM_SPEED 0.0035

#include <iostream>
using namespace std;

class Phantom: public GameEntity {
    Vector2D moveTo;
    Prisma prisma;
    public:
    Phantom(Engine& engine) : prisma(BLUE), GameEntity(engine, prisma) {
        const float height = 0.65;
        const float width = 0.65;
        size = Vector2D(width, height);
        speed = Vector2D(0.01, 0.0);
    }

    bool canMoveInto(CellType cellType){
        return cellType == CellType::Corridor || cellType == CellType::FixedCorridor;
    }

    void update(long t){
        vector<Cell> path = engine.pathTo(logicPosition.asCell(), PacMan::getTypeName());
        if (path.size() == 0) {
            return;
        }
        bool moved = false;
        bool forceOtherMove = false;
        int i = 0;
        do{
            moveTo = Vector2D(path[0].x, path[0].y);
            Vector2D direction = Vector2D(path[0].x - logicPosition.getX(), path[0].y - logicPosition.getY());
            bool xBigger = abs(direction.getX()) > abs(direction.getY());
            if (xBigger ^ forceOtherMove) {
                direction = Vector2D(direction.getX(), 0); 
            } else {
                direction = Vector2D(0, direction.getY()); 
            }
            float abs_val = abs(direction.getX()) + abs(direction.getY());
            Vector2D _speed = direction.multiply(t * PHANTOM_SPEED / abs_val);
            Vector2D nextPos = this->logicPosition.add(_speed);
            moved = setPosition(nextPos);
            forceOtherMove = !moved;
            i++;
        } while(!moved && i < 2);
    }

    void receiveCollision(GameEntity& entity) {
        if (entity.getName() == PacMan::getTypeName()) {
            Vector2D entityCenter = entity.getCenter();
            Vector2D center = getCenter();
            center = logicPosition.add(center);
            Vector2D delta = entity.getPosition().add(entityCenter).subsctract(center);
            float sqrLength = delta.getX() + delta.getY();
            if (delta.getX() < 0.5 && delta.getY() < 0.5){
                cout << "End Game" << endl;
                exit(0);
            }
        }
    }

    void draw(CoordinateMapper& mapper) {

        glColor3f(1, 0, 0);
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

        /*
        Debug position
        glColor3f(1, 0, 1);
        glBegin(GL_QUADS);
        centerPoint = getCenter();
        renderOn = moveTo.add(centerPoint);
        x = renderOn.getX();
        y = renderOn.getY();

        glVertex2f(mapper.XtoVisualFloat(x), mapper.YtoVisualFloat(y));
        glVertex2f(mapper.XtoVisualFloat(x + size.getX() / 2), mapper.YtoVisualFloat(y));
        glVertex2f(mapper.XtoVisualFloat(x + size.getX() / 2), mapper.YtoVisualFloat(y + size.getY()));
        glVertex2f(mapper.XtoVisualFloat(x), mapper.YtoVisualFloat(y + size.getY()));

        glEnd();
        */
    }

    static string getTypeName(){
        return "Phantom";
    }

    string getName() {
        return this->getTypeName();
    }
};

#endif