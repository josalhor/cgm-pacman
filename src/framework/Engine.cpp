
#include "Engine.hpp"
#include "scenario/MapBuilder.hpp"
#include "scenario/MatrixFiller.hpp"
#include "utils/Matrix.hpp"
#include "utils/utils.hpp"
#include "framework/GameCell.hpp"
#include <GL/glut.h>
#include <math.h>

#define PI M_PI
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

void idleOpenGL()
{
  engine->idle();
}

void keyboardOpenGL(unsigned char c,int x,int y)
{
  engine->keyboard(c);
}

void specialFuncOpenGL(int key, int x, int y)
{
    engine->specialFunc(key);
}


Engine::Engine() {

}

CellType Engine::getCellType(Cell cell) {
    return (*(this->matrix))[cell].getCellType();
}

void Engine::setup(EngineSetup* setup){
    settings = setup;
    int columns = settings->cols;
    int rows = settings->rows;
    MapBuilder map(columns, rows);

    map.makeHouse();            // first insert the housing in the middle
    map.generateRandomRec();    // then explore the map and open it up
    map.postProcessGenerator(); // remove dead end parts in the map
    map.print();                // print the map in the console

    this->matrix = new Matrix<GameCell>(columns, rows);
    this->pathFinder = new PathFinder(*matrix);
    this->mapper = new CoordinateMapper(columns, rows, WIDTH, HEIGHT);
        
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            Cell c = Cell(i, j);
            CellType m = map.map[c];
            CellType t = m;
            if (m == CellType::FixedWall || m == CellType::Wall){
                t = CellType::Wall;
            }
            (*(this->matrix))[c] = GameCell(t, Vector2D(i, j));
        }
    }

    fillMatrix(*this, *(this->matrix), settings->phantoms);

    engine = this;
}

void Engine::run(){
    int argc = 0;
    glutInit(&argc, NULL);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(SIZE_CELL * this->matrix->width, SIZE_CELL * this->matrix->height);
    glutCreateWindow("Amazing Pacman Game v2");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(displayOpenGL);
    glutIdleFunc(idleOpenGL);
    glutKeyboardFunc(keyboardOpenGL);
    glutSpecialFunc(specialFuncOpenGL);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH - 1, 0, HEIGHT - 1);

    glutMainLoop();
}

void Engine::idle(){
    long t;

    t=glutGet(GLUT_ELAPSED_TIME);

    if(last_t==0) {
        last_t=t;
    }
    else
    {
        update(t-last_t);
        last_t=t;
    }

    glutPostRedisplay();
}

void PositionObserver(float alpha,float beta,int radi)
{
  float x,y,z;
  float upx,upy,upz;
  float modul;

  x = (float)radi*cos(alpha*2*PI/360.0)*cos(beta*2*PI/360.0);
  y = (float)radi*sin(beta*2*PI/360.0);
  z = (float)radi*sin(alpha*2*PI/360.0)*cos(beta*2*PI/360.0);

  if (beta>0)
    {
      upx=-x;
      upz=-z;
      upy=(x*x+z*z)/y;
    }
  else if(beta==0)
    {
      upx=0;
      upy=1;
      upz=0;
    }
  else
    {
      upx=x;
      upz=z;
      upy=-(x*x+z*z)/y;
    }


  modul=sqrt(upx*upx+upy*upy+upz*upz);

  upx=upx/modul;
  upy=upy/modul;
  upz=upz/modul;

  gluLookAt(x,y,z,    0.0, 0.0, 0.0,     upx,upy,upz);
}

/*--- Global variables that determine the viewpoint location ---*/
int anglealpha = 90;
int anglebeta = 30;


void Engine::display(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    //glClearColor(1.0,1.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    PositionObserver(anglealpha,anglebeta,450);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH*0.6,WIDTH*0.6,-HEIGHT*0.6,HEIGHT*0.6,10,2000);

    glMatrixMode(GL_MODELVIEW);

    glPolygonMode(GL_FRONT,GL_FILL);
    glPolygonMode(GL_BACK,GL_LINE);
    Matrix<GameCell>& matrix = *(this->matrix);
    CoordinateMapper& mapper = *(this->mapper);

    for (int y = 0; y < this->matrix->height; y++)
    {
        for (int x = 0; x < this->matrix->width; x++)
        {
            Cell current(x, y);
            GameCell& gc = matrix[current];
            gc.drawScenario(mapper);
        }
    }

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

void Engine::update(long t){
    Matrix<GameCell>& matrix = *(this->matrix);

    // update logic positions
    for (int y = 0; y < this->matrix->height; y++)
    {
        for (int x = 0; x < this->matrix->width; x++)
        {
            Cell current(x, y);
            GameCell& gc = matrix[current];
            gc.update(t);
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

void Engine::keyboard(Direction d){
    Matrix<GameCell>& matrix = *(this->matrix);
    for (int y = 0; y < this->matrix->height; y++)
    {
        for (int x = 0; x < this->matrix->width; x++)
        {
            Cell current(x, y);
            GameCell& gc = matrix[current];
            gc.receiveKeyboard(d);
        }
    }
}

void Engine::keyboard(unsigned char c){
    Direction d = (Direction) -1;
    if (c == 'w'){
        d = Direction::Up;
    } else if (c == 'd') {
        d = Direction::Right;
    } else if (c == 's') {
        d = Direction::Down;  
    } else if (c == 'a') {
        d = Direction::Left;
    }
      int i,j;

    if (c=='i' && anglebeta<=(90-4))
        anglebeta=(anglebeta+3);
    else if (c=='k' && anglebeta>=(-90+4))
        anglebeta=anglebeta-3;
    else if (c=='j')
        anglealpha=(anglealpha+3)%360;
    else if (c=='l')
        anglealpha=(anglealpha-3+360)%360;
    if (d != -1) {
        this->keyboard(d);
    }
}

void Engine::specialFunc(int c){
    Direction d = (Direction) -1;
    if (c == GLUT_KEY_UP){
        d = Direction::Up;
    } else if (c == GLUT_KEY_RIGHT) {
        d = Direction::Right;
    } else if (c == GLUT_KEY_DOWN) {
        d = Direction::Down;  
    } else if (c == GLUT_KEY_LEFT) {
        d = Direction::Left;
    }
    if (d != -1) {
        this->keyboard(d);
    }
}


void Engine::destroy(GameEntity* entity){
    Matrix<GameCell>& matrix = *(this->matrix);

    for (int y = 0; y < this->matrix->height; y++)
    {
        for (int x = 0; x < this->matrix->width; x++)
        {
            Cell current(x, y);
            GameCell& gc = matrix[current];
            for(int z = gc.entities.size() - 1; z >= 0; z--){
                GameEntity* e = gc.entities[z];
                if (e == entity){
                    // update matrix
                    gc.entities.erase(gc.entities.begin() + z);
                }
            }
        }
    }

    delete entity;
}

vector<Cell> Engine::pathTo(Cell base, string name){
    return pathFinder->searchOn(base, name);
}