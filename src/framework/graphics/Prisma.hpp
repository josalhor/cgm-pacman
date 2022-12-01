#ifndef SHAPE_PRISMA
#define SHAPE_PRISMA
#include "framework/graphics/Shape.hpp"
#include "utils/Vector3D.hpp"
#include <GL/glut.h>

class Prisma: public Shape {
    public:
        Prisma(int x, int y) : Shape() {
            this->collision_boxing = Vector3D(0.5*x, 0, 0.5*y);
            this->geo_center = Vector3D(0.5*x, 0, -0.5*y);
        }

        void draw() {
            glColor3f(1, 0, 0);

            glBegin(GL_QUADS);
            glVertex3i(50,50,50);
            glVertex3i(-50,50,50);
            glVertex3i(-50,-50,50);
            glVertex3i(50,-50,50);
            glEnd();

            glColor3f(1.0, 1.0, 0.0);
            glBegin(GL_QUADS);
            glVertex3i(50,-50,-50);
            glVertex3i(-50,-50,-50);
            glVertex3i(-50,50,-50);
            glVertex3i(50,50,-50);
            glEnd();

            glColor3f(0.0, 0.0, 1.0);
            glBegin(GL_QUADS);
            glVertex3i(50,-50,50);
            glVertex3i(50,-50,-50);
            glVertex3i(50,50,-50);
            glVertex3i(50,50,50);
            glEnd();

            glColor3f(0.0, 1.0, 0.0);
            glBegin(GL_QUADS);
            glVertex3i(-50,50,50);
            glVertex3i(-50,50,-50);
            glVertex3i(-50,-50,-50);
            glVertex3i(-50,-50,50);
            glEnd();

            glColor3f(1.0, 0.0, 1.0);
            glBegin(GL_QUADS);
            glVertex3i(-50,50,50);
            glVertex3i(50,50,50);
            glVertex3i(50,50,-50);
            glVertex3i(-50,50,-50);
            glEnd();

            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_QUADS);
            glVertex3i(-50,-50,50);
            glVertex3i(-50,-50,-50);
            glVertex3i(50,-50,-50);
            glVertex3i(50,-50,50);
            glEnd();

        }

        void print() {

        }
};

#endif