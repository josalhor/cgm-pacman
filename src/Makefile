CP := $(shell find . -type f -iregex ".*\.cpp")
HP := $(shell find . -type f -iregex ".*\.hpp")
CFLAGS := -I. -o pacman -g -ggdb -lglut -lGLU -lGL -lm -ljpeg -O3

ifdef PERSPECTIVE
CFLAGS += -DPERSPECTIVE=$(PERSPECTIVE)
endif

all:
	g++ $(HP) $(CP) $(CFLAGS)

clean:
	find . -name "*.out" -type f -delete
	find . -name "*.d" -type f -delete
	find . -name "*.gch" -type f -delete
	rm -f pacman
	
