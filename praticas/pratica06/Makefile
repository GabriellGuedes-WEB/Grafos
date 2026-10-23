CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11
TARGET = main
SOURCES = main.c dijkstra.c
HEADERS = dijkstra.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe