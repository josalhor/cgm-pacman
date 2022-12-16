
#include "TextureLoader.hpp"
#include <vector>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "jpeglib.h"
using namespace std;

TextureLoader::TextureLoader() {
    
}

void TextureLoader::loadTextures() {
    vector<TextureMapping> toLoad;
    toLoad.push_back(TextureMapping {"textures/iloveimg-converted/TexturesCom_MarbleTiles0090_1_seamless_S.jpg", PACMAN_TEXTURE_INDEX});
    toLoad.push_back(TextureMapping {"textures/iloveimg-converted/TexturesCom_SlatePavement3_512_albedo_1.jpg", FLOOR_TEXTURE_INDEX});
    toLoad.push_back(TextureMapping {"textures/iloveimg-converted/TexturesCom_Wall_Stone3_2x2_512_albedo_1.jpg", WALL_TEXTURE_INDEX});
    toLoad.push_back(TextureMapping {"textures/iloveimg-converted/TexturesCom_Marble_Checkerboard2_512_albedo.jpg", ENEMY_TEXTURE_INDEX});
    toLoad.push_back(TextureMapping {"textures/mineral.jpg", FOOD_TEXTURE_INDEX});
    for(int i = 0; i < toLoad.size(); i++){
        glBindTexture(GL_TEXTURE_2D,toLoad[i].index);
        loadTexture(toLoad[i].path, 128);
    }
}

void TextureLoader::ReadJPEG(const char *filename,unsigned char **image,int *width, int *height) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE * infile;
    unsigned char **buffer;
    int i,j;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);


    if ((infile = fopen(filename, "rb")) == NULL) {
        printf("Unable to open file %s\n",filename);
        exit(1);
    }

    jpeg_stdio_src(&cinfo, infile);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_calc_output_dimensions(&cinfo);
    jpeg_start_decompress(&cinfo);

    *width = cinfo.output_width;
    *height  = cinfo.output_height;


    *image=(unsigned char*)malloc(cinfo.output_width*cinfo.output_height*cinfo.output_components);

    buffer=(unsigned char **)malloc(1*sizeof(unsigned char **));
    buffer[0]=(unsigned char *)malloc(cinfo.output_width*cinfo.output_components);


    i=0;
    while (cinfo.output_scanline < cinfo.output_height) {
        jpeg_read_scanlines(&cinfo, buffer, 1);

        for(j=0;j<cinfo.output_width*cinfo.output_components;j++)
        {
        (*image)[i]=buffer[0][j];
        i++;
        }   

        }

    free(buffer);
    jpeg_finish_decompress(&cinfo);
}

void TextureLoader::loadTexture(const char* path, int dim){
    unsigned char *buffer;
    unsigned char *buffer2;
    int width,height;
    long i,j;
    long k,h;

    ReadJPEG(path,&buffer,&width,&height);

    buffer2=(unsigned char*)malloc(dim*dim*3);

    //-- The texture pattern is subsampled so that its dimensions become dim x dim --
    for(i=0;i<dim;i++)
        for(j=0;j<dim;j++)
        {
        k=i*height/dim;
        h=j*width/dim;
        
        buffer2[3*(i*dim+j)]=buffer[3*(k*width +h)];
        buffer2[3*(i*dim+j)+1]=buffer[3*(k*width +h)+1];
        buffer2[3*(i*dim+j)+2]=buffer[3*(k*width +h)+2];

        }

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,dim,dim,0,GL_RGB,GL_UNSIGNED_BYTE,buffer2);

    free(buffer);
    free(buffer2);
}
