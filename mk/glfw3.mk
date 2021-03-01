# ======================================================================
# glfw3.mk
# ======================================================================

here = $(shell pwd)
COOL_HOME := $(shell dirname $(here))

DBIN := bin
BIN := $(DBIN)/$(BINNAME)
OBJS := $(addprefix $(DBIN)/, $(notdir $(SRCS:.c=.o)))

NUKEDIR ?= ${HOME}/git/Nuklear
FONT_NAME ?= Karla-Regular.ttf
FONT_HEIGHT ?= 16
NUKEFONT := $(NUKEDIR)/extra_font/$(FONT_NAME)
# Flags
CDEFINES := -D'NUKEFONT="$(NUKEFONT)"' -DFONT_HEIGHT=$(FONT_HEIGHT)
CFLAGS += -std=c99 -Wall -pedantic -O2 -I$(NUKEDIR) -I../include $(CDEFINES)


ifeq ($(OS),Windows_NT)
	BIN := $(BIN).exe
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

all: lib $(DBIN) $(BIN)

clean:
	rm -f $(BIN) $(OBJS)

run: all
	./$(BIN)

$(DBIN):
	@mkdir -p $(DBIN)

$(DBIN)/%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS) -lm

.PHONY: all clean run
