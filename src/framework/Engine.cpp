
#include "Engine.hpp"
#include "scenario/MapBuilder.hpp"
#include "utils/Matrix.hpp"
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

Engine::Engine() {

}

void Engine::setup(int columns, int rows){
    MapBuilder map(columns, rows);

    map.makeHouse();            // first insert the housing in the middle
    map.generateRandomRec();    // then explore the map and open it up
    map.postProcessGenerator(); // remove dead end parts in the map
    map.print();                // print the map in the console

    this->matrix = new Matrix<GameCell>(columns, rows);
        
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
    // glutKeyboardFunc(keyboard);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH - 1, 0, HEIGHT - 1);

    glutMainLoop();
}

void Engine::display(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    Matrix<GameCell>& matrix = *(this->matrix);

    for (int y = 0; y < this->matrix->height; y++)
    {
        for (int x = 0; x < this->matrix->width; x++)
        {
            Cell current(x, y);
            
            CellType mCell = matrix[current].getCellType();
            bool printBlue = mCell == CellType::Wall || mCell == CellType::FixedWall;
            if (printBlue)
            {
                glColor3f(0, 0, 1);
            }
            else
            {
                glColor3f(1, 1, 1);
            }
            glBegin(GL_QUADS);

            glVertex2i(x * WIDTH / this->matrix->width, y * HEIGHT / this->matrix->height);
            glVertex2i((x + 1) * WIDTH / this->matrix->width, y * HEIGHT / this->matrix->height);
            glVertex2i((x + 1) * WIDTH / this->matrix->width, (y + 1) * HEIGHT / this->matrix->height);
            glVertex2i(x * WIDTH / this->matrix->width, (y + 1) * HEIGHT / this->matrix->height);

            glEnd();
        }
    }

    glutSwapBuffers();
}

void Engine::destroy(GameEntity entity){
    
}