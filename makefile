CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGET = printy
SRC = analisador_lexico.c analisador_semantico.c main.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

main.o: main.c analisador_lexico.h analisador_semantico.h
	$(CC) $(CFLAGS) -c main.c

analisador_lexico.o: analisador_lexico.c analisador_lexico.h
	$(CC) $(CFLAGS) -c analisador_lexico.c

analisador_semantico.o: analisador_semantico.c analisador_semantico.h analisador_lexico.h
	$(CC) $(CFLAGS) -c analisador_semantico.c

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean