#include "GameEntity.hpp"

GameEntity::GameEntity(Engine& engine) : engine(engine) {

}

void GameEntity::update(){
    // empty by default
}

void GameEntity::destroy() {
    engine.destroy(this);
}

void GameEntity::draw(CoordinateMapper& mapper){
    // empty by default
}

void GameEntity::receiveCollision(GameEntity& entity) {
    // empty by default
}

void GameEntity::receiveKeyboard(unsigned char c) {
    // empty by default
}

Vector2D GameEntity::center(Vector2D point) {
    const float centerY = 0.5 - this->size.getY() / 2.0;
    const float centerX = 0.5 - this->size.getX() / 2.0;
    return Vector2D(centerX, centerY);
}

string GameEntity::getName(){
    return "XXX";
}