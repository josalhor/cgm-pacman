#ifndef VECTOR_3D
#define VECTOR_3D

/*
 * This is how the 3D world is represented inside the project using openGL and Glut
 * therefore it is important to consider that the "normal plane" is the XZ plane
 *              ^ y
 *              |
 *              |
 *              | _ _ _  x
 *             / 
 *            /
 *           z
*/

class Vector3D {
    private:
        float x;
        float y;
        float z;
        
    public:
        Vector3D();

        Vector3D(float x, float y, float z);
        Vector3D operator +(Vector3D const &v);
        Vector3D operator -(Vector3D const &v);
        Vector3D operator *(float k);
        // The dot product of two vectors is a scalar.
        float operator *(Vector3D const &v);

        Vector3D crossProduct(Vector3D const &v);
        float getX();
        float getY();
        float getZ();
};

#endif