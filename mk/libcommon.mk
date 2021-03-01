# ======================================================================
# libcommon.mk
# ======================================================================

AR = ar
ARFLAGS = rcs

LIB_DIR := $(COOL_HOME)/lib
LIB_SOURCES :=  $(COOL_HOME)/src/environment.c $(COOL_HOME)/src/nuklear_glfw_gl3.c
LIB_OBJS :=  $(addprefix $(LIB_DIR)/, $(notdir $(LIB_SOURCES:.c=.o)))
LIB_NAME := common
LIB_FILE := $(LIB_DIR)/lib$(LIB_NAME).a

LIBS += -L$(LIB_DIR) -l$(LIB_NAME)

lib: $(LIB_DIR) $(LIB_FILE)

$(LIB_DIR):
	@mkdir -p $(LIB_DIR)

$(LIB_FILE): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $(LIB_OBJS)


$(LIB_DIR)/%.o: $(COOL_HOME)/src/%.c
	$(CC) -c $< $(CFLAGS) -o $@

cleanlib:
	rm -fv $(LIB_FILE) $(LIB_OBJS)

.PHONY: lib cleanlib
