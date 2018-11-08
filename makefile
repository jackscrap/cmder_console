ogl = -lGL -lGLEW
sdl = -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

make: main.cpp
	g++ main.cpp $(ogl) $(sdl)
