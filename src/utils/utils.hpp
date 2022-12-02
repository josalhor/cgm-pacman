#ifndef UTILS
#define UTILS

#include "Vector2D.hpp"
#include "Vector3D.hpp"

bool hasMinimumAmount(int minimum, int quantity);

bool isOddInput(int num);


Vector3D to3dSpace(Vector2D other);

/*
Vector2D toLogic2d(Vector3D);
*/

int roundToInt(float x);

#endif