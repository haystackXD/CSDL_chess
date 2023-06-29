all:
	gcc *.c `sdl2-config --cflags --libs` -lSDL2_image -o /tmp/main
	/tmp/main

debug:
	gcc *.c `sdl2-config --cflags --libs` -lSDL2_image -g -o /tmp/main
	gdb /tmp/main
