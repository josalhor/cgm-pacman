#ifndef SHAPE_PRISMA
#define SHAPE_PRISMA
#include "framework/graphics/Shape.hpp"
#include "framework/graphics/Color.hpp"
#include "utils/Vector3D.hpp"
#include <GL/glut.h>

class Prisma: public Shape {
    public:
        Color color;
        Prisma(CoordinateMapper& mapper, Color color) : color(color), Shape(mapper) {
            // float x = 0;
            // float y = 0;
            // collision_boxing = Vector3D(0.5*x, offset, 0.5*z);
            // geo_center = Vector3D(0.5*x, offset, -0.5*z);
        }

        void draw(Vector2D logicPosition, Vector2D size, float height, float offset) {
            Vector2D centerPoint = getP2(size);
            Vector2D renderOn = logicPosition.add(centerPoint);
            Vector2D p0 = renderOn.add(size);
            Vector3D renderOn3D = to3dSpace(renderOn);
            Vector3D p03D = to3dSpace(p0);
            float x = mapper.XtoVisualFloat(renderOn3D.getX());
            float z = mapper.YtoVisualFloat(renderOn3D.getZ());
            float px = mapper.XtoVisualFloat(p03D.getX());
            float pz = mapper.YtoVisualFloat(p03D.getZ());
            int high = height + offset;

            glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glVertex3i(x, high, z);
            glVertex3i(px, high, z);
            glVertex3i(px, high, pz);
            glVertex3i(x, high, pz);
            glEnd();

            glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glVertex3i(x, offset, pz);
            glVertex3i(px, offset, pz);
            glVertex3i(px, offset, z);
            glVertex3i(x, offset, z);
            glEnd();

            glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glVertex3i(x, high, pz);
            glVertex3i(x, offset, pz);
            glVertex3i(x, offset, z);
            glVertex3i(x, high, z);
            glEnd();

            glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glVertex3i(px, high, z);
            glVertex3i(px, offset, z);
            glVertex3i(px, offset, pz);
            glVertex3i(px, high, pz);
            glEnd();

            glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glVertex3i(px, high, z);
            glVertex3i(x, high, z);
            glVertex3i(x, offset, z);
            glVertex3i(px, offset, z);
            glEnd();

            glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glVertex3i(px, high, pz);
            glVertex3i(px, offset, pz);
            glVertex3i(x, offset, pz);
            glVertex3i(x, high, pz);
            glEnd();

        }

        void print() {

        }
};

#endif