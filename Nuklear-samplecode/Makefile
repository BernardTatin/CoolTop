# Install
BIN = bin/demo

NUKEDIR ?= ${HOME}/git/Nuklear
FONT_NAME ?= Karla-Regular.ttf
FONT_HEIGHT ?= 16
NUKEFONT = $(NUKEDIR)/extra_font/$(FONT_NAME)
# Flags
CDEFINES := -D'NUKEFONT="$(NUKEFONT)"' -DFONT_HEIGHT=$(FONT_HEIGHT)
CFLAGS += -std=c99 -Wall -pedantic -O2 -I$(NUKEDIR)

SRC = main.c overview.c style.c calculator.c node_editor.c
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

%.o:%.c common.h
	$(CC) -c $< $(CFLAGS) -o $@

$(BIN): $(OBJS)
	@mkdir -p bin
	$(CC) $(OBJS) -o $@ $(LIBS)
