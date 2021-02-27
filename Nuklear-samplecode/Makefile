# Install
BIN = demo

NUKEDIR := ${HOME}/git/Nuklear
# Flags
CFLAGS += -std=c99 -pedantic -O2 -I$(NUKEDIR)

SRC = main.c
OBJ = $(SRC:.c=.o)

ifeq ($(OS),Windows_NT)
BIN := $(BIN).exe
LIBS = -lglfw3 -lopengl32 -lm -lGLU32 -lGLEW32
else
	UNAME_S := $(shell uname -s)
	GLFW3 := $(shell pkg-config --libs glfw3)
	ifeq ($(UNAME_S),Darwin)
		LIBS := $(GLFW3) -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -lm -lGLEW -L/usr/local/lib
	else
		LIBS = $(GLFW3) -lGL -lm -lGLU -lGLEW
	endif
endif

all: $(BIN)

clean:
	rm -f bin/$(BIN) $(OBJS)

$(BIN):
	@mkdir -p bin
	$(CC) $(SRC) $(CFLAGS) -o bin/$(BIN) $(LIBS)
