CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic
OBJS = token.o
TARGET = lexer

all: $(TARGET)

$(TARGET): $(TARGET).c $(OBJS)
	$(CC) -g -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -rf *.o *.dSYM scanner
