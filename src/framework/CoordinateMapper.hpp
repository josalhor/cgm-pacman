#ifndef COORDINATE_MAPPER
#define COORDINATE_MAPPER

class CoordinateMapper
{
    public:
    int width;
    int height;
    int opengl_width;
    int opengl_height;

    CoordinateMapper(int width, int height, int opengl_width, int opengl_height) : width(width), height(height), opengl_width(opengl_width), opengl_height(opengl_height)
    {
    }

    int XtoVisual(int x) {
        return x * opengl_width / width;
    }

    int YtoVisual(int y){
        return y * opengl_height / height;
    }
};

#endif