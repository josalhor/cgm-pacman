#ifndef SHAPE_RECTANGLE
#define SHAPE_RECTANGLE
#include "framework/graphics/Shape.hpp"
#include "utils/Vector3D.hpp"

class Rectangle: private Shape {
    public:
        Rectangle(int x, int y) : Shape() {
            this->collision_boxing = Vector3D(0.5*x, 0, 0.5*y);
            this->geo_center = Vector3D(0.5*x, 0, -0.5*y);
        }

        void draw() {

        }

        void print() {
            
        }
};

#endif