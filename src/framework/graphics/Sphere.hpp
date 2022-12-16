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
        int lightIndex;
        Sphere(CoordinateMapper& mapper, Color color, int texture_index, int lightIndex) : lightIndex(lightIndex), color(color), Shape(mapper, texture_index) {
            // float x = 0;
            // float y = 0;
            // collision_boxing = Vector3D(0.5*x, offset, 0.5*z);
            // geo_center = Vector3D(0.5*x, offset, -0.5*z);
        }

        void draw(Vector2D logicPosition, Vector3D normalDirection, float radius, float offset, float flashAngle) {
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
                direction[0] = normalDirection.getX(); direction[1] = normalDirection.getY(); direction[2] = normalDirection.getZ(); 
                glLightiv(GL_LIGHT1 + lightIndex, GL_SPOT_DIRECTION, direction);
                float linearAtt = 0.001;
                
                if (lightIndex == 0) {
                    color[0]=0.5; color[1]=0.5; color[2]=0.25; color[3]=1;
                } else {
                    color[0]=0.7; color[1]=0; color[2]=0.1; color[3]=1;
                }
                
                glLightfv(GL_LIGHT1 + lightIndex,GL_DIFFUSE,color);

                glLightf(GL_LIGHT1 + lightIndex,GL_CONSTANT_ATTENUATION,0.01);
                // glLightf(GL_LIGHT1 + lightIndex,GL_LINEAR_ATTENUATION,0.001);
                // glLightf(GL_LIGHT1 + lightIndex,GL_QUADRATIC_ATTENUATION,0.0000001);
                glLightf(GL_LIGHT1 + lightIndex,GL_LINEAR_ATTENUATION,linearAtt);
                glLightf(GL_LIGHT1 + lightIndex,GL_QUADRATIC_ATTENUATION,0.0);
                glLightf(GL_LIGHT1 + lightIndex,GL_SPOT_CUTOFF,flashAngle);
                glLightf (GL_LIGHT1 + lightIndex, GL_SPOT_EXPONENT, 1);

                glEnable(GL_LIGHT1 + lightIndex);
            }
        }

        void destroy() {
            if (lightIndex > -1) {
                glDisable(GL_LIGHT1 + lightIndex);
            }
        }

        void print() {

        }
};

#endif