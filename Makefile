CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRCS = src/main.c src/lexer.c src/parser.c src/interpreter.c
OBJS = $(SRCS:.c=.o)
EXEC = uzbeklang

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
