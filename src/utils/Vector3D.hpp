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
        Vector3D(){
            this->x = 0;
            this->y = 0;
            this->z = 0;
        }

        Vector3D(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        Vector3D operator +(Vector3D const &v)
        {
            return Vector3D(this->x + v.x, this->y + v.y, this->z + v.z);
        }

        Vector3D operator -(Vector3D const &v)
        {
            return Vector3D(this->x - v.x, this->y - v.y, this->z - v.z);
        }

        Vector3D operator *(float k)
        {
            return Vector3D(k * this->x, k * this->y, k * this->z);
        }

        // The dot product of two vectors is a scalar.
        float operator *(Vector3D const &v)
        {
            return ((this->x * v.x) + (this->y * v.y) + (this->z * v.z));
        }

        Vector3D crossProduct(Vector3D const &v)
        {
            float x = this->y * v.z - this->z * v.y;
            float y = -1*(this->x * v.z - this->z * v.x);
            float z = this->x * v.y - this->y * v.x;
            return Vector3D(x, y, z);
        }

        float getX(){
            return x;
        }

        float getY(){
            return y;
        }

        float getZ(){
            return z;
        }
};

#endif