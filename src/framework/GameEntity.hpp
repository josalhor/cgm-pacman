#ifndef GAMEENTITY
#define GAMEENTITY

#include <string>
#include <map>
#include <vector>
#include "utils/Vector2D.hpp"
class Engine;
#include "Engine.hpp"
#include "CoordinateMapper.hpp"
using namespace std;

class GameEntity {
    private:
        Engine& engine;
        void destroy();
    protected:
        // Absolute position in the matrix ex: [0.5, 0.5]
        Vector2D logicPosition;
        // Vertices to paint
        vector<Vector2D> region;
        // Vector that indicates the speed of a game object
        Vector2D speed;
        map<string, void(*)()> collisionResolver;
    public:
        GameEntity(Engine& engine);
        static const string typeName;
        Vector2D getPosition() {
            return this->logicPosition;
        }
        void setPosition(Vector2D position){
            this->logicPosition = position;
        }
        virtual void update();
        virtual void draw(CoordinateMapper& mapper);
        virtual void receiveCollision(GameEntity& entity);
};

#endif