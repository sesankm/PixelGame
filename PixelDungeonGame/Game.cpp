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
	for (int i = 0; i < layers[1].layer_tiles.size(); i++) {
		for (int j = 0; j < layers[1].layer_tiles[i].size(); j++) {
			int map_num = layers[1].map[i][j];
			if (map_num != -1) {
				layers[1].layer_tiles[i][j].collision_rect.x = layers[1].layer_tiles[i][j].get_pos().x;
				layers[1].layer_tiles[i][j].collision_rect.y = layers[1].layer_tiles[i][j].get_pos().y;
				layers[1].layer_tiles[i][j].collision_rect.w = layers[1].layer_tiles[i][j].get_pos().w;
				layers[1].layer_tiles[i][j].collision_rect.h = layers[1].layer_tiles[i][j].get_pos().h;
			}
			if (map_num == 275 || map_num == 277 || map_num == 279 || map_num == 281) {
				layers[1].layer_tiles[i][j].collision_rect.x = layers[1].layer_tiles[i][j].collision_rect.x + layers[1].layer_tiles[i][j].collision_rect.w / 2;
				layers[1].layer_tiles[i][j].collision_rect.w /= 2;
			}
			else if (map_num == 276 || map_num == 278 || map_num == 280 || map_num == 282) {
				layers[1].layer_tiles[i][j].collision_rect.w /= 2;
			}
			else if (map_num <= 244 && map_num >= 237) {
				layers[1].layer_tiles[i][j].collision_rect.y = layers[1].layer_tiles[i][j].collision_rect.y + layers[1].layer_tiles[i][j].collision_rect.h / 2;
				layers[1].layer_tiles[i][j].collision_rect.h /= 2;
			}

			if (SDL_HasIntersection(&(player->collision_rect), &layers[1].layer_tiles[i][j].collision_rect)) {
				player->vel_x = 0;
				player->vel_y = 0;
				printf("asdfsadf\n");
			}

			SDL_SetRenderDrawColor(renderer, 10, 210, 10, 255);
			SDL_RenderDrawRect(renderer, &layers[1].layer_tiles[i][j].collision_rect);
			SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255);
		}
	}

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
