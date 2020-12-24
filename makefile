MAIN = $(wildcard src/*.cc)
BUILD = build
CC = g++
INCLUDES = -I ./include
FLAGS =
OUT = $(BUILD)/yagb-emu

# Windows / Linux Variables
ifeq ($(OS),Windows_NT)
$(info Windows Variables Init)
	INCLUDES += -I C:\MinGW\SDL2\include -L C:\MinGW\SDL2\lib\x86
    #FLAGS += -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2
    FLAGS += -w -lmingw32 -lSDL2main -lSDL2
else
$(info Non-Windows Variables Init)
	FLAGS += $(shell sdl2-config --cflags --libs)
endif

build:
ifeq ($(wildcard $(BUILD)),)
	$(shell mkdir $(BUILD))
endif
	$(CC) $(MAIN) $(INCLUDES) $(FLAGS) -o $(OUT)
	$(info Building Binary)

clean:
ifeq ($(OS),Windows_NT)
	$(info Windows Remove)
	$(shell rmdir /Q /S $(BUILD))
else
	$(info Removing Build)
	rm -rf $(BUILD)
endif