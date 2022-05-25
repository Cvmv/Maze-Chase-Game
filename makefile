CC = g++
objects = Enemy.o Entry.o Funcs.o Game.o Globals.o Highscore.o KI.o Main.o Map.o Menu.o NewHighscore.o Object.o Player.o UI.o
LIBS = -lSDL2 -lSDL2_ttf
CFLAGS = -Wall
BINDIR = $(DESTDIR)/usr/bin

Game : $(objects)
	$(CC) -o Game $(objects) $(LIBS)

Main.o : src/Main.cpp Game.o Menu.o Highscore.o NewHighscore.o 
	$(CC) -c src/Main.cpp $(LIBS)

Game.o : src/Game.cpp Player.o Map.o KI.o Funcs.o UI.o
	$(CC) -c src/Game.cpp $(LIBS)

Menu.o : src/Menu.cpp Globals.o Funcs.o
	$(CC) -c src/Menu.cpp $(LIBS)

Highscore.o : src/Highscore.cpp Entry.o Funcs.o Globals.o 
	$(CC) -c src/Highscore.cpp $(LIBS)

NewHighscore.o : src/NewHighscore.cpp Globals.o Entry.o Funcs.o
	$(CC) -c src/NewHighscore.cpp $(LIBS)

Player.o : src/Player.cpp Globals.o Funcs.o KI.o
	$(CC) -c src/Player.cpp $(LIBS)

Enemy.o : src/Enemy.cpp Globals.o Funcs.o
	$(CC) -c src/Enemy.cpp $(LIBS)

Entry.o  : src/Entry.cpp Globals.o
	$(CC) -c src/Entry.cpp $(LIBS)

KI.o : src/KI.cpp Enemy.o
	$(CC) -c src/KI.cpp $(LIBS)

Map.o : src/Map.cpp Globals.o
	$(CC) -c src/Map.cpp $(LIBS)

UI.o : src/UI.cpp Globals.o
	$(CC) -c src/UI.cpp $(LIBS)

Funcs.o : src/Funcs.cpp Globals.o
	$(CC) -c src/Funcs.cpp $(LIBS)

Globals.o : src/Globals.cpp 
	$(CC) -c src/Globals.cpp $(LIBS)

Object.o : src/Object.cpp 
	$(CC) -c src/Object.cpp $(LIBS)

clean :
	rm $(objects)
