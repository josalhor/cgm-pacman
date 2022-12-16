#ifndef COORDINATE_MAPPER
#define COORDINATE_MAPPER

#include "utils/utils.hpp"
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
        return XtoVisualWithoutCenter(x * opengl_width / width) - (opengl_width/2);
    }

    int XtoVisualWithoutCenter(int x) {
        return (x * opengl_width / width);
    }

    int YtoVisual(int y){
        return (y * opengl_height / height) + (opengl_height/2) ;
    }

    int YtoVisualWithoutCenter(int y){
        return (y * opengl_height / height) + (opengl_height/2) ;
    }

    int XtoVisual(float x) {
        return roundToInt(x * (float)opengl_width / (float)width - (opengl_width/2));
    }

    int XtoVisualWithoutCenter(float x) {
        return roundToInt(x * (float)opengl_width / (float)width);
    }

    int YtoVisual(float y){
        return roundToInt((y * (float)opengl_height / (float)height) + (opengl_height/2));
    }

    int YtoVisualWithoutCenter(float y){
        return roundToInt((y * (float)opengl_height / (float)height));
    }

    float XtoVisualFloat(float x) {
        return (x * (float)opengl_width / (float)width) - ((float) opengl_width / 2.0);
    }

    float XtoVisualFloatWithoutCenter(float x) {
        return (x * (float)opengl_width / (float)width);
    }

    float YtoVisualFloat(float y){
        return (y * (float)opengl_height / (float)height) + ((float) opengl_height / 2.0);
    }

    float YtoVisualFloatWithoutCenter(float y){
        return (y * (float)opengl_height / (float)height);
    }
};

#endif