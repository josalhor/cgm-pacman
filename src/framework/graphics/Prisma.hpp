#ifndef SHAPE_PRISMA
#define SHAPE_PRISMA
#include "framework/graphics/Shape.hpp"
#include "utils/Vector3D.hpp"
#include <GL/glut.h>

class Prisma: public Shape {
    public:
        float x;
        float px;
        float y;
        float py;
        Prisma(float x, float y, float px, float py) : Shape() {
            this->x = x;
            this->px = px;
            this->py = py;
            this->y = y;
            this->collision_boxing = Vector3D(0.5*x, 0, 0.5*y);
            this->geo_center = Vector3D(0.5*x, 0, -0.5*y);
        }

        void draw() {
            glColor3f(1, 0, 0);

            int p = this->px - this->x;

            glBegin(GL_QUADS);
            glVertex3i(this->x,this->y,p);
            glVertex3i(this->px,this->y,p);
            glVertex3i(this->px,this->py,p);
            glVertex3i(this->x,this->py,p);
            glEnd();

            glColor3f(1.0, 1.0, 0.0);
            glBegin(GL_QUADS);
            glVertex3i(this->x,this->py,0);
            glVertex3i(this->px,this->py,0);
            glVertex3i(this->px,this->y,0);
            glVertex3i(this->x,this->y,0);
            glEnd();

            glColor3f(0.0, 0.0, 1.0);
            glBegin(GL_QUADS);
            glVertex3i(this->x,this->py,p);
            glVertex3i(this->x,this->py,0);
            glVertex3i(this->x,this->y,0);
            glVertex3i(this->x,this->y,p);
            glEnd();

            glColor3f(0.0, 1.0, 0.0);
            glBegin(GL_QUADS);
            glVertex3i(this->px,this->y,p);
            glVertex3i(this->px,this->y,0);
            glVertex3i(this->px,this->py,0);
            glVertex3i(this->px,this->py,p);
            glEnd();

            glColor3f(1.0, 0.0, 1.0);
            glBegin(GL_QUADS);
            glVertex3i(this->px,this->y,p);
            glVertex3i(this->x,this->y,p);
            glVertex3i(this->x,this->y,0);
            glVertex3i(this->px,this->y,0);
            glEnd();

            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_QUADS);
            glVertex3i(this->px,this->py,p);
            glVertex3i(this->px,this->py,0);
            glVertex3i(this->x,this->py,0);
            glVertex3i(this->x,this->py,p);
            glEnd();

        }

        void print() {

        }
};

#endif