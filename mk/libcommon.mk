# ======================================================================
# libcommon.mk
# ======================================================================

AR = ar
ARFLAGS = rcs

LBIN := $(COOL_HOME)/lib
LSRCS :=  $(COOL_HOME)/src/environment.c $(COOL_HOME)/src/nuklear_glfw_gl3.c
LOBJS :=  $(addprefix $(LBIN)/, $(notdir $(LSRCS:.c=.o)))
LIBNAME := common
LIBFILE := $(LBIN)/lib$(LIBNAME).a

LIBS += -L$(LBIN) -l$(LIBNAME)

lib: $(LBIN) $(LIBFILE)

$(LBIN):
	@mkdir -p $(LBIN)

$(LIBFILE): $(LOBJS)
	$(AR) $(ARFLAGS) $@ $(LOBJS)


$(LBIN)/%.o: $(COOL_HOME)/src/%.c
	$(CC) -c $< $(CFLAGS) -o $@

.PHONY: lib
