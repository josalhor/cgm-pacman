#ifndef SHAPE_H
#define SHAPE_H

#include "utils/Vector3D.hpp"
#include "framework/CoordinateMapper.hpp"
#include <array>

using namespace std;

class Shape {
    protected:
        // represents the geometrical center of the shape to paint
        Vector3D geo_center;
        /*
         * represents the distance from the center to the collision box
         * in the x axis, used to compute a collision cube
         */
        Vector3D collision_boxing;
        CoordinateMapper& mapper;
    public:
        Shape(CoordinateMapper& mapper) : mapper(mapper) {

        }
        // virtual void draw() = 0;
        virtual void print() = 0;
        bool intersects(Shape& s)
        {
            // compute shape's collision box
            array<Vector3D, 8> myBox = getCollisionBox();
            array<Vector3D, 8> otherBox = getCollisionBox();

            //detect if in the same height
            if(
                myBox[0].getY() <= otherBox[4].getY() && myBox[0].getY() >= otherBox[0].getY() ||
                myBox[4].getY() <= otherBox[4].getY() && myBox[4].getY() >= otherBox[0].getY()
            ) {
                // detect if inside XZ region, X inside, Z inside
                if(
                    (
                        myBox[0].getX() >= otherBox[1].getX() && myBox[0].getX() <= otherBox[0].getX() ||
                        myBox[1].getX() >= otherBox[1].getX() && myBox[1].getX() <= otherBox[0].getX()
                    ) &&
                    (
                        myBox[0].getZ() >= otherBox[2].getZ() && myBox[0].getZ() <= otherBox[0].getZ() ||
                        myBox[2].getZ() >= otherBox[2].getZ() && myBox[2].getZ() <= otherBox[0].getZ()
                    )
                ) {
                    return true;
                }
            }
            return false;
        }

        /*
         * Points are represented counter clock wise 
         * starting from the furthest "behind" right point in the XZ plane
         * and from the bottom to the top in the Y axis
         *        1 _______ 0
         *         |       |
         *         |       |
         *        2|_______|3
        */
        array<Vector3D, 8> getCollisionBox() 
        {
            array<Vector3D, 8> box;
            float posX = geo_center.getX() + collision_boxing.getX();
            float negX = geo_center.getX() - collision_boxing.getX();
            float posZ = geo_center.getZ() + collision_boxing.getZ();
            float negZ = geo_center.getZ() - collision_boxing.getZ();
            float posY = geo_center.getY() + collision_boxing.getY();
            float negY = geo_center.getY() - collision_boxing.getY();

            // "-Y"
            box[0] = Vector3D(posX, negY, negZ);
            box[1] = Vector3D(negX, negY, negZ);
            box[2] = Vector3D(negX, negY, posZ);
            box[3] = Vector3D(posX, negY, posZ);
            // "+Y"
            box[4] = Vector3D(posX, posY, negZ);
            box[5] = Vector3D(negX, posY, negZ);
            box[6] = Vector3D(negX, posY, posZ);
            box[7] = Vector3D(posX, posY, posZ);
            return box;
        }

        Vector2D getP2(Vector2D size) {
            const float centerY = 0.5 - size.getY() / 2.0;
            const float centerX = 0.5 - size.getX() / 2.0;
            return Vector2D(centerX, centerY);
        }
};

#endif