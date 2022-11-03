#ifndef MAPBUILDER
#define MAPBUILDER
#include <iostream>
#include "utils/Matrix.hpp"
#include "framework/CellType.hpp"
#include "MapConstants.hpp"

using namespace std;

enum CellTypeVisit
{
    Unvisited,
    Visited
};

class MapBuilder
{
public:
    Matrix<CellType> map;

    MapBuilder(int width, int height) : map(Matrix<CellType>(width, height, CellType::Wall)) {}

    void print()
    {
        for (int y = map.height - 1; y >= 0; y--)
        {
            for (int x = 0; x < map.width; x++)
            {
                char c;
                CellType m = map.matrix[y][x];
                if (m == CellType::Wall || m == CellType::FixedWall)
                {
                    c = '0';
                }
                else if (m == CellType::Corridor || m == CellType::FixedCorridor)
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
        Matrix<CellTypeVisit> visited(map.width, map.height, CellTypeVisit::Unvisited);
        /*
        Mark the external walls as "fixed"
        */
        for (int x = 0; x < map.width; x++)
        {
            Cell up(x, 0);
            Cell down(x, map.height - 1);

            setSymetric(up, CellType::FixedWall, visited);
            setSymetric(down, CellType::FixedWall, visited);
        }

        for (int y = 0; y < map.height; y++)
        {
            Cell left(0, y);
            Cell right(map.width - 1, y);
            setSymetric(left, CellType::FixedWall, visited);
            setSymetric(right, CellType::FixedWall, visited);
        }
        
        /*
        Mark Fixed Walls as visited
        */

        for (int x = 0; x < map.width; x++)
        {
            for (int y = 0; y < map.height; y++)
            {
                Cell current(x, y);
                if (map[current] == CellType::FixedWall || map[current] == CellType::FixedCorridor)
                {
                    visited[current] = CellTypeVisit::Visited;
                }
            }
        }
        // The initial cell is the opening of the house
        // (so the opening can be accessed from anywhere)
        const int startHeight = (map.height / 2) + (HOUSE_HEIGHT / 2);
        const int startWidth = (map.width / 2);
        
        Cell openingHouse(startWidth, startHeight);
        map[openingHouse] = CellType::Corridor;
        visited[openingHouse] = CellTypeVisit::Visited;

        // generate recursively!
        srand(time(NULL));
        generateRandomRecInner(openingHouse, visited);
    }

    Cell getSymmetricCell(Cell &cell)
    {
        return Cell(map.width - cell.x - 1, cell.y);
    }

    void setSymetric(Cell &cell, CellType value, Matrix<CellTypeVisit> &visited)
    {
        Cell sym = getSymmetricCell(cell);
        setSymetric(cell, value);
        visited[cell] = CellTypeVisit::Visited;
        visited[sym] = CellTypeVisit::Visited;
    }

    void setSymetric(Cell &cell, CellType value)
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
        map[opening] = CellType::Corridor;
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
            map[current] = CellType::FixedWall;
        }
        for (; i > downLimit; i--)
        {
            Cell current(j, i);
            map[current] = CellType::FixedWall;
        }
        for (; j < rightLimit; j++)
        {
            Cell current(j, i);
            map[current] = CellType::FixedWall;
        }
        for (; i < upLimit; i++)
        {
            Cell current(j, i);
            map[current] = CellType::FixedWall;
        }
        for (; j > startWidth; j--)
        {
            Cell current(j, i);
            map[current] = CellType::FixedWall;
        }

        for (j = leftLimit + 1; j < rightLimit; j++)
        {
            for (i = downLimit + 1; i < upLimit; i++)
            {
                Cell current(j, i);
                map[current] = CellType::FixedCorridor;
            }
        }
    }

    void generateRandomRecInner(Cell currentCell, Matrix<CellTypeVisit> &visited)
    {
        while (true)
        {
            // If the current cell has any neighbours which have not been visited
            visited[currentCell] = CellTypeVisit::Visited; // mark it as visited
            int initialRandomIntDir = rand() % NUM_DIRECTIONS;
            Direction randomDirection = (Direction)(initialRandomIntDir);
            Cell wall = currentCell.move(randomDirection);
            Cell corridor = wall.move(randomDirection);
            int nextRandomIntDir = -1;
            
            // While we haven't found a movement to an unvisited cell...
            while (nextRandomIntDir != initialRandomIntDir &&
                   !(map.validInBounds(corridor) &&
                     visited[corridor] == CellTypeVisit::Unvisited))
            {
                // loop through all possible movements deterministically
                if (!map.validInBounds(corridor) &&
                    map.validInBounds(wall))
                {
                    visited[wall] = CellTypeVisit::Visited;
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
            setSymetric(corridor, CellType::Corridor, visited);
            setSymetric(wall, CellType::Corridor, visited);
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
                if (map[current] == CellType::Corridor)
                {
                    int numWallsAround = 0;
                    for (int i = 0; i < 4; i++)
                    {
                        Direction d = (Direction)(i);
                        Cell next = current.move(d);
                        CellType mc = map[next];
                        if (map.validInBounds(next) && mc == CellType::Wall || mc == CellType::FixedWall)
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
                        if (map.validInBounds(next) && map[next] == CellType::Wall)
                        {
                            setSymetric(next, CellType::Corridor);
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

#endif