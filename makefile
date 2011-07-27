CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=
SOURCES=src/util.c src/config.c src/initialisation.c src/genops.c src/main.c
INCLUDES=-Iheaders -Ilibs/includes
LIBS=-Llibs
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=cge
BASEDIR=/Users/eoin/Workspaces/CGE

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	cd $(BASEDIR)
	$(CC) $(LDFLAGS) $(LIBS) $(OBJECTS) -o $@

.c.o:
	cd $(BASEDIR)
	$(CC) $(INCLUDES) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJECTS)