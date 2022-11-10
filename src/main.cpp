#include "framework/Engine.hpp"
#include "utils/utils.hpp"
#include "utils/parser.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv){
    if (argc < 3)
    {
        cout << "Use with: " << argv[0] << " <rows> <columns>"
             << "\n";
        exit(-1);
    }
    int rows = stoi(argv[1]);
    int columns = stoi(argv[2]);
    /*
    Parse Args
    */

    if (columns < 23 || rows < 17)
    {
        cout << "Minimum columns and rows is 17x23"
             << "\n";
        exit(-1);
    }

    if ((rows % 2) == 0)
    {
        cout << "Rows must be an odd number"
             << "\n";
        exit(-1);
    }

    if ((columns % 2) == 0)
    {
        cout << "Columns must be an odd number"
             << "\n";
        exit(-1);
    }

    ArgParser parser = ArgParser(argc, argv);

    EngineSetup setup = parser.parse();

    cout << "ROWS: " << setup.rows << "\n";
    cout << "COLS: " << setup.cols << "\n";
    cout << "PHANTOMS: " << setup.phantoms << "\n";

    Engine engine = Engine();

    engine.setup(columns, rows);
    engine.run();
}