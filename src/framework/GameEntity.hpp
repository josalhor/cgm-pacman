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
    protected:
        Vector2D logicPosition;
        Engine& engine;
        // Absolute position in the matrix ex: [0.5, 0.5]
        // Vertices to paint
        vector<Vector2D> region;
        // Vector that indicates the speed of a game object
        Vector2D speed;
        Vector2D size;
        // map<string, void(*)()> collisionResolver;
    public:
        GameEntity(Engine& engine);
        void destroy();
        Vector2D getPosition() {
            return this->logicPosition;
        }
        void setPosition(Vector2D position);
        virtual bool canMoveInto(CellType cellType);
        virtual void update();
        virtual void draw(CoordinateMapper& mapper);
        virtual void receiveCollision(GameEntity& entity);
        virtual void receiveKeyboard(Direction d);
        virtual string getName();
        Vector2D center(Vector2D point);
};

#endif