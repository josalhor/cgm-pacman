#include <iostream>
#include "utils/Matrix.hpp"

using namespace std;

enum MapCell
{
    Wall,
    Corridor,
    FixedWall,
    Debug
};
enum MapCellVisit
{
    Unvisited,
    Visited
};

#define NUM_DIRECTIONS 4

#define HOUSE_WIDTH 4
#define HOUSE_HEIGHT 6


class MapBuilder
{
public:
    Matrix<MapCell> map;

    MapBuilder(int width, int height) : map(Matrix<MapCell>(width, height, MapCell::Wall)) {}

    void print()
    {
        for (int y = map.height - 1; y >= 0; y--)
        {
            for (int x = 0; x < map.width; x++)
            {
                char c;
                MapCell m = map.matrix[y][x];
                if (m == MapCell::Wall || m == MapCell::FixedWall)
                {
                    c = '0';
                }
                else if (m == MapCell::Corridor)
                {
                    c = ' ';
                }
                else
                {
                    c = 'X'; // for debug case
                }
                cout << c;
            }
            cout << "\n";
        }
    }

    void generateRandomRec()
    {
        Matrix<MapCellVisit> visited(map.width, map.height, MapCellVisit::Unvisited);
        /*
        Mark the external walls as "fixed"
        */
        for (int x = 0; x < map.width; x++)
        {
            Cell up(x, 0);
            Cell down(x, map.height - 1);

            setSymetric(up, MapCell::FixedWall, visited);
            setSymetric(down, MapCell::FixedWall, visited);
        }

        for (int y = 0; y < map.height; y++)
        {
            Cell left(0, y);
            Cell right(map.width - 1, y);
            setSymetric(left, MapCell::FixedWall, visited);
            setSymetric(right, MapCell::FixedWall, visited);
        }
        
        /*
        Mark Fixed Walls as visited
        */

        for (int x = 0; x < map.width; x++)
        {
            for (int y = 0; y < map.height; y++)
            {
                Cell current(x, y);
                if (map[current] == MapCell::FixedWall)
                {
                    visited[current] = MapCellVisit::Visited;
                }
            }
        }
        // The initial cell is the opening of the house
        // (so the opening can be accessed from anywhere)
        const int startHeight = (map.height / 2) + (HOUSE_HEIGHT / 2);
        const int startWidth = (map.width / 2);
        
        Cell openingHouse(startWidth, startHeight);
        map[openingHouse] = MapCell::Corridor;
        visited[openingHouse] = MapCellVisit::Visited;

        // generate recursively!
        srand(time(NULL));
        generateRandomRecInner(openingHouse, visited);
    }

    Cell getSymmetricCell(Cell &cell)
    {
        return Cell(map.width - cell.x - 1, cell.y);
    }

    void setSymetric(Cell &cell, MapCell value, Matrix<MapCellVisit> &visited)
    {
        Cell sym = getSymmetricCell(cell);
        setSymetric(cell, value);
        visited[cell] = MapCellVisit::Visited;
        visited[sym] = MapCellVisit::Visited;
    }

    void setSymetric(Cell &cell, MapCell value)
    {
        Cell sym = getSymmetricCell(cell);
        map[cell] = value;
        map[sym] = value;
    }

    void makeHouse()
    {
        // Insert housing in the middle
        const int startHeight = (map.height / 2) + (HOUSE_HEIGHT / 2);
        const int startWidth = (map.width / 2);

        Cell opening(startWidth, startHeight);
        map[opening] = MapCell::Corridor;
        int i = startHeight;
        int j = startWidth - 1;
        int leftLimit = startWidth - HOUSE_WIDTH;
        int downLimit = startHeight - HOUSE_HEIGHT;
        int rightLimit = startWidth + HOUSE_WIDTH;
        int upLimit = startHeight;

        /*
        Note that this could be very simplified with setSymmetric()
        but for reference, the full code is written
        */
        
        for (; j > leftLimit; j--)
        {
            Cell current(j, i);
            map[current] = MapCell::FixedWall;
        }
        for (; i > downLimit; i--)
        {
            Cell current(j, i);
            map[current] = MapCell::FixedWall;
        }
        for (; j < rightLimit; j++)
        {
            Cell current(j, i);
            map[current] = MapCell::FixedWall;
        }
        for (; i < upLimit; i++)
        {
            Cell current(j, i);
            map[current] = MapCell::FixedWall;
        }
        for (; j > startWidth; j--)
        {
            Cell current(j, i);
            map[current] = MapCell::FixedWall;
        }

        for (j = leftLimit + 1; j < rightLimit; j++)
        {
            for (i = downLimit + 1; i < upLimit; i++)
            {
                Cell current(j, i);
                map[current] = MapCell::Corridor;
            }
        }
    }

    void generateRandomRecInner(Cell currentCell, Matrix<MapCellVisit> &visited)
    {
        while (true)
        {
            // If the current cell has any neighbours which have not been visited
            visited[currentCell] = MapCellVisit::Visited; // mark it as visited
            int initialRandomIntDir = rand() % NUM_DIRECTIONS;
            Direction randomDirection = (Direction)(initialRandomIntDir);
            Cell wall = currentCell.move(randomDirection);
            Cell corridor = wall.move(randomDirection);
            int nextRandomIntDir = -1;
            
            // While we haven't found a movement to an unvisited cell...
            while (nextRandomIntDir != initialRandomIntDir &&
                   !(map.validInBounds(corridor) &&
                     visited[corridor] == MapCellVisit::Unvisited))
            {
                // loop through all possible movements deterministically
                if (!map.validInBounds(corridor) &&
                    map.validInBounds(wall))
                {
                    visited[wall] = MapCellVisit::Visited;
                }
                nextRandomIntDir = nextRandomIntDir == -1 ? initialRandomIntDir + 1 : nextRandomIntDir + 1;
                nextRandomIntDir = nextRandomIntDir % NUM_DIRECTIONS;
                randomDirection = (Direction)(nextRandomIntDir);
                wall = currentCell.move(randomDirection);
                corridor = wall.move(randomDirection);
            }

            // if we haven't found any available unvisited cell...
            if (nextRandomIntDir == initialRandomIntDir)
            {
                // finish searching and return (pop from call stack)
                return;
            }

            // Choose one of the unvisited neighbours
            // Remove the wall between the current cell and the chosen cell
            setSymetric(corridor, MapCell::Corridor, visited);
            setSymetric(wall, MapCell::Corridor, visited);
            // Note that this sets the values SYMETRICALLY!
            // This means that the resulting map will be symetrical
            // also, because the visited flag is also set symetrically there
            // is no unnecessary map exploration
            generateRandomRecInner(corridor, visited);
            // This implementation could be done in two ways:
            // call generateRandomRecInner again with the currentCell, or loop in a while True
            // both implementations are correct and should compile to the same machine code
        }
    }

    void postProcessGenerator()
    {
        bool changed = true;
        while (changed)
        {
            changed = postProcessGeneratorPass();
        }
    }

    bool postProcessGeneratorPass()
    {
        bool changedWall = false;
        for (int y = 0; y < map.height; y++)
        {
            for (int x = 0; x < map.width; x++)
            {
                Cell current(x, y);
                if (map[current] == MapCell::Corridor)
                {
                    int numWallsAround = 0;
                    for (int i = 0; i < 4; i++)
                    {
                        Direction d = (Direction)(i);
                        Cell next = current.move(d);
                        MapCell mc = map[next];
                        if (map.validInBounds(next) && mc == MapCell::Wall || mc == MapCell::FixedWall)
                        {
                            numWallsAround++;
                        }
                    }

                    if (numWallsAround < 3)
                    {
                        continue;
                    }

                    for (int i = 0; i < 4; i++)
                    {
                        Direction d = (Direction)(i);
                        Cell next = current.move(d);
                        if (map.validInBounds(next) && map[next] == MapCell::Wall)
                        {
                            setSymetric(next, MapCell::Corridor);
                            changedWall = true;
                            break;
                        }
                    }
                }
            }
        }

        return changedWall;
    }
};
