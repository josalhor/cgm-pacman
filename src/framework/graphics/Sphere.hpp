#ifndef SHAPE_SPHERE
#define SHAPE_SPHERE

#include "framework/graphics/Shape.hpp"
#include "framework/graphics/Color.hpp"
#include "utils/Vector3D.hpp"
#include <GL/glut.h>

class Sphere: public Shape {
    public:
        Color color;
        Sphere(CoordinateMapper& mapper, Color color) : color(color), Shape(mapper) {
            // float x = 0;
            // float y = 0;
            // collision_boxing = Vector3D(0.5*x, offset, 0.5*z);
            // geo_center = Vector3D(0.5*x, offset, -0.5*z);
        }

        void draw(Vector2D logicPosition, float radius, float offset) {
            Vector2D centerOffset = Vector2D(0.5, 0.5);
            Vector2D renderOn = logicPosition.add(centerOffset);
            Vector3D renderOn3D = to3dSpace(renderOn);
            float x = mapper.XtoVisualFloat(renderOn3D.getX());
            float z = mapper.YtoVisualFloat(renderOn3D.getZ());
            radius = mapper.XtoVisualFloat(radius);
            int slices = 20;

            glColor3f(this->color[0], this->color[1], this->color[2]);
            glPushMatrix();
            GLUquadric *quad;
            quad = gluNewQuadric();
            glTranslatef(x,offset,z);
            gluSphere(quad,radius,slices,slices);
            glPopMatrix();
        }

        void print() {

        }
};

#endif