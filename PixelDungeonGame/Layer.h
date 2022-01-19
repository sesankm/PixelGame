#pragma once
#include "GameObject.h"

class Layer {
private:
	SDL_Rect map_left;
	SDL_Rect map_right;
public:
	std::vector<std::vector<int>> map;
	std::vector<std::vector<Tile>> layer_tiles;
public:
	Layer(SDL_Renderer* renderer, char* file_name, char* image_path);
	void read_file(char* file_name);
	void create_layer(char* image_path, SDL_Renderer* renderer);
	void update(Player player);
};
