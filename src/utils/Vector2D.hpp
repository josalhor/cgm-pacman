#ifndef VECT2D
#define VECT2D

#include "utils.hpp"
#include "Cell.hpp"
#include <array>

using namespace std;

class Vector2D {
    private:
        float x;
        float y;
        
    public:
    Vector2D(){
        this->x = 0;
        this->y = 0;
    }

    Vector2D(float x, float y) {
        this->x = x;
        this->y = y;
    }

    Vector2D add(Vector2D& o){
        return Vector2D(
            this->x + o.x,
            this->y + o.y
        );
    }

    Vector2D subsctract(Vector2D& o){
        return Vector2D(
            this->x - o.x,
            this->y - o.y
        );
    }

    Cell asCell() {
        return Cell(
            roundToInt(x),
            roundToInt(y)
        );
    }

    Cell asCellRaw() {
        return Cell(
            
            (int) x,
            (int) y
        );
    }

    float getX(){
        return x;
    }

    float getY(){
        return y;
    }

    Vector2D multiply(float scalar){
        return Vector2D(
            x * scalar,
            y * scalar
        );
    }

    array<Vector2D, 4> withRespectTo(Vector2D center){
        array<Vector2D, 4> arr;
        arr[0] = Vector2D(x + center.x, y + center.y);
        arr[1] = Vector2D(x - center.x, y + center.y);
        arr[2] = Vector2D(x + center.x, y - center.y);
        arr[3] = Vector2D(x - center.x, y - center.y);
        return arr;
    }
};

#endif