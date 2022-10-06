#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <queue>

using namespace std;

enum MapCell { Wall, Corridor };

class Cell {
    public:
    int x;
    int y;
    Cell(int x, int y) {
        this->x = x;
        this->y = y;
    }

    bool operator==(const Cell &other) const
    { return (x == other.x && y == other.y); }

};

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

    void generateRandom() {
        // Randomly select a node (or cell) N.

        srand(time(NULL));   // Initialization, should only be called once.
        Cell randomCell(rand() % width, rand() % height);
        queue<Cell> first;
        // Push the node N onto a queue Q.
        first.push(randomCell);

        // Mark the cell N as visited.

        // Randomly select an adjacent cell A of node N that has not been visited. If all the neighbors of N have been visited:
            // Continue to pop items off the queue Q until a node is encountered with at least one non-visited neighbor - assign this node to N and go to step 4.
            // If no nodes exist: stop.
        // Break the wall between N and A.
        // Assign the value A to N.
        // Go to step 2.

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

int main(int argc, char** argv) {
    Map map(5, 10);

    map.print();
    map.generateRandom();
}