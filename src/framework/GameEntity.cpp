#include "GameEntity.hpp"

GameEntity::GameEntity(int entityIndex, Engine& engine, Shape& shape) : entityIndex(entityIndex), engine(engine), shape(shape), mapper(engine.getCoordinateMapper()) {

}

void GameEntity::update(long t){
    // empty by default
}

void GameEntity::destroy() {
    engine.destroy(this);
}

void GameEntity::draw(){
    // empty by default
}

void GameEntity::shapeClear(){
    shape.destroy();
}

void GameEntity::receiveCollision(GameEntity& entity) {
    // empty by default
}

void GameEntity::receiveKeyboard(Direction d) {
    // empty by default
}

#include <iostream>

bool GameEntity::canSetPosition(Vector2D position){
    bool canMove = true;
    Vector2D halfSize = size.multiply(0.5);
    Vector2D centerCell = Vector2D(0.5, 0.5);
    // Vector2D center = getCenter();
    array<Vector2D, 4> arr = position.add(centerCell).withRespectTo(size.multiply(0.5));
    for(int i = 0; i < arr.size() && canMove; i++){
        Vector2D& d = arr[i];
        Cell c = d.asCellRaw();
        CellType tp = this->engine.getCellType(c);
        canMove &= canMoveInto(tp);
    }

    return canMove;
}

bool GameEntity::setPosition(Vector2D position) {
    bool canMove = canSetPosition(position);
    if(canMove){
        this->logicPosition = position;
        return true;
    } else {
        speed = Vector2D(0.0, 0.0);
        return false;
    }
}

bool GameEntity::canMoveInto(CellType cellType) {
    return true;
}

// TODO remove
Vector2D GameEntity::getCenter() {
    const float centerY = 0.5 - this->size.getY() / 2.0;
    const float centerX = 0.5 - this->size.getX() / 2.0;
    return Vector2D(centerX, centerY);
}

string GameEntity::getName(){
    return "XXX";
}