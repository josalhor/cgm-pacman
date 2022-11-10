CP := $(shell find . -type f -iregex ".*\.cpp")
HP := $(shell find . -type f -iregex ".*\.hpp")
all:
	g++ $(HP) $(CP) -I. -o pacman -g -ggdb -lglut -lGLU -lGL -lm 

clean:
	rm -f pacman