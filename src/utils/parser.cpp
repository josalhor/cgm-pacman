#include "./parser.hpp"

ArgParser::ArgParser(int argc, char **argv)
{
    this->argc = argc;
    this->argv = argv;
    this->setup = EngineSetup();
}

void ArgParser::invalid()
{
    cout << "Invalid command, please use --help / -h to get more information about how to run the program\n\n";
    exit(-1);
}

void ArgParser::parse()
{
    int c;
    bool parsedRows = false;
    bool parsedCols = false;

    // check parsing conditions
    preValidate();

    // parse input data
    while(true)
    {
        int option_index = 0;
        static struct option long_options[] = 
        {
        {"help",     no_argument, nullptr,     'h'},
        {"phantoms",     required_argument, nullptr,     0},
        {"verbose", no_argument, nullptr, 'v'},
        {"view",     required_argument, nullptr,     0},
        {NULL,      0,           NULL,       0}
        };

        c = getopt_long(argc, argv, "-:hv", long_options, &option_index);
        if(c == -1)
        {
            break;
        }

        switch (c)
        {
            case 0:
                if(long_options[option_index].name == "view")
                {
                    cout << "Parameter [view] ignored, NOT IMPLEMENTED YET\n";
                } else if (long_options[option_index].name == "phantoms")
                {
                    unsigned int phantoms = atoi(optarg);
                    if(phantoms >= 0 && phantoms <= 10)
                    {
                        this->setup.phantoms = phantoms;
                    } else {
                        invalid();
                    }
                }
                break;
            case 1:
                if(!parsedRows)
                {
                    this->setup.rows = atoi(optarg);
                    parsedRows = !parsedRows;
                } else if (!parsedCols)
                {
                    this->setup.cols = atoi(optarg);
                    parsedCols = !parsedCols;
                } else {
                    invalid();
                }
                break;
            case 'h':
                usage();
                break;
            case 'v':
                this->setup.verbose = true;
                cout << "INFO: Verbose mode activated\n";
                break;
            case '?':
                invalid();
                break;
            default:
                invalid();
                break;
        }
    }
    validate();
}

void ArgParser::preValidate()
{
    if(this->argc < 3 && this->argc != 2)
    {
        invalid();
    }
}

void ArgParser::usage()
{
    cout << "Use with: " << this->argv[0] << " <rows> <columns>\n";
    cout << "Additional options:\n";
    cout << "--phantoms: Select the number of enemies to spawn\n";
    cout << "--verbose: Provides additional information into the terminal\n";
    cout << "--view: Accepts 3 values: {'2d','3d', '3dT'}\n";
    cout << "-h,--help: Provides information about the program usage\n\n";
    exit(0);
}

void ArgParser::validate()
{
    bool valid = true;
    
    if(!hasMinimumAmount(17, this->setup.rows) || !hasMinimumAmount(23, this->setup.cols))
    {
        cout << "ERROR: The smallest map size posible is 17x23\n";
        valid = false;
    }

    if(!isOddInput(this->setup.rows) || !isOddInput(this->setup.cols))
    {
        cout << "ERROR: COLS and ROWS need to be an odd number!\n";
        valid = false;
    }

    if(!valid)
    {
        cout << "\tProvided:\n";
        cout << "\tROWS: " <<  this->setup.rows << "COLS: " << this->setup.cols << "\n";
        cout << "RESULT: Game " << this->argv[0] << " not started\n";
        cout << "SOLUTION: Please correct the validation errors shown\n";
        exit(-1);
    }
}
