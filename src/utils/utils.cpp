#include "./utils.hpp"

bool hasMinimumAmount(int minimum, int quantity)
{
    return quantity >= minimum;
}

bool isOddInput(int num)
{
    return (num % 2) != 0;
}

int roundToInt(float x){
    return (int) (x + 0.5);
}

Vector3D to3dSpace(Vector2D v) {
    return Vector3D(
        v.getX(),
        0,
        v.getY()
    );
}