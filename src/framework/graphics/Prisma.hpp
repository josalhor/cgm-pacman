#ifndef SHAPE_PRISMA
#define SHAPE_PRISMA
#include "framework/graphics/Shape.hpp"
#include "framework/graphics/Color.hpp"
#include "utils/Vector3D.hpp"
#include "framework/TextureLoader.hpp"
#include <GL/glut.h>

#define O(c,t,v) (c ? (t, v) : (v));

#define PRISMA_SLICES 8

class Prisma: public Shape {
    public:
        Color color;
        Prisma(CoordinateMapper& mapper, Color color, int texture_index) : color(color), Shape(mapper, texture_index) {
            // float x = 0;
            // float y = 0;
            // collision_boxing = Vector3D(0.5*x, offset, 0.5*z);
            // geo_center = Vector3D(0.5*x, offset, -0.5*z);
        }

    void renderFaceX(float x, float y, float yf, float z, float zf) {
        const float slicesF = (float) PRISMA_SLICES;
        for(int j = 0; j < PRISMA_SLICES; j++){
            float yi = ((yf - y) * ((float) j) / slicesF) + y;
            for(int k = 0; k < PRISMA_SLICES; k++){
                float zi = ((zf - z) * ((float) k) / slicesF) + z;
                glTexCoord2f(1.0 / (float) j,1.0 / (float) k), glVertex3f(x, yi, zi);
            }
        }
    }

    void renderFaceY(float x, float xf, float y, float z, float zf) {
        const float slicesF = (float) PRISMA_SLICES;
        for(int i = 0; i < PRISMA_SLICES; i++){
            float xi = ((xf - x) * ((float) i) / slicesF) + x;
            for(int k = 0; k < PRISMA_SLICES; k++){
                float zi = ((zf - z) * ((float) k) / slicesF) + z;
                glTexCoord2f(1.0 / (float) i,1.0 / (float) k), glVertex3f(xi, y, zi);
            }
        }
    }

    void renderFaceZ(float x, float xf, float y, float yf, float z) {
        const float slicesF = (float) PRISMA_SLICES;
        for(int i = 0; i < PRISMA_SLICES; i++){
            float xi = ((xf - x) * ((float) i) / slicesF) + x;
            for(int j = 0; j < PRISMA_SLICES; j++){
                float yi = ((yf - y) * ((float) j) / slicesF) + y;
                glTexCoord2f(1.0 / (float) i,1.0 / (float) j), glVertex3f(xi, yi, z);
            }
        }
    }

    /*void renderFace(float x, float xf, float y, float yf, float z, float zf) {
        
            const float slicesF = (float) PRISMA_SLICES;
            float incX = (xf - x) / (float) slices;
            float incY = (yf - y) / (float) slices;
            float incZ = (zf - z) / (float) slices;
            glTexCoord2f(-1.0,0.0), glVertex3f(x, high, z);
            glTexCoord2f(1.0,0.0), glVertex3f(px, high, z);
            glTexCoord2f(1.0,1.0), glVertex3f(px, high, pz);
            glTexCoord2f(-1.0,1.0), glVertex3f(x, high, pz);
            for(int i = 0; i < slices; i++){
                float xi = ((xf - x) * ((float) i) / slicesF) + x;
                for(int j = 0; j < slices; j++){
                    float yi = ((yf - y) * ((float) j) / slicesF) + y;
                    for(int k = 0; k < slices; k++){
                        float zi = ((zf - z) * ((float) k) / slicesF) + z;

                        glTexCoord2f(-1.0,1.0), glVertex3f(x, high, pz);
                        if(z == zf) break;
                    }
                    if(y == yf) break;
                }
                if(x == xf) break;
            }
        }*/


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
            GLfloat material[4];
            if (texture_index >= 0){
                glBindTexture(GL_TEXTURE_2D, texture_index);
            }

            material[0]=1.0; material[1]=1.0; material[2]=1.0; material[3]=0.0; 
            
            //glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);
            glNormal3f(0,1,0);
            glTexCoord2f(-1.0,0.0), glVertex3f(x, high, z);
            glTexCoord2f(1.0,0.0), glVertex3f(px, high, z);
            glTexCoord2f(1.0,1.0), glVertex3f(px, high, pz);
            glTexCoord2f(-1.0,1.0), glVertex3f(x, high, pz);
            glEnd();

            //glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);
            glNormal3f(0,-1,0);
            glTexCoord2f(-1.0,0.0), glVertex3f(x, offset, pz);
            glTexCoord2f(1.0,0.0), glVertex3f(px, offset, pz);
            glTexCoord2f(1.0,1.0), glVertex3f(px, offset, z);
            glTexCoord2f(-1.0,1.0), glVertex3f(x, offset, z);
            glEnd();

            //glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);
            
            glNormal3f(-1,0,0);
            glTexCoord2f(-1.0,0.0), glVertex3f(x, high, pz);
            glTexCoord2f(1.0,0.0), glVertex3f(x, offset, pz);
            glTexCoord2f(1.0,1.0), glVertex3f(x, offset, z);
            glTexCoord2f(-1.0,1.0), glVertex3f(x, high, z);
            glEnd();

            //glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);
            glNormal3f(1,0,0);
            glTexCoord2f(-1.0,0.0), glVertex3f(px, high, z);
            glTexCoord2f(1.0,0.0), glVertex3f(px, offset, z);
            glTexCoord2f(1.0,1.0), glVertex3f(px, offset, pz);
            glTexCoord2f(-1.0,1.0), glVertex3f(px, high, pz);
            glEnd();

            //glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);
            glNormal3f(0,0,1);
            glTexCoord2f(-1.0,0.0), glVertex3f(px, high, z);
            glTexCoord2f(1.0,0.0), glVertex3f(x, high, z);
            glTexCoord2f(1.0,1.0), glVertex3f(x, offset, z);
            glTexCoord2f(-1.0,1.0), glVertex3f(px, offset, z);
            glEnd();

            //glColor3f(this->color[0], this->color[1], this->color[2]);
            glBegin(GL_QUADS);
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);
            glNormal3f(0,0,-1);
            glTexCoord2f(-1.0,0.0), glVertex3f(px, high, pz);
            glTexCoord2f(1.0,0.0), glVertex3f(px, offset, pz);
            glTexCoord2f(1.0,1.0), glVertex3f(x, offset, pz);
            glTexCoord2f(-1.0,1.0), glVertex3f(x, high, pz);
            glEnd();

            if (texture_index == PACMAN_TEXTURE_INDEX) {
                GLint position[4];
                GLfloat color[4];
                position[0]=(x + px) /2; position[1]=offset+(height/2); position[2]=(z + pz)/2; position[3]=1; 
                glLightiv(GL_LIGHT1,GL_POSITION,position);
                GLint direction[3];
                direction[0] = 0; direction[1] = 0; direction[2] = 1; 
                glLightiv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
                
                color[0]=0; color[1]=0.5; color[2]=0.5; color[3]=1;
                glLightfv(GL_LIGHT1,GL_DIFFUSE,color);

                glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION,0.005);
                // glLightf(GL_LIGHT1,GL_LINEAR_ATTENUATION,0.001);
                // glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,0.0000001);
                glLightf(GL_LIGHT1,GL_LINEAR_ATTENUATION,0.0);
                glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,0.0);
                glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,20.0);
                glLightf (GL_LIGHT1, GL_SPOT_EXPONENT, 1);

                glEnable(GL_LIGHT1);
            }

           

        }

        void print() {

        }
};

#endif