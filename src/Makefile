CP := $(shell find . -type f -iregex ".*\.cpp")
HP := $(shell find . -type f -iregex ".*\.hpp")
all:
	g++ $(CP) $(HP) -I. -o pacman -g -ggdb -lglut -lGLU -lGL -lm 
