#include <iostream>

using namespace std;

enum MapCell { Wall, Corridor };

class Map {
    public:
    MapCell ** matrix;
    int width;
    int height;

    Map(int width, int height) {
        this->width = width;
        this->height = height;
        this->matrix = new MapCell*[height];
        preGenerateMap();
    }

    void print() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++){
                char c;
                if (matrix[i][j] == MapCell::Wall){
                    c = '0';
                }  else {
                    c = ' ';
                }
                cout << c;
            }
            cout << "\n";
        }
    }

    private:
    void preGenerateMap() {
        for (int i = 0; i < height; i++) {
            matrix[i] = new MapCell[width];
                for (int j = 0; j < width; j++){
                    matrix[i][j] = MapCell::Wall;
            }
        }
    }
};

int main(int argc, char* argv) {
    Map map(5, 10);

    map.print();
}