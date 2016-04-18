#   Mateus Cordeiro
#   2016
#   Makefile for QMKP
#

MAKEFILE = Makefile
SOURCES = input.cpp output.cpp solution.cpp pair_sorter.cpp item_sorter.cpp main.cpp
OBJECTS = input.o output.o solution.o pair_sorter.o item_sorter.o main.o
BINARIES = qmkp
INCLUDES = input.h output.h solution.h pair_sorter.h item_sorter.h


CC = g++ -std=c++11
CFLAGS = -ggdb # -O4 -g -DNDEBUG -pg
LFLAGS = -lm # -g -lm -pg

make: $(BINARIES)

$(OBJECTS):
	$(CC) -c $(SOURCES) $(INCLUDES)

all: $(BINARIES)

qmkp: $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LFLAGS)

lint:
	lint -h $(SOURCES)

clean:
	rm -f core *.o *.gch a.out $(BINARIES)
