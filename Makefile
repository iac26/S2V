#Makefile

CFLAGS=-Wall

LIBS=-lncurses

all : game.x

game.x : main.o textures.o game.o
	gcc $(CFLAGS) main.o textures.o game.o -o $@ $(LIBS)
	
main.o : main.c game.h
	gcc $(CFLAGS) -c $< -o $@ $(LIBS)
	
textures.o : textures.c textures.h
	gcc $(CFLAGS) -c $< -o $@
	
game.o : game.c game.h textures.h
	gcc $(CFLAGS) -c $< -o $@ $(LIBS)
	
clean : 
	@rm -f *.x *.o
	@echo "CLEANED"
