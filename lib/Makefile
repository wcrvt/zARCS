##########################
## COMPILE/LINK OPTIONS ##
##########################

CC = gcc
LD = ld

CCFLAGS := -Wall -W -Weffc++ -O3		# warnings, optimization
LDFLAGS :=		# warnings, optimization

CCLIBPASS := -I.
LDLIBPASS := -L.

CCLIBTAR :=				# target library:
LDLIBTAR := 				# target library: libm.so,stdc++

CCOPTIONS := $(CCFLAGS) $(CCLIBPASS) $(CDLIBTAR)
LDOPTIONS := $(LDFLAGS) $(LDLIBPASS) $(LDLIBTAR)

###################
## TARGET FILES  ##
###################

TARGET = ARCS_LIBS.o
SRCS=$(shell ls *.cc)
OBJS=$(SRCS:.cc=.o)

.SUFFIXES:
.SUFFIXES:.cc .hh .o

####################
##  TASK TARGETS  ##
####################

all: $(TARGET)
	
# include .depend file
-include Makefile.depend

$(TARGET): $(OBJS)
	@$(LD) $(LDOPTIONS) -r -o $(TARGET) $(OBJS)

# generate object
.cc.o:
	@$(CC) $(CFLAGS) -c $<

# clean targets
.PHONY: clean
clean:
	@rm -f *.o
	@rm -f Makefile.depend

#  generate .depend file
.PHONY: dep
dep:
	@$(CC) $(CCOPTIONS) -MM $(SRCS) > Makefile.depend








