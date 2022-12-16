#include "Vector2D.hpp"
#include "utils.hpp"
using namespace std;

Vector2D::Vector2D(){
    this->x = 0;
    this->y = 0;
}

Vector2D::Vector2D(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2D Vector2D::add(Vector2D& o){
    return Vector2D(
        this->x + o.x,
        this->y + o.y
    );
}

Vector2D Vector2D::subsctract(Vector2D& o){
    return Vector2D(
        this->x - o.x,
        this->y - o.y
    );
}

Cell Vector2D::asCell() {
    return Cell(
        roundToInt(x),
        roundToInt(y)
    );
}

Cell Vector2D::asCellRaw() {
    return Cell(
        (int) x,
        (int) y
    );
}

float Vector2D::getX(){
    return x;
}

float Vector2D::getY(){
    return y;
}

Vector2D Vector2D::multiply(float scalar){
    return Vector2D(
        x * scalar,
        y * scalar
    );
}

array<Vector2D, 4> Vector2D::withRespectTo(Vector2D center){
    array<Vector2D, 4> arr;
    arr[0] = Vector2D(x + center.x, y + center.y);
    arr[1] = Vector2D(x - center.x, y + center.y);
    arr[2] = Vector2D(x + center.x, y - center.y);
    arr[3] = Vector2D(x - center.x, y - center.y);
    return arr;
}
