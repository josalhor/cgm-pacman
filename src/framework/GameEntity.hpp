/*
 * Vector2D position;
*/
#include <string>
using namespace std;

class GameEntity {
    protected:
        // Absolute position in the matrix ex: [0.5, 0.5]
        Vector2D logicPosition;
        // Vertices to paint
        vec<Vector2D> region;
        // Vector that indicates the speed of a game object
        Vector2D speed;
        map<string, void(*)()> collisionResolver;
        void destroy();
    public:
        static const string typeName;
        void update();
        void receiveCollision(GameEntity entity);
}