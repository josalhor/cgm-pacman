#ifndef GAMEENTITY
#define GAMEENTITY

#include <string>
#include <map>
#include <vector>
#include "utils/Vector2D.hpp"
class Engine;
#include "Engine.hpp"
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
        void update();
        void draw();
        Vector2D getPosition() {
            return this->logicPosition;
        }
        void receiveCollision(GameEntity entity);
};

#endif