#include "GameEntity.hpp"

GameEntity::GameEntity(Engine& engine) : engine(engine) {

}

void GameEntity::update(long t){
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

void GameEntity::receiveKeyboard(Direction d) {
    // empty by default
}

#include <iostream>

void GameEntity::setPosition(Vector2D position) {
    bool canMove = true;
    const float centerY = 0.5 - this->size.getY() / 2.0;
    const float centerX = 0.5 - this->size.getX() / 2.0;
    Vector2D center = Vector2D(centerX, centerY);
    array<Vector2D, 4> arr = position.add(center).withRespectTo(size.multiply(0.5));
    for(int i = 0; i < arr.size() && canMove; i++){
        Vector2D& d = arr[i];
        Cell c = d.asCellRaw();
        CellType tp = this->engine.getCellType(c);
        canMove &= canMoveInto(tp);
        cout << getName() << " " << d.getX() << " " << d.getY() << " " << canMove << endl;
    }
    if(canMove){
        this->logicPosition = position;
    } else {
        speed = Vector2D(0.0, 0.0);
    }
}

bool GameEntity::canMoveInto(CellType cellType) {
    return true;
}

Vector2D GameEntity::getCenter() {
    const float centerY = 0.5 - this->size.getY() / 2.0;
    const float centerX = 0.5 - this->size.getX() / 2.0;
    return Vector2D(centerX, centerY);
}

string GameEntity::getName(){
    return "XXX";
}