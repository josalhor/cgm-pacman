#ifndef PHANTOM
#define PHANTOM

#include "framework/GameEntity.hpp"
#include "framework/graphics/Color.hpp"
#include "framework/graphics/Sphere.hpp"
#include "PacMan.hpp"
#include <GL/glut.h>

#define PHANTOM_SPEED 0.0035

#include <iostream>
using namespace std;

class Phantom: public GameEntity {
    Vector2D moveTo;
    Vector3D normalMovementDirection;
    Sphere sphere;
    public:
    Phantom(int entityIndex, Engine& engine) : sphere(engine.getCoordinateMapper(), RED, ENEMY_TEXTURE_INDEX, entityIndex), GameEntity(entityIndex, engine, sphere) {
        const float height = 0.65;
        const float width = 0.65;
        normalMovementDirection = Vector3D(0.0, 0.0, 0.0);
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
            Vector3D direction3d = to3dSpace(_speed);
            //cout << direction3d.getX() << ", " << direction3d.getY() << ", " << direction3d.getZ() << "\n"; 
            //cout << _speed.getX() << ", " << _speed.getY() << "\n";
            normalMovementDirection = Vector3D( 
                direction3d.getX() != 0 ? direction3d.getX() / abs(direction3d.getX()) : 0.0, 
                direction3d.getY() != 0 ? direction3d.getY() / abs(direction3d.getY()) : 0.0, 
                direction3d.getZ() != 0 ? direction3d.getZ() / abs(direction3d.getZ()) : 0.0
            );
            //cout << normalMovementDirection.getX() << ", " << normalMovementDirection.getY() << ", " << normalMovementDirection.getZ() << "\n"; 
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
                engine.endGame(false);
            }
        }
    }

    void draw() {
        sphere.draw(
            logicPosition,
            normalMovementDirection,
            size.getX() / 2,
            20,
            8.0
        );
    }

    static string getTypeName(){
        return "Phantom";
    }

    string getName() {
        return this->getTypeName();
    }
};

#endif