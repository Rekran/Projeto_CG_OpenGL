CC = g++

all:
	$(CC) object.cpp display.cpp objloader.cpp main.cpp -lGLEW -lGLU -lGL -I  -lSDL2main -lSDL2 -lassimp -o cgprog

clean:
	rm cgprog

