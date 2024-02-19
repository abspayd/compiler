CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic
OBJS = token.o lexer.o parser.o
TARGET = compiler

all: $(TARGET)

$(TARGET): $(TARGET).c $(OBJS)
	$(CC) -g -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -rf *.o *.dSYM $(TARGET)
