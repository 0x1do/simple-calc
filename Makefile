CC = clang
CFLAGS = -Wall -I./include -ggdb3
SRC = src/main.c
EXEC = out
HEADER = include/calc.h


all: clean $(EXEC)

$(EXEC): $(SRC) $(HEADER)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

clean:
	rm -f $(EXEC)
