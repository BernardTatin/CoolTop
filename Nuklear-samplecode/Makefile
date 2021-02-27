# Install
BIN = bin/demo

NUKEDIR := ${HOME}/git/Nuklear
# Flags
CFLAGS += -std=c99 -pedantic -O2 -I$(NUKEDIR) -Wall

SRC = main.c overview.c style.c calculator.c
OBJS = $(SRC:.c=.o)

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
	rm -f $(BIN) $(OBJS)

%.o:%.c
	$(CC) -c $< $(CFLAGS) -o $@

$(BIN): $(OBJS)
	@mkdir -p bin
	$(CC) $(OBJS) -o $@ $(LIBS)
