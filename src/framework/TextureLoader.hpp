#ifndef TEXTURELOADER
#define TEXTURELOADER

#define PACMAN_TEXTURE_INDEX 1
#define FLOOR_TEXTURE_INDEX 2
#define WALL_TEXTURE_INDEX 3
#define ENEMY_TEXTURE_INDEX 4
#define FOOD_TEXTURE_INDEX 5

typedef struct
{
    const char* path;
    const int index;
} TextureMapping;

class TextureLoader {
    private:
    void loadTexture(const char* path, int dim);
    void ReadJPEG(const char *filename,unsigned char **image,int *width, int *height);
    public:
    TextureLoader();
    void loadTextures();
};

#endif