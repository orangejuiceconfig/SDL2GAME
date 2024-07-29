main: main.cpp
	g++ main.cpp -o main `sdl2-config --cflags --libs` -lSDL2_image -lSDL2main -lSDL2 
