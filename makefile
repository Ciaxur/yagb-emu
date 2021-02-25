MAIN = $(wildcard src/*.cc)
SRC = src/main.cc
IMGUI = $(wildcard include/imgui/*.cpp) include/imgui/backends/imgui_impl_sdl.cpp include/imgui/backends/imgui_impl_opengl3.cpp
BUILD = build
CC = g++
INCLUDE_PATHS = ./include ./include/imgui ./include/imgui/backends ./include/imgui_club
INCLUDES = $(addprefix -I, $(INCLUDE_PATHS))
FLAGS = -Wall
OUT = $(BUILD)/yagb-emu
CACHE = $(BUILD)/cache

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

build-debug: prebuild
	$(info Building Debug Binary)
	$(CC) $(MAIN) $(IMGUI) $(INCLUDES) $(FLAGS) -g -o $(OUT)

# Cached Version of the Build
build-cached:
ifneq ($(wildcard $(CACHE)),)
	$(info Building Binary from Cache)
	$(CC) $(SRC) $(CACHE)/*.o $(INCLUDES) $(FLAGS) -o $(OUT)
endif

# Builds a Development Binary of the Application
build: prebuild
	$(info Building Binary)
	$(CC) $(MAIN) $(IMGUI) $(INCLUDES) $(FLAGS) -o $(OUT)


# CACHE SECTION #
CACHE_INCLUDES = $(addprefix -I../../, $(INCLUDE_PATHS))
cache-all: cache-utils cache-imgui

# Caches Source file includes to main.cc
CACHE_UTILS = $(addprefix ../../, $(filter-out $(SRC), $(MAIN)))
cache-utils: prebuild
	$(info Building App Object Files as Cache)
	cd $(CACHE); \
	$(CC) $(CACHE_UTILS) $(CACHE_INCLUDES) $(FLAGS) -c
	


# Caches ImGui - Object Files
CACHE_IMGUI = $(addprefix ../../, $(IMGUI))
cache-imgui: prebuild
	$(info Building ImGUI Object Files as Cache)
	cd $(CACHE); \
	$(CC) $(CACHE_IMGUI) $(CACHE_INCLUDES) $(FLAGS) -c


# Cleans up the Build Directory
prebuild:
ifeq ($(wildcard $(BUILD)),)
	$(shell mkdir $(BUILD))
	$(shell mkdir $(CACHE))
endif
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
