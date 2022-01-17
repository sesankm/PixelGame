#pragma once
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "GameObject.h"

class Game {
public:

private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	std::vector<Layer> layers;
	SDL_Event event;
	Player* p;

public:
	Game(char* window_name, int win_x, int win_y, int win_w, int win_h);
	int handle_event();
	void add_layer(char* file_name, char* image_path);
	void run();
private:
	void update();
	void render();
};
