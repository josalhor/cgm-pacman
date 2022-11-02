CP := $(shell find . -type f -iregex ".*\.cpp")
HP := $(shell find . -type f -iregex ".*\.hpp")

all:
	echo $(CP) $(HP) 
	g++ $(CP) $(HP) -I. -o pacman
