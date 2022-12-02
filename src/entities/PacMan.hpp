#ifndef PACMAN
#define PACMAN

#include "framework/GameEntity.hpp"
#include "framework/graphics/Prisma.hpp"
#include "framework/graphics/Color.hpp"
#include <GL/glut.h>

#define PACMAN_BASE_SPEED 0.004

class PacMan: public GameEntity {
    private:
        Prisma prisma;
    public:
    PacMan(Engine& engine) : prisma(YELLOW), GameEntity(engine, prisma) {
        const float height = 0.65;
        const float width = 0.65;
        size = Vector2D(width, height);
        speed = Vector2D(0, 0);
    }

    bool canMoveInto(CellType cellType){
        return cellType == CellType::Corridor;
    }

    void update(long t){
        Vector2D _speed = speed.multiply(t);
        Vector2D nextPos = this->logicPosition.add(_speed);
        setPosition(nextPos);
    }

    void receiveKeyboard(Direction d) {
        if (d == Direction::Up) {
            speed = Vector2D(0.0, PACMAN_BASE_SPEED);
        } else if (d == Direction::Right)
        {
            speed = Vector2D(PACMAN_BASE_SPEED, 0.0);
        } else if (d == Direction::Down)
        {
            speed = Vector2D(0.0, -PACMAN_BASE_SPEED);
        } else if (d == Direction::Left)
        {
            speed = Vector2D(-PACMAN_BASE_SPEED, 0.0);
        }
    }

    void draw(CoordinateMapper& mapper) {
        Vector2D centerPoint = getCenter();
        Vector2D renderOn = logicPosition.add(centerPoint);
        float x = renderOn.getX();
        float y = renderOn.getY();

        prisma.draw(
            mapper.XtoVisualFloat(x),
            mapper.YtoVisualFloat(y),
            mapper.XtoVisualFloat(x + size.getX()),
            mapper.YtoVisualFloat(y + size.getY()),
            mapper.XtoVisualFloat(x + size.getX()) - mapper.XtoVisualFloat(x)
        );
        // glColor3f(0, 1, 0);
        // glBegin(GL_QUADS);
        // glVertex3f(mapper.XtoVisualFloat(x), mapper.YtoVisualFloat(y), 0);
        // glVertex3f(mapper.XtoVisualFloat(x + size.getX()), mapper.YtoVisualFloat(y), 0);
        // glVertex3f(mapper.XtoVisualFloat(x + size.getX()), mapper.YtoVisualFloat(y + size.getY()), 0);
        // glVertex3f(mapper.XtoVisualFloat(x), mapper.YtoVisualFloat(y + size.getY()), 0);

        // glEnd();
    }

    static string getTypeName(){
        return "PacMan";
    }
    
    string getName() {
        return this->getTypeName();
    }
};
#endif