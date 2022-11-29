CL := $(shell find . -type f -iregex ".*\.c")
CP := $(shell find . -type f -iregex ".*\.cpp")
HP := $(shell find . -type f -iregex ".*\.hpp")
all:
	gcc $(CL) -I. -o pacman -g -ggdb -lglut -lGLU -lGL -lm 

clean:
	rm -f pacman