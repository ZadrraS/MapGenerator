CC=g++
CFLAGS=-Wall -c -g
LDFLAGS=
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system
INCLDS=-I.

SOURCES:=$(wildcard *.cpp)

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=feudo_sim

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLDS) $< -o $@

clean:
	find . -name \*.o -delete 