CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic
# CTEST = -Wall -ansi -pedantic
SRCDIR =  src
OBJDIR = bin
HEADERDIR = header
TESTDIR = tests
EXECUTABLE = rshell
CURSHELL = $(SHELL)
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
HEADER = $(wildcard $(SRCDIR)/$(HEADERDIR)/*.h)
TEST = $(wildcard $(TESTDIR)/*.sh)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	#1
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ)
	#2
	$(CC) $(CFLAGS) $(OBJ) -o $(OBJDIR)/$(EXECUTABLE)

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	#3
	@mkdir -p $(OBJDIR)

# Test only runs the first file..(all.sh)
test: $(TEST)
	@./$<

# compile and test
ct: all test

run:
	@./bin/rshell

clean:
	@rm -rf $(OBJDIR)
