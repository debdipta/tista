
CC=g++
CFLAGS=-g -c 
LDFLAGS=
DEBUG_FLAGS=-D$(debug_level)

SOURCES=tista.cpp logger.cpp connect.cpp soc.c HttpHandler.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tista

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE) 
