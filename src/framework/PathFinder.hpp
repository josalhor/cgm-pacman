#ifndef PATHFINDER
#define PATHFINDER

#include <string>
#include <queue>
#include "utils/Matrix.hpp"
#include "utils/Cell.hpp"
#include "CellType.hpp"
#include "GameCell.hpp"
#include <algorithm>

using namespace std;
class SearchNode {
    public:
    Cell current;
    vector<Cell> previous;

    SearchNode(Cell current, vector<Cell> previous);
    SearchNode(Cell current);
    SearchNode addNode(Cell cell);
    vector<SearchNode> nextCells(Matrix<GameCell>& matrix);
};

class PathFinder {
    public:
    Matrix<GameCell>& matrix;
    PathFinder(Matrix<GameCell>& matrix);

    vector<Cell> searchOn(Cell base, string searching);
};

#endif