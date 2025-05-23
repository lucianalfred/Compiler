CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGET = printy
SRC = analisador_lexico.c analisador_sintatico.c main.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

main.o: main.c analisador_lexico.h analisador_sintatico.h
	$(CC) $(CFLAGS) -c main.c

analisador_lexico.o: analisador_lexico.c analisador_lexico.h
	$(CC) $(CFLAGS) -c analisador_lexico.c

analisador_semantico.o: analisador_sintatico.c analisador_sintatico.h analisador_lexico.h
	$(CC) $(CFLAGS) -c analisador_semantico.c

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean