CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = main

SRC = main.c grafo_lista.c grafo_matriz.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)