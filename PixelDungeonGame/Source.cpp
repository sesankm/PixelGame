#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "Game.h"

using namespace std;


int main(int argc, char** argv) {
	Game g((char*) "Grimline", 100, 100, 900, 700);
	g.add_layer((char*)"Map_Floor.csv", (char*) "tileset.png");
	g.add_layer((char*)"Map_Trees.csv", (char*) "tileset.png");
 	g.add_layer((char*)"Map_Stones.csv", (char*) "tileset.png");
 	g.add_layer((char*)"Map_Decor.csv", (char*) "tileset.png");
	g.run();
	return 0;
}

/*
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Event event;
	SDL_Window* window = SDL_CreateWindow("Dungeon", 100, 100, 900, 700, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

	Layer t;
	t.read_file((char*)"Map_Floor.csv");
	t.create_layer((char*)"tileset.png", renderer);

	Layer t2;
	t2.read_file((char*)"Map_Trees.csv");
	t2.create_layer((char*)"tileset.png", renderer);


	Player p(renderer, (char*)"fHero_.png");
	int quit = false;

	p.camera.w = 900;
	p.camera.h = 700;

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = 1;
				break;
			}
			else if (event.type == SDL_KEYDOWN) {
				p.keyDown(event.key.keysym.sym);
			}
			else if (event.type == SDL_KEYUP) {
				p.keyUp(event.key.keysym.sym);
			}
		}

		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255);
		t.update(p.camera, p.get_vel_x(), p.get_vel_y());
		t2.update(p.camera, p.get_vel_x(), p.get_vel_y());
		p.update();
		p.camera.x = p.getX() + 70 - p.camera.w / 2;
		p.camera.y = p.getY() + 70 - p.camera.h / 2;


		for (int i = 0; i < t2.layer_tiles.size(); i++) {
			for (int j = 0; j < t2.layer_tiles[i].size(); j++) {
				int map_num = t2.map[i][j];
				if (map_num != -1) {
					t2.layer_tiles[i][j].collision_rect.x = (*t2.layer_tiles[i][j].getPos()).x;
					t2.layer_tiles[i][j].collision_rect.y = (*t2.layer_tiles[i][j].getPos()).y;
					t2.layer_tiles[i][j].collision_rect.w = (*t2.layer_tiles[i][j].getPos()).w;
					t2.layer_tiles[i][j].collision_rect.h = (*t2.layer_tiles[i][j].getPos()).h;
				}
				if (map_num == 275 || map_num == 277 || map_num == 279 || map_num == 281) {
					t2.layer_tiles[i][j].collision_rect.x = t2.layer_tiles[i][j].collision_rect.x + t2.layer_tiles[i][j].collision_rect.w / 2;
					t2.layer_tiles[i][j].collision_rect.w /= 2;
				}
				else if (map_num == 276 || map_num == 278 || map_num == 280 || map_num == 282) {
					t2.layer_tiles[i][j].collision_rect.w /= 2;
				}
				else if (map_num <= 244 && map_num >= 237) {
					t2.layer_tiles[i][j].collision_rect.y = t2.layer_tiles[i][j].collision_rect.y + t2.layer_tiles[i][j].collision_rect.h / 2;
					t2.layer_tiles[i][j].collision_rect.h /= 2;
				}

				SDL_SetRenderDrawColor(renderer, 10, 210, 10, 255);
				SDL_RenderDrawRect(renderer, &t2.layer_tiles[i][j].collision_rect);
				SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255);
			}
		}

		SDL_SetRenderDrawColor(renderer, 210, 210, 0, 255);
		SDL_RenderDrawRect(renderer, &p.camera);
		SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255);
		SDL_RenderPresent(renderer);
		Sleep(20);
	}
	SDL_Quit();
*/
