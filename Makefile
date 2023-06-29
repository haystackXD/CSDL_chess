all:
	gcc.exe *.c  -I .\include\SDL2 -L .\lib -L.\bin -lsdl2 -lsdl2_image -o .\bin\main.exe
	.\bin\main.exe

debug:
	gcc.exe *.c  -I .\include\SDL2 -L .\lib -L.\bin -lsdl2 -lsdl2_image -g -o .\bin\main.exe
	gdb.exe .\bin\main.exe