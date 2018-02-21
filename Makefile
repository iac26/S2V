#Makefile

CFLAGS=-Wall

LIBS=-lncurses

all : game

game : main.o textures.o game.o
	gcc $(CFLAGS) main.o textures.o game.o -o $@ $(LIBS)
	
main.o : main.c game.h
	gcc $(CFLAGS) -c $< -o $@
	
textures.o : textures.c textures.h
	gcc $(CFLAGS) -c $< -o $@
	
game.o : game.c game.h textures.h
	gcc $(CFLAGS) -c $< -o $@ 
	
clean : 
	@rm -f *.x *.o
	@echo "CLEANED"
