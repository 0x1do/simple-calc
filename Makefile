CC = clang
CFLAGS = -Wall -I./include -ggdb3 $(shell pkg-config --cflags glib-2.0)
LDFLAGS = $(shell pkg-config --libs glib-2.0)
SRC = src/main.c
EXEC = out
HEADER = include/calc.h


all: clean $(EXEC)

$(EXEC): $(SRC) $(HEADER)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC) $(LDFLAGS)

clean:
	rm -f $(EXEC)



CFLAGS = -Wall -I./include -ggdb3 $(shell pkg-config --cflags glib-2.0)
LDFLAGS = $(shell pkg-config --libs glib-2.0)






