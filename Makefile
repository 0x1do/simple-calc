CC = clang
CFLAGS = -Wall -I./include -g
SRC = src/main.c
EXEC = out
HEADER = include/calc.h


all: clean $(EXEC)

$(EXEC): $(SRC) $(HEADER)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

clean:
	rm -f $(EXEC)