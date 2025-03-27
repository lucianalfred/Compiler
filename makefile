CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGET = printy
SRC = main.c analisador_lexico.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c analisador_lexico.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean