/*
 * Vector2D position;
*/
#include <string>
#include <map>
#include <vector>
#include "utils/Vector2D.hpp"

using namespace std;

class GameEntity {
    protected:
        // Absolute position in the matrix ex: [0.5, 0.5]
        Vector2D logicPosition;
        // Vertices to paint
        vector<Vector2D> region;
        // Vector that indicates the speed of a game object
        Vector2D speed;
        map<string, void(*)()> collisionResolver;
        void destroy();
    public:
        static const string typeName;
        void update();
        void receiveCollision(GameEntity entity);
};