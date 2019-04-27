LANG = c
# LANG = c++
MACOS = false
MINGW = false
SDL = false
CURSES = true

CFLAGS = -Wall -g

ifeq ($(LANG),c)
	CC = gcc
	SRC_EXT = c
else
	CC = g++
	SRC_EXT = cpp
	CFLAGS += -std=c++1z
endif

INCLUDE_PATH = ./include
BIN_PATH = ./bin
LIBS_PATH = ./lib
OBJ_PATH = ./obj
SRC_PATH = ./src
SOURCES = $(wildcard $(SRC_PATH)/*.$(SRC_EXT))
OBJECTS = $(patsubst $(SRC_PATH)/%.$(SRC_EXT), $(OBJ_PATH)/%.o, $(SOURCES))
INCLUDES = -I $(INCLUDE_PATH)
LIBS = -L$(LIBS_PATH)
TARGET = bin/tetris

ifeq ($(MINGW),true)
	INCLUDES += -I C:/MinGW/include
	LIBS += -lmingw32
endif

ifeq ($(SDL),true)
	ifeq ($(MACOS),true)
		INCLUDES += -F/Library/Frameworks -I/Library/Frameworks/SDL2.framework/Headers
		LIBS += -framework SDL2
	else
		INCLUDES += -I thirdparty/SDL2/include
		LIBS += -lSDL2main -lSDL2
	endif
endif

ifeq ($(CURSES),true)
	LIBS += -lncursesw
endif

$(TARGET): $(OBJECTS) | $(BIN_PATH) $(INCLUDE_PATH) $(LIBS_PATH)
	@ echo [Linking $@]
	@ $(CC) $(CFLAGS) -o $@ $^ $(INCLUDES) $(LIBS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT) | $(OBJ_PATH) $(INCLUDE_PATH) $(SRC_PATH)
	@ echo [Compiling $@]
	@ $(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

$(BIN_PATH):
	@ mkdir -p $(BIN_PATH)

$(INCLUDE_PATH):
	@ mkdir -p $(INCLUDE_PATH)

$(LIBS_PATH):
	@ mkdir -p $(LIBS_PATH)

$(OBJ_PATH):
	@ mkdir -p $(OBJ_PATH)

$(SRC_PATH):
	@ mkdir -p $(SRC_PATH)

clean:
	@ echo [Cleaning project]
	@ rm -rf $(OBJ_PATH)
	@ rm -f $(TARGET)

run: $(TARGET)
	@ echo [Running project]
	@ $(TARGET)
	@ echo
