CC = gcc
CFLAGS = -Wall -g

BIN = ./bin/
OBJ = ./obj/
INC = ./include/
SRC = ./src/

vpath %.c = ./src/
vpath %.o = ./obj/
vpath %.h = ./include/

main : main.o grille.o io.o jeu.o
	gcc $(CFLAGS) -o $(BIN)main $(OBJ)main.o $(OBJ)grille.o $(OBJ)io.o $(OBJ)jeu.o
io.o : io.c io.h grille.h jeu.h
main.o : main.c grille.h io.h jeu.h
grille.o : grille.c grille.h
jeu.o : jeu.c jeu.h grille.h

%.o : %.c
	$(CC) $(CFLAGS) -o $(OBJ)$@ -c $<

clean : 
	rm $(OBJ)*.o $(BIN)main 
docs: 
	doxygen Doxyfile
dist : 
	tar -f dist.tar.gz -cvz $(INC) $(SRC) $(OBJ) $(BIN) makefile Doxyfile
