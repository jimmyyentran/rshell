CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic
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

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp ${HEADER}
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OBJDIR)/$(EXECUTABLE)

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

test:
	@./$(TEST)

# compile and test
ct: all test

clean:
	@rm -rf $(OBJDIR)
