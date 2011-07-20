#
# (c) Garret Raziel and Alda (2010)
# released under GNU/GPL v.3,
# for further details, see LICENCE
#

program=gobango


HACKA=defines.h game.h human.h ai1.h ai2.h graphics.h 
OCKA=main.o ai1.o ai2.o game.o human.o graphics.o


CFLAGS:=$(CFLAGS) -std=c99 -pedantic -Wall
LIBS=-lSDL -lSDL_gfx

build:$(program)
all:$(program)

$(program): $(OCKA)
	$(CC) $(CFLAGS) $(OCKA) $(LIBS) -o $(program)

$(OCKA):$(HACKA)

main.o: main.c
	$(CC) $(CFLAGS) main.c -c

ai1.o: ai1.c
	$(CC) $(CFLAGS) ai1.c -c

ai2.o: ai2.c
	$(CC) $(CFLAGS) ai2.c -c

game.o: game.c
	$(CC) $(CFLAGS) game.c -c

human.o: human.c
	$(CC) $(CFLAGS) human.c -c

graphics.o: graphics.c
	$(CC) $(CFLAGS) graphics.c -c

clean:
	rm -f $(program) $(OCKA)
