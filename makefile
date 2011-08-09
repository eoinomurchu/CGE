CC=gcc
CFLAGS=-c -Wall -g -pg
LDFLAGS=-pg
SOURCES=src/util.c src/config.c src/tree.c src/contextfree.c src/initialisation.c src/genops.c src/population.c src/main.c
INCLUDES=-Iheaders -Ilibs/includes
LIBS=
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=cge

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(LIBS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJECTS)
