#   Mateus Cordeiro
#   2016
#   Makefile for QMKP
#

MAKEFILE = Makefile
SOURCES = ../input.cpp main.cpp
OBJECTS = ../input.o main.o
BINARIES = qmkp_article
INCLUDES = ../input.hpp


CC = g++ -std=c++11
CFLAGS = -ggdb # -O4 -g -DNDEBUG -pg
LFLAGS = -lm # -g -lm -pg

make: $(BINARIES)

$(OBJECTS):
	$(CC) -c $(SOURCES) $(INCLUDES)

all: $(BINARIES)

qmkp_article: $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LFLAGS)

lint:
	lint -h $(SOURCES)

clean:
	rm -f core *.o *.gch a.out $(BINARIES)
