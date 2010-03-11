program=piskvorky


HACKA=defines.h game.h human.h ai1.h ai2.h graphics.h 
OCKA=main.o ai1.o ai2.o game.o human.o graphics.o


FLAGS=-std=c99 -pedantic -Wall -g
#LIBS=-lSDL -lSDL_gfx
LIBS=-lSDL_gfx

build:$(program)

$(program): $(OCKA)
	gcc $(FLAGS) $(OCKA) $(LIBS) -o piskvorky

$(OCKA):$(HACKA)

main.o: main.c
	gcc $(FLAGS) main.c -c

ai1.o: ai1.c
	gcc $(FLAGS) ai1.c -c

ai2.o: ai2.c
	gcc $(FLAGS) ai2.c -c

game.o: game.c
	gcc $(FLAGS) game.c -c

human.o: human.c
	gcc $(FLAGS) human.c -c

graphics.o: graphics.c
	gcc $(FLAGS) graphics.c -c
