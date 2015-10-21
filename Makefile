CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic
SRCDIR =  src
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJDIR = bin
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
HEADERDIR = header
HEADER = $(wildcard $(SRCDIR)/$(HEADERDIR)/*.h)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp ${HEADER}
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OBJDIR)/rshell

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

test:
	./tests/multi_command.sh

clean:
	@echo "Cleaning Up"
	rm -rf $(OBJDIR)
	rm -f all
