CXX = g++
SRC = main.cpp $(shell find Entity/ Levels/ SDLLibrary/Core SDLLibrary/Utils -name "*.cpp")
FLAGS = -ISDLLibrary $(shell sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf -lSDL2_gfx

all:
	$(CXX) $(SRC) $(FLAGS) -o EvadeSDL
