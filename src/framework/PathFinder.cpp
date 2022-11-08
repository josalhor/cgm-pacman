#include "PathFinder.hpp"
#include "scenario/MapBuilder.hpp"
using namespace std;

SearchNode::SearchNode(Cell current) : current(current) {
}

SearchNode::SearchNode(Cell current, vector<Cell> previous) : current(current), previous(previous) {
}

SearchNode SearchNode::addNode(Cell cell){
    vector<Cell> p(previous);
    p.push_back(cell);
    return SearchNode(cell, p);
}

vector<SearchNode> SearchNode::nextCells(Matrix<GameCell>& matrix){
    vector<SearchNode> cells;
    for(int i = 0; i < NUM_DIRECTIONS; i++){
        Direction d = (Direction)(i);
        Cell next = current.move(d);
        CellType mc = matrix[next].getCellType();
        if (matrix.validInBounds(next) && mc != CellType::Wall && mc != CellType::FixedWall)
        {
            cells.push_back(addNode(next));
        }
    }
    return cells;
}
   

PathFinder::PathFinder(Matrix<GameCell>& matrix) : matrix(matrix) {

}

vector<Cell> PathFinder::searchOn(Cell base, string searching){
    queue<SearchNode> q;
    Matrix<CellTypeVisit> visited(matrix.width, matrix.height, CellTypeVisit::Unvisited);
    visited[base] = CellTypeVisit::Visited;
    q.push(SearchNode(base));
    while(!q.empty()) {
        SearchNode current = q.front();
        q.pop();
        vector<SearchNode> cells = current.nextCells(matrix);
        for(int i = 0; i < cells.size(); i++){
            SearchNode node = cells[i];
            if (visited[node.current] == CellTypeVisit::Visited){
                continue;
            }
            GameCell cell = matrix[node.current];
            if (cell.containsEntity(searching)){
                return node.previous;
            }
            // cout << node.current.x << " " << node.current.y << endl;
            visited[node.current] = CellTypeVisit::Visited;
            q.push(node);
        }
    }
    vector<Cell> cells;
    return cells;
}