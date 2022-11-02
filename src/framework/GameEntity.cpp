#include "GameEntity.hpp"

GameEntity::GameEntity(Engine& engine) : engine(engine) {

}

void GameEntity::update(){
    // empty by default
}

void GameEntity::draw(){
    // empty by default
}

void GameEntity::receiveCollision(GameEntity entity) {
    // empty by default
}