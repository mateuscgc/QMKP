#   Mateus Cordeiro
#   2016
#   Makefile for QMKP
#

MAKEFILE = Makefile
SOURCES = input.cpp output.cpp solution.cpp main.cpp
OBJECTS = input.o output.o solution.o main.o
BINARIES = hcp
INCLUDES = input.h output.h solution.h


CC = g++ -std=c++11
CFLAGS = -ggdb # -O4 -g -DNDEBUG -pg
LFLAGS = -lm # -g -lm -pg

make: $(BINARIES)

$(OBJECTS):
    $(CC) -c $(SOURCES) $(INCLUDES)

all:    $(BINARIES)

hcp:    $(OBJECTS)
        $(CC) -o $@ $(OBJECTS) $(LFLAGS)

lint:
    lint -h $(SOURCES)

clean:
    rm -f core *.o a.out $(BINARIES)
