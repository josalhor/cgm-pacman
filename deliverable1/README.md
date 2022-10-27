# cgm-pacman-1

## Authors
[Josep Maria Salvia Hornos](https://github.com/josalhor)

[Joan Palau Oncins](https://github.com/JoanPalau)

## Dependencies
- freeglut3-dev
- freeglut3
- binutils-gold

## How to execute the program
The repository provides a Makefile which will allow you to compile the C++ code. In order to do so, just introduce the following command line:

`make`

In order to execute the code, use the following command:

`./pacman <rows> <columns>`

## Map generator limitations
The map generation has the following constraints:
- The grid **MUST** be at least 17x23.
- **Both, rows and columns** need to be an **odd number**

## First delivery

### Problems faced
- Lack of time
- Instalation of wsl ubuntu
- The generation of the map is more tricky than what one may initialy have thought
- How to call our display method using the glutDisplayFunc
- 2D and console displayed verions do not match

### Implementation
**Global functions**

- **main**: inside the main function we implemented the argument validation and the secuential execution of the diferent object methods in order to display the pacman maze in 2D
- **displayOpenGL**: global function that serves a strategic solution in order to enable calling the mapPrinter display method using glutDisplayFunc

**Enums**

In order to have consistent values across the different classes developed, we decided to implement the following enums:
- MapCell: type of cell
- MapCellVisited: contains the values that atribute to a cell if it has been visited or not
- Direction: where is the next connected cell located from the cell selected

**Classes**
- Cell: class that defines the most "basic data structure used" to generate the map
- MatrixValue: class that defines the data structure used to generate the map
- MapBuilder: class that encapsulates all the methods used in order to generate and post-process the map
- MapPrinter: class that contains encapsulates the complexity of displaying the map using openGL
