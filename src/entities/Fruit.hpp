#ifndef FRUIT
#define FRUIT

#include "PacMan.hpp"
#include "framework/graphics/Sphere.hpp"
#include "framework/GameEntity.hpp"
#include "framework/graphics/Color.hpp"
#include <GL/glut.h>

class Fruit: public GameEntity {
    Sphere sphere;
    public:
    Fruit(int entityIndex, Engine& engine) : sphere(engine.getCoordinateMapper(), GREEN, FOOD_TEXTURE_INDEX, -1), GameEntity(entityIndex, engine, sphere) {
        const float height = 0.33;
        const float width = 0.33;
        size = Vector2D(width, height);
    }

    void update(long t){
        
    }

    void draw() {
        sphere.draw(
            logicPosition,
            Vector3D(0.0, 0.0, 0.0),
            size.getX(),
            25,
            0
        );
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
            PacMan& p = dynamic_cast<PacMan&>(entity);
            p.eatFruit();
        }

    }
};

#endif