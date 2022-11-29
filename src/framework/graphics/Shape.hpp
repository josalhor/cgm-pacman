#ifndef SHAPE_H
#define SHAPE_H

#include "utils/Vector3D.hpp"

class Shape {
    protected:
        // represents the geometrical center of the shape to paint
        Vector3D geo_center;
        /*
         * represents the distance from the center to the collision box
         * in the x axis, used to compute a collision cube
         */
        Vector3D collision_boxing;
    public:
        virtual void draw();
        virtual void print();
        bool intersects(Shape s)
        {
            // compute shape's collision box
            array<Vector3D, 8> myBox = getCollisionBox();
            array<Vector3D, 8> otherBox = getCollisionBox();

            //detect if in the same height
            if(
                myBox[0].y <= otherBox[4].y && myBox[0].y >= otherBox[0].y ||
                myBox[4].y <= otherBox[4].y && myBox[4].y >= otherBox[0].y
            ) {
                // detect if inside XZ region, X inside, Z inside
                if(
                    (
                        myBox[0].x >= otherBox[1].x && myBox[0].x <= otherBox[0].x ||
                        myBox[1].x >= otherBox[1].x && myBox[1].x <= otherBox[0].x
                    ) &&
                    (
                        myBox[0].z >= otherBox[2].z && myBox[0].z <= otherBox[0].z ||
                        myBox[2].z >= otherBox[2].z && myBox[2].z <= otherBox[0].z
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
            float posX = geo_center.x + collision_boxing.x;
            float negX = geo_center.x - collision_boxing.x;
            float posZ = geo_center.z + collision_boxing.z;
            float negZ = geo_center.z - collision_boxing.z;
            float posY = geo_center.y + collision_boxing.y;
            float negY = geo_center.y - collision_boxing.y;

            // "-Y"
            arr[0] = Vector3D(posX, negY, negZ)
            arr[1] = Vector3D(negX, negY, negZ);
            arr[2] = Vector3D(negX, negY, posZ);
            arr[3] = Vector3D(posX, negY, posZ);
            // "+Y"
            arr[4] = Vector3D(posX, posY, negZ);
            arr[5] = Vector3D(negX, posY, negZ);
            arr[6] = Vector3D(negX, posY, posZ);
            arr[7] = Vector3D(posX, posY, posZ);
            return box;
        }

}

#endif