all:
	gcc *.c  `sdl2-config --cflags --libs` -l SDL2_image -o ./bin/main
	./bin/main

debug:
	gcc *.c  `sdl2-config --cflags --libs` -l SDL2_image -g -o ./bin/main
	gdb ./bin/main
