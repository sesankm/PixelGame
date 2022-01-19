#include "Game.h"

Game::Game(char* window_name, int win_x, int win_y, int win_w, int win_h) {
	window = SDL_CreateWindow(window_name, win_x, win_y, win_w, win_h, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
	player = new Player(renderer, (char*)"fHero_.png");
	(*player).camera.w = 900;
	(*player).camera.h = 700;
}

int Game::handle_event() {
	if (event.type == SDL_QUIT) {
		return 1;
	}
	else if (event.type == SDL_KEYDOWN) {
		(*player).key_down(event.key.keysym.sym);
	}
	else if (event.type == SDL_KEYUP) {
		(*player).key_up(event.key.keysym.sym);
	}
	return 0;
}

void Game::add_layer(char* file_name, char* image_path) {
	layers.push_back(Layer(renderer, file_name, image_path));
}

void Game::update() {
	for (int i = 0; i < layers.size(); i++)
		layers[i].update(*player);
	(*player).update();
}

void Game::render() {
	SDL_RenderPresent(renderer);
}

void Game::run() {
	int quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&event)) { if ((quit = handle_event()) == 1) break; }
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		update();
		render();
		Sleep(15);
	}
}
