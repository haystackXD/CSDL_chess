# compiler settings
CC=gcc

DEBUGGER=gdb

# required library linking 
LIBS=`sdl2-config --cflags --libs` -lSDL2_image

# files for compilation
CFILES=main.c gameworld.c Actors.c include/utils.c

# output file name
OUTPUT_FILE=./main.out

all:
	$(CC) $(CFILES) $(LIBS) -Wall -o $(OUTPUT_FILE)

run:
	$(OUTPUT_FILE)

debug:
	$(CC) $(CFILES) $(LIBS) -g -o $(OUTPUT_FILE) 
	$(DEBUGGER) -q $(OUTPUT_FILE)

clean:
	rm -rf $(OUTPUT_FILE)
