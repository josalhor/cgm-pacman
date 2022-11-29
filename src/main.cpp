#include "framework/Engine.hpp"
#include "utils/utils.hpp"
#include "utils/parser.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv){

    ArgParser parser = ArgParser(argc, argv);

    EngineSetup setup = parser.parse();

    cout << "ROWS: " << setup.rows << "\n";
    cout << "COLS: " << setup.cols << "\n";
    cout << "PHANTOMS: " << setup.phantoms << "\n";

    Engine engine = Engine();

    engine.setup(&setup);
    engine.run();
}