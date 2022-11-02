
#include "Engine.hpp"
#include "scenario/MapBuilder.hpp"
#include "utils/Matrix.hpp"
#include "framework/GameCell.hpp"

Engine::Engine() {

}

void Engine::setup(int columns, int rows){
    MapBuilder map(columns, rows);

    map.makeHouse();            // first insert the housing in the middle
    map.generateRandomRec();    // then explore the map and open it up
    map.postProcessGenerator(); // remove dead end parts in the map
    map.print();                // print the map in the console

    this->matrix = new Matrix<GameCell>(columns, rows);
    
    for (int i = 0; i < map.map.height; i++)
    {
        for (int j = 0; j < map.map.width; j++)
        {
            CellType t = CellType::Corridor;
            Cell c = Cell(i, j);
            CellType m = map.map[c];
            if (m == CellType::FixedWall || m == CellType::Wall){
                t = CellType::Wall;
            }
            (*(this->matrix))[c] = GameCell(t, Vector2D(i, j));
        }
    }
}

void Engine::run(){
    
}

void Engine::display(){
    
}

void Engine::destroy(GameEntity entity){
    
}