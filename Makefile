CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic
SRC = $(wildcard src/*.cpp)
OBJDIR = bin
OBJ = $(patsubst src/%.cpp, $(OBJDIR)/%.o, $(SRC))

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o all

$(OBJDIR)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	rm -f all
