#ifndef VECT2D
#define VECT2D

#include "Cell.hpp"
#include <array>

using namespace std;

class Vector2D {
    private:
        float x;
        float y;
        
    public:
    Vector2D();
    Vector2D(float x, float y);
    Vector2D add(Vector2D& o);
    Vector2D subsctract(Vector2D& o);
    Cell asCell();
    Cell asCellRaw();
    float getX();
    float getY();
    Vector2D multiply(float scalar);
    array<Vector2D, 4> withRespectTo(Vector2D center);
};

#endif