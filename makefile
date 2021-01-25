MAIN = $(wildcard src/*.cc)
IMGUI = $(wildcard include/imgui/*.cpp) include/imgui/backends/imgui_impl_sdl.cpp include/imgui/backends/imgui_impl_opengl3.cpp
BUILD = build
CC = g++
INCLUDES = -I ./include -I ./include/imgui -I ./include/imgui/backends
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
	FLAGS += $(shell sdl2-config --cflags --libs) $(shell pkg-config --libs glew)
endif



all: build

# Builds a Development Binary of the Application
build: prebuild
ifeq ($(wildcard $(BUILD)),)
	$(shell mkdir $(BUILD))
endif
	$(CC) $(MAIN) $(IMGUI) $(INCLUDES) $(FLAGS) -o $(OUT)
	$(info Building Binary)

# Cleans up the Build Directory
prebuild:
ifneq (,$(wildcard $(OUT)))
ifeq ($(OS),Windows_NT)
	$(info Windows Remove Pre-build)
	$(shell del /F /A $(OUT))
else
	$(info Removing Build Pre-build)
	rm $(OUT)
endif	
endif

# Cleans up everything
clean:
ifeq ($(OS),Windows_NT)
	$(info Windows Remove)
	$(shell rmdir /Q /S $(BUILD))
else
	$(info Removing Build)
	rm -rf $(BUILD)
endif