# Basic comands

## Compile with:
Go to the src folder and execute the following command:

```
make
```

## See options with:

```
./pacman --help
```

## Run with default settings:

```
./pacman 17 23
```

## Custom phantom number

```
./pacman 17 23 --phantoms=8
```

# Advanced usage

In this last delivery we have observed quite an interesting behaviour due to the prespective we are using.

In real life, we trend to see objects further down in the distance smaller than objects that are close to us, with the default setting taught and provided this is not the case. 

By default we are using **glOrtho** which tries to preserve the same proportionality between the different objects rendered, therefore not being accurate to what we would expect in reality.

As an alternative, we are providing the option of rendering the Pacman game using **gluPerspective** which will provide a more realistic prespective from their POV to the user. In order to enable this feature please use the following command when compiling the project:
```
make PRESPECTIVE=1
```
