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
        Vector3D normalMovementDirection;
        Direction currentDirection = Direction::None;
        Direction nextDirection = Direction::None;
        int leftToEat = 0;
    public:
    PacMan(int entityIndex, Engine& engine) : sphere(engine.getCoordinateMapper(), WHITE, PACMAN_TEXTURE_INDEX, entityIndex), GameEntity(entityIndex, engine, sphere) {
        const float height = 0.65;
        const float width = 0.65;
        normalMovementDirection = Vector3D(0.0, 0.0, 0.0);
        size = Vector2D(width, height);
        speed = Vector2D(0, 0);
    }

    bool canMoveInto(CellType cellType){
        return cellType == CellType::Corridor;
    }

    void update(long t){
        bool currentMov = false;
        bool moved = false;
        int numTries = 2;
        Direction tryDirection = nextDirection;
        if (nextDirection == Direction::None) {
            tryDirection = currentDirection;
            currentMov = true;
        }
        Vector2D trySpeed;
        Vector3D trynormalMovementDirection;
        while(numTries > 0 && !moved) {
            if (tryDirection == Direction::Up) {
                trySpeed = Vector2D(0.0, PACMAN_BASE_SPEED);
                trynormalMovementDirection = Vector3D(0.0, 0.0, -1.0);
            } else if (tryDirection == Direction::Right)
            {
                trySpeed = Vector2D(PACMAN_BASE_SPEED, 0.0);
                trynormalMovementDirection = Vector3D(1.0, 0.0, 0.0);
            } else if (tryDirection == Direction::Down)
            {
                trySpeed = Vector2D(0.0, -PACMAN_BASE_SPEED);
                trynormalMovementDirection = Vector3D(0.0, 0.0, 1.0);
            } else if (tryDirection == Direction::Left)
            {
                trySpeed = Vector2D(-PACMAN_BASE_SPEED, 0.0);
                trynormalMovementDirection = Vector3D(-1.0, 0.0, 0.0);
            }
            Vector2D _speed = trySpeed.multiply(t);
            Vector2D nextPos = this->logicPosition.add(_speed);
            Vector2D _aheadSpeed = trySpeed.multiply(0.35 / PACMAN_BASE_SPEED);
            Vector2D nextPosTry = this->logicPosition.add(_aheadSpeed);
            moved = canSetPosition(nextPosTry);
            if (!moved) {
                tryDirection = currentDirection;
                currentMov = true;
            } else {
                setPosition(nextPos);
            }
            numTries--;
        }
        currentDirection = tryDirection;
        speed = trySpeed;
        normalMovementDirection = trynormalMovementDirection;
    }

    void receiveKeyboard(Direction d) {
        if (currentDirection == Direction::None) {
            currentDirection = d;
        } else {
            nextDirection = d;
        }
    }

    void draw() {
        sphere.draw(
            logicPosition,
            normalMovementDirection,
            size.getX() / 2,
            20,
            15.0
        );
    }

    static string getTypeName(){
        return "PacMan";
    }
    
    string getName() {
        return this->getTypeName();
    }

    void setFruitsToEat(int fruits) {
        leftToEat = fruits;
    }

    void eatFruit(){
        leftToEat--;
        if (leftToEat <= 0) {
            engine.setEngineState(EngineState::PostGame);
        }
    }
};
#endif