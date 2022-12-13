#ifndef PACMAN
#define PACMAN

#include "framework/GameEntity.hpp"
#include "framework/graphics/Sphere.hpp"
#include "framework/graphics/Color.hpp"
#include "framework/TextureLoader.hpp"
#include <GL/glut.h>

#define PACMAN_BASE_SPEED 0.004

class PacMan: public GameEntity {
    private:
        Sphere sphere;
    public:
    PacMan(int entityIndex, Engine& engine) : sphere(engine.getCoordinateMapper(), WHITE, PACMAN_TEXTURE_INDEX), GameEntity(entityIndex, engine, sphere) {
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

    void draw() {
        sphere.draw(
            logicPosition,
            size.getX() / 2,
            20,
            entityIndex
        );
    }

    static string getTypeName(){
        return "PacMan";
    }
    
    string getName() {
        return this->getTypeName();
    }
};
#endif