CC=gcc
CFLAGS=-c -Wall -pedantic -g -pg
LDFLAGS=-pg
SOURCES = $(wildcard src/*.c) $(wildcard src/*/*.c)
HEADERS = $(wildcard headers/*.h)
INCLUDES=-Iheaders -Ilibs/includes
LIBS=-lm
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=cge

all: $(SOURCES) $(HEADERS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(LIBS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJECTS)
