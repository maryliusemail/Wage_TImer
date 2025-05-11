main: main.cpp
	@clang++ main.cpp -o main `pkg-config --cflags --libs sdl2` `pkg-config --cflags --libs sdl2_ttf` `pkg-config --cflags --libs sdl2_image`