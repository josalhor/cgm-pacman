#ifndef SHAPE_PRISMA
#define SHAPE_PRISMA
#include "framework/graphics/Shape.hpp"
#include "framework/graphics/Color.hpp"
#include "utils/Vector3D.hpp"
#include <GL/glut.h>

#define O(c,t,v) (c ? (t, v) : (v));

#define PRISMA_SLICES 10

class PointSquare {
    public:
    float a;
    float b;
    PointSquare(float a, float b) : a(a), b(b) {}
};

// class SquarePrisma {
//     public:
//     array<PointSquare, 4> pointSquare;
//     PointSquare(array<PointSquare, 4> pointSquare) : pointSquare(pointSquare) {}
// };



class Prisma: public Shape {
    public:
        Color color;
        GLfloat material[4];
        Prisma(CoordinateMapper& mapper, Color color, int texture_index) : color(color), Shape(mapper, texture_index) {
            // float x = 0;
            // float y = 0;
            // collision_boxing = Vector3D(0.5*x, offset, 0.5*z);
            // geo_center = Vector3D(0.5*x, offset, -0.5*z);
            material[0]=1.0; material[1]=1.0; material[2]=1.0; material[3]=1.0; 
        }

        void renderFaceX(float x, float y, float yf, float z, float zf, float normal) {
            const float slicesF = (float) PRISMA_SLICES;
            for(int j = 0; j < PRISMA_SLICES; j++){
                for(int k = 0; k < PRISMA_SLICES; k++){

                    float yi = ((yf - y) * ((float) j) / slicesF) + y;
                    float yiF = ((yf - y) * ((float) j + 1) / slicesF) + y;
                    float zi = ((zf - z) * ((float) k) / slicesF) + z;
                    float ziF = ((zf - z) * ((float) k + 1) / slicesF) + z;
                    float progressYi = ((float) j) / slicesF;
                    float progressYiF = ((float) j + 1) / slicesF;
                    float progressZi = ((float) k) / slicesF;
                    float progressZiF = ((float) k + 1) / slicesF;

                    glBegin(GL_QUADS);
                    glNormal3f(normal,0,0);                    

                    auto F1 = [&]() { glTexCoord2f(progressYiF,progressZi), glVertex3f(x, yiF, zi); };
                    auto F2 = [&]() { glTexCoord2f(progressYi,progressZi), glVertex3f(x, yi, zi); };
                    auto F3 = [&]() { glTexCoord2f(progressYi,progressZiF), glVertex3f(x, yi, ziF); };
                    auto F4 = [&]() { glTexCoord2f(progressYiF,progressZiF), glVertex3f(x, yiF, ziF); };

                    if (normal > 0) {
                        F1(); F2(); F3(); F4();
                    } else {
                        F4(); F3(); F2(); F1();
                    }


                    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);
                    
                    glEnd();
                }
            }
        }

        void renderFaceY(float x, float xf, float y, float z, float zf, float normal) {
            const float slicesF = (float) PRISMA_SLICES;
            for(int j = 0; j < PRISMA_SLICES; j++){
                for(int k = 0; k < PRISMA_SLICES; k++){

                    float xi = ((xf - x) * ((float) j) / slicesF) + x;
                    float xiF = ((xf - x) * ((float) j + 1) / slicesF) + x;
                    float zi = ((zf - z) * ((float) k) / slicesF) + z;
                    float ziF = ((zf - z) * ((float) k + 1) / slicesF) + z;
                    float progressXi = ((float) j) / slicesF;
                    float progressXiF = ((float) j + 1) / slicesF;
                    float progressZi = ((float) k) / slicesF;
                    float progressZiF = ((float) k + 1) / slicesF;

                    glBegin(GL_QUADS);
                    glNormal3f(0,normal,0);
                    auto F1 = [&]() { glTexCoord2f(progressXiF,progressZiF), glVertex3f(xi, y, zi); };
                    auto F2 = [&]() { glTexCoord2f(progressXi,progressZiF), glVertex3f(xiF, y, zi); };
                    auto F3 = [&]() { glTexCoord2f(progressXi,progressZi), glVertex3f(xiF, y, ziF); };
                    auto F4 = [&]() { glTexCoord2f(progressXiF,progressZi), glVertex3f(xi, y, ziF); };

                    if (normal > 0) {
                        F1(); F2(); F3(); F4();
                    } else {
                        F4(); F3(); F2(); F1();
                    }

                    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);
                    
                    glEnd();
                }
            }
        }

        void renderFaceZ(float x, float xf, float y, float yf, float z, float normal) {
            const float slicesF = (float) PRISMA_SLICES;
            for(int j = 0; j < PRISMA_SLICES; j++){
                for(int k = 0; k < PRISMA_SLICES; k++){

                    float xi = ((xf - x) * ((float) j) / slicesF) + x;
                    float xiF = ((xf - x) * ((float) j + 1) / slicesF) + x;
                    float yi = ((yf - y) * ((float) k) / slicesF) + y;
                    float yiF = ((yf - y) * ((float) k + 1) / slicesF) + y;
                    float progressXi = ((float) j) / slicesF;
                    float progressXiF = ((float) j + 1) / slicesF;
                    float progressYi = ((float) k) / slicesF;
                    float progressYiF = ((float) k + 1) / slicesF;

                    glBegin(GL_QUADS);
                    glNormal3f(0,0,normal);

                    auto F1 = [&]() { glTexCoord2f(progressXiF,progressYi), glVertex3f(xi, yiF, z); };
                    auto F2 = [&]() { glTexCoord2f(progressXi,progressYi), glVertex3f(xi, yi, z); };
                    auto F3 = [&]() { glTexCoord2f(progressXi,progressYiF), glVertex3f(xiF, yi, z); };
                    auto F4 = [&]() { glTexCoord2f(progressXiF,progressYiF), glVertex3f(xiF, yiF, z); };

                    if (normal > 0) {
                        F1(); F2(); F3(); F4();
                    } else {
                        F4(); F3(); F2(); F1();
                    }

                    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);
                    
                    glEnd();
                }
            }
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
            
            glBindTexture(GL_TEXTURE_2D, texture_index);

            renderFaceY(x, px, high, z, pz, 1);
            renderFaceY(x, px, offset, z, pz, -1);

            renderFaceX(x, offset, high, z, pz, -1);

            renderFaceX(px, offset, high, z, pz, 1);

            renderFaceZ(x, px, offset, high, z, 1);

            renderFaceZ(x, px, offset, high, pz, -1);         

        }

        void destroy() {

        }

        void print() {

        }
};

#endif