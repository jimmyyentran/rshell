
SRC=$(filter-out %main.cpp, src/*)
OBJ=shell.o parser.o
# OBJDIR=bin
# OBJ=$(wildcard $OBJDIR/*.o)
# OBJ=$(pathsubst src/%.cpp, bin/%.o, $(SRC))
header=$(wildcard src/header/*.h)

vpath %.cpp src/

all: $(OBJ) main.cpp
	g++ -o output_file $^

# test: all
# ./grid_router Tests/test_sample.json

# bin/%.o: src/%.cpp ${header}
%.o: %.cpp ${header}
	g++ -c $^

cleanup:
	rm -f output_file
	rm -f *.o

# clean: cleanup
#	# rm -f lab2

