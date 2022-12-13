#ifndef SHAPE_SPHERE
#define SHAPE_SPHERE

#include "framework/TextureLoader.hpp"
#include "framework/graphics/Shape.hpp"
#include "framework/graphics/Color.hpp"
#include "utils/Vector3D.hpp"
#include <GL/glut.h>

class Sphere: public Shape {
    public:
        Color color;
        Sphere(CoordinateMapper& mapper, Color color, int texture_index) : color(color), Shape(mapper, texture_index) {
            // float x = 0;
            // float y = 0;
            // collision_boxing = Vector3D(0.5*x, offset, 0.5*z);
            // geo_center = Vector3D(0.5*x, offset, -0.5*z);
        }

        void draw(Vector2D logicPosition, float radius, float offset, int lightIndex) {
            Vector2D centerOffset = Vector2D(0.5, 0.5);
            Vector2D renderOn = logicPosition.add(centerOffset);
            Vector3D renderOn3D = to3dSpace(renderOn);
            float x = mapper.XtoVisualFloat(renderOn3D.getX());
            float z = mapper.YtoVisualFloat(renderOn3D.getZ());
            radius = mapper.XtoVisualFloatWithoutCenter(radius);
            int slices = 20;

            //glColor3f(this->color[0], this->color[1], this->color[2]);
            glPushMatrix();
            GLUquadric *quad;
            quad = gluNewQuadric();
            gluQuadricTexture(quad, GL_TRUE);
            glBindTexture(GL_TEXTURE_2D, texture_index);
            //glBindTexture(GL_TEXTURE_2D, 0);
            GLfloat material[4];
            material[0]=1.0; material[1]=1.0; material[2]=1.0; material[3]=1.0;
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);
            glTranslatef(x,offset,z);
            gluSphere(quad,radius,slices,slices);
            gluDeleteQuadric(quad);
            glPopMatrix();


            if (lightIndex > -1) {
                GLint position[4];
                GLfloat color[4];
                position[0]=x; position[1]=offset; position[2]=z; position[3]=1; 
                glLightiv(GL_LIGHT1 + lightIndex, GL_POSITION,position);
                GLint direction[3];
                direction[0] = 0; direction[1] = 0; direction[2] = 1; 
                glLightiv(GL_LIGHT1 + lightIndex, GL_SPOT_DIRECTION, direction);
                
                color[0]=0.0; color[1]=0.5; color[2]=0.5; color[3]=1;
                glLightfv(GL_LIGHT1 + lightIndex,GL_DIFFUSE,color);

                glLightf(GL_LIGHT1 + lightIndex,GL_CONSTANT_ATTENUATION,0.005);
                // glLightf(GL_LIGHT1 + lightIndex,GL_LINEAR_ATTENUATION,0.001);
                // glLightf(GL_LIGHT1 + lightIndex,GL_QUADRATIC_ATTENUATION,0.0000001);
                glLightf(GL_LIGHT1 + lightIndex,GL_LINEAR_ATTENUATION,0.0);
                glLightf(GL_LIGHT1 + lightIndex,GL_QUADRATIC_ATTENUATION,0.0);
                glLightf(GL_LIGHT1 + lightIndex,GL_SPOT_CUTOFF,20.0);
                glLightf (GL_LIGHT1 + lightIndex, GL_SPOT_EXPONENT, 1);

                glEnable(GL_LIGHT1 + lightIndex);
            }
        }

        void print() {

        }
};

#endif