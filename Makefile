##########################
## COMPILE/LINK OPTIONS ##
##########################

CC := gcc	# compiler
LD := gcc	# linker

CCFLAGS := -Wall -W -Weffc++ -O3		# warnings, optimization
LDFLAGS := -Wall -W -Weffc++ -O3	# warnings, optimization

CCLIBPASS := -I. -I./lib
LDLIBPASS := -L. -L./lib

CCLIBTAR :=				# target library:
LDLIBTAR := -lm -lstdc++	# target library: libm.so,stdc++

CCOPTIONS := $(CCFLAGS) $(CCLIBPASS) $(CDLIBTAR)
LDOPTIONS := $(LDFLAGS) $(LDLIBPASS) $(LDLIBTAR)

###################
## TARGET FILES  ##
###################

TARGET := ARCS
SRCS := $(shell ls  *cc)
OBJS := $(SRCS:%.cc=%.o)
LIBS := ./lib/ARCS_LIBS.o

.SUFFIXES:
.SUFFIXES: .cc .hh .o

####################
##  TASK TARGETS  ##
####################

# build application
#def: clean $(TARGET)
def: $(TARGET)
all: clean libfiles $(TARGET)

# build application
$(TARGET): $(OBJS) $(LIBS)
	@$(LD) $(LDOPTIONS) -o $@ $^

# generate object
.cc.o:
	@$(CC) $(CCOPTIONS) -c $< -o $@

# clean and compile libraries: reffer to ./lib/Makefile
libfiles:
	@$(MAKE) clean -s -C ./lib
	@$(MAKE) dep -s -C ./lib
	@$(MAKE) all -s -C ./lib
	
setup:
	@$(MAKE) setup -s -C ./FPGA

# clean targets
.PHONY: clean
clean: 
	@rm -f $(OBJS) $(TARGET)
	@$(MAKE) clean -s -C ./FPGA
