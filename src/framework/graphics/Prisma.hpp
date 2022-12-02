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
            float x = 0;
            float y = 0;
            collision_boxing = Vector3D(0.5*x, 0, 0.5*y);
            geo_center = Vector3D(0.5*x, 0, -0.5*y);
        }

        void draw(Vector2D logicPosition, Vector2D size, float height, float offset) {
            Vector2D centerPoint = getCenter(size);
            Vector2D renderOn = logicPosition.add(centerPoint);
            float x = renderOn.getX();
            float y = renderOn.getY();
            Vector2D p0 = renderOn.add(size);
            Vector3D renderOn3D = to3dSpace(renderOn);
            x = mapper.XtoVisualFloat(renderOn3D.getX());
            y = mapper.YtoVisualFloat(renderOn3D.getZ());
            glColor3f(this->color[0], this->color[1], this->color[2]);
            float px = mapper.XtoVisualFloat(p0.getX());
            float py = mapper.YtoVisualFloat(p0.getY());
            int p = -height;

            glBegin(GL_QUADS);
            glVertex3i(x, p, y);
            glVertex3i(px, p, y);
            glVertex3i(px, p, py);
            glVertex3i(x, p, py);
            glEnd();

            glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glVertex3i(x, 0, py);
            glVertex3i(px, 0, py);
            glVertex3i(px, 0, y);
            glVertex3i(x, 0, y);
            glEnd();

            glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glVertex3i(x, p, py);
            glVertex3i(x, 0, py);
            glVertex3i(x, 0, y);
            glVertex3i(x, p, y);
            glEnd();

            glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glVertex3i(px, p, y);
            glVertex3i(px, 0, y);
            glVertex3i(px, 0, py);
            glVertex3i(px, p, py);
            glEnd();

            glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glVertex3i(px, p, y);
            glVertex3i(x, p, y);
            glVertex3i(x, 0, y);
            glVertex3i(px, 0, y);
            glEnd();

            glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glVertex3i(px, p, py);
            glVertex3i(px, 0, py);
            glVertex3i(x, 0, py);
            glVertex3i(x, p, py);
            glEnd();

        }

        void print() {

        }
};

#endif