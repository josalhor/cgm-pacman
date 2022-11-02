#ifndef VECT2D
#define VECT2D

class Vector2D {
    private:
        float x;
        float y;
        
    public:
    Vector2D(){
        this->x = 0;
        this->y = 0;
    }

    Vector2D(float x, float y) {
        this->x + x;
        this->y = y;
    }

    Vector2D add(Vector2D& o){
        return Vector2D(
            this->x + o.x,
            this->y + o.y
        );
    }
};

#endif