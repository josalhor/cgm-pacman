
#include "Engine.hpp"
#include "scenario/MapBuilder.hpp"
#include "scenario/MatrixFiller.hpp"
#include "utils/Matrix.hpp"
#include "utils/utils.hpp"
#include "framework/GameCell.hpp"
#include "TextureLoader.hpp"
#include <GL/glut.h>
#include <cstring>
#include <math.h>

#define PI M_PI
#define SIZE_CELL 50
#define WIDTH 1000
#define HEIGHT 1000
#ifdef PERSPECTIVE
#define CAMERA_DISTANCE 1750
#else
#define CAMERA_DISTANCE 700
#endif
#define SMOOTH_CAMERA_FACTOR 0.5
#define TEXT_FONT GLUT_BITMAP_TIMES_ROMAN_24
#define TEXT_FONT_HEIGHT 24



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
    engine = this;
    setupGame();
}

void Engine::run(){
    int argc = 0;
    glutInit(&argc, NULL);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowPosition(50, 50);
    int width = SIZE_CELL * this->matrix->width;
    int height = SIZE_CELL * this->matrix->height;
    glutInitWindowSize(width, height);
    glutCreateWindow("Amazing Pacman Game v2");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_MULTISAMPLE);  

    // glEnable(GL_LINE_SMOOTH), glEnable(GL_POLYGON_SMOOTH), glEnable(GL_POINT_SMOOTH);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glutDisplayFunc(displayOpenGL);
    glutIdleFunc(idleOpenGL);
    glutKeyboardFunc(keyboardOpenGL);
    glutSpecialFunc(specialFuncOpenGL);

    TextureLoader loader = TextureLoader();
    loader.loadTextures();

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

void Engine::PositionObserver(int radi)
{
    float beta = anglebeta;
    float alpha = anglealpha;
    float x,y,z;
    float upx,upy,upz;
    float modul;


    // code that computes x,y,z and upx,upy,upz and modul

    x = (float)radi*cos(alpha*2*PI/360.0)*cos(beta*2*PI/360.0);
    y = (float)radi*sin(beta*2*PI/360.0);
    z = (float)radi*sin(alpha*2*PI/360.0)*cos(beta*2*PI/360.0);
    cameraPosition = Vector3D(x, y, z);

    if (beta>0) { upx=-x; upz=-z; upy=(x*x+z*z)/y; }
    else if(beta==0) {  upx=0; upy=1; upz=0; }
    else { upx=x; upz=z; upy=-(x*x+z*z)/y; }

    modul=sqrt(upx*upx+upy*upy+upz*upz);

    upx=upx/modul;
    upy=upy/modul;
    upz=upz/modul;

    gluLookAt(x,y,z,    0.0, 0.0, 0.0,     upx,upy,upz);
}

void renderText(Vector3D cameraPosition, const char* text, float extraHeight, float extraX, float extraZ) {
    int width = glutBitmapLength(TEXT_FONT, (char unsigned*) text);

    int x = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int y = (glutGet(GLUT_WINDOW_HEIGHT) - 18) / 2;
    // x = mapper->XtoVisualFloat(x);
    // y = mapper->YtoVisualFloat(y);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(1, 0, 0);
    // glRasterPos3f(cameraPosition.getX(), cameraPosition.getY(), cameraPosition.getZ());
    // glRasterPos3f(0, 0, 0);
    glRasterPos3f(((float) cameraPosition.getX() + extraX) / 1.5f, ((float) cameraPosition.getY() + extraHeight) / 1.5f, (float) (cameraPosition.getZ() + extraZ) / 1.5f);
    // Loop through each character in the string
    for (int i = 0; i < strlen(text); i++) {
    // Render the character at the current raster position
        glutBitmapCharacter(TEXT_FONT, text[i]);
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void Engine::displayPreGame(){
    // Set the raster position to the specified coordinates
    const char text[100] = "Press SPACE to continue";
    renderText(cameraPosition, text, 0, -200, -200);
}

void Engine::displayEndGame()
{
    const char *result = (this->winner) ? "You WON\0" : "You Lost\0";
    const char replayMsg[100] = "Press SPACE to PLAY Again\0";
    renderText(cameraPosition, result, 60, -50, -200);
    renderText(cameraPosition, replayMsg, -60, -200, -200);
}

void Engine::displayScenario(){
    Matrix<GameCell>& matrix = *(this->matrix);
    CoordinateMapper& mapper = *(this->mapper);

    for (int y = 0; y < this->matrix->height; y++)
    {
        for (int x = 0; x < this->matrix->width; x++)
        {
            Cell current(x, y);
            GameCell& gc = matrix[current];
            gc.drawScenario();
        }
    }
}

void Engine::displayInGame(){
    Matrix<GameCell>& matrix = *(this->matrix);
    CoordinateMapper& mapper = *(this->mapper);

    for (int y = 0; y < this->matrix->height; y++)
    {
        for (int x = 0; x < this->matrix->width; x++)
        {
            Cell current(x, y);
            GameCell& gc = matrix[current];
            gc.draw();
        }
    }

}

void Engine::display(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_MULTISAMPLE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef PERSPECTIVE
    gluPerspective(45.0, (((float) glutGet(GLUT_WINDOW_WIDTH)) / ((float) glutGet(GLUT_WINDOW_HEIGHT))), 10, 3000);
#else
    glOrtho(-glutGet(GLUT_WINDOW_WIDTH)*0.6,glutGet(GLUT_WINDOW_WIDTH)*0.6,-glutGet(GLUT_WINDOW_HEIGHT)*0.6,glutGet(GLUT_WINDOW_HEIGHT)*0.6,10,2000);
#endif

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    PositionObserver(CAMERA_DISTANCE);


    glPolygonMode(GL_FRONT,GL_FILL);
    glPolygonMode(GL_BACK,GL_LINE);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    GLint position[4];
    GLfloat color[4];
    position[0]=0; position[1]=8; position[2]=0; position[3]=1; 
    glLightiv(GL_LIGHT0,GL_POSITION,position);
    color[0]=0.35; color[1]=0.35; color[2]=0.35; color[3]=0;
    glLightfv(GL_LIGHT0, GL_AMBIENT, color);
    glEnable(GL_LIGHT0);
    displayScenario();


    if (state == EngineState::InGame) {
        displayInGame();
    } else if(state == EngineState::PreGame) {
        displayPreGame();
    } else if(state == EngineState::PostGame){
        displayEndGame();
    }

    glutSwapBuffers();
}

void Engine::update(long t){
    if (state != EngineState::InGame) {
        return;
    }
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
    if(this->state == EngineState::InGame) {
        if (c == 'w'){
            this->keyboard(Direction::Up);
        } else if (c == 'd') {
            this->keyboard(Direction::Right);
        } else if (c == 's') {
            this->keyboard(Direction::Down);  
        } else if (c == 'a') {
        this->keyboard(Direction::Left);
        } else if (c=='i' && anglebeta<=(90-4)) {
            anglebeta=(anglebeta+3);
        } else if (c=='k' && anglebeta>=(-90+4)) {
            anglebeta=anglebeta-3;
        } else if (c=='j') {
            anglealpha=(anglealpha+3)%360;
        } else if (c=='l') {
            anglealpha=(anglealpha-3+360)%360;
        }
    }
    
    if(this->state != EngineState::InGame) {
        if (c==' ') {
            startGame();
            
        }
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

void Engine::destroyAll(){
    Matrix<GameCell>& matrix = *(this->matrix);

    for (int y = 0; y < this->matrix->height; y++)
    {
        for (int x = 0; x < this->matrix->width; x++)
        {
            Cell current(x, y);
            GameCell& gc = matrix[current];
            for(int z = gc.entities.size() - 1; z >= 0; z--){
                GameEntity* e = gc.entities[z];
                e->shapeClear();
                // update matrix
                gc.entities.erase(gc.entities.begin() + z);
                delete e;
            }
        }
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

void Engine::setEngineState(EngineState state){
    this->state = state;
}

void Engine::setupGame() {
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
            (*(this->matrix))[c] = GameCell(mapper, t, Vector2D(i, j));
        }
    }

    setEngineState(EngineState::PreGame);
}

void Engine::startGame() {
    // spawn pacman, phantoms and fruits
    //set game to InGame
    fillMatrix(*this, *(this->matrix), settings->phantoms);
    setEngineState(EngineState::InGame);
}

void Engine::endGame(bool winner) {
    this->winner = winner;
    anglealpha = 78;
    anglebeta = 51;
    destroyAll();
    setupGame();
    setEngineState(EngineState::PostGame);
}