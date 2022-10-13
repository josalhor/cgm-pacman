#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <functional>
#include <optional>

#include <GL/glut.h>

#define SIZE_CELL 50
#define WIDTH 1000
#define HEIGHT 1000

void displayOpenGL();

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

template <typename T>
class MatrixValue {
    public:
    T ** matrix;
    int width;
    int height;

    MatrixValue(int width, int height, T def) {
        this->width = width;
        this->height = height;
        this->matrix = new T*[height];
        for (int i = 0; i < height; i++) {
            matrix[i] = new T[width];
            for (int j = 0; j < width; j++){
                matrix[i][j] = def;
            }
        }
    }

    ~MatrixValue() {
        for (int i = 0; i < height; i++) {
            delete matrix[i];
        }
        delete matrix;
    }

    bool validInBounds(Cell cell){
        return cell.validInBounds(width, height);
    }

    bool isPerimeter(Cell cell) {
        return cell.x == 0 || cell.x == width - 1 || cell.y == 0 || cell.y == height - 1;
    }

    T& operator[](Cell cell) {
        return matrix[cell.y][cell.x];
    }
};

class MapBuilder {
    public:
    MatrixValue<MapCell> map;

    MapBuilder(int width, int height) : map(MatrixValue<MapCell>(width, height, MapCell::Wall)) {}

    void print() {
        for (int y = 0; y < map.height; y++){
            for (int x = 0; x < map.width; x++) {
                char c;
                if (map.matrix[y][x] == MapCell::Wall){
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
        MatrixValue<MapCellVisit> visited(map.width, map.height, MapCellVisit::Unvisited);
        // Choose the initial cell

        srand(time(NULL));   // Initialization, should only be called once.
        Cell randomCell(1, 1);
        //srand(1);
        //Cell randomCell(4, 4);
        map[randomCell] = MapCell::Corridor;
        stack<Cell> stackCells;
        visited[randomCell] = MapCellVisit::Visited; // mark it as visited
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
                    !(map.validInBounds(corridor) &&
                    visited[corridor] == MapCellVisit::Unvisited)
            ){
                if (!map.validInBounds(corridor) &&
                    map.validInBounds(wall))
                {
                    visited[wall] = MapCellVisit::Visited;
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
            map[corridor] = MapCell::Corridor;
            map[wall] = MapCell::Corridor;
            // Mark the chosen cell as visited and push it to the stack
            visited[wall] = MapCellVisit::Visited;
            visited[corridor] = MapCellVisit::Visited;
            stackCells.push(corridor);
        }
    }

    void generateRandomRec() {
        MatrixValue<MapCellVisit> visited(map.width, map.height, MapCellVisit::Unvisited);
        // Choose the initial cell

        for (int x = 0; x < map.width; x++) {
            Cell up(x, 0);
            Cell down(x, map.height - 1);
            visited[up] = MapCellVisit::Visited;
            visited[down] = MapCellVisit::Visited;
        }

        for (int y = 0; y < map.height; y++) {
            Cell left(0, y);
            Cell right(map.width - 1, y);
            visited[left] = MapCellVisit::Visited;
            //visited[right] = MapCellVisit::Visited;
        }

        srand(time(NULL));
        Cell randomCell(1, 1);

        map[randomCell] = MapCell::Corridor;
        visited[randomCell] = MapCellVisit::Visited; // mark it as visited
        generateRandomRecInner(randomCell, visited);
    }

    void generateRandomRecInner(Cell currentCell, MatrixValue<MapCellVisit>& visited) {
        while (true) {
            // If the current cell has any neighbours which have not been visited
            visited[currentCell] = MapCellVisit::Visited; // mark it as visited
            int initialRandomIntDir = rand() % 4;
            Direction randomDirection = (Direction) (initialRandomIntDir);
            Cell wall = currentCell.move(randomDirection);
            Cell corridor = wall.move(randomDirection);
            int nextRandomIntDir = -1;
            while ( nextRandomIntDir != initialRandomIntDir &&
                    !(map.validInBounds(corridor) &&
                    visited[corridor] == MapCellVisit::Unvisited)
            ){
                if (!map.validInBounds(corridor) &&
                    map.validInBounds(wall))
                {
                    visited[wall] = MapCellVisit::Visited;
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
            map[corridor] = MapCell::Corridor;
            map[wall] = MapCell::Corridor;
            // Mark the chosen cell as visited and push it to the stack
            visited[wall] = MapCellVisit::Visited;
            visited[corridor] = MapCellVisit::Visited;
            generateRandomRecInner(corridor, visited);
        }
    }

    void postProcessGenerator() {
        for (int y = 0; y < map.height; y++) {
            for (int x = 0; x < map.width; x++){
                Cell current(x, y);
                if (map[current] == MapCell::Corridor){
                    int numWallsAround = 0;
                    for (int i = 0; i < 4; i++){
                        Direction d = (Direction) (i);
                        Cell next = current.move(d);
                        if (map.validInBounds(next) && map[next] == MapCell::Wall) {
                            numWallsAround++;
                        }
                    }

                    if (numWallsAround < 3) {
                        continue;
                    }

                    for (int i = 0; i < 4; i++){
                        Direction d = (Direction) (i);
                        Cell next = current.move(d);
                        if (map.validInBounds(next) && map[next] == MapCell::Wall && !map.isPerimeter(next)) {
                            map[next] = MapCell::Corridor;
                            break;
                        }
                    }
                }
            }
        }
    }

    MapBuilder symmetric() {
        bool isOdd = (map.width % 2) == 1;
        int newWidth = map.width * 2 - (isOdd ? 1 : 0);
        MapBuilder r = MapBuilder(newWidth, map.height);

        for (int y = 0; y < map.height; y++) {
            for (int x = 0; x < map.width; x++){
                if (x == map.width - 1 && isOdd) {
                    continue;
                }
                Cell current = Cell(x, y);
                Cell sym = Cell(r.map.width - x - 1, y);
                r.map[current] = map[current];
                r.map[sym] = map[current];
            }
        }

        return r;
    }
};

class MapPrinter {
    public:
    MatrixValue<MapCell>& map;
    MapPrinter(MatrixValue<MapCell>& generatedMap) : map(generatedMap) {
    }

    void initOpenGL() {
        int argc = 0;
        glutInit(&argc, NULL);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowPosition(50, 50);
        glutInitWindowSize(SIZE_CELL * map.width, SIZE_CELL * map.height);
        glutCreateWindow("Amazing Pacman Game");

        glutDisplayFunc(displayOpenGL);
        // glutKeyboardFunc(keyboard);

        glMatrixMode(GL_PROJECTION);
        gluOrtho2D(0,WIDTH-1,0,HEIGHT-1);

        glutMainLoop();
    }

    void display() {

        glClearColor(0.0,0.0,0.0,0.0);
        glClear(GL_COLOR_BUFFER_BIT);

        for(int y=0; y < map.height; y++){
            for(int x=0; x < map.width; x++){
                Cell current(x,y);
                bool printBlue = map[current] == MapCell::Wall;
                if (printBlue) {
                    glColor3f(0,0,1);
                } else {
                    glColor3f(1,1,1);
                }
                glBegin(GL_QUADS);
                
                glVertex2i(x*WIDTH/map.width,y*HEIGHT/map.height); 
                glVertex2i((x+1)*WIDTH/map.width,y*HEIGHT/map.height); 
                glVertex2i((x+1)*WIDTH/map.width,(y+1)*HEIGHT/map.height); 
                glVertex2i(x*WIDTH/map.width,(y+1)*HEIGHT/map.height); 

                glEnd();
            }
        }

        glutSwapBuffers();
    }

    
};

MapPrinter* mapPrinter;

void displayOpenGL()
{
  mapPrinter->display();

}

int main(int argc, char** argv) {

    if (argc < 3) {
        cout << "Use with: " << argv[0] << " <rows> <columns>" << "\n";
        exit(-1);
    }
    int rows = stoi(argv[1]);
    int columns = stoi(argv[2]);

    if (columns <= 10 || rows <= 10) {
        cout << "Minimum columns and rows is 11x11" << "\n";
        exit(-1);
    }

    if ((rows %2) == 0) {
        cout << "Rows must be an odd number" << "\n";
        exit(-1);
    }

    if ((columns %2) == 1) {
        cout << "Rows must be an even number" << "\n";
        exit(-1);
    }
    
    bool isEven = (columns % 2) == 0;
    int regionColumns = (columns / 2) + (isEven ? 0 : 1);

    MapBuilder map(regionColumns, rows);

    map.generateRandomRec();

    MapBuilder sym = map.symmetric();
    sym.postProcessGenerator();
    sym.print();
    MapPrinter mpPrinter(sym.map);

    mapPrinter = &mpPrinter;
    mpPrinter.initOpenGL();

}