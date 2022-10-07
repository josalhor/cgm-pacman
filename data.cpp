#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <functional>
#include <optional>

using namespace std;

enum MapCell { Wall, Corridor };
enum MapCellVisit { Unvisited, Visited };
enum Direction {
    Up = 0,
    Down = 1,
    Left = 2,
    Right = 3
};

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

    Cell move(Direction d) {
        switch (d)
        {
        case Direction::Up:
            return Cell(x, y + 1);
        case Direction::Down:
            return Cell(x, y - 1);
        case Direction::Left:
            return Cell(x - 1, y);
        case Direction::Right:
            return Cell(x + 1, y);
        default:
            return *this;
        }
    }

    bool validInBounds(int width, int height){
        return 0 <= x && x < width && 0 <= y && y < height;
    }
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
        MapCellVisit ** matrixVisit = new MapCellVisit*[height];
        for (int i = 0; i < height; i++) {
            matrixVisit[i] = new MapCellVisit[width];
                for (int j = 0; j < width; j++){
                    matrixVisit[i][j] = MapCellVisit::Unvisited;
            }
        }
        // Choose the initial cell

        srand(time(NULL));   // Initialization, should only be called once.
        Cell randomCell(rand() % width, rand() % height);
        //srand(1);
        //Cell randomCell(4, 4);
        matrix[randomCell.y][randomCell.x] = MapCell::Corridor;
        stack<Cell> stackCells;
        matrixVisit[randomCell.y][randomCell.x] = MapCellVisit::Visited; // mark it as visited
        stackCells.push(randomCell); // push it to the stack
        while (!stackCells.empty()){ // While the stack is not empty 
            Cell currentCell = stackCells.top(); // Pop a cell from the stack and make it a current cell
            stackCells.pop();
            // If the current cell has any neighbours which have not been visited
            int initialRandomIntDir = rand() % 4;
            Direction randomDirection = (Direction) (initialRandomIntDir);
            Cell wall = currentCell.move(randomDirection);
            Cell corridor = wall.move(randomDirection);
            int nextRandomIntDir = -1;
            while ( nextRandomIntDir != initialRandomIntDir &&
                    !(corridor.validInBounds(width, height) &&
                    matrixVisit[corridor.y][corridor.x] == MapCellVisit::Unvisited)
            ){
                if (!corridor.validInBounds(width, height) &&
                    wall.validInBounds(width, height))
                {
                    matrixVisit[wall.y][wall.x] = MapCellVisit::Visited;
                }
                nextRandomIntDir = nextRandomIntDir == -1 ? initialRandomIntDir + 1: nextRandomIntDir + 1;
                nextRandomIntDir = nextRandomIntDir % 4;
                randomDirection = (Direction) (nextRandomIntDir);
                wall = currentCell.move(randomDirection);
                corridor = wall.move(randomDirection);
            }


            if (nextRandomIntDir == initialRandomIntDir) {
                continue; // all nodes visited
                // Continue to pop items off the stack
            }

            // Push the current cell to the stack
            stackCells.push(currentCell);

            // Choose one of the unvisited neighbours
            // Remove the wall between the current cell and the chosen cell
            matrix[corridor.y][corridor.x] = MapCell::Corridor;
            matrix[wall.y][wall.x] = MapCell::Corridor;
            // Mark the chosen cell as visited and push it to the stack
            matrixVisit[wall.y][wall.x] = MapCellVisit::Visited;
            matrixVisit[corridor.y][corridor.x] = MapCellVisit::Visited;
            stackCells.push(corridor);
        }

        for (int i = 0; i < height; i++) {
            delete matrixVisit[i];
        }
        delete matrixVisit;
    }

    void generateRandomRec() {
        MapCellVisit ** matrixVisit = new MapCellVisit*[height];
        for (int i = 0; i < height; i++) {
            matrixVisit[i] = new MapCellVisit[width];
                for (int j = 0; j < width; j++){
                    matrixVisit[i][j] = MapCellVisit::Unvisited;
            }
        }
        // Choose the initial cell

        srand(time(NULL));   // Initialization, should only be called once.
        Cell randomCell(rand() % width, rand() % height);
        //srand(1);
        //Cell randomCell(4, 4);
        matrix[randomCell.y][randomCell.x] = MapCell::Corridor;
        matrixVisit[randomCell.y][randomCell.x] = MapCellVisit::Visited; // mark it as visited
        generateRandomRecInner(randomCell, matrixVisit);

        for (int i = 0; i < height; i++) {
            delete matrixVisit[i];
        }
        delete matrixVisit;
    }

    void generateRandomRecInner(Cell currentCell, MapCellVisit ** matrixVisit) {
        while (true) {
            // If the current cell has any neighbours which have not been visited
            matrixVisit[currentCell.y][currentCell.x] = MapCellVisit::Visited; // mark it as visited
            int initialRandomIntDir = rand() % 4;
            Direction randomDirection = (Direction) (initialRandomIntDir);
            Cell wall = currentCell.move(randomDirection);
            Cell corridor = wall.move(randomDirection);
            int nextRandomIntDir = -1;
            while ( nextRandomIntDir != initialRandomIntDir &&
                    !(corridor.validInBounds(width, height) &&
                    matrixVisit[corridor.y][corridor.x] == MapCellVisit::Unvisited)
            ){
                if (!corridor.validInBounds(width, height) &&
                    wall.validInBounds(width, height))
                {
                    matrixVisit[wall.y][wall.x] = MapCellVisit::Visited;
                }
                nextRandomIntDir = nextRandomIntDir == -1 ? initialRandomIntDir + 1: nextRandomIntDir + 1;
                nextRandomIntDir = nextRandomIntDir % 4;
                randomDirection = (Direction) (nextRandomIntDir);
                wall = currentCell.move(randomDirection);
                corridor = wall.move(randomDirection);
            }


            if (nextRandomIntDir == initialRandomIntDir) {
                return; // all nodes visited
            }

            // Choose one of the unvisited neighbours
            // Remove the wall between the current cell and the chosen cell
            matrix[corridor.y][corridor.x] = MapCell::Corridor;
            matrix[wall.y][wall.x] = MapCell::Corridor;
            // Mark the chosen cell as visited and push it to the stack
            matrixVisit[wall.y][wall.x] = MapCellVisit::Visited;
            matrixVisit[corridor.y][corridor.x] = MapCellVisit::Visited;
            generateRandomRecInner(corridor, matrixVisit);
        }
    }

    void postProcessGenerator() {
        for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++){
                    Cell current(x, y);
                    if (matrix[y][x] == MapCell::Corridor){
                        int numWallsAround = 0;
                        for (int i = 0; i < 4; i++){
                            Direction d = (Direction) (i);
                            Cell next = current.move(d);
                            if (next.validInBounds(width, height) && matrix[next.y][next.x] == MapCell::Wall) {
                                numWallsAround++;

                                if (numWallsAround == 3) {
                                    matrix[next.y][next.x] = MapCell::Corridor;
                                }
                            }
                        }
                    }
            }
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

int main(int argc, char** argv) {
    Map map(20, 20);

    map.generateRandomRec();
    map.postProcessGenerator();
    map.print();
}