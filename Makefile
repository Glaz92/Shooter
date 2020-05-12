CC      := g++
CFLAGS  := -std=c++17 -Wall -Wextra

SRC     := src
GUISRC  := gui/src
INC     := -Iinc -Igui/inc
SFML    := -DSFML_STATIC -Isfml/include -Lsfml/lib
BOX2D   := -Ibox2d/include -Lbox2d/lib
LIB        := -lsfml-window-s -lsfml-graphics-s -lsfml-audio-s -lsfml-system-s -lopengl32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg  -lwinmm -lgdi32 -lfreetype -lBox2D

BIN     := bin
EXE     := game.exe

all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(SRC)/*
    $(CC) $(CFLAGS) $(INC) $(SFML) $(BOX2D) $^ -o $@ $(LIB)

$(BIN)/$(EXE): $(GUISRC)/*
    $(CC) $(CFLAGS) $(INC) $(SFML) $(BOX2D) $^ -o $@ $(LIB)

clean:
    rm *.o $(EXECUTABLE)

run: all
    ./$(BIN)/$(EXECUTABLE)
