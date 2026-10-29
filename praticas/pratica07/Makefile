CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = main

OBJS = main.o bellman_ford.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c bellman_ford.h
	$(CC) $(CFLAGS) -c main.c

bellman_ford.o: bellman_ford.c bellman_ford.h
	$(CC) $(CFLAGS) -c bellman_ford.c

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean