# Project Variables
CC = g++
FLAGS = -I include
SDL_FLAG = -lSDL2
MAIN = src/main.cc
OUT = app


all: build

build:
	$(CC) $(FLAGS) $(SDL_FLAG) $(MAIN) -o $(OUT)

clean:
	rm $(OUT)