#ifndef SHAPE_PRISMA
#define SHAPE_PRISMA
#include "framework/graphics/Shape.hpp"
#include "framework/graphics/Color.hpp"
#include "utils/Vector3D.hpp"
#include <GL/glut.h>

class Prisma: public Shape {
    public:
        Color color;
        Prisma(Color color) : color(color), Shape() {
            float x = 0;
            float y = 0;
            collision_boxing = Vector3D(0.5*x, 0, 0.5*y);
            geo_center = Vector3D(0.5*x, 0, -0.5*y);
        }

        void draw(float x, float y, float px, float py, float height) {
            glColor3f(this->color[0], this->color[1], this->color[2]);

            int p = height;

            glBegin(GL_QUADS);
            glVertex3i(x,y,p);
            glVertex3i(px,y,p);
            glVertex3i(px,py,p);
            glVertex3i(x,py,p);
            glEnd();

            glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glVertex3i(x,py,0);
            glVertex3i(px,py,0);
            glVertex3i(px,y,0);
            glVertex3i(x,y,0);
            glEnd();

            glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glVertex3i(x,py,p);
            glVertex3i(x,py,0);
            glVertex3i(x,y,0);
            glVertex3i(x,y,p);
            glEnd();

            glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glVertex3i(px,y,p);
            glVertex3i(px,y,0);
            glVertex3i(px,py,0);
            glVertex3i(px,py,p);
            glEnd();

            glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glVertex3i(px,y,p);
            glVertex3i(x,y,p);
            glVertex3i(x,y,0);
            glVertex3i(px,y,0);
            glEnd();

            glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glVertex3i(px,py,p);
            glVertex3i(px,py,0);
            glVertex3i(x,py,0);
            glVertex3i(x,py,p);
            glEnd();

        }

        void print() {

        }
};

#endif