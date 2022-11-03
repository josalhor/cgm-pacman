
#include "Engine.hpp"
#include "scenario/MapBuilder.hpp"
#include "scenario/MatrixFiller.hpp"
#include "utils/Matrix.hpp"
#include "utils/utils.hpp"
#include "framework/GameCell.hpp"
#include <GL/glut.h>

#define SIZE_CELL 50
#define WIDTH 1000
#define HEIGHT 1000

/*
This trick allows us to encapsulate all OpenGL
code in a class and map C API class to C++ methods
*/
Engine *engine;
void displayOpenGL()
{
    engine->display();
}

void idleOpenGl()
{
  engine->idle();
}


Engine::Engine() {

}

void Engine::setup(int columns, int rows){
    MapBuilder map(columns, rows);

    map.makeHouse();            // first insert the housing in the middle
    map.generateRandomRec();    // then explore the map and open it up
    map.postProcessGenerator(); // remove dead end parts in the map
    map.print();                // print the map in the console

    this->matrix = new Matrix<GameCell>(columns, rows);
    this->mapper = new CoordinateMapper(columns, rows, WIDTH, HEIGHT);
        
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
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

    fillMatrix(*this, *(this->matrix));

    engine = this;
}

void Engine::run(){
    int argc = 0;
    glutInit(&argc, NULL);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(SIZE_CELL * this->matrix->width, SIZE_CELL * this->matrix->height);
    glutCreateWindow("Amazing Pacman Game v2");

    glutDisplayFunc(displayOpenGL);
    glutIdleFunc(idleOpenGl);
    // glutKeyboardFunc(keyboard);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH - 1, 0, HEIGHT - 1);

    glutMainLoop();
}

void Engine::idle(){
    long t;

    t=glutGet(GLUT_ELAPSED_TIME);

    update();

    /*
    if(last_t==0) {
        last_t=t;
    }
    else
    {
        square.integrate(t-last_t);
        last_t=t;
    }*/


    glutPostRedisplay();
}

void Engine::display(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    Matrix<GameCell>& matrix = *(this->matrix);
    CoordinateMapper& mapper = *(this->mapper);

    for (int y = 0; y < this->matrix->height; y++)
    {
        for (int x = 0; x < this->matrix->width; x++)
        {
            Cell current(x, y);
            GameCell& gc = matrix[current];
            gc.draw(mapper);
        }
    }

    glutSwapBuffers();
}

void Engine::update(){
    Matrix<GameCell>& matrix = *(this->matrix);

    // update logic positions
    for (int y = 0; y < this->matrix->height; y++)
    {
        for (int x = 0; x < this->matrix->width; x++)
        {
            Cell current(x, y);
            GameCell& gc = matrix[current];
            gc.update();
        }
    }
    
    // update cells
    for (int y = 0; y < this->matrix->height; y++)
    {
        for (int x = 0; x < this->matrix->width; x++)
        {
            Cell current(x, y);
            GameCell& gc = matrix[current];
            for(int z = gc.entities.size() - 1; z >= 0; z--){
                GameEntity* e = gc.entities[z];
                Vector2D v = e->getPosition();

                Cell c = Cell(roundToInt(v.getX()), roundToInt(v.getY()));
                if (c.x != x || c.y != y){
                    // update matrix
                    gc.entities.erase(gc.entities.begin() + z);
                    matrix[c].entities.push_back(e);
                }
            }
        }
    }

    // update collisions
    for (int y = 0; y < this->matrix->height; y++)
    {
        for (int x = 0; x < this->matrix->width; x++)
        {
            Cell current(x, y);
            GameCell& gc = matrix[current];
            gc.detectCollision();
        }
    }
}


void Engine::destroy(GameEntity* entity){
    
}