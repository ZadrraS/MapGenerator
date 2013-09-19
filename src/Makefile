CC=g++
CFLAGS=-Wall -c -g -std=c++11
LDFLAGS=
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system
INCLDS=-I.

SOURCES:=$(wildcard *.cpp map/*.cpp generation/*.cpp helpers/*.cpp)

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=feudo_sim

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLDS) $< -o $@

clean:
	find . -name \*.o -delete 