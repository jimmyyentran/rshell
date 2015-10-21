
SRC=$(filter-out %main.cpp, src/*)
OBJ=shell.o parser.o
header=$(wildcard src/header/*.h)


vpath %.cpp src/

all: $(OBJ) main.cpp
	g++ -o output_file $^

# test: all
# ./grid_router Tests/test_sample.json

%.o: %.cpp ${header}
	g++ -c $^

# car.o:
# g++ -c car.cpp

cleanup:
	rm -f output_file
	rm -f *.o

# clean: cleanup
#	# rm -f lab2

