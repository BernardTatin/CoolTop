# ======================================================================
# glfw3.mk
# ======================================================================

here = $(shell pwd)
COOL_HOME := $(shell dirname $(here))

BIN_DIR := bin
BIN_FILE := $(BIN_DIR)/$(BINNAME)
BIN_OBJS := $(addprefix $(BIN_DIR)/, $(notdir $(SRCS:.c=.o)))

NUKEDIR ?= ${HOME}/git/Nuklear
FONT_NAME ?= Karla-Regular.ttf
FONT_HEIGHT ?= 16
NUKEFONT := $(NUKEDIR)/extra_font/$(FONT_NAME)
# Flags
CDEFINES := -D'NUKEFONT="$(NUKEFONT)"' -DFONT_HEIGHT=$(FONT_HEIGHT)
CINCLUDES := -I$(NUKEDIR) -I../include
CFLAGS += -std=c99 -Wall -pedantic -O2  $(CDEFINES) $(CINCLUDES)


ifeq ($(OS),Windows_NT)
	BIN_FILE := $(BIN_FILE).exe
	LIBS := -lglfw3 -lopengl32 -lm -lGLU32 -lGLEW32
else
	UNAME_S := $(shell uname -s)
	GLFW3 := $(shell pkg-config --libs glfw3)
	ifeq ($(UNAME_S),Darwin)
		LIBS := $(GLFW3) -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -lm -lGLEW -L/usr/local/lib
	else
		LIBS := $(GLFW3) -lGL -lGLU -lGLEW
	endif
endif

include libcommon.mk

all: lib $(BIN_DIR) $(BIN_FILE)

clean:
	rm -f $(BIN_FILE) $(BIN_OBJS)

run: all
	./$(BIN_FILE)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(BIN_DIR)/%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

$(BIN_FILE): $(BIN_OBJS)
	$(CC) $(BIN_OBJS) -o $@ $(LIBS) -lm

.PHONY: all clean run
