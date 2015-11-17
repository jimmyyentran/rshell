CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic -g
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
	$(CC) $(CFLAGS) -c $< -o $@

# all: clean $(OBJ)
all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OBJDIR)/$(EXECUTABLE)

$(OBJ): | $(OBJDIR)

$(OBJDIR):
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
